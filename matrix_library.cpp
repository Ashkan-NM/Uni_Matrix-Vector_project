#include "matrix_library.h"

// --- MATRIX LOGIC ---
Matrix addM(Matrix A, Matrix B, string &err) {
    if (A.rows != B.rows || A.cols != B.cols) { err = "Error: Dimension mismatch for addition!"; return A; }
    Matrix res = A;
    for(int i=0; i<A.rows; i++) for(int j=0; j<A.cols; j++) res.data[i][j] += B.data[i][j];
    return res;
}
Matrix subM(Matrix A, Matrix B, string &err) {
    if (A.rows != B.rows || A.cols != B.cols) { err = "Error: Dimension mismatch for subtraction!"; return A; }
    Matrix res = A;
    for(int i=0; i<A.rows; i++) for(int j=0; j<A.cols; j++) res.data[i][j] -= B.data[i][j];
    return res;
}
Matrix multiplyM(Matrix A, Matrix B, string &err) {
    if (A.cols != B.rows) { err = "Error: Invalid dimensions for multiplication!"; return A; }
    Matrix res; res.rows = A.rows; res.cols = B.cols;
    for(int i=0; i<A.rows; i++) {
        for(int j=0; j<B.cols; j++) {
            res.data[i][j] = 0;
            for(int k=0; k<A.cols; k++) res.data[i][j] += A.data[i][k] * B.data[k][j];
        }
    }
    return res;
}
Matrix scalarM(Matrix A, double k) {
    for(int i=0; i<A.rows; i++) for(int j=0; j<A.cols; j++) A.data[i][j] *= k;
    return A;
}
Matrix transposeM(Matrix A) {
    Matrix res; res.rows = A.cols; res.cols = A.rows;
    for(int i=0; i<A.rows; i++) for(int j=0; j<A.cols; j++) res.data[j][i] = A.data[i][j];
    return res;
}
double determinantM(Matrix A, int n, string &err) {
    if (A.rows != A.cols) { err = "Error: Determinant requires a square matrix!"; return 0; }
    if (n == 1) return A.data[0][0];
    if (n == 2) return (A.data[0][0]*A.data[1][1]) - (A.data[0][1]*A.data[1][0]);
    double det = 0; Matrix sub;
    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;
                sub.data[subi][subj] = A.data[i][j];
                subj++;
            }
            subi++;
        }
        det += pow(-1, x) * A.data[0][x] * determinantM(sub, n-1, err);
    }
    return det;
}
Matrix inverseM(Matrix A, string &err) {
    double det = determinantM(A, A.rows, err);
    if (abs(det) < 0.000001) { err = "Error: Singular matrix (Det=0), no inverse!"; return A; }
    Matrix res; res.rows = 2; res.cols = 2; // For demonstration 2x2
    res.data[0][0] = A.data[1][1]/det; res.data[0][1] = -A.data[0][1]/det;
    res.data[1][0] = -A.data[1][0]/det; res.data[1][1] = A.data[0][0]/det;
    return res;
}

// --- VECTOR LOGIC ---
Vector addV(Vector v1, Vector v2, string &err) {
    if(v1.size != v2.size) { err = "Error: Vector size mismatch!"; return v1; }
    for(int i=0; i<v1.size; i++) v1.comp[i] += v2.comp[i];
    return v1;
}
Vector subV(Vector v1, Vector v2, string &err) {
    if(v1.size != v2.size) { err = "Error: Vector size mismatch!"; return v1; }
    for(int i=0; i<v1.size; i++) v1.comp[i] -= v2.comp[i];
    return v1;
}
Vector scalarV(Vector v, double k) {
    for(int i=0; i<v.size; i++) v.comp[i] *= k;
    return v;
}
double dotV(Vector v1, Vector v2, string &err) {
    if(v1.size != v2.size) { err = "Error: Vector size mismatch!"; return 0; }
    double d = 0; for(int i=0; i<v1.size; i++) d += v1.comp[i]*v2.comp[i];
    return d;
}
Vector crossV(Vector v1, Vector v2, string &err) {
    if(v1.size != 3 || v2.size != 3) { err = "Error: Cross product only for 3D vectors!"; return v1; }
    Vector r; r.size = 3;
    r.comp[0] = v1.comp[1]*v2.comp[2] - v1.comp[2]*v2.comp[1];
    r.comp[1] = v1.comp[2]*v2.comp[0] - v1.comp[0]*v2.comp[2];
    r.comp[2] = v1.comp[0]*v2.comp[1] - v1.comp[1]*v2.comp[0];
    return r;
}
double magnitudeV(Vector v) {
    double s = 0; for(int i=0; i<v.size; i++) s += v.comp[i]*v.comp[i];
    return sqrt(s);
}
Vector normalizeV(Vector v, string &err) {
    double m = magnitudeV(v);
    if(m < 0.000001) { err = "Error: Zero vector normalization!"; return v; }
    return scalarV(v, 1.0/m);
}

// --- HTML HELPERS ---
void startHTML(ofstream &f) {
    f << "<!DOCTYPE html><html><head><meta charset='UTF-8'><style>"
      << "body{font-family:Arial; text-align:center; background:#f4f4f4; color:#333;}"
      << "header{background:#2c3e50; color:white; padding:20px; margin-bottom:20px;}"
      << "section{background:white; width:70%; margin:20px auto; padding:15px; border-radius:10px; box-shadow:0 4px 8px rgba(0,0,0,0.1);}"
      << "table{margin:10px auto; border-collapse:collapse;} td{padding:12px; border:1px solid #ccc; background:#fafafa;}"
      << ".error{color:red; font-weight:bold;}</style></head><body>"
      << "<header><h1>Engineering Math Report</h1></header>";
}
void writeMatrixHTML(ofstream &f, Matrix M, string title, string err) {
    f << "<section><h3>" << title << " (" << M.rows << "x" << M.cols << ")</h3>";
    if(!err.empty()) f << "<p class='error'>" << err << "</p>";
    else {
        f << "<table>";
        for(int i=0; i<M.rows; i++) {
            f << "<tr>";
            for(int j=0; j<M.cols; j++) f << "<td>" << M.data[i][j] << "</td>";
            f << "</tr>";
        }
        f << "</table>";
    }
    f << "</section>";
}
void writeVectorHTML(ofstream &f, Vector v, string title, string err) {
    f << "<section><h3>" << title << "</h3>";
    if(!err.empty()) f << "<p class='error'>" << err << "</p>";
    else {
        f << "<p>[ ";
        for(int i=0; i<v.size; i++) f << v.comp[i] << (i==v.size-1 ? "" : ", ");
        f << " ]</p>";
    }
    f << "</section>";
}
void writeResultHTML(ofstream &f, string label, double val, string err) {
    f << "<section><h3>" << label << "</h3>";
    if(!err.empty()) f << "<p class='error'>" << err << "</p>";
    else f << "<p><b>Result:</b> " << val << "</p>";
    f << "</section>";
}
void endHTML(ofstream &f) { f << "<footer>Math Project 2026</footer></body></html>"; }
