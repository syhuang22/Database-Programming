#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg) {
    try {
        // Create a new SQL statement to insert a new player
        work W(*C);
        stringstream ss;
        ss << "INSERT INTO PLAYER (team_id, jersey_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg) "
           << "VALUES (" << team_id << ", " << jersey_num << ", " << W.quote(first_name) << ", "
           << W.quote(last_name) << ", " << mpg << ", " << ppg << ", " << rpg << ", " << apg << ", "
           << spg << ", " << bpg << ");";
        
        // Execute the SQL statement
        W.exec(ss.str());
        W.commit();
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to add player." << endl;
    }
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses) {
    try {
        // Create a new SQL statement to insert a new team
        work W(*C);
        stringstream ss;
        ss << "INSERT INTO TEAM (name, state_id, color_id, wins, losses) "
           << "VALUES (" << W.quote(name) << ", " << state_id << ", " << color_id << ", " << wins << ", "
           << losses << ");";
        
        // Execute the SQL statement
        W.exec(ss.str());
        W.commit();
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to add team." << endl;
    }
}


void add_state(connection *C, string name) {
    try {
        // Create a new SQL statement to insert a new state
        work W(*C);
        stringstream ss;
        ss << "INSERT INTO STATE (name) VALUES (" << W.quote(name) << ");";
        
        // Execute the SQL statement
        W.exec(ss.str());
        W.commit();
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to add state." << endl;
    }
}


void add_color(connection *C, string name) {
    try {
        // Create a new SQL statement to insert a new color
        work W(*C);
        stringstream ss;
        ss << "INSERT INTO COLOR (name) VALUES (" << W.quote(name) << ");";
        
        // Execute the SQL statement
        W.exec(ss.str());
        W.commit();
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to add color." << endl;
    }
}

/*
 * All use_ params are used as flags for corresponding attributes
 * a 1 for a use_ param means this attribute is enabled (i.e. a WHERE clause is needed)
 * a 0 for a use_ param means this attribute is disabled
 */
void query1(connection *C,
	        int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            ) {
    try {
        work W(*C);
        stringstream ss;
        ss << "SELECT * FROM PLAYER WHERE ";
        bool first_condition = true;
        if (use_mpg) {
            ss << "mpg BETWEEN " << min_mpg << " AND " << max_mpg;
            first_condition = false;
        }
        if (use_ppg) {
            if (!first_condition) {
                ss << " AND ";
            }
            ss << "ppg BETWEEN " << min_ppg << " AND " << max_ppg;
            first_condition = false;
        }
        if (use_rpg) {
            if (!first_condition) {
                ss << " AND ";
            }
            ss << "rpg BETWEEN " << min_rpg << " AND " << max_rpg;
            first_condition = false;
        }
        if (use_apg) {
            if (!first_condition) {
                ss << " AND ";
            }
            ss << "apg BETWEEN " << min_apg << " AND " << max_apg;
            first_condition = false;
        }
        if (use_spg) {
            if (!first_condition) {
                ss << " AND ";
            }
            ss << "spg BETWEEN " << min_spg << " AND " << max_spg;
            first_condition = false;
        }
        if (use_bpg) {
            if (!first_condition) {
                ss << " AND ";
            }
            ss << "bpg BETWEEN " << min_bpg << " AND " << max_bpg;
        }
        ss << ";";
        W.exec(ss.str());
        cout << "Query successfully executed" << endl;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
    }

}


void query2(connection *C, string team_color){
    try {
        nontransaction N(*C);

        work W(*C);
        string sql = "SELECT team.name "
                 "FROM team "
                 "JOIN color ON team.color_id = color.color_id "
                 "WHERE color.name = " + W.quote(team_color);
        W.commit();

        // Execute SQL query
        result R(N.exec(sql));

        // Print out result
        cout << "Query result:" << endl;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        cout << c[0].as<string>() << endl;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to query team by color." << endl;
    }
}


void query3(connection *C, string team_name) {
    try {
        nontransaction N(*C);

        work W(*C);
        string sql = "SELECT * "
                     "FROM player "
                     "JOIN team ON player.team_id = team.team_id "
                     "WHERE team.name = " + W.quote(team_name) + ";";
        W.commit();

        // Execute SQL query
        result R(N.exec(sql));

        // Print out result
        cout << "Query result:" << endl;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << "Player " << c[1].as<string>() << " " << c[2].as<string>() << endl;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to query players by team name." << endl;
    }
}


void query4(connection *C, string team_state, string team_color) {
    try {
        nontransaction N(*C);

        work W(*C);
        stringstream ss;
        ss << "SELECT TEAM.NAME FROM TEAM, COLOR, STATE WHERE "
        "TEAM.COLOR_ID = COLOR.COLOR_ID AND "
        "TEAM.STATE_ID = STATE.STATE_ID AND "
        "STATE.NAME = "
        << W.quote(team_state) << " AND "
        "COLOR.NAME = "
        << W.quote(team_color) << ";";
        W.commit();

        // Execute SQL query
        result R(N.exec(ss));

        // Print out result
        cout << "Query result:" << endl;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << c[0].as<string>() << endl;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to query team by state and color." << endl;
    }
}


void query5(connection *C, int num_wins) {
    try {
        work W(*C);
        stringstream ss;
        ss << "SELECT TEAM.NAME, WINS FROM TEAM WHERE WINS > " << num_wins << ";";
        W.commit();
        nontransaction N(*C);

        // Execute SQL query
        result R(N.exec(ss));

        // Print out result
        cout << "Query result:" << endl;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << c[0].as<string>() << " " << c[1].as<int>() << endl;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to query teams by number of wins." << endl;
    }
}
