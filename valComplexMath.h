#pragma once
#define vabs(a) (a<0?a*-1.0:a)

void VS_complex_div(double a, double b, double c, double d, double& rr, double& ii) {
    double h = ((c * c) + (d * d));
    if (h == 0) {
        cout << "complex division by zero, returning 0 error\n";
        rr = 0; ii = 0; return;
    }
    rr = ((a * c) + (b * d)) / h;
    ii = ((b * c) - (a * d)) / h;
}
void VS_complex_divLD(long double a, long  double b, long  double c, long  double d, long double& rr, long  double& ii) {
    long double h = ((c * c) + (d * d));
    if (h == 0) {
        cout << "complex division by zero, returning 0 error\n";
        rr = 0; ii = 0; return;
    }
    rr = ((a * c) + (b * d)) / h;
    ii = ((b * c) - (a * d)) / h;
}

void VS_complex_mul(double a, double b, double c, double d, double& rr, double& ii) {
    rr = (a * c) - (b * d);
    ii = (b * c) + (a * d);
}

void VS_complex_sin(double& r, double& i) {
    //sin(z) = sin(x + iy) = sin(x)cosh(y) + isinh(y)cos(x) https://math.stackexchange.com/questions/2738852/coding-the-complex-exp-sin-and-cos-function
    double rr = sin(r) * cosh(i);
    double ii = sinh(i) * cos(r);
    r = rr;
    i = ii;
}
void VS_complex_cos(double& r, double& i) {
    double rr = cos(r) * cosh(i);
    double ii = sinh(i) * sin(r);
    r = rr;
    i = ii;
}
void VS_complex_tan(double& r, double& i) {
    //double rr = sin(r) * cos(r);
    //double ii = sinh(i) * cosh(i) * sin(2 * r);
    //r = rr;
    //i = ii;
    double a = r, b = i, c = r, d = i;
    VS_complex_sin(a, b);
    VS_complex_cos(c, d);
    VS_complex_div(a, b, c, d, r, i);
}
void VS_complex_square(double& r, double& i) {
    double rr = r * r;
    double ii = i * i;
    i = (2 * r * i);
    r = (rr - ii);
}
void VS_complex_expweird(double& r, double& i, double expr) {
    double rr = pow(r, expr);
    double ii = pow(i, expr);
    i = (expr * r * i);
    double test = fmod(expr, 2);
    if (test == 0.0) {
        r = (rr - ii);
    }
    else {
        r = rr;
        i += ii;
    }

}

