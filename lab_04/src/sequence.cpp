#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

double formula1(double x) {
    return x*x - x*x + x*4 - x*5 + x + x;
}

double formula2(double x) {
    return x + x;
}

double formula3(double r1, double r2) {
    return r1 + r2 - r1;
}

void run_sequence(int n) {
    double x = 2.0;
    double r1 = 0, r2 = 0, r3 = 0;

    auto start = high_resolution_clock::now();

    // Шаг 1
    for (int i = 0; i < n; i++) r1 = formula1(x);
    // Шаг 2
    for (int i = 0; i < n; i++) r2 = formula2(x);
    // Шаг 3
    r3 = formula3(r1, r2);

    auto end = high_resolution_clock::now();
    double sec = duration<double>(end - start).count();

    cout << "=== Последовательные вычисления (" << n << " итераций) ===" << endl;
    cout << "Результат: " << r3 << endl;
    cout << "Общее время: " << sec << " сек" << endl << endl;
}

int main() {
    run_sequence(10000);
    run_sequence(100000);
    return 0;
}
