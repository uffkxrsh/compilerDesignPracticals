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

void deterministicFiniteAutomata::displayTransitionTable() {
    cout << setw(4) << "  " << setw(7) << "States";

    for (const auto& value : this->alphabet) cout << setw(5) << value;

    cout << endl;

    for (int i = 0; i < this->transitions.size(); i++) {
        if (i == 0)
            cout << setw(4) << "->";
        else if (this->finalStates.find(i) != this->finalStates.end())
            cout << setw(4) << " *";
        else
            cout << setw(4) << "  ";

        cout << setw(7) << i;

        for (const auto& value : this->alphabet)
            cout << setw(5) << ("q" + to_string(this->transitions[i][value]));

        cout << endl;
    }
}

string trim(const string& str) {
    auto start = find_if_not(str.begin(), str.end(), [](int c) { return isspace(c); });
    auto end = find_if_not(str.rbegin(), str.rend(), [](int c) { return isspace(c); }).base();

    return (start < end) ? string(start, end) : "";
}

template<typename T>
void sortUnorderedSetDecreasing(unordered_set<T>& s) {
    // Copy elements from unordered_set to vector
    vector<T> tempVector(s.begin(), s.end());

    // Sort the vector in decreasing order
    sort(tempVector.begin(), tempVector.end(), greater<T>());

    // Clear the unordered_set
    s.clear();

    // Insert sorted elements from the vector back to the unordered_set
    for (const auto& elem : tempVector) {
        s.insert(elem);
    }
}