#pragma once

#include "alex_model.h"
#include "imgui.h"


class alex_controller : public Observer {
public:
	alex_controller(alex_model& m) : m(&m) {

	}

	virtual void update(void*) {
		//Pero el hechicero NI SE INMUTA!!!
	}
	void cycle(void) {
		//draw windows
		ImGui::Begin("Window 1");
		static int selectedBlockChain = 1;
		ImGui::InputInt("Select a BlockChain",&selectedBlockChain);
		if (ImGui::Button("Prev"))
			selectedBlockChain--;
		ImGui::SameLine();
		if (ImGui::Button("Next"))
			selectedBlockChain++;

		if (ImGui::Button("Open BlockChain")) {
			m->openBlockChain(selectedBlockChain);
		}
		ImGui::End();

		ImGui::Begin("Window 2");
		static int selectedBlock = 1;
		ImGui::InputInt("Select a Block", &selectedBlock);
		if (ImGui::Button("Prev"))
			selectedBlock--;
		ImGui::SameLine();
		if (ImGui::Button("Next"))
			selectedBlock++;
		if (ImGui::Button("Open Block")) {
			m->openBlock(selectedBlock);
		}
		ImGui::End();
	}
private:
	alex_model* m;
};