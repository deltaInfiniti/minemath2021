#pragma once



int calc_mandle_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > bail)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        its++;
    }
    return its;
}
/*
-2.96975927166248
-0.83089024430443
4.61209878610413
1.67078048860887
*/
int calc_mandle_magnetm2_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) + 2;
    consfacty -= (y * 3);
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        //numerx = denomx, numery = denomy;
        VS_complex_mulLD(denomx, denomy, zx, zy, numerx, numery);
        denomx *= 3;
        denomy *= 3;
        // at this point, we have z^3/3z^2
        VS_complex_mulLD(threecx - 3, threecy, zx, zy, zxcopy, zycopy);
        numerx += zxcopy;
        numery += zycopy;
        VS_complex_mulLD(threecx - 6, threecy, zx, zy, zxcopy, zycopy);
        denomx += zxcopy;
        denomy += zycopy;
        // at this point we have  z^3+ 3(c-1)z / 3z^2 + 3(c-2)z
        numerx += consfactx;
        numery += consfacty;
        denomx += consfactx + 1;
        denomy += consfacty;

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .00000000001)) return its;
        its++;

        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
    }
    return its;
}
int calc_mandle_magnetm2_true_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) - 2;
    consfacty -= (y * 3);
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        //numerx = denomx, numery = denomy;
        VS_complex_mulLD(denomx, denomy, zx, zy, numerx, numery);
        denomx *= 3;
        denomy *= 3;
        // at this point, we have z^3/3z^2
        VS_complex_mulLD(threecx, threecy, zx, zy, zxcopy, zycopy);
        numerx += zxcopy - (zx * 3);
        numery += zycopy - (zy * 3);
        denomx += zxcopy - (zx * 6);
        denomy += zycopy - (zy * 6);
        // at this point we have  z^3+ 3(c-1)z / 3z^2 + 3(c-2)z
        numerx += consfactx;
        numery += consfacty;
        denomx += consfactx + 1;
        denomy += consfacty;

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true_buddahb(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) - 2;
    consfacty -= (y * 3);
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        //numerx = denomx, numery = denomy;
        VS_complex_mulLD(denomx, denomy, zx, zy, numerx, numery);
        denomx *= 3;
        denomy *= 3;
        // at this point, we have z^3/3z^2
        VS_complex_mulLD(threecx, threecy, zx, zy, zxcopy, zycopy);
        numerx += zxcopy - (zx * 3);
        numery += zycopy - (zy * 3);
        denomx += zxcopy - (zx * 6);
        denomy += zycopy - (zy * 6);
        // at this point we have  z^3+ 3(c-1)z / 3z^2 + 3(c-2)z
        numerx += consfactx;
        numery += consfacty;
        denomx += consfactx + 1;
        denomy += consfacty;

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}

int calc_mandle_magnetm1_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    // c^2-3c-2
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = ((zx * 2) + x) - 2; denomy = ((zy * 2) + y);
        numerx = zx; numery = zy;
        VS_complex_squareLD(numerx, numery);
        numerx += x - 1;
        numery += y;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        zycopyb = zy;
        zxcopyb = zx;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        its++;
    }
    return its;
}

int calc_mandle_Euler_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = 0, zy = 0;
    double* trackbufff = trackbuff;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        its++;
    }
    return its;
}

int calc_ANDRO_buddah(double x, double y, int maxits, double bailout, double* trackbuff) {
    int its = 1;
    double xx, yy, zxcopy, zycopy, zx = x, zy = y;
    int spaces = maxits / 7;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        newton_derbail_itteratemf(zx, zy, G_Mandel_ANDRO_factorslist, G_Mandel_ANDRO_factorslistlen, zxcopy, zycopy, G_Mandel_ANDRO_relax);

        if (VS_complex_rangecomp(zxcopy, zycopy, zx, zy, 0.00000001)) {

            foreach(i, G_Mandel_ANDRO_rootslistlen) {
                if (VS_complex_rangecomp(zxcopy, zycopy, G_Mandel_ANDRO_rootslist[i * 2], G_Mandel_ANDRO_rootslist[1 + (i * 2)], 0.00000001)) {
                    return its;
                }
            }

        }
        if (vabs(zxcopy) + vabs(zycopy) > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        its++;
    }
    return maxits;
}

