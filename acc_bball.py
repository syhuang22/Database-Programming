from sqlalchemy import create_engine, Column, Integer, String, ForeignKey, Float
from sqlalchemy.orm import sessionmaker, relationship
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()


class State(Base):
    __tablename__ = 'state'
    state_id = Column(Integer, primary_key=True)
    name = Column(String)


class Color(Base):
    __tablename__ = 'color'
    color_id = Column(Integer, primary_key=True)
    name = Column(String)


class Team(Base):
    __tablename__ = 'team'
    team_id = Column(Integer, primary_key=True)
    name = Column(String)
    state_id = Column(Integer, ForeignKey('state.state_id'))
    color_id = Column(Integer, ForeignKey('color.color_id'))
    wins = Column(Integer)
    losses = Column(Integer)

    state = relationship("State")
    color = relationship("Color")


class Player(Base):
    __tablename__ = 'player'
    player_id = Column(Integer, primary_key=True)
    team_id = Column(Integer, ForeignKey('team.team_id'))
    uniform_num = Column(Integer)
    first_name = Column(String)
    last_name = Column(String)
    mpg = Column(Float)
    ppg = Column(Float)
    rpg = Column(Float)
    apg = Column(Float)
    spg = Column(Float)
    bpg = Column(Float)

    team = relationship("Team")

