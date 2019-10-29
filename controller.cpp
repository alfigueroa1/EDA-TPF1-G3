#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "controller.h"

fileController::fileController(Model& model) {
	m = &model;
	filenames.push_back("file1");
	filenames.push_back("file2");
	filenames.push_back("file3");

}

void fileController::update(void* model) {
	m = (Model*)model;
}

void fileController::cycle() {
	askPath();


}

void fileController::askPath() {

	ImGui::Begin("Window 1");
	ImGui::Text("Por favor especifique la carpeta con los archivos que desea");
	ImGui::Text("Recuerde que en Windows las carpetas se separan con \\");
	ImGui::NewLine();

	ImGui::InputText("Path", path, _MAX_PATH);
	ImGui::SameLine();
	if (ImGui::Button("Submit")) {
		//m->getFilenames(path, filenames);		//busca los .json en el path
	}

	for (int i = 0; i < filenames.size(); i++)
		ImGui::Selectable(filenames[i].c_str());

	ImGui::End();

}
