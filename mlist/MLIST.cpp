#include "MLIST.h"
#include <iostream>
#include <string>
using namespace std;

Film* createFilm(int id, string title, int year) {
    Film* f = new Film;
    f->id = id;
    f->title = title;
    f->year = year;
    f->next = nullptr;
    f->relHead = nullptr;
    return f;
}

Actor* createActor(int id, string name, int age) {
    Actor* a = new Actor;
    a->id = id;
    a->name = name;
    a->age = age;
    a->performance = 0;
    a->next = nullptr;
    a->relHead = nullptr;
    return a;
}


void insertFilm(Film* &head, Film* newFilm) {
    newFilm->next = head;
    head = newFilm;
}

void insertActor(Actor* &head, Actor* newActor) {
    newActor->next = head;
    head = newActor;
}

Film* findFilm(Film* head, int id) {
    while (head != nullptr) {
        if (head->id == id) return head;
        head = head->next;
    }
    return nullptr;
}

Actor* findActor(Actor* head, int id) {
    while (head != nullptr) {
        if (head->id == id) return head;
        head = head->next;
    }
    return nullptr;
}


Relation* connectFilmActor(Film* f, Actor* a) {
    Relation* r = new Relation;
    r->filmNode = f;
    r->actorNode = a;

    r->nextFilm = f->relHead;
    f->relHead = r;

    r->nextActor = a->relHead;
    a->relHead = r;

    return r;
}


void deleteFilm(Film* &head, Film* target) {

    Relation* r = target->relHead;
    while (r != nullptr) {
        Relation* next = r->nextFilm;

        Relation* ra = r->actorNode->relHead;
        Relation* prev = nullptr;

        while (ra != nullptr) {
            if (ra == r) {
                if (prev == nullptr)
                    r->actorNode->relHead = ra->nextActor;
                else
                    prev->nextActor = ra->nextActor;
                break;
            }
            prev = ra;
            ra = ra->nextActor;
        }

        delete r;
        r = next;
    }

    if (head == target) head = target->next;
    else {
        Film* p = head;
        while (p->next != nullptr && p->next != target)
            p = p->next;
        p->next = target->next;
    }
    delete target;
}


void deleteActor(Actor* &head, Actor* target) {

    Relation* r = target->relHead;
    while (r != nullptr) {
        Relation* next = r->nextActor;

        Relation* rf = r->filmNode->relHead;
        Relation* prev = nullptr;

        while (rf != nullptr) {
            if (rf == r) {
                if (prev == nullptr)
                    r->filmNode->relHead = rf->nextFilm;
                else
                    prev->nextFilm = rf->nextFilm;
                break;
            }
            prev = rf;
            rf = rf->nextFilm;
        }

        delete r;
        r = next;
    }

    if (head == target) head = target->next;
    else {
        Actor* p = head;
        while (p->next != nullptr && p->next != target)
            p = p->next;
        p->next = target->next;
    }
    delete target;
}

void showAllFilms(Film* head) {
    while (head != nullptr) {
        cout << head->id << " - " << head->title
             << " (" << head->year << ")\n";
        head = head->next;
    }
}

void showAllActors(Actor* head) {
    while (head != nullptr) {
        cout << head->id << " - " << head->name
             << " | Age: " << head->age
             << " | Perf: " << head->performance << "\n";
        head = head->next;
    }
}

void showActorsInFilm(Film* f) {
    cout << "Aktor di film: " << f->title << "\n";
    Relation* r = f->relHead;
    while (r != nullptr) {
        cout << "- " << r->actorNode->name << "\n";
        r = r->nextFilm;
    }
}

void showFilmsOfActor(Actor* a) {
    cout << "Film dari aktor: " << a->name << "\n";
    Relation* r = a->relHead;
    while (r != nullptr) {
        cout << "- " << r->filmNode->title << "\n";
        r = r->nextActor;
    }
}



void insertFilmByCondition(Film* &head, Film* newFilm) {
    if (head == nullptr || newFilm->year < head->year) {
        newFilm->next = head;
        head = newFilm;
        return;
    }
    Film* p = head;
    while (p->next != nullptr && p->next->year <= newFilm->year)
        p = p->next;

    newFilm->next = p->next;
    p->next = newFilm;
}

