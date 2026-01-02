#include <iostream>
#include "header.h"

using namespace std;

int main() {
    List L;
    createList(L);

    Panen p1 = {"Padi", "Maret", 1000};
    Panen p2 = {"Jagung", "Maret", 790};
    Panen p3 = {"Labu", "Maret", 550};
    Panen p4 = {"Padi", "Februari", 850};
    Panen p5 = {"Wortel", "Januari", 500};

    insertFirst(L, p5);
    insertFirst(L, p4);
    insertFirst(L, p3);
    insertFirst(L, p2);
    insertFirst(L, p1);

    cout << "Tanaman yang dipanen bulan Maret:" << endl;
    panenBulanan(L, "Maret");

    Node* maks = panenTerbanyak(L);
    if (maks != nullptr) {
        cout << "\nPanen terbanyak:" << endl;
        cout << "Tanaman : " << maks->info.namaTanaman << endl;
        cout << "Bulan   : " << maks->info.bulanPanen << endl;
        cout << "Jumlah  : " << maks->info.jumlahPanen << endl;
    }

    return 0;
}
