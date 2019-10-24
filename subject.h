#pragma once
#include <vector>
#include "observer.h"

using namespace std;

class Subject {
public:
	void attach(Observer& o) { observers.push_back(&o); };
	void detach(vector<Observer*>::iterator pos) { observers.erase(pos); };
private:
	vector<Observer*> observers;
};