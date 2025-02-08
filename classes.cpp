#include <iostream>
#include <random>
#include <windows.h>
#include <stdlib.h>
using namespace std;

const int MAX_X = 10;
const int MAX_Y = 10;

void clear(){
    cout << string(20, '\n');
}

class Point {
    public:
        int x = 0, y = 0;

        void Print() {
            cout << endl << x << " - " << y;
        }
        
        void MakeRandom() {
            x = RandomNumber(MAX_X);
            y = RandomNumber(MAX_Y);
        }

        bool Equal(Point b) {
            return x == b.x && y == b.y;
        }
    
    private:
        int RandomNumber(int range){
            random_device rd;
            uniform_int_distribution<int> dist(1, range - 2);
            return dist(rd);
        }
};

class Player{
public:
    Point location;
    void Set(int x, int y) {
        location.x = x;
        location.y = y;
    }
    void MoveLeft() {
        location.x = location.x - 1;
    }
    void MoveRight() {
        location.x = location.x + 1;
    }
    void MoveDown() {
        location.y = location.y + 1;
    }
    void MoveUp() {
        location.y = location.y - 1;
    }
};

class Game{
private:
    int x, y;
    Point food;
    Player player;
    int score;
    bool playing;

public:
    void StartNewGame() {
       // Initialise size.
       x = MAX_X;
       y = MAX_Y;

       // Set food and player locations.
       food.MakeRandom();
       player.Set(x / 2, y / 2);

       score = 0;
       playing = false;

       Start();
    }

    void Start() {
        playing = true;

        while(playing) { // 17ms => 60 fps
            Input();
            Update();
            Render();
            Sleep(200);
        }
    }

private:
    void Input() {
        if (GetAsyncKeyState('W') & 0b1) {
            player.MoveUp();
        }
        else if (GetAsyncKeyState('S') & 0b1) {
            player.MoveDown();
        }
        else if (GetAsyncKeyState('A') & 0b1) {
            player.MoveLeft();
        }
        else if (GetAsyncKeyState('D') & 0b1) {
            player.MoveRight();
        }
    }

    bool isOutOfBounds() {
        return player.location.x == 0 || 
            player.location.x == x - 1 || 
            player.location.y == 0 || 
            player.location.y == y - 1; 
    }

    void Update() {
        // 1. Check game end
        if (isOutOfBounds()) {
            GameOver();
            return;
        }

        // 2. Check if food eaten
        if (player.location.Equal(food)) {
            score++;
            food.MakeRandom();
            return;
        }

        // Anything else.
    }

    void Render() {
        clear();
        for (int row = 0; row < y; row++) { // Rows
            string line = "";
            for (int col = 0; col < x; col++) { // Cols
                Point current;
                current.y = row;
                current.x = col;

                // Borders
                if (col == 0 || col == x - 1 || row == 0 || row == y - 1) {
                    line = line + "#";
                }

                // Player
                else if (current.Equal(player.location)) {
                    line = line + "x";
                }

                // Food
                else if(current.Equal(food)){
                    line = line + "o";
                }

                else {
                   line = line + ".";
                }
            }

            cout << line;
            if(row < y - 1){
                cout << endl;
            }
        }
    }


    void GameOver() {
        playing = false;

        cout << endl << "You lost! You got " << score << "point! Try again (Y or N)?" << endl;

        string input;
        cin >> input;

        if(input == "Y") {
            StartNewGame();
        }
    }
};


int main() {
    Game game;
    game.StartNewGame();

    return 0;
}