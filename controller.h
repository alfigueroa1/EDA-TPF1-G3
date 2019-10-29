#pragma once

#include "observer.h"
#include "model.h"
#include "fileController.h"
#include "blockController.h"

typedef enum { INIT, BLOCK, ERR } stateType;

class controllerHandler {
public:
	controllerHandler(Model&);
	~controllerHandler();
	void cycle();

private:
	fileController* fc;
	blockController* bc;
	stateType state;
};

