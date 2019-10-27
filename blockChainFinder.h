#pragma once
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <string>
#include <vector>
#include "json.hpp"
#include "blockChain.h"

using namespace std;
using json = nlohmann::json;


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 *****************************************************************************/
typedef enum { NO_BLOCK_ERROR, NOT_FOUND, INVALID_JSON, EMPTY_FOLDER, INVALID_PATH } BlockChainError;


/*******************************************************************************
 * CLASS PROTOTYPE
 ******************************************************************************/
class BlockChainFinder 
{
public:
	BlockChainFinder();
	~BlockChainFinder();
	BlockChain getBlockChain(string path);
	vector<string>* getValidJSONs(string path);
	bool getJSONNames(string path);
	BlockChainError getError() { return error; }

private:
	vector<json> getJSONs(string path);


	vector<string> jsonNames;
	BlockChainError error;
};