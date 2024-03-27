#pragma once

#include <bits/stdc++.h>
using namespace std;

typedef map<int, map<char, set<int>>> Tablenfa;

class nonDeterministicFiniteAutomata {
    
   public:
    set<int> states;
    unordered_set<char> alphabet;
    Tablenfa transitions;
    int initialState;
    unordered_set<int> finalStates;

    nonDeterministicFiniteAutomata(set<int> states, unordered_set<char> alphabet, Tablenfa transitions,
                                char initialState, unordered_set<int> finalStates)
        : states(states),
          alphabet(alphabet),
          transitions(transitions),
          initialState(initialState),
          finalStates(finalStates) {}

    bool processString(string str);
    void displayTransitionTablenfa();
};

// bool nonDeterministicFiniteAutomata::processString(string str) {
//     int currentState = 0;

//     cout << "String Processing: " << endl
//          << setw(16) << left << "Current State" << setw(10) << left << "Input" << setw(10)
//          << left << "New State" << endl;
//     int newState;
//     for (const auto& character : str) {
//         newState = transitions[currentState][character];
//         cout << setw(16) << left << ("q" + to_string(currentState)) << setw(10) << left <<
//         character << setw(10)
//          << left << ("q" + to_string(newState)) << endl;
//         currentState = newState;
//     }
//     if (finalStates.find(currentState) != finalStates.end()) return true;
//     return false;
// }

void nonDeterministicFiniteAutomata::displayTransitionTablenfa() {
    cout << setw(4) << "  " << setw(7) << "States";

    for (const auto& value : this->alphabet) cout << setw(15) << value;

    cout << endl;

    for (auto state: this->states) {
        if (state == 0)
            cout << setw(4) << "->";
        else if (this->finalStates.find(state) != this->finalStates.end())
            cout << setw(4) << " *";
        else
            cout << setw(4) << "  ";

        cout << setw(7) << state;

        for (const auto& value : this->alphabet) {
            string trnsStates = "{ ";
            for (auto resultStates : this->transitions[state][value]) {
                trnsStates = trnsStates + "q" + to_string(resultStates) + " ";
            }
            trnsStates += "}";
            cout << setw(15) << (trnsStates);
        }
        cout << endl;
    }
}
