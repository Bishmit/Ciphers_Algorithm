#include <iostream>
using namespace std;

#define ROW 2
#define COL 2

bool flag = false;
int newinverse;

// struct to store two integers
struct Pair {
    int x, y;
};

// fn prototypes
void importMatrix(int mat[ROW][COL]);
void importPlaintext(string& plaintext, int mat[ROW][COL]);
Pair doEncryption(char first, char second, int mat[ROW][COL]);

void computeDeterminant(int mat[ROW][COL], int &determinant);
void transposeMatrix(int mat[ROW][COL], int transpose[ROW][COL]);
void performOperation(int transpose[ROW][COL], int adj[ROW][COL]);
void findInverse(int adj[ROW][COL], int determinant, int inversemat[ROW][COL]);

void importCiphertext(string& ciphertext, int mat[ROW][COL], int inversemat[ROW][COL]);
Pair doDecryption(char first, char second, int inversemat[ROW][COL]);

// fn to import matrix from user
void importMatrix(int mat[ROW][COL]) {
    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cin >> mat[i][j];
        }
    }
}

// fn to import plaintext and prepare it for encryption
void importPlaintext(string& plaintext, int mat[ROW][COL]) {
    cout << "Enter the plaintext: ";
    cin >> plaintext;

    string newtext = plaintext;

    if (newtext.size() % 2 != 0) {
        newtext += 'z'; // Padding with 'z' if not divisible by 2
    }

    plaintext = newtext;

    // Partitioning the plaintext into pairs of characters
    for (int i = 1; i <= plaintext.size(); i += 2) {
        char first = plaintext[i - 1];
        char second = plaintext[i];

        Pair result = doEncryption(first, second, mat);
        char ch1 = 'A' + result.x;
        char ch2 = 'A' + result.y;

        cout << first << second << " = " << ch1 << " " << ch2 << endl;
    }
}

// fn to perform encryption on a pair of characters
Pair doEncryption(char first, char second, int mat[ROW][COL]) {
    Pair result;

    result.x = (first >= 'a') ? first - 'a' : first - 'A';
    result.y = (second >= 'a') ? second - 'a' : second - 'A';

    int newX = (result.x * mat[0][0] + result.y * mat[1][0]) % 26;
    int newY = (result.x * mat[0][1] + result.y * mat[1][1]) % 26;

    result.x = (newX + 26) % 26;
    result.y = (newY + 26) % 26;

    return result;
}

// fn to compute determinant of a 2x2 matrix
void computeDeterminant(int mat[ROW][COL], int &determinant) {
    determinant = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    determinant = (determinant % 26 + 26) % 26;
    cout << "Determinant: " << determinant << endl;
}

// fn to transpose a matrix
void transposeMatrix(int mat[ROW][COL], int transpose[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            transpose[j][i] = mat[i][j];
        }
    }
}

// fn to find adjoint of a matrix
void performOperation(int transpose[ROW][COL], int adj[ROW][COL]) {
    adj[0][0] = transpose[1][1];
    adj[0][1] = -transpose[1][0];
    adj[1][0] = -transpose[0][1];
    adj[1][1] = transpose[0][0];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            adj[i][j] = (adj[i][j] % 26 + 26) % 26;
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

// fn to find inverse of a matrix
void findInverse(int adj[ROW][COL], int determinant, int inversemat[ROW][COL]) {
    cout << "Inverse matrix:" << endl;

    // Compute modular inverse of determinant
    for (int n = 0; n < 26; n++) {
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

    string newtext = ciphertext;

    if (newtext.size() % 2 != 0) {
        newtext += 'z'; // Padding with 'z' if not divisible by 2
    }

    ciphertext = newtext;

    for (int i = 1; i <= ciphertext.size(); i += 2) {
        char first = ciphertext[i - 1];
        char second = ciphertext[i];

        Pair result = doDecryption(first, second, inversemat);
        char ch1 = 'A' + result.x;
        char ch2 = 'A' + result.y;

        cout << first << second << " = " << ch1 << " " << ch2 << endl;
    }
}

// fn to perform decryption on a pair of characters
Pair doDecryption(char first, char second, int inversemat[ROW][COL]) {
    Pair result;

    result.x = (first >= 'a') ? first - 'a' : first - 'A';
    result.y = (second >= 'a') ? second - 'a' : second - 'A';

    int newX = (result.x * inversemat[0][0] + result.y * inversemat[1][0]) % 26;
    int newY = (result.x * inversemat[0][1] + result.y * inversemat[1][1]) % 26;

    result.x = (newX + 26) % 26;
    result.y = (newY + 26) % 26;

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
        int transpose[ROW][COL], adj[ROW][COL];
        int determinant;
        int inversemat[ROW][COL];
        importMatrix(mat);
        computeDeterminant(mat, determinant);
        if (determinant == 0) {
            cout << "The matrix is not invertible!" << endl;
            return 1;
        }
        transposeMatrix(mat, transpose);
        performOperation(transpose, adj);
        findInverse(adj, determinant, inversemat);
        importCiphertext(ciphertext, mat, inversemat);
        break;

    default:
        cout << "Invalid mode!" << endl;
        break;
    }

    return 0;
}
