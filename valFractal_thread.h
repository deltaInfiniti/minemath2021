#define foreach(a,b) for(int a=0; a < b; a++)

class valfractal_orbit {
public:
    double* bufferdata = NULL;
    bool hasbuffer = false;
    int  bufferlength = 0;
    int indexes_per_landing = 0;
    int iterations = 0; // should be bufferlength/indexex_per_landing
    double x = 0, y = 0;
    void build(double* buf, int len, int indexes, int iter, double xx, double yy) {
        bufferdata = buf;
        bufferlength = len;
        indexes_per_landing = indexes;
        iterations = iter;
        x = xx;
        y = yy;
    }
    void build_copy(double* buf, int iter, double xx, double yy, int indexes = 2) {
        if (hasbuffer)deletebuffer();
        bufferdata = new double[(iter * indexes) + 1];
        hasbuffer = true;
        double* plc = bufferdata, * buff = buf;
        foreach(n, iter) { // assume 2 indexes since that's all I use currently
            *plc = *buff; plc++; buff++;
            *plc = *buff; plc++; buff++;
        }

        bufferlength = iter * indexes;
        indexes_per_landing = indexes;
        iterations = iter;
        x = xx;
        y = yy;
    }
    double* walkpoint = NULL;
    int walkind = -1;
    void begin_walk() {
        walkpoint = bufferdata;
        walkind = 0;
    }
    bool walk(double& zx, double& zy) {
        if (walkind >= iterations || walkind == -1) { walkind = -1; return false; }
        zx = *walkpoint; walkpoint++;
        zy = *walkpoint; walkpoint++;
        walkind++;
        return true;
    }

    void deletebuffer() {
        if (hasbuffer)delete[] bufferdata;
        hasbuffer = false;
    }
    ~valfractal_orbit() {
        deletebuffer();
    }
};


class valfractal {
    int global_threadlock = 64;
public:
    valfractal_orbit* orbits;
    int totalorbits = 0;
    int* itsbuf;
    bool hasbuffer = false;
    int threadsidle = 0, threadsinpool=0;
    int maxthreads, threadplace=0;
    int threadsfinished = 0;
    
    int rwidth = 0, rheight = 0;
    double dimx = 0, dimy = 0;
    double dimxmax = 0, dimymax = 0;
    double dimw = 0, dimh = 0;
    double stepx = 0; stepy = 0;
    double cx, cy, bailout, relax;
    int maxits, rebuild;
    int type;
    BYTE* buffer;
    void* Mcallback=nullptr, * progCallback=nullptr;
    mutex job_mut;
    string threadstat = "";
    bool renderpause = false;
    unsigned long long int samplecount = 0, hitcount = 0;
    int samples_perthread = 500;

    int progress[64];
    bool running = false;
    bool threading_halt = false;
    
    
    valfractal(int w, int h) {

        rwidth = w; rheight = h;
        totalorbits = w * h;
        orbits = new valfractal_orbit[totalorbits];
        hasbuffer = true;
    }


