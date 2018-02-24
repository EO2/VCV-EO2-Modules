#include "EO2.hpp"


Plugin *plugin;


void init(rack::Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	p->addModel(modelMixxx); 


	/* 'createModel' here or in Module?
	p->addModel(createModel<BraidsWidget>("Audible Instruments", "Braids", "Macro Oscillator", OSCILLATOR_TAG, WAVESHAPER_TAG));
	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
	*/
}
