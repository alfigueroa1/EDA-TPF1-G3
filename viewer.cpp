#include "viewer.h"
#include "model.h"

Viewer::Viewer() : windowList()
{
}

void Viewer::update(void* m)
{
	Model* model = (Model*)m;
	const MerkleTree* incoming = model->getOpenTree();
	if (incoming == nullptr) {
		//close all windows
		windowList.clear();
	}
	else {
		map<longN, treeWindow>::iterator it;
		if ((it = windowList.find(incoming->height)) == windowList.end())
		{
			windowList.emplace(incoming->height, *incoming);
			//agregar ventana
		}
		else
		{
			it->second.replace(*incoming);
			//Reemplazar existente
		}
	}
}

void Viewer::cycle(void)
{
	if (windowList.empty() == false) {

		map<longN, treeWindow>::iterator closing, it; //auto no me salvo de esta
		bool closeWindow = false;

		for (it = windowList.begin(); it != windowList.end(); it++) {
			it->second.draw();
			if (it->second.isOpen() == false) {
				closeWindow = true;
				closing = it;
			}
		}

		if (closeWindow == true) {
			windowList.erase(closing);
		}

	}
}
