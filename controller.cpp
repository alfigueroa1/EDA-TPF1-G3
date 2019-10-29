#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "controller.h"

fileController::fileController(Model& model) {
	m = &model;
	open = -1;
}

void fileController::update(void* model) {
	m = (Model*)model;
}

void fileController::cycle() {
	askPath();

	if (open >= 0) {
		string aux = path;
		aux += filenames[open];
		m->openBlockChain(aux);
	}

}

void fileController::askPath() {

	ImGui::Begin("Blockchain Files");
	ImGui::Text("Por favor especifique la carpeta con los archivos que desea");
	ImGui::Text("Recuerde que en Windows las carpetas se separan con \\");
	ImGui::NewLine();

	ImGui::InputText("Path", path, _MAX_PATH);
	ImGui::SameLine();
	if (ImGui::Button("Submit")) {
		filenames.clear();
		vector<string>* p = m->getBlockChainNames(path);		//busca los .json en el path
		for (int i = 0; i < p->size(); i++) {
			filenames.push_back((*p)[i]);
			open = -1;
		}
	}
	ImGui::NewLine();
	for (int i = 0; i < filenames.size(); i++) {
		if (ImGui::Selectable(filenames[i].c_str()))
			open = i;
	}

	ImGui::End();
}
