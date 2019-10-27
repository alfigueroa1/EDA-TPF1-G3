/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "model.h"

 /*******************************************************************************
  * FUNCTION DECLARATIONS WITH FILE LEVEL SCOPE
  ******************************************************************************/
static unsigned int generateID(const char* str);
 /*******************************************************************************
  * CLASS METHODS DEFINITIONS
  ******************************************************************************/

Model::Model(void)
{
	curr = 0;
}

Model::~Model(void)
{

}

vector<string>* Model::getBlockChainNames(string path) {
	return finder.getValidJSONs(path);
}

void Model::openBlockChain(string path) {
	blockChain = finder.getBlockChain(path);
}

unsigned long int Model::getNumberOfBlocks() {
	return blockChain.size();
}

void Model::openBlock(unsigned long int b) {
	for (auto i = blockChain.begin(); i != blockChain.end(); i++) {
		if (i->height == b)
			curr = i;
	}
}

const MerkleTree* Model::getOpenTree() {
	tree.blockId = curr->blockId;
	tree.height = curr->height;
	tree.nonce = curr->nonce;
	tree.nTx = curr->nTx;
	tree.previousBlockId = curr->previousBlockId;
	//Missing: tree.merkleRoot, tree.tree. getMerkleTree takes care of that.
	getMerkleTree();
}

void Model::getMerkleTree() {
	unsigned long int transactions = curr->nTx;
	unsigned long int nearestPowerOf2 = pow(2, ceil(log(transactions) / log(2)));
	//Normalize floor of tree
	for (int i = 0; i < nearestPowerOf2; i++) {
		char aux[9];
		if (i < transactions) {
			unsigned int ID = generateID(curr->tx[i].txId.c_str());
			sprintf(&aux[0], "%x", ID);
			newIDstr newID(aux);
			tree.tree.push_back(newID);
		}
		else {
			unsigned int ID = generateID(curr->tx[transactions - 1].txId.c_str());
			sprintf(&aux[0], "%x", ID);
			newIDstr newID(aux);
			tree.tree.push_back(newID);
		}
	}
	int maxLvl = (log(nearestPowerOf2) / log(2));		//Max level es el nivel del arbol menos el MerkleRoot
	for (int i = maxLvl; i > 0; i --) {					//Itera por cada nivel del arbol menos el primero que ya esta normalizado
		for (int j = 0; j < (nearestPowerOf2 / (i + 1)); j++) {
			newIDstr ID1 = tree.tree[0];
			newIDstr ID2 = tree.tree[0];
		}
	}
	vector<newIDstr> aux;

}

Block Model::getBlock(void)
{
	if (!(blockChain.empty()))
	{
		return blockChain[curr];
	}
}

unsigned int Model::getCurr(void){ return curr; }

/*******************************************************************************
 * FUNCTION DEFINITIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static unsigned int generateID(const char* str) {
	unsigned int ID = 0;
	int c;
	while (c = *str++)
		ID = c + (ID << 6) + (ID << 16) - ID;

	return ID;
}