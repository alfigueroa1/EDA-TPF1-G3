#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "observer.h"
#include "controller.h"
#include "model.h"
#include "fileController.h"
#include "blockController.h"
#include "controllerHandler.h"

//CONTROLLER HANDLER
controllerHandler::controllerHandler(Model& model) {
	state = INIT;
	controllers[FILE_C] = new fileController(model);
	controllers[BLOCK_C] = new blockController(model);
	m = &model;
}

controllerHandler::~controllerHandler() {
	for (int i = 0; i < MAX_CTRL; i++)
		delete controllers[i];
}

void controllerHandler::update(void* model) {
	for (int i = 0; i < MAX_CTRL; i++)
		controllers[i]->update((Model*)model);
}

void controllerHandler::cycle() {
	controllers[FILE_C]->cycle();
	if(m->getPath().size() && m->getPath().find('.') > 0)
		controllers[BLOCK_C]->cycle();
}

