#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// Data Structures
struct Matrix {
    double data[10][10];
    int rows, cols;
};

struct Vector {
    double comp[10];
    int size;
};

// --- Matrix Functions (7 Items) ---
Matrix addM(Matrix A, Matrix B, string &err);
Matrix subM(Matrix A, Matrix B, string &err);
Matrix multiplyM(Matrix A, Matrix B, string &err);
Matrix scalarM(Matrix A, double k);
Matrix transposeM(Matrix A);
double determinantM(Matrix A, int n, string &err);
Matrix inverseM(Matrix A, string &err);

// --- Vector Functions (7 Items) ---
Vector addV(Vector v1, Vector v2, string &err);
Vector subV(Vector v1, Vector v2, string &err);
Vector scalarV(Vector v, double k);
double dotV(Vector v1, Vector v2, string &err);
Vector crossV(Vector v1, Vector v2, string &err);
double magnitudeV(Vector v);
Vector normalizeV(Vector v, string &err);

// --- HTML Report Helpers ---
void startHTML(ofstream &f);
void writeMatrixHTML(ofstream &f, Matrix M, string title, string err = "");
void writeVectorHTML(ofstream &f, Vector v, string title, string err = "");
void writeResultHTML(ofstream &f, string label, double val, string err = "");
void endHTML(ofstream &f);

#endif
