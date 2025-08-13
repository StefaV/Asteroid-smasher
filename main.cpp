#include <iostream>
#include <ctime>
#include <conio.h> //For detecting key strokes
#include <windows.h>//For screen clearing
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
        bool active = false;
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

            //Asteroid behavior
            if(asteroid.row > world_rows){ //Resets if out of bounds
                asteroid.row = 1;
                asteroid.column = 1 + (rand() % world_columns);
                score --;
            }
            else{
                asteroid.row ++; //Movement
            }

            //Rocket behavior
            if(rocket.row < 1)
                rocket.active = false;
            else
                if(rocket.active == true)
                    rocket.row --; // Movement
        }

        //Draws the screen
        for (int i = 1; i < world_rows + 1; i++){ //Draws rows
                cout << border_left;
                
                for (int j = 1; j < world_columns + 1; j++){ //Draws columns
                    if (j == player.column && i == player.row)
                        player.draw();
                    else if(j == asteroid.column && i == asteroid.row)
                        asteroid.draw();
                    else if(j == rocket.column && i == rocket.row)
                        rocket.draw();
                    else
                        cout << space;
                }
                cout << border_right << endl;
            }
        cout << endl;
        cout << "Score: " << score << endl;
        cout << endl;
        cout << "Use a and d to move and w to shoot (all lower case) \nHit the asteroid: +1 point \nMiss the asteroid: -1 point \nAsteroid hits the player: -3 points";
        
        //Checks for key presses
        if(kbhit()){
            key = (int)getch();
            switch(key) {
            case 119: //Letter w; fires the rocket
                if(rocket.active == false){
                    rocket.active = true;
                    rocket.row = player.row - 1;
                    rocket.column = player.column;
                }
                break;
            case 97:  //Letter a; move left
                if (player.column > 1) player.column --; //Left border collision check
                break;
            case 100: //Letter d; move right
                if (player.column < world_columns) player.column ++; //Right border collision check
                break;
            default:
                cout << endl << "Invalid command" << endl;  //Not arrow
                getch();
                break;
            }
        }

        //Collisions
        if(asteroid.column == player.column && asteroid.row == player.row){ //Asteroid collides with player
            asteroid.row = 1;
            asteroid.column = 1 + (rand() % world_columns);
            score -= 3;
        }
        else if(asteroid.column == rocket.column && (asteroid.row == rocket.row || asteroid.row == rocket.row - 1)){ // Asteroid collides with rocket
            asteroid.row = 1;
            asteroid.column = 1 + (rand() % world_columns);
            score ++;
            rocket.active == false;
            rocket.row = 0;
        }
    }
    return 0;
}