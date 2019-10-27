#pragma once
#include "observer.h"
#include "treeWindow.h"
#include <map>
#include <string>
using namespace std;


class Viewer : public Observer {
public:
	Viewer();

	virtual void update(void*);//Llamar cada vez q algo cambia en el modelo
	void cycle(void);//Funciones de dibujo

private:
	map<string, treeWindow> windowList;
};