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
	void drawFloor(const longN totalHeight, const longN floor, const longN uniques, vector<newIDstr>::iterator& i);
};

