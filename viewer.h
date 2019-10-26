#pragma once

class Viewer : public Observer {
public:
	virtual void update(void*) {}
	void cycle(void) {}
};