#include <iostream>
#include <random>
#include <windows.h>
#include <stdlib.h>
using namespace std;

class Area{
public:
    int n, m;
    int x1, y1;
};
class Player{
public:
    int x, y;
    int score;
    int steps;
};

int RandomNumber(int area){
    random_device rd;
    uniform_int_distribution<int> dist(1, area);
    return dist(rd);
}

bool map(int n, int m, int x, int y, int& x1, int& y1, int steps, int& score) {
    bool IsItOn = true;

    if (x > m || y > n || x == 0 || y == 0)
    {
        cout << "You lost!";
        cout << endl
             << "Your steps: " << steps;
        cout << endl
             << "Your score: " << score;
        return false;
    }

    n = n + 2;
    m = m + 2;
    string arr[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0 || j == m - 1 || i == 0 || i == n - 1) {
                arr[i][j] = "#";
            }
            else if (i == x && j == y) {
                arr[i][j] = "x";
            }
            else if(i == x1 && j == y1){
                arr[i][j] = "o";
                IsItOn = false;
            }
            else {
                arr[i][j] = ".";
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    if(IsItOn){
        x1 = RandomNumber(n-2);
        y1 = RandomNumber(m-2);
        map(n-2, m-2, x, y, x1, y1, steps, ++score);
    }
    return true;
}

int Input(int x, int y, int n, int m, int x1, int y1, int steps, int score) {
    bool playing = true;
    while (playing) {
        if (GetAsyncKeyState('W') & 0b1) {
            x = x - 1;
            playing = map(n, m, x, y, x1, y1, ++steps, score);
        }
        if (GetAsyncKeyState('A') & 0b1) {
            y = y - 1;
            playing = map(n, m, x, y, x1, y1, ++steps, score);
        }
        if (GetAsyncKeyState('S') & 0b1) {
            x = x + 1;
            playing = map(n, m, x, y, x1, y1, ++steps, score);
        }
        if (GetAsyncKeyState('D') & 0b1) {
            y = y + 1;
            playing = map(n, m, x, y, x1, y1, ++steps, score);
        }
        if(GetAsyncKeyState(VK_ESCAPE)){
            return 0;
        }
    }
    return 0;
}

int main() {
    int n, m;
    cout << "Please write n and m: ";
    cin >> n >> m;
    int x = 1, y = 1, steps = 0, score = 0;
    int x1 = RandomNumber(n);
    int y1 = RandomNumber(m);
    //functions
    map(n, m, x, y, x1, y1, steps, score);
    Input(x, y, n, m, x1, y1, steps, score);
    return 0;
}