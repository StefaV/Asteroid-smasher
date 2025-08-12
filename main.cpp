#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> //for detecting key strokes
#include <windows.h>//for screen clearing
#include <deque>

using namespace std;

//Alternative to cls comand for screen clearing
void gotoxy(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}

//World elements
string space = " ";
string border_left = ">";
string border_right = "<";

class Player{
    public:
        int row = 10;
        int column = 10;
        string sprite = "@";

        void draw(){
            cout << sprite;
        }
};

class Rocket{
    public:
        int row;
        int column;
        string sprite = "^";

        void draw(){
            cout << sprite;
        }
};

class Asteroid{
    public:
        int row = 1;
        int column = 1;
        int speed;
        string sprite = "*";

        void draw(){
            cout << sprite;
        }
};

//Game variables
int score = 0;
int world_rows = 10;
int world_columns = 20;
int asteroid_count = 0;
int key;
int tick;
int game_speed = 30;

int main(){

    srand(time(0));

    Player player;
    Rocket rocket;
    Asteroid asteroid;

    //removes the cmd cursor
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    while(true){

        gotoxy(0, 0);

        tick ++;
        if(tick == game_speed) {
            tick = 0;
            if(asteroid.row > world_rows){
                asteroid.row = 1;
                asteroid.column = 1 + (rand() % world_columns);
            }
            else
                asteroid.row++;

        }

        //Draws the screen
        for (int i = 1; i < world_rows + 1; i++){ //Draws rows
                cout << border_left;
                
                for (int j = 1; j < world_columns + 1; j++){ //Draws columns
                    if (j == player.column && i == player.row){
                        player.draw();
                    }
                    else if(j == asteroid.column && i == asteroid.row){
                        asteroid.draw();
                    }
                    else
                        cout << space;
                }
                cout << border_right << endl;
            }
        
        //checks for key presses
        if(kbhit()){
            key = (int)getch();
            switch(key) {
            case 119: //letter w
                break;
            case 97:  //letter a
                if (player.column > 1) player.column --;
                break;
            case 100: //letter d
                if (player.column < world_columns) player.column ++;
                break;
            default:
                cout << endl << "null" << endl;  //not arrow
                break;
            }
        }
    }
    return 0;
}