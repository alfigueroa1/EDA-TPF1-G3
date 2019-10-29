#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "controller.h"
#include "model.h"


//CONTROLLER HANDLER
controllerHandler::controllerHandler(Model& model) {
	state = INIT;
	fc = new fileController(model);
	model.attach(*fc);
	bc = new blockController(model);
	model.attach(*bc);

}

controllerHandler::~controllerHandler() {
	delete fc;
	delete bc;
}

void controllerHandler::cycle() {
	string filename;
	if ((filename = fc->askPath()) != "")
		state = GET_BLOCK;

	if (state == GET_BLOCK) {
		bc->askBlock(filename);
		state = SHOW_BLOCK;
	}

	if (state == SHOW_BLOCK)
		bc->selectBlock();
}






