#include <iostream>

using namespace std;

const double g = { 9.80665 };

void Calculate_values(int x,double V0,double h)
{  
    double height = { h - V0*x - g * pow(x, 2) / 2 };
    if(height>0)
    cout << "At " << x << " second the ball is on the "<<height << "m from the ground" << '\n';
    else
        cout << "At " << x << " second the ball is on the 0m from the gorund" << '\n';
}
int main()
{
    double V0 = {};
    double h = {};
    cout << "Enter height of tower:";
    cin >> h;
    cout << "Enter start speed:";
    cin >> V0;
    for (int i = 0; i < 6; i++)
    {
        Calculate_values(i,V0,h);
    }
    bool a = {true};
    while (a)
    {
        cout << "Will u want to continue? \n Y/N \n";
        char c = {};

        Again:
        cin >> c;
        switch (c)
        {
        case 'n':
        case 'N':
            cout << "Thanks!";
            exit(0);
        case 'y':
        case 'Y':
            break;
        default:
            goto Again;
        }

        int time = {};
        cout << "Enter the time value(integer):";
        cin >> time;
        Calculate_values(time, V0, h);
    }
}

