#include "library.h"
#include <iostream>
#include <string>
#include <QDebug>

using namespace std;

int main()
{
    Library ithala_lencwadi = Library();
    QString text;
    string input;
    cout << "Hello" << endl;
    cin >> input;
    cout << "You entered: " << input << endl;
    printf("John vula");
    // QDebug() << "Hello World";

#ifdef _WIN32
    // Wait for key press to keep console open
    printf("\nPress Enter to exit...");
    getchar();
#endif

    return 0;
}
