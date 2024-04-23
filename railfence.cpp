#include <iostream>
using namespace std;

void encryptRailFence(const string& plaintext, int depth) { 
    int n = plaintext.size(); 
    string s[depth][n]; 

    int row = 0;
    int col = 0;
    bool down = true; // to indicate direction

    for(int i = 0; i < n; i++) {
        s[row][col] = plaintext[i]; 
        
        // If we reach the top or bottom, change direction
        if(row == 0) {
            down = true;
        } else if(row == depth-1) {
            down = false;
        }
        
        if(down) {
            row++;
        } else {
            row--;
        }
        
        col++;
    }

    cout<<endl; 
    for(int i = 0; i < depth; i++) {
        for(int j = 0; j < n; j++) {
            cout << (s[i][j].empty() ? " " : s[i][j]) << " "; 
        }
        cout << endl; 
}
   
    cout<<"\nEncrypted output: "; 
    for(int i = 0; i < depth; i++) {
        for(int j = 0; j < n; j++) {
            cout <<s[i][j]; 
        }
    }
}

void decryptRailFence(const string& ciphertext, int depth) {
    int n = ciphertext.size();
    string s[depth][n];

    int row = 0;
    int col = 0;
    bool down = true;

    // Create the zigzag pattern in the matrix
    for(int i = 0; i < n; i++) {
        s[row][col] = "*"; 

        if(row == 0) {
            down = true;
        } else if(row == depth-1) {
            down = false;
        }

        if(down) {
            row++;
        } else {
            row--;
        }

        col++;
    }

    int index = 0;
    // Fill in the characters in the zigzag pattern
    for(int i = 0; i < depth; i++) {
        for(int j = 0; j < n; j++) {
            if(s[i][j] == "*") {
                s[i][j] = ciphertext[index++];
            }
        }
    }

    cout << "\nDecrypted output: ";
    // printing coloumn wise to get output
    row = 0;
    col = 0;
    down = true;

    for(int i = 0; i < n; i++) {
        cout << s[row][col];

        if(row == 0) {
            down = true;
        } else if(row == depth-1) {
            down = false;
        }

        if(down) {
            row++;
        } else {
            row--;
        }

        col++;
    }
    cout << endl;
}

int main() {
    string text; 
    int depth, mode; 
    cout << "1. Encryption" << endl;
    cout << "2. Decryption" << endl;
    cout << "Choose mode: ";
    cin>>mode; 
    cin>>ignore(); 
    
        switch(mode) {
            case 1: 
                cout << "Enter the plaintext for encryption: "; 
                getline(cin, text);  
                cout << "Enter the depth: "; 
                cin >> depth; 
                encryptRailFence(plaintext, depth);
                break;

            case 2: 
                cout << "Enter the ciphertext for decryption: "; 
                getline(cin, text); 
                cout << "Enter the depth: "; 
                cin >> depth; 
                decryptRailFence(text, depth);
                break;

            default:
                cout << "Invalid mode.\n";
                break;
        }
    return 0;
}
