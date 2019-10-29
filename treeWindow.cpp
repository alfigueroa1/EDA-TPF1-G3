#include "treeWindow.h"

#include "imgui.h"

treeWindow::treeWindow(const MerkleTree& t) :
	tree(t), open(true), validRoot(false)
{
	windowName = "Bloque ";
	windowName += to_string(tree.height);

	validateRoot();

}

void treeWindow::replace(const MerkleTree& t)
{
	tree = t;

	validateRoot();
}

void treeWindow::draw(void) {
	ImGui::Begin(windowName.c_str(),&open);
	ImGui::Text("Numero de bloque: %lu",tree.height);
	ImGui::Text("ID del bloque: %s",tree.blockId.c_str());
	ImGui::Text("ID del bloque anterior: %s", tree.previousBlockId.c_str());
	ImGui::Text("Numero de transaccioens: %lu", tree.nTx);
	ImGui::Text("Nonce: %lu", tree.nonce);

	if (validRoot == false) {
		ImGui::Text("PRECAUCION! El MerkleRoot miembro del bloque, y el calculado a partir de las transacciones, no coinciden");
	}

	drawTree();

	ImGui::End;
}

bool treeWindow::isOpen(void)
{
	return open;
}

void treeWindow::validateRoot(void)
{
	if (tree.merkleRoot == tree.tree.back()) {
		validRoot = true;
	}
	else {
		validRoot = false;
	}
}

void treeWindow::drawTree(void)
{
	//TO DO!!!!
}