#pragma once
#include "observer.h"
#include "model.h"

class blockController : public Observer {
public:
	blockController(Model&);
	virtual void update(void*);
	void askBlock(string);

private:
	Model* m;
	int currBlock;
	bool merkle;
	void openBlock(unsigned long int);
};