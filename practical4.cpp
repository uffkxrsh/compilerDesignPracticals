#include <bits/stdc++.h>
using namespace std;

// Enum for token types
enum class TokenType { Identifier, Constant, Operator, Keyword };

// Structure to represent a token
struct Token {
    TokenType type;
    string value;
};

// Function to check if a string is a keyword
bool isKeyword(const string& str) {
    static unordered_map<string, bool> keywords = {
        {"auto", true},     {"double", true},   {"int", true},
        {"struct", true},   {"break", true},    {"else", true},
        {"long", true},     {"switch", true},   {"case", true},
        {"enum", true},     {"register", true}, {"typedef", true},
        {"char", true},     {"extern", true},   {"return", true},
        {"union", true},    {"const", true},    {"float", true},
        {"short", true},    {"unsigned", true}, {"continue", true},
        {"for", true},      {"signed", true},   {"void", true},
        {"default", true},  {"goto", true},     {"sizeof", true},
        {"volatile", true}, {"do", true},       {"if", true},
        {"static", true},   {"while", true}
        // Add more keywords as needed
    };
    return keywords.find(str) != keywords.end();
}

// Function to classify a character
TokenType classifyChar(char c) {
    if (isalpha(c) || c == '_') {
        return TokenType::Identifier;
    } else if (isdigit(c)) {
        return TokenType::Constant;
    } else if (isspace(c)) {
        return TokenType::Operator;  // Space is considered an operator here
    } else {
        // Assume everything else is an operator
        return TokenType::Operator;
    }
}

// Function to tokenize a given source code
vector<Token> tokenize(const string& sourceCode) {
    vector<Token> tokens;
    string currentToken;
    for (char c : sourceCode) {
        TokenType type = classifyChar(c);
        if (type == TokenType::Operator) {
            if (!currentToken.empty()) {
                tokens.push_back(
                    {isKeyword(currentToken) ? TokenType::Keyword : TokenType::Identifier,
                     currentToken});
                currentToken.clear();
            }
            if (!isspace(c)) {
                tokens.push_back({TokenType::Operator, string(1, c)});
            }
        } else {
            currentToken += c;
        }
    }
    // Add the last token if any
    if (!currentToken.empty()) {
        tokens.push_back(
            {isKeyword(currentToken) ? TokenType::Keyword : TokenType::Identifier, currentToken});
    }
    return tokens;
}

// Function to print tokens
void printTokens(const vector<Token>& tokens) {
    cout << setw(10) << "TokenType"
         << "  " << setw(10) << "Value" << endl;
    for (const auto& token : tokens) {
        switch (token.type) {
            case TokenType::Identifier:
                cout << "<" << setw(10) << right << "id"
                     << " , " << setw(10) << left << token.value << "> " << endl;
                break;
            case TokenType::Constant:
                cout << "<" << setw(10) << right << "const"
                     << " , " << setw(10) << left << token.value << "> " << endl;
                break;
            case TokenType::Operator:
                cout << "<" << setw(10) << right << "operator"
                     << " , " << setw(10) << left << token.value << "> " << endl;
                break;
            case TokenType::Keyword:
                cout << "<" << setw(10) << right << "keyword"
                     << " , " << setw(10) << left << token.value << "> " << endl;
                break;
        }
    }
    cout << endl;
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);
    cout << expression << endl << endl;
    vector<Token> tokens = tokenize(expression);
    printTokens(tokens);
    return 0;
}
