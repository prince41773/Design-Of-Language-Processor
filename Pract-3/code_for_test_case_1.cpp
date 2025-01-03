#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

class LexicalAnalyzer {
private:
    vector<string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "inline", "int", "long", "register", "restrict", "return", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
    };
    vector<string> type_keywords = {
        "int", "char", "float", "double", "void", "long", "short",
        "unsigned", "signed", "_Bool", "_Complex", "_Imaginary"
    };
    vector<string> operators = {
        "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!",
        "&", "|", "^", "~", ">>", "<<", "++", "--", "%", "+=", "-=", "*=", "/=",
        "%=", "&=", "|=", "^=", ">>=", "<<="
    };
    vector<string> punctuation = {
        ",", ";", "(", ")", "{", "}", "[", "]", ".", "->", "..."
    };
    vector<string> symbol_table;
    vector<string> errors;
    vector<pair<string, string>> tokens_list;

public:
    bool is_valid_identifier(const string& lexeme) {
        if (!isalpha(lexeme[0]) && lexeme[0] != '_') return false;
        return all_of(lexeme.begin(), lexeme.end(), [](char c) { return isalnum(c) || c == '_'; });
    }

    string remove_comments(const string& code) {
        stringstream result;
        istringstream stream(code);
        string line;
        bool in_multiline_comment = false;

        while (getline(stream, line)) {
            if (!in_multiline_comment) {
                size_t single_line_comment = line.find("//");
                if (single_line_comment != string::npos) line = line.substr(0, single_line_comment);

                size_t multi_line_start = line.find("/*");
                if (multi_line_start != string::npos) {
                    size_t multi_line_end = line.find("*/", multi_line_start + 2);
                    if (multi_line_end != string::npos) {
                        line.erase(multi_line_start, multi_line_end - multi_line_start + 2);
                    } else {
                        line.erase(multi_line_start);
                        in_multiline_comment = true;
                    }
                }
            } else {
                size_t multi_line_end = line.find("*/");
                if (multi_line_end != string::npos) {
                    line.erase(0, multi_line_end + 2);
                    in_multiline_comment = false;
                } else {
                    line.clear();
                }
            }
            result << line << endl;
        }
        return result.str();
    }

    void tokenize(const string& code) {
        tokens_list.clear();
        string lexeme;
        size_t i = 0;

        while (i < code.size()) {
            char ch = code[i];

            if (isspace(ch)) {
                if (!lexeme.empty()) process_lexeme(lexeme);
                lexeme.clear();
                i++;
                continue;
            }

            if (ch == '"' || ch == '\'') {
                if (!lexeme.empty()) process_lexeme(lexeme);
                lexeme.clear();

                char quote = ch;
                string string_content(1, quote);
                i++;

                while (i < code.size() && code[i] != quote) {
                    string_content += code[i];
                    i++;
                }
                if (i < code.size()) {
                    string_content += code[i];
                    tokens_list.emplace_back("String", string_content);
                } else {
                    errors.push_back("Unterminated string: " + string_content);
                }
                i++;
                continue;
            }

            if (find(operators.begin(), operators.end(), string(1, ch)) != operators.end()) {
                if (!lexeme.empty()) process_lexeme(lexeme);
                lexeme.clear();

                string op(1, ch);
                if (i + 1 < code.size() && find(operators.begin(), operators.end(), op + code[i + 1]) != operators.end()) {
                    op += code[i + 1];
                    i++;
                }
                tokens_list.emplace_back("Operator", op);
                i++;
                continue;
            }

            if (find(punctuation.begin(), punctuation.end(), string(1, ch)) != punctuation.end()) {
                if (!lexeme.empty()) process_lexeme(lexeme);
                lexeme.clear();
                tokens_list.emplace_back("Punctuation", string(1, ch));
                i++;
                continue;
            }

            lexeme += ch;
            i++;
        }

        if (!lexeme.empty()) process_lexeme(lexeme);
    }

    void process_lexeme(const string& lexeme) {
        if (find(keywords.begin(), keywords.end(), lexeme) != keywords.end()) {
            tokens_list.emplace_back("Keyword", lexeme);
        } else if (isdigit(lexeme[0]) || (lexeme[0] == '.' && lexeme.size() > 1)) {
            tokens_list.emplace_back("Constant", lexeme);
        } else if (is_valid_identifier(lexeme)) {
            tokens_list.emplace_back("Identifier", lexeme);
        } else {
            errors.push_back("Invalid lexeme: " + lexeme);
        }
    }

    void populate_symbol_table() {
        for (size_t i = 0; i < tokens_list.size(); i++) {
            if (tokens_list[i].first == "Keyword" && find(type_keywords.begin(), type_keywords.end(), tokens_list[i].second) != type_keywords.end()) {
                if (i + 1 < tokens_list.size() && tokens_list[i + 1].first == "Identifier") {
                    string identifier = tokens_list[i + 1].second;
                    if (find(symbol_table.begin(), symbol_table.end(), identifier) == symbol_table.end()) {
                        symbol_table.push_back(identifier);
                    }
                }
            }
        }
    }

    void analyze(const string& code) {
        string cleaned_code = remove_comments(code);
        tokenize(cleaned_code);
        populate_symbol_table();

        cout << "TOKENS" << endl;
        for (const auto& token : tokens_list) {
            cout << token.first << ": " << token.second << endl;
        }

        if (!errors.empty()) {
            cout << "\nLEXICAL ERRORS" << endl;
            for (const auto& error : errors) {
                cout << error << endl;
            }
        }

        cout << "\nSYMBOL TABLE ENTRIES" << endl;
        for (size_t i = 0; i < symbol_table.size(); i++) {
            cout << i + 1 << ") " << symbol_table[i] << endl;
        }
    }
};

int main() {
    ifstream file("input_3.c");
    if (!file) {
        cerr << "Error: File 'input.c' not found." << endl;
        return 1;
    }

    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    LexicalAnalyzer analyzer;
    analyzer.analyze(code);

    return 0;
}

