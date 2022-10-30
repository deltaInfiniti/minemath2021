#pragma once

int calc_mandle_julia_Euler(double x, double y, double cx, double cy, int maxits, int bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}

int calc_mandle_julia_sqrt(double x, double y, double cx, double cy, int maxits, double bail) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_iansfunction(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}

int calc_mandle_sqrt(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt2(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp_dumb(zx, zy, 3, zx, zy);
        zx += cx;
        zy += cy;
        VS_COMPLEX_Sqrt(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt2(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp_dumb(zx, zy, 3, zx, zy);
        zx += x;
        zy += y;
        VS_COMPLEX_Sqrt(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt3(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt3(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt4(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = 0, zy = 0;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt4(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = 0, zy = 0;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt5(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);

        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt5(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt6(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt_b(zx, zy);

        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt6(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt_b(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt7(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt7(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}int calc_mandle_julia_sqrt8(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);

        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt8(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt9(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_square(zx, zy);
        VS_complex_square(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt9(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = y, zy = x;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_square(zx, zy);
        VS_complex_square(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt1t(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_COMPLEX_Sqrt2(zx, zy);
        zx -= cx;
        zy -= cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt1t(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_COMPLEX_Sqrt2(zy, zx);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt10(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);

        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt10(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt11(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);

        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt11(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt12(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);

        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt12(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt13(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt13(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt14(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt14(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt15(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp_dumb(zx, zy, 8, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt15(double x, double y, int maxits, double bail) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp_dumb(zx, zy, 8, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        zx += x;
        zy += y;
        if ((zx * zx) + (zy * zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt_error1(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {


        VS_complex_square(zx, zy);
        VS_COMPLEX_Sqrt3(zx, zy);
        VS_complex_square(zx, zy);

        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt_error1(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {


        VS_complex_square(zx, zy);
        VS_COMPLEX_Sqrt3(zx, zy);
        VS_complex_square(zx, zy);

        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt_error2(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_square(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_complex_square(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt_error2(double x, double y, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_square(zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);
        VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt_errortest(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt_errortest(double x, double y, int maxits, double bail) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        if ((zx * zx) + (zy * zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_julia_sqrt_errortest2(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp_dumb(zx, zy, 4, zx, zy);
        //VS_COMPLEX_Sqrt2(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt_errortest2(double x, double y, int maxits, double bail) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp_dumb(zx, zy, 4, zx, zy);
        //VS_COMPLEX_Sqrt2(zx, zy);
        zx += x;
        zy += y;
        if ((zx * zx) + (zy * zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_sqrt_errortesttrue(double x, double y, int maxits, int bail = 4) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}

int calc_mandle_julia_magnetm2(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_exp(zx, zy, 19, zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        VS_COMPLEX_Sqrt2(zx, zy);
        zx += cx;
        zy += cy;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2b(double x, double y, int maxits, double bail = 4) {
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
        its++;
    }
    return its;
}
int calc_mandle_magnetm2bb(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = x, zy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) + 2;
    consfacty -= (y * 3);
    long double zxcopyb = 100, zycopyb = 100;
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
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return (its * its) % maxits;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true(double x, double y, int maxits, double bail = 4) {
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

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true2(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = x, zy = y;
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

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3(double x, double y, double cx, double cy, int maxits, double bail = 4) {
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
    consfactx += cx;
    consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3b(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = cx, zy = cy;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) - 2;
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3c(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = cx * 3, threecy = cy * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (cx * 3) - 2;
    consfacty -= (cy * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3d(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = x, zy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = cx * 3, threecy = cy * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = cx, consfacty = cy;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (cx * 3) - 2;
    consfacty -= (cy * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3e(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = cx * 3, threecy = cy * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = cx, consfacty = cy;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (cx * 3) - (x + 2);
    consfacty -= (cy * 3) - y;
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3f(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = cx * 3, threecy = cy * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = cx, consfacty = cy;
    VS_complex_squareLD(consfactx, consfacty);

    VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (cx * 3) - (2);
    consfacty -= (cy * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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
        zx += cx;
        zy += cy;
        if (vabs((zx * zx)) + vabs((zy * zy)) > bail2)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3g(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = cx, consfacty = cy;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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
        zx += cx;
        zy += cy;
        if (vabs((zx * zx)) + vabs((zy * zy)) > bail2)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3h(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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
        zx += cx;
        zy += cy;
        if (sqrt(vabs((zx * zx)) + vabs((zy * zy))) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3i(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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
        numerx += consfactx + cx;
        numery += consfacty + cy;
        denomx += consfactx + 1;
        denomy += consfacty;

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
        //zx += cx;
        //zy += cy;
        if (sqrt(vabs((zx * zx)) + vabs((zy * zy))) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3j(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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
        denomx += consfactx + 1 + cx;
        denomy += consfacty + cy;

        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);
        //zx += cx;
        //zy += cy;
        if (sqrt(vabs((zx * zx)) + vabs((zy * zy))) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3k(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
    while (its < maxits) {
        denomx = zx + cx; denomy = zy + cy;
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
        //zx += cx;
        //zy += cy;
        if (sqrt(vabs((zx * zx)) + vabs((zy * zy))) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3l(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        //numerx = denomx, numery = denomy;
        VS_complex_mulLD(denomx, denomy, cx, cy, numerx, numery);
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
        //zx += cx;
        //zy += cy;
        if (sqrt(vabs((zx * zx)) + vabs((zy * zy))) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3m(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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
        zx += cx;
        zy += cy;
        VS_complex_square(zx, zy);

        if (sqrt(vabs((zx * zx)) + vabs((zy * zy))) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3n(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    long double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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

        VS_complex_divLD(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_mulLD(zx, zy, cx, cy, zx, zy);
        VS_complex_expLD(zx, zy, 3, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);

        if (sqrt(vabs((zx * zx)) + vabs((zy * zy))) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2_true3o(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    long double zx = 0, zy = 0;
    long double xx = x, yy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double bail2 = bail * bail;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);

    //VS_complex_mulLD(consfactx, consfacty, xx, yy, consfactx, consfacty);
    consfactx -= (x * 3) - (2);
    consfacty -= (y * 3);
    //consfactx += cx;
    //consfacty += cy;
    long double zxcopyb = 100, zycopyb = 100;
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

        VS_complex_divLD(numerx, numery, denomx, denomy, zx, zy);
        //VS_complex_squareLD(zx, zy);
        //       VS_complex_mulLD(zx, zy, cx, cy, zx, zy);
        VS_complex_expLD(zx, zy, 5, zx, zy);
        VS_COMPLEX_Sqrt(zx, zy);

        //        if (sqrt(vabs((zx * zx)) + vabs((zy * zy))) > bail)return its;
        //        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;

        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2(double x, double y, int maxits, double bail = 4) {
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
        its++;
    }
    return its;
}
int calc_mandle_magnetm2c(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double zxcopyb = 100, zycopyb = 100;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) + 2;
    consfacty -= (y * 3);
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
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return (its * its) % maxits;
        //if (vabs(zx) + vabs(zy) > vabs(zxcopyb) + vabs(zycopyb))return its;//return maxits - its;// 
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2d(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double zxcopyb = 100, zycopyb = 100;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) + 2;
    consfacty -= (y * 3);
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        //numerx = denomx, numery = denomy;
        VS_complex_mulLD(denomx, denomy, zx, zy, numerx, numery);
        denomx *= 3;
        denomy *= 3;
        // at this point, we have z^3/3z^2
        VS_complex_mulLD(x, y, zx, zy, zxcopy, zycopy);
        zxcopy *= 3;
        zycopy *= 3;
        zxcopy -= (x * 3);
        zycopy -= (y * 3);
        numerx += zxcopy;
        numery += zycopy;
        zxcopy -= (x * 3);
        zycopy -= (y * 3);
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
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return (its * its) % maxits;
        //if (vabs(zx) + vabs(zy) > vabs(zxcopyb) + vabs(zycopyb))return its;//return maxits - its;// 
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2db(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = x, zy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double zxcopyb = 100, zycopyb = 100;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) + 2;
    consfacty -= (y * 3);
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        //numerx = denomx, numery = denomy;
        VS_complex_mulLD(denomx, denomy, zx, zy, numerx, numery);
        denomx *= 3;
        denomy *= 3;
        // at this point, we have z^3/3z^2
        VS_complex_mulLD(x, y, zx, zy, zxcopy, zycopy);
        zxcopy *= 3;
        zycopy *= 3;
        zxcopy -= (x * 3);
        zycopy -= (y * 3);
        numerx += zxcopy;
        numery += zycopy;
        zxcopy -= (x * 3);
        zycopy -= (y * 3);
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
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return (its * its) % maxits;
        //if (vabs(zx) + vabs(zy) > vabs(zxcopyb) + vabs(zycopyb))return its;//return maxits - its;// 
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm2dc(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    long double zxcopyb = 100, zycopyb = 100;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) - 2;
    consfacty -= (y * 3);
    while (its < maxits) {
        denomx = zx; denomy = zy;
        VS_complex_squareLD(denomx, denomy);
        //numerx = denomx, numery = denomy;
        VS_complex_mulLD(denomx, denomy, zx, zy, numerx, numery);
        denomx *= 3;
        denomy *= 3;
        // at this point, we have z^3/3z^2
        VS_complex_mulLD(x, y, zx, zy, zxcopy, zycopy);
        zxcopy *= 3;
        zycopy *= 3;
        zxcopy -= (x * 3);
        zycopy -= (y * 3);
        numerx += zxcopy;
        numery += zycopy;
        zxcopy -= (x * 3);
        zycopy -= (y * 3);
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
        if (VS_complex_rangecomp(zx, zy, 0, 0, .0000001))return maxits;// -(its % (maxits / 100));
        //if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return (its * its) % maxits;
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        //if (vabs(zx) + vabs(zy) > vabs(zxcopyb) + vabs(zycopyb))return its;//return maxits - its;// 
        zxcopyb = zx; zycopyb = zy;
        its++;
    }
    return its;
}
int calc_mandle_magnetm1b(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = x, zy = y;
    long double numerx, numery;
    long double denomx, denomy;
    long double threecx = x * 3, threecy = y * 3;
    long double zxcopy, zycopy;
    // c^2-3c-2
    long double consfactx = x, consfacty = y;
    VS_complex_squareLD(consfactx, consfacty);
    consfactx -= (x * 3) + 2;
    consfacty -= (y * 3);
    while (its < maxits) {
        denomx = ((zx * 2) + x) - 1; denomy = ((zy * 2) + y);
        numerx = zx; denomy = zy;
        VS_complex_squareLD(numerx, numery);
        numerx += x - 1;
        numery += y;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_magnetm1(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    // c^2-3c-2

    while (its < maxits) {
        denomx = ((zx * 2) + x) - 1; denomy = ((zy * 2) + y);
        numerx = zx; numery = zy;
        VS_complex_squareLD(numerx, numery);
        numerx += x - 1;
        numery += y;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_magnetm1c(double x, double y, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    // c^2-3c-2
    long double zxcopyb = 100, zycopyb = 100;
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
        its++;
    }
    return its;
}
int calc_mandle_magnetm1d(double x, double y, double cx, double cy, int maxits, double bail = 4) {
    int its = 1;
    double zx = 0, zy = 0;
    long double numerx, numery;
    long double denomx, denomy;
    // c^2-3c-2
    long double zxcopyb = 100, zycopyb = 100;
    while (its < maxits) {
        denomx = ((zx * 2) + x) - 2; denomy = ((zy * 2) + y);
        numerx = zx; numery = zy;
        VS_complex_squareLD(numerx, numery);
        numerx += (x - 1) + cx;
        numery += y + cy;
        VS_complex_div(numerx, numery, denomx, denomy, zx, zy);
        VS_complex_square(zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        if (VS_complex_rangecomp(zx, zy, zxcopyb, zycopyb, .0000000001))return its;
        zycopyb = zy;
        zxcopyb = zx;
        its++;
    }
    return its;
}


int calc_mandle_Euler(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = 0, zy = 0;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler2(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        //VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        VS_complex_E_Exponent(zx, zy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler3(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        VS_complex_E_Exponent(zx, zy, zx, zy);

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler4(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;

        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler5(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_square(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx -= x;
        zy -= y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler6(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_tan(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler7(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_sin(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler8(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_cos(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler9(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        VS_complex_tanwrong(zx, zy);
        VS_complex_E_Exponent(zx, zy, zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler10(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_tanwrong(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler11(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {

        VS_complex_E_Exponent(zx, zy, zx, zy);
        VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler12(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    double halfpi = 1.57079632679;
    while (its < maxits) {

        VS_complex_E_Exponent(zx, zy * halfpi, zx, zy);
        //VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_Euler13(double x, double y, int maxits, double bail = 4.0) {
    //cout << "euler bail = " << bail << endl;
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    long double zxcopy, zycopy;
    double halfpi = 1.57079632679;
    while (its < maxits) {

        VS_complex_E_Exponent(zx, zy * halfpi * 2, zx, zy);
        //VS_complex_square(zx, zy);
        zx += x;
        zy += y;
        if (vabs(zx) + vabs(zy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_derbail(double x, double y, int maxits = 1000, double bail = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX = 0, derbY = 0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX += 2 * zx;
        derbY += 2 * zy;
        if (vabs(derbX) + vabs(derbY) > bail)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_derbail2(double x, double y, int maxits = 1000, double bail = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX = 0, derbY = 0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX += 2 * zx;
        derbY += 2 * zy;
        if (vabs((derbX + derbY)) > bail)return its;
        zy = (2 * zx * zy) + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_derbail3(double x, double y, int maxits = 1000, double bail = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX = 0, derbY = 0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX += 2 * zx;
        derbY += 2 * zy;
        zy = (2 * zx * zy) + y;
        zx = (zxcopy - zycopy) + x;
        if (vabs((derbX + derbY)) > (vabs((zx + zy))) * (bail))return its;
        if (vabs(zxcopy) + vabs(zycopy) > bail)return its;
        its++;
    }
    return its;
}
int calc_mandle_derbail4(double x, double y, int maxits = 1000, double bail = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX = 0, derbY = 0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX += 2 * zx;
        derbY += 2 * zy;
        zy = (2 * zx * zy) + y;
        zx = (zxcopy - zycopy) + x;
        if (vabs((derbX + derbY)) > (vabs(zxcopy) + vabs(zycopy)) * (bail))return its;
        if (vabs(zxcopy) + vabs(zycopy) > bail)return its;
        its++;
    }
    return its;
}

int calc_mandle_derbail5(double x, double y, int maxits = 1000, double bail = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double derbX = 0, derbY = 0;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        derbX = 2 * zx;
        derbY = 2 * zy;
        zy = (2 * zx * zy) + y;
        zx = (zxcopy - zycopy) + x;
        if (vabs((derbX + derbY)) > (vabs(zxcopy) * vabs(zycopy)) * (bail))return its;
        if (vabs(zxcopy) + vabs(zycopy) > bail)return its;
        its++;
    }
    if (vabs(derbX) + vabs(derbY) > bail) return its - 3;
    return its;
}



int calc_mandle(double x, double y, int maxits = 1000) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong(double x, double y, int maxits = 1000) {
    // 3 arms of oddity
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double xh;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;

        zy = (2 * zx * zy) + x;
        zx = (zxcopy - zycopy) + y;
        xh = zy;
        zy = zx;
        zx = xh;
        its++;
    }
    return its;
}
int calc_mandle_wrong2(double x, double y, int maxits = 1000) {
    // swiped mandelbrot set
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double xh;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;

        //zy = (2 * zx * zy) + x; 
        zy = (2 * zx * zy) + y;
        //zx = (zxcopy - zycopy) + y;
        //zx = (zxcopy - zycopy) + (y-1);
        //zx = (zxcopy - zycopy) + (y/1.1);
        zx = (zxcopy - zycopy) - x;
        its++;
        //(+y)  (-1) for rocket ship
    }
    return its;
}
int calc_mandle_wrong3(double x, double y, int maxits = 1000) {
    // swiped mandelbrot set correct direction
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double xh;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;

        //zy = (2 * zx * zy) + x; 
        zy = (2 * zx * zy) - y;
        //zx = (zxcopy - zycopy) + y;
        //zx = (zxcopy - zycopy) + (y-1);
        //zx = (zxcopy - zycopy) + (y/1.1);
        zx = (zxcopy - zycopy) + x;
        its++;
        //(+y)  (-1) for rocket ship
    }
    return its;
}
int calc_mandle_wrong4(double x, double y, int maxits = 1000) {
    // flatback with rainbow spirals
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    long double xh;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;

        //zy = (2 * zx * zy) + x; 
        zy = (2 * zx * zy) + zy;
        //zx = (zxcopy - zycopy) + y;
        //zx = (zxcopy - zycopy) + (y-1);
        //zx = (zxcopy - zycopy) + (y/1.1);
        zx += (zxcopy - zycopy) - x;
        its++;
        //(+y)  (-1) for rocket ship
    }
    return its;
}
int calc_mandle_wrong5(double x, double y, int maxits = 1000) {
    //  Whoah!...  

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx + y;
        zycopy = zy * zy + x;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) - y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) - x;
        its++;
    }
    return its;
}
int calc_mandle_wrong6(double x, double y, int maxits = 1000) {
    //  Whoah !...  but correct orientation

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx - y;
        zycopy = zy * zy - x;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong7(double x, double y, int maxits = 1000) {
    //  kinda boring zoomed out

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx + y;
        zycopy = zy * zy + x;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong8(double x, double y, int maxits = 1000) {
    //  kinda boring zoomed out

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 8.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zycopy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong9(double x, double y, int maxits = 1000) {
    //  kinda boring zoomed out

    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zx = (2 * zxcopy * zycopy) + y;
        //zx = zxcopy - zycopy + y;
        zy = (zx - zy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong10(double x, double y, int maxits = 1000) {
    //weird mandle-boodah triangle 128 itts shows the magic hands
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zx = (2 * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zy = (zxcopy - zycopy) + x;
        its++;
    }
    return its;
}
int calc_mandle_wrong11(double x, double y, int maxits = 1000) {
    //The fumkin mandelbrot-butterfly.  I found it.
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + (y * y / x);
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (x * x / y);
        its++;
    }
    return its;
}
int calc_mandle_wrong12(double x, double y, int maxits = 1000) {
    //odd splitup
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) - (zy / x);
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (zx / y);
        its++;
    }
    return its;
}
int calc_mandle_wrong13(double x, double y, int maxits = 1000) {
    //starry claw2
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = (2 * zx * zy) + (zy / x);
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (zx / y);
        its++;
    }
    return its;
}
int calc_mandle_wrong14(double x, double y, int maxits = 1000) {
    long double its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = ((2 - vabs(x / its)) * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (x)-y;// -(y / its);
        its++;
    }
    return its;
}
int calc_mandle_wrong15(double x, double y, int maxits = 1000) {
    int its = 1;
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 4.0)return its;
        zy = (2 * zx * zy) + x;
        zx = (zxcopy - zycopy) + y;
        its++;
    }
    return its;
}
int calc_mandle_wrong16(double x, double y, int maxits = 1000) {
    long double its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = ((2 - vabs(x / its)) * zx * zy) + y;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (x);// -(y / its);
        its++;
    }
    return its;
}
int calc_mandle_wrong17(double x, double y, int maxits = 1000) {
    long double its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    long double zxcopy, zycopy;
    while (its < maxits) {
        zxcopy = zx * zx;
        zycopy = zy * zy;
        if (vabs(zxcopy) + vabs(zycopy) > 32.0)return its;
        //zy = 2 * zx * zy + x;
        zy = ((2 - vabs(x / its)) * zx * zy) + x;
        //zx = zxcopy - zycopy + y;
        zx = (zxcopy - zycopy) + (y)+(y + x / its);// -(y / its);
        its++;
    }
    return its;
}
int calc_mandle_wrong18(double x, double y, int maxits = 1000) {
    long double its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy;
    while (its < maxits) {
        if (vabs(zx * zx) + vabs(zy * zy) > 16) return its;
        VS_complex_square(zx, zy);
        zx += x; zy += y;
        its++;
    }
    return its;
}
#define JULIASET_Y 2100
#define JULIASET_X 2100
#define VPNLRF Vals_parameterized_nonlinear_recursive_function

int Vals_parameterized_nonlinear_recursive_function(double& x, double& y, double& cx, double& cy, int& depth, int maxdepth = 100, int Rvalue = 1) {
    if (depth >= maxdepth) {
        return maxdepth;
    }
    depth++;
    double n = x * cx;
    double t = y * cy;
    double c = (double)depth / (double)maxdepth;

    if ((vabs(n) + vabs(t)) * c > Rvalue)return depth;
    VS_complex_square(n, t);
    if (n < t) n *= -1;
    else if (t < n)t *= -1;
    if (x > n && y > t) {
        Vals_parameterized_nonlinear_recursive_function(x, y, n, t, depth, maxdepth, Rvalue * 2);
    }
    else if (x < n && y < t) {
        int d2 = depth / 2;
        Vals_parameterized_nonlinear_recursive_function(n, t, cx, cy, d2, maxdepth, Rvalue / 2);
        depth += d2 / c;
    }
    else {
        x = n;
        cy = t;
        VS_complex_sin(n, t);
        depth++;
        cx = n;
        y = t;
    }
    return Vals_parameterized_nonlinear_recursive_function(x, y, cx, cy, depth, maxdepth, Rvalue);
}

int calc_julia2(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * x * y) + cx;
        x = (xcopy - ycopy) + cy;

        its++;
    }

    return its;
}
int calc_julia(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * x * y) + cy;
        x = (xcopy - ycopy) + cx;

        its++;
    }

    return its;
}
int calc_julia3(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 - vabs(x / its) * x * y) + cy;
        x = (xcopy - ycopy) + cx;

        its++;
    }

    return its;
}

int calc_julia4(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        x = (2 * x * y) + cy;
        y = (xcopy - ycopy) + cx;

        its++;
    }

    return its;
}
int calc_julia5(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * xcopy * y) + cy;
        x = (x - ycopy) + cx;

        its++;
    }

    return its;
}
int calc_julia6(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * x * ycopy) + cy;
        x = (xcopy - y) + cx;

        its++;
    }

    return its;
}
int calc_julia7(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 4) {

    int its = 1;
    double xcopy, ycopy;
    while (its < maxits) {
        xcopy = x * x;
        ycopy = y * y;
        if (xcopy + ycopy > Rvalue)return its;

        y = (2 * x * y) + cy;
        x = (xcopy - ycopy) + cx;

        cx = y;
        cy = x;
        its++;
    }

    return its;
}
int calc_julia_tan(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_tan(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_tanwrong(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_tanwrong(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_cotanwrong(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_cotanwrong(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_cotan(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_cotan(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_cos(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_cos(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_sin(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_sin(xcopy, ycopy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_sin_tan(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_sin(cx, ycopy);
        VS_complex_tan(xcopy, cy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_sin_tanwrong(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_sin(cx, ycopy);
        VS_complex_tanwrong(xcopy, cy);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}
int calc_julia_exp_exp(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_square(x, ycopy);
        VS_complex_square(xcopy, y);
        if (xcopy + ycopy > Rvalue)return its;
        xcopy += cx;
        ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_exp_exp_exp(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_square(x, ycopy);
        VS_complex_square(cx, y);
        VS_complex_square(xcopy, cy);
        VS_complex_square(xcopy, y);
        if (xcopy + ycopy > Rvalue)return its;
        //        xcopy += cx;
        //       ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_threexp(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_exp(xcopy, ycopy, 4, xcopy, ycopy);

        if (xcopy + ycopy > Rvalue)return its;
        xcopy += cx;
        ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_threexpLD(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 64) {

    int its = 1;
    long double xcopy = x, ycopy = y;
    while (its < maxits) {

        VS_complex_expLD(xcopy, ycopy, 4, xcopy, ycopy);

        if (xcopy + ycopy > Rvalue)return its;
        xcopy += cx;
        ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_exp7(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 6400) {

    int its = 1;
    double xcopy = x, ycopy = y;
    double rr, ii;
    while (its < maxits) {
        VS_complex_bigexp(xcopy, ycopy, 7, rr, ii);
        xcopy = rr;
        ycopy = ii;

        if (xcopy + ycopy > Rvalue)return its;
        xcopy += cx;
        ycopy += cy;
        its++;
    }

    return its;
}
int calc_julia_exp127(double x, double y, double cx, double cy, int maxits = 100, int Rvalue = 6400) {

    int its = 1;
    double xcopy = x, ycopy = y;
    double rr, ii;
    while (its < maxits) {
        VS_complex_bigexp(xcopy, ycopy, 127, rr, ii);
        xcopy = rr;
        ycopy = ii;

        if (xcopy + ycopy > Rvalue)return its;
        xcopy *= cx;
        ycopy *= cy;
        its++;
    }

    return its;
}

int calc_Newton_e3m1(double x, double y, int maxits = 1000, double bailout = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    while (its < maxits) {
        VS_complex_exp(zx, zy, 3, zxcopy, zycopy);
        //zxcopy -= 1;
        zxcopy += x;
        zycopy += y;
        hold = vabs(zxcopy) + vabs(zycopy);
        if (hold == 0)return maxits - its;// return its;// *-1;
        if (hold > bailout)return its;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    return its;
}

int calc_Newton_e3m1_2(double x, double y, int maxits = 1000, double bailout = 4.0) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    long double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    while (its < (maxits / 6)) {
        VS_complex_exp(zx, zy, 4, zxcopy, zycopy);
        zxcopy -= 1;
        //zxcopy += x;
        //zycopy += y;
        hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.0001))return its * 3;
        if (VS_complex_rangecomp(zxcopy, zycopy, -1, 0, 0.0001))return its * 4;
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, 1, 0.0001))return its * 5;
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, -1, 0.0001))return its * 6;
        if (hold > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    if (its == maxits / 6)return maxits;

    if (its < maxits / 6)its %= maxits / 5;
    else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e3m1_3(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        //VS_complex_exp(zx, zy, 3, xx, yy);
        //VS_complex_mul(xx, yy, 3, 0, xx, yy);
        //VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        //zxcopy= zx - xx;
        //zycopy= zy- yy;
//        zxcopy = xx;
 //       zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.00005))return (spaces * 2);

        if (VS_complex_rangecomp(zxcopy, zycopy, -1, 0, 0.00005))return  (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, 1, 0.00005))return (spaces * 5);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, -1, 0.00005))return (spaces * 6);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e4m1_db(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 3;
        yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        //zxcopy= zx - xx;
        //zycopy= zy- yy;
        zxcopy = xx;
        zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecompw(zxcopy, zycopy, 1, 0, 0.00005))return (its % spaces) + (spaces * 2);
        if (VS_complex_rangecompw(zxcopy, zycopy, -1, 0, 0.00005))return  (its % spaces) + (spaces * 4);
        if (VS_complex_rangecompw(zxcopy, zycopy, 0, 1, 0.0000000001))return (its % spaces) + (spaces * 5);
        if (VS_complex_rangecompw(zxcopy, zycopy, 0, -1, 0.0000000001))return (its % spaces) + (spaces * 6);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e4m1_db_b(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 3;
        yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        //zxcopy= zx - xx;
        //zycopy= zy- yy;
        zxcopy = xx;
        zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.00005))return (its % spaces) + (spaces * 2);
        //if (VS_complex_rangecomp(zxcopy, zycopy, -1, 0, 0.00005))return  (its % spaces) + (spaces * 4);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0, 1, 0.0000000001))return (its % spaces) + (spaces * 5);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0, -1, 0.0000000001))return (its % spaces) + (spaces * 6);
        if (VS_complex_rangecompw(zxcopy, zycopy, cx, cy, 0.0000001))return its + (spaces);
        if (VS_complex_rangecompw(zxcopy, zycopy, cx * -1, cy, 0.0000001))return its + (spaces * 3);
        if (VS_complex_rangecompw(zxcopy, zycopy, cx, cy * -1, 0.0000001))return its + (spaces * 2);
        if (VS_complex_rangecompw(zxcopy, zycopy, cx * -1, cy * -1, 0.0000001))return its + (spaces * 4);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e3m1_4(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 3;
        yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        //zxcopy = xx;
        //zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.0000000001))return (its % spaces * 2);// +(spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, -1, 0, 0.0000000001))return  (its % spaces * 2) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, 1, 0.0000000001))return (its % spaces * 2) + (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, -1, 0.0000000001))return (its % spaces * 2) + (spaces * 6);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_2E4M1(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy *= 2;
        zycopy *= 2;
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 6;
        yy *= 6;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;

        if (VS_complex_rangecomp(zxcopy, zycopy, 0, -0.840896, 0.00001))return (its % spaces);// +(spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.840896, 0, 0.00001))return  (its % spaces) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.840896, 0, 0.00001))return (its % spaces) + (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0, 0.840896, 0.00001))return (its % spaces) + (spaces * 6);
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_trueE3M1(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 3, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 2, xx, yy);
        xx *= 2;
        yy *= 2;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.5, -0.866025, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 1);
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.5, 0.866025, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 3);
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_E13M1(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 13, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 12, xx, yy);
        xx *= 12;
        yy *= 12;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.748511, -0.663123, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 1);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.120537, -0.992709, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 1, 0, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 3);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.748511, 0.663123, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.120537, 0.992709, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 0);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.354605, -0.935016, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 1);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.885456, 0.464723, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.885456, -0.464723, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 3);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.970942, -0.239316, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 4);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.568065, -0.822984, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 0);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.354605, 0.935016, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 1);
        if (VS_complex_rangecomp(zxcopy, zycopy, -0.970942, 0.239316, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 2);
        if (VS_complex_rangecomp(zxcopy, zycopy, 0.568065, 0.822984, 0.00001))return ((its * its) % (spaces * 3)) + (spaces * 3);

        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e3m1_4c(double x, double y, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx * 3, zy * 3, 3, xx, yy);
        //xx *= 3;
        //yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        //zxcopy = xx;
        //zycopy = yy;
        //zxcopy += x;
        //zycopy += y;
        //hold = vabs(zxcopy) + vabs(zycopy);
        //if (hold == 0)return maxits - its;// return its;// *-1;
        //if (zxcopy == 1 && zycopy == 0)return its * 3;
        //if (zxcopy == -1 && zycopy == 0)return its * 4;
        //if (zxcopy == 0 && zycopy == 1)return its * 5;
        //if (zxcopy == 0 && zycopy == -1)return its * 6;
        if (VS_complex_rangecompw(zxcopy, zycopy, 1, 0, 0.0000000001))return (its % spaces * 2);// +(spaces * 2);
        if (VS_complex_rangecompw(zxcopy, zycopy, -1, 0, 0.0000000001))return  (its % spaces * 2) + (spaces * 2);
        if (VS_complex_rangecompw(zxcopy, zycopy, 0, 1, 0.0000000001))return (its % spaces * 2) + (spaces * 4);
        if (VS_complex_rangecompw(zxcopy, zycopy, 0, -1, 0.0000000001))return (its % spaces * 2) + (spaces * 6);
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, 0.7071068, 0.0001))return its * 3;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, 0.7071068, 0.0001))return its * 4;
        //if (VS_complex_rangecomp(zxcopy, zycopy, 0.7071068, -0.7071068, 0.0001))return its * 5;
        //if (VS_complex_rangecomp(zxcopy, zycopy, -0.7071068, -0.7071068, 0.0001))return its * 6;
        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}
int calc_Newton_e3m1_4b(double x, double y, double cx, double cy, int maxits, double bailout) {
    int its = 1;
    //double abs = vabs(x) + vabs(y);
    double zx = x, zy = y;
    double zxcopy, zycopy, hold;
    double xx, yy;
    int spaces = (maxits / 7) + 1;
    while (its < (maxits / 6)) { // currently  z^4+1 / 3z^3
        VS_complex_exp_dumb(zx, zy, 4, zxcopy, zycopy);  // 5 was nice
        zxcopy -= 1;
        VS_complex_exp_dumb(zx, zy, 3, xx, yy);
        xx *= 3;
        yy *= 3;
        VS_complex_div(zxcopy, zycopy, xx, yy, xx, yy);
        zxcopy = zx - xx;
        zycopy = zy - yy;
        if (VS_complex_rangecompw2(zxcopy, zycopy, cx, cy, 0.0001))return its + (spaces);
        if (VS_complex_rangecompw2(zxcopy, zycopy, cx * -1, cy, 0.0001))return its + (spaces * 3);
        if (VS_complex_rangecompw2(zxcopy, zycopy, cx, cy * -1, 0.0001))return its + (spaces * 2);
        if (VS_complex_rangecompw2(zxcopy, zycopy, cx * -1, cy * -1, 0.0001))return its + (spaces * 4);

        if (vabs(zxcopy) + vabs(zycopy) > bailout)break;
        zx = zxcopy;
        zy = zycopy;
        its++;
    }
    //if (its == maxits / 6)return maxits;
    return maxits;
    //    if (its < maxits / 6)its %= maxits / 5;
      //  else its = maxits - (its % (maxits / 5));
    return its;
}