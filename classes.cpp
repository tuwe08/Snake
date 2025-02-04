#include <iostream>
#include <random>
#include <windows.h>
#include <stdlib.h>
using namespace std;

class Area{
public:
    int x, y;
    int x1, y1;

    int RandomNumber(int area){
        random_device rd;
        uniform_int_distribution<int> dist(1, area);
        return dist(rd);
    }
};
class Player{
public:
    int x = 1, y = 1;
    int score;
    int steps;
};
class Trail{
public:
    int n = 0;
    int arr[1000];
};

bool map(Player &player, Area &area, Trail &trail) {
    bool IsItOn = true;
    trail.n = 2*player.score;
    int temp = player.score;



    if (player.x > area.x || player.y > area.y || player.x == 0 || player.y == 0)
    {
        cout << "You lost!";
        cout << endl << "Your steps: " << player.steps;
        cout << endl << "Your score: " << player.score;
        return false;
    }

    area.y = area.y + 2;
    area.x = area.x + 2;
    string arr[area.y][area.x];

    for (int i = 0; i < area.y; i++) {
        for (int j = 0; j < area.x; j++) {
            if (j == 0 || j == area.x - 1 || i == 0 || i == area.y - 1) {
                arr[i][j] = "#";
            }
            else if (i == player.x && j == player.y) {
                arr[i][j] = "x";
                trail.arr[trail.n] = i;
                trail.arr[trail.n+1] = j;
            }
            else if(i == area.x1 && j == area.y1){
                arr[i][j] = "o";
                IsItOn = false;
            }
            else {
                arr[i][j] = ".";
            }
        }
    }
    while(temp > 0){
        trail.n = 2 * temp;
        arr[trail.arr[trail.n]][trail.arr[(trail.n + 1)]] = "x";
        temp--;
    }

    for (int i = 0; i < area.y; i++)
    {
        for (int j = 0; j < area.x; j++)
        {
            cout << arr[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    area.y = area.y - 2;
    area.x = area.x - 2;
    if(IsItOn){
        area.x1 = area.RandomNumber(area.x);
        area.y1 = area.RandomNumber(area.y);
        player.score++;
    }
    return true;
}

int Input(Player &player, Area &area, Trail &trail) {
    bool playing = true;
    while (playing) {
        if (GetAsyncKeyState('W') & 0b1) {
            player.x = player.x - 1;
            player.steps++;
            playing = map(player, area, trail);
        }
        else if (GetAsyncKeyState('A') & 0b1) {
            player.y = player.y - 1;
            player.steps++;
            playing = map(player, area, trail);
        }
        else if (GetAsyncKeyState('S') & 0b1) {
            player.x = player.x + 1;
            player.steps++;
            playing = map(player, area, trail);
        }
        else if (GetAsyncKeyState('D') & 0b1) {
            player.y = player.y + 1;
            player.steps++;
            playing = map(player, area, trail);
        }
        else if(GetAsyncKeyState('E') & 0b1){
            return 0;
        }
        Sleep(100);
    }
    return 0;
}

int main() {
    Area area;
    Player player;
    Trail trail;

    cout << "Please write the maps size(x, y): ";
    cin >> area.x >> area.y;
    area.x1 = area.RandomNumber(area.x);
    area.y1 = area.RandomNumber(area.y);
    player.score = 0;
    player.steps = 0;

    map(player, area, trail);
    Input(player, area, trail);
    return 0;
}