#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static AppTimer *timer;

static void timer_callback(void *data) {
  text_layer_set_text(text_layer, "Timer happened!");
}

void handle_init(void) {	
	// Setup the window
	window = window_create();
 	window_stack_push(window, true /* Animated */);
	
	// Setup the layer that will display the text
  	Layer *window_layer = window_get_root_layer(window);
  	GRect bounds = layer_get_frame(window_layer);
  	text_layer = text_layer_create((GRect){ .origin = { 0, 30 }, .size = bounds.size });
  	text_layer_set_text(text_layer, "Il treno per" "\nArriverà tra:");
  	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  	layer_add_child(window_layer, text_layer_get_layer(text_layer));

	
	timer = app_timer_register(1500 /* milliseconds */, timer_callback, NULL);
  	// A timer can be canceled with `app_timer_cancel()`
}

void handle_deinit(void) {
	text_layer_destroy(text_layer);
	window_destroy(window);
}

int main(void) {
	handle_init();
	
	app_event_loop();
	
	handle_deinit();
}
