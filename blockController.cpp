#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "model.h"
#include "blockController.h"


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

	for (int i = 0; i < m->getNumberOfBlocks(); i++) {

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

	if (ImGui::Combo("Bloques", &currBlock, blocks.c_str()))
		m->openBlock(currBlock);

	ImGui::End();
}
