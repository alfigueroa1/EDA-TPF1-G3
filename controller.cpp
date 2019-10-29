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
		state = BLOCK;

	if (state == BLOCK)
		bc->askBlock(filename);

}


//FILE CONTROLLER
fileController::fileController(Model& model) {
	m = &model;
	selected = -1;
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
		//		open = -1;
		vector<string>* p = m->getBlockChainNames(path);		//busca los .json en el path
		if (p != NULL)
			for (int i = 0; i < p->size(); i++)
				filenames.push_back((*p)[i]);
	}

	ImGui::NewLine();
	for (int i = 0; i < filenames.size(); i++) {
		if (ImGui::Selectable(filenames[i].c_str()))
			selected = i;
	}

	ImGui::End();

	if(selected != -1)
		aux = filenames[selected];

	return aux;
}


//BLOCK CONTROLLER
blockController::blockController(Model& model) {
	m = &model;
	currBlock = -1;
	merkle = false;
}

void blockController::update(void* model) {
	m = (Model*)model;
}

void blockController::askBlock(string path) {
	ImGui::Begin("Block Selection");
	m->openBlockChain(path);
	ImGui::Text("Se encontraron %u bloques en el archivo seleccionado", /*m->getNumberOfBlocks()*/2);
	ImGui::Text("Seleccione el numero de bloque que desee abrir");


	ImGui::NewLine();
	string blocks = "";
	for (int i = 1; i <= /*m->getNumberOfBlocks()*/2; i++) {

		blocks += "Block" + to_string(i);
		blocks += '\0';
	}
	blocks += '\0';
	ImGui::Combo("Bloques", &currBlock, blocks.c_str());

	if(currBlock != -1)
		openBlock(currBlock + 1);

	ImGui::End();
}


void blockController::openBlock(unsigned long int b) {
	m->openBlock(b);

	//ImGui::Begin("Block Selection");
	ImGui::Text("Block ID: %u", m->getCurr()->blockId);
	ImGui::Text("Previous Block ID: %u", m->getCurr()->previousBlockId);
	ImGui::Text("Cantidad de transacciones: %u", m->getCurr()->nTx);
	ImGui::Text("Nonce: %u", m->getCurr()->nonce);

	if (ImGui::Button("Calculate Merkle Root"))
		merkle = !merkle;

	if (merkle) {
		ImGui::Text("Merkle Root: %u", m->getCurr()->merkleRoot);
		ImGui::SameLine();
		if (ImGui::Button("Check Merkle Root")) {
			//if(m->checkMerkleRoot())
			ImGui::SameLine();
			ImGui::Text("Valid");
		}
	}

	if (ImGui::Button("Show Merkle Tree"));
		//m->showOpenTree();

	//ImGui::End();
}





