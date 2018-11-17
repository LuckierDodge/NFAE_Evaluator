# build nfa from nfa.cpp
all: nfa_e.cpp
	g++ -g -Wall -o nfa_e nfa_e.cpp

clean:
	$(RM) nfa_e
