#include "viewer.h"

Viewer::Viewer() : windowList()
{
}

void Viewer::update(void*)
{

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
