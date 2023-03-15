#include "exerciser.h"

void exercise(connection *C) {
    // Query 1
    cout << "Executing Query 1: " << endl;
    cout << "==============================================" << endl;
    query1(C, 1, 35, 40, 0, 10, 12, 0, 7, 9, 0, 1, 3, 0, 0.6, 0.8, 0, 1.8, 2);
    cout << "==============================================" << endl;
    cout << endl;

    // Query 2
    cout << "Executing Query 2: " << endl;
    cout << "==============================================" << endl;
    query2(C, "Red");
    cout << "==============================================" << endl;
    cout << endl;

    // Query 3
    cout << "Executing Query 3: " << endl;
    cout << "==============================================" << endl;
    query3(C, "Duke");
    cout << "==============================================" << endl;
    cout << endl;

    // Query 4
    cout << "Executing Query 4: " << endl;
    cout << "==============================================" << endl;
    query4(C, "NC", "Red");
    cout << "==============================================" << endl;
    cout << endl;

    // Query 5
    cout << "Executing Query 5: " << endl;
    cout << "==============================================" << endl;
    query5(C, 13);
    cout << "==============================================" << endl;
    cout << endl;
}
