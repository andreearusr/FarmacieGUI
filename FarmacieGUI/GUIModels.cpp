#include "GUIModels.h"

#include <QtWidgets/QApplication>

void GUIModels::initGUIcmp() {
	setLayout(lyMain);
	lyMain->addWidget(lstV);
	lyMain->addWidget(tblV);
	lstV->setModel(model);
	tblV->setModel(model);

	auto stgLy = new QVBoxLayout;

	lyForm->addRow("Denumire", txtDenumire);
	lyForm->addRow("Pret", txtPret);
	lyForm->addRow("Producator", txtProducator);
	lyForm->addRow("Substanta", txtSubstanta);
	stgLy->addLayout(lyForm);
	ly->addLayout(stgLy);

	ly->addWidget(btnAdauga);
	ly->addWidget(btnSterge);
	ly->addWidget(btnModifica);
	ly->addWidget(btnCauta);
	ly->addSpacing(25);
	lyMain->addLayout(ly);

	ly->addWidget(btnSDen);
	ly->addWidget(btnSProd);
	ly->addWidget(btnSSubst_Pret);
	
	ly->addWidget(btnFPret);
	ly->addWidget(btnFSubst);

	stgLy->addLayout(ly);

	lyMain->addLayout(stgLy);

	auto updLy = new QVBoxLayout;
	lyForm2->addRow("Denumire noua", txtDenumireN);
	lyForm2->addRow("Pret nou", txtPretN);
	lyForm2->addRow("Producator nou", txtProducatorN);
	lyForm2->addRow("Substanta noua", txtSubstantaN);

	lyForm2->addWidget(btnAll);
	lyForm2->addWidget(btnUndo);
	lyForm2->addWidget(btnIesire);


	lyForm2->addWidget(btnRaport);
	lyForm2->addWidget(btnGolire);
	
	updLy->addLayout(lyForm2);
	lyMain->addLayout(updLy);

	auto nou = new QVBoxLayout;

	nou->addWidget(addReteta);
	nou->addWidget(genReteta);
	nou->addWidget(sp);

	nou->addWidget(showReteta);
	nou->addWidget(showRetetaReadOnly);
	nou->addWidget(CSVReteta);
	lyMain->addLayout(nou);

	auto lyFnou = new QFormLayout;
	lyFnou->addRow("Fisier", txtFisier);
	lyMain->addLayout(lyFnou);

}

void GUIModels::reloadList(const vector<Medicament>& meds) {
	model->setMedicamente(meds);
}

