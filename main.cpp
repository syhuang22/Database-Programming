#include <fstream>
#include <iostream>
#include <pqxx/pqxx>  // Include the PostgreSQL library
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace pqxx;

// TODO: Implement function to read from text file and insert into database tables

int main(int argc, char * argv[]) {
  try {
    // Set up a connection to the PostgreSQL database
    connection C("dbname=ACC_BBALL user=postgres password=passw0rd \
                       hostaddr=127.0.0.1 port=5432");
    if (C.is_open()) {
      cout << "Opened database successfully: " << C.dbname() << endl;
    }
    else {
      cout << "Failed to open database" << endl;
      return 1;
    }

    // TODO: Implement code to drop tables (if they exist) and create new tables

    // TODO: Implement code to read from source text files and insert into database tables

    // TODO: Implement calls to query functions to test database

    // Close the database connection
    C.disconnect();
  }
  catch (const std::exception & e) {
    cerr << e.what() << endl;
    return 1;
  }
  return 0;
}
