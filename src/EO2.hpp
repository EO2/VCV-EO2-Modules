#include "rack.hpp"


using namespace rack;


extern Plugin *plugin;

// Widgets

struct MixWidget : ModuleWidget {
	MixWidget();
};

struct MultiWidget : ModuleWidget {
	MultiWidget();
};


// Colors

#define COLOR_SOFT_RED nvgRGB(0x6f, 0x17, 0x17)
#define COLOR_SOFT_GREEN nvgRGB(0x3f, 0x72, 0x31)
#define COLOR_SOFT_BLUE nvgRGB(0x31, 0x4a, 0x72)
#define COLOR_SOFT_YELLOW nvgRGB(0xd6, 0xaa, 0x0b)
#define COLOR_SOFT_GRAY nvgRGB(0xa9, 0xa9, 0xa9)
#define COLOR_MEDIUM_GRAY nvgRGB(0x62, 0x62, 0x62)
#define COLOR_HARD_GRAY nvgRGB(0x33, 0x33, 0x33)


// Components

struct EO2_Knob : SVGKnob {
	EO2_Knob() {
		//box.size = sw->box.size; //Vec(15, 15);
		minAngle = -0.83 * M_PI; // -0.75
		maxAngle = 0.83 * M_PI; // 0.75
		//setSVG(SVG::load(assetPlugin(plugin, "res/Knob.svg")));
		// todo: set svg color from script?
		sw->svg = SVG::load(assetPlugin(plugin, "res/Knob.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct EO2_RedKnob : EO2_Knob {
	EO2_RedKnob() {
		sw->svg = SVG::load(assetPlugin(plugin, "res/KnobRed.svg"));
	}
};

struct EO2_GreenKnob : EO2_Knob {
	EO2_GreenKnob() {
		sw->svg = SVG::load(assetPlugin(plugin, "res/KnobGreen.svg"));
	}
};

struct EO2_BlueKnob : EO2_Knob {
	EO2_BlueKnob() {
		sw->svg = SVG::load(assetPlugin(plugin, "res/KnobBlue.svg"));
	}
};

struct EO2_YellowKnob : EO2_Knob {
	EO2_YellowKnob() {
		sw->svg = SVG::load(assetPlugin(plugin, "res/KnobYellow.svg"));
	}
};

/*
struct EO2_SnapKnob : EO2_Knob {
	EO2_SnapKnob() {
		snap = true;
	}
}*/

/*
struct EO2_Slider : SVGSlider {
	EO2_Slider() {
		Vec margin = Vec(3.5, 3.5);
		maxHandlePos = Vec(-1, -2).plus(margin);
		minHandlePos = Vec(-1, 87).plus(margin);
		background->svg = SVG::load(assetPlugin("res/SliderBG.svg"));
		background->wrap();
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
		handle->svg = SVG::load(assetPlugin("res/Slider.svg"));
		handle->wrap();
	}
};
*/

struct EO2_Port : SVGPort {
	EO2_Port() {
		background->svg = SVG::load(assetPlugin(plugin, "res/Port.svg"));
		background->wrap();
		box.size = background->box.size;
	}
	// static Vec size(),pos() ?
};


/*
struct SoftBlueLight : ModuleLightWidget {
	SoftBlueLight() {
		addBaseColor(COLOR_SOFT_BLUE);
		//addBaseColor(COLOR_RED);
	}
};


template <typename BASE>
struct SuperTinyLight : BASE {
	SuperTinyLight() {
		this->box.size = mm2px(Vec(1.0, 1.0));
	}
};


struct EO2_Switch : SVGSwitch, ToggleSwitch {
	EO2_Switch() {
		addFrame(SVG::load(assetPlugin("res/Switch_0.svg")));
		addFrame(SVG::load(assetPlugin("res/Switch_1.svg")));
	}
};


struct EO2_Screw : SVGScrew {
	EO2_Screw() {
		sw->setSVG(SVG::load(assetPlugin("res/Screw.svg")))
	}
};


struct EO2_Panel : Panel {
	EO2_Panel() {
		backgroundColor = nvgRGB(0x10, 0xe1, 0x15);
	}
};
*/