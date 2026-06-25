#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

double compute(double x) {
    return x*x - x*x + x*4 - x*5 + x + x;
}

int main() {
    string input;

    while (true) {
        cout << "Введите количество итераций (или не число для выхода): ";
        cin >> input;

        bool is_number = true;
        for (char c : input) {
            if (!isdigit(c) && c != '-') {
                is_number = false;
                break;
            }
        }

        if (!is_number) {
            cout << "Введено не число. Завершение программы." << endl;
            break;
        }

        int n = stoi(input);
        if (n <= 0) {
            cout << "Число должно быть положительным. Попробуйте снова." << endl;
            continue;
        }

        double x = 2.0;
        auto start = high_resolution_clock::now();

        for (int i = 0; i < n; i++) {
            compute(x);
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        cout << "Выполнено " << n << " итераций за " << duration.count() << " микросекунд" << endl;
        cout << "Среднее время на итерацию: " << (double)duration.count() / n << " мкс" << endl;
    }

    return 0;
}
