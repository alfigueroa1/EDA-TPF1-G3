/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "blockChainFinder.h"
#include <iostream>
#include <fstream>
#include <intrin.h>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;


/*******************************************************************************
 * CASS METHODS DEFINITIONS
 ******************************************************************************/
BlockChainFinder::BlockChainFinder() {
	error = NO_BLOCK_ERROR;
}

BlockChainFinder::~BlockChainFinder() {

}
BlockChain BlockChainFinder::getBlockChain(string path) {
	BlockChain chain;


	return chain;
}

vector<string> BlockChainFinder::getJSONNames(string path) {
	string fileExtension;
	error = NO_BLOCK_ERROR;
	vector<string> jsons;
	jsons.clear();

	if (exists(path))    // Existe el path?
	{
		if (is_regular_file(path)) {        // El path es un archivo?
			cout << path << " size is " << file_size(path) << '\n';	//DEBUGGING
		}
		else if (is_directory(path)) {		// de no serlo, es una carpeta?
			cout << "Is a directory" << endl;
			for (directory_entry& x : directory_iterator(path))	//Recorre toda la carpeta, elemento a elemento.
			{
				fileExtension = extension(x.path());			//Obtiene la extension del archivo
				if (!fileExtension.find(".json"))					//Y verifica si es .json.
				{
					string aux;
					aux = x.path().generic_path().string().c_str();
					jsons.push_back(aux);
					//cout << aux << " es un archivo .json valido" << std::endl; //DEBUGGING
				}
			}
		}
		else {
			cout << path << " exists, but is not a regular file or directory\n"; //DEBUGGING
			error = INVALID_PATH;
		}
	}
	else {
		cout << path << " does not exist\n";	//DEBUGGING
		error = INVALID_PATH;
		return jsons;
	}
	if (jsons.empty())
		error = NOT_FOUND;
	return jsons;
}


vector<json> BlockChainFinder::getJSONs(string path) {
	vector<json> jsons;

	return jsons;
}



//Pueden cambiarle el nombre lo que devuelve y recibe
void JSONparse(Block& block)
{
	try
	{
		std::ifstream i("test.json"); //Se puede cambiar, no se como recibo el JSON;
		json j;

		i >> j;

		//Block 
		auto height = j["height"];
		block.height = height;

		auto nonce = j["nonce"];
		block.nonce = nonce;

		auto blockId = j["blockid"];
		block.blockId = blockId.get<string>();

		auto prevBlockId = j["previousblockid"];
		block.previousBlockId = prevBlockId.get<string>();

		auto root = j["merkleroot"];
		block.merkleRoot = root.get<string>();

		auto nTx = j["nTx"];
		block.nTx = nTx;

		//Transactions
		auto arrayTrans = j["tx"];
		for (auto& trans : arrayTrans)
		{
			Transaction auxTrans;

			auto txId = trans["txid"];
			auxTrans.txId = txId.get<string>();

			auto nTxIn = trans["nTxin"];
			auxTrans.nTxIn = nTxIn;

			auto vIn = trans["vin"];
			for (auto& elsi : vIn)
			{
				auto tBlockId = elsi["blockid"];
				auxTrans.vIn.blockId = tBlockId.get<string>();

				auto tTxId = elsi["txid"];
				auxTrans.vIn.txId = tTxId.get<string>();
			}

			auto nTxOut = trans["nTxout"];
			auxTrans.nTxOut = nTxOut;

			auto vOut = trans["vout"];
			for (auto& elso : vOut)
			{
				auto publicId = elso["publicid"];
				auxTrans.vOut.publicId = publicId.get<string>();

				auto amount = elso["amount"];
				auxTrans.vOut.amount = amount;
			}

			block.tx.push_back(auxTrans);
		}

	}

	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl; //Es posible que este mall el JSON?
	}

}