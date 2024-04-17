#include <iostream>
using namespace std;

#define row 3
#define col 3

// Define a structure to store three integers
struct Triplet {
    int x;
    int y;
    int z;
};

// Function declarations
void importMatrix(int mat[row][col]);
void importPlaintext(string& plaintext,int mat[row][col]);
Triplet doEncryption(char first, char second, char third, int mat[col][row]);

void importMatrix(int mat[row][col]) {
    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> mat[i][j];
        }
    }
}

void importPlaintext(string& plaintext, int mat[row][col]) {
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

Triplet doEncryption(char first, char second, char third, int mat[col][row]) {
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
    
    cout<<endl; 

    result.x = (newX) % 26;
    result.y = (newY) % 26;
    result.z = (newZ) % 26;
    
    return result;
}

int main() {
    int mode, mat[row][col];
    string plaintext;
    cout << "Choose mode:" << endl;
    cout << "1. Encryption" << endl;
    cout << "2. Decryption" << endl;

    cin >> mode; 

    switch (mode) {
    case 1:
        importMatrix(mat);
        importPlaintext(plaintext,mat);
        break;

    case 2:
       // decryption part remains
        break;

    default:
        cout << "Invalid mode!" << endl;
        break;
    }

    return 0;
}
