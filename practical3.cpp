#pragma once

#include <bits/stdc++.h>

#include "dfa.hpp"
#include "nfa.hpp"
using namespace std;

void manualInput(set<int> states, unordered_set<char>& alphabet, Tablenfa& transitions);
deterministicFiniteAutomata* convertNFAtoDFA(nonDeterministicFiniteAutomata* nfa);

int main() {
    set<int> states;
    unordered_set<char> alphabet;
    Tablenfa transitions;
    int initialState = 0;
    unordered_set<int> finalStates;
    string inputString;
    // alphabet.insert('φ');

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

    int nstates;
    cout << "Enter the number of states : " << endl;
    cin >> nstates;
    for (int i = 0; i < nstates; i++) states.insert(i);
    cout << nstates << endl;

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

    nonDeterministicFiniteAutomata* nfa = new nonDeterministicFiniteAutomata(
        states, alphabet, transitions, initialState, finalStates);
    cout << endl;
    nfa->displayTransitionTablenfa();
    cout << endl;

    deterministicFiniteAutomata* dfa = convertNFAtoDFA(nfa);

    delete nfa;
    delete dfa;
}

void manualInput(set<int> states, unordered_set<char>& alphabet, Tablenfa& transitions) {
    // std::locale::global(std::locale("en_US.UTF-8"));
    cout << "Input transitions (f is the transition function)" << endl
         << "\u03B4(x,y) : <state1> <state2> .... <stateN>" << endl
         << endl;
    int state;
    string delta = "\u03B4";
    for (auto state : states) {
        for (const auto& value : alphabet) {
            cout << delta << "(" << state << "," << value << ") : ";
            {
                string tempStr;
                getline(cin, tempStr);

                istringstream ss(tempStr);
                string token;

                while (getline(ss, token, ' ')) {
                    int tState = stoi(trim(token));
                    if (tState == -1) continue;
                    transitions[state][value].insert(tState);
                }
            }

            cout << "{ ";
            for (auto value : transitions[state][value]) cout << value << " ";
            cout << '}';
            cout << endl;
        }
    }
    cin.ignore();
}

int setToNumber(set<int> st) {
    int num = 0;
    for (auto it = st.rbegin(); it != st.rend(); it++) {
        num = num * 10 + *it;
    }
    return num;
}

deterministicFiniteAutomata* convertNFAtoDFA(nonDeterministicFiniteAutomata* nfa) {
    set<int> states;
    unordered_set<char> alphabet = nfa->alphabet;
    Table transitions;
    int initialState = 0;
    unordered_set<int> finalStates;

    stack<int> stck;
    stck.push(0);
    states.insert(0);
    // set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(unionSet,
    // unionSet.begin()));
    while (!stck.empty()) {
        int state = stck.top();
        stck.pop();

        for (auto alp : nfa->alphabet) {
            if (state / 10 > 0) {
                set<int> unionSet;
                int temp = state;
                bool final = false;
                while (temp > 0) {
                    int digit = temp % 10;
                    set_union(nfa->transitions[digit][alp].begin(),
                              nfa->transitions[digit][alp].end(), unionSet.begin(), unionSet.end(),
                              inserter(unionSet, unionSet.begin()));
                    if (nfa->finalStates.find(digit) != nfa->finalStates.end()) final = true;
                    temp /= 10;
                }
                if (final) finalStates.insert(state);
                transitions[state][alp] = setToNumber(unionSet);
            } else {
                int nState = setToNumber(nfa->transitions[state][alp]);
                transitions[state][alp] = nState;
            }
            if (states.find(transitions[state][alp]) == states.end()) {
                states.insert(transitions[state][alp]);
                stck.push(transitions[state][alp]);
            }
        }
    }

    deterministicFiniteAutomata* dfa =
        new deterministicFiniteAutomata(states, alphabet, transitions, initialState, finalStates);

    dfa->displayTransitionTableNFA();

    return dfa;
}