#pragma once
#include "observer.h"
#include "controller.h"
#include "model.h"

class blockController : public Controller {
public:
	blockController(Model&);
	virtual void update(void*);
	virtual void cycle();
	void askBlock(string);
	void selectBlock(string);
	void reAsk();

private:
	Model* m;
	int currBlock;
	string blocks;
	bool showBlocks;
	string filepath;
	string getFilename(string);
};