#pragma once

#include "blockChain.h"

class treeWindow
{
public:
	treeWindow(const MerkleTree& tree);
	void replace(const MerkleTree& tree);
	void draw(void);
	bool isOpen(void);
private:
	MerkleTree tree;
	bool open;

	string windowName;

	bool validRoot;
	void validateRoot(void);

	void drawTree(void);
};

