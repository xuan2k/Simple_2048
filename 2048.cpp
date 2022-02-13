#include "2048.h"
#include<iostream>
#include<sstream>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<cmath>
#include<fstream>
using namespace std;


Game::Game(){
    this -> point = 0;
    this -> max = 2;
    for(int i = 0; i < GAME_SIZE; i++){
        for(int j = 0; j < GAME_SIZE; j++){
            this -> board[i][j] = 0;
        }
    }
    this -> appear();
    this -> appear();
    // int arr[GAME_SIZE][GAME_SIZE] = {
    //     {0,0,0,0},
    //     {0,0,2,4},
    //     {2,4,8,8},
    //     {16,16,16,16}
    // };
    // for(int i = 0; i < GAME_SIZE; i++){
    //     for(int j = 0; j < GAME_SIZE; j++){
    //         this -> board[i][j] = arr[i][j];
    //     }
    // }
}

void Game::show_board(){
    int len;
    int space = (int)log10(this -> max);
    for(int i = 0; i < GAME_SIZE; i++){
        stringstream ss;
        for(int j = 0; j < GAME_SIZE; j++){
            if(this -> board[i][j] == 0){
                ss << "| ";
                for(int i = 0; i < space; i++){
                    ss << " ";
                }
                ss << ".";
            }
            else{
                ss << "| ";
                int lim = space - (int)log10(this -> board[i][j]);
                for(int i = 0; i < lim; i++){
                    ss << " ";
                }
                ss << this -> board[i][j];
            }
        }
        string out = ss.str();
        len = out.length();
        for(int k = 0; k <= len; k++){
            cout << '-';
        }
        cout << '\n';
        cout << out;
        cout << "|\n";
    }
    for(int k = 0; k <= len; k++){
        cout << '-';
    }
    cout << '\n';
}

bool Game::isEndgame(){
    for(int i = 0; i < GAME_SIZE; i++){
        for(int j = 0; j < GAME_SIZE; j++){
            if(this -> board[i][j] == 0){
                return false;
            }
            if(this -> isEqual(i, j, 2) || this -> isEqual(i, j, 4) || this -> isEqual(i, j, 6) || this -> isEqual(i, j, 8)){
                return false;
            }
        }
    }
    return true;
}

bool Game::isEqual(int row, int col, int direction){
    if(row == 0 && direction == 2){
        return false;
    }
    if(row == (GAME_SIZE - 1) && direction == 8){
        return false;
    }
    if(col == 0 && direction == 4){
        return false;
    }
    if(col == (GAME_SIZE - 1) && direction == 6){
        return false;
    }
    if(direction == 2){
        if(this -> board[row][col] == this -> board[row - 1][col]){
            return true;
        }
        else return false;
    }
    else if(direction == 4){
        if(this -> board[row][col] == this -> board[row][col - 1]){
            return true;
        }
        else return false;
    }
    else if(direction == 6){
        if(this -> board[row][col] == this -> board[row][col + 1]){
            return true;
        }
        else return false;
    }
    else{
        if(this -> board[row][col] == this -> board[row + 1][col]){
            return true;
        }
        else return false;
    }
}

void Game::bubble(int type, int direct){
    /*
        This function is used to bubble the empty cell out of border
        Type = 0 for horizon and type = 1 for vertical
        Direct = 1 for go in the same direct with array and direct = -1 for other
    */
    int stop;
    if(direct == 1){
        stop = GAME_SIZE;
    }
    else{
        stop = 1;
    }
    if(type == 0){
        for(int row = 0; row < GAME_SIZE; row++){
            int curr = GAME_SIZE - stop;
            bool flag = true;
            while(flag && curr < GAME_SIZE && curr >= 0){
                int step = stop - 1;
                flag = false;
                while(step != curr){
                    if(this -> board[row][step] == 0 && this -> board[row][step - direct] != 0){
                        swap(this -> board[row][step], this -> board[row][step - direct]);
                        flag = true;
                    }
                    step -= direct;
                }
                curr += direct;
            }
        }
    }
    else{
        for(int col = 0; col < GAME_SIZE; col++){
            int curr = GAME_SIZE - stop;
            bool flag = true;
            while(flag && curr < GAME_SIZE && curr >= 0){
                int step = stop - 1;
                flag = false;
                while(step != curr){
                    if(this -> board[step][col] == 0 && this -> board[step - direct][col] != 0){
                        swap(this -> board[step][col], this -> board[step - direct][col]);
                        flag = true;
                    }
                    step -= direct;
                }
                curr += direct;
            }
        }
    }
}

void Game::Slide(int direction){
    if(direction == 2){
        this -> bubble(1, -1);
    }
    else if(direction == 4){
        this -> bubble(0, -1);
    }
    else if(direction == 6){
        this -> bubble(0, 1);

    }
    else{
        this -> bubble(1, 1);
    }
}

void Game::move(int direction){
    bool combined = false;
    bool movable = this -> movable(direction);
    if(direction == 2 || direction == 8){
        combined = this -> combine_row();
        this -> Slide(direction);
    }
    else{
        combined = this -> combine_col();
        this -> Slide(direction);
    }
    if(!movable && !combined){
        cout << "Unmovable\n";
        return;
    }
    this -> appear();
}

