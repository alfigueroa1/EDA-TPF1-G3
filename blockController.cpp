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
	lastPath = "";
}

void blockController::update(void* model) {
	m = (Model*)model;
}

void blockController::cycle() {
	if (lastPath != m->getPath()) {
		askBlock(m->getPath());
		lastPath = m->getPath();
	}
	else
		selectBlock(getFilename(m->getPath()));
}


void blockController::askBlock(string path) 
{
	blocks.clear();
	m->clearBlockChain();
	m->openBlockChain(path);

	for (int i = 0; i < m->getNumberOfBlocks(); i++) {

		//m->resetCurr();
		blocks += "Block" + to_string(i);
		blocks += '\0';
	}
	blocks += '\0';
}

void blockController::selectBlock(string filename) {
	ImGui::Begin("Block Selection");
	ImGui::Text("Archivo: %s", filename.c_str());
	if (m->getNumberOfBlocks() == 1)
		ImGui::Text("Se encontro 1 bloque:");
	else if (m->getNumberOfBlocks() == 0)
		ImGui::Text("No se encontraron bloques");
	else
		ImGui::Text("Se encontraron %d bloques:", m->getNumberOfBlocks());

	ImGui::Text("Seleccione el bloque que desee abrir");

	ImGui::NewLine();

	if (ImGui::Combo("Bloques", &currBlock, blocks.c_str()))
	{
		m->resetCurr();
		m->openBlock((m->getCurr())[currBlock].height);
	}

	ImGui::End();
}

string blockController::getFilename(string filepath) {
	int place = filepath.find_last_of('/');
	filepath.erase(0, place + 1);
	return filepath;
}

