#pragma once
#include "repo.h"
#include "domain.h"
#include "observer.h"

#include <string>
#include <iostream>
#include <vector>
using std::string;
using std::vector;

class Reteta: public Observable{
private:
	vector<Medicament> inReteta;
	Repo& repo;
	int n; 

public:
	//constructorul implicit al retetei
	//Reteta() = default;

	/*
	functie pentru creeare reteta
	date de intrare
		repo - repository-ul de medicamente
	post: obiect de tip Reteta
	*/
	Reteta(Repo& repo) noexcept : repo{ repo } {}

	//nu se mai pot copia obiectele de tip Reteta
	//Reteta(const Reteta& reteta) = delete;


	/*
	functie pentru adaugare medicament in Reteta
	date de intrare:
		denumire - denumirea medicamentului de adaugat
	post: medicamentul e adaugat in reteta
	*/
	void adauga(const string& denumire);

	/*
	functie pentru stergere toate medicamentele din Reteta
	date de intrare -
	post: Reteta nu contine niciun medicament
	*/
	void goleste() noexcept;

	/*
	functie pentru adaugare medicamente random in Reteta
	date de intrare:
		nr - cate medicamente random sa se adauge
	post: in Reteta au fost adaugate nr medicamente random
	*/
	void genereaza(int nr);

	// functie ce returneaza numarul de medicamente din Reteta
	int dimensiune() noexcept;

	/*
	functie pentru stergerea unui medicament din Reteta
	date de intrare:
		den - denumirea medicamentului ce se doreste a fi sters
	post: medicamentul este sters daca el exista in Reteta
	*/
	void sterge(const string& den);

	/*
	functie pentru modificarea unui medicament din Reteta
	date de intrare:
		den - denumirea medicamentului ce se doreste a fi modificat
		med - noul medicament
	post: medicamentul vechi este modificat daca exista in Reteta
	*/
	void modifica(const string& den, const Medicament& med);

	/*
	functie pentru exportul medicamentelor adaugate intr-un fisier csv/html
	date de intrare:
		fisier - numele fisierului unde se vor exporta medicamentele
	post: fisier contine medicamentele din Reteta
	*/
	void export_reteta(const string& fisier);


	Medicament cauta(const string& denumire);

	vector<Medicament>& all_meds();
};

