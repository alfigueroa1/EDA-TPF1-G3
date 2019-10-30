#pragma once
#include "observer.h"
#include "controller.h"
#include "model.h"

#define MAX_CTRL	2

typedef enum { INIT, GET_BLOCK, SHOW_BLOCK, ERR } stateType;
enum { FILE_C, BLOCK_C };

class controllerHandler : public Observer {
public:
	controllerHandler(Model&);
	~controllerHandler();
	virtual void update(void*);
	void cycle();

private:
	Controller* controllers[MAX_CTRL];
	stateType state;
	Model* m;
};
