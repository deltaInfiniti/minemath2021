#pragma once

void newton_derbail_itteratemf(double x, double y, int* factors, int factorslen, double& rx, double& ry, double relax = 1.0) {
    if (x == 0 && y == 0)return;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int xe, xf;
    double xntot = 0, yntot = 0, xdtot = 0, ydtot = 0;
    bool neg = false;
    bool needsconstnegone = true;
    // loop through factorslen, factors[x*2]=xf [+1]=xe
    foreach(i, factorslen) {
        xf = factors[i * 3];
        xe = factors[(i * 3) + 1];
        neg = factors[(i * 3) + 2] == 1;
        if (xe == 0) {
            if (!neg)xntot += xf;
            else xntot -= xf;
            needsconstnegone = false;
            continue;
        }
        if (xe == -1) { // negative xe means const i
            if (!neg)yntot += xf;
            else yntot -= xf;
            continue;
        }
        VS_complex_exp(zx, zy, xe, zxcopy, zycopy);
        zxcopy *= xf;
        //zxcopy -= 1;
        if (!neg) {
            xntot += zxcopy;
            yntot += zycopy;
        }
        else {
            xntot -= zxcopy;
            yntot -= zycopy;
        }
        VS_complex_exp(zx, zy, xe - 1, xx, yy);
        xx *= (xe - 1) * xf; // might need to change that.
        yy *= (xe - 1) * xf;
        if (!neg) {
            xdtot += xx;
            ydtot += yy;
        }
        else {
            xdtot -= xx;
            ydtot -= yy;
        }
    }
    if (needsconstnegone)xntot -= 1;// assumed ((qz^n, qqz^n-1...)(- 1)) constant
    VS_complex_div(xntot, yntot, xdtot, ydtot, xx, yy);
    xx *= relax;
    yy *= relax;
    rx = zx - xx;
    ry = zy - yy;

}
newton_fractal arbitrary_newton_derbail_root_process_mf(double x, double y, int* factors, int factorslen, int maxits, double bail) {
    newton_fractal ret;
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    double zxm1 = 0, zym1 = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, factors, factorslen, zxcopy, zycopy);

        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.000000001)) {
            ret.its = its;
            ret.x = zxcopy;
            ret.y = zycopy;
            ret.cat = 1;
            if (zxcopy == zx && zycopy == zy) ret.cat = 1;            // report as definite root;
            return ret;
        }
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    ret.its = its;
    ret.x = zxcopy;
    ret.y = zycopy;
    ret.cat = 0;
    return ret;
}
int ANDRO_addtoarray(double x, double y, double* arr, int& len) {


    if (vabs(x) < .000000001)x = 0;
    if (vabs(y) < .000000001)y = 0;
    double* harr = arr;
    if (len > 1000) {
        cout << "len too long" << endl;
        pause();
    }
    foreach(i, len) {
        if (VS_complex_rangecomp(x, y, *harr, *(harr + 1), 0.00001))return i;
        if (*harr == x && *(harr + 1) == y)return i;
        harr += 2;
    }
    *harr = x;
    harr++;
    *harr = y;
    len++;
    return len;
}
int arbitrary_newton_derbail_roots_mf(int* factors, int factorslen, int maxits, double bail, double* arr, int& arrlen) {
    newton_fractal val;
    double* pla;
    // process a sample of spaces to find roots.  
    for (double n = -3.0; n < 3.0; n += .002) {
        val = arbitrary_newton_derbail_root_process_mf(n, n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(0, n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(n, 0, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(n, -n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(n, sin(n), factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_derbail_root_process_mf(cos(n), n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

    }
    return arrlen;
}

newton_fractal arbitrary_newton_nova_derbail_root_process_mf(double x, double y, int* factors, int factorslen, int maxits, double bail) {
    newton_fractal ret;
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    double zxm1 = 0, zym1 = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, factors, factorslen, zxcopy, zycopy);
        zxcopy += x;
        zxcopy += y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000000001)) {
            ret.its = its;
            ret.x = zxcopy;
            ret.y = zycopy;
            ret.cat = 0;
            if (zxcopy == zx && zycopy == zy) ret.cat = 1;            // report as definite root;
            return ret;
        }
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    ret.its = its;
    ret.x = zxcopy;
    ret.y = zycopy;
    ret.cat = 0;
    return ret;
}
int arbitrary_newton_nova_derbail_roots_mf(int* factors, int factorslen, int maxits, double bail, double* arr, int& arrlen) {
    newton_fractal val;
    double* pla;
    // process a sample of spaces to find roots.  
    cout << "into nova roots process\n";
    for (double n = -3.0; n < 3.0; n += .002) {
        val = arbitrary_newton_nova_derbail_root_process_mf(n, n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(0, n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(n, 0, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(n, -n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(n, sin(n), factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_nova_derbail_root_process_mf(cos(n), n, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

    }
    return arrlen;
}
newton_fractal arbitrary_newton_julia_derbail_root_process_mf(double x, double y, double cx, double cy, int* factors, int factorslen, int maxits, double bail) {
    newton_fractal ret;
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    double zxm1 = 0, zym1 = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, factors, factorslen, zxcopy, zycopy);
        zxcopy += cx;
        zxcopy += cy;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.0000001)) {
            ret.its = its;
            ret.x = zxcopy;
            ret.y = zycopy;
            ret.cat = 1;
            if (zxcopy == zx && zycopy == zy) ret.cat = 1;            // report as definite root;
            return ret;
        }
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    ret.its = its;
    ret.x = zxcopy;
    ret.y = zycopy;
    ret.cat = 0;
    return ret;
}
int arbitrary_newton_julia_derbail_roots_mf(int* factors, int factorslen, double cx, double cy, int maxits, double bail, double* arr, int& arrlen) {
    newton_fractal val;
    double* pla;
    // process a sample of spaces to find roots.  
    cout << "into julia roots process\n";
    for (double n = -3.0; n < 3.0; n += .001) {
        val = arbitrary_newton_julia_derbail_root_process_mf(n, n, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(0, n, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(n, 0, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(n, -n, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(n, sin(n), cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(cos(n), n, cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

        val = arbitrary_newton_julia_derbail_root_process_mf(cos(n), sin(n), cx, cy, factors, factorslen, maxits, bail);
        if (val.cat == 1)ANDRO_addtoarray(val.x, val.y, arr, arrlen);

    }
    return arrlen;
}

string arbitrary_newton_derbail_roots_outputmf(int* factors, int factorslen, int maxits, double bail) {
    double arr[2000];
    foreach(i, 2000)arr[i] = 0.0;
    int arrlen = 0;
    arrlen = arbitrary_newton_derbail_roots_mf(factors, factorslen, maxits, bail, (double*)arr, arrlen);
    cout << arrlen << " roots detected\n";
    int a, b;
    foreach(i, arrlen) {
        a = arr[i * 2];
        b = arr[(i * 2) + 1];
        //if (vabs(a) < .000000001)a = 0;
        //if (vabs(b) < .000000001)b = 0;
        cout << "if(VS_complex_rangecomp(zxcopy, zycopy," << a << ", " << b << ", 0.00001))return ((its*its) % (spaces*3))+(spaces*" << ((i + 1) % 5) << "); \n";
    }

    return "done";
}

void ANDRO_factors_removeExp(int xe, int* factors, int& factorslen) {
    foreach(i, factorslen) {
        if (factors[(i * 3) + 1] == xe) {
            factorslen--;
            if (i == factorslen) return;
            factors[(i * 3)] = factors[(factorslen * 3)];
            factors[(i * 3) + 1] = factors[(factorslen * 3) + 1];
            factors[(i * 3) + 2] = factors[(factorslen * 3) + 2];
        }
    }

}

string ANDRO_factors_str(int* factors, int factorslen) {

    int xe, xf;
    bool neg = false;
    // loop through factorslen, factors[x*2]=xf [+1]=xe
    string ret = "F(x)=";
    foreach(i, factorslen) {
        xf = factors[i * 3];
        xe = factors[(i * 3) + 1];
        if (factors[(i * 3) + 2] == 1)ret += "-";
        else if (i != 0) ret += "+";
        if (xe == -1) ret += " (" + ctostr(xf) + "i) ";
        else if (xe == 0) ret += " (" + ctostr(xf) + ") ";
        else ret += " (" + (xf == 1 ? "" : ctostr(xf)) + "z^" + ctostr(xe) + ") ";
    }

    return ret;

}
string ANDRO_Equation() {
    return ANDRO_factors_str(G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen);
}
string ANDROctostr(double a) {
    if (a == 1.0)return "1";
    if (vabs(a) < 0.0000001) return "0";
    char buff[25];
    sprintf(buff, "%2.6f", a);
    return string(buff);
}
string ANDRO_roots_str(double* roots, int rootslen) {
    string ret = "";
    foreach(i, rootslen) {
        ret += "(" + ANDROctostr(roots[i * 2]) + "," + ANDROctostr(roots[1 + (i * 2)]) + ") ";
        if (i != rootslen - 1)ret += ",";
    }
    return ret;
}
string ANDRO_Roots() {
    return ANDRO_roots_str(G_Mandel_ANDRO_rootslist, G_Mandel_ANDRO_rootslistlen);

}
void ANDRO_factorlist_alter(int xf, int xe, bool neg, int* factors, int& factorslen) {
    int xff;
    foreach(i, factorslen) {
        xff = factors[i * 3];
        if (xe == factors[(i * 3) + 1]) {
            if (neg != (factors[(i * 3) + 2] == 1)) factors[i * 3] -= xf;
            else factors[i * 3] += xf;
            if (factors[i * 3] == 0)ANDRO_factors_removeExp(xe, factors, factorslen);
            return;
        }
    }
    factors[factorslen * 3] = xf;
    factors[(factorslen * 3) + 1] = xe;
    factors[(factorslen * 3) + 2] = (neg ? 1 : 0);
    factorslen++;
}
double G_Mandel_ANDRO_relax = 1;
int calc_ANDRO(double x, double y, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);

        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }

        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_julia(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int spaces = maxits / G_Mandel_ANDRO_rootslistlen + 1;
    int bailcount = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy += cx;
        zycopy += cy;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            if (bailcount++ > 100)return its;

        }
        else bailcount = 0;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_nova(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;// zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy += x;
        zycopy += y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            return its;

        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_novaB(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;// zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy += cx;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            return its;

        }
        //if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_novaC(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = G_Mandel_ANDRO_rootslist[0], zy = G_Mandel_ANDRO_rootslist[1];// zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy += x;
        zycopy += y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            return its;

        }
        //if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_novaE(double x, double y, double cx, double cy, int maxits, double bailout) {
    int spaces = maxits / 7;
    int plc = cx;
    if (plc >= G_Mandel_ANDRO_rootslistlen) {
        plc = 0;
    }
    int its = 1;
    double xx, yy, zxcopy, zycopy,
        //   zx = G_Mandel_ANDRO_rootslist[plc*2],
        //    zy = G_Mandel_ANDRO_rootslist[(plc*2)+1];// 
        zx = 1, zy = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy += x;
        zycopy += y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            return its;

        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_novaF(double x, double y, double cx, double cy, int maxits, double bailout) {
    int plc = floor(cx);
    if (plc >= G_Mandel_ANDRO_rootslistlen) {
        plc = 0;
    }
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = G_Mandel_ANDRO_rootslist[plc * 2], zy = G_Mandel_ANDRO_rootslist[(plc * 2) + 1];// zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy -= x;
        zycopy -= y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            return its;

        }
        //if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_novaG(double x, double y, double cx, double cy, int maxits, double bailout) {
    int plc = floor(cx);
    if (plc >= G_Mandel_ANDRO_rootslistlen) {
        plc = 0;
    }
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = G_Mandel_ANDRO_rootslist[plc * 2], zy = G_Mandel_ANDRO_rootslist[(plc * 2) + 1];// zx = x, zy = y;
    int spaces = maxits / 7;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy += x;
        zycopy += y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            return its;

        }
        //if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_novajulia(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int spaces = maxits / G_Mandel_ANDRO_rootslistlen;
    int bailcount = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy += cx + x;
        zycopy += cy + y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            if (bailcount++ > 10)return its;

        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}
int calc_ANDRO_novajuliaB(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = cx, zy = cy;
    int spaces = maxits / G_Mandel_ANDRO_rootslistlen;
    int bailcount = 0;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);
        zxcopy += x;
        zycopy += y;
        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    its += its;
                    its %= (spaces * 2);// +spaces / 2;
                    its += spaces * (i % 6);
                    return its;
                }
            }
            if (bailcount++ > 10)return its;

        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return maxits;
}