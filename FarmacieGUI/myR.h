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
#include<qspinbox.h>

#include "service.h"
#include "domain.h"
#include "Reteta.h"
#include <vector>

using std::vector;
using std::string;

class myR : public QWidget
{
private:
	Reteta& r;

	QHBoxLayout* lyMain = new QHBoxLayout;
	QVBoxLayout* ly = new QVBoxLayout;

	QListWidget* lst_meds = new QListWidget;

	QPushButton* btnAdauga = new QPushButton("Adauga medicament");
	QPushButton* btnGoleste = new QPushButton("Goleste reteta");
	QPushButton* btnGenereaza = new QPushButton("Genereaza reteta");
	QPushButton* btnExport = new QPushButton("Export reteta");

	QPushButton* btnGolire = new QPushButton("Golire campuri");

	QFormLayout* lyForm = new QFormLayout;
	QFormLayout* lyForm2 = new QFormLayout;
	QFormLayout* lyForm3 = new QFormLayout;

	QLineEdit* txtDenumire = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	QLineEdit* txtSubstanta = new QLineEdit;

	QLineEdit* txtFisier = new QLineEdit;
	//QLineEdit* txtNumar = new QLineEdit;
	QSpinBox* sp = new QSpinBox;


	/*
	functie pentru initializare GUI
	*/
	void initGUI();

	/*
	functie pentru conexiune semnale primite de lla utilizator
	*/
	void connect();

	/*
	functie pentru afisarea constanta in lista, a medicamentelor - denumirea
	date de intrare:
		meds - vectorul de medicamente
	post: medicamentele sunt listate
	*/
	void reload(const vector<Medicament>& meds);

public:

	/*
	functie pentru creeare myGUI
	date de intrare
		srv - obiect de tip Service
	post: obiect de tip myGUI
	*/
	myR(Reteta& r) : r{ r } {
		initGUI();
		connect();
		reload(r.all_meds());
	}
};

