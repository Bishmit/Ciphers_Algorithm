#include<iostream>
#include<unordered_map>
#include<string>
#include<utility>
using namespace std;

#define row 5
#define col 5

void insertInGrid(int, int, char grid[][col]);
void removeDuplicateLetters(const string& key, char grid[row][col]);
void partationOfText(string& text, char grid[row][col]);
pair<char, char> compute(char first, char second, char grid[row][col]);

void removeDuplicateLetters(const string& key, char grid[row][col]){
    unordered_map<char, bool> charSeen;
    
    int k = 0, l = 0;
    for(char ch : key){
        if(charSeen[ch] == false){
            grid[k][l] = ch;
            charSeen[ch] = true;
            l++;
            if(l == col){
                l = 0;
                k++;
            }
            if(k == row){
                break;
            }
        }
    }
 
    for(int i = 0; i < 26; i++){
        char ch = 'a' + i;
        if(i == 9){
            continue;
        }
        if(charSeen[ch] == false){
            grid[k][l] = ch;
            l++;
            if(l == col){
                l = 0;
                k++;
            }
            if(k == row){
                break;
            }
        }
    }

    insertInGrid(row, col, grid);
}

void insertInGrid(int k, int l, char grid[row][col]){
    for(int i = 0; i < k; i++){
        for(int j = 0; j < l; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void partationOfText(string& text, char grid[row][col]){
    string newtext;
    for(int i = 0; i < text.size(); i++){
        newtext += text[i];
        if(i < text.size() - 1 && text[i] == text[i+1]){
            newtext += 'x';  // add x in the middle of the same character
        }
    }
    if(newtext.size() % 2 != 0){  // add z in the end if the length of text is even
        newtext += 'z';
    }

    text = newtext;
    cout << text << endl;
    
    for(int i = 1; i <= text.size(); i++){
        for(int counter = 1; counter <= text.size()/2; counter++){
            if(i == counter*2){
               char first = text[i-2];
               char second = text[i-1];
               pair<char, char> finalResult = compute(first, second, grid);
               cout << text[i-2] << text[i-1] << " = " << finalResult.first << finalResult.second << endl;
            }
        }
    }
    cout << endl;
}

pair<char, char> compute(char first, char second, char grid[row][col]){
    pair<char, char> positions;
    int a = -1, b = -1, c = -1, d = -1;
    
    if(first == 'j') first = 'i';  // since i/j are written in same index in playfair cipher
    if(second == 'j') second = 'i';
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(grid[i][j] == first){
                a = i;
                b = j;
            }
            if(grid[i][j] == second){
                c = i;
                d = j;
            }
        }
    }
    
    // handle the row case
    if(a == c){
        positions.first = grid[a][(b + 1) % col];
        positions.second = grid[c][(d + 1) % col];
    }
    // Handle the same column case
    else if(b == d){
        positions.first = grid[(a + 1) % row][b];
        positions.second = grid[(c + 1) % row][d];
    }
    
    // Handle the other case
    else{
        positions.first = grid[a][d];
        positions.second = grid[c][b];
    }

    return positions;
}


int main(){
    string text, key;
    char grid[row][col] = {0};
    
    cout << "Enter the Plain-text: ";
    cin >> text;
    cout << "\nEnter the key: ";
    cin >> key;
    
    removeDuplicateLetters(key, grid);
    cout << endl;
    partationOfText(text, grid);
    
    return 0;
}
