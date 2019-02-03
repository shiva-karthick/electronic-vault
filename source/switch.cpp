#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int number = 1;
    int button;
    switch (number)
    {
    case 1:
        cout << "1" << endl;
        cout << "Finished executing !" << endl;
    default:
        cout << "Press any button to close the door" << endl;
        cin >> button;
        if (button)
        {
            cout << "Exit" << endl;
        }
        break;
    }
    return 0;
}
