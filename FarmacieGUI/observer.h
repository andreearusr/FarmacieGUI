#pragma once
#include <vector>
#include <algorithm>

/*
  Clasa abstracta
*/
class Observer {
public:
	virtual void update() = 0;
};

/*
  Observable sau Subiect - clasa care notifica schimbarile
*/
class Observable {
private:
	std::vector<Observer*> observers;
public:
	//adauga observer
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	//sterge  observer
	void removeObserver(Observer* obs) {
		observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
	}

protected:
	//notifica
	void notify() {
		for (auto obs : observers) {
			obs->update();
		}
	}
};