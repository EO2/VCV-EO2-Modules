#include "EO2.hpp"


Plugin *plugin;


void init(rack::Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);
	p->website = "https://github.com/EO2/VCV-EO2-Modules";
	p->manual = "https://github.com/EO2/VCV-EO2-Modules/blob/master/README.md";

	p->addModel(createModel<MixWidget>("EO2", "Mix", "Mixer", MIXER_TAG, AMPLIFIER_TAG));
	p->addModel(createModel<MultiWidget>("EO2", "Multi", "Multiple", MIXER_TAG, AMPLIFIER_TAG));
}