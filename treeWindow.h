#pragma once

#include "blockChain.h"

class treeWindow
{
public:
	treeWindow(const MerkelTree& tree);
	void replace(const MerkelTree& tree);
	void draw(void);
	bool isOpen(void);
private:
	MerkelTree tree;
	bool open;

	string windowName;

	bool validRoot;
	void validateRoot(void);

	void drawTree(void);
	void drawFloor(const longN totalHeight, const longN floor,const longN leafs, vector<newIDstr>::iterator& i);
};

