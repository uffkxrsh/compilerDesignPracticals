#pragma once

#include <bits/stdc++.h>
using namespace std;

typedef map<int, map<char, int>> Table;

class deterministicFiniteAutomata {
    int states;
    unordered_set<char> alphabet;
    Table transitions;
    int initialState;
    unordered_set<int> finalStates;

   public:
    deterministicFiniteAutomata(int states, unordered_set<char> alphabet, Table transitions,
                                char initialState, unordered_set<int> finalStates)
        : states(states),
          alphabet(alphabet),
          transitions(transitions),
          initialState(initialState),
          finalStates(finalStates) {}

    bool processString(string str);
    void displayTransitionTable();
};

bool deterministicFiniteAutomata::processString(string str) {
    int currentState = 0;
    for (const auto& character : str) currentState = transitions[currentState][character];
    if (finalStates.find(currentState) != finalStates.end()) return true;
    return false;
}

