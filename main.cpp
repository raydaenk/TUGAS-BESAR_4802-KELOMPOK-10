#include <iostream>
#include <string>
#include "MLIST.h"
using namespace std;


int main() {
    Film* filmList = nullptr;
    Actor* actorList = nullptr;

    int choice;

    while (true) {
        cout << "\n=========== MENU =============\n";
        cout << "1. Tambahkan Film\n";
        cout << "2. Tambahkan Aktor + Buat Relasi\n";
        cout << "3. Hapus Film (ID)\n";
        cout << "4. Hapus Aktor (ID)\n";
        cout << "5. Tampilkan aktor dalam film\n";
        cout << "6. Tampilkan film dari aktor\n";
        cout << "7. Update performa aktor\n";
        cout << "8. Aktor dengan performa terbaik\n";
        cout << "9. Insert Film by Condition\n";
        cout << "10. Insert Actor by Condition\n";
        cout << "11. Delete film by condition\n";
        cout << "12. Delete actor by condition\n";
        cout << "13. Searching film (tahun > ...)\n";
        cout << "14. Komputasi statistik\n";
        cout << "15. Assign aktor yang belum punya film\n";
        cout << "16. Tampilkan semua film\n";
        cout << "17. Tampilkan semua aktor\n";
        cout << "18. Jalankan Studi Kasus\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;
        cout << "\n";

        if (choice == 0) break;

        else if (choice == 1) {
            int id, year;
            string title;
            cout << "ID: ";
            cin >> id;

            if (findFilm(filmList, id) != nullptr) {
                cout << "Film dengan ID tersebut sudah ada.\n";
                continue;
            }

            cout << "Title: ";
            cin.ignore();
            getline(cin, title);

            cout << "Year: ";
            cin >> year;

            insertFilm(filmList, createFilm(id, title, year));
            cout << "Film berhasil ditambahkan.\n";
        }

        else if (choice == 2) {
            int id, age;
            string name;

            cout << "ID Aktor: ";
            cin >> id;

            if (findActor(actorList, id) != nullptr) {
                cout << "Aktor dengan ID tersebut sudah ada.\n";
                continue;
            }

            cout << "Nama: ";
            cin.ignore();
            getline(cin, name);

            cout << "Usia: ";
            cin >> age;

            Actor* A = createActor(id, name, age);
            insertActor(actorList, A);

            cout << "Pilih ID film (0 = skip): ";
            int fid;
            cin >> fid;

            if (fid != 0) {
                Film* F = findFilm(filmList, fid);

                if (!F) cout << "Film tidak ditemukan.\n";
                else {
                    if (actorAlreadyLinked(F, A)) {
                        cout << "Aktor sudah ada di film ini.\n";
                    } else {
                        connectFilmActor(F, A);
                        cout << "Relasi berhasil dibuat.\n";
                    }
                }
            }
        }

        else if (choice == 3) {
            int id;
            cout << "ID Film: ";
            cin >> id;

            Film* f = findFilm(filmList, id);
            if (!f) cout << "Film tidak ditemukan.\n";
            else {
                deleteFilm(filmList, f);
                cout << "Film berhasil dihapus.\n";
            }
        }

        else if (choice == 4) {
            int id;
            cout << "ID Aktor: ";
            cin >> id;

            Actor* a = findActor(actorList, id);
            if (!a) cout << "Aktor tidak ditemukan.\n";
            else {
                deleteActor(actorList, a);
                cout << "Aktor berhasil dihapus.\n";
            }
        }

        else if (choice == 5) {
            int id;
            cout << "ID Film: ";
            cin >> id;

            Film* f = findFilm(filmList, id);
            if (!f) cout << "Film tidak ditemukan.\n";
            else showActorsInFilm(f);
        }

        else if (choice == 6) {
            int id;
            cout << "ID Aktor: ";
            cin >> id;

            Actor* a = findActor(actorList, id);
            if (!a) cout << "Aktor tidak ditemukan.\n";
            else showFilmsOfActor(a);
        }

        else if (choice == 7) {
            int id, perf;
            cout << "ID Aktor: ";
            cin >> id;

            Actor* a = findActor(actorList, id);
            if (!a) cout << "Aktor tidak ditemukan.\n";
            else {
                cout << "Nilai performa: ";
                cin >> perf;
                a->performance = perf;
                cout << "Performa diperbarui.\n";
            }
        }

        else if (choice == 8) {
            if (!actorList) {
                cout << "Tidak ada aktor.\n";
            } else {
                Actor* best = actorList;
                Actor* p = actorList->next;

                while (p != nullptr) {
                    if (p->performance > best->performance)
                        best = p;
                    p = p->next;
                }

                cout << "Aktor terbaik: "
                     << best->name << " (Perf: "
                     << best->performance << ")\n";
            }
        }

        else if (choice == 9) {
            int id, year;
            string title;

            cout << "ID Film: ";
            cin >> id;

            if (findFilm(filmList, id) != nullptr) {
                cout << "Film dengan ID tersebut sudah ada.\n";
                continue;
            }

            cout << "Judul Film: ";
            cin.ignore();
            getline(cin, title);

            cout << "Tahun: ";
            cin >> year;

            insertFilmByCondition(filmList, createFilm(id, title, year));
            cout << "Film dimasukkan sesuai urutan.\n";
        }

        else if (choice == 10) {
            int id, age;
            string name;

            cout << "ID Aktor: ";
            cin >> id;

            if (findActor(actorList, id) != nullptr) {
                cout << "Aktor dengan ID tersebut sudah ada.\n";
                continue;
            }

            cout << "Nama Aktor: ";
            cin.ignore();
            getline(cin, name);

            cout << "Usia: ";
            cin >> age;

            insertActorByCondition(actorList, createActor(id, name, age));
            cout << "Aktor dimasukkan sesuai urutan.\n";
        }

        else if (choice == 11) {
            int limit;
            cout << "Hapus film dengan tahun < ";
            cin >> limit;

            deleteFilmByCondition(filmList, limit);
            cout << "Film berhasil dihapus berdasarkan kondisi.\n";
        }

        else if (choice == 12) {
            int limit;
            cout << "Hapus aktor dengan usia > ";
            cin >> limit;

            deleteActorByCondition(actorList, limit);
            cout << "Aktor berhasil dihapus berdasarkan kondisi.\n";
        }

        else if (choice == 13) {
            searchByCondition(filmList, actorList);
        }

        else if (choice == 14) {
            computeStatistics(filmList, actorList);
        }

        else if (choice == 15) {
            cout << "\n=== Assign Aktor yang Belum Punya Film ===\n";

            showAllActors(actorList);

            int actorID;
            cout << "Masukkan ID aktor: ";
            cin >> actorID;

            Actor* a = findActor(actorList, actorID);
            if (!a) {
                cout << "Aktor tidak ditemukan.\n";
                continue;
            }

            if (actorHasFilm(a)) {
                cout << "Aktor ini sudah memiliki film.\n";
                continue;
            }

            cout << "\nPilih Film Tujuan:\n";
            showAllFilms(filmList);

            int filmID;
            cout << "Masukkan ID Film: ";
            cin >> filmID;

            Film* f = findFilm(filmList, filmID);
            if (!f) cout << "Film tidak ditemukan.\n";
            else {
                if (actorAlreadyLinked(f, a)) {
                    cout << "Aktor sudah ada di film tersebut.\n";
                } else {
                    connectFilmActor(f, a);
                    cout << "Aktor berhasil di-assign.\n";
                }
            }
        }

        else if (choice == 16) {
            cout << "\n=== SEMUA FILM ===\n";
            showAllFilms(filmList);
        }

        else if (choice == 17) {
            cout << "\n=== SEMUA AKTOR ===\n";
            showAllActors(actorList);
        }

        else if (choice == 18) {
            menuStudiKasus(filmList, actorList);
        }
    }

    return 0;
}
