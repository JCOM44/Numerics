#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_eq 3   // Number of equations

double f(double x, double y[], int i) {
    if (i == 0) {
        return y[0]*y[0];  // First equation
    } else if (i == 1) {
        return -y[1]+y[0]; // Second equation
    } else {
        return 1-2 * y[2]; // Third equation
    }
}

// RungeKutta function: receives initial x, initial y_i, step size and number of iterations
void RungeKutta(double x0, double y0[], double h, int n)
 {              
    double k1[N_eq], k2[N_eq], k3[N_eq], k4[N_eq];
    double y_temp[N_eq];

    double x = x0;
    double y[N_eq];
    for (int i = 0; i < N_eq; i++) {
        y[i] = y0[i];                       // Initialize y_i as y_i(x_0)
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



// ROUTINE TO IMPLEMENT ADAPTIVE STEPSIZE CONTROL
double RungeKutta_step(double x0, double y0[], double h, double tol)//, double yout[]) 
{
    double y1[N_eq], y2[N_eq]; // evaluate the solution at 2 points
    double k1[N_eq], k2[N_eq], k3[N_eq], k4[N_eq]; // intermediate slopes
    double err, h_opt; // local error and optimal step size
    double h_temp = h;

    // calculate k1
    for (int j = 0; j < N_eq; j++) {
        k1[j] = h * f(x0, y0, j);
        y1[j] = y0[j] + 0.5 * k1[j];
    }

    // calculate k2
    for (int j = 0; j < N_eq; j++) {
        k2[j] = h * f(x0 + 0.5 * h, y1, j);
        y1[j] = y0[j] + 0.5 * k2[j]; 
    }

    // calculate k3
    for (int j = 0; j < N_eq; j++) {
        k3[j] = h * f(x0 + 0.5 * h, y1, j);
        y2[j] = y0[j] + k3[j];
        y1[j] = y0[j] + 0.5 * k3[j];
    }

    // calculate k4 and update the solution
    for (int j = 0; j < N_eq; j++) {
        k4[j] = h * f(x0 + h, y2, j);
//        yout[j] = y0[j] + (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]) / 6.0;
    }

    // calculate local error and optimal step size
    err = fabs(y2[0]-y1[0])/15.0;
    for (int j = 1; j < N_eq; j++) {
        err = fmax(err, fabs(y2[j]-y1[j])/15.0);
    }

      // check if error is within tolerance
    if (err <= tol) {
        printf("optimal h: %.20lf \n",h_temp);
        return h_temp;
        // use current step size
    } else {
        h_opt = h * pow(tol/err, 0.25);
        printf("Error of %.20lf. Recalculating with h= %.20lf \n",err,h_opt);
        // recalculate solution with optimal step size
        h_opt = RungeKutta_step(x0, y0, h_opt, tol);
        return h_opt;
    }
}