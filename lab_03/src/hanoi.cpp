#include <iostream>

using namespace std;

// Узел двусвязного списка
struct Node {
    int from;
    int to;
    Node* prev;
    Node* next;

    Node(int f, int t) : from(f), to(t), prev(nullptr), next(nullptr) {}
};

// Двусвязный список
struct DoublyLinkedList {
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(int from, int to) {
        Node* node = new Node(from, to);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void print() {
        Node* current = head;
        int step = 1;
        while (current) {
            cout << "Шаг " << step++ << ": Переместить кольцо со стержня "
                 << current->from << " на стержень " << current->to << endl;
            current = current->next;
        }
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }
};

// Рекурсивное решение Ханойской башни
void hanoi(int n, int from, int to, int aux, DoublyLinkedList& list) {
    if (n == 0) return;

    hanoi(n - 1, from, aux, to, list);
    list.append(from, to);
    hanoi(n - 1, aux, to, from, list);
}

int main() {
    int n = 8; // 8 колец по условию
    DoublyLinkedList moves;

    cout << "Ханойская башня (" << n << " колец)" << endl;
    cout << "Стержни: 1 (исходный), 2 (вспомогательный), 3 (целевой)" << endl;
    cout << endl;

    hanoi(n, 1, 3, 2, moves);

    moves.print();

    cout << endl;
    cout << "Общее число ходов: " << ((1 << n) - 1) << endl;

    // Освобождение памяти
    moves.clear();

    return 0;
}

