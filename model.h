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

	//Metodos llamados desde el controller:

	//Cuando en la ventana 1 se selecciona un determinado Json:
	void openBlockChain(string path) {} //Abre el archivo apuntado por path (descarga su contenido, el de todos sus bloques, pero SIN CALCULAR LOS TREES)
	//Cuando en la ventana 2 se selecciono un determinado Bloque
	void openBlock(unsigned long int b) {}//"Abre" un determinado bloque: calcula el Merkel Tree, y lo deja a disposicion para obtenerlo con getOpenTree()
	//En cuanto se selecciono un archivo (en ventana 1), para poder tener un valor maximo en la ventana 2 (no tiene sentido q te dejen elegir Bloque 15 si solo hay 12)
	unsigned long int getNumberOfBlocks(void);//Devuelve el numero de bloques del BlockChain actualmente abierto

	//Metodos llamados desde el viewer
	//Nota de getOpenTree(): cuando se acaba de abrir un Chain, no se abrio todavia ningun bloque, por lo q esta funcion podria devolver nullptr. De este modo, evitamos el flag "CreateNewWindow"
	//Asimismo, solo si getOpenTree() devuelve null, se cierran todas las ventanas de merkel tree (del viewer) abiertas
	const MerkelTree* getOpenTree() {} //Devuelve la estructura del ultimo tree abierto (consecuencia de openBlock)
	//bool replaceLastTree(); //En caso de utilizar, en la ventana 2, teclas "Previous"/"Next", sera necesario una variable q valga FALSE si se llamo por ultima vez a openBlock, o TRUE, si se llamo a una hipotetica funcion openNext/openPrev

private:

	BlockChain blockChain;

};