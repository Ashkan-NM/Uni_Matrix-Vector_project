#include "Matrix_Library.h"

bool matrix_sum(const double a[][10], const double b[][10], double res[][10], int r1, int c1, int r2, int c2) {
    if (r1 != r2 || c1 != c2) return false;
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++) res[i][j] = a[i][j] + b[i][j];
    return true;
}

bool matrix_diff(const double a[][10], const double b[][10], double res[][10], int r1, int c1, int r2, int c2) {
    if (r1 != r2 || c1 != c2) return false;
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++) res[i][j] = a[i][j] - b[i][j];
    return true;
}

bool matrix_prod(const double a[][10], const double b[][10], double res[][10], int r1, int c1, int r2, int c2) {
    if (c1 != r2) return false;
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++) res[i][j] += a[i][k] * b[k][j];
        }
    }
    return true;
}

void matrix_scale(const double a[][10], double res[][10], int r, int c, double k) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) res[i][j] = a[i][j] * k;
}

void matrix_flip(const double a[][10], double res[][10], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) res[j][i] = a[i][j];
}

double matrix_det_calc(const double a[][10], int n) {
    if (n == 1) return a[0][0];
    if (n == 2) return (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
    double d = 0;
    double sub[10][10];
    for (int x = 0; x < n; x++) {
        int si = 0;
        for (int i = 1; i < n; i++) {
            int sj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;
                sub[si][sj] = a[i][j]; sj++;
            }
            si++;
        }
        d += ((x % 2 == 0) ? 1 : -1) * a[0][x] * matrix_det_calc(sub, n - 1);
    }
    return d;
}

bool matrix_inv_calc(const double a[][10], double res[][10], int n) {
    double det = matrix_det_calc(a, n);
    if (abs(det) < 1e-10) return false;
    double temp[10][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int r = 0;
            for (int x = 0; x < n; x++) {
                if (x == i) continue;
                int c = 0;
                for (int y = 0; y < n; y++) {
                    if (y == j) continue;
                    temp[r][c] = a[x][y]; c++;
                }
                r++;
            }
            res[j][i] = (((i + j) % 2 == 0) ? 1 : -1) * matrix_det_calc(temp, n - 1) / det;
        }
    }
    return true;
}

bool vector_sum(const double v1[], const double v2[], double res[], int s1, int s2) {
    if (s1 != s2) return false;
    for (int i = 0; i < s1; i++) res[i] = v1[i] + v2[i];
    return true;
}

bool vector_diff(const double v1[], const double v2[], double res[], int s1, int s2) {
    if (s1 != s2) return false;
    for (int i = 0; i < s1; i++) res[i] = v1[i] - v2[i];
    return true;
}

void vector_scale(const double v[], double res[], int s, double k) {
    for (int i = 0; i < s; i++) res[i] = v[i] * k;
}

double vector_dot_prod(const double v1[], const double v2[], int s1, int s2) {
    if (s1 != s2) return 0;
    double p = 0;
    for (int i = 0; i < s1; i++) p += v1[i] * v2[i];
    return p;
}

bool vector_cross_prod(const double v1[], const double v2[], double res[], int s1, int s2) {
    if (s1 != 3 || s2 != 3) return false;
    res[0] = v1[1] * v2[2] - v1[2] * v2[1];
    res[1] = v1[2] * v2[0] - v1[0] * v2[2];
    res[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return true;
}

double vector_norm(const double v[], int s) {
    double q = 0;
    for (int i = 0; i < s; i++) q += v[i] * v[i];
    return sqrt(q);
}

bool vector_unit_vec(const double v[], double res[], int s) {
    double m = vector_norm(v, s);
    if (m < 1e-10) return false;
    for (int i = 0; i < s; i++) res[i] = v[i] / m;
    return true;
}
