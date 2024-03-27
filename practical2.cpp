#pragma once

#include <bits/stdc++.h>

#include "dfa.hpp"
using namespace std;

void starting_with(set<int> states, unordered_set<char>& alphabet, Table& transitions, int initialState,
                   int finalState, string& inputString);
void ending_with(set<int> states, unordered_set<char>& alphabet, Table& transitions, int initialState,
                 int finalState, string& inputString);
void containing(set<int> states, unordered_set<char>& alphabet, Table& transitions, int initialState,
                int finalState, string& inputString);


int main() {
    set<int> states;
    unordered_set<char> alphabet;
    Table transitions;
    int initialState = 0;
    unordered_set<int> finalStates;
    string inputString;

    cout << "Enter the alphabet of the DFA (space seperated): " << endl
         << "<alphabet> <alphabet> <alphabet> .... <Enter to end the string>" << endl;

    {
        string tempStr;
        getline(cin, tempStr);

        istringstream ss(tempStr);
        string token;

        while (getline(ss, token, ' ')) alphabet.insert(trim(token)[0]);
    }

    sortUnorderedSetDecreasing(alphabet);

    for (auto value : alphabet) cout << value << " ";
    cout << endl << endl;

    int choice;
    cout << "Choose where you want to find the string: " << endl
         << "1. Starting with input string" << endl
         << "2. Ending with input string" << endl
         << "3. Containing input string" << endl;

    cin >> choice;
    cout << "Option Chosen: " << choice << endl;
    cout << endl;
    cin.ignore(256, '\n');
    do {
        switch (choice) {
            case 1: {
                cout << "Enter the string you want to construct DFA for:";
                getline(cin, inputString);
                cout<< '\n' <<inputString<<endl;
                for(int i = 0; i < inputString.size() + 2;i++) states.insert(i);
                finalStates.insert(states.size() - 2);
                starting_with(states, alphabet, transitions, initialState, states.size() - 2, inputString);
            } break;
            case 2: {
                cout << "Enter the string you want to construct DFA for:";
                getline(cin, inputString);
                cout<< '\n' <<inputString<<endl;
                for(int i = 0; i < inputString.size() + 1;i++) states.insert(i);
                finalStates.insert(states.size() - 1);
                ending_with(states, alphabet, transitions, initialState, states.size() - 1, inputString);
            } break;
            case 3: {
                cout << "Enter the string you want to construct DFA for:";
                getline(cin, inputString);
                cout<< '\n' <<inputString<<endl;
                for(int i = 0; i < inputString.size() + 2;i++) states.insert(i);
                finalStates.insert(states.size() - 1);
                containing(states, alphabet, transitions, initialState, states.size() - 1, inputString);
            } break;
            default: {
                cout << "Invalid Choice, Re-Enter!" << endl;
                cin >> choice;
            } break;
        }
    } while (choice < 1 || choice > 7);

    deterministicFiniteAutomata* DFA =
        new deterministicFiniteAutomata(states, alphabet, transitions, initialState, finalStates);

    cout<<"\n Transition Table : "<<endl;
    DFA->displayTransitionTable();
    string input;
    cout << "Enter String to check in DFA:" << endl;
    getline(cin, input);
    cout<<input<<endl<<endl;
    if (DFA->processString(input))
        cout << "Success" << endl;
    else
        cout << "Failed" << endl;
    delete DFA;
    return 0;
}

void starting_with(set<int> states, unordered_set<char>& alphabet, Table& transitions, int initialState,
                   int finalState, string& inputString) {
    int deadState = states.size() - 1;
    for (auto state: states) {
        if (state == finalState || state == deadState) {
            for (const auto& value : alphabet) transitions[state][value] = state;
            continue;
        }

        for (const auto& value : alphabet) {
            if (inputString[state] == value) {
                transitions[state][value] = state + 1;
                continue;
            }
            transitions[state][value] = deadState;
        }
    }
}

void ending_with(set<int> states, unordered_set<char>& alphabet, Table& transitions, int initialState,
                 int finalState, string& inputString) {
    map<char, int> flags;
    for (const auto& value : alphabet) flags[value] = -1;

    for (auto state: states) {
        if (state == finalState) {
            for (const auto& value : alphabet) transitions[state][value] = flags[value];
            continue;
        }

        for (const auto& value : alphabet) {
            if (inputString[state] == value)
                transitions[state][value] = state + 1;
            else {
                if (flags[value] == -1) flags[value] = state;
                transitions[state][value] = flags[value];
            }
        }
    }
}

void containing(set<int> states, unordered_set<char>& alphabet, Table& transitions, int initialState,
                int finalState, string& inputString) {
    map<char, int> flags;
    for (const auto& value : alphabet) flags[value] = -1;

    for (auto state: states) {
        if (state == finalState) {
            for (const auto& value : alphabet) transitions[state][value] = state;
            continue;
        }

        for (const auto& value : alphabet) {
            if (inputString[state] == value)
                transitions[state][value] = state + 1;
            else {
                if (flags[value] == -1) flags[value] = state;
                transitions[state][value] = flags[value];
            }
        }
    }
}
