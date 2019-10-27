#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "imgui.h"
#include "imgui_impl_allegro5.h"

#include "controller.h"
#include "model.h"
#include "viewer.h"

static void init_interface(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue);
static void close_interface(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue);

static void start_frame(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue,bool& running);
static void end_frame(ImVec4 color);


void alexTesteaImGui(void);
#define SCREEN_WIDTH	1280
#define	SCREEN_HEIGHT	720

int main() {
	alexTesteaImGui();
	return 0;
}

void alexTesteaImGui(void) {

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;

	init_interface(display, queue);
	ImVec4 backColor = ImVec4(0.f, 0.75f, 0.75f, 1.f);

	Model m;
	Controller c(m);
	Viewer v;

	m.attach(c);
	m.attach(v);

	bool running = true;
	while (running) {
		start_frame(display, queue, running);

		c.cycle();
		v.cycle();

		end_frame(backColor);
	}
	close_interface(display, queue);
}




static void init_interface(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue) {
	//Inicializa Allegro
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	al_set_window_title(display, "TP FINAL PARTE 1");
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	//Inicializa ImGui
	IMGUI_CHECKVERSION(); //?
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();
	ImGui_ImplAllegro5_Init(display);
}
static void close_interface(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue) {
	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();
	al_destroy_event_queue(queue);
	al_destroy_display(display);
}


static void start_frame(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue, bool& running) {
	ALLEGRO_EVENT ev;
	while (al_get_next_event(queue, &ev)) {
		ImGui_ImplAllegro5_ProcessEvent(&ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
		if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
			ImGui_ImplAllegro5_InvalidateDeviceObjects();
			al_acknowledge_resize(display);
			ImGui_ImplAllegro5_CreateDeviceObjects();
		}
	}

	ImGui_ImplAllegro5_NewFrame();
	ImGui::NewFrame();
}

static void end_frame(ImVec4 color) {
	ImGui::Render();
	al_clear_to_color(al_map_rgba_f(color.x, color.y, color.z, color.w));
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
	al_flip_display();
}