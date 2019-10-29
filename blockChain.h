#pragma once
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <string>
#include <vector>

using namespace std;

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 *****************************************************************************/
struct Vin
{
	string blockId;
	string txId;

};

struct Vout
{
	string publicId;
	unsigned long int amount;

};

struct Transaction
{
	string txId;
	unsigned long int nTxIn;
	vector<Vin> vIn;
	unsigned long int nTxOut;
	vector<Vout> vOut;

};

struct Block 
{
	vector<Transaction> tx;

	unsigned long int height;
	unsigned long int nonce;
	string blockId;
	string previousBlockId;
	string merkleRoot;
	unsigned long int nTx;
};

typedef vector<Block> BlockChain;

typedef std::string newIDstr;	//Cambie de parecer. Q los IDs sean strings
//typedef unsigned char newIDstr[4]; //antigua definicion
typedef unsigned long int longN;

struct MerkleTree { //COMPLETAR ACA CON LA FORMA EN Q SE GUARDA EL CONTENIDO DE UN TREE PROCESADO
	vector<newIDstr> tree;	//FORMATO	A B C D AB CD ABCD porq a Ale le parece mas facil de hacer

	longN height;
	longN nonce;
	string blockId;	//OJO CON STRINGS Y ARCHIVOS BINARIOS!!!
	string previousBlockId;
	newIDstr merkleRoot;
	longN nTx;

	//Constructor por defecto
	MerkleTree() : tree(), height(0), nonce(0), blockId(),
		previousBlockId(), merkleRoot(), nTx(0) {}
	//Constructor copiador
	MerkleTree(const MerkleTree& c):tree(c.tree), height(c.height), nonce(c.nonce), blockId(c.blockId),
		previousBlockId(c.previousBlockId), merkleRoot(c.merkleRoot), nTx(c.nTx) {}
	//Operador de asignacion
	MerkleTree& operator=(const MerkleTree& c) {
		tree = c.tree;
		height = c.height;
		nonce = c.nonce;
		blockId = c.blockId;
		previousBlockId = c.previousBlockId;
		merkleRoot = c.merkleRoot;
		nTx = c.nTx;
		return *this;
	}

};



/*struct Transaction {
	string hash;
	int ver;
	int vin_sz;
	int vout_sz;
	string lock_time;
	unsigned long int size;
	string relayed_by;
	unsigned int block_height;
	string tx_index;

	struct inputs {
		struct prev_out {
			string hash;
			string value;
			string tx_index;
			string n;
		};
		string script;
	};

	struct out {
		string value;
		string hash;
		string script;
	}out1, out2;
};

struct Block {
	string hash;
	int ver;
	string prev_block;
	string mrkl_root;
	unsigned long int time;
	unsigned long int bits;
	unsigned long int nonce;
	unsigned long int n_tx;
	unsigned long int size;
	unsigned long int block_index;
	bool main_chain;
	unsigned long int height;
	unsigned long long int received_time;
	string relayed_by;
	vector<Transaction> tx;

};*/
