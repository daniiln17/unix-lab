#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx; // для синхронизации вывода

//--------- Команды ---------
class Cmd {
public:
    virtual void run() = 0;
    virtual ~Cmd() {}
};

// print текст
class Print : public Cmd {
    string s;
public:
    Print(string t) : s(t) {}
    void run() override {
        lock_guard<mutex> lock(mtx);
        cout << s << endl;
    }
};

// save файл текст
class Save : public Cmd {
    string f, t;
public:
    Save(string ff, string tt) : f(ff), t(tt) {}
    void run() override {
        ofstream file(f, ios::app);
        file << t << endl;
    }
};

// math a op b
class Math : public Cmd {
    double a, b; char op;
public:
    Math(double x, char o, double y) : a(x), op(o), b(y) {}
    void run() override {
        double r;
        if (op == '+') r = a + b;
        else if (op == '-') r = a - b;
        else if (op == '*') r = a * b;
        else r = a / b;
        lock_guard<mutex> lock(mtx);
        cout << a << op << b << "=" << r << endl;
    }
};

// for N { команды }
class For : public Cmd {
    int n;
    vector<Cmd*> body;
public:
    For(int nn, vector<Cmd*> b) : n(nn), body(b) {}
    void run() override {
        for (int i = 0; i < n; i++)
            for (auto c : body) c->run();
    }
};

//--------- Парсер строки ---------
vector<Cmd*> parse(string s) {
    vector<Cmd*> cmds;
    stringstream ss(s);
    string w;
    while (ss >> w) {
        if (w == "print") {
            string t; getline(ss, t);
            cmds.push_back(new Print(t.substr(1)));
        }
        else if (w == "save") {
            string f, t; ss >> f; getline(ss, t);
            cmds.push_back(new Save(f, t.substr(1)));
        }
        else if (w == "math") {
            double a, b; char op; ss >> a >> op >> b;
            cmds.push_back(new Math(a, op, b));
        }
        else if (w == "for") {
            int n; string brace, rest;
            ss >> n >> brace;
            getline(ss, rest, '}');
            cmds.push_back(new For(n, parse(rest)));
        }
    }
    return cmds;
}

//--------- main ---------
int main() {
    vector<string> lines;
    string line;

    cout << "Вводите строки. run - запустить, exit - выход" << endl;

    while (getline(cin, line)) {
        if (line == "run") {
            vector<thread> ths;
            for (int i = 0; i < (int)lines.size(); i++) {
                ths.emplace_back([i, &lines]() {
                    auto cmds = parse(lines[i]);
                    lock_guard<mutex> lock(mtx);
                    cout << "[Поток " << i+1 << "] старт" << endl;
                    mtx.unlock();
                    for (auto c : cmds) c->run();
                    mtx.lock();
                    cout << "[Поток " << i+1 << "] финиш" << endl;
                    for (auto c : cmds) delete c;
                });
            }
            for (auto& t : ths) t.join();
            lines.clear();
            cout << "Готово." << endl;
        }
        else if (line == "exit") break;
        else if (!line.empty()) lines.push_back(line);
    }
}
