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
};

