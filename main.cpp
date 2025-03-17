#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <variant>

using namespace std;

using Value = variant<bool, int, string>;
unordered_map<string, Value> variables;

Value eval(const string& expr) {
    if (expr == "канешнбро") return true;
    if (expr == "пиздишь") return false;
    if (!expr.empty() && isdigit(expr[0])) return stoi(expr);
    if (!expr.empty() && expr[0] == '\'') {
        return expr.substr(1, expr.size() - 2);
    }

    if (variables.count(expr)) return variables[expr];
    return false;
}

void execute(const string& line) {
    if (line.empty()) return;

    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "сосал????нет") {
        string name, eq, value;
        ss >> name >> eq;
        getline(ss, value);
        value = value.substr(1);

        variables[name] = eval(value);
    } else if (cmd == "тыкто") {
        string value;
        ss >> value;
        Value result = eval(value);

        if (holds_alternative<bool>(result)) {
            cout << (get<bool>(result) ? "канешнбро" : "пиздишь") << endl;
        } else if (holds_alternative<int>(result)) {
            cout << get<int>(result) << endl;
        } else if (holds_alternative<string>(result)) {
            cout << get<string>(result) << endl;
        }
    } else {
        cout << "Ты долбаеб?" << endl;
    }
}

void runFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка: файл не найден" << endl;
        return;
    }

    string line;
    while (getline(file, line)) execute(line);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        runFile(argv[1]);
    } else {
        string line;
        while (getline(cin, line)) execute(line);
    }
    return 0;
}
