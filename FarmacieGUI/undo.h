#pragma once
#include "domain.h"
#include "repo.h"

class ActiuneUndo {
public:
	//functie virtuala pentru doUndo
	virtual void doUndo() = 0;

	//desctructor virtual pentru undo
	virtual ~ActiuneUndo() = default;

};


class UndoAdauga : public ActiuneUndo {

	Medicament medAdaugat;
	Repo& rep;

public:
	/*
	constructorul pentru UndoAdauga
	date de intrare:
		rep - Repository-ul de medicamente
		med - medicament de tipul Medicament
	*/
	UndoAdauga(Repo& rep, const Medicament& med) : rep{ rep }, medAdaugat{ med }{}

	/*
	functia doUndo suprascrisa pentru UndoAdauga
	se sterge medicamentul adaugat - medAdaugat
	*/
	void doUndo() override {
		rep.delete_medicament(medAdaugat.get_denumire());
	}
};

class UndoSterge : public ActiuneUndo {

	Medicament medSters;
	Repo& rep;

public:
	/*
	constructorul pentru UndoSterge
	date de intrare:
		rep - Repository-ul de medicamente
		med - medicament de tipul Medicament
	*/
	UndoSterge(Repo& rep, const Medicament& med) : rep{ rep }, medSters{ med }{}

	/*
	functia doUndo suprascrisa pentru UndoSterge
	se adauga medicamentul sters - medSters
	*/
	void doUndo() override {
		rep.add_medicament(medSters);
	}
};


class UndoModifica : public ActiuneUndo {

	Medicament medNeModificat;
	Medicament medModificat;
	Repo& rep;

public:
	/*
	constructorul pentru UndoModifica
	date de intrare :
		rep - Repository-ul de medicamente
		med_nem - medicament de tipul Medicament
		med - medicament de tipul Medicament
	*/
	UndoModifica(Repo& rep, const Medicament& med_nem, const Medicament& med) : rep{ rep }, medNeModificat{ med_nem }, medModificat{ med } {}

	/*
	functia doUndo suprascrisa pentru UndoModifica
	se sterge medicamentul modificat - medModificat
	se adauga medicamentul nemodificat - medNeModificat
	*/
	void doUndo() override {
		rep.delete_medicament(medModificat.get_denumire());
		rep.add_medicament(medNeModificat);
	}
};

