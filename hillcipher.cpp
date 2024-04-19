#include <iostream>
using namespace std;

#define ROW 3
#define COL 3

bool flag = false;
int newinverse; // Global variable for inverse matrix

// Struct to store three integers
struct Triplet {
    int x, y, z;
};

// Function prototypes
void importMatrix(int mat[ROW][COL]);
void importPlaintext(string& plaintext, int mat[ROW][COL]);
Triplet doEncryption(char first, char second, char third, int mat[ROW][COL]);

void computeDeterminant(int mat[ROW][COL], int &determinant);
void transposeMatrix(int mat[ROW][COL], int transpose[ROW][COL]);
void performOperation(int transpose[ROW][COL], int newmat[ROW][COL], int adj[ROW][COL]);
void findInverse(int adj[ROW][COL], int determinant, int inversemat[ROW][COL]);

void importCiphertext(string& ciphertext, int mat[ROW][COL], int inversemat[ROW][COL]);
Triplet doDecryption(char first, char second, char third, int inversemat[ROW][COL]);

// Function to import matrix from user
void importMatrix(int mat[ROW][COL]) {
    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cin >> mat[i][j];
        }
    }
}

// Function to import plaintext and prepare it for encryption
void importPlaintext(string& plaintext, int mat[ROW][COL]) {
    cout << "Enter the plaintext: ";
    cin >> plaintext;

    string newtext;
    for (int i = 0; i < plaintext.size(); i++) {
        newtext += plaintext[i];
    }

    if (newtext.size() % 3 != 0) {
        newtext += 'z'; // Adding 'z' at the end if the size is not divisible by 3
    }

    plaintext = newtext;

    // Now partitioning the plaintext into three equal parts
    for (int i = 1; i <= plaintext.size(); i++) {
        for (int counter = 1; counter <= plaintext.size() / 3; counter++) {
            if (i == counter * 3) {
                char first = plaintext[i - 3];
                char second = plaintext[i - 2];
                char third = plaintext[i - 1];

                Triplet result = doEncryption(first, second, third,mat);
                char ch1, ch2, ch3; 
                if (result.x >= 0 && result.x <= 25) {
                    ch1 = 'A' + result.x;
                   
                }
                
                if (result.y >= 0 && result.y <= 25) {
                    ch2 = 'A' + result.y;
                   
                }
                
                if (result.z >= 0 && result.z <= 25) {
                    ch3 = 'A' + result.z;
                    
                }
                
                cout<<first<<second<<third<<" = "<<ch1<<" "<<ch2<<" "<<ch3<<endl; 
            }
        }
    }
}

// Function to perform encryption on a triplet of characters
Triplet doEncryption(char first, char second, char third, int mat[ROW][COL]) {
    Triplet result;

    if (first >= 'a' && first <= 'z') {
        result.x = int(first) - 97;
    } else if (first >= 'A' && first <= 'Z') {
        result.x = int(first) - 65;
    } else {
        cout << "Not a letter!";
    }

    if (second >= 'a' && second <= 'z') {
        result.y = int(second) - 97;
    } else if (second >= 'A' && second <= 'Z') {
        result.y = int(second) - 65;
    } else {
        cout << "Not a letter!";
    }

    if (third >= 'a' && third <= 'z') {
        result.z = int(third) - 97;
    } else if (third >= 'A' && third <= 'Z') {
        result.z = int(third) - 65;
    } else {
        cout << "Not a letter!";
    }

     int newX = result.x * mat[0][0] + result.y * mat[1][0] + result.z * mat[2][0];
    int newY = result.x * mat[0][1] + result.y * mat[1][1] + result.z * mat[2][1];
    int newZ = result.x * mat[0][2] + result.y * mat[1][2] + result.z * mat[2][2];

    // somewhere this type of matrix multiplication is also done
    // int newX = result.x * mat[0][0] + result.y * mat[0][1] + result.z * mat[0][2];
    // int newY = result.x * mat[1][0] + result.y * mat[1][1] + result.z * mat[1][2];
    // int newZ = result.x * mat[2][0] + result.y * mat[2][1] + result.z * mat[2][2];
    
    result.x = (newX) % 26;
    result.y = (newY) % 26;
    result.z = (newZ) % 26;
    
    return result;
}

// Function to compute determinant of a 3x3 matrix
void computeDeterminant(int mat[ROW][COL], int &determinant) {
    determinant = (mat[0][0] * ((mat[1][1] * mat[2][2]) - (mat[1][2] * mat[2][1]))) -
                  (mat[0][1] * ((mat[1][0] * mat[2][2]) - (mat[1][2] * mat[2][0]))) +
                  (mat[0][2] * ((mat[1][0] * mat[2][1]) - (mat[1][1] * mat[2][0])));
    
    int newDeterminant = determinant % 26; 
    if(newDeterminant < 0 ) newDeterminant += 26; 
    determinant = newDeterminant; 
    cout << "Determinant: " << determinant << endl;
}

// Function to transpose a matrix
void transposeMatrix(int mat[ROW][COL], int transpose[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            transpose[j][i] = mat[i][j];
        }
    }
}

