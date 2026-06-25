#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

double formula1(double x) { return x*x - x*x + x*4 - x*5 + x + x; }
double formula2(double x) { return x + x; }
double formula3(double r1, double r2) { return r1 + r2 - r1; }

void run_threads(int n) {
    double x = 2.0;
    double r1 = 0, r2 = 0, r3 = 0;

    auto t1_start = high_resolution_clock::now();
    thread th1([&]() { for (int i = 0; i < n; i++) r1 = formula1(x); });
    auto t2_start = high_resolution_clock::now();
    thread th2([&]() { for (int i = 0; i < n; i++) r2 = formula2(x); });

    th1.join();
    auto t1_end = high_resolution_clock::now();
    th2.join();
    auto t2_end = high_resolution_clock::now();

    auto t3_start = high_resolution_clock::now();
    r3 = formula3(r1, r2);
    auto t3_end = high_resolution_clock::now();

    double sec1 = duration<double>(t1_end - t1_start).count();
    double sec2 = duration<double>(t2_end - t2_start).count();
    double sec3 = duration<double>(t3_end - t3_start).count();

    cout << "=== Параллельные вычисления (потоки, " << n << " итераций) ===" << endl;
    cout << "Результат: " << r3 << endl;
    cout << "Шаг 1: " << sec1 << " сек" << endl;
    cout << "Шаг 2: " << sec2 << " сек" << endl;
    cout << "Шаг 3: " << sec3 << " сек" << endl;
    cout << "Общее время: " << (sec1 + sec2 + sec3) << " сек" << endl << endl;
}

int main() {
    run_threads(10000);
    run_threads(100000);
    return 0;
}
