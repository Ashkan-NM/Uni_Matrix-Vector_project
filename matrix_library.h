#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

// Matrix Operations
bool matrix_sum(const double a[][10], const double b[][10], double res[][10], int r1, int c1, int r2, int c2);
bool matrix_diff(const double a[][10], const double b[][10], double res[][10], int r1, int c1, int r2, int c2);
bool matrix_prod(const double a[][10], const double b[][10], double res[][10], int r1, int c1, int r2, int c2);
void matrix_scale(const double a[][10], double res[][10], int r, int c, double k);
void matrix_flip(const double a[][10], double res[][10], int r, int c);
double matrix_det_calc(const double a[][10], int n);
bool matrix_inv_calc(const double a[][10], double res[][10], int n);

// Vector Operations
bool vector_sum(const double v1[], const double v2[], double res[], int s1, int s2);
bool vector_diff(const double v1[], const double v2[], double res[], int s1, int s2);
void vector_scale(const double v[], double res[], int s, double k);
double vector_dot_prod(const double v1[], const double v2[], int s1, int s2);
bool vector_cross_prod(const double v1[], const double v2[], double res[], int s1, int s2);
double vector_norm(const double v[], int s);
bool vector_unit_vec(const double v[], double res[], int s);

#endif
