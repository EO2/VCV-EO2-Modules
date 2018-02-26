#include "EO2.hpp"
#include "rack.hpp"

#define nCHANNELS 16

struct Multi : Module {
	enum ParamIds {
		PARAM_VOLUME,
		nPARAMS
	};
	enum InputIds {
		IN,
		nINPUTS
	};
	enum OutputIds {
		OUT, // + 8
		nOUTPUTS
	};
	enum LightIds {
		LIGHT,
		nLIGHTS
	};

	Multi() : Module(nPARAMS, nINPUTS, nOUTPUTS, nLIGHTS) {}
	void step() override;
};


void Multi::step() {
	float volume = 0.0f;
	for (int i = 0; i < nCHANNELS; i++) {
		volume += inputs[i].value;
	}
	for (int i = 0; i < nCHANNELS; i++) {
		outputs[i].value = volume * PARAM_VOLUME; 	
	}
}


MultiWidget::MultiWidget() {
	Multi *module = new Multi();
	setModule(module);
	box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Multi.svg")));
		addChild(panel);
	}
	
	int start_pos = RACK_GRID_WIDTH + (RACK_GRID_WIDTH/2);
	int pos = start_pos;

	for (int i = 0; i < nCHANNELS; i++) {
		addInput(createInput<EO2_Port>(Vec(RACK_GRID_WIDTH/3, start_pos + (RACK_GRID_WIDTH*i)), module, i));
		addOutput(createOutput<EO2_Port>(Vec(RACK_GRID_WIDTH/3+RACK_GRID_WIDTH, start_pos + (RACK_GRID_WIDTH*i)), module, i));
		pos += RACK_GRID_WIDTH;
	}

	addParam(createParam<EO2_BlueKnob>(Vec(RACK_GRID_WIDTH/2, pos + start_pos), module, Multi::PARAM_VOLUME, -0.1, 1.0, 0.0));

}