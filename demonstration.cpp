#include "Matrix_Library.h"

void html_mat(ofstream& h, const double m[][10], int r, int c, string t, bool success) {
    h << "<h4>" << t << "</h4>";
    if (success) {
        h << "<table border='1' style='border-collapse:collapse; text-align:center;'>";
        for(int i = 0; i < r; i++) {
            h << "<tr>";
            for(int j = 0; j < c; j++) h << "<td style='padding:8px; width:45px;'>" << m[i][j] << "</td>";
            h << "</tr>";
        }
        h << "</table><br>";
    } else h << "<p style='color:red;'>Operation Impossible</p><br>";
}

void html_vec(ofstream& h, const double v[], int s, string t, bool success) {
    h << "<h4>" << t << "</h4>";
    if (success) {
        h << "<p style='background:#f9f9f9; padding:10px; display:inline-block;'>[ ";
        for(int i = 0; i < s; i++) h << v[i] << (i == s - 1 ? "" : " , ");
        h << " ]</p><br>";
    } else h << "<p style='color:red;'>Dimension Error</p><br>";
}

int main() {
    double mA[10][10], mB[10][10], mR[10][10], v1[10], v2[10], vR[10];
    int rA=3, cA=3, rB=2, cB=2, sV=3; double k=2.5;

    // Initialization
    mA[0][0]=2; mA[0][1]=1; mA[0][2]=0; mA[1][0]=1; mA[1][1]=2; mA[1][2]=1; mA[2][0]=0; mA[2][1]=1; mA[2][2]=2;
    mB[0][0]=1; mB[0][1]=0; mB[0][2]=1; mB[1][0]=0; mB[1][1]=1; mB[1][2]=0; mB[2][0]=1; mB[2][1]=0; mB[2][2]=1;
    v1[0]=1; v1[1]=0; v1[2]=2; v2[0]=3; v2[1]=1; v2[2]=4;

    ofstream out("report_sample.html");
    out << "<html><body style='font-family:serif; padding:40px;'><h1>Matrix & Vector Analysis</h1><hr>";

    // Step 1: Inputs
    out << "<h2>1. Input Data</h2>";
    html_mat(out, mA, rA, cA, "A =", true);
    html_mat(out, mB, rB, cB, "B =", true);
    html_vec(out, v1, sV, "v<sub>1</sub> =", true);
    html_vec(out, v2, sV, "v<sub>2</sub> =", true);
    out << "<p>k = " << k << "</p><hr><h2>2. Calculations</h2>";

    // Step 2: 14 Operations with Symbols
    html_mat(out, mR, rA, cA, "1) A + B =", matrix_sum(mA, mB, mR, rA, cA, rB, cB));
    html_mat(out, mR, rA, cA, "2) A - B =", matrix_diff(mA, mB, mR, rA, cA, rB, cB));
    html_mat(out, mR, rA, cB, "3) A &times; B =", matrix_prod(mA, mB, mR, rA, cA, rB, cB));
    matrix_scale(mA, mR, rA, cA, k); html_mat(out, mR, rA, cA, "4) k &sdot; A =", true);
    matrix_flip(mA, mR, rA, cA); html_mat(out, mR, cA, rA, "5) A<sup>T</sup> =", true);
    out << "<h4>6) |A| = " << matrix_det_calc(mA, rA) << "</h4><br>";
    html_mat(out, mR, rA, rA, "7) A<sup>-1</sup> =", matrix_inv_calc(mA, mR, rA));

    html_vec(out, vR, sV, "8) v<sub>1</sub> + v<sub>2</sub> =", vector_sum(v1, v2, vR, sV, sV));
    html_vec(out, vR, sV, "9) v<sub>1</sub> - v<sub>2</sub> =", vector_diff(v1, v2, vR, sV, sV));
    vector_scale(v1, vR, sV, k); html_vec(out, vR, sV, "10) k &sdot; v<sub>1</sub> =", true);
    out << "<h4>11) v<sub>1</sub> &sdot; v<sub>2</sub> = " << vector_dot_prod(v1, v2, sV, sV) << "</h4><br>";


    html_vec(out, vR, 3, "12) v<sub>1</sub> &times; v<sub>2</sub> =", vector_cross_prod(v1, v2, vR, sV, sV));
    out << "<h4>13) v<sub>1</sub> = " << vector_norm(v1, sV) << "</h4><br>";
    if(vector_unit_vec(v1, vR, sV)) html_vec(out, vR, sV, "14) v&#770;<sub>1</sub> =", true);

    out << "</body></html>";
    out.close();
    cout << "Final Report generated as report.html" << endl;
    return 0;
}