void GUIModels::connectSignals() {

	QObject::connect(btnAdauga, &QPushButton::clicked, this, [=]() {
		try {
			string den = txtDenumire->text().toStdString();
			string prod = txtProducator->text().toStdString();
			string subst = txtSubstanta->text().toStdString();
			float pret = txtPret->text().toFloat();
			
			srv.add_medicament(den, prod, subst, pret);
			reloadList(srv.get_all());
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
		}
		catch (ValidException& ex) {
			QMessageBox::information(this, "Validate Exception", QString::fromStdString(ex.getMessage()));
		}
		});

	QObject::connect(btnSterge, &QPushButton::clicked, this, [=]() {
		try {
			srv.delete_medicament(txtDenumire->text().toStdString());
			reloadList(srv.get_all());
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
		}
		catch (ValidException& ex) {
			QMessageBox::information(this, "Validate Exception", QString::fromStdString(ex.getMessage()));
		}
		});

	QObject::connect(btnModifica, &QPushButton::clicked, this, [=]() {

		string den = txtDenumire->text().toStdString();
		string denN = txtDenumireN->text().toStdString();
		string prodN = txtProducatorN->text().toStdString();
		string substN = txtSubstantaN->text().toStdString();
		float pretN = txtPretN->text().toFloat();

		try {
			srv.update_medicament(den, Medicament(denN, prodN, substN, pretN));
			reloadList(srv.get_all());
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
		}
		catch (ValidException& ex) {
			QMessageBox::information(this, "Validate Exception", QString::fromStdString(ex.getMessage()));
		}
		});


	QObject::connect(btnCauta, &QPushButton::clicked, this, [=]() {
		try {
			auto m = srv.find_medicament(txtDenumire->text().toStdString());
			txtDenumire->setText(QString::fromStdString(m.get_denumire()));
			txtPret->setText(QString::number(m.get_pret()));
			txtProducator->setText(QString::fromStdString(m.get_producator()));
			txtSubstanta->setText(QString::fromStdString(m.get_substanta()));
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
		}
		catch (ValidException& ex) {
			QMessageBox::information(this, "Validate Exception", QString::fromStdString(ex.getMessage()));
		}
		});


	QObject::connect(btnFPret, &QPushButton::clicked, this, [=]() {
		float pret = txtPret->text().toFloat();
		if (pret < 0)
			QMessageBox::information(this, "Validate Exception", "Pret invalid!\n");
		else
			reloadList(srv.filter_pret(pret));
		});

	QObject::connect(btnFSubst, &QPushButton::clicked, this, [=]() {
		string subst = txtSubstanta->text().toStdString();
		try {
			reloadList(srv.filter_subst(subst));
		}
		catch (ValidException& ex) {
			QMessageBox::information(this, "Validate Exception", QString::fromStdString(ex.getMessage()));
		}
		});


	QObject::connect(btnSDen, &QPushButton::clicked, this, [=]() {
		reloadList(srv.sort_denumire());
		});

	QObject::connect(btnSProd, &QPushButton::clicked, this, [=]() {
		reloadList(srv.sort_producator());
		});

	QObject::connect(btnSSubst_Pret, &QPushButton::clicked, this, [=]() {
		reloadList(srv.sort_subst_pret());
		});

	QObject::connect(lstV->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (lstV->selectionModel()->selectedIndexes().isEmpty()) {
			txtDenumire->setText("");
			txtPret->setText("");
			txtProducator->setText("");
			txtSubstanta->setText("");
			return;
		}
		else {
			auto selIndex = lstV->selectionModel()->selectedIndexes().at(0);
			auto denumire = selIndex.data().toString();
			txtDenumire->setText(denumire);
			try {
				auto m = srv.find_medicament(denumire.toStdString());
				txtPret->setText(QString::number(m.get_pret()));
				txtProducator->setText(QString::fromStdString(m.get_producator()));
				txtSubstanta->setText(QString::fromStdString(m.get_substanta()));
			}
			catch (RepoException& ex) {
				QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
			}

		}
		});

	QObject::connect(btnUndo, &QPushButton::clicked, this, [=]() {
		try {
			srv.undo();
			reloadList(srv.sort_subst_pret());
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
		}

		});


	QObject::connect(btnIesire, &QPushButton::clicked, this, [=]() {
		QMessageBox::information(this, "Info", "Goodbye");
		close();
		});

	QObject::connect(btnAll, &QPushButton::clicked, this, [=]() {
		reloadList(srv.get_all());
		});

	QObject::connect(btnGolire, &QPushButton::clicked, this, [=]() {

		txtDenumire->setText("");
		txtPret->setText("");
		txtProducator->setText("");
		txtSubstanta->setText("");

		txtDenumireN->setText("");
		txtPretN->setText("");
		txtProducatorN->setText("");
		txtSubstantaN->setText("");

		});

	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
			txtDenumire->setText("");
			txtPret->setText("");
			txtProducator->setText("");
			txtSubstanta->setText("");
			return;
		}
		else {
			auto selItem = tblV->selectionModel()->selectedIndexes().at(0);
			auto denumire = selItem.data().toString();
			txtDenumire->setText(denumire);
			try {
				auto m = srv.find_medicament(denumire.toStdString());
				txtPret->setText(QString::number(m.get_pret()));
				txtProducator->setText(QString::fromStdString(m.get_producator()));
				txtSubstanta->setText(QString::fromStdString(m.get_substanta()));
			}
			catch (RepoException& ex) {
				QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
			}
		}
		});

	QObject::connect(btnRaport, &QPushButton::clicked, this, [=]() {
		std::map<string, DTO> rez = srv.producator();
		QDialog* d = new QDialog;
		int nr;
		nr = static_cast<int>(rez.size());
		QTableWidget* t = new QTableWidget{nr, 2 };
		QHBoxLayout* l = new QHBoxLayout;
		d->setLayout(l);
		l->addWidget(t);

		t->clear();
		int poz = 0;

		for (auto& elem : rez)
		{

			QTableWidgetItem* cel1 = new QTableWidgetItem("Tip(producator)");
			//cel1->setBackground(Qt::red);
			t->setHorizontalHeaderItem(0, cel1);

			QTableWidgetItem* cel2 = new QTableWidgetItem("Numar produse");
			t->setHorizontalHeaderItem(1, cel2);;
			//cel2->setBackground(Qt::red);

			QTableWidgetItem* cell1 = new QTableWidgetItem(QString::fromStdString(elem.first));
			t->setItem(poz, 0, cell1);

			QTableWidgetItem* cell2 = new QTableWidgetItem(QString::number(elem.second.get_count()));
			t->setItem(poz, 1, cell2);

			poz++;
		}
		d->show();
		});


	QObject::connect(addReteta, &QPushButton::clicked, this, [=]() {
		string den = txtDenumire->text().toStdString();
		srv.adauga_reteta(den);
		});

	QObject::connect(genReteta, &QPushButton::clicked, this, [=]() {
		int nr = sp->value();
		if (nr <= 0)
			QMessageBox::information(this, "msg", "Numar invalid!");
		else
		{
			srv.genereaza_reteta(nr);
		}
		});

	QObject::connect(emptyReteta, &QPushButton::clicked, this, [=]() {
		srv.goleste_reteta();
		});

	QObject::connect(CSVReteta, &QPushButton::clicked, [=]() {
		string fisier = txtFisier->text().toStdString();
		if (fisier == "")
			QMessageBox::information(this, "msg", "Nume fisier vid!");
		else
		{
			srv.exporteaza(fisier);
		}
		});

	QObject::connect(showReteta, &QPushButton::clicked, [=]() {
		//r.addObserver(new CosCRUDGUI{ r });
		auto w = new CosCRUDGUI{ r };
		w->show();
		});
	QObject::connect(showRetetaReadOnly, &QPushButton::clicked, [=]() {
		//r.addObserver(new CosReadOnlyGUI{ r });
		auto w = new CosReadOnlyGUI{ r };
		w->show();
		});

}