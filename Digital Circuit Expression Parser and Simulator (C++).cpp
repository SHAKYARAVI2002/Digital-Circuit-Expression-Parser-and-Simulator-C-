
#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

// Helper to get precedence
int precedence(string op) {
    if (op == "NOT") return 3;
    if (op == "AND") return 2;
    if (op == "OR") return 1;
    return 0;
}

// Check if operator
bool isOperator(const string& token) {
    return token == "AND" || token == "OR" || token == "NOT";
}

// Infix to Postfix conversion
vector<string> infixToPostfix(vector<string> tokens) {
    vector<string> output;
    stack<string> opStack;
    for (auto& token : tokens) {
        if (token == "(") {
            opStack.push(token);
        } else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.pop(); // remove '('
        } else if (isOperator(token)) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(token)) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        } else {
            output.push_back(token); // operand
        }
    }
    while (!opStack.empty()) {
        output.push_back(opStack.top());
        opStack.pop();
    }
    return output;
}

// Evaluate postfix for given values
bool evalPostfix(const vector<string>& postfix, map<char, bool> values) {
    stack<bool> st;
    for (auto& token : postfix) {
        if (token == "AND" || token == "OR") {
            bool b = st.top(); st.pop();
            bool a = st.top(); st.pop();
            st.push(token == "AND" ? a & b : a | b);
        } else if (token == "NOT") {
            bool a = st.top(); st.pop();
            st.push(!a);
        } else {
            st.push(values[token[0]]);
        }
    }
    return st.top();
}

// Tokenizer for string
vector<string> tokenize(string expr) {
    vector<string> tokens;
    string token;
    for (size_t i = 0; i < expr.size(); ++i) {
        if (isspace(expr[i])) continue;
        if (expr[i] == '(' || expr[i] == ')') {
            tokens.push_back(string(1, expr[i]));
        } else if (isalpha(expr[i])) {
            token = string(1, expr[i]);
            while (i+1 < expr.size() && isalpha(expr[i+1])) {
                token += expr[++i];
            }
            transform(token.begin(), token.end(), token.begin(), ::toupper);
            tokens.push_back(token);
        }
    }
    return tokens;
}

int main() {
    string expr;
    cout << "Enter boolean expression (use A, B, C and AND, OR, NOT): ";
    getline(cin, expr);

    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);

    cout << "\nTruth Table for Expression: " << expr << "\n";
    cout << "A B C | Output\n";
    cout << "--------------\n";

    for (int a = 0; a <= 1; ++a)
        for (int b = 0; b <= 1; ++b)
            for (int c = 0; c <= 1; ++c) {
                map<char, bool> vals = {{'A', a}, {'B', b}, {'C', c}};
                bool res = evalPostfix(postfix, vals);
                cout << a << " " << b << " " << c << " |   " << res << "\n";
            }

    return 0;
}
