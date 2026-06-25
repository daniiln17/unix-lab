#include <iostream>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <cstring>

using namespace std;
using namespace std::chrono;

double formula1(double x) { return x*x - x*x + x*4 - x*5 + x + x; }
double formula2(double x) { return x + x; }
double formula3(double r1, double r2) { return r1 + r2 - r1; }

void run_processes(int n) {
    double x = 2.0;

    // Общая память для результатов
    double* shared = (double*)mmap(nullptr, 2 * sizeof(double),
                                    PROT_READ | PROT_WRITE,
                                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    auto t1_start = high_resolution_clock::now();

    pid_t pid1 = fork();
    if (pid1 == 0) {
        double r = 0;
        for (int i = 0; i < n; i++) r = formula1(x);
        shared[0] = r;
        exit(0);
    }

    auto t2_start = high_resolution_clock::now();

    pid_t pid2 = fork();
    if (pid2 == 0) {
        double r = 0;
        for (int i = 0; i < n; i++) r = formula2(x);
        shared[1] = r;
        exit(0);
    }

    waitpid(pid1, nullptr, 0);
    auto t1_end = high_resolution_clock::now();

    waitpid(pid2, nullptr, 0);
    auto t2_end = high_resolution_clock::now();

    double r1 = shared[0];
    double r2 = shared[1];
    munmap(shared, 2 * sizeof(double));

    auto t3_start = high_resolution_clock::now();
    double r3 = formula3(r1, r2);
    auto t3_end = high_resolution_clock::now();

    double sec1 = duration<double>(t1_end - t1_start).count();
    double sec2 = duration<double>(t2_end - t2_start).count();
    double sec3 = duration<double>(t3_end - t3_start).count();

    cout << "=== Параллельные вычисления (процессы, " << n << " итераций) ===" << endl;
    cout << "Результат: " << r3 << endl;
    cout << "Шаг 1: " << sec1 << " сек" << endl;
    cout << "Шаг 2: " << sec2 << " сек" << endl;
    cout << "Шаг 3: " << sec3 << " сек" << endl;
    cout << "Общее время: " << (sec1 + sec2 + sec3) << " сек" << endl << endl;
}

int main() {
    run_processes(10000);
    run_processes(100000);
    return 0;
}
