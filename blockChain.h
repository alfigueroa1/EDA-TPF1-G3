#pragma once
#include <string>
#include <vector>

using namespace std;

struct Transaction {
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

};

typedef vector<Block> BlockChain;