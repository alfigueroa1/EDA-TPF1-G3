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
	if ((filename = fc->askPath()) != " ")
		state = GET_BLOCK;

	if (state == GET_BLOCK) {
		bc->askBlock(filename);
		state = SHOW_BLOCK;
	}

	if (state == SHOW_BLOCK)
		bc->selectBlock();

}




//FILE CONTROLLER
fileController::fileController(Model& model) {
	m = &model;
}


void fileController::update(void* model) {
	m = (Model*)model;
}


string fileController::askPath() {
	string aux = " ";

	ImGui::Begin("File Selector");
	ImGui::Text("Por favor especifique la carpeta con los archivos que desea");
	ImGui::Text("Recuerde que en Windows las carpetas se separan con \\");
	ImGui::NewLine();

	ImGui::InputText("Path", path, _MAX_PATH);
	ImGui::SameLine();
	if (ImGui::Button("Submit")) {
		filenames.clear();
		vector<string>* p = m->getBlockChainNames(path);		//busca los .json en el path
		if (p != NULL)
			for (int i = 0; i < p->size(); i++)
				filenames.push_back((*p)[i]);
	}

	ImGui::NewLine();
	for (int i = 0; i < filenames.size(); i++) {
		if (ImGui::Selectable(filenames[i].c_str()))
			aux = filenames[i];
	}

	ImGui::End();

	return aux;
}


//BLOCK CONTROLLER
blockController::blockController(Model& model) {
	m = &model;
	currBlock = -1;
	blocks = "";
}

void blockController::update(void* model) {
	m = (Model*)model;
}

void blockController::askBlock(string path) {
	//m->clearBlockChain();
	m->openBlockChain(path);

	for (int i = 1; i <= m->getNumberOfBlocks(); i++) {

		blocks += "Block" + to_string(i);
		blocks += '\0';
	}
	blocks += '\0';

}


void blockController::selectBlock(void) {
	ImGui::Begin("Block Selection");
	ImGui::Text("Se encontraron %u bloques en el archivo seleccionado", m->getNumberOfBlocks());
	ImGui::Text("Seleccione el numero de bloque que desee abrir (Proximamente)");

	ImGui::NewLine();

	if(ImGui::Combo("Bloques", &currBlock, blocks.c_str()))
		m->openBlock(currBlock + 1);

	ImGui::End();
}





