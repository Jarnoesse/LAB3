#include <iostream>

using namespace std;
#include "GameManager.h"

int main()
{
    cout << "Welcome to Guderian Dream 0.2!" << endl;
    cout << "Select an option: 1. Play game  2. Exit game" << endl;
    int scelta;
    cin >> scelta;

    if(scelta != 2)
    {
    GameManager();

    }
    return 0;
}
