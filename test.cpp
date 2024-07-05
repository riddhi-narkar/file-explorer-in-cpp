// // #include <conio.h>
// #include <iostream>
// using namespace std;

// #define KEY_UP 72
// #define KEY_DOWN 80
// #define KEY_LEFT 75
// #define KEY_RIGHT 77

// int main()
// {
//     int c = 0;
//     while(1)
//     {
//         c = 0;
//         cin >> c;
//         switch(c) {
//         case KEY_UP:
//             cout << endl << "Up" << endl;//key up
//             break;
//         case KEY_DOWN:
//             cout << endl << "Down" << endl;   // key down
//             break;
//         case KEY_LEFT:
//             cout << endl << "Left" << endl;  // key left
//             break;
//         case KEY_RIGHT:
//             cout << endl << "Right" << endl;  // key right
//             break;
//         default:
//             cout << endl << "null" << endl;  // not arrow
//             break;
//         }

//     }

//     return 0;
// }

#include <iostream>
#include <termios.h>
#define STDIN_FILENO 0
using namespace std;
int main()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

// Once the buffering is turned off, the rest is simple.
    cout << "Enter a character: ";
    char c,d,e;
    cin >> c;
    cin >> d;
    cin >> e;
    cout << "\nYour character was ";
// Using 3 char type, Cause up down right left consist with 3 character
    if ((c==27)&&(d==91)) {
        if (e==65) { cout << "UP";}
        if (e==66) { cout << "DOWN";}
        if (e==67) { cout << "RIGHT";}
        if (e==68) { cout << "LEFT";}
    }
    return 0;
}


// the handle arrow key needs to be working with the navigate function
// I have mentioned the specifications for this many times

// the navigate functions need arrow keys to operate, here are all the specifications.
// It feels as if you keep forgetting things, which is making building this project extremely difficult
// Traversal
// a. Go back - Left arrow key should take the user to the previously visited directory
// b. Go forward - Right arrow key should take the user to the next directory
// c. Up one level - Backspace key should take the user up one level
// d. Home – h key should take the user to the home folder


// this is a code for processing arrow key inputs, you can refer to this to make necessary changes to the navigate function in accordance to the specification provided already.
// #include <iostream>
// #include <termios.h>
// #define STDIN_FILENO 0
// using namespace std;
// int main()
// {
//     struct termios t;
//     tcgetattr(STDIN_FILENO, &t);
//     t.c_lflag &= ~ICANON;
//     tcsetattr(STDIN_FILENO, TCSANOW, &t);


//     cout << "Enter a character: ";
//     char c,d,e;
//     cin >> c;
//     cin >> d;
//     cin >> e;
//     cout << "\nYour character was ";
// // Using 3 char type, Cause up down right left consist with 3 character
//     if ((c==27)&&(d==91)) {
//         if (e==65) { cout << "UP";}
//         if (e==66) { cout << "DOWN";}
//         if (e==67) { cout << "RIGHT";}
//         if (e==68) { cout << "LEFT";}
//     }
//     return 0;
// }