#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Умножение через сложение
double multiply(double a, double b) {
    double result = 0;
    bool negative = false;

    if (b < 0) {
        b = -b;
        negative = true;
    }

    for (int i = 0; i < (int)b; i++) {
        result += a;
    }

    // Учёт дробной части (грубо, для демонстрации)
    double frac = b - (int)b;
    if (frac > 0) {
        result += a * frac;
    }

    return negative ? -result : result;
}

// Возведение в степень через умножение сложением
double power(double base, double exp) {
    if (exp == 0) return 1;
    if (exp < 0) return 1.0 / power(base, -exp);

    double result = 1;
    for (int i = 0; i < (int)exp; i++) {
        result = multiply(result, base);
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Использование: calc <число1> <оператор> <число2>" << endl;
        cout << "Операторы: +, -, ^" << endl;
        return 1;
    }

    double a = stod(argv[1]);
    string op = argv[2];
    double b = stod(argv[3]);
    double result;

    if (op == "+") {
        result = a + b;
    } else if (op == "-") {
        result = a - b;
    } else if (op == "^") {
        result = power(a, b);
    } else {
        cout << "Неизвестный оператор: " << op << endl;
        cout << "Допустимые: +, -, ^" << endl;
        return 1;
    }

    cout << a << " " << op << " " << b << " = " << result << endl;
    return 0;
}

