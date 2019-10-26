#pragma once

#include "model.h"

class Controller : public Observer {
public:
	Controller(Model& m) { model = &m; }
	virtual void update(void*){}
	void cycle(void){}

private:
	Model* model;
};