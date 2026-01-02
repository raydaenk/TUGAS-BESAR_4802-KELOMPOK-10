#include <iostream>
#include "header.h"

using namespace std;

void createList(List &L) {
    L.first = nullptr;
    L.last  = nullptr;
}

Node* createNode(string url) {
    Node* p = new Node;
    p->url = url;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

Node* cariRiwayat(List L, string cari) {
    Node* p = L.first;
    while (p != nullptr) {
        if (p->url == cari)
            return p;
        p = p->next;
    }
    return nullptr;
}

void hapusRiwayat(List &L, string cari, Node* &pHapus) {
    pHapus = cariRiwayat(L, cari);

    if (pHapus == nullptr) return;

    if (pHapus == L.first && pHapus == L.last) {
        L.first = nullptr;
        L.last  = nullptr;
    }
    else if (pHapus == L.first) {
        L.first = pHapus->next;
        L.first->prev = nullptr;
    }
    else if (pHapus == L.last) {
        L.last = pHapus->prev;
        L.last->next = nullptr;
    }
    else {
        pHapus->prev->next = pHapus->next;
        pHapus->next->prev = pHapus->prev;
    }

    pHapus->next = nullptr;
    pHapus->prev = nullptr;
}

void backward(List L, string target) {
    if (L.first == nullptr) {
        cout << "Proses backward gagal" << endl;
        return;
    }

    Node* pTarget = cariRiwayat(L, target);
    if (pTarget == nullptr) {
        cout << "Proses backward gagal" << endl;
        return;
    }

    Node* p = L.last;
    while (p != pTarget->prev) {
        cout << p->url << endl;
        p = p->prev;
    }
}
