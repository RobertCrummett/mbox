#include <math.h>
#include <stddef.h>

#include "mbox.h"

void mbox_dircos(double incl, double decl, double azim, double* a, double* b, double* c) {
    const double deg2rad = 0.017453292519943295;
    double xincl = incl * deg2rad;
    double xdecl = decl * deg2rad;
    double xazim = azim * deg2rad;
    *a = cos(xincl) * cos(xdecl - xazim);
    *b = cos(xincl) * sin(xdecl - xazim);
    *c = sin(xincl);
}

void mbox_mbox(double* x0, double* y0, double* z0, size_t n, double x1, double y1, double z1, double x2, double y2,
        double mincl, double mdecl, double fincl, double fdecl, double magn, double* tfa) {
    const double cm = 1e-7;
    const double t2nt = 1e9;
    size_t i,j,k;
    double ma,mb,mc,fa,fb,fc,fm1,fm2,fm3,fm4,fm5,fm6;

    mbox_dircos(mincl, mdecl, 0.0, &ma, &mb, &mc);
    mbox_dircos(fincl, fdecl, 0.0, &fa, &fb, &fc);

    fm1 = ma*fb + mb*fa;
    fm2 = ma*fc + mc*fa;
    fm3 = mb*fc + mc*fb;
    fm4 = ma*fa;
    fm5 = mb*fb;
    fm6 = mc*fc;

    for (k = 0; k < n; k++) {
        double alpha[2] = {x1 - x0[k], x2 - x0[k]};
        double beta[2]  = {y1 - y0[k], y2 - y0[k]};
        double h = z1 - z0[k];
        double h2 = h * h;
        double a,b,a2,sign,r02,r0,r0h,ab,arg1,arg2,arg3,arg4,tlog,tatan,t=0.0;

        for (i = 0; i < 2; i++) {
            a = alpha[i];
            a2 = a * a;
            for (j = 0; j < 2; j++) {
                sign = (i != j) ? -1.0 : 1.0;
                b = beta[j];
                r02 = a2 + b * b + h2;
                r0 = sqrt(r02);
                r0h = r0 * h;
                ab = a * b;
                arg1 = (r0-a)/(r0+a);
                arg2 = (r0-b)/(r0+b);
                arg3 = a2 + r0h + h2;
                arg4 = r02 + r0h - a2;
                tlog = fm3 * log(arg1) / 2.0 + fm2 * log(arg2) / 2.0 - fm1 * log(r0 + h);
                tatan = -fm4 * atan2(ab, arg3) - fm5 * atan2(ab, arg4) + fm6 * atan2(ab, r0h);
                t += sign * (tlog + tatan);
            }
        }
        tfa[k] = magn * cm * t2nt * t;
    }
}

