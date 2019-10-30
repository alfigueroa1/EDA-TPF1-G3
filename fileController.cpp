#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "model.h"
#include "fileController.h"

//FILE CONTROLLER
fileController::fileController(Model& model) {
	m = &model;
}

void fileController::update(void* model) {
	m = (Model*)model;
}

void fileController::cycle() {
	askPath();
	string filename;
	if ((filename = drawFiles()) != "")
		m->setPath(filename);
}

void fileController::askPath() {

	ImGui::Begin("File Selector");
	ImGui::Text("Por favor especifique la carpeta con los archivos que desea");
	ImGui::Text("Recuerde que en Windows las carpetas se separan con \\");
	ImGui::NewLine();

	ImGui::InputText("Path", path, _MAX_PATH);
	ImGui::SameLine();
	if (ImGui::Button("Submit")) {
		filenames.clear();
		p = m->getBlockChainNames(path);		//busca los .json en el path
	}

	if (p != NULL) {
		filenames.clear();
		for (int i = 0; i < p->size(); i++)
			filenames.push_back((*p)[i]);
	}
	//else
		//ImGui::Text("El archivo no existe");
	
	if (filenames.size() == 1)
		ImGui::Text("Se encontro 1 archivo:");
	else if(filenames.size() > 0)
		ImGui::Text("Se encontraron %d archivos:", filenames.size());

	ImGui::End();
}


string fileController::drawFiles() {
	string aux = "";

	ImGui::Begin("File Selector");
	ImGui::NewLine();
	for (int i = 0; i < filenames.size(); i++) {
		if (ImGui::Selectable(filenames[i].c_str()))
			aux = filenames[i];
	}

	ImGui::End();

	return aux;
}







