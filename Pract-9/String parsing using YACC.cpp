#include <iostream>
#include <string>
#include <stack>
#include <vector>


using namespace std;

class GrammarParser {
private:
    string input;
    size_t pos;
    stack<char> parseStack;

    // Grammar rules:
    // S → i E t S S' | a
    // S' → e S | ε
    // E → b

    bool parse_S() {
        if (peek() == 'i') {
            // S → i E t S S'
            if (!match('i')) return false;
            if (!parse_E()) return false;
            if (!match('t')) return false;
            if (!parse_S()) return false;
            return parse_S_prime();
        } else if (peek() == 'a') {
            // S → a
            return match('a');
        }
        return false;
    }

    bool parse_S_prime() {
        if (peek() == 'e') {
            // S' → e S
            if (!match('e')) return false;
            return parse_S();
        }
        // S' → ε
        return true;
    }

    bool parse_E() {
        // E → b
        return match('b');
    }

    char peek() {
        if (pos < input.size()) return input[pos];
        return '\0';
    }

    bool match(char expected) {
        if (peek() == expected) {
            pos++;
            return true;
        }
        return false;
    }

public:
    bool parse(const string& str) {
        input = str;
        pos = 0;
        return parse_S() && pos == input.size();
    }
};

int main() {
    GrammarParser parser;

    vector<string> testCases = {
        "ibtai", "ibtaea", "a", "ibtibta", "ibtaeibta",
        "ibti", "ibtaa", "iea", "ibtb", "ibtibt"
    };

    cout << "String Validation Results:\n";
    cout << "-------------------------\n";
    for (const string& testCase : testCases) {
        cout << "Input: " << testCase << " - ";
        if (parser.parse(testCase)) {
            cout << "Valid string\n";
        } else {
            cout << "Invalid string\n";
        }
    }

    return 0;
}
