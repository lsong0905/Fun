#include <iostream>
#include <string.h>
#include<stdlib.h>
#include<ctime>
#include<vector>

using namespace std;

// Function declaration
void printStatus(vector<char> correct, vector<char> miss);
void updateCorrect(string randWord, char guess, vector<char>& correct);
bool checkIfWin(vector<char> correct);

bool winFlag;

int main()
{
    srand(time(0));
    int level;
    char guess;
    string words[3][5] = { {"fun", "car", "test", "book", "class"},
                           {"mouse", "notepad", "computer", "blackboard"},
                           {"kayak", "oxygen", "memento", "bagpipes"}};
    while(true){
        cout << "Please enter the difficulty level (1-3): ";
        cin >> level;
    
        // check if level is valid
        if(level < 1 || level > 3){
            cout << "Please enter a valid difficulty level!" << endl;
            continue;
        }
        
        cout<<"— Start guessing the chosen one —"<<endl;
        
        // pick a random word 
        string randWord = words[level-1][rand()%5];
        
        cout << "randWord: " << randWord << endl;
        
        // Create an array initialized with '_'s 
        vector<char> correct;
        vector<char> miss;
        for(int i=0; i<randWord.length(); i++){
            correct.push_back('_');
        }
        
        printStatus(correct, miss);
        int chance = 4;
        while(chance > 0){
            cout<<"Enter a letter:";
            cin >> guess;
            
            // check if guess is correct
            size_t position = randWord.find(guess);
            if(position != string::npos){
                // update correct vector 
                updateCorrect(randWord, guess, correct);
            }else{
                miss.push_back(guess);
                chance—;
            }
            
            // display status
            printStatus(correct, miss);
            
            // check if a user wins
            if(checkIfWin(correct)){
                winFlag = true;
                break;
            }
        }
        
        // Display result
        if(winFlag){
            cout << "— You have Won —" << endl;
        }else{
            cout << "— You have lost —" << endl;
        }
        
        // ask to play again
        char playAgain;
        cout << "Want to play again (Y/N)? ";
        cin >> playAgain;
        
        if(playAgain == 'Y' || playAgain == 'y'){
            continue;
        }else if(playAgain == 'N' || playAgain == 'n'){
            break;
        }else{
            cout << "Invalid answer. Exit." << endl;
        }
        
    }
}

bool checkIfWin(vector<char> correct){
    for(int i=0; i<correct.size(); i++){
        if(correct.at(i) == '_'){
            return false;
        }
    }
    return true;
}

void updateCorrect(string randWord, char guess, vector<char>& correct){
    for(int i=0; i<randWord.length(); i++){
        if(randWord.at(i) == guess){
            correct.at(i) = guess;
        }
    }
}

void printStatus(vector<char> correct, vector<char> miss){
    
    // print correct guess
    for(int i=0; i<correct.size(); i++){
        cout << correct.at(i) << " ";
    }
    cout << endl;
    
    // print wrong guess
    cout<< "Wrong guesses: ";
    if(miss.size() == 0){
        cout << "None!" << endl;
    }else{
        for(int i=0; i<miss.size(); i++){
            cout << "(" << i << ") " << miss.at(i) << " ";  
        }
        cout << endl;
    }
    cout << endl;
}