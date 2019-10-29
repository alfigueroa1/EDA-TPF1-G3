#pragma once
#include "observer.h"
#include "model.h"

class blockController : public Observer {
public:
	blockController(Model&);
	virtual void update(void*);
	void askBlock(string);
	void selectBlock();

private:
	Model* m;
	int currBlock;
	char* preview;
	char* blocks[100];
	//void openBlock(unsigned long int);
};