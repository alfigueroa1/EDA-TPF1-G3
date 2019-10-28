#include "treeWindow.h"

#include "imgui.h"

#define verticalStep 25.
#define horizontalStep 25.

treeWindow::treeWindow(const MerkelTree& t) :
	tree(t), open(true), validRoot(false)
{
	windowName = "Bloque ";
	windowName += to_string(tree.height);

	validateRoot();

}

void treeWindow::replace(const MerkelTree& t)
{
	tree = t;

	validateRoot();
}

void treeWindow::draw(void) {
	ImGui::Begin(windowName.c_str(), &open);

	if (validRoot == false) {
		ImGui::Text("PRECAUCION! El MerkleRoot miembro del bloque, y el calculado a partir de las transacciones, no coinciden");
	}

	if (ImGui::TreeNode("Data")) {
		ImGui::Text("Numero de bloque: %lu", tree.height);
		ImGui::Text("ID del bloque: %s", tree.blockId.c_str());
		ImGui::Text("ID del bloque anterior: %s", tree.previousBlockId.c_str());
		ImGui::Text("Numero de transaccioens: %lu", tree.nTx);
		ImGui::Text("Nonce: %lu", tree.nonce);
		ImGui::Text("Merkel Root: %s", tree.merkleRoot.c_str());
		ImGui::TreePop();
	}

	drawTree();

	ImGui::End();
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
	if (ImGui::TreeNode("Merkle Tree")) {
		ImGui::BeginChild("child", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
		{
			longN leafs = tree.nTx;
			longN height = (longN)ceil(log2(leafs)) + 1;
			longN width = 1 << (height - 1);
			longN floor;
			vector<newIDstr>::iterator it = tree.tree.begin();

			for (floor = height; floor > 0; floor--) {
				drawFloor(height, floor, leafs,it);
			}


			/*
			static bool f = false;
			static bool t = true;
			ImGui::SetCursorPos(ImVec2(20,20));
			ImGui::Checkbox("", &t);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Oh Yeah Mr. Crabs!!");

			f = false;
			t = true;
			*/
		}
		ImGui::EndChild();
		ImGui::TreePop();
	}
	//TO DO!!!!
}

void treeWindow::drawFloor(const longN totalHeight, const longN floor, const longN leafs, vector<newIDstr>::iterator& it)
{
	longN nodes = 1 << (floor - 1);
	double offset = exp2((signed long)(totalHeight-floor-1)) * horizontalStep;
	double distance = 2 * offset;
	double verPos = verticalStep * floor;
	double horPos = offset;
	bool marked = false;
	for (longN i = 0; i < nodes; i++, it++, horPos+=distance) {
		if (floor != totalHeight)
			marked = false;
		else {
			if (i < leafs) {
				marked = true;
			}
			else {
				marked = false;
			}
		}
		ImGui::SetCursorPos(ImVec2(horPos, verPos));
		ImGui::Checkbox("", &marked);
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Merkel: %s",it->c_str());
		}
	}
}