bool Game::movable(int direction){
    if(direction == 2){
        for(int col = 0; col < GAME_SIZE; col++){
            bool maybe = false;
            for(int row = GAME_SIZE - 1; row >= 0; row --){
                if(this -> board[row][col] != 0){
                    maybe = true;
                }
                if(maybe){
                    if(this -> board[row][col] == 0){
                        return true;
                    }
                }
            }
        }
    }
    else if(direction == 4){
        for(int row = 0; row < GAME_SIZE; row++){
            bool maybe = false;
            for(int col = GAME_SIZE - 1; col >= 0; col--){
                if(this -> board[row][col] != 0){
                    maybe = true;
                }
                if(maybe){
                    if(this -> board[row][col] == 0){
                        return true;
                    }
                }
            }
        }
    }
    else if(direction == 6){
        for(int row = 0; row < GAME_SIZE; row++){
            bool maybe = false;
            for(int col = 0; col < GAME_SIZE; col ++){
                if(this -> board[row][col] != 0){
                    maybe = true;
                }
                if(maybe){
                    if(this -> board[row][col] == 0){
                        return true;
                    }
                }
            }
        }
    }
    else{
        for(int col = 0; col < GAME_SIZE; col++){
            bool maybe = false;
            for(int row = 0; row < GAME_SIZE; row ++){
                if(this -> board[row][col] != 0){
                    maybe = true;
                }
                if(maybe){
                    if(this -> board[row][col] == 0){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::combine_row(){
    bool combined = false;
    for(int col = 0; col < GAME_SIZE; col++){
        int prev = this -> board[0][col];
        int prev_row = 0;
        for(int row = 1; row < GAME_SIZE; row++){
            if(this -> board[row][col] == 0){
                continue;
            }
            if(prev == this -> board[row][col]){
                this -> board[prev_row][col] = 2*prev;
                this -> point += 2*prev;
                if(this -> max < 2*prev){
                    this -> max = 2*prev;
                }
                this -> board[row][col] = 0;
                combined = true;
            }
            prev = this -> board[row][col];
            prev_row = row;
        }
    }
    return combined;
}

bool Game::combine_col(){
    bool combined = false;
    for(int row = 0; row < GAME_SIZE; row++){
        int prev = this -> board[row][0];
        int prev_col = 0;
        for(int col = 1; col < GAME_SIZE; col++){
            if(this -> board[row][col] == 0){
                continue;
            }
            if(prev == this -> board[row][col]){
                this -> board[row][prev_col] = 2*prev;
                this -> point += 2*prev;
                if(this -> max < 2*prev){
                    this -> max = 2*prev;
                }
                this -> board[row][col] = 0;
                combined = true;
            }
            prev = this -> board[row][col];
            prev_col = col;
        }
    }
    return combined;
}

void Game::play(){
    this -> show_board();
    cout << "Game begin, enter your move: \n";
    char cmd;
    while(cmd != 'q' && cmd != 27){
        cmd = getch();
        system ("CLS");
        if(cmd == 'w' || cmd == KEY_UP){
            this -> move(2);
        }
        else if(cmd == 'a' || cmd == KEY_LEFT){
            this -> move(4);
        }
        else if(cmd == 'd' || cmd == KEY_RIGHT){
            this -> move(6);
        }
        else if (cmd == 's' || cmd == KEY_DOWN){
            this -> move(8);
        }
        else{
            continue;
        }
        this -> show_board();
        if(this -> isEndgame()){
            break;
        }
        cout << "Your score: " << this -> point << ". Enter your movement or 'q' to quit: \n";
    }
    this -> show_board();
    cout << "Your score: " << this -> point << endl;
    this -> updateRank();
    cout << "Game over!\n";
}

void Game::appear(){
    int ammount = GAME_SIZE*GAME_SIZE;
    int *arr = new int[ammount];
    int k = 0;
    int count = 0;
    for(int row = 0; row < GAME_SIZE; row++){
        for(int col = 0; col < GAME_SIZE; col++){
            if(this -> board[row][col] == 0){
                arr[count++] = k;
            }
            k++;
        }
    }
    if(count > 0){
        int idx = rand() % (count);
        int choose = arr[idx];
        int row = choose / GAME_SIZE;
        int col = choose % GAME_SIZE;
        double number = rand() / RAND_MAX;
        if(number > 0.5){
            this -> board[row][col] = 4;
        }
        else{
            this -> board[row][col] = 2;
        }
    }
    delete arr;
}

void Game::showrank(){
    ifstream file("rank.txt");
    if(file){            
        cout << "--- Leader board ---\n";
        for(int i = 0; i < 10; i++){
            string tmp;
            getline(file, tmp);
            cout << "Top " << i + 1 << ": " << tmp << endl;
        }
    }
    else{
        this -> updateRank();
        this -> showrank();
    }
    file.close();
}

void Game::updateRank(){    
    ifstream file("rank.txt");
    int rank[10] {0};
    if(file){
        for(int i = 0; i < 10; i++){
            string tmp;
            getline(file, tmp);
            rank[i] = stoi(tmp);
        }
    }
    for(int i = 0; i < 10; i++){
        if(this -> point > rank[i]){
            rank[i] = this -> point;
            break;
        }
    }
    file.close();
    ofstream out("rank.txt");
    out << rank[0];
    for(int i = 1; i < 10; i++){
        out << '\n';
        out << rank[i];
    }
    out.close();
}

int main(){
    srand(time(NULL));
    bool play = true;
    cout << "---Welcome to 2048 game---\n";    
    cout << "Press 'p' to play game\n";
    cout << "Press 'r' to show leader board\n";        
    cout << "Press 'q' to quit the game\n";
              
    while(play){
        Game newGame;
        char c;
        c = getch();
        if(c == 'r'){
            newGame.showrank();
            cout << "Press 'p' to play game\n";
            cout << "Press 'q' to quit the game\n";
            continue;
        }
        else if(c == 'q'){
            break;
        }  
        newGame.play();
        cout << "Wanna try again? Please press 'c' to continue!\nPress 'r' to show the leader board\nPress 'q' to quit.\n";
    }
    system("CLS");
    cout << "Thank for playing our game!\n";
}
