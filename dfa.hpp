#pragma once

#include <bits/stdc++.h>
using namespace std;

typedef map<int, map<char, int>> Table;

class deterministicFiniteAutomata {
    set<int> states;
    unordered_set<char> alphabet;
    Table transitions;
    int initialState;
    unordered_set<int> finalStates;

   public:
    deterministicFiniteAutomata(set<int> states, unordered_set<char> alphabet, Table transitions,
                                char initialState, unordered_set<int> finalStates)
        : states(states),
          alphabet(alphabet),
          transitions(transitions),
          initialState(initialState),
          finalStates(finalStates) {}

    bool processString(string str);
    void displayTransitionTable();
    void displayTransitionTableNFA();
};

bool deterministicFiniteAutomata::processString(string str) {
    int currentState = 0;

    cout << "String Processing: " << endl
         << setw(16) << left << "Current State" << setw(10) << left << "Input" << setw(10) << left
         << "New State" << endl;
    int newState;
    for (const auto& character : str) {
        newState = transitions[currentState][character];
        cout << setw(16) << left << ("q" + to_string(currentState)) << setw(10) << left << character
             << setw(10) << left << ("q" + to_string(newState)) << endl;
        currentState = newState;
    }
    if (finalStates.find(currentState) != finalStates.end()) return true;
    return false;
}

inline string intToState(int n) {
    string num = to_string(n);
    reverse(num.begin(), num.end());
    return "q" + num + "";
}

inline string intToState(int n, int x) {
    string num = to_string(n);
    reverse(num.begin(), num.end());
    return "q[" + num + "]";
}

void deterministicFiniteAutomata::displayTransitionTable() {
    cout << setw(4) << "  " << setw(7) << "States";

    for (const auto& value : this->alphabet) cout << setw(15) << value;

    cout << endl;

    for (auto state : this->states) {
        if (state == 0)
            cout << setw(4) << "->";
        else if (this->finalStates.find(state) != this->finalStates.end())
            cout << setw(4) << " *";
        else
            cout << setw(4) << "  ";

        cout << setw(7) << intToState(state);

        for (const auto& value : this->alphabet)
            cout << setw(15) << intToState(this->transitions[state][value]);

        cout << endl;
    }
}

void deterministicFiniteAutomata::displayTransitionTableNFA() {
    cout << setw(4) << "  " << setw(7) << "States";

    for (const auto& value : this->alphabet) cout << setw(15) << value;

    cout << endl;

    for (auto state : this->states) {
        if (state == 0)
            cout << setw(4) << "->";
        else if (this->finalStates.find(state) != this->finalStates.end())
            cout << setw(4) << " *";
        else
            cout << setw(4) << "  ";

        cout << setw(7) << intToState(state,0);

        for (const auto& value : this->alphabet)
            cout << setw(15) << intToState(this->transitions[state][value],0);

        cout << endl;
    }
}

string trim(const string& str) {
    auto start = find_if_not(str.begin(), str.end(), [](int c) { return isspace(c); });
    auto end = find_if_not(str.rbegin(), str.rend(), [](int c) { return isspace(c); }).base();

    return (start < end) ? string(start, end) : "";
}

template <typename T>
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
