#include "MLIST.h"
#include <iostream>

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


void insertFilm(Film*& head, Film* newFilm) {
    newFilm->next = head;
    head = newFilm;
}

void insertActor(Actor*& head, Actor* newActor) {
    newActor->next = head;
    head = newActor;
}

void insertFilmByCondition(Film*& head, Film* newFilm) {
    if (!head || newFilm->year < head->year) {
        newFilm->next = head;
        head = newFilm;
        return;
    }
    Film* p = head;
    while (p->next && p->next->year <= newFilm->year)
        p = p->next;
    newFilm->next = p->next;
    p->next = newFilm;
}

void insertActorByCondition(Actor*& head, Actor* newActor) {
    if (!head || newActor->age > head->age) {
        newActor->next = head;
        head = newActor;
        return;
    }
    Actor* p = head;
    while (p->next && p->next->age >= newActor->age)
        p = p->next;
    newActor->next = p->next;
    p->next = newActor;
}


Film* findFilm(Film* head, int id) {
    while (head) {
        if (head->id == id) return head;
        head = head->next;
    }
    return nullptr;
}

Actor* findActor(Actor* head, int id) {
    while (head) {
        if (head->id == id) return head;
        head = head->next;
    }
    return nullptr;
}

Relation* connectFilmActor(Film* f, Actor* a) {
    if (!f || !a) return nullptr;

    Relation* r = new Relation;
    r->filmNode = f;
    r->actorNode = a;

    r->nextFilm = f->relHead;
    f->relHead = r;

    r->nextActor = a->relHead;
    a->relHead = r;

    return r;
}

bool actorAlreadyLinked(Film* f, Actor* a) {
    if (!f || !a) return false;
    Relation* r = f->relHead;
    while (r) {
        if (r->actorNode == a) return true;
        r = r->nextFilm;
    }
    return false;
}


void deleteFilm(Film*& head, Film* target) {
    if (!head || !target) return;

    Relation* r = target->relHead;
    while (r) {
        Relation* nextRel = r->nextFilm;

        Relation* ra = r->actorNode->relHead;
        Relation* prev = nullptr;
        while (ra) {
            if (ra == r) {
                if (!prev) r->actorNode->relHead = ra->nextActor;
                else prev->nextActor = ra->nextActor;
                break;
            }
            prev = ra;
            ra = ra->nextActor;
        }

        delete r;
        r = nextRel;
    }

    if (head == target) head = target->next;
    else {
        Film* p = head;
        while (p->next && p->next != target)
            p = p->next;
        if (p->next) p->next = target->next;
    }

    delete target;
}

void deleteActor(Actor*& head, Actor* target) {
    if (!head || !target) return;

    Relation* r = target->relHead;
    while (r) {
        Relation* nextRel = r->nextActor;

        Relation* rf = r->filmNode->relHead;
        Relation* prev = nullptr;
        while (rf) {
            if (rf == r) {
                if (!prev) r->filmNode->relHead = rf->nextFilm;
                else prev->nextFilm = rf->nextFilm;
                break;
            }
            prev = rf;
            rf = rf->nextFilm;
        }

        delete r;
        r = nextRel;
    }

    if (head == target) head = target->next;
    else {
        Actor* p = head;
        while (p->next && p->next != target)
            p = p->next;
        if (p->next) p->next = target->next;
    }

    delete target;
}

void deleteFilmByCondition(Film*& head, int yearLimit) {
    Film* curr = head;
    while (curr) {
        Film* next = curr->next;
        if (curr->year < yearLimit)
            deleteFilm(head, curr);
        curr = next;
    }
}

void deleteActorByCondition(Actor*& head, int limit) {
    Actor* curr = head;
    while (curr) {
        Actor* next = curr->next;
        if (curr->performance < limit)
            deleteActor(head, curr);
        curr = next;
    }
}


void showAllFilms(Film* head) {
    while (head) {
        cout << head->id << " - " << head->title
             << " (" << head->year << ")\n";
        head = head->next;
    }
}

void showAllActors(Actor* head) {
    while (head) {
        cout << head->id << " - " << head->name
             << " | Age: " << head->age
             << " | Perf: " << head->performance << "\n";
        head = head->next;
    }
}

void showActorsInFilm(Film* f) {
    if (!f) return;
    Relation* r = f->relHead;
    cout << "Aktor di film: " << f->title << endl;
    while (r) {
        cout << "- " << r->actorNode->name << endl;
        r = r->nextFilm;
    }
}

void showFilmsOfActor(Actor* a) {
    if (!a) return;
    Relation* r = a->relHead;
    cout << "Film dari aktor: " << a->name << endl;
    while (r) {
        cout << "- " << r->filmNode->title << endl;
        r = r->nextActor;
    }
}

bool actorHasFilm(Actor* a) {
    return a && a->relHead != nullptr;
}

void searchByCondition(Film* filmHead, Actor* actorHead) {
    int year;
    cout << "Cari film dengan tahun > ";
    cin >> year;
    while (filmHead) {
        if (filmHead->year > year)
            cout << "- " << filmHead->title << endl;
        filmHead = filmHead->next;
    }
}

void computeStatistics(Film* filmHead, Actor* actorHead) {
    int filmCount = 0, actorCount = 0;
    while (filmHead) { filmCount++; filmHead = filmHead->next; }
    while (actorHead) { actorCount++; actorHead = actorHead->next; }
    cout << "Total Film  = " << filmCount << endl;
    cout << "Total Aktor = " << actorCount << endl;
}

void assignUnassignedActor(Film* filmHead, Actor* actorHead) {
    Actor* a = actorHead;
    cout << "Aktor tanpa film:\n";
    while (a) {
        if (!actorHasFilm(a))
            cout << a->id << " - " << a->name << endl;
        a = a->next;
    }

    int aid, fid;
    cout << "ID Aktor: "; cin >> aid;
    cout << "ID Film: "; cin >> fid;

    Actor* A = findActor(actorHead, aid);
    Film* F = findFilm(filmHead, fid);

    if (A && F && !actorAlreadyLinked(F, A)) {
        connectFilmActor(F, A);
        cout << "Berhasil di-assign.\n";
    }
}


void menuStudiKasus(Film*& filmList, Actor*& actorList) {
    cout << "\n=== STUDI KASUS ===\n";

    insertFilmByCondition(filmList, createFilm(501, "Avatar", 2009));
    insertFilmByCondition(filmList, createFilm(502, "Avengers", 2012));
    insertFilmByCondition(filmList, createFilm(503, "The Matrix", 1999));

    insertActorByCondition(actorList, createActor(601, "Keanu Reeves", 55));
    insertActorByCondition(actorList, createActor(602, "Robert Downey Jr.", 54));
    insertActorByCondition(actorList, createActor(603, "Sam Worthington", 48));

    connectFilmActor(findFilm(filmList, 501), findActor(actorList, 603));
    connectFilmActor(findFilm(filmList, 502), findActor(actorList, 602));
    connectFilmActor(findFilm(filmList, 503), findActor(actorList, 601));

    showAllFilms(filmList);
    showAllActors(actorList);
}
