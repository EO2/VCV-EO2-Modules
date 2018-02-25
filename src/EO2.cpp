#include "EO2.hpp"


Plugin *plugin;


void init(rack::Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);
	p->website = "https://github.com/EO2/VCV-EO2-Modules";
	p->manual = "https://github.com/EO2/VCV-EO2-Modules/blob/master/README.md";

	p->addModel(createModel<MixxxWidget>("EO2", "Mixxx", "Hardcore Mixxx", MIXER_TAG, AMPLIFIER_TAG));
}
