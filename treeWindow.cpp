#include "treeWindow.h"

#include "imgui.h"

#define verticalStep 25.
#define horizontalStep 25.

#define LEAF	ImVec4(0.0f,1.0f,0.0f,1.0f)
#define NODE	ImVec4(0.5f,0.5f,0.5f,1.0f)
#define ROOT	ImVec4(1.0f,0.0f,0.0f,1.0f)
#define CLEAF	ImVec4(0.0f,0.5f,0.0f,1.0f)
#define CNODE	ImVec4(0.25f,0.25f,0.25f,1.0f)

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
			longN uniques = leafs;
			vector<newIDstr>::iterator it = tree.tree.begin();

			for (floor = height; floor > 0; floor--, uniques = (uniques + (uniques&1))/2 ) {
				drawFloor(height, floor, uniques,it);
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

void treeWindow::drawFloor(const longN totalHeight, const longN floor, const longN uniques, vector<newIDstr>::iterator& it)
{
	longN nodes;
	if (uniques == 1)
		nodes = 1;
	else
		nodes = uniques + (uniques & 1);
	double offset = exp2((signed long)(totalHeight-floor-1)) * horizontalStep;
	double distance = 2 * offset;
	double verPos = verticalStep * floor;
	double horPos = offset;
	ImVec4 color;
	for (longN i = 0; i < nodes; i++, it++, horPos+=distance) {
		/*if (totalHeight == floor) {
			if (i < uniques) {
				marked = true;
			}
			else {
				marked = false;
			}
		}
		else {
			marked = false;
		}*/

		if (floor == 1) {
			color = ROOT;
		}
		else if (floor == totalHeight) {
			if (i < uniques)
				color = LEAF;
			else
				color = CLEAF;
		}
		else {
			if (i < uniques)
				color = NODE;
			else
				color = CNODE;
		}

		ImGui::PushID(i);
		ImGui::PushStyleColor(ImGuiCol_Button, color);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);

		ImGui::SetCursorPos(ImVec2(horPos, verPos));
		ImGui::Button("  ");
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Merkel: %s",it->c_str());
		}

		ImGui::PopStyleColor(3);
		ImGui::PopID();


	}
}