void VS_complex_exp(double a, double b, int e, double& rr, double& ii) {
    rr = a; ii = b;
    double cc, ccc;
    if (e == 2) {
        VS_complex_square(rr, ii);
        return;
    }
    for (int i = 2; i <= e; i++) {
        VS_complex_mul(rr, ii, a, b, cc, ccc);
        rr = cc;
        ii = ccc;
    }
}
void VS_complex_expb(double a, double b, int e, double& rr, double& ii) {
    rr = a; ii = b;
    double cc, ccc;
    if (e == 2) {
        VS_complex_square(rr, ii);
        return;
    }
    for (int i = 2; i <= e; i++) {
        VS_complex_mul(rr, ii, a, b, cc, ccc);
        rr = cc;
        ii = ccc;
    }
}
void VS_complex_E_Exponent(double x, double y, double& rx, double& ry) {
    double ex = exp(x);
    rx = ex * cos(y);
    ry = ex * sin(y);
}
void VS_complex_E_ExponentLD(double x, double y,long double& rx,long double& ry) {
    double ex = exp(x);
    rx = ex * cos(y);
    ry = ex * sin(y);
}
void VS_complex_R_Exponent(double r, double x, double y, double& rx, double& ry) {
    r = vabs(r); // r cannot be negative or 0 technically.
    double a = log(r);
    double ex = pow(r, x);
    rx = ex * cos(a * y);
    ry = ex * sin(a * y);

}
bool VS_complex_rangecomp(double x, double y, double xx, double yy, double swing) {
    /*if (xx == x && yy == y)return true;
    long double holdx=0,holdy=0;
    if(x>xx)holdx=x*/
    return (vabs((xx - x)) < swing && vabs((yy - y)) < swing);

}
bool VS_complex_rangecompw2(double x, double y, double xx, double yy, double swing) {
    /*if (xx == x && yy == y)return true;
    long double holdx=0,holdy=0;
    if(x>xx)holdx=x*/
    return (vabs(xx - x) < swing && vabs(yy - y) < swing);

}
bool VS_complex_rangecompw(double x, double y, double xx, double yy, double swing) {
    /*if (xx == x && yy == y)return true;
    long double holdx=0,holdy=0;
    if(x>xx)holdx=x*/
    return (vabs(x - xx) < swing && vabs(y - yy) < swing);

}
void VS_complex_mulLD(long double a, long  double b, long  double c, long  double d, long  double& rr, long  double& ii) {
    rr = (a * c) - (b * d);
    ii = (b * c) + (a * d);
}
void VS_complex_squareLD(long double& r, long  double& i) {
    long double rr = r * r;
    long double ii = i * i;
    i = (2 * r * i);
    r = (rr - ii);
}
void VS_complex_expLD(long double a, long  double b, int e, long  double& rr, long  double& ii) {
    rr = a; ii = b;
    long double cc, ccc;
    if (e == 2) {
        VS_complex_squareLD(rr, ii);
        return;
    }
    for (int i = 2; i <= e; i++) {
        VS_complex_mulLD(rr, ii, a, b, cc, ccc);
        rr = cc;
        ii = ccc;
    }
}
void VS_complex_exp_dumb(double a, double b, int e, double& rr, double& ii) {
    rr = a; ii = b;
    double cc, ccc;
    while (e != 1) {
        e--;
        VS_complex_mul(rr, ii, a, b, cc, ccc);
        rr = cc;
        ii = ccc;
    }
}
void VS_complex_bigexp(double a, double b, int e, double& rr, double& ii) {
    double hr = a, hi = b;
    while (e != 1) {
        while (e % 2 == 0) {
            e /= 2;
            VS_complex_square(a, b);
        }
        if (e == 1)break;
        VS_complex_mul(hr, hi, a, b, hr, hi);
        e -= 1;
    }
    VS_complex_mul(hr, hi, a, b, rr, ii);
    //while (exp.comp(BWONE) != 0) {

    //    while (exp.mod2() == 0) {
    //        exp = exp.half();
    //        hold = hold.squared();
    //        //hold2=hold2.mulbeta2(this);
    //    }
    //    if (exp.comp(BWONE) == 0)break;
    //    hold3 = hold3.mulbeta2(hold);
    //    exp.minus1();

    //}
    //return hold.mulbeta2(hold3);//.mulbeta2(hold2);
}

void VS_complex_cotan(double& r, double& i) {
    //double rr = sin(r) * cos(r);
    //double ii = sinh(i) * cosh(i) * sin(2 * r);
    //r = rr;
    //i = ii;
    double a = r, b = i, c = r, d = i;
    VS_complex_cos(a, b);
    VS_complex_sin(c, d);
    VS_complex_div(a, b, c, d, r, i);
}
void VS_complex_divwrong(double a, double b, double c, double d, double& rr, double& ii) {
    double h = ((c * c) + (d * d));
    if (h == 0) {
        rr = 0; ii = 0; return;
    }
    rr = a * c + b * d / h;
    ii = b * c - a * d / h;
}
void VS_complex_tanwrong(double& r, double& i) {
    //double rr = sin(r) * cos(r);
    //double ii = sinh(i) * cosh(i) * sin(2 * r);
    //r = rr;
    //i = ii;
    double a = r, b = i, c = r, d = i;
    VS_complex_sin(a, b);
    VS_complex_cos(c, d);
    VS_complex_divwrong(a, b, c, d, r, i);
}
void VS_complex_cotanwrong(double& r, double& i) {
    //double rr = sin(r) * cos(r);
    //double ii = sinh(i) * cosh(i) * sin(2 * r);
    //r = rr;
    //i = ii;
    double a = r, b = i, c = r, d = i;
    VS_complex_cos(a, b);
    VS_complex_sin(c, d);
    VS_complex_divwrong(a, b, c, d, r, i);
}
void VS_COMPLEX_Sqrt(long double& xr, long double& ir) {
    if (ir == 0) { xr = sqrt(xr); return; }
    long double x = xr, i = ir;
    //https://www.cuemath.com/algebra/square-root-of-complex-number/ adapted from equation found here
    long double xs = x * x, is = i * i;
    long double zabsz = sqrt(xs + is);
    long double r = sqrt((zabsz + x) / 2);
    long double ii = sqrt((zabsz - x) / 2);
    if (ir < 0)ii *= -1;
    // if (xr < 0)r *= -1;
    xr = r;
    ir = ii;
}
void VS_COMPLEX_Sqrt(double& xr, double& ir) {
    if (ir == 0) { xr = sqrt(xr); return; }
    double x = xr, i = ir;
    //https://www.cuemath.com/algebra/square-root-of-complex-number/ adapted from equation found here
    double xs = x * x, is = i * i;
    double zabsz = sqrt(xs + is);
    double r = sqrt((zabsz + x) / 2);
    double ii = sqrt((zabsz - x) / 2);
    if (i < 0)ii *= -1;
    xr = r;
    ir = ii;
}
void VS_COMPLEX_Sqrt_b(double& xr, double& ir) {
    if (ir == 0) { xr = sqrt(xr); return; }
    double x = xr, i = ir;
    //https://www.cuemath.com/algebra/square-root-of-complex-number/ adapted from equation found here
    double xs = x * x, is = i * i;
    double zabsz = sqrt(xs + is);
    double r = sqrt((zabsz + x) / 2);
    double ii = sqrt((zabsz - x) / 2);
    //if (i < 0)ii *= -1;
    xr = r * (xr < 0 ? 1 : -1);
    ir = ii * (ir < 0 ? 1 : -1);
}

