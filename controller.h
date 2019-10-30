#pragma once

#include "observer.h"

class Controller : public Observer {
public:
	virtual void update(void*) = 0;
	virtual void cycle() = 0;
};


