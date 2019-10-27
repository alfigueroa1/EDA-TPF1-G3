/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "model.h"

 /*******************************************************************************
  * CASS METHODS DEFINITIONS
  ******************************************************************************/

Model::Model(void)
{
	curr = 0;
}

Model::~Model(void)
{

}


Block Model::getBlock(void)
{
	if (!(blockChain.empty()))
	{
		return blockChain[curr];
	}
}



unsigned long int Model::getNumberOfBlocks(void) { return blockChain.size(); }
unsigned int Model::getCurr(void){ return curr; }

