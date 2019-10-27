#pragma once


#include "blockChain.h"
#include "subject.h"


extern MerkelTree arrMarineros[9];

class alex_model : public Subject {
public:
	alex_model() : selectedBlock(1), selectedBlockChain(1),
	ready(false), tree(){

	}
	~alex_model() {

	}

	//from controller
	void openBlockChain(int i) {
		selectedBlockChain = i;
		ready = false;
		notifyAllObservers();
	}

	void openBlock(int i) {
		selectedBlock = i;
		ready = true;
		//getTree();
		notifyAllObservers();
	}

	longN getNumberOfBlocks(void) {
		return 3;
	}

	//from viewer
	const MerkelTree* getOpenTree() {
		if (ready)
			return &(arrMarineros[3 * (selectedBlockChain - 1) + (selectedBlock - 1)]);
		else
			return nullptr;
	}

private:
	int selectedBlockChain;
	int selectedBlock;
	MerkelTree tree;
	bool ready;

	//void getTree(void) {
	//	tree = arrMarineros[3*(selectedBlockChain-1)+(selectedBlock-1)];
	//}
};