#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include<vector>
#include<qdebug.h>
using std::vector;

class MyTableModel: public QAbstractTableModel{
	vector<Medicament> meds;

public:
	MyTableModel(const vector<Medicament>& med) : meds{ med } {};

	int rowCount(const QModelIndex& = QModelIndex()) const override {
		return static_cast<int>(meds.size());
	}

	int columnCount(const QModelIndex&  = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index = QModelIndex(), int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Medicament m = meds[index.row()];
			if (index.column() == 0)
				return QString::fromStdString(m.get_denumire());
			else if (index.column() == 1) {
				//char numar[10];
				//return QString::fromStdString(itoa(m.get_pret(), numar, 10));
				return QString::number(m.get_pret());
			}
			else if (index.column() == 2)
				return QString::fromStdString(m.get_producator());
			else if (index.column() == 3)
				return QString::fromStdString(m.get_substanta());
		}
		
		return QVariant{};
	}

	void setMedicamente(const vector<Medicament>& m) {
		this->meds = m;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}


};

