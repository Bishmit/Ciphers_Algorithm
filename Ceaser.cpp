#include <iostream>
using namespace std; 

int main() {
    int mode; 
    cout << "1. encrypt" << endl; 
    cout << "2. decrypt" << endl; 
    cin >> mode; 
    switch(mode) {
        case 1: {
            string plaintext; 
            cin.ignore(); 
            getline(cin, plaintext);
            int n = plaintext.size(); 
            char result[n]; 
            for(int i = 0; i < n; i++) {
                if(plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
                    result[i] = 'A' + ( (plaintext[i] - 'A' + 3) % 26 ); 
                } else {
                    result[i] = plaintext[i]; 
                }
            }
            cout << endl; 
            cout << result << endl; 
            break; 
        }
        case 2: {
            string ciphertext; 
            cin.ignore(); 
            getline(cin, ciphertext); 
            int n = ciphertext.size(); 
            char result[n];
            for(int i = 0; i < n; i++) {
                if(ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                    result[i] = 'A' + ( (ciphertext[i] - 'A' - 3 + 26) % 26 ); 
                } else {
                    result[i] = ciphertext[i]; 
                }
            }
            cout << endl; 
            cout << result << endl; 
            break; 
        }
        default:
            cout << "Invalid mode selected" << endl; 
            break; 
    }
    
    return 0; 
}