void VS_COMPLEX_Sqrt2(double& xr, double& ir) {
    if (ir == 0) { xr = sqrt(xr); return; }
    double x = xr, i = ir;
    //https://www.cuemath.com/algebra/square-root-of-complex-number/ adapted from equation found here
    double xs = x * x, is = i * i;
    double zabsz = sqrt(xs + is);
    double r = sqrt((zabsz + x) / 2);
    double ii = sqrt((zabsz - x) / 2);
    //if (i < 0)ii *= -1;
    xr = r * (xr < 0 ? -1 : 1);
    ir = ii * (ir < 0 ? -1 : 1);
}
void VS_COMPLEX_Sqrt3(double& xr, double& ir) {
    if (ir == 0) { xr = sqrt(xr); return; }
    double x = xr, i = ir;
    //https://www.cuemath.com/algebra/square-root-of-complex-number/ adapted from equation found here
    double xs = x * x, is = i * i;
    double zabsz = sqrt(xs + is);
    double r = sqrt((zabsz + x) / 2);
    double ii = sqrt((zabsz - x) / 2);
    if (x < 0)r *= -1;
    xr = r;
    ir = ii;
}
int VS_COMPLEX_SqrtSafe2(long double& xr, long double& ir) {
    long double h = xr, hh = ir;
    long double xrd, ird;
    VS_COMPLEX_Sqrt(h, hh);
    long double xh = h, ih = hh;
    long double t = h, tt = hh;
    xrd = h; ird = hh;
    for (int i = -6; i < 6; i++) {

        for (int n = -30; n < 30; n++) {
            t = h + (.00000000000000001 * i);
            tt = hh + (.00000000000000001 * n);
            xrd = t; ird = tt;
            VS_complex_squareLD(t, tt);
            if (t == xr && tt == ir) {
                xr = xrd; ir = ird;
                return i + 7;
            }
        }
    }
    xr = xh;
    ir = ih;
    return 0;
}
int VS_COMPLEX_SqrtSafe2(double& xr, double& ir) {
    double h = xr, hh = ir;
    double xrd, ird;
    VS_COMPLEX_Sqrt(h, hh);
    double xh = h, ih = hh;
    double t = h, tt = hh;
    xrd = h; ird = hh;
    for (int i = -6; i < 6; i++) {

        for (int n = -30; n < 30; n++) {
            t = h + (.00000000000000001 * i);
            tt = hh + (.00000000000000001 * n);
            xrd = t; ird = tt;
            VS_complex_square(t, tt);
            if (t == xr && tt == ir) {
                xr = xrd; ir = ird;
                return i + 7;
            }
        }
    }
    xr = xh;
    ir = ih;
    return 0;
}
/******************************************end VS_COMPLEX math block*************************************************************/