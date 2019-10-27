#include "treeWindow.h"

#include "imgui.h"

treeWindow::treeWindow(const MerkelTree& t) :
	tree(t), open(true)
{
}

void treeWindow::replace(const MerkelTree& t)
{
	tree = t;
}