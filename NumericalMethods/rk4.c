#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_eq 3   // Number of equations

double f(double x, double y[], int i) {
    if (i == 0) {
        return y[1];  // First equation
    } else if (i == 1) {
        return -y[0]; // Second equation
    } else {
        return 2 * y[2]; // Third equation
    }
}

void RungeKutta(double x0, double y0[], double h, int n) {
    double k1[N_eq], k2[N_eq], k3[N_eq], k4[N_eq];
    double y_temp[N_eq];

    double x = x0;
    double y[N_eq];
    for (int i = 0; i < N_eq; i++) {
        y[i] = y0[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < N_eq; j++) {
            k1[j] = h * f(x, y, j);
            y_temp[j] = y[j] + 0.5 * k1[j];
        }

        for (int j = 0; j < N_eq; j++) {
            k2[j] = h * f(x + 0.5 * h, y_temp, j);
            y_temp[j] = y[j] + 0.5 * k2[j];
        }

        for (int j = 0; j < N_eq; j++) {
            k3[j] = h * f(x + 0.5 * h, y_temp, j);
            y_temp[j] = y[j] + k3[j];
        }

        for (int j = 0; j < N_eq; j++) {
            k4[j] = h * f(x + h, y_temp, j);
            y[j] += (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]) / 6.0;
        }

        x += h;

        printf("%lf ", x);
        for (int j = 0; j < N_eq; j++) {
            printf("%lf ", y[j]);
        }
        printf("\n");
    }
}

int main() {
    double x0 = 0.0;
    double y0[N_eq] = {1.0, 0.0, -1.0}; // Initial conditions
    double h = 0.1;
    int n = 10;

    RungeKutta(x0, y0, h, n);

    return 0;
}
