#include "viewer.h"
#include "model.h"

Viewer::Viewer() : windowList()
{
}

void Viewer::update(void* m)
{
	Model* model = (Model*)m;
	const MerkelTree* incoming = model->getOpenTree();
	if (incoming == nullptr) {
		//close all windows
		windowList.clear();
	}
	else {
		map<string, treeWindow>::iterator it;
		if((it = windowList.find(incoming->merkleRoot)) == windowList.end() )
		//try to get a new window
	}
}

void Viewer::cycle(void)
{
	if (windowList.empty() == false) {

		std::_Tree_iterator<pair<string, treeWindow>>::value_type closing; //auto no me salvo de esta
		bool closeWindow = false;

		for (auto it : windowList) {
			it.second.draw();
			if (it.second.isOpen() == false) {
				closeWindow = true;
				closing = it;
			}
		}

		if (closeWindow == true) {
			windowList.erase(closing);
		}

	}
}
