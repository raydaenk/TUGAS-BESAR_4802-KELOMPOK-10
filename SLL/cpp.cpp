#include "header.h"

void createList(List &L) {
    L.FIRST = nullptr;
}

Node* createNewElm(Panen x) {
    Node* p = new Node;
    p->info = x;
    p->next = nullptr;
    return p;
}


void insertFirst(List &L, Panen x) {
    Node* p = createNewElm(x);
    p->next = L.FIRST;
    L.FIRST = p;
}

Node* panenTerbanyak(List L) {
    if (L.FIRST == nullptr) {
        return nullptr;
    }

    Node* p = L.FIRST;
    Node* maks = p;

    while (p != nullptr) {
        if (p->info.jumlahPanen > maks->info.jumlahPanen) {
            maks = p;
        }
        p = p->next;
    }

    return maks;
}


void panenBulanan(List L, string bulan) {
    Node* p = L.FIRST;

    while (p != nullptr) {
        if (p->info.bulanPanen == bulan) {
            cout << p->info.namaTanaman << endl;
        }
        p = p->next;
    }
}
