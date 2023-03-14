# Database-Programming
This repository contains the source code for a PostgreSQL database management system that supports the ACC_BBALL database. The database is designed to store information about players, teams, states, and colors in the Atlantic Coast Conference (ACC) basketball league.

## Getting Started
### Prerequisites
Before you can use this database, you must have the following software installed on your computer:
* PostgreSQL
* C++ compiler (e.g. g++)
* GNU Make

## Installing
To install the database, follow these steps:
1. Clone this repository to your local machine.
2. Open a terminal window and navigate to the root directory of the repository.
3. Run the following command to compile the source code and create the ACC_BBALL database:
4. Run the following command to execute the program and populate the database with data from the source text files:

## Usage
Once the database is installed, you can use the following functions to interact with it:

* query1(): show all attributes of each player with average statistics that fall between the min and max (inclusive) for each enabled statistic.
* query2(): show the name of each team with the indicated uniform color.
* query3(): show the first and last name of each player that plays for the indicated team, ordered from highest to lowest ppg (points per game).
* query4(): show uniform number, first name and last name of each player that plays in the indicated state and wears the indicated uniform color.
* query5(): show first name and last name of each player, and team name and number of wins for each team that has won more than the indicated number of games.

To use these functions, add calls to them in the exerciser() function in exerciser.cpp. The program will execute the queries and print the results to the console.

