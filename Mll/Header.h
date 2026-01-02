#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <string>
using namespace std;

struct Node {
    string url;
    Node* next;
    Node* prev;
};

struct List {
    Node* first;
    Node* last;
};

void createList(List &L);
Node* createNode(string url);
Node* cariRiwayat(List L, string cari);
void hapusRiwayat(List &L, string cari, Node* &pHapus);
void backward(List L, string target);
#endif // HEADER_H_INCLUDED
