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

int main() {
    string plaintext; 
    int depth, mode; 
    cout << "1. Encryption" << endl;
    cout << "2. Decryption" << endl;
    cout << "Choose mode: ";
    cin>>mode; 
        switch(mode) {
            case 1: 
                cout << "Enter the plaintext for encryption: "; 
                cin >> plaintext; 
                cout << "Enter the depth: "; 
                cin >> depth; 
                encryptRailFence(plaintext, depth);
                break;

            case 2: 
                cout << "Decryption feature will be implemented soon.\n";
                break;

            default:
                cout << "Invalid mode.\n";
                break;
        }
    return 0;
}
