#include "myR.h"

void myR::initGUI() {
	setLayout(lyMain);

	lyMain->addWidget(lst_meds);

	auto stgLy = new QVBoxLayout;

	lyForm->addRow("Denumire", txtDenumire);
	lyForm->addRow("Pret", txtPret);
	lyForm->addRow("Producator", txtProducator);
	lyForm->addRow("Substanta", txtSubstanta);
	
	stgLy->addLayout(lyForm);

	ly->addWidget(btnAdauga);
	ly->addWidget(btnGoleste);
	ly->addSpacing(25);

	//lyForm2->addRow("Numar", txtNumar);
	lyForm2->addWidget(sp);
	ly->addLayout(lyForm2);
	ly->addWidget(btnGenereaza);
	ly->addSpacing(25);

	lyForm3->addRow("Nume fisier", txtFisier);
	ly->addLayout(lyForm3);
	ly->addWidget(btnExport);
	ly->addSpacing(25);

	ly->addWidget(btnGolire);
	stgLy->addLayout(ly);
	lyMain->addLayout(stgLy);

}


void myR::reload(const vector<Medicament>& meds) {

	lst_meds->clear();
	for (const Medicament& m : meds) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(m.get_denumire()));
		//item->setData(Qt::BackgroundRole, QBrush(Qt::yellow, Qt::SolidPattern));
		lst_meds->addItem(item);
	}

}

void myR::connect() {

	QObject::connect(btnAdauga, &QPushButton::clicked, this, [=]() {
		try {
			string den = txtDenumire->text().toStdString();

			r.adauga(den);
			reload(r.all_meds());
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
		}
		catch (ValidException& ex) {
			QMessageBox::information(this, "Validate Exception", QString::fromStdString(ex.getMessage()));
		}
		});

	QObject::connect(btnGoleste, &QPushButton::clicked, this, [=]() {
		r.goleste();
		reload(r.all_meds());
		});


	QObject::connect(btnGenereaza, &QPushButton::clicked, this, [=]() {
		//int nr = txtNumar->text().toInt();
		int nr = sp->value();
		if(nr<=0)
			QMessageBox::information(this, "msg", "Numar invalid!");
		else
		{
			r.genereaza(nr);
			reload(r.all_meds());
		}
		});

	QObject::connect(btnExport, &QPushButton::clicked, this, [=]() {
		string fisier = txtFisier->text().toStdString();
		if (fisier == "")
			QMessageBox::information(this, "msg", "Nume fisier vid!");
		else
			r.export_reteta(fisier);
		});


	QObject::connect(btnGolire, &QPushButton::clicked, this, [=]() {

		txtDenumire->setText("");
		txtPret->setText("");
		txtProducator->setText("");
		txtSubstanta->setText("");
		//txtNumar->setText("");
		sp->setValue(0);
		txtFisier->setText("");
		});

	QObject::connect(lst_meds, &QListWidget::itemSelectionChanged, this, [=]() {
		auto sel = lst_meds->selectedItems();
		if (sel.isEmpty()) {
			txtDenumire->setText("");
			txtPret->setText("");
			txtProducator->setText("");
			txtSubstanta->setText("");
		}
		else {
			auto selItem = sel.at(0);
			auto denumire = selItem->text();
			txtDenumire->setText(denumire);

			auto m = r.cauta(denumire.toStdString());
			txtPret->setText(QString::number(m.get_pret()));
			txtProducator->setText(QString::fromStdString(m.get_producator()));
			txtSubstanta->setText(QString::fromStdString(m.get_substanta()));
		}
		});

}