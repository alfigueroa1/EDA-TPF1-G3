#include "blockChain.h"

typedef MerkelTree arr[9];

arr arrMarineros{ {},{},{},{},{},{},{},{},{} };

void initAlex(void) {
	arr& a = arrMarineros;

	int i;

	i = 0;
	a[i].tree = {"A","B","C","D","AB","CB","ABCD"};
	a[i].height = 1;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "ABCD";
	a[i].nTx = 4;

	i = 1;
	a[i].tree = { "A","B","C","D","E","F","G","H","I","I","AB","CB","EF","GH","II","II","ABCD","EFGH","IIII","IIII","ABCDEFGH","IIIIIIII","ABCDEFGHIIIIIIII" };
	a[i].height = 2;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "ABCD";
	a[i].nTx = 9;

	i = 2;
	a[i].tree = { "A","B","C","D","E","F","AB","CD","EF","EF","ABCD","EFEF","ABCDEFEF"};
	a[i].height = 3;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "ABCD";
	a[i].nTx = 6;

	i = 3;
	a[i].tree = { "1","2","3","4","5","6","7","8","9","a","b","b","12","34","56","78","9a","bb","1234","5678","9abb","9abb","12345678","9abb9abb","123456789abb9abb" };
	a[i].height = 5;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "123456789abb9abb";
	a[i].nTx = 11;

	i = 4;
	a[i].tree = { "1","2","3","4","5","6","7","8","9","a","b","b","12","34","56","78","9a","bb","1234","5678","9abb","9abb","12345678","9abb9abb","123456789abb9abb"};
	a[i].height = 5;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "123456789abb9abb";
	a[i].nTx = 11;

	i = 5;
	a[i].tree = { "1","2","3","4","5","6","7","8","9","a","b","b","12","34","56","78","9a","bb","1234","5678","9abb","9abb","12345678","9abb9abb","123456789abb9abb" };
	a[i].height = 5;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "123456789abb9abb";
	a[i].nTx = 11;

	i = 6;
	a[i].tree = { "A","B","C","D","AB","CB","ABCD" };
	a[i].height = 7;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "ABCD";
	a[i].nTx = 4;

	i = 7;
	a[i].tree = { "A","B","C","D","E","F","G","H","I","I","I","I","I","I","I","I","AB","CB","EF","GH","II","II","II","II","ABCD","EFGH","IIII","IIII","ABCDEFGH","IIIIIIII","ABCDEFGHIIIIIIII" };
	a[i].height = 8;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "ABCD";
	a[i].nTx = 9;

	i = 8;
	a[i].tree = { "A","B","C","D","AB","CB","ABCD" };
	a[i].height = 9;
	a[i].nonce = 1234;
	a[i].blockId = "BLABLA";
	a[i].previousBlockId = "----";
	a[i].merkleRoot = "ABCD";
	a[i].nTx = 4;
}