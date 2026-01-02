#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;
struct Panen {
    string namaTanaman;
    string bulanPanen;
    int jumlahPanen;
};

struct Node {
    Panen info;
    Node* next;
};

struct List {
    Node* FIRST;
};

void createList(List &L);
Node* createNewElm(Panen x);
void insertFirst(List &L, Panen x);
Node* panenTerbanyak(List L);
void panenBulanan(List L, std::string bulan);


#endif // HEADER_H_INCLUDED
