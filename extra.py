from sqlalchemy import create_engine, text
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm import joinedload
from acc_bball.models import Team, Player, State, Color

def query1(conn,
           use_mpg, min_mpg, max_mpg,
           use_ppg, min_ppg, max_ppg,
           use_rpg, min_rpg, max_rpg,
           use_apg, min_apg, max_apg,
           use_spg, min_spg, max_spg,
           use_bpg, min_bpg, max_bpg):
    try:
        # Create database connection and create a session
        engine = create_engine(conn)
        Session = sessionmaker(bind=engine)
        session = Session()

        # Create a base query object
        query = session.query(Player)

        # Apply filters to the query object based on function arguments
        if use_mpg:
            query = query.filter(Player.mpg.between(min_mpg, max_mpg))
        if use_ppg:
            query = query.filter(Player.ppg.between(min_ppg, max_ppg))
        if use_rpg:
            query = query.filter(Player.rpg.between(min_rpg, max_rpg))
        if use_apg:
            query = query.filter(Player.apg.between(min_apg, max_apg))
        if use_spg:
            query = query.filter(Player.spg.between(min_spg, max_spg))
        if use_bpg:
            query = query.filter(Player.bpg.between(min_bpg, max_bpg))

        # Execute the query and retrieve the results
        results = query.all()

        # Print out result
        print("PLAYER_ID TEAM_ID JERSEY_NUM LAST_NAME FIRST_NAME MPG PPG RPG APG SPG BPG")
        for row in results:
            print(f"{row.player_id} {row.team_id} {row.jersey_num} {row.last_name} {row.first_name} {row.mpg} {row.ppg} {row.rpg} {row.apg} {row.spg} {row.bpg}")

    except Exception as e:
        print(e)
        print("Failed to query player stats.")

def query2(conn, team_color):
    try:
        # Create a session
        Session = sessionmaker(bind=conn)
        session = Session()

        # Execute SQL query
        result = session.query(Team.name).\
            join(Team.color).\
            filter_by(name=team_color)

        # Print out result
        print("NAME")
        for row in result:
            print(row[0])

        # Commit the transaction
        session.commit()

    except Exception as e:
        # Rollback the transaction in case of error
        session.rollback()
        print("Failed to query team by color.")
        print(e)

    finally:
        # Close the session
        session.close()

def query3(conn, team_name):
    try:
        # Create SQLAlchemy engine and session
        engine = create_engine(conn)
        Session = sessionmaker(bind=engine)
        session = Session()

        # Query players by team name and order by PPG
        players = session.query(Player).join(Team).filter(Team.name == team_name).order_by(Player.ppg.desc()).all()

        # Print out result
        print("FIRST_NAME LAST_NAME")
        for player in players:
            print(player.first_name, player.last_name)

    except Exception as e:
        print(e)
        print("Failed to query players by team name.")

def query4(conn, team_state, team_color):
    try:
        # Create a SQLAlchemy engine object
        engine = create_engine(conn)

        # Create a session factory
        Session = sessionmaker(bind=engine)

        # Create a session
        session = Session()

        # Construct the query using ORM syntax
        query = session.query(Player.uniform_num, Player.first_name, Player.last_name) \
            .join(Team) \
            .join(Color) \
            .join(State) \
            .filter(State.name == team_state, Color.name == team_color)

        # Execute the query and fetch the results
        result = query.all()

        # Print out result
        print("UNIFORM_NUM FIRST_NAME LAST_NAME")
        for row in result:
            print(row[0], row[1], row[2])

    except Exception as e:
        print(e)
        print("Failed to query players by team state and color.")

def query5(conn, num_wins):
    try:
        # Create SQLAlchemy engine and session
        engine = create_engine(conn)
        Session = sessionmaker(bind=engine)
        session = Session()

        # Define ORM query
        query = session.query(Player.first_name, Player.last_name, Team.name, Team.wins)\
            .join(Player.team)\
            .options(joinedload(Player.team))

        # Apply filter to query
        query = query.filter(Team.wins > num_wins)

        # Execute the query and fetch the results
        result = query.all()

        # Print out result
        print("FIRST_NAME LAST_NAME TEAM_NAME WINS")
        for row in result:
            print(row[0], row[1], row[2], row[3])

    except Exception as e:
        print(e)
        print("Failed to query players and teams by number of wins.")