    bool Prep_workerthread_job(double inx, double iny, double inw, double inh, double incx, double incy,
                                   void* inMcallback, int inrebuild, double inbailout, int intype,
                                   char* inbuffer, int incwid, int inchit, int inmaxthreads, void* inprogCallback) {
        if (running) {
            threadstat = "already rendering, can't prep threads";
            return false;
        }

        dimx = inx; dimy = iny; dimw = inw; dimh = inh; rwidth = incwid; rheight = inchit; 
        cx = incx; cy = incy; rebuild = inrebuild; bailout = inbailout; type = intype;
        Mcallback = inMcallback; progCallback = inprogCallback;
        stepx = dimw / rwidth;
        stepy = dimh / rheight;
        dimxmax = dimx + dimw;
        dimymax = dimy + dimh;
        foreach(bbb, 20)progress[bbb] = 0;

        return true;
    }
    void process_andro_roots() {
        cout << "starting to process ANDRO roots\n";
        G_Mandel_ANDRO_rootslistlen = 0;
        int roots = 0;
        if (type == 300 || type == 303)roots = arbitrary_newton_derbail_roots_mf(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, maxits, bailout, G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);
        if (type == 302)roots = arbitrary_newton_nova_derbail_roots_mf(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, maxits, bailout, G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);
        if (type == 301)roots = arbitrary_newton_julia_derbail_roots_mf(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, cx, cy, maxits, bailout, G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);



        double a, b;
        if (roots < 1) {
            cout << "no roots found with method specific root detection method, finding non-normalized roots\n";
            roots = arbitrary_newton_derbail_roots_mf(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, maxits, bailout, G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);
            if (roots < 1) {
                cout << "no roots found for current arbitrary equation\n";
                return;
            }

        }
        cout << roots << " roots found \n";
        foreach(i, G_Mandel_ANDRO_rootslistlen) {
            a = G_Mandel_ANDRO_rootslist[i * 2];
            b = G_Mandel_ANDRO_rootslist[(i * 2) + 1];
            if (vabs(a) < .00000001)a = 0;
            if (vabs(b) < .00000001)b = 0;
            cout << "if(VS_complex_rangecomp(zxcopy, zycopy," << a << ", " << b << ", 0.00001))return ((its*its) % (spaces*3))+(spaces*" << ((i + 1) % 5) << "); \n";
        }
        cout << "out of roots processing\n";

    }
    void render_itsbuf( double reduction = 0.0, double factor = 1.0, int maxv=maxits) {
        int* itsbufh = (int*)itsbuf, temp;
        char* bufh = buffer;
//        if (maxv > maxits)maxv = maxits;
        foreach(i, rwidth) {
            foreach(n, rheight) {
                temp = floor(((*itsbufh) - reduction) * factor);
                temp = Linear_color(temp, maxv);// maxv
                *bufh = GetBValue(temp); bufh++;
                *bufh = GetGValue(temp); bufh++;
                *bufh = GetRValue(temp); bufh++; bufh++;
                itsbufh++;
            }
        }

    }
    void render_orbits(int plane=0) {
        // plane- 0=crci 1=zrci
        cout << "rendering orbits for plane: " <<plane << "\n";
        valfractal_orbit* o;
        int xxx,yyy;
        this->begin_walk();
        BYTE* bufh = buffer;
        if (plane == 0) {
            while (this->walk(o, xxx, yyy)) {
                temp = Linear_color(o->iterations, maxits);// maxv
                *bufh = GetBValue(temp); bufh++;
                *bufh = GetGValue(temp); bufh++;
                *bufh = GetRValue(temp); bufh++; bufh++;
                itsbufh++;

            }
        }else{
            double zx, zy;
            BYTE* buft;
            while (this->walk(o, xxx, yyy)) {
                o->begin_walk();
                while (o->walk(zx, zy)) {
                    switch(plane){
                    case 1:
                        buft = (buffer + (zx + (yyy * rwidth)));

                        break;
                }
            }
        }
    }

    void Dispatch_workerthreads(int maxthreadsin) {
        if (running) {
            threadstat = "already rendering, can't dispatch threads";
            return;
        }
        running = true;
        if (type > 299 && type < 400) {
            process_andro_roots();
        }
        if (maxthreadsin > global_threadlock)maxthreadsin = global_threadlock;

        maxthreads = maxthreadsin; // threads can begin to wake now
        threadstat = "dispatched";
        threadsfinished = 0;
        unsigned long long militime = chrono_milli();
        unsigned long long time = 0;
        long int maxprogress = rwidth * rheight;
        unsigned long long int totalprogress = 0;
        unsigned long long int progr;

        while (threadsfinished != maxthreads) {

            totalprogress = 0;
            foreach(bbb, 20) totalprogress += progress[bbb];
            progr = (totalprogress * 100) / maxprogress;
            if (progr < 0)progr = 0;
            threadstat = ctostr(threadsinpool - threadsidle) + " rendering | " + ctostr(totalprogress) + ":" + ctostr(maxprogress);

            ((void(__cdecl*)(int))(progCallback))(progr);

            Sleep(4);
        }
        if (!threading_halt) {
            ((void(__cdecl*)(int))(progCallback))(100);
        }
        if (type >= 400 && type < 500) {
            cout << "into buddahbrot image renderer\n";
            int maxv = 0, minv = 10000000;
            int* itsbufh = (int*)itsbuf;
            unsigned long long int total = 0;
            foreach(i, 2000) {
                foreach(n, 2000) {
                    if (*itsbufh > maxv)maxv = *itsbufh;
                    if (*itsbufh < minv)minv = *itsbufh;
                    total += *itsbufh;
                    itsbufh++;
                }
            }
            hitcount = total;
            if (type == 419)render_itsbuf();
            else {
                double redu = minv, factor = maxits / (maxv - minv);
                render_itsbuf(redu, factor);
            }
        }
        unsigned long long ms;
        militime = chrono_milli() - militime;
        string rt = "render time: " + ctostr(militime / 1000) + "." + ctostr(militime % 1000) + "seconds";
        G_Mandel_threadstat = rt;
        cout << rt << "\n";
        maxthreads = 0;
        running = false;
        cout << "finished threaded rendering\n";

    }
    void join_threadpool() {
        job_mut.lock();
        threadsinpool++;
        threadsidle++;
        job_mut.unlock();
    }
    int join_threadpool_job() {
        while (maxthreads == 0 || threadplace >= maxthreads)   Sleep(8);
        job_mut.lock();
        if (threadplace >= maxthreads) return -1;
        int myplace = threadplace;
        threadplace++;
        threadsidle--;
        job_mut.unlock();
        
        return myplace;
    }
    int leave_threadpool_job() {
        job_mut.lock();
        finished++;
        threadsidle++;
        //cout << "thread " << myplace << " ended stepcounts x,y: " << x_stepcount<<","<<y_stepcount<<"\n";
        job_mut.unlock();
    }
    void resize(int w, int h) {
        rwidth = w; rheight = h;
        delete_buffers();
        totalorbits = w * h;
        orbits = new valfractal_orbit[totalorbits];
        hasbuffer = true;
    }

    valfractal_orbit& getorbit(int xx, int yy) {
        if (hasbuffer && xx < rheight && yy < rwidth && xx>0 && yy>0) return *(orbits + ((yy * rwidth) + xx));
    }

    valfractal_orbit* walkpoint = NULL;
    int walkind = -1;
    int walkx = 0, walky = 0;
    void begin_walk() {
        walkpoint = orbits;
        walkind = 0;
        walkx = 0; walky = 0;
    }

    bool walk(valfractal_orbit*& orbit, int& x, int& y) {
        if (walkind >= totalorbits || walkind == -1) { walkind = -1; return false; }
        orbit = walkpoint; walkpoint++;
        walkind++;
        walkx++;
        if (walkx >= rwidth) {
            walky++; walkx = 0;
        }
        x = walkx;
        y = walky;
        return true;
    }

    void delete_buffers() {
        if (hasbuffer)delete[] orbits;
        hasbuffer = false;
    }

    ~valfractal() {
        delete_buffers();
    }


    int budda_crciPlane_jset_step(double xin, double yin, double* trackbuff, int* myhit_data,) {
        double n = xin, i = yin;
        int ctch = ((int(__cdecl*)(double, double, double, double, int, double, double*))(Mcallback)) (xin, yin, cx, cy, maxits, bailout, trackbuff);

        int hits = 0;
        if (ctch < maxits) {// check if escapes-
            int cModifier = floor(((yin - dimy) / stepy) * rwidth);
            cModifier += (xin - dimx) / stepx;
            myhit_data[(cModifier)] += ctch;//myhit_data[xx][yy]++;
            hits += ctch;
        }
        if (hits == 0)return 0;
        return 1;

    }

    void threadprocess_budda_plane_jset(int myplace, double yy) {
        //int* itsbuf, mutex& workmut, double dimx, double ymin, double xmax, double ymax, int maxits, double bail, int samples, void* function, int& progress, int numer, int denom, int myplace, int maxthreads, int tstepsy, int tstepsx, double basex, double yy, double stepx, double stepy, int type, double cx, double cy
        job_mut.lock();
        auto myhit_data = new int[totalorbits];

        bool isdone = false;
        foreach(i, rwidth) { foreach(n, rheight) { myhit_data[i + (n * rwidth)] = 0; } }
        job_mut.unlock();
        double* trackbuff = new double[maxits * 5];
        double xx;
        double* tb_h = trackbuff;
        double xwid = dimxmax - dimx, ywid = dimymax - dimy;

        //auto funcpoint = mandel_buddah_thread_process_step_zrciPlane_jset;
        bool isjset = false;
        //   if (type == 416) funcpoint = mandel_buddah_thread_process_step_zrcrPlane;
        //   if (type == 417) funcpoint = mandel_buddah_thread_process_step_crziPlane;
        //   if (type == 418) funcpoint = mandel_buddah_thread_process_step_ciziPlane;
        //if (type == 419) funcpoint = mandel_buddah_thread_process_step_crciPlane_jset;

        int ctch = 0,hold;
        for (int y = myplace; y < rheight - 1; y += maxthreads) {
            xx = dimx;
            for (int x = 0; x < rwidth; x++) {
                if (threading_halt) { y = rheight; break; }
                //switch numer/denom with min_iterations
                switch (type) {
                case 419:
                    hold = budda_crciPlane_jset_step(xx, yy, trackbuff, myhit_data);
                    break;
                }
                ctch += hold;
                //(*itsbuf) = mandel_worker_thread_process(xx, yy, cx, cy, maxits, bailout, function, type);
                orbits[(y * rwidth) + x].build_copy(trackbuff, hold, xx, yy);
                xx += stepx;
                progress[myplace]++;
            }
            yy += stepy;

        }
        int* itsh = itsbuf;
        job_mut.lock();
        foreach(i, rwidth) { foreach(n, rheight) { *itsh += myhit_data[n + (i * rwidth)]; itsh++; } }
        samplecount += ctch;
        job_mut.unlock();
        delete[] trackbuff;
        delete[] myhit_data;
    }
    void thread_function(int myplace) {
        double yy = dimy + (stepy * myplace);
        switch (type) {
        case 419:
            //mandel_buddahplane_thread_process_jset(itsbuf,job_mut, dimx, dimy, dimw, dimh, maxits, bailout,samples_perthread, Mcallback, progress[myplace], cx, cy
            //    , myplace, maxthreads, rwidth, rheight, dimx, yy, stepx, stepy, type, cx, cy);
            threadprocess_budda_plane_jset(myplace, yy);
            break;
        default:
            thread_linearprocess(myplace, yy);
            break;
        }
    }
    void thread_linearprocess(int myplace,double yy) {
        int* itsbufh = itsbuf + (myplace * rwidth);
        BYTE* bufferh = (BYTE*)buffer;
        double xx; int color;
        for (int y = myplace; y < rheight - 1; y += maxthreads) {
            xx = dimx;
            for (int x = 0; x < rwidth; x++) {
                if (threading_halt) { y = rheight; break; }
                if (!rebuild || (rebuild && rebuild == (*itsbufh))) {
                    (*itsbufh) = worker_thread_callback_process(xx, yy);
                    color = Linear_color((*itsbufh), maxits);
                    *bufferh = GetBValue((COLORREF)color); bufferh++;
                    *bufferh = GetGValue((COLORREF)color); bufferh++;
                    *bufferh = GetRValue((COLORREF)color); bufferh += 2;
                }
                else bufferh += 4;
                itsbufh++;
                xx += stepx;
                //x_stepcount++;
                progress[myplace]++;
            }
            bufferh += (rwidth * (maxthreads - 1) * 4);
            itsbufh += (rwidth * (maxthreads - 1));
            //y_stepcount++;
            yy += stepy;
        }
    }
    int worker_thread_callback_process(double xh, double yh) {
        int ret = 0;

        switch (type) {

        case 0:
            ret = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
            break;
        case 1: // Jset_brot calculation
            ret = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (cx, cy, xh, yh, maxits, bailout);
            break;
        case 2:
            ret = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (0, yh, cx + xh, cy, maxits, bailout);
            break;
        case 3:
            ret = ((int(__cdecl*)(double, double, double, double, int, int))(Mcallback)) (yh, 0, cx + xh, cy, maxits, bailout);
            break;
        case 4:
            ret = ((int(__cdecl*)(double, double, double, double, int, double))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
            break;
        default:
        case 300: // arbitrary newton same callback as brot with bail
        case 302: // newton nova filler
            ret = ((int(__cdecl*)(double, double, int, double))(Mcallback)) (xh, yh, maxits, bailout);
            break;
        case 301: // arbitrary newton same callback as brot with bail
        case 303: // arbitrary newton same callback as brot with bail but roots calculated without cx/cy contribution.
        case 304:
            ret = ((int(__cdecl*)(double, double, double, double, int, double))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
            break;
        case 100: // regular brot types
            ret = ((int(__cdecl*)(double, double, int))(Mcallback)) (xh, yh, maxits);
            break;
        case 101: // regular brot types with bail
            ret = ((int(__cdecl*)(double, double, int, double))(Mcallback)) (xh, yh, maxits, bailout);
            break;
        case 200: // newton fractal
            ret = ((int(__cdecl*)(double, double, int, double))(Mcallback)) (xh, yh, maxits, bailout);
            break;
        case 201: // newton fractal
            ret = ((int(__cdecl*)(double, double, double, double, int, double))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
            break;

        }
        return ret;

}ValFractal(2000,2000);






/*

void valfractal::thread_function(int myplace) {
    switch (type) {
    case 400:
    case 401:
        //Note: must clear iterationsBuffer before iterating here. 
        //this is for mandelbudah rendering
        mandel_buddah_thread_process(itsbufbase, ValFractal.jobinfo.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, ValFractal.jobinfo.progress[myplace], 9, 10);
        break;
    case 402:
    case 403:
        //Note: must clear iterationsBuffer before iterating here. 
        //this is for mandelbudah rendering
        mandel_buddah_thread_process(itsbufbase, ValFractal.jobinfo.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, ValFractal.jobinfo.progress[myplace], cx, cy);
        break;
    case 405: // these are for the extra plane renderers, crzi etc.
    case 406:
    case 407:
    case 408:
    case 409:

        mandel_buddahplane_thread_process(itsbufbase, ValFractal.jobinfo.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, ValFractal.jobinfo.progress[myplace], cx, cy
            , myplace, maxthreads, tstepsy, tstepsx, basex, yy, stepx, stepy, type);
        break;
    case 419:

        mandel_buddahplane_thread_process_jset(itsbufbase, ValFractal.jobinfo.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, ValFractal.jobinfo.progress[myplace], cx, cy
            , myplace, maxthreads, tstepsy, tstepsx, basex, yy, stepx, stepy, type, cx, cy);
        break;

    default:
        //thread_linearprocess(myplace);
        break;
    }
}


*/

void ValFractal_workerthread(void* a) {



    int myplace = 0;
    while (1) {
        myplace = ValFractal.join_threadpool_job();
        if (myplace == -1)continue;
        //double xwid = basex + (tstepsx * stepx), ywid = basey + (tstepsy * (stepy / maxthreads));
        ValFractal.thread_function(myplace);
        //cout << "thread " << myplace << " started with type=" << type << "tstepsy: " << tstepsy << "\n";
        ValFractal.leave_threadpool_job();
    }
}


/*deprecated
struct valfractal_workerthread_info {
    int place = 0;
    int maxthreads = 0;
    mutex job_mut;
    double cx, cy;
    int maxits;
    double bailout;
    double basex;
    double basey;
    double stepx;
    double stepy;
    int totalstepsx;// grid width
    int totalstepsy;// grid height
    double windowwidth;
    double windowheight;
    void* buffer;
    void* function;
    int* itsbuf;
    int type;
    int finished;
    double rebuild;

    int progress[20];
    int threadsinpool = 0;
    int threadsidle = 0;
    bool running = false;
    int global_maxthreadslock = 64;
};
valfractal_workerthread_info_copy_simple(valfractal_workerthread_info& out, valfractal_workerthread_info& in) {
    out = in;
}
valfractal_workerthread_info_copy(valfractal_workerthread_info& out, valfractal_workerthread_info& in) {

    out.place = in.place;
    out.maxthreads = in.maxthreads;
    out.job_mut = in.job_mut;
    out.cx = in.cx;
    out.cy = in.cy;
    out.maxits = in.maxits;
    out.bailout = in.bailout;
    out.basex = in.basex;
    out.basey = in.basey;
    out.stepx = in.stepx;
    out.stepy = in.stepy;
    out.totalstepsx = in.totalstepsx;
    out.totalstepsy = in.totalstepsy;
    out.buffer = in.buffer;
    out.windowwidth = in.windowwidth;
    out.windowheight = in.windowheight;
    out.function = in.function;
    out.itsbuf = in.itsbuf;
    out.type = in.type;
    out.finished = in.finished;
    out.rebuild = in.rebuild;

}

class valfractal_thread {
public:
    valfractal_workerthread_info info;
    //   BYTE* buffer = NULL;
    int myplace = -1;
    int xx = 0, yy = 0;
    int place = 0;
    int maxthreads = 0;
    mutex job_mut;
    double cx, cy;
    int maxits;
    double bailout;
    double basex;
    double basey;
    double stepx;
    double stepy;
    int totalstepsx;// grid width
    int totalstepsy;// grid height
    double windowwidth;
    double windowheight;
    void* function;
    int* itsbuf;
    int type;
    int finished;
    double rebuild;
    void init(valfractal_workerthread_info& in) {
        place = in.place;
        maxthreads = in.maxthreads;
        job_mut = in.job_mut;
        cx = in.cx;
        cy = in.cy;
        maxits = in.maxits;
        bailout = in.bailout;
        basex = in.basex;
        basey = in.basey;
        stepx = in.stepx;
        stepy = in.stepy;
        totalstepsx = in.totalstepsx;
        totalstepsy = in.totalstepsy;
        buffer = in.buffer;
        windowwidth = in.windowwidth;
        windowheight = in.windowheight;
        function = in.function;
        itsbuf = in.itsbuf;
        type = in.type;
        finished = in.finished;
        rebuild = in.rebuild;
        myplace = info.place;
        buffer = (BYTE*)in.buffer;
        buffer += (info.tstepsx * info.myplace * 4);
        //itsbufbase = itsbuf;
        info.itsbuf += info.tstepsx * myplace; //*4?
        xx = info.basex;
        yy = basey + (stepy * myplace);
        info.stepy *= (maxthreads);
    }
};*/