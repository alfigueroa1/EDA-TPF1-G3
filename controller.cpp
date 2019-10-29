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
	//selected = -1;
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
			aux = filenames[i];
			//selected = i;
	}

	ImGui::End();

	//if(selected != -1)

	return aux;
}


//BLOCK CONTROLLER
blockController::blockController(Model& model) {
	m = &model;
	currBlock = 1;
	//merkle = false;
}

void blockController::update(void* model) {
	m = (Model*)model;
}

void blockController::askBlock(string path) {
	m->openBlockChain(path);
	char num[11];

	for (int i = 0; i < m->getNumberOfBlocks(); i++) {
		sprintf_s(num, 11, "Bloque %d", i);
		blocks[i] = num;
	}

}

void blockController::selectBlock(void) {
	ImGui::Begin("Block Selection");
	ImGui::Text("Se encontraron %u bloques en el archivo seleccionado", m->getNumberOfBlocks());
	ImGui::Text("Seleccione el numero de bloque que desee abrir (Proximamente)");
	
	ImGui::NewLine();

	preview = blocks[currBlock];

	if (ImGui::BeginCombo("Bloques", preview)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < m->getNumberOfBlocks(); n++)
		{
			bool is_selected = (preview == blocks[n]);
			if (ImGui::Selectable(blocks[n], is_selected))
				preview = blocks[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		ImGui::EndCombo();
	}

	if(currBlock != -1)
		m->openBlock(currBlock + 1);

	ImGui::End();
}


//void blockController::openBlock(unsigned long int b) {
//	m->openBlock(b);
//
//	//ImGui::Begin("Block Selection");
//	ImGui::Text("Block ID: %u", m->getCurr()->blockId);
//	ImGui::Text("Previous Block ID: %u", m->getCurr()->previousBlockId);
//	ImGui::Text("Cantidad de transacciones: %u", m->getCurr()->nTx);
//	ImGui::Text("Nonce: %u", m->getCurr()->nonce);
//
//	if (ImGui::Button("Calculate Merkle Root"))
//		merkle = !merkle;
//
//	if (merkle) {
//		ImGui::Text("Merkle Root: %u", m->getCurr()->merkleRoot);
//		ImGui::SameLine();
//		if (ImGui::Button("Check Merkle Root")) {
//			//if(m->checkMerkleRoot())
//			ImGui::SameLine();
//			ImGui::Text("Valid");
//		}
//	}
//
//	if (ImGui::Button("Show Merkle Tree"));
//		//m->showOpenTree();
//
//	//ImGui::End();
//}