// Function to find adjoint of a matrix
void performOperation(int transpose[ROW][COL], int newmat[ROW][COL], int adj[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            newmat[i][j] = (transpose[(i + 1) % 3][(j + 1) % 3] * transpose[(i + 2) % 3][(j + 2) % 3])
                           - (transpose[(i + 1) % 3][(j + 2) % 3] * transpose[(i + 2) % 3][(j + 1) % 3]);
            if ((i + j) % 2 != 0) {
                newmat[i][j] = -newmat[i][j];
            }
            cout << newmat[i][j] << " ";
        }
        cout << endl;
    }

    // Compute adjoint
    cout << "The adjoint is:" << endl;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            adj[i][j] = newmat[i][j];
            if ((i + j) % 2 != 0) {
                adj[i][j] = -adj[i][j];
            }
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to find inverse of a matrix
void findInverse(int adj[ROW][COL], int determinant, int inversemat[ROW][COL]) {
    cout << "Inverse matrix:" << endl;

    // Compute modular inverse
    for (int n = 0; n < 55; n++) {
        if ((determinant * n) % 26 == 1) {
            newinverse = n;
            flag = true;
            break;
        }
    }

    if (!flag) {
        cout << "Inverse does not exist!" << endl;
        return;
    }

    // Compute inverse matrix
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            inversemat[i][j] = (adj[i][j] * newinverse) % 26;
            cout << inversemat[i][j] << " ";
        }
        cout << endl;
    }
}

void importCiphertext(string& ciphertext, int mat[ROW][COL], int inversemat[ROW][COL]) {
    cout << "Enter the Ciphertext: ";
    cin >> ciphertext;

    string newtext;
    for (int i = 0; i < ciphertext.size(); i++) {
        newtext += ciphertext[i];
    }

    if (newtext.size() % 3 != 0) {
        newtext += 'z';
    }

    ciphertext = newtext;

    for (int i = 1; i <= ciphertext.size(); i++) {
        for (int counter = 1; counter <= ciphertext.size() / 3; counter++) {
            if (i == counter * 3) {
                char first = ciphertext[i - 3];
                char second = ciphertext[i - 2];
                char third = ciphertext[i - 1];

                Triplet result = doDecryption(first, second, third, inversemat);
                char ch1, ch2, ch3; 
                if (result.x >= 0 && result.x <= 25) {
                    ch1 = 'A' + result.x;
                }
                
                if (result.y >= 0 && result.y <= 25) {
                    ch2 = 'A' + result.y;
                }
                
                if (result.z >= 0 && result.z <= 25) {
                    ch3 = 'A' + result.z;
                }
                
               cout << first << second << third << " = " << ch1 << " " << ch2 << " " << ch3 << endl; 
            }
        }
    }
}

// Function to perform decryption on a triplet of characters
Triplet doDecryption(char first, char second, char third, int inversemat[ROW][COL]) {
    Triplet result;

    if (first >= 'a' && first <= 'z') {
        result.x = int(first) - 97;
    } else if (first >= 'A' && first <= 'Z') {
        result.x = int(first) - 65;
    } else {
        cout << "Not a letter!";
    }

    if (second >= 'a' && second <= 'z') {
        result.y = int(second) - 97;
    } else if (second >= 'A' && second <= 'Z') {
        result.y = int(second) - 65;
    } else {
        cout << "Not a letter!";
    }

    if (third >= 'a' && third <= 'z') {
        result.z = int(third) - 97;
    } else if (third >= 'A' && third <= 'Z') {
        result.z = int(third) - 65;
    } else {
        cout << "Not a letter!";
    }

    // Perform matrix multiplication for decryption
    int decryptedX = (result.x * inversemat[0][0] + result.y * inversemat[1][0] + result.z * inversemat[2][0]) % 26;
    int decryptedY = (result.x * inversemat[0][1] + result.y * inversemat[1][1] + result.z * inversemat[2][1]) % 26;
    int decryptedZ = (result.x * inversemat[0][2] + result.y * inversemat[1][2] + result.z * inversemat[2][2]) % 26;

    // somewhere this type of matrix multiplication is done 
    // int decryptedX = (result.x * inversemat[0][0] + result.y * inversemat[0][1] + result.z * inversemat[0][2]) % 26;
    // int decryptedY = (result.x * inversemat[1][0] + result.y * inversemat[1][1] + result.z * inversemat[1][2]) % 26;
    // int decryptedZ = (result.x * inversemat[2][0] + result.y * inversemat[2][1] + result.z * inversemat[2][2]) % 26;

    // Ensure decrypted values are positive
    decryptedX = (decryptedX + 26) % 26;
    decryptedY = (decryptedY + 26) % 26;
    decryptedZ = (decryptedZ + 26) % 26;

    result.x = decryptedX;
    result.y = decryptedY;
    result.z = decryptedZ;

    cout<<result.x<<" "<<result.y<<" "<<result.z<<endl; 
    return result;
}

int main() {
    int mode, mat[ROW][COL];
    string plaintext, ciphertext; 

    cout << "Choose mode:" << endl;
    cout << "1. Encryption" << endl;
    cout << "2. Decryption" << endl;
    cin >> mode; 

    switch (mode) {
    case 1:
        importMatrix(mat);
        importPlaintext(plaintext, mat);
        break;

    case 2:
        int transpose[ROW][COL], newmat[ROW][COL], adj[ROW][COL];
        int determinant;
        int inversemat[ROW][COL];
        importMatrix(mat);
        computeDeterminant(mat, determinant); 
        if (determinant == 0) {
            cout << "The matrix is not invertible!" << endl;
            return 1; // Exit the program
        }
        transposeMatrix(mat, transpose);
        performOperation(transpose, newmat, adj);
        findInverse(adj, determinant, inversemat);
        importCiphertext(ciphertext, mat, inversemat);
        break;

    default:
        cout << "Invalid mode!" << endl;
        break;
    }

    return 0;
}
