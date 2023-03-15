#include "query_funcs.h"


void add_player(connection *C, int team_id, int uniform_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg) {
    try {

        // cout << "this is team_id:" << team_id << endl;
        // cout << "this is unifrom_num:" << uniform_num << endl;
        // cout << "this is first_name:" << first_name << endl;
        // cout << "this is last_name:" << last_name << endl;
        // cout << "this is mpg:" << mpg << endl;
        // cout << "this is ppg:" << ppg << endl;
        // cout << "this is rpg:" << rpg << endl;
        // cout << "this is apg:" << apg << endl;
        // cout << "this is spg:" << spg << endl;
        // cout << "this is bpg:" << bpg << endl;
        // Create a new SQL statement to insert a new player
        work W(*C);
        stringstream ss;
        ss << "INSERT INTO PLAYER (team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg) "
           << "VALUES (" << team_id << ", " << uniform_num << ", " << W.quote(first_name) << ", "
           << W.quote(last_name) << ", " << mpg << ", " << ppg << ", " << rpg << ", " << apg << ", "
           << spg << ", " << bpg << ");";
        
        // Execute the SQL statement
        W.exec(ss.str());
        W.commit();
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to add player." << endl;
        exit(1);
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
        // Start a transaction
        nontransaction N(*C);

        // Build the SQL query
        string sql = "SELECT * FROM player WHERE true";

        if (use_mpg) {
            sql += " AND mpg >= " + to_string(min_mpg) + " AND mpg <= " + to_string(max_mpg);
        }

        if (use_ppg) {
            sql += " AND ppg >= " + to_string(min_ppg) + " AND ppg <= " + to_string(max_ppg);
        }

        if (use_rpg) {
            sql += " AND rpg >= " + to_string(min_rpg) + " AND rpg <= " + to_string(max_rpg);
        }

        if (use_apg) {
            sql += " AND apg >= " + to_string(min_apg) + " AND apg <= " + to_string(max_apg);
        }

        if (use_spg) {
            sql += " AND spg >= " + to_string(min_spg) + " AND spg <= " + to_string(max_spg);
        }

        if (use_bpg) {
            sql += " AND bpg >= " + to_string(min_bpg) + " AND bpg <= " + to_string(max_bpg);
        }

        // Execute the SQL query
        result R(N.exec(sql));

        // Print the results
        cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << c[0].as<int>() << " "
                 << c[1].as<int>() << " "
                 << c[2].as<int>() << " "
                 << c[3].as<string>() << " "
                 << c[4].as<string>() << " "
                 << c[5].as<int>() << " "
                 << c[6].as<int>() << " "
                 << c[7].as<int>() << " "
                 << c[8].as<int>() << " "
                 << c[9].as<double>() << " "
                 << c[10].as<double>() << " " << endl;
        }

    } catch (const exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to query players." << endl;
    }

}


void query2(connection *C, string team_color){
    try {
        nontransaction N(*C);

        string sql = "SELECT team.name "
                 "FROM team "
                 "JOIN color ON team.color_id = color.color_id "
                 "WHERE color.name = " + N.quote(team_color);

        // Execute SQL query
        result R(N.exec(sql));

        // Print out result
        cout << "NAME" << endl;
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
        // Start a transaction
        work W(*C);

        // Construct the SQL query string
        string sql = "SELECT player.first_name, player.last_name "
                     "FROM player "
                     "JOIN team ON player.team_id = team.team_id "
                     "WHERE team.name = " + W.quote(team_name) + " "
                     "ORDER BY player.ppg DESC;";

        // Execute the SQL query
        result R(W.exec(sql));

        // Print out result
        cout << "FIRST_NAME LAST_NAME" << endl;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << c[0].as<string>() << " " << c[1].as<string>() << endl;
        }

        // Commit the transaction
        W.commit();
    } catch (const exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to query players by team name." << endl;
    }
}


void query4(connection *C, string team_state, string team_color) {
    try {
        nontransaction N(*C);

        string sql = "SELECT p.uniform_num, p.first_name, p.last_name "
                     "FROM player AS p "
                     "JOIN team AS t ON p.team_id = t.team_id "
                     "JOIN color AS c ON t.color_id = c.color_id "
                     "JOIN state AS s ON t.state_id = s.state_id "
                     "WHERE s.name = " + N.quote(team_state) +
                     " AND c.name = " + N.quote(team_color) + ";";

        // Execute SQL query
        result R(N.exec(sql));

        // Print out result
        cout << "UNIFORM_NUM FIRST_NAME LAST_NAME" << endl;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << c[0].as<string>() << " " << c[1].as<string>() << " " << c[2].as<string>() << endl;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to query players by team state and color." << endl;
    }
}


void query5(connection *C, int num_wins) {
    try {
        nontransaction N(*C);

        string sql = "SELECT player.first_name, player.last_name, team.name, team.wins "
                     "FROM player "
                     "JOIN team ON player.team_id = team.team_id "
                     "WHERE team.wins > " + to_string(num_wins) + ";";

        // Execute SQL query
        result R(N.exec(sql));

        // Print out result
        cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << c[0].as<string>() << " " 
                 << c[1].as<string>() << " "
                 << c[2].as<string>() << " "
                 << c[3].as<int>() << endl;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        cerr << "Failed to query players and teams by number of wins." << endl;
    }
}
