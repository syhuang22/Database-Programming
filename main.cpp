#include <iostream>
#include <pqxx/pqxx>
#include <fstream>     // for reading from file

#include "exerciser.h"

using namespace std;
using namespace pqxx;

void dropTables(connection *C) {
  try {
    work W(*C);
    W.exec("DROP TABLE IF EXISTS PLAYER");
    W.exec("DROP TABLE IF EXISTS TEAM");
    W.exec("DROP TABLE IF EXISTS STATE");
    W.exec("DROP TABLE IF EXISTS COLOR");
    W.commit();
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
  }
}

void createPlayerTable(connection *C) {
  try {
    work W(*C);
    // Create PLAYER table
    string sql = "CREATE TABLE PLAYER ("
                "PLAYER_ID SERIAL PRIMARY KEY,"
                "TEAM_ID INTEGER NOT NULL REFERENCES TEAM(TEAM_ID),"
                "UNIFORM_NUM INTEGER NOT NULL,"
                "FIRST_NAME TEXT NOT NULL,"
                "LAST_NAME TEXT NOT NULL,"
                "MPG REAL NOT NULL,"
                "PPG REAL NOT NULL,"
                "RPG REAL NOT NULL,"
                "APG REAL NOT NULL,"
                "SPG REAL NOT NULL,"
                "BPG REAL NOT NULL"
                ");";
    // Execute the SQL statement
    W.exec(sql);
    W.commit();
    cout << "PLAYER table created successfully." << endl;
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
  }
}

void createTeamTable(connection *C) {
    try {
      // Create a new SQL statement to create a team table
      work W(*C);
      string sql = "CREATE TABLE TEAM("
                  "TEAM_ID SERIAL PRIMARY KEY,"
                  "NAME TEXT NOT NULL,"
                  "STATE_ID INTEGER NOT NULL,"
                  "COLOR_ID INTEGER NOT NULL,"
                  "WINS INTEGER NOT NULL,"
                  "LOSSES INTEGER NOT NULL"
                  ");";
      W.exec(sql);
      W.commit();

      cout << "Team table created successfully!" << endl;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to create team table." << endl;
    }
}

void createStateTable(connection *C) {
    try {
      // Create a new SQL statement to create the STATE table
      work W(*C);
      string sql = "CREATE TABLE STATE("
                    "STATE_ID SERIAL PRIMARY KEY,"
                    "NAME TEXT NOT NULL);";

      // Execute the SQL statement
      W.exec(sql);
      W.commit();

      cout << "STATE table created successfully." << endl;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to create STATE table." << endl;
    }
}

void createColorTable(connection *C) {
    try {
        // Create a new SQL statement to create the table
        work W(*C);
        string sql = "CREATE TABLE COLOR("
                    "COLOR_ID SERIAL PRIMARY KEY,"
                    "NAME TEXT NOT NULL);";
        W.exec(sql);
        W.commit();
        
        cout << "COLOR Table created successfully." << endl;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to create COLOR table." << endl;
    }
}


void loadPlayerData(connection *C) {
    try {
        // Read data from file
        ifstream file("player.txt");
        if (!file.is_open()) {
            cerr << "Failed to open player.txt" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int key_id, team_id, uniform_num, mpg, ppg, rpg, apg;
            double spg, bpg;
            string first_name, last_name;

            ss >> key_id >> team_id >> uniform_num >> first_name >> last_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg;

            // Insert player into the database
            add_player(C, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
        }

        cout << "Data loaded into PLAYER table successfully." << endl;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to load data into PLAYER table." << endl;
    }
}

void loadTeamData(connection *C) {
    try {
        // Read data from file
        ifstream file("team.txt");
        if (!file.is_open()) {
            cerr << "Failed to open team.txt" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int team_id, state_id, color_id, wins, losses;
            string name;
            ss >> team_id >> name >> state_id >> color_id >> wins >> losses;

            // Insert team into the database
            add_team(C, name, state_id, color_id, wins, losses);
        }

        cout << "Data loaded into TEAM table successfully." << endl;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to load data into TEAM table." << endl;
    }
}

void loadStateData(connection *C) {
    try {
      // Read data from file
      ifstream file("state.txt");
      if (!file.is_open()) {
          cerr << "Failed to open state.txt" << endl;
          return;
      }
      string line;
      while (getline(file, line)) {
          stringstream ss(line);
          int state_id;
          string name;
          ss >> state_id >> name;
          // Insert state into the database
          add_state(C, name);
      }

      cout << "Data loaded into STATE table successfully." << endl;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to load data into STATE table." << endl;
    }
}

void loadColorData(connection *C) {
    try {
      // Read data from file
      ifstream file("color.txt");
      if (!file.is_open()) {
          cerr << "Failed to open color.txt" << endl;
          return;
      }
      string line;
      while (getline(file, line)) {
          stringstream ss(line);
          int color_id;
          string color_name;

          ss >> color_id >> color_name;

          // Insert color into the database
          add_color(C, color_name);
      }
      cout << "Data loaded into COLOR table successfully." << endl;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to load data into COLOR table." << endl;
    }
}

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files

  //drop any tables if exits 
  dropTables(C);

  //create table needed 
  createStateTable(C);
  createColorTable(C);
  createTeamTable(C);
  createPlayerTable(C);
 
  //load data 
  loadStateData(C);
  loadColorData(C);
  loadTeamData(C);
  loadPlayerData(C);

  exercise(C);


  //Close database connection
  C->disconnect();

  return 0;
}


