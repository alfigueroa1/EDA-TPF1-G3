#pragma once
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "blockChain.h"
#include "subject.h"


/*******************************************************************************
 * CLASS PROTOTYPE
 ******************************************************************************/
class Model : public Subject 
{
public:
	Model(void);
	~Model(void);

	Block getBlock(void);
	unsigned int getCurr(void);


private:

	BlockChain blockChain;
	unsigned int curr;
};