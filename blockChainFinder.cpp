#include "blockChainFinder.h"
#include <iostream>
#include <fstream>
#include <intrin.h>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

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