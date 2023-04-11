#include "rk4.h"

int main() {
    double x0 = 0.0;
    double y0[N_eq] = {1.0, 0.0, -1.0}; // Initial conditions
    double h = 0.1;
    int n = 10;

    RungeKutta(x0, y0, h, n);

    return 0;
}