int calc_ANDRO_novaE_buddah(double x, double y, int maxits, double bailout, double* trackbuff) {
    int spaces = maxits / 7;
    int its = 1;
    double xx, yy, zxcopy, zycopy,
        //   zx = G_Mandel_ANDRO_rootslist[plc*2],
        //    zy = G_Mandel_ANDRO_rootslist[(plc*2)+1];// 
        zx = 1, zy = 0;
    double* trackbufff = trackbuff;
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
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        its++;
    }
    return maxits;
}
//((-c + 2 z - c z + c z^2 - 2 z^3 + c z^3)/(-2 + c) ) /z^2
int calc_mandle_weirdMag_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    
    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -=  2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = ((-x) + zx + zx);
        numery = ((-y) + zy + zy);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx+ zhx);
        numery -= (zhy+ zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx += zhx ;
        numery += zhy ;



        VS_complex_div(numerx, numery, consdenomx, consdenomy, zx, zy);
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        //if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}

int calc_mandle_weirdMag_buddahB(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = (zx + zx-x);
        numery = ( + zy + zy-y);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);// zh=cz
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx -= zhx;
        numery -= zhy;



        VS_complex_div(numerx, numery, consdenomx, consdenomy, zx, zy);
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        //if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMagJset_buddahD(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = 1, zy = 0;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = (zx + zx - x);
        numery = (+zy + zy - y);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);// zh=cz
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh =cz^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= c^2 *z^3
        numerx += zhx;
        numery += zhy;



        VS_complex_div(numerx, numery, consdenomx, consdenomy, zx, zy);
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);
        zx += cx;
        zy += cy;
        //if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMagJset_buddahB(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) {
    // actual equation of weirdmag B is 
    //( ( ( (-c + 2 z - c z + c z ^ 2 - 2cz ^ 3 - ((c^2) * (z^3)) ) ) /  (2-c) ) / (z^2)  ) +j  ,  z0=c
    //where c is pixel coordinatesand j is a user input that is constant over the whole image rendered.

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2cz ^ 3 - ((c^2) * (z^3)) )
        numerx = (zx + zx - x);
        numery = (+zy + zy - y);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);// zh=cz
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh =cz^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx -= zhx;
        numery -= zhy;



        VS_complex_div(numerx, numery, consdenomx, consdenomy, zx, zy);
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);
        zx += cx;
        zy += cy;
        //if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag_buddahC(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx += 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = (zx + zx - x);
        numery = (+zy + zy - y);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);// zh=cz
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx += zhx;
        numery += zhy;



        VS_complex_div(numerx, numery, consdenomx, consdenomy, zx, zy);
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        //if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag_buddahD(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = 1, zy = 0;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = (zx + zx - x);
        numery = (+zy + zy - y);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);// zh=cz
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(zhx, zhy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx += zhx;
        numery += zhy;



        VS_complex_div(numerx, numery, consdenomx, consdenomy, zx, zy);
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        //if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag_buddahE(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = ((-x) + zx + zx);
        numery = ((-y) + zy + zy);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx += zhx;
        numery += zhy;



        VS_complex_div(numerx, numery, consdenomx, consdenomy, zx, zy);
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag_buddahF(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = ((-x) + zx + zx);
        numery = ((-y) + zy + zy);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx += zhx;
        numery += zhy;


        VS_complex_div(denomx, denomy, consdenomx, consdenomy, zx, zy);
        VS_complex_div(numerx, numery, zx, zy, zx, zy);
        //VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        //if (vabs(zx) + vabs(zy) > bail)return its;

        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return its;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMagJset_buddahF(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = ((-x) + zx + zx);
        numery = ((-y) + zy + zy);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);// zh=cz
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx += zhx;
        numery += zhy;


        VS_complex_div(denomx, denomy, consdenomx, consdenomy, zx, zy);
        VS_complex_div(numerx, numery, zx, zy, zx, zy);
        //VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        //if (vabs(zx) + vabs(zy) > bail)return its;
        zx += cx;
        zy += cy;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return its;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag_buddahG(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx += 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = ((-x) + zx + zx);
        numery = ((-y) + zy + zy);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx += zhx;
        numery += zhy;


        VS_complex_div(denomx, denomy, consdenomx, consdenomy, zx, zy);
        VS_complex_div(numerx, numery, zx, zy, zx, zy);
        //VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        //if (vabs(zx) + vabs(zy) > bail)return its;

        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return its;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}


int calc_mandle_weirdMag_buddahI(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = 2, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y; // c-2 divisor
    consdenomx -= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        // denom is now z^2
        //(-c + 2 z - c z + c z ^ 2 - 2 z ^ 3 + c z ^ 3)
        numerx = ((-x) + zx + zx);
        numery = ((-y) + zy + zy);
        VS_complex_mulLD(zx, zy, x, y, zhx, zhy);
        numerx -= zhx;
        numery -= zhy;
        // here -c + 2 z - c z
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); //zh= cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh =z^3, need 2
        numerx -= (zhx + zhx);
        numery -= (zhy + zhy);
        VS_complex_mulLD(zhx, zhy, x, y, zhx, zhy); //zh= cz^3
        numerx += zhx;
        numery += zhy;



        VS_complex_div(numerx, numery, consdenomx, consdenomy, zx, zy);
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
//        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag_buddahJ(double x, double y, int maxits, double bail, double* trackbuff) {
    //this is the correct rendition of weirdMag1
    int its = 1;
    double zx = 2, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = 2-x, consdenomy = -y; // -c/ (2-c)
    VS_complex_divLD(-x, -y, consdenomx, consdenomy, consdenomx, consdenomy);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        zhx = zx - 1;
        zhy = zy;
        numerx = zx + consdenomx;
        numery = zy + consdenomy;
        VS_complex_mulLD(numerx, numery, zhx, zhy, numerx, numery); //(z-1)*(z-(c/2-c))
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // z^2

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        //        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
//c/(2 - c) - z - (c z^2)/(2 - c) + z^3
int calc_mandle_weirdMag2_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 2 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        zhy = denomy; zhx = denomx;
        VS_complex_squareLD(zhx, zhy);//zh = z^3   --- error, this is z^4
        numerx += zhx; numery += zhy;

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return its;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
//c/(2 - c) - z - (c z^2)/(2 - c) + z^3
int calc_mandle_weirdMag2_buddahB(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 2 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;


        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);

//        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2_buddahC(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 2 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx;
        numery += zhy;
        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;


        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
                if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits-its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2_buddahD(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 2 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;


        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits-its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}

int calc_mandle_weirdMag2_buddahE(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 2 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx;numery += zhy;
        
        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;

        //denomx -= x;
        //denomy -= y;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2_buddahF(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 2 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx; numery += zhy;

        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;

        denomx -= x;
        denomy -= y;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2_buddahG(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 1 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx; numery += zhy;

        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;

        denomx -= x;
        denomy -= y;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2_buddahH(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 1 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx; numery += zhy;

        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;

        denomx -= x;
        denomy -= y;
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy);
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
        
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2_buddahI(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 1 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx; numery += zhy;

        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;

        denomx -= x;
        denomy -= y;
        VS_complex_mulLD(denomx, denomy, x, y, denomx, denomy);
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2_buddahJ(double x, double y, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 2 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx; numery += zhy;

        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;

        denomx -= x;
        denomy -= y;
        VS_complex_mulLD(denomx, denomy, x, y, denomx, denomy);
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2Jset_buddahJ(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E
    // actual equation of weirdmag B is 
    //( ( (c/(2 - c) - z - (c z^2)/(2 - c) + z^3 + cz^2  )    /  (z^2-c) *(c))^2 ) +j 

    //where c is pixel coordinatesand j is a user input that is constant over the whole image rendered.
    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy = y * -1; // 2-c divisor
    consdenomx = 2 - consdenomx;

    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx; numery += zhy;

        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;

        denomx -= x;
        denomy -= y;
        VS_complex_mulLD(denomx, denomy, x, y, denomx, denomy);
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag2Jset_buddahJ2(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // this is the same as weirdMag_E

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = x, consdenomy =cy+ (y * -1); // 2-c divisor
    consdenomx =cx+ 2 - consdenomx;


    long double consfactx = x, consfacty = y; // (c/(2-c)) factor
    VS_complex_divLD(consfactx, consfacty, consdenomx, consdenomy, consfactx, consfacty);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        numerx = consfactx - zx;
        numery = consfacty - zy;
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // denom = z^2
        VS_complex_mulLD(denomx, denomy, x, y, zhx, zhy); // zh = cz^2
        numerx += zhx; numery += zhy;

        VS_complex_divLD(zhx, zhy, consdenomx, consdenomy, zhx, zhy);// zh= (c z^2)/(2 - c)
        numerx -= zhx; numery -= zhy;
        //zhy = denomy; zhx = denomx;
        VS_complex_mulLD(denomx, denomy, zx, zy, zhx, zhy); //zh = z^3
        numerx += zhx; numery += zhy;

        denomx -= x;
        denomy -= y;
        VS_complex_divLD(denomx, denomy, cx, cy, denomx, denomy);
        VS_complex_mulLD(denomx, denomy, x, y, denomx, denomy);
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
        //zx += cx;
        //zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_iansfunction_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;

    }
    return its;
}
int calc_fractal_cos_zoverc_buddah(double x, double y, int maxits, double bail, double* trackbuff) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    double* trackbufff = trackbuff;
    long double zxcopyb = 100, zycopyb = 100;
    while (its < maxits) {
        VS_complex_div(zx, zy, x, y, zx, zy);
        VS_complex_cos(zx, zy);
    //    zx += x;
    //   zy += y;
    //    if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return its;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        zxcopyb = zx; zycopyb = zy;
        its++;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;

    }
    return its;
}
int calc_fractal_cos_zoverc(double x, double y, int maxits, double bail ) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double zxcopyb = 100, zycopyb = 100;
    while (its < maxits) {
        VS_complex_div(zx, zy, x, y, zx, zy);
        VS_complex_cos(zx, zy);
        //    zx += x;
        //   zy += y;
        //    if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return its;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        zxcopyb = zx; zycopyb = zy;
        its++;

    }
    return its;
}

int calc_mandle_weirdMag3Jset_buddah(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //(cz-c^2/2)/z^2

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = cx, consfacty = cy; // (c^2/(2)) factor
    VS_complex_squareLD(consfactx, consfacty);
    //VS_complex_divLD(consfactx, consfacty, 2.0, 0, consfactx, consfacty);
    consfactx /= 2; consfacty /= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);

        VS_complex_mul(zx, zy, cx, cy, zx, zy);
        zx -= consfactx;
        zy -= consfacty;
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag3Jset_buddahB(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //(cz-c^2/2)/z^2

    int its = 1;
    double zx = cx, zy = cy;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = x, consfacty = y; // (c^2/(2)) factor
    VS_complex_squareLD(consfactx, consfacty);
    //VS_complex_divLD(consfactx, consfacty, 2.0, 0, consfactx, consfacty);
    consfactx /= 2; consfacty /= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);

        VS_complex_mul(zx, zy, x, y, zx, zy);
        zx -= consfactx;
        zy -= consfacty;
        //zx /= 2;zy /= 2;
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMag3Jset_buddahC(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //(cz-c^2/2)/z^2

    int its = 1;
    double zx = cx, zy = cy;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = x, consfacty = y; // (c^2/(2)) factor
    VS_complex_squareLD(consfactx, consfacty);
    //VS_complex_divLD(consfactx, consfacty, 2.0, 0, consfactx, consfacty);
    consfactx /= 2; consfacty /= 2;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);

        VS_complex_mul(zx, zy, x, y, zx, zy);
        zx -= consfactx;
        zy -= consfacty;
        //zx /= 2;zy /= 2;
        VS_complex_div(zx, zy, denomx, denomy, zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddah(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = 0, consfacty = 0; 

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        consfactx = zx; consfacty = zy;
        VS_complex_mulLD(consfactx, consfacty, x, y, consfactx, consfacty); // consfact = cz
        zhx = consfactx; zhy = consfacty; // zh = cz
        VS_COMPLEX_Sqrt(consfactx, consfacty); // consfact = sqrt(cz)
        numerx = 6 * zhx; numery = 6 * zhy;  // numer = 6cz;

        VS_complex_mulLD(numerx, numery, consfactx, consfacty, numerx, numery); // numer = 6cz * sqrt(cz)
        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czz
        zhx = denomx; zhy = denomy; // zh = czz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czz * sqrt(cz)
        numerx -= 5 * denomx;
        numery -= 5 * denomy; // numer -=  5czz * sqrt(cz)

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzz
        zhx = denomx; zhy = denomy; // zh = czzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzz * sqrt(cz)
        numerx -= 2 * denomx;
        numery -= 2 * denomy; // numer -= = 2czzz * sqrt(cz);

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzzz * sqrt(cz)
        numerx += denomx;
        numery += denomy;
        zx = numerx;
        zy = numery;
        //VS_complex_square(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahB(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = 0, consfacty = 0;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        consfactx = zx; consfacty = zy;
        VS_complex_mulLD(consfactx, consfacty, x, y, consfactx, consfacty); // consfact = cz
        zhx = consfactx; zhy = consfacty; // zh = cz
        VS_COMPLEX_Sqrt(consfactx, consfacty); // consfact = sqrt(cz)
        numerx = 6 * zhx; numery = 6 * zhy;  // numer = 6cz;

        VS_complex_mulLD(numerx, numery, consfactx, consfacty, numerx, numery); // numer = 6cz * sqrt(cz)
        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czz
        zhx = denomx; zhy = denomy; // zh = czz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czz * sqrt(cz)
        numerx -= 5 * denomx;
        numery -= 5 * denomy; // numer -=  5czz * sqrt(cz)

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzz
        zhx = denomx; zhy = denomy; // zh = czzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzz * sqrt(cz)
        numerx -= 2 * denomx;
        numery -= 2 * denomy; // numer -= = 2czzz * sqrt(cz);

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzzz * sqrt(cz)
        numerx += denomx;
        numery += denomy;
        zx = numerx;
        zy = numery;
        VS_complex_square(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahC(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = 0, consfacty = 0;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        consfactx = zx; consfacty = zy;
        VS_complex_mulLD(consfactx, consfacty, x, y, consfactx, consfacty); // consfact = cz
        zhx = consfactx; zhy = consfacty; // zh = cz
        VS_COMPLEX_Sqrt(consfactx, consfacty); // consfact = sqrt(cz)
        numerx = 6 * zhx; numery = 6 * zhy;  // numer = 6cz;

        VS_complex_mulLD(numerx, numery, consfactx, consfacty, numerx, numery); // numer = 6cz * sqrt(cz)
        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czz
        zhx = denomx; zhy = denomy; // zh = czz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czz * sqrt(cz)
        numerx -= 5 * denomx;
        numery -= 5 * denomy; // numer -=  5czz * sqrt(cz)

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzz
        zhx = denomx; zhy = denomy; // zh = czzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzz * sqrt(cz)
        numerx -= 2 * denomx;
        numery -= 2 * denomy; // numer -= = 2czzz * sqrt(cz);

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzzz * sqrt(cz)
        VS_complex_E_ExponentLD(denomx, denomy, denomx, denomy);
        numerx += denomx;
        numery += denomy;
        zx = numerx;
        zy = numery;
        VS_complex_square(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahD(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = 0, consfacty = 0;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        consfactx = zx; consfacty = zy;
        VS_complex_mulLD(consfactx, consfacty, x, y, consfactx, consfacty); // consfact = cz
        zhx = consfactx; zhy = consfacty; // zh = cz
        //VS_COMPLEX_Sqrt(consfactx, consfacty); // consfact = sqrt(cz)
        VS_complex_divLD(consfactx, consfacty, cx+x, cy+y, consfactx, consfacty);
        numerx = 6 * zhx; numery = 6 * zhy;  // numer = 6cz;

        VS_complex_mulLD(numerx, numery, consfactx, consfacty, numerx, numery); // numer = 6cz * sqrt(cz)
        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czz
        zhx = denomx; zhy = denomy; // zh = czz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czz * sqrt(cz)
        numerx -= 5 * denomx;
        numery -= 5 * denomy; // numer -=  5czz * sqrt(cz)

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzz
        zhx = denomx; zhy = denomy; // zh = czzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzz * sqrt(cz)
        numerx -= 2 * denomx;
        numery -= 2 * denomy; // numer -= = 2czzz * sqrt(cz);

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzzz * sqrt(cz)
        VS_complex_E_ExponentLD(denomx, denomy, denomx, denomy);
        numerx += denomx;
        numery += denomy;
        zx = numerx;
        zy = numery;
        VS_complex_square(zx, zy);
        //zx += cx;
        //zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahE(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = 0, consfacty = 0;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        consfactx = zx; consfacty = zy;
        VS_complex_mulLD(consfactx, consfacty, x, y, consfactx, consfacty); // consfact = cz
        zhx = consfactx; zhy = consfacty; // zh = cz
        //VS_COMPLEX_Sqrt(consfactx, consfacty); // consfact = sqrt(cz)
        VS_complex_divLD(consfactx, consfacty, cx + x, cy + y, consfactx, consfacty);
        numerx = 6 * zhx; numery = 6 * zhy;  // numer = 6cz;

        VS_complex_mulLD(numerx, numery, consfactx, consfacty, numerx, numery); // numer = 6cz * sqrt(cz)
        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czz
        zhx = denomx; zhy = denomy; // zh = czz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czz * sqrt(cz)
        numerx -= 5 * denomx;
        numery -= 5 * denomy; // numer -=  5czz * sqrt(cz)

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzz
        zhx = denomx; zhy = denomy; // zh = czzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzz * sqrt(cz)
        VS_complex_E_ExponentLD(denomx, denomy, denomx, denomy);
        numerx -= 2 * denomx;
        numery -= 2 * denomy; // numer -= = 2czzz * sqrt(cz);

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzzz * sqrt(cz)
        VS_complex_E_ExponentLD(denomx, denomy, denomx, denomy);
        numerx += denomx;
        numery += denomy;
        zx = numerx;
        zy = numery;
        //VS_complex_exp(zx, zy, 3, zx, zy);
        //VS_complex_square(zx, zy);
        //zx += cx;
        //zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahF(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = 0, consfacty = 0;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        consfactx = zx; consfacty = zy;
        VS_complex_mulLD(consfactx, consfacty, x, y, consfactx, consfacty); // consfact = cz
        zhx = consfactx; zhy = consfacty; // zh = cz
        //VS_COMPLEX_Sqrt(consfactx, consfacty); // consfact = sqrt(cz)
        VS_complex_divLD(consfactx, consfacty, cx + x, cy + y, consfactx, consfacty);
        numerx = 6 * zhx; numery = 6 * zhy;  // numer = 6cz;

        VS_complex_mulLD(numerx, numery, consfactx, consfacty, numerx, numery); // numer = 6cz * sqrt(cz)
        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czz
        zhx = denomx; zhy = denomy; // zh = czz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czz * sqrt(cz)
        numerx -= 5 * denomx;
        numery -= 5 * denomy; // numer -=  5czz * sqrt(cz)

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzz
        zhx = denomx; zhy = denomy; // zh = czzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzz * sqrt(cz)
        VS_complex_E_ExponentLD(denomx, denomy, denomx, denomy);
        numerx -= 2 * denomx;
        numery -= 2 * denomy; // numer -= = 2czzz * sqrt(cz);

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzzz * sqrt(cz)
        VS_complex_E_ExponentLD(denomx, denomy, denomx, denomy);
        numerx += denomx;
        numery += denomy;
        zx = numerx;
        zy = numery;
        //VS_complex_exp(zx, zy, 3, zx, zy);
        //VS_complex_square(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        //zx += cx;
        //zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahG(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consfactx = 0, consfacty = 0;

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        consfactx = zx; consfacty = zy;
        VS_complex_mulLD(consfactx, consfacty, x, y, consfactx, consfacty); // consfact = cz
        zhx = consfactx; zhy = consfacty; // zh = cz
        //VS_COMPLEX_Sqrt(consfactx, consfacty); // consfact = sqrt(cz)
        VS_complex_divLD(consfactx, consfacty, cx + x, cy + y, consfactx, consfacty);
        numerx = 6 * zhx; numery = 6 * zhy;  // numer = 6cz;

        VS_complex_mulLD(numerx, numery, consfactx, consfacty, numerx, numery); // numer = 6cz * sqrt(cz)
        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czz
        zhx = denomx; zhy = denomy; // zh = czz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czz * sqrt(cz)
        numerx -= 5 * denomx;
        numery -= 5 * denomy; // numer -=  5czz * sqrt(cz)

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzz
        zhx = denomx; zhy = denomy; // zh = czzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzz * sqrt(cz)
        VS_complex_E_ExponentLD(denomx, denomy, denomx, denomy);
        numerx -= 2 * denomx;
        numery -= 2 * denomy; // numer -= = 2czzz * sqrt(cz);

        VS_complex_mulLD(zhx, zhy, zx, zy, denomx, denomy); // denom = czzzz
        VS_complex_mulLD(denomx, denomy, consfactx, consfacty, denomx, denomy); //denom = czzzz * sqrt(cz)
        VS_complex_E_ExponentLD(denomx, denomy, denomx, denomy);
        numerx += denomx;
        numery += denomy;
        zx = numerx;
        zy = numery;
        //VS_complex_exp(zx, zy, 3, zx, zy);
        //
        
        //zx += cx;
        //zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahH(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double zchx = 0, zchy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double consfactx = 0, consfacty = 0;
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;

    while (its < maxits) {
        numerx = zx; numery = zy;
        VS_complex_expLD(numerx, numery, 2, numerx, numery);
        VS_complex_mulLD(numerx, numery, x, y, numerx, numery);
        denomx = zx; denomy = zy;
        VS_complex_expLD(denomx, denomy, 3, denomx, denomy);
        denomx += cx; denomy += cy;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        //zx += cx; zy += cy;
        //VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahI(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double zchx = 0, zchy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double consfactx = 0, consfacty = 0;
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;

    while (its < maxits) {
        numerx = zx; numery = zy;
        VS_complex_expLD(numerx, numery, 2, numerx, numery);
        VS_complex_mulLD(numerx, numery, x, y, numerx, numery);
        numerx += 1;
        denomx = zx; denomy = zy;
        VS_complex_expLD(denomx, denomy, 3, denomx, denomy);
        denomx += cx; denomy += cy;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        //zx += cx; zy += cy;
        //VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahJ(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double zchx = 0, zchy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double consfactx = 0, consfacty = 0;
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;

    while (its < maxits) {

        numerx = zx; numery = zy;
        VS_complex_expLD(numerx, numery, 2, numerx, numery);
        VS_complex_mulLD(numerx, numery, x, y, numerx, numery);
        zhx = zx; zhy = zy;
        VS_complex_E_ExponentLD(zhx, zhy, zhx, zhy);
        numerx += zhx; numery += zhy;

        denomx = zx; denomy = zy;
        VS_complex_expLD(denomx, denomy, 3, denomx, denomy);
        denomx -= cx; denomy -= cy;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        //zx += cx; zy += cy;
        //VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahk(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double zchx = 0, zchy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double consfactx = 0, consfacty = 0;
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;

    while (its < maxits) {

        numerx = zx; numery = zy;
        VS_complex_expLD(numerx, numery, 2, numerx, numery);
        //VS_complex_mulLD(numerx, numery, x, y, numerx, numery);
        zhx = zx+cx; zhy = zy+cy;
        //VS_complex_E_ExponentLD(zhx, zhy, zhx, zhy);
        VS_complex_squareLD(zhx, zhy);
        VS_complex_divLD(zhx, zhy, x, y, zhx, zhy);
        numerx += zhx; numery += zhy;

        denomx = zx; denomy = zy;
        VS_complex_expLD(denomx, denomy, 3, denomx, denomy);
        denomx -= cx; denomy -= cy;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        //zx += cx; zy += cy;
        //VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahL(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double zchx = 0, zchy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double consfactx = 0, consfacty = 0;
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;

    while (its < maxits) {

        numerx = zx; numery = zy;
        VS_complex_expLD(numerx, numery, 2, numerx, numery);
        //VS_complex_mulLD(numerx, numery, x, y, numerx, numery);
        zhx = zx + cx; zhy = zy + cy;
        //VS_complex_E_ExponentLD(zhx, zhy, zhx, zhy);
        VS_complex_squareLD(zhx, zhy);
        VS_complex_divLD(zhx, zhy, x, y, zhx, zhy);
        numerx += zhx; numery += zhy;

        denomx = zx; denomy = zy;
        VS_complex_expLD(denomx, denomy, 3, denomx, denomy);
        denomx -= cx; denomy -= cy;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        //zx += cx; zy += cy;
        //VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
 //       if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
//        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahM(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double zchx = 0, zchy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double consfactx = 0, consfacty = 0;
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;

    while (its < maxits) {

        numerx = zx; numery = zy;
        VS_complex_expLD(numerx, numery, 2, numerx, numery);
        //VS_complex_mulLD(numerx, numery, x, y, numerx, numery);
        zhx = zx + cx; zhy = zy + cy;
        //VS_complex_E_ExponentLD(zhx, zhy, zhx, zhy);
        VS_complex_squareLD(zhx, zhy);
        VS_complex_divLD(zhx, zhy, x, y, zhx, zhy);
        numerx += zhx; numery += zhy;

        denomx = zx; denomy = zy;
     //   VS_complex_expLD(denomx, denomy, 3, denomx, denomy);
        denomx -= cx; denomy -= cy;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        //zx += cx; zy += cy;
        //VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        //       if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
               //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
               if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_Valsfunc_buddahN(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) { // new mag from same site after they changed the formula
    //c z^4 sqrt(c z) - 2 c z^3 sqrt(c z) - 5 c z^2 sqrt(c z) + 6 c z sqrt(c z)

    int its = 1;
    double zx = x, zy = y;
    long double zhx = 0, zhy = 0;
    long double zchx = 0, zchy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double consfactx = 0, consfacty = 0;
    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    // (([z^3] + [z+j]^2) / ((z^2)/c)-j )^2 
    while (its < maxits) {

        numerx = zx; numery = zy;
        VS_complex_expLD(numerx, numery, 3, numerx, numery);
        //VS_complex_mulLD(numerx, numery, x, y, numerx, numery);
        zhx = zx + cx; zhy = zy + cy;
        //VS_complex_E_ExponentLD(zhx, zhy, zhx, zhy);
        VS_complex_squareLD(zhx, zhy);
        //VS_complex_divLD(zhx, zhy, x, y, zhx, zhy);
        numerx += zhx; numery += zhy;

        denomx = zx; denomy = zy;
           VS_complex_expLD(denomx, denomy, 2, denomx, denomy);
           VS_complex_divLD(denomx, denomy, x, y, denomx, denomy);
        denomx -= cx; denomy -= cy;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        //zx += cx; zy += cy;
        //VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        if (vabs(zx) + vabs(zy) > bail)return its;
        //       if (VS_complex_rangecomp(zx, zy, 0, 0, .000000001))return maxits - its;// -(its % (maxits / 100));
               //if (VS_complex_rangecomp(zx, zy, 1, 0, .000000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_weirdMagJ_jset_buddah(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff) {
    //this is the correct rendition of weirdMag1
    int its = 1;
    double zx = 2, zy = y;
    long double zhx = 0, zhy = 0;
    long double numerx, numery;
    long double denomx, denomy;

    long double consdenomx = 2 - x, consdenomy = -y; // -c/ (2-c)
    VS_complex_divLD(-x, -y, consdenomx, consdenomy, consdenomx, consdenomy);

    long double zxcopyb = 100, zycopyb = 100;
    double* trackbufff = trackbuff;
    while (its < maxits) {
        zhx = zx - 1;
        zhy = zy;
        numerx = zx + consdenomx;
        numery = zy + consdenomy;
        VS_complex_mulLD(numerx, numery, zhx, zhy, numerx, numery); //(z-1)*(z-(c/2-c))
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // z^2

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        //        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        *trackbufff = zx; trackbufff++;
        *trackbufff = zy; trackbufff++;
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
#define ValFractal_iterator(fnname) int fnname (double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff)
#define ValFractal_iterator_preamble(x,y) int its = 1; double zx = x, zy = y; long double zhx = 0, zhy = 0, numerx, numery, denomx, denomy,zxcopyb = 100, zycopyb = 100; double* trackbufff = trackbuff;
#define ValFractal_iterator_loopend()if (vabs(zx) + vabs(zy) > bail)return its; \
if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its; \
*trackbufff = zx; trackbufff++; *trackbufff = zy; trackbufff++; zxcopyb = zx; zycopyb = zy; its++; 

#define ValFractal_iterator_loopendINFT()if (vabs(zx) + vabs(zy) > bail)return its; \
*trackbufff = zx; trackbufff++; *trackbufff = zy; trackbufff++; zxcopyb = zx; zycopyb = zy; its++; 

#define ValFractal_iterator_loopendROOT()if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its; \
*trackbufff = zx; trackbufff++; *trackbufff = zy; trackbufff++; zxcopyb = zx; zycopyb = zy; its++; 

ValFractal_iterator(VF_test_iterator) {//(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff)
        //this is the correct rendition of weirdMag1
    ValFractal_iterator_preamble(2, y);
    long double consdenomx = 2 - x, consdenomy = -y; // -c/ (2-c)
    VS_complex_divLD(-x, -y, consdenomx, consdenomy, consdenomx, consdenomy);

    while (its < maxits) {
        zhx = zx - 1;
        zhy = zy;
        numerx = zx + consdenomx;
        numery = zy + consdenomy;
        VS_complex_mulLD(numerx, numery, zhx, zhy, numerx, numery); //(z-1)*(z-(c/2-c))
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy); // z^2

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        zx += cx;
        zy += cy;
        ValFractal_iterator_loopendROOT();
    }
    return its;
}


/******************************************start arbitrary fractal threading system***********************************/

struct Mandel_workerthread_info {
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
    int totalstepsx;
    int totalstepsy;
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
    int global_threadlock = 64;
};

Mandel_workerthread_info G_mandel_workerthread_info;
string G_Mandel_threadstat = "";
bool G_Mandel_Buddahbrot_renderpause = false;
unsigned long long int G_Mandel_Buddahbrot_samplecount = 0, G_Mandel_Buddahbrot_HitcountTotal = 0;
/********heart and soul of the threaded renderer.***********/
int mandel_worker_thread_process(double xh, double yh, double cx, double cy, int maxits, double bailout, void* Mcallback, int type) {
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
        ret = ((int(__cdecl*)(double, double, double, double, int, double))(Mcallback)) (xh, yh, cx, cy, maxits, bailout);
        break;
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
}
double vs_rand_double() {
    double a = G_VS_Rand3(1000000000), b = G_VS_Rand3(1000000000);
    if (a < b) return a / b;
    return b / a;
}

//this is technically the zrzi plane
int mandel_buddah_thread_process_step(double x, double y, int maxits, double bail, double* trackbuff, int* myhit_data, double xmin, double xmax, double ymin, double ymax, double xstep, double ystep, int numerator, int denominator, void* function) {
    double n = x, i = y;
    int ctch = ((int(__cdecl*)(double, double, int, double, double*))(function)) (x, y, maxits, bail, trackbuff);
    //int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch > (maxits * numerator) / denominator && ctch < maxits) {// check if escapes-
        ctch -= 2;
        double* tb_h = trackbuff;
        foreach(xxx, ctch) {
            n = *tb_h;
            i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

            if (n <= xmin + xstep || n >= xmax - xstep || i <= ymin + ystep || i >= ymax - ystep) continue;
            int xx = ((n - xmin) / xstep);
            int yy = ((i - ymin) / ystep);
            myhit_data[xx + (yy * 2000)]++;//myhit_data[xx][yy]++;
            hits++;
        }
    }
    if (hits == 0)return 0;
    return 1;

}

int mandel_buddah_thread_process_step_crciPlane(double x, double y, int maxits, double bail, double* trackbuff, int* myhit_data, double xmin, double xmax, double ymin, double ymax, double xstep, double ystep, int numerator, int denominator, void* function) {
    double n = x, i = y;
    int ctch = ((int(__cdecl*)(double, double, int, double, double*))(function)) (x, y, maxits, bail, trackbuff);
    int cModifier = floor(((y - ymin) / ystep) * 2000);
    cModifier += (x - xmin) / xstep;
    //int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch > (maxits * numerator) / denominator && ctch < maxits) {// check if escapes-
        //ctch -= 2;
        //double* tb_h = trackbuff;
        //foreach(xxx, ctch) {
        //    n = *tb_h;
        //    i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

        //    if (n <= xmin + xstep || n >= xmax - xstep /*|| i <= ymin + ystep || i >= ymax - ystep*/) continue;
        //    int xx = ((n - xmin) / xstep);
        //    //int yy = ((i - ymin) / ystep);
        //    myhit_data[xx + (cModifier)]++;//myhit_data[xx][yy]++;
        //    hits++;
        //}
        myhit_data[(cModifier)]+= ctch;//myhit_data[xx][yy]++;
        hits += ctch;
    }
    if (hits == 0)return 0;
    return 1;

}
int mandel_buddah_thread_process_step_crciPlane_jset(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff, int* myhit_data, double xmin, double xmax, double ymin, double ymax, double xstep, double ystep, int numerator, int denominator, void* function) {
    double n = x, i = y;
    int ctch = ((int(__cdecl*)(double, double, double, double, int, double, double*))(function)) (x, y,cx,cy, maxits, bail, trackbuff);
    int cModifier = floor(((y - ymin) / ystep) * 2000);
    cModifier += (x - xmin) / xstep;
    //int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch < maxits) {// check if escapes-
        //ctch -= 2;
        //double* tb_h = trackbuff;
        //foreach(xxx, ctch) {
        //    n = *tb_h;
        //    i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

        //    if (n <= xmin + xstep || n >= xmax - xstep /*|| i <= ymin + ystep || i >= ymax - ystep*/) continue;
        //    int xx = ((n - xmin) / xstep);
        //    //int yy = ((i - ymin) / ystep);
        //    myhit_data[xx + (cModifier)]++;//myhit_data[xx][yy]++;
        //    hits++;
        //}
        myhit_data[(cModifier)] += ctch;//myhit_data[xx][yy]++;
        hits += ctch;
    }
    if (hits == 0)return 0;
    return 1;

}
int mandel_buddah_thread_process_step_zrciPlane_jset(double x, double y, double cx, double cy, int maxits, double bail, double* trackbuff, int* myhit_data, double xmin, double xmax, double ymin, double ymax, double xstep, double ystep, int numerator, int denominator, void* function) {
    double n = x, i = y;
    int ctch = ((int(__cdecl*)(double, double, double, double, int, double, double*))(function)) (x, y, cx, cy, maxits, bail, trackbuff);
    int cModifier = floor(((y - ymin) / ystep) * 2000);
    //int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch > (maxits * numerator) / denominator && ctch < maxits) {// check if escapes-
        ctch -= 2;
        double* tb_h = trackbuff;
        foreach(xxx, ctch) {
            n = *tb_h;
            i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

            if (n <= xmin + xstep || n >= xmax - xstep /*|| i <= ymin + ystep || i >= ymax - ystep*/) continue;
            int xx = ((n - xmin) / xstep);
            //int yy = ((i - ymin) / ystep);
            myhit_data[xx + (cModifier)]++;//myhit_data[xx][yy]++;
            hits++;
        }
    }
    if (hits == 0)return 0;
    return 1;

}
int mandel_buddah_thread_process_step_zrciPlane(double x, double y, int maxits, double bail, double* trackbuff, int* myhit_data, double xmin, double xmax, double ymin, double ymax, double xstep, double ystep, int numerator, int denominator, void* function) {
    double n = x, i = y;
    int ctch = ((int(__cdecl*)(double, double, int, double, double*))(function)) (x, y, maxits, bail, trackbuff);
    int cModifier = floor(((y - ymin) / ystep) * 2000);
    //int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch > (maxits * numerator) / denominator && ctch < maxits) {// check if escapes-
        ctch -= 2;
        double* tb_h = trackbuff;
        foreach(xxx, ctch) {
            n = *tb_h;
            i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

            if (n <= xmin + xstep || n >= xmax - xstep /*|| i <= ymin + ystep || i >= ymax - ystep*/) continue;
            int xx = ((n - xmin) / xstep);
            //int yy = ((i - ymin) / ystep);
            myhit_data[xx + (cModifier)]++;//myhit_data[xx][yy]++;
            hits++;
        }
    }
    if (hits == 0)return 0;
    return 1;

}

int mandel_buddah_thread_process_step_zrcrPlane(double x, double y, int maxits, double bail, double* trackbuff, int* myhit_data, double xmin, double xmax, double ymin, double ymax, double xstep, double ystep, int numerator, int denominator, void* function) {
    double n = x, i = y;
    int ctch = ((int(__cdecl*)(double, double, int, double, double*))(function)) (x, y, maxits, bail, trackbuff);
    int cModifier = floor(((x - xmin) / xstep) * 2000);
    //int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch > (maxits * numerator) / denominator && ctch < maxits) {// check if escapes-
        ctch -= 2;
        double* tb_h = trackbuff;
        foreach(xxx, ctch) {
            n = *tb_h;
            i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

            if (n <= xmin + xstep || n >= xmax - xstep /*|| i <= ymin + ystep || i >= ymax - ystep*/) continue;
            int xx = ((n - xmin) / xstep);
            //int yy = ((i - ymin) / ystep);
            myhit_data[xx + (cModifier)]++;//myhit_data[xx][yy]++;
            hits++;
        }
    }
    if (hits == 0)return 0;
    return 1;

}
int mandel_buddah_thread_process_step_crziPlane(double x, double y, int maxits, double bail, double* trackbuff, int* myhit_data, double xmin, double xmax, double ymin, double ymax, double xstep, double ystep, int numerator, int denominator, void* function) {
    double n = x, i = y;
    int ctch = ((int(__cdecl*)(double, double, int, double, double*))(function)) (x, y, maxits, bail, trackbuff);
    int cModifier = floor(((x - xmin) / xstep) * 2000);
    //int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch > (maxits * numerator) / denominator && ctch < maxits) {// check if escapes-
        ctch -= 2;
        double* tb_h = trackbuff;
        foreach(xxx, ctch) {
            n = *tb_h;
            i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

            if (i <= ymin + ystep || i >= ymax - ystep) continue;

            int yy = ((i - ymin) / ystep);
            myhit_data[yy + (cModifier)]++;//myhit_data[xx][yy]++;
            hits++;
        }
    }
    if (hits == 0)return 0;
    return 1;

}
int mandel_buddah_thread_process_step_ciziPlane(double x, double y, int maxits, double bail, double* trackbuff, int* myhit_data, double xmin, double xmax, double ymin, double ymax, double xstep, double ystep, int numerator, int denominator, void* function) {
    double n = x, i = y;
    int ctch = ((int(__cdecl*)(double, double, int, double, double*))(function)) (x, y, maxits, bail, trackbuff);
    int cModifier = floor(((y - ymin) / ystep) * 2000);
    //int ctch = calc_mandle_buddah(n, i, maxits, bail, trackbuff);
    int hits = 0;
    if (ctch > (maxits * numerator) / denominator && ctch < maxits) {// check if escapes-
        ctch -= 2;
        double* tb_h = trackbuff;
        foreach(xxx, ctch) {
            n = *tb_h;
            i = *(tb_h + 1); tb_h = (trackbuff + (xxx * 2));

            if (i <= ymin + ystep || i >= ymax - ystep) continue;

            int yy = ((i - ymin) / ystep);
            myhit_data[yy + (cModifier)]++;//myhit_data[xx][yy]++;
            hits++;
        }
    }
    if (hits == 0)return 0;
    return 1;

}
#define G_Mandel_BuddahPlane_CrCi 0
#define G_Mandel_BuddahPlane_ZrCi 1
static unsigned short G_Mandel_BuddahPlane = 0;
static bool G_Mandel_threading_halt = false;
static double G_Mandel_Buddahbrot_searchdims[5] = { 0,0,0,0,0 };
void mandel_buddah_thread_process(int* itsbuf, mutex& workmut, double xmin, double ymin, double xmax, double ymax, int maxits, double bail, int samples, void* function, int& progress, int numer, int denom) {
    workmut.lock();
    auto myhit_data = new int[2002 * 2002];

    bool isdone = false;
    foreach(i, 2000) { foreach(n, 2000) { myhit_data[i + (n * 2000)] = 0; } }
    workmut.unlock();
    double* trackbuff = new double[maxits * 5];

    double* tb_h = trackbuff;
    double n, i;
    double xwid = xmax - xmin, ywid = ymax - ymin;
    double xstep = xwid / 2000, ystep = ywid / 2000;
    int xx, yy;
    int ctch = 0;
    double xwidsearch = xwid, ywidsearch = ywid;
    double xminsearch = xmin, yminsearch = ymin;
    auto funcpoint = mandel_buddah_thread_process_step;
    if (G_Mandel_BuddahPlane == G_Mandel_BuddahPlane_ZrCi)funcpoint = mandel_buddah_thread_process_step_zrciPlane;

    if (G_Mandel_Buddahbrot_searchdims[0] > 0) {
        xminsearch = G_Mandel_Buddahbrot_searchdims[1];
        yminsearch = G_Mandel_Buddahbrot_searchdims[2];
        xwidsearch = G_Mandel_Buddahbrot_searchdims[3];
        ywidsearch = G_Mandel_Buddahbrot_searchdims[4];
    }
    while (samples > 0) {
        //generate 2 random doubles. n,i
        workmut.lock();
        //n = (vs_rand_double()*xwid)+xmin;
        //i = (vs_rand_double()*ywid)+ymin;
        n = (vs_rand_double() * xwidsearch) + xminsearch;
        i = (vs_rand_double() * ywidsearch) + yminsearch;
        workmut.unlock();

        if (G_Mandel_threading_halt)break;

        ctch += funcpoint(n, i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += funcpoint(-n, i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += funcpoint(n, -i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += funcpoint(-n, -i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += funcpoint(i, n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += funcpoint(-i, n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += funcpoint(i, -n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += funcpoint(-i, -n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);

        /*ctch+=mandel_buddah_thread_process_step(n, i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep,numer,denom,function);
        ctch += mandel_buddah_thread_process_step(-n, i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += mandel_buddah_thread_process_step(n, -i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += mandel_buddah_thread_process_step(-n, -i, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += mandel_buddah_thread_process_step(i, n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += mandel_buddah_thread_process_step(-i, n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += mandel_buddah_thread_process_step(i, -n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
        ctch += mandel_buddah_thread_process_step(-i, -n, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);*/


        progress++;
        samples--;
    }


    // int h, w, h, mi = myhit_data[0], ma = myhit_data[0];
    int* itsh = itsbuf;
    workmut.lock();
    foreach(i, 2000) { foreach(n, 2000) { *itsh += myhit_data[n + (i * 2000)]; itsh++; } }//myhit_data[n][i];
    G_Mandel_Buddahbrot_samplecount += ctch;
    workmut.unlock();

    delete[] trackbuff;
    delete[] myhit_data;
}

void mandel_buddahplane_thread_process(int* itsbuf, mutex& workmut, double xmin, double ymin, double xmax, double ymax, int maxits, double bail, int samples, void* function, int& progress, int numer, int denom, int myplace, int maxthreads, int tstepsy, int tstepsx, double basex, double yy, double stepx, double stepy, int type) {
    workmut.lock();
    auto myhit_data = new int[2000 * 2001];

    bool isdone = false;
    foreach(i, 2000) { foreach(n, 2000) { myhit_data[i + (n * 2000)] = 0; } }
    workmut.unlock();
    double* trackbuff = new double[maxits * 5];
    double xx;
    double* tb_h = trackbuff;
    double xwid = xmax - xmin, ywid = ymax - ymin;
    double xstep = xwid / 2000, ystep = ywid / 2000;
    auto funcpoint = mandel_buddah_thread_process_step_zrciPlane;
//    bool isjset = false;
    if (type == 406) funcpoint = mandel_buddah_thread_process_step_zrcrPlane;
    if (type == 407) funcpoint = mandel_buddah_thread_process_step_crziPlane;
    if (type == 408) funcpoint = mandel_buddah_thread_process_step_ciziPlane;
    if (type == 409) funcpoint = mandel_buddah_thread_process_step_crciPlane;

    int ctch = 0;
    for (int y = myplace; y < tstepsy - 1; y += maxthreads) {
        xx = basex;
        for (int x = 0; x < tstepsx; x++) {
            if (G_Mandel_threading_halt) { y = tstepsy; break; }
            ctch += funcpoint(xx, yy, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
            //(*itsbuf) = mandel_worker_thread_process(xx, yy, cx, cy, maxits, bailout, function, type);

            xx += stepx;
            progress++;
            //x_stepcount++;
            //G_mandel_workerthread_info.progress[myplace]++;
        }
        //y_stepcount++;
        yy += stepy;

    }
    int* itsh = itsbuf;
    workmut.lock();
    foreach(i, 2000) { foreach(n, 2000) { *itsh += myhit_data[n + (i * 2000)]; itsh++; } }//myhit_data[n][i];
    G_Mandel_Buddahbrot_samplecount += ctch;
    workmut.unlock();
    delete[] trackbuff;
    delete[] myhit_data;
}
void mandel_buddahplane_thread_process_jset(int* itsbuf, mutex& workmut, double xmin, double ymin, double xmax, double ymax, int maxits, double bail, int samples, void* function, int& progress, int numer, int denom, int myplace, int maxthreads, int tstepsy, int tstepsx, double basex, double yy, double stepx, double stepy, int type, double cx, double cy) {
    workmut.lock();
    auto myhit_data = new int[2000 * 2001];

    bool isdone = false;
    foreach(i, 2000) { foreach(n, 2000) { myhit_data[i + (n * 2000)] = 0; } }
    workmut.unlock();
    double* trackbuff = new double[maxits * 5];
    double xx;
    double* tb_h = trackbuff;
    double xwid = xmax - xmin, ywid = ymax - ymin;
    double xstep = xwid / 2000, ystep = ywid / 2000;
    auto funcpoint = mandel_buddah_thread_process_step_zrciPlane_jset;
    bool isjset = false;
 /*   if (type == 416) funcpoint = mandel_buddah_thread_process_step_zrcrPlane;
    if (type == 417) funcpoint = mandel_buddah_thread_process_step_crziPlane;
    if (type == 418) funcpoint = mandel_buddah_thread_process_step_ciziPlane;*/
    if (type == 419) funcpoint = mandel_buddah_thread_process_step_crciPlane_jset;

    int ctch = 0;
    for (int y = myplace; y < tstepsy - 1; y += maxthreads) {
        xx = basex;
        for (int x = 0; x < tstepsx; x++) {
            if (G_Mandel_threading_halt) { y = tstepsy; break; }
            ctch += funcpoint(xx, yy,cx,cy, maxits, bail, trackbuff, myhit_data, xmin, xmax, ymin, ymax, xstep, ystep, numer, denom, function);
            //(*itsbuf) = mandel_worker_thread_process(xx, yy, cx, cy, maxits, bailout, function, type);

            xx += stepx;
            progress++;
            //x_stepcount++;
            //G_mandel_workerthread_info.progress[myplace]++;
        }
        //y_stepcount++;
        yy += stepy;

    }
    int* itsh = itsbuf;
    workmut.lock();
    foreach(i, 2000) { foreach(n, 2000) { *itsh += myhit_data[n + (i * 2000)]; itsh++; } }//myhit_data[n][i];
    G_Mandel_Buddahbrot_samplecount += ctch;
    workmut.unlock();
    delete[] trackbuff;
    delete[] myhit_data;
}



static int G_Mandel_buddahbrot_samples = 500;
void Mandel_workerthread(void* a) {

    int myplace = 0;
    int maxthreads = 0;
    double cx, cy;
    int maxits;
    double bailout;
    double basex;
    double basey;
    double stepx;
    double stepy;
    BYTE* buffer;
    int tstepsx;
    int tstepsy;
    void* function;
    int* itsbuf, * itsbufbase;
    int itsbuf_jump;
    int type;
    //int its;
    double rebuild;
    int color;
    double xx, yy;
    int y_stepcount = 0, x_stepcount = 0;;

    // mandelbuddah vars:
    // int* buddahbuffer;
    // int* bbufferhold;


    G_mandel_workerthread_info.job_mut.lock();
    G_mandel_workerthread_info.threadsinpool++;
    G_mandel_workerthread_info.threadsidle++;
    G_mandel_workerthread_info.job_mut.unlock();
    while (1) {
        while (G_mandel_workerthread_info.maxthreads == 0 || G_mandel_workerthread_info.place >= G_mandel_workerthread_info.maxthreads)Sleep(8);
        G_mandel_workerthread_info.job_mut.lock();
        //cout << "thread awoke\n";
        if (G_mandel_workerthread_info.maxthreads == 0)continue;
        if (G_mandel_workerthread_info.place >= G_mandel_workerthread_info.maxthreads) {
            //G_mandel_workerthread_info.maxthreads = 0;.
            G_mandel_workerthread_info.job_mut.unlock();
            continue;
        }
        maxthreads = G_mandel_workerthread_info.maxthreads;
        myplace = G_mandel_workerthread_info.place;

        G_mandel_workerthread_info.place++;
        G_mandel_workerthread_info.threadsidle--;
        stepx = G_mandel_workerthread_info.stepx;
        stepy = G_mandel_workerthread_info.stepy;

        buffer = (BYTE*)G_mandel_workerthread_info.buffer;
        basex = G_mandel_workerthread_info.basex;
        basey = G_mandel_workerthread_info.basey;
        tstepsx = G_mandel_workerthread_info.totalstepsx;
        tstepsy = G_mandel_workerthread_info.totalstepsy;
        buffer += (tstepsx * myplace * 4);
        function = G_mandel_workerthread_info.function;
        type = G_mandel_workerthread_info.type;
        itsbuf = G_mandel_workerthread_info.itsbuf;
        itsbufbase = itsbuf;
        itsbuf += tstepsx * myplace; //*4?
        itsbuf_jump = maxthreads * tstepsx;
        cx = G_mandel_workerthread_info.cx;
        cy = G_mandel_workerthread_info.cy;
        maxits = G_mandel_workerthread_info.maxits;
        bailout = G_mandel_workerthread_info.bailout;
        rebuild = G_mandel_workerthread_info.rebuild;
        y_stepcount = 0;
        x_stepcount = 0;
        yy = basey + (stepy * myplace);
        stepy *= (maxthreads);
        G_mandel_workerthread_info.job_mut.unlock();
        double xwid = basex + (tstepsx * stepx), ywid = basey + (tstepsy * (stepy / maxthreads));

        //cout << "thread " << myplace << " started with type=" << type << "tstepsy: " << tstepsy << "\n";
        switch (type) {
        case 400:
        case 401:
            //Note: must clear iterationsBuffer before iterating here. 
            //this is for mandelbudah rendering
            mandel_buddah_thread_process(itsbufbase, G_mandel_workerthread_info.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, G_mandel_workerthread_info.progress[myplace], 9, 10);
            break;
        case 402:
        case 403:
            //Note: must clear iterationsBuffer before iterating here. 
            //this is for mandelbudah rendering
            mandel_buddah_thread_process(itsbufbase, G_mandel_workerthread_info.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, G_mandel_workerthread_info.progress[myplace], cx, cy);
            break;
        case 405: // these are for the extra plane renderers, crzi etc.
        case 406:
        case 407:
        case 408:
        case 409:

            mandel_buddahplane_thread_process(itsbufbase, G_mandel_workerthread_info.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, G_mandel_workerthread_info.progress[myplace], cx, cy
                , myplace, maxthreads, tstepsy, tstepsx, basex, yy, stepx, stepy, type);
            break;
        case 419:

            mandel_buddahplane_thread_process_jset(itsbufbase, G_mandel_workerthread_info.job_mut, basex, basey, xwid, ywid, maxits, bailout, G_Mandel_buddahbrot_samples, function, G_mandel_workerthread_info.progress[myplace], cx, cy
                , myplace, maxthreads, tstepsy, tstepsx, basex, yy, stepx, stepy, type,cx,cy);
            break;

        default:
            for (int y = myplace; y < tstepsy - 1; y += maxthreads) {
                xx = basex;
                for (int x = 0; x < tstepsx; x++) {
                    if (G_Mandel_threading_halt) { y = tstepsy; break; }
                    if (!rebuild || (rebuild && rebuild == (*itsbuf))) {
                        (*itsbuf) = mandel_worker_thread_process(xx, yy, cx, cy, maxits, bailout, function, type);
                        color = Linear_color((*itsbuf), maxits);
                        *buffer = GetBValue((COLORREF)color); buffer++;
                        *buffer = GetGValue((COLORREF)color); buffer++;
                        *buffer = GetRValue((COLORREF)color); buffer += 2;
                    }
                    else buffer += 4;
                    itsbuf++;
                    xx += stepx;
                    x_stepcount++;
                    G_mandel_workerthread_info.progress[myplace]++;
                }
                buffer += (tstepsx * (maxthreads - 1) * 4);
                itsbuf += (tstepsx * (maxthreads - 1));
                y_stepcount++;
                yy += stepy;

            }
            break;
        }
        G_mandel_workerthread_info.job_mut.lock();
        G_mandel_workerthread_info.finished++;
        G_mandel_workerthread_info.threadsidle++;
        //cout << "thread " << myplace << " ended stepcounts x,y: " << x_stepcount<<","<<y_stepcount<<"\n";
        G_mandel_workerthread_info.job_mut.unlock();
    }

}

string ctostr(unsigned long long i) {
    char a[38];
    _ui64toa(i, a, 10);
    //_itoa_s(i, a, 10);
    return a;

}

void Dispatch_workerthread_job(double x, double y, double w, double h, double cx, double cy,
    int maxits, void* Mcallback, int inpBuf[][Mandelbrot_window_dims],
    int rebuild, double bailout, int type, char* buffer, int cwid, int chit, int maxthreads, void* progCallback) {
    unsigned long long militime = chrono_milli();
    unsigned long long time = 0;
    if (G_mandel_workerthread_info.running) {
        if (G_mandel_workerthread_info.finished != G_mandel_workerthread_info.maxthreads) {
            cout << "last threaded render is not complete. please wait\n";
            return;
        }

    }
    if (type > 299 && type < 400) {
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

    if (G_mandel_workerthread_info.global_threadlock < maxthreads) maxthreads = G_mandel_workerthread_info.global_threadlock;
    long int maxprogress = cwid * chit;
    if (type >= 400 && type < 500) {
        maxprogress = G_Mandel_buddahbrot_samples * maxthreads;
        if (type > 404 && type < 429)maxprogress = 4000000;
        if (!rebuild) {
            cout << "resetting input iteration buffer to 0s\n";
            G_Mandel_Buddahbrot_samplecount = 0;
            foreach(xxx, Mandelbrot_window_dims) {
                foreach(yyy, Mandelbrot_window_dims) {
                    inpBuf[xxx][yyy] = 0;
                }
            }
        }

    }
    cout << "dispatching\n";
    //    cout << "dispatching threads now\n";
    G_Mandel_threadstat = "dispatching";
    G_mandel_workerthread_info.rebuild = rebuild;
    G_mandel_workerthread_info.running = true;
    G_mandel_workerthread_info.place = 0;
    G_mandel_workerthread_info.cx = cx;
    G_mandel_workerthread_info.cy = cy;
    G_mandel_workerthread_info.maxits = maxits;
    G_mandel_workerthread_info.bailout = bailout;
    G_mandel_workerthread_info.basex = x;
    G_mandel_workerthread_info.basey = y;
    G_mandel_workerthread_info.stepx = w / cwid;
    G_mandel_workerthread_info.stepy = h / chit;
    G_mandel_workerthread_info.totalstepsx = cwid;
    G_mandel_workerthread_info.totalstepsy = chit;
    G_mandel_workerthread_info.buffer = buffer;
    G_mandel_workerthread_info.function = Mcallback;
    G_mandel_workerthread_info.itsbuf = (int*)inpBuf;
    G_mandel_workerthread_info.type = type;
    G_mandel_workerthread_info.finished = 0;
    //G_Mandel_Stopwatch.Restart();
    //G_Mandel_Stopwatch.Start();
    foreach(bbb, 20)G_mandel_workerthread_info.progress[bbb] = 0;
    time = chrono_micro();

    G_mandel_workerthread_info.maxthreads = maxthreads; // this line causes the threads in the worker pool to awaken. Do all setup before this line
    //cout << "threads messaged\n";
//    Sleep(5);
    //cout << "threads rendering: " <<(G_mandel_workerthread_info.threadsinpool - G_mandel_workerthread_info.threadsidle) << "\n";
    unsigned long long int totalprogress = 0;
    unsigned long long int progr;
    cout << "dispatched\n";
    while (G_mandel_workerthread_info.finished != G_mandel_workerthread_info.maxthreads) {

        totalprogress = 0;
        foreach(bbb, 20) totalprogress += G_mandel_workerthread_info.progress[bbb];
        progr = (totalprogress * 100) / maxprogress;
        if (progr < 0)progr = 0;
        G_Mandel_threadstat = ctostr(G_mandel_workerthread_info.threadsinpool - G_mandel_workerthread_info.threadsidle) + " rendering | " + ctostr(totalprogress) + ":" + ctostr(maxprogress);

        ((void(__cdecl*)(int))(progCallback))(progr);

        Sleep(4);
    }
    if (!G_Mandel_threading_halt) {
        ((void(__cdecl*)(int))(progCallback))(100);
    }

    if (type >= 400 && type < 500) {
        cout << "into buddahbrot image renderer\n";
        int maxv = 0, minv = 10000000;
        int* itsbufh = (int*)inpBuf;
        unsigned long long int total = 0;
        foreach(i, 2000) {
            foreach(n, 2000) {
                if (*itsbufh > maxv)maxv = *itsbufh;
                if (*itsbufh < minv)minv = *itsbufh;
                total += *itsbufh;
                itsbufh++;
            }
        }
        G_Mandel_Buddahbrot_HitcountTotal = total;
        cout << maxv << ":max " << minv << ":min    " << total << ":total  " << G_Mandel_Buddahbrot_samplecount << " samples rendered \n";
        maxv -= minv;
        int tot = 765;
        int temp, tt;
        double dtemp;
        itsbufh = (int*)inpBuf;
        char r, g, b;
        char* bufh = buffer;
        if (maxv > maxits || type== 419)maxv = maxits;
        if (type == 419)minv = 0;
        if (type != 401 && type != 403) {
            foreach(i, 2000) {
                foreach(n, 2000) {
                    temp = (*itsbufh) - minv;
                    temp = Linear_color(temp, maxv);// maxv
                    *bufh = GetBValue(temp); bufh++;
                    *bufh = GetGValue(temp); bufh++;
                    *bufh = GetRValue(temp); bufh++; bufh++;
                    itsbufh++;
                }
            }
        }
        else {
            foreach(i, 2000) {
                foreach(n, 2000) {
                    temp = (*itsbufh) - minv;
                    itsbufh++;
                    if ((*itsbufh) != 0) {

                        dtemp = (double)maxv / (double)(temp);
                        dtemp = tot * dtemp;
                        temp = dtemp;
                        tt = temp / 3;
                        temp = temp % 3;
                    }
                    else {
                        tt = 0; temp = 0;
                    }
                    r = tt + (temp > 0 ? 1 : 0);
                    g = tt + (temp > 1 ? 1 : 0);
                    b = tt;
                    *bufh = b; bufh++;
                    *bufh = g; bufh++;
                    *bufh = r; bufh++; bufh++;
                }
            }
        }
    }

    unsigned long long ms;
    //G_Mandel_Stopwatch.End(lp, ms);
    //ms=G_Mandel_Stopwatch.Stop();
    militime = chrono_milli() - militime;
    string rt = "render time: " + ctostr(militime / 1000) + "." + ctostr(militime % 1000) + "seconds";
    G_Mandel_threadstat = rt;
    cout << rt << "\n";
    G_mandel_workerthread_info.maxthreads = 0;
    G_mandel_workerthread_info.running = false;
    cout << "finished threaded rendering\n";

}