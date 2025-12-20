#include <iostream>
#include <string>
#include "MLIST.h"
using namespace std;


int main() {
    Film* filmList = nullptr;
    Actor* actorList = nullptr;

    int choice;

    insertFilmByCondition(filmList, createFilm(101, "The Matrix", 1999));
    insertFilmByCondition(filmList, createFilm(102, "Inception", 2010));
    insertFilmByCondition(filmList, createFilm(103, "Interstellar", 2014));
    insertFilmByCondition(filmList, createFilm(104, "Titanic", 1997));
    insertFilmByCondition(filmList, createFilm(105, "Avengers: Endgame", 2019));
    insertFilmByCondition(filmList, createFilm(106, "Joker", 2019));
    insertFilmByCondition(filmList, createFilm(107, "Gladiator", 2000));
    insertFilmByCondition(filmList, createFilm(108, "Parasite", 2019));
    insertFilmByCondition(filmList, createFilm(109, "The Dark Knight", 2008));
    insertFilmByCondition(filmList, createFilm(110, "Forrest Gump", 1994));

    // --- AKTOR (5) ---
    insertActorByCondition(actorList, createActor(201, "Keanu Reeves", 58));
    insertActorByCondition(actorList, createActor(202, "Leonardo DiCaprio", 49));
    insertActorByCondition(actorList, createActor(203, "Robert Downey Jr.", 59));
    insertActorByCondition(actorList, createActor(204, "Joaquin Phoenix", 50));
    insertActorByCondition(actorList, createActor(205, "Tom Hanks", 67));

    while (true) {
        cout << "\n=========== MENU =============\n";
        cout << "1. Tambahkan Film\n";
        cout << "2. Tambahkan Aktor \n";
        cout << "3. Hapus Film (ID)\n";
        cout << "4. Hapus Aktor (ID)\n";
        cout << "5. Tampilkan aktor dalam film\n";
        cout << "6. Tampilkan film dari aktor\n";
        cout << "7. Update performa aktor\n";
        cout << "8. Aktor dengan performa terbaik\n";
        cout << "9. Delete film by condition\n";
        cout << "10. Delete actor by condition\n";
        cout << "11. Searching film (tahun > ...)\n";
        cout << "12. Komputasi statistik\n";
        cout << "13. Masukkan aktor ke dalam film \n";
        cout << "14. Tampilkan semua film\n";
        cout << "15. Tampilkan semua aktor\n";
        cout << "16. Jalankan Studi Kasus\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;
        cout << "\n";

        if (choice == 0) break;

        else if (choice == 1) {
            int id, year;
            string title;

            cout << "ID Film: ";
            cin >> id;

            if (findFilm(filmList, id)) {
                cout << "Film dengan ID tersebut sudah ada.\n";
                continue;
            }

            cout << "Judul Film: ";
            cin.ignore();
            getline(cin, title);

            cout << "Tahun Rilis: ";
            cin >> year;

            Film* f = createFilm(id, title, year);

            insertFilmByCondition(filmList, f);

            cout << "Film berhasil ditambahkan (otomatis terurut).\n";
        }


        else if (choice == 2) {
            int id, age;
            string name;

            cout << "ID Aktor: ";
            cin >> id;

            if (findActor(actorList, id)) {
                cout << "Aktor dengan ID tersebut sudah ada.\n";
                continue;
            }

            cout << "Nama Aktor: ";
            cin.ignore();
            getline(cin, name);

            cout << "Usia: ";
            cin >> age;

            Actor* a = createActor(id, name, age);

            insertActorByCondition(actorList, a);

            cout << "Aktor berhasil ditambahkan.\n";
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
            int limit;
            cout << "Hapus film dengan tahun < ";
            cin >> limit;

            deleteFilmByCondition(filmList, limit);
            cout << "Film berhasil dihapus berdasarkan kondisi.\n";
        }

        else if (choice == 10) {
            int limit;
            cout << "Hapus aktor dengan performa < ";
            cin >> limit;

            deleteActorByCondition(actorList, limit);
            cout << "Aktor Telah terhapus.\n";
        }

        else if (choice == 11) {
            searchByCondition(filmList, actorList);
        }

        else if (choice == 12) {
            computeStatistics(filmList, actorList);
        }

        else if (choice == 13) {
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

        else if (choice == 14) {
            cout << "\n=== SEMUA FILM ===\n";
            showAllFilms(filmList);
        }

        else if (choice == 15) {
            cout << "\n=== SEMUA AKTOR ===\n";
            showAllActors(actorList);
        }

        else if (choice == 16) {
            menuStudiKasus(filmList, actorList);
        }
    }

    return 0;
}
