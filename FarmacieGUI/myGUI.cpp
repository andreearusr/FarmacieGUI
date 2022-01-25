#include "myGUI.h"
#include <QtWidgets/QApplication>

void myGUI::initGUIcmp() {
	setLayout(lyMain);
	lyMain->addWidget(lst_meds);
	lyMain->addWidget(table); 

	auto stgLy = new QVBoxLayout;

	lyForm->addRow("Denumire", txtDenumire);
	//lyForm->addRow("Pret", txtPret);
	lyForm->addWidget(sl1);
	//lyForm->addWidget(spPret);
	lyForm->addRow("Producator", txtProducator);
	lyForm->addRow("Substanta", txtSubstanta);
	stgLy->addLayout(lyForm);

	ly->addWidget(btnAdauga);
	ly->addWidget(btnSterge);
	ly->addWidget(btnModifica);
	ly->addWidget(btnCauta);
	ly->addSpacing(25);

	
	ly->addWidget(btnSDen); 
	ly->addWidget(btnSProd); 
	ly->addWidget(btnSSubst_Pret);

	/*ly->addWidget(bd); 
	ly->addWidget(bp); 
	ly->addWidget(bsp);*/

	/*ly->addWidget(c);
	c->addItem("Sort den");
	c->addItem("Sort prod");
	c->addItem("Sort subst+pret");*/

	ly->addWidget(btnFPret);
	ly->addWidget(btnFSubst);

	stgLy->addLayout(ly);

	lyMain->addLayout(stgLy);

	auto updLy = new QVBoxLayout;
	lyForm2->addRow("Denumire noua", txtDenumireN);
	//lyForm2->addRow("Pret nou", txtPretN);
	lyForm2->addWidget(spPretN);
	lyForm2->addRow("Producator nou", txtProducatorN);
	lyForm2->addRow("Substanta noua", txtSubstantaN);
	lyForm2->addWidget(btnAll);
	lyForm2->addWidget(btnUndo);

	//lyForm2->addWidget(btnReteta);
	lyForm2->addWidget(btnRaport);
	lyForm2->addWidget(btnGolire);
	lyForm2->addWidget(btnIesire);

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

void myGUI::reloadList(const vector<Medicament>& meds) {

	lst_meds->clear();
	table->clear();
	int poz = 0;
	for (const Medicament& m : meds) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(m.get_denumire()));
		//item->setData(Qt::BackgroundRole, QBrush(Qt::yellow, Qt::SolidPattern));
		lst_meds->addItem(item);

		QTableWidgetItem* cel1 = new QTableWidgetItem("Denumire");
		table->setHorizontalHeaderItem(0, cel1);

		QTableWidgetItem* cel2 = new QTableWidgetItem("Pret");
		table->setHorizontalHeaderItem(1, cel2);

		QTableWidgetItem* cel3 = new QTableWidgetItem("Producator");
		table->setHorizontalHeaderItem(2, cel3);

		QTableWidgetItem* cel4 = new QTableWidgetItem("Substanta");
		table->setHorizontalHeaderItem(3, cel4);

		QTableWidgetItem* cell1 = new QTableWidgetItem(QString::fromStdString(m.get_denumire()));
		QTableWidgetItem* cell2 = new QTableWidgetItem(QString::number(m.get_pret()));
		QTableWidgetItem* cell3 = new QTableWidgetItem(QString::fromStdString(m.get_producator()));
		QTableWidgetItem* cell4 = new QTableWidgetItem(QString::fromStdString(m.get_substanta()));

		table->setItem(poz, 0, cell1); 
		table->setItem(poz, 1, cell2); 
		table->setItem(poz, 2, cell3); 
		table->setItem(poz, 3, cell4); 
		 
		poz++;  
	} 


}

/*
void myGUI::generare(const vector<Medicament>& meds) {
	vector<string> prod;
	for (const auto& m : meds) {
		int ok = 1;
		string producator = m.get_producator();

		for (const auto& p : prod)
		{
			if (p == producator)
			{
				ok = 0;
				break;
			}
		}
		if(ok==1)
			prod.push_back(producator);
		
	}

	for (const auto& p : prod) {
		auto btn = new QPushButton{ QString::fromStdString(p) };
		lyForm2->addWidget(btn);

		QObject::connect(btn, &QPushButton::clicked, [this, btn, p, meds]()
			{
				for (const auto& m : meds) {
					if (m.get_producator() == p)
					{
						srv.delete_medicament(m.get_denumire());
						reloadList(srv.get_all());
					}
				}
				delete btn;
			});

	}
}
*/

