#ifndef MLIST_H_INCLUDED
#define MLIST_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

struct Film;
struct Actor;
struct Relation;

struct Film {
    int id;
    string title;
    int year;
    Film *next;
    Relation *relHead;
};

struct Actor {
    int id;
    string name;
    int age;
    int performance;
    Actor *next;
    Relation *relHead;
};

struct Relation {
    Film *filmNode;
    Actor *actorNode;
    Relation *nextFilm;
    Relation *nextActor;
};

Film* createFilm(int id, string title, int year);
Actor* createActor(int id, string name, int age);

void insertFilm(Film* &head, Film* newFilm);
void insertActor(Actor* &head, Actor* newActor);

Relation* connectFilmActor(Film* f, Actor* a);

void deleteFilm(Film* &head, Film* target);
void deleteActor(Actor* &head, Actor* target);

Film* findFilm(Film* head, int id);
Actor* findActor(Actor* head, int id);

void showAllFilms(Film* head);
void showAllActors(Actor* head);

void showActorsInFilm(Film* f);
void showFilmsOfActor(Actor* a);

void insertFilmByCondition(Film* &head, Film* newFilm);
void insertActorByCondition(Actor* &head, Actor* newActor);

void deleteFilmByCondition(Film* &head, int yearLimit);
void deleteActorByCondition(Actor* &head, int ageLimit);

void searchByCondition(Film* filmHead, Actor* actorHead);
void computeStatistics(Film* filmHead, Actor* actorHead);

void displayAllParents(Film* head);
void menuStudiKasus(Film* &filmList, Actor* &actorList);

bool actorHasFilm(Actor* a);
void assignUnassignedActor(Film* filmHead, Actor* actorHead);

bool actorAlreadyLinked(Film* f, Actor* a);

#endif
