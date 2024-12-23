/*
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function for Test Case 1: DFA for the string "abbabab"
int dfa1(const char *input) {
    int transitionTable[5][2] = {
        {0, 0}, // Dummy state
        {2, 3}, // State 1: 'a' -> 2, 'b' -> 3
        {1, 4}, // State 2: 'a' -> 1, 'b' -> 4
        {4, 1}, // State 3: 'a' -> 4, 'b' -> 1
        {3, 2}  // State 4: 'a' -> 3, 'b' -> 2
    };

    int currentState = 1; // Initial state
    for (int i = 0; input[i] != '\0'; i++) {
        char symbol = input[i];
        int symbolIndex = (symbol == 'a') ? 0 : 1; // Map 'a' to 0, 'b' to 1
        currentState = transitionTable[currentState][symbolIndex];
    }
    return currentState == 2; // Accepting state
}

// Function for Test Case 2: DFA for strings where every 0 is followed by 11
int dfa2(const char *input) {
    int transitionTable[4][2] = {
        {0, 0}, // Dummy state
        {2, 0}, // State 1: '0' -> 2, '1' -> invalid
        {0, 3}, // State 2: '0' -> invalid, '1' -> 3
        {1, 0}  // State 3: '0' -> 1, '1' -> invalid
    };

    int currentState = 1; // Initial state
    for (int i = 0; input[i] != '\0'; i++) {
        char symbol = input[i];
        int symbolIndex = (symbol == '0') ? 0 : 1; // Map '0' to 0, '1' to 1
        currentState = transitionTable[currentState][symbolIndex];
    }
    return currentState == 1; // Accepting state
}

// Function for Test Case 3: DFA for strings over 'a', 'b', 'c' that start and end with the same letter
int dfa3(const char *input) {
    if (strlen(input) < 2 || input[0] != input[strlen(input) - 1]) {
        return 0; // Start and end letters must be the same
    }
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != 'a' && input[i] != 'b' && input[i] != 'c') {
            return 0; // Invalid character
        }
    }
    return 1; // Valid if conditions are met
}

// Function for Test Case 4: DFA for strings over lowercase alphabets and digits, starting with an alphabet
int dfa4(const char *input) {
    if (!islower(input[0])) {
        return 0; // Must start with a lowercase alphabet
    }
    for (int i = 1; input[i] != '\0'; i++) {
        if (!islower(input[i]) && !isdigit(input[i])) {
            return 0; // Only lowercase alphabets and digits are allowed
        }
    }
    return 1; // Valid if conditions are met
}

int main() {
    int choice;
    char input[100];

    // Display menu
    printf("Choose DFA to test:\n");
    printf("1. DFA for string 'abbabab'\n");
    printf("2. DFA for strings where every 0 is followed by 11\n");
    printf("3. DFA for strings over 'a', 'b', 'c' starting and ending with the same letter\n");
    printf("4. DFA for strings over lowercase alphabets and digits, starting with an alphabet\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    // Input string
    printf("Enter input string: ");
    scanf("%s", input);

    // Test selected DFA
    int isValid = 0;
    switch (choice) {
        case 1:
            isValid = dfa1(input);
            break;
        case 2:
            isValid = dfa2(input);
            break;
        case 3:
            isValid = dfa3(input);
            break;
        case 4:
            isValid = dfa4(input);
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }

    // Output result
    if (isValid) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}
*/
#include <bits/stdc++.h>
using namespace std;

// Test Case 1: DFA for the string "abbabab"
bool testCase1(const string &input) {
    int transition[5][2] = {{0, 0}, {2, 3}, {1, 4}, {4, 1}, {3, 2}};
    int currentState = 1; // Start state

    for (char ch : input) {
        int symbol = (ch == 'a') ? 0 : 1; // Map 'a' -> 0, 'b' -> 1
        currentState = transition[currentState][symbol];
    }
    return currentState == 2; // Check if the final state is accepting
}

// Test Case 2: DFA for strings where every '0' is followed by '11'
bool testCase2(const string &input) {
    int i = 0;
    while (i < input.length()) {
        if (input[i] == '0') {
            if (i + 2 < input.length() && input[i + 1] == '1' && input[i + 2] == '1') {
                i += 3;
            } else {
                return false; // Invalid if '0' is not followed by '11'
            }
        } else {
            i++; // Move to the next character
        }
    }
    return true;
}

// Test Case 3: DFA for strings over 'a', 'b', 'c' that start and end with the same letter
bool testCase3(const string &input) {
    int n = input.length();
    if (n == 0 || input[0] != input[n - 1]) {
        return false; // Start and end letters must match
    }
    for (char ch : input) {
        if (ch != 'a' && ch != 'b' && ch != 'c') {
            return false; // Invalid if any character is not 'a', 'b', or 'c'
        }
    }
    return true;
}

// Test Case 4: DFA for strings over lowercase alphabets and digits, starting with an alphabet
bool testCase4(const string &input) {
    if (!islower(input[0])) {
        return false; // Must start with a lowercase alphabet
    }
    for (char ch : input) {
        if (!islower(ch) && !isdigit(ch)) {
            return false; // Only lowercase alphabets and digits are allowed
        }
    }
    return true;
}

int main() {
    int choice;
    string input;

    // Display menu
    cout << "Choose Test Case:\n";
    cout << "1. DFA for string 'abbabab'\n";
    cout << "2. DFA for strings where every '0' is followed by '11'\n";
    cout << "3. DFA for strings over 'a', 'b', 'c' starting and ending with the same letter\n";
    cout << "4. DFA for strings over lowercase alphabets and digits, starting with an alphabet\n";
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    // Input string
    cout << "Enter input string: ";
    cin >> input;

    // Validate based on selected test case
    bool isValid = false;
    switch (choice) {
        case 1:
            isValid = testCase1(input);
            break;
        case 2:
            isValid = testCase2(input);
            break;
        case 3:
            isValid = testCase3(input);
            break;
        case 4:
            isValid = testCase4(input);
            break;
        default:
            cout << "Invalid choice\n";
            return 1;
    }

    // Output result
    if (isValid) {
        cout << "Valid\n";
    } else {
        cout << "Invalid\n";
    }

    return 0;
}

