#include <bits/stdc++.h>
using namespace std;

typedef map<int, string> CommentMap;

pair<CommentMap, CommentMap> getComments(stringstream& program) {
    pair<CommentMap, CommentMap> comments;
    CommentMap& singleLineComments = comments.first;
    CommentMap& multiLineComments = comments.second;

    string line;
    int lineNumber = 1;

    string multiLineComment;
    bool inMultiLineComment = false;

    while (getline(program, line)) {
        size_t pos;
        if (!inMultiLineComment) {
            if ((pos = line.find("//")) != string::npos) {
                singleLineComments[lineNumber] = line.substr(pos + 2);
            } else if ((pos = line.find("/*")) != string::npos) {
                inMultiLineComment = true;
                if ((pos = line.find("*/")) != string::npos) {
                    multiLineComments[lineNumber] = line.substr(pos + 1);
                    inMultiLineComment = false;
                } else {
                    multiLineComment = line.substr(pos + 1) + "\n";
                }
            }
        } else {
            if ((pos = line.find("*/")) != string::npos) {
                multiLineComment += line.substr(0, pos + 2);
                multiLineComments[lineNumber] = multiLineComment;
                inMultiLineComment = false;
            } else {
                multiLineComment += line + "\n";
            }
        }

        lineNumber++;
    }
    return comments;
}

void displayComments(const pair<CommentMap, CommentMap>& comments) {
    std::cout << "Single-line Comments:\n";
    std::cout << "---------------------\n";
    for (const auto& entry : comments.first) {
        std::cout << "Line " << entry.first << ": " << entry.second << endl;
    }

    std::cout << "\nMulti-line Comments:\n";
    std::cout << "--------------------\n";
    for (const auto& entry : comments.second) {
        std::cout << "Line " << entry.first << ":\n" << entry.second << endl;
    }
}

int main() {
    int choice;
    stringstream program;
    std::cout << "menu : " << endl
              << "1. enter program from file" << endl
              << "2. enter program in console" << endl;
    cin >> choice;

    std::cout << "Option Selected : " << choice << endl;
    cin.ignore();
    do {
        switch (choice) {
            case 1: {
                string filePath;
                std::cout << "enter file path: " << endl;
                getline(cin, filePath);
                ifstream file(filePath);
                if (!file.is_open()) {
                    cerr << "Error: Unable to open file: " << filePath << endl;
                    return 1;
                }

                string line;
                string prgmString = "";
                while (getline(file, line)) {
                    prgmString += (line + "\n");
                }
                program.str(prgmString);

                file.close();
            } break;

            case 2: {
                const string delimiter = "END";
                std::cout << endl
                          << "enter the cpp code below (type 'END' on a separate line to finish): "
                          << endl
                          << endl;
                string line;
                string prgmString = "";
                while (getline(cin, line) && line != delimiter) {
                    prgmString += (line + "\n");
                }
                program.str(prgmString);
            } break;

            default: {
                std::cout << "Invalid Choice! Re-enter: ";
                cin >> choice;
                cin.ignore();
            }
        }
    } while (choice != 1 && choice != 2);

    pair<CommentMap, CommentMap> comments = getComments(program);
    displayComments(comments);
    return 0;
}
