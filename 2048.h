#ifndef GAME_2048_H
#define GAME_2048_H
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80


const int GAME_SIZE = 4;

class Game{
private:
    int board[GAME_SIZE][GAME_SIZE];
    int point;
    int max;
private: 
    bool isEndgame();
    //direction: 2 for up, 8 for down, 4 for left and 6 for right
    bool isEqual(int, int, int);
    void bubble(int, int);
    void Slide(int);
    void move(int);
    bool movable(int);
    bool combine_col();
    bool combine_row();
    void appear();
    void updateRank();
public:
    Game();
    void show_board();
    void play();
    void showrank();
};

#endif