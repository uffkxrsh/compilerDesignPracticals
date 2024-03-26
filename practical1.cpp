#pragma once

#include <bits/stdc++.h>
#include "dfa.hpp"
using namespace std;

void manual(int states, unordered_set<char>& alphabet, Table& transitions);

int main() {
    int states;
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

    for(auto value: alphabet)
        cout<<value<<" ";
    cout<<endl; 

    int init;
    int finalS; 
    cout << "Enter the initial state : " << endl;
    cin >> init;
    cout << init << endl;

    cout << "Enter the number of states : " << endl;
    cin >> states;
    cout<< states << endl; 

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

    for(auto value: finalStates)
        cout<<value<<" ";
    cout<<endl;

    manual(states, alphabet, transitions);

    deterministicFiniteAutomata* DFA =
        new deterministicFiniteAutomata(states, alphabet, transitions, initialState, finalStates);
    cout << endl;
    DFA->displayTransitionTable();
    cout << endl;
    string input;

    cout << "Enter String to check in DFA" << endl;
    getline(cin, input);
    cout<<input<<endl;

    if (DFA->processString(input))
        cout << "Success" << endl;
    else
        cout << "Failed" << endl;
    delete DFA;
    return 0;
}

void manual(int states, unordered_set<char>& alphabet, Table& transitions) {
    
    // std::locale::global(std::locale("en_US.UTF-8"));
    cout <<"Input transitions (f is the transition function)" <<endl;
    int state;
    string delta = "f";
    for (size_t i = 0; i < states; i++) {
        for (const auto& value : alphabet) {
            cout << delta << "( " << i << "," << value << " ): ";
            cin >> state;   
            cout << state << endl;
            transitions[i][value] = state;
        }
    }
    cin.ignore();
} 