#pragma once

#include <bits/stdc++.h>

#include "dfa.hpp"
#include "nfa.hpp"
using namespace std;

void manualInput(int states, unordered_set<char>& alphabet, Tablenfa& transitions);

int main() {
    int states;
    unordered_set<char> alphabet;
    Tablenfa transitions;
    int initialState = 0;
    unordered_set<int> finalStates;
    string inputString;
    // alphabet.insert('ε');

    cout << "Enter the alphabet of the NFA (space seperated): " << endl
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
    cout << endl;

    int init;
    int finalS;
    cout << "Enter the initial state : " << endl;
    cin >> init;
    cout << init << endl;

    cout << "Enter the number of states : " << endl;
    cin >> states;
    cout << states << endl;

    initialState = init;
    cout << "Enter the final states seperated by a space: " << endl;
    cin.ignore();
    {
        string tempStr;
        getline(cin, tempStr);

        istringstream ss(tempStr);
        string token;

        while (getline(ss, token, ' ')) finalStates.insert(stoi(trim(token)));
    }

    sortUnorderedSetDecreasing(finalStates);

    for (auto value : finalStates) cout << value << " ";
    cout << endl << endl;

    manualInput(states, alphabet, transitions);

    nonDeterministicFiniteAutomata* NFA = new nonDeterministicFiniteAutomata(
        states, alphabet, transitions, initialState, finalStates);
    cout << endl;
    NFA->displayTransitionTablenfa();
    cout << endl;
    // string input;

    // cout << "Enter String to check in DFA" << endl;
    // getline(cin, input);
    // cout << input << endl;
    // cout << endl;
    // if (DFA->processString(input))
    //     cout << "Success" << endl;
    // else
    //     cout << "Failed" << endl;
    // delete DFA;
    // return 0;
}

void manualInput(int states, unordered_set<char>& alphabet, Tablenfa& transitions) {
    // std::locale::global(std::locale("en_US.UTF-8"));
    cout << "Input transitions (f is the transition function)" << endl
         << "\u03B4(x,y): <state1> <state2> .... <stateN>" << endl;
    int state;
    string delta = "\u03B4";
    for (size_t i = 0; i < states; i++) {
        for (const auto& value : alphabet) {
            cout << delta << "( " << i << "," << value << " ): ";
            {
                string tempStr;
                getline(cin, tempStr);

                istringstream ss(tempStr);
                string token;

                while (getline(ss, token, ' ')){
                    int tState = stoi(trim(token));
                    transitions[i][value].insert(tState);
                } 
            }

            sortUnorderedSetDecreasing(transitions[i][value]);

            cout << "{ ";
            for (auto value : transitions[i][value]) cout << value << " ";
            cout << '}';
            cout << endl;
        }
    }
    cin.ignore();
}