void myGUI::connectSignals() {

	QObject::connect(btnAdauga, &QPushButton::clicked, this, [=]() {
		try {
			string den = txtDenumire->text().toStdString();
			string prod = txtProducator->text().toStdString();
			string subst = txtSubstanta->text().toStdString();
			//float pret = txtPret->text().toFloat();
			float pret = sl1->value();

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
		//float pretN = txtPretN->text().toFloat();
		float pretN = spPretN->value();

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
			//txtPret->setText(QString::number(m.get_pret()));
			sl1->setValue(m.get_pret());

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
		//float pret = txtPret->text().toFloat();
		float pret = sl1->value();
		if (pret < 0)
			QMessageBox::information(this, "Validate Exception", "Pret invalid!\n");
		else
		{//reloadList(srv.filter_pret(pret));
			lst_meds->clear();
			for (const Medicament& m : srv.get_all()) {
				QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(m.get_denumire()));
				if (m.get_pret() < pret)
					item->setData(Qt::BackgroundRole, QBrush(Qt::yellow, Qt::SolidPattern));

				lst_meds->addItem(item);

			}
		}
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
	  
	/*QObject::connect(c, &QComboBox::currentTextChanged, this, [=]() { 
		string text = c->currentText().toStdString();
		if(text== "Sort den")
			reloadList(srv.sort_denumire());
		else if(text == "Sort prod")
			reloadList(srv.sort_producator());
		else 
			reloadList(srv.sort_subst_pret());
		});*/ 
	 
	/*QObject::connect(bd, &QPushButton::toggled, this, [=]() {
		reloadList(srv.sort_denumire());
		});

	QObject::connect(bp, &QPushButton::toggled, this, [=]() { 
		reloadList(srv.sort_producator()); 
		}); 

	QObject::connect(bsp, &QPushButton::toggled, this, [=]() {
		reloadList(srv.sort_subst_pret());
		});*/


	QObject::connect(lst_meds, &QListWidget::itemSelectionChanged, this, [=]() {
		auto sel = lst_meds->selectedItems();
		if (sel.isEmpty()) {
			txtDenumire->setText("");
			//txtPret->setText("");
			sl1->setValue(0);
			txtProducator->setText("");
			txtSubstanta->setText("");
		}
		else {
			auto selItem = sel.at(0);
			auto denumire = selItem->text();
			txtDenumire->setText(denumire);
			try {
				auto m = srv.find_medicament(denumire.toStdString());
				//txtPret->setText(QString::number(m.get_pret()));
				sl1->setValue(m.get_pret());
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
		//txtPret->setText("");
		sl1->setValue(0);
		txtProducator->setText("");
		txtSubstanta->setText("");

		txtDenumireN->setText("");
		//txtPretN->setText("");
		spPretN->setValue(0);
		txtProducatorN->setText("");
		txtSubstantaN->setText("");

		});

	QObject::connect(table, &QTableWidget::itemSelectionChanged, [=]() {
		auto sel = table->selectedItems();
		if (sel.isEmpty()) {
			txtDenumire->setText("");
			//txtPret->setText("");
			sl1->setValue(0);
			txtProducator->setText("");
			txtSubstanta->setText("");
		}
		else {
			auto selItem = sel.at(0);
			auto denumire = selItem->text();
			txtDenumire->setText(denumire);
			try {
				auto m = srv.find_medicament(denumire.toStdString());
				//txtPret->setText(QString::number(m.get_pret()));
				sl1->setValue(m.get_pret());
				txtProducator->setText(QString::fromStdString(m.get_producator()));
				txtSubstanta->setText(QString::fromStdString(m.get_substanta()));
			}
			catch (RepoException& ex) {
				QMessageBox::information(this, "Repo Exception", QString::fromStdString(ex.getMessage()));
			}
		}
		});

	/*QObject::connect(btnReteta, &QPushButton::clicked, this, [=]() {
		guiR.show();
		});*/

	QObject::connect(btnRaport, &QPushButton::clicked, this, [=]() {
		std::map<string, DTO> rez = srv.producator();
		QDialog* d = new QDialog;
		QTableWidget* t = new QTableWidget{ 12, 2 };
		QHBoxLayout* l = new QHBoxLayout;
		d->setLayout(l);
		l->addWidget(t);

		t->clear();
		int poz = 1;

		for (auto& elem : rez)
		{
			
			QTableWidgetItem* cel1 = new QTableWidgetItem("Tip(producator)");
			t->setItem(0, 0, cel1);
			cel1->setBackground(Qt::red);

			QTableWidgetItem* cel2 = new QTableWidgetItem("Numar produse");
			t->setItem(0, 1, cel2);
			cel2->setBackground(Qt::red);

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
		//r.addObserver(new CosCRUDGUI{r});
		auto w = new CosCRUDGUI{ r };
		w->show();
		});
	QObject::connect(showRetetaReadOnly, &QPushButton::clicked, [=]() {
		//r.addObserver(new CosReadOnlyGUI{r});
		auto w = new CosReadOnlyGUI{ r };
		w->show();
		});

}