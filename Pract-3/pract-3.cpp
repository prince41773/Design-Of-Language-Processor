/*
Implementation of a lexical analyser for C language compiler that takes input from any c file like 'temp.c'.
1. Tockenize input string
2. remove comments
3. remove white spaces
4. entering identifiers into symbol table
5. generating lexical errors

input should contain keyword, identifier, constsnts, strings, punctuation, operators, comments and white spaces

int main() {
int a=5, 7H;
// assing value
char b='x';
/*return
value
return a+b;
}

output in tokenized category in keyword, identifier, punctuation, operator, constatnt, string, identifier for all individual char like keyword: int, identifier: main, identifier:a , etc...

Lexical error: if any like invalid words like 7H

Symbol table entries:
1. a
2. b
*/

#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

unordered_set<string> keywords = {"int", "char", "return", "if", "else", "while", "for", "main", "long", "double", "float"};
unordered_set<char> punctuation = {';', ',', '(', ')', '{', '}'};
unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '!', '&', '|'};
vector<string> symbolTable;
vector<string> lexicalErrors;

bool isKeyword(const string& token) {
    return keywords.find(token) != keywords.end();
}

bool isIdentifier(const string& token) {
    return regex_match(token, regex("[a-zA-Z_][a-zA-Z0-9_]*"));
}

bool isConstant(const string& token) {
    return regex_match(token, regex("[0-9]+"));
}

vector<string> tokenize(const string& line) {
    vector<string> tokens;
    string token;
    for (char ch : line) {
        if (isspace(ch) || punctuation.count(ch) || operators.count(ch)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            if (punctuation.count(ch) || operators.count(ch)) {
                tokens.push_back(string(1, ch));
            }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to process tokens
void processTokens(const vector<string>& tokens, ofstream& output) {
    for (const string& token : tokens) {
        if (isKeyword(token)) {
            output << "Keyword: " << token << endl;
            cout << "Keyword: " << token << endl;
        } else if (isIdentifier(token)) {
            output << "Identifier: " << token << endl;
            cout << "Identifier: " << token << endl;
            if (find(symbolTable.begin(), symbolTable.end(), token) == symbolTable.end()) {
                symbolTable.push_back(token);
            }
        } else if (isConstant(token)) {
            output << "Constant: " << token << endl;
            cout << "Constant: " << token << endl;
        } else if (punctuation.count(token[0])) {
            output << "Punctuation: " << token << endl;
            cout << "Punctuation: " << token << endl;
        } else if (operators.count(token[0])) {
            output << "Operator: " << token << endl;
            cout << "Operator: " << token << endl;
        } else {
            output << "Lexical Error: " << token << endl;
            cout << "Lexical Error: " << token << endl;
            lexicalErrors.push_back(token);
        }
    }
}

string removeComments(const string& line) {
    size_t singleLineComment = line.find("//");
    size_t multiLineComment = line.find("/*");

    if (singleLineComment != string::npos) {
        return line.substr(0, singleLineComment);
    } else if (multiLineComment != string::npos) {
        return line.substr(0, multiLineComment);
    }
    return line;
}

int main() {
    ifstream input("input.c");      //  Use Except input_1
    ofstream output("output.txt");

    if (!input.is_open() || !output.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    bool inMultiLineComment = false;

    while (getline(input, line)) {
        if (inMultiLineComment) {
            size_t endComment = line.find("*/");
            if (endComment != string::npos) {
                inMultiLineComment = false;
                line = line.substr(endComment + 2);
            } else {
                continue;
            }
        }

        size_t startComment = line.find("/*");
        if (startComment != string::npos) {
            inMultiLineComment = true;
            line = line.substr(0, startComment);
        }

        line = removeComments(line);
        vector<string> tokens = tokenize(line);
        processTokens(tokens, output);
    }

    output << "\nSymbol Table Entries:" << endl;
    cout << "\nSymbol Table Entries:" << endl;
    for (size_t i = 0; i < symbolTable.size(); ++i) {
        output << i + 1 << ". " << symbolTable[i] << endl;
        cout << i + 1 << ". " << symbolTable[i] << endl;
    }

    if (!lexicalErrors.empty()) {
        output << "\nLexical Errors:" << endl;
        cout << "\nLexical Errors:" << endl;
        for (const string& error : lexicalErrors) {
            output << error << endl;
            cout << error << endl;
        }
    }

    input.close();
    output.close();
    return 0;
}
