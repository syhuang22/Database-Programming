CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g
LDFLAGS = -lpqxx -lpq

SRCS = main.cpp query_funcs.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

.PHONY: all clean

all: test

test: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

-include $(DEPS)

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM -MT '$(<:.cpp=.o) $@' $< > $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *~ *.o test $(OBJS) $(DEPS)