void insertActorByCondition(Actor* &head, Actor* newActor) {
    if (head == nullptr || newActor->age > head->age) {
        newActor->next = head;
        head = newActor;
        return;
    }
    Actor* p = head;
    while (p->next != nullptr && p->next->age >= newActor->age)
        p = p->next;

    newActor->next = p->next;
    p->next = newActor;
}

void deleteFilmByCondition(Film* &head, int yearLimit) {
    Film* curr = head;
    while (curr != nullptr) {
        Film* next = curr->next;
        if (curr->year < yearLimit)
            deleteFilm(head, curr);
        curr = next;
    }
}

void deleteActorByCondition(Actor* &head, int ageLimit) {
    Actor* curr = head;
    while (curr != nullptr) {
        Actor* next = curr->next;
        if (curr->age > ageLimit)
            deleteActor(head, curr);
        curr = next;
    }
}


void searchByCondition(Film* filmHead, Actor* actorHead) {
    int year;
    cout << "Cari film dengan tahun > ";
    cin >> year;

    while (filmHead != nullptr) {
        if (filmHead->year > year)
            cout << "- " << filmHead->title << "\n";
        filmHead = filmHead->next;
    }
}

void computeStatistics(Film* filmHead, Actor* actorHead) {
    int filmCount = 0;
    int actorCount = 0;

    while (filmHead != nullptr) {
        filmCount++;
        filmHead = filmHead->next;
    }

    while (actorHead != nullptr) {
        actorCount++;
        actorHead = actorHead->next;
    }

    cout << "Total Film = " << filmCount << endl;
    cout << "Total Aktor = " << actorCount << endl;
}


void displayAllParents(Film* head) {
    showAllFilms(head);
    }

bool actorHasFilm(Actor* a) {
    return (a->relHead != nullptr);
}

void showUnassignedActors(Actor* head) {
    cout << "\n=== Aktor yang Belum Bermain di Film Manapun ===\n";
    bool found = false;

    Actor* p = head;
    while (p != nullptr) {
        if (!actorHasFilm(p)) {
            cout << "ID: " << p->id
                 << " | Nama: " << p->name
                 << " | Usia: " << p->age << endl;
            found = true;
        }
        p = p->next;
    }

    if (!found) cout << "(Semua aktor sudah memiliki film)\n";
}

bool actorAlreadyLinked(Film* f, Actor* a) {
    Relation* r = f->relHead;
    while (r != nullptr) {
        if (r->actorNode == a) return true;
        r = r->nextFilm;
    }
    return false;
}


void menuStudiKasus(Film* &filmList, Actor* &actorList) {
    cout << "\n========== STUDI KASUS ==========\n";

    insertFilmByCondition(filmList, createFilm(501, "Avatar", 2009));
    insertFilmByCondition(filmList, createFilm(502, "Avengers", 2012));
    insertFilmByCondition(filmList, createFilm(503, "The Matrix", 1999));

    insertActorByCondition(actorList, createActor(601, "Keanu Reeves", 55));
    insertActorByCondition(actorList, createActor(602, "Robert Downey Jr.", 54));
    insertActorByCondition(actorList, createActor(603, "Sam Worthington", 48));

    connectFilmActor(findFilm(filmList, 501), findActor(actorList, 603));
    connectFilmActor(findFilm(filmList, 502), findActor(actorList, 602));
    connectFilmActor(findFilm(filmList, 503), findActor(actorList, 601));

    cout << "\n>>> Setelah insert otomatis\n";
    showAllFilms(filmList);
    cout << endl;
    showAllActors(actorList);

    cout << "\n>>> Searching film tahun > 2000\n";
    Film* p = filmList;
    while (p != nullptr) {
        if (p->year > 2000)
            cout << "- " << p->title << endl;
        p = p->next;
    }

    cout << "\n>>> Statistik\n";
    computeStatistics(filmList, actorList);

    cout << "\n>>> Hapus film tahun < 2005\n";
    deleteFilmByCondition(filmList, 2005);

    cout << "\n>>> Hapus aktor usia > 53\n";
    deleteActorByCondition(actorList, 53);

    cout << "\n>>> Data Film (Final):\n";
    showAllFilms(filmList);

    cout << "\n>>> Data Aktor (Final):\n";
    showAllActors(actorList);

    cout << "\n========== SELESAI STUDI KASUS ==========\n";
}
