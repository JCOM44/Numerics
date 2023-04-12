#include "rk4.h"

int main() {
    double x0 = 0.0;                                // Initial x
    double y0[N_eq] = {1.0, 0.0, -1.0};             // Initial conditions
    double h = 0.2;                                 // Initial stepsize
    double z;                                       // Value where adaptive stepsize is stored
    double tol = 1.01e-4;                            // Tolerance value, minimum error, usually 10e-4 to 10e-6
    int n = 10;                                     // Number of iterations

    z = RungeKutta_step(x0,y0,h,tol);
    printf("%lf \n",z);
    RungeKutta(x0, y0, z, n);

    return 0;
}
