#pragma once
#include <QtWidgets/QApplication>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include<qspinbox.h>
#include<qmessagebox.h>
#include <QColor>
#include<qpainter.h>
#include<qslider.h>
#include<random>
#include<qtableview.h>
#include<qlistview.h>

#include<vector>
using std::vector;
#include<string>
using std::string;

#include"observer.h"
#include"service.h"
#include"repo.h"
#include "MyTableModel.h"

class CosCRUDGUI :public QWidget, public Observer {
private:
	Reteta& reteta;

	QHBoxLayout* lyMain = new QHBoxLayout;
	QTableView* tab = new QTableView();
	QPushButton* btnGoleste = new QPushButton("Goleste reteta");
	QPushButton* btnG = new QPushButton("Genereaza reteta");
	QSpinBox* spin = new QSpinBox;

	MyTableModel* retetaTab = new MyTableModel(reteta.all_meds());
	//initializeaza fereastra CosCRUDGUI
	void initGUI() {
		
		setLayout(lyMain);
		lyMain->addWidget(tab);
		lyMain->addWidget(btnG);
		lyMain->addWidget(spin);
		//lyMain->addWidget(sl);
		lyMain->addWidget(btnGoleste);
		tab->setModel(retetaTab);
		
		this->show();
	}

	//incarca lista de medicamente din Reteta
	void loadList(const vector<Medicament>& meds) {
		//lst->clear();
		/*for (const Medicament& m : meds) {
			lst->addItem(QString::fromStdString(m.get_denumire()));
		}*/
		retetaTab->setMedicamente(meds);
	}

	//conecteaza semnalele de la utilizator
	void connectSignals() {
		reteta.addObserver(this);
		QObject::connect(btnGoleste, &QPushButton::clicked, [=]() {
			reteta.goleste();
			loadList(reteta.all_meds());
			});

		QObject::connect(btnG, &QPushButton::clicked, [=]() {
			//int nr = txt->text().toInt();
			int nr = spin->value();
			if (nr <= 0)
				QMessageBox::information(this, "msg", "Numar invalid!");
			else
			{
				reteta.genereaza(nr);
				loadList(reteta.all_meds());
			}
			});
	}

public:
	//constructorul pentru CosCRUDGUI
	// reteta- o reteta de tip Reteta
	CosCRUDGUI(Reteta& reteta) : reteta{ reteta }{
		initGUI();
		connectSignals();
		loadList(reteta.all_meds());
	};

	//cand apare o modificare, se apeleaza update
	void update() override {
		loadList(reteta.all_meds());
	}

	/*~CosCRUDGUI() {
		reteta.removeObserver(this);
	}*/

};


class CosReadOnlyGUI :public QWidget, public Observer {

private:
	Reteta& reteta;

public:
	//constructorul pentru CosReadOnlyGUI
	// reteta- o reteta de tip Reteta
	CosReadOnlyGUI(Reteta& reteta) : reteta{ reteta }{
		reteta.addObserver(this);
		this->show();
		//repaint();
	}

	//functie pentru desenare
	void paintEvent(QPaintEvent* ) override {
		QPainter p{ this };
		//for (const auto& m: reteta.all_meds()) {
		for(int i=0; i<reteta.all_meds().size(); i++){
			int x = rand() % width();
			if (x >= width() - 20) {
				x -= 20;
			}
			int y = rand() % height();
			if (y >= height() - 20) {
				y -= 20;
			}
			p.drawRect(x, y, 20, 20);
		}
	}

	//cand apare o modificare, se apeleaza update
	void update() override {
		repaint();
	}

};