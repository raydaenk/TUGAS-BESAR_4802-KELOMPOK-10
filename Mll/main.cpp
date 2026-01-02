#include <iostream>
#include "header.h"

using namespace std;

int main() {
    List L;
    createList(L);

    Node* a = createNode("google.com");
    Node* b = createNode("youtube.com");
    Node* c = createNode("github.com");
    Node* d = createNode("stackoverflow.com");

    L.first = a;
    a->next = b; b->prev = a;
    b->next = c; c->prev = b;
    c->next = d; d->prev = c;
    L.last = d;

    cout << "Backward sampai github.com:" << endl;
    backward(L, "github.com");

    Node* hapus;
    hapusRiwayat(L, "youtube.com", hapus);

    cout << "\nSetelah hapus youtube.com (Backward sampai google.com):" << endl;
    backward(L, "google.com");

    return 0;
}
