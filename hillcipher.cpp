#include<iostream>
#include<math.h>
using namespace std;

void computeDeterminant(int mat[3][3], double & determinant){
    determinant = (mat[0][0] * ((mat[1][1] * mat[2][2]) - (mat[1][2] * mat[2][1]))) -
                  (mat[0][1] * ((mat[1][0] * mat[2][2]) - (mat[1][2] * mat[2][0]))) +
                  (mat[0][2] * ((mat[1][0] * mat[2][1]) - (mat[1][1] * mat[2][0])));
    cout << "Determinant: " << determinant << endl;
}

void transposeMatrix(int mat[3][3], int transpose[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            transpose[j][i] = mat[i][j];
        }
    }
}

void performOperation(int transpose[3][3], int newmat[3][3], int adj[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            newmat[i][j] = (transpose[(i + 1) % 3][(j + 1) % 3] * transpose[(i + 2) % 3][(j + 2) % 3])
                           - (transpose[(i + 1) % 3][(j + 2) % 3] * transpose[(i + 2) % 3][(j + 1) % 3]);

            if ((i + j) % 2 != 0) {
                newmat[i][j] = (-1) * newmat[i][j];
            }
           // cout << newmat[i][j] << " ";
        }
       // cout << endl;
    }
   // cout << endl;

    // Finding adjoint now 
    cout<<"The adjoint is: "<<endl; 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adj[i][j] = newmat[i][j];
            if ((i + j) % 2 != 0) adj[i][j] = (-1) * adj[i][j];
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

void findinverse(int adj[3][3], double determinant, double inversemat[3][3]) {
    cout << endl << "Inverse matrix:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inversemat[i][j] = adj[i][j] / determinant;
            cout << inversemat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int mat[3][3];
    int transpose[3][3], newmat[3][3], adj[3][3];
    double determinant;
    double inversemat[3][3];
    
    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> mat[i][j];
        }
    }
    
    computeDeterminant(mat, determinant); 
    transposeMatrix(mat, transpose);
    performOperation(transpose, newmat, adj);
    findinverse(adj, determinant, inversemat);

    return 0;
}
