#pragma once

class Viewer : public Observer {
public:
	virtual void update(void*) {}//Llamar cada vez q algo cambia en el modelo
	void cycle(void) {}//Funciones de dibujo
};