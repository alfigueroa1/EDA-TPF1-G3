#pragma once

#include "model.h"

class fileController : public Observer {
public:
	fileController(Model&);
	virtual void update(void*);
	void cycle(void);

private:
	Model* m;
	char path[_MAX_PATH];
	vector<string> filenames;
	int open;
	void askPath();
};


//class blockController : public Observer {
//public:
//	blockController(Model&);
//	virtual void update(void*);
//	void cycle(void);
//
//private:
//	Model* m;
//
//
//};