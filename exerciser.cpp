#include "exerciser.h"

void exercise(connection *C) {
    // Query 1
    query1(C, 1, 35, 40, 0, 10, 12, 0, 7, 9, 0, 1, 3, 0, 0.6, 0.8, 0, 1.8, 2);

    // Query 2
    query2(C, "Red");

    // Query 3
    query3(C, "Duke");

    // Query 4
    query4(C, "NC", "Red");

    // Query 5
    query5(C, 13);
}
