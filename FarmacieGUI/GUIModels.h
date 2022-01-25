#pragma once
#include <QtWidgets/QApplication>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>
#include <QColor>
#include <QPainter>
#include <QBrush.h>
#include <qtablewidget.h>
#include <qspinbox.h>
#include <qradiobutton.h>
#include "service.h"
#include "domain.h"
#include "Reteta.h"
#include <vector>
#include "myR.h"
#include"GUI.h"
#include"observer.h"
using std::vector;
using std::string;

#include "MyTableModel.h"
#include <qlistview.h>
#include <qtableview.h>

class GUIModels: public QWidget {
private:
	Service& srv;
	Reteta& r;

	MyTableModel* model = new MyTableModel(srv.get_all());

	QHBoxLayout* lyMain = new QHBoxLayout;
	QVBoxLayout* ly = new QVBoxLayout;

	QListView* lstV = new QListView();
	QTableView* tblV = new QTableView();

	QPushButton* btnAdauga = new QPushButton("Adauga medicament");
	QPushButton* btnSterge = new QPushButton("Sterge medicament");
	QPushButton* btnModifica = new QPushButton("Modifica medicament");
	QPushButton* btnCauta = new QPushButton("Cauta medicament");

	QPushButton* btnSDen = new QPushButton("Sortare -> denumire");
	QPushButton* btnSProd = new QPushButton("Sortare -> producator");
	QPushButton* btnSSubst_Pret = new QPushButton("Sortare -> substanta+pret");

	QPushButton* btnFPret = new QPushButton("Filtrare -> pret");
	QPushButton* btnFSubst = new QPushButton("Filtrare -> substanta");
	QPushButton* btnUndo = new QPushButton("Undo");
	QPushButton* btnIesire = new QPushButton("IESIRE");
	QPushButton* btnAll = new QPushButton("Afisare");
	QPushButton* btnGolire = new QPushButton("Golire campuri");

	QPushButton* btnRaport = new QPushButton("Raport");
	QFormLayout* lyForm = new QFormLayout;
	QFormLayout* lyForm2 = new QFormLayout;

	QLineEdit* txtDenumire = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	QLineEdit* txtSubstanta = new QLineEdit;

	QLineEdit* txtDenumireN = new QLineEdit;
	QLineEdit* txtPretN = new QLineEdit;
	QLineEdit* txtProducatorN = new QLineEdit;
	QLineEdit* txtSubstantaN = new QLineEdit;

	QPushButton* addReteta = new QPushButton("Adauga medicament reteta");
	QPushButton* genReteta = new QPushButton("Genereaza reteta");
	QPushButton* emptyReteta = new QPushButton("Golire reteta");
	QPushButton* showReteta = new QPushButton("Afisare reteta CRUD");
	QPushButton* showRetetaReadOnly = new QPushButton("Afisare reteta Read-Only");
	QPushButton* CSVReteta = new QPushButton("Export reteta");

	QLineEdit* txtFisier = new QLineEdit;
	QSpinBox* sp = new QSpinBox;

	/*
	functie pentru initializare GUI
	*/
	void initGUIcmp();

	/*
	functie pentru conexiune semnale primite de lla utilizator
	*/
	void connectSignals();

	/*
	functie pentru afisarea constanta in lista, a medicamentelor - denumirea
	date de intrare:
		meds - vectorul de medicamente
	post: medicamentele sunt listate
	*/
	void reloadList(const vector<Medicament>& meds);

public:

	/*
	functie pentru creeare myGUI
	date de intrare
		srv - obiect de tip Service
	post: obiect de tip myGUI
	*/
	GUIModels(Service& srv, Reteta& r) : srv{ srv }, r{ r } {
		initGUIcmp();
		connectSignals();
		reloadList(srv.get_all());

	}
};


