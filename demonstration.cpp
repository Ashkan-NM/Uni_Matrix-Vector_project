#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

#include "matrix_library.h"

int main() {
    ofstream report("report_sample.html");
    if (!report) {
        cout << "Error creating file!" << endl;
        return 1;
    }

    startHTML(report);
    string err = "";

    // 1. Setup Input Data
    Matrix A; A.rows=2; A.cols=2; A.data[0][0]=1; A.data[0][1]=2; A.data[1][0]=3; A.data[1][1]=4;
    Matrix B; B.rows=2; B.cols=2; B.data[0][0]=5; B.data[0][1]=6; B.data[1][0]=7; B.data[1][1]=8;

    Vector v1; v1.size=3; v1.comp[0]=1; v1.comp[1]=2; v1.comp[2]=3;
    Vector v2; v2.size=3; v2.comp[0]=4; v2.comp[1]=5; v2.comp[2]=6;

    // --- بخش نمایش ورودی‌ها (Input Data Section) ---
    report << "<header style='background:#555;'><h2>Step 1: Input Data</h2></header>";
    writeMatrixHTML(report, A, "Input Matrix A");
    writeMatrixHTML(report, B, "Input Matrix B");
    writeVectorHTML(report, v1, "Input Vector v1");
    writeVectorHTML(report, v2, "Input Vector v2");
    report << "<hr>";

    // --- بخش عملیات ماتریسی (Matrix Operations) ---
    report << "<header><h2>Step 2: Matrix Operations (7 Items)</h2></header>";

    err=""; writeMatrixHTML(report, addM(A, B, err), "1. Addition (A+B)", err);
    err=""; writeMatrixHTML(report, multiplyM(A, B, err), "2. Multiplication (A*B)", err);

    // نکته: برای ضرب اسکالر، یک کپی از A می‌سازیم تا خود A برای مراحل بعد خراب نشود
    Matrix A_copy = A;
    writeMatrixHTML(report, scalarM(A_copy, 10), "3. Scalar Mult (A*10)");

    err=""; writeMatrixHTML(report, subM(A, B, err), "4. Subtraction (A-B)", err);
    writeMatrixHTML(report, transposeM(A), "5. Transpose of A");

    err=""; writeResultHTML(report, "6. Determinant of A", determinantM(A, A.rows, err), err);
    err=""; writeMatrixHTML(report, inverseM(A, err), "7. Inverse of A", err);

    // --- بخش عملیات برداری (Vector Operations) ---
    report << "<hr><header><h2>Step 3: Vector Operations (7 Items)</h2></header>";

    err=""; writeVectorHTML(report, addV(v1, v2, err), "1. Vector Addition", err);
    err=""; writeVectorHTML(report, subV(v1, v2, err), "2. Vector Subtraction", err);

    Vector v1_copy = v1;
    writeVectorHTML(report, scalarV(v1_copy, 5), "3. Scalar Mult (v1*5)");

    err=""; writeResultHTML(report, "4. Dot Product", dotV(v1, v2, err), err);
    err=""; writeVectorHTML(report, crossV(v1, v2, err), "5. Cross Product (v1 x v2)", err);
    writeResultHTML(report, "6. Magnitude of v1", magnitudeV(v1));

    err=""; writeVectorHTML(report, normalizeV(v1, err), "7. Normalization (Unit Vector)", err);

    endHTML(report);
    report.close();

    cout << "========================================" << endl;
    cout << "  Success! Full Report Generated." << endl;
    cout << "  Check 'report_sample.html' now." << endl;
    cout << "========================================" << endl;

    return 0;
}
