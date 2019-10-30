#pragma once

#include "observer.h"
#include "model.h"
#include "controller.h"

class fileController : public Controller {
public:
	fileController(Model&);
	virtual void update(void*);
	virtual void cycle();
	void askPath();
	string drawFiles();

private:
	Model* m;
	char path[_MAX_PATH];
	vector<string> filenames;
	vector<string>* p;
};
