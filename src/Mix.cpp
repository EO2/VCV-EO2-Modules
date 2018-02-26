#include "EO2.hpp"
#include "rack.hpp"

#define nCHANNELS 16
#define nAUX 4
#define nBUS 4

struct Mix : Module {
	enum ParamIds {
		MIX_VOL,
		VOL, // 18, 20  // VOL_POT VOL[nCHANNELS]
		PAN,
		MUTE,
		SOLO,
		SEND1, // SENDS 1-4+ * 16
		SEND2,
		SEND3,
		SEND4,
		RECEIVE, // 1-4 total
		BUS1, // BUSES / GROUPS
		BUS2,
		BUS3,
		BUS4,
		nPARAMS
	};
	enum InputIds {
		CH_IN,  // 16
		AUX_IN, // 4
		LINK_IN,// 2
		CV_VOL, // 1
		CV_PAN, // 1
		CV_AUX, // 4
		nINPUTS
	};
	enum OutputIds {
		MIX_OUT, 	//2
		CH_OUT, 	//2,4 // 16,18
		AUX_OUT, 	//4
		BUS_OUT, 	//4
		LINK_OUT, //2
		nOUTPUTS
	};
	enum LightIds {
		VU_LIGHT,	// 1
		MUTE_LIGHT,
		nLIGHTS
	};


	Mix() : Module(nPARAMS, nINPUTS, nOUTPUTS, nLIGHTS) {}
	void step() override;

	/*
	for (var i = 0; i < lengthOf(CH_IN); i++) {
		VOL[i] = 0.0f;
		PAN[i] = 0.5f;
		MUTE[i] = false;
		SOLO[i] = false;
		SEND1[i] = 0.0f; // for (1-4) do
		SEND2[i] = 0.0f;
		SEND3[i] = 0.0f;
		SEND4[i] = 0.0f;
		BUS1[i] = false;
		BUS2[i] = false;
		BUS3[i] = false;
		BUS4[i] = false;
	}

	bool	bMuteStates[ nCHANNELS ] = {};
	bool  bSoloStates[ nCHANNELS ] = {};

	float mixL = 0.0f;
	float mixR = 0.0f;

	float aux1_receive = 0.0f;
	float aux2_receive = 0.0f;
	float aux3_receive = 0.0f;
	float aux4_receive = 0.0f;
*/
	/*
	json_t *toJson() override {
		json_t *json = json_object();
		json_t *mute = json_array();

		json_t *m1 = json_integer((int) ch1m);
		json_t *m2 = json_integer((int) ch2m);

		json_array_append_new(mute, m1);
		json_array_append_new(mute, m2);

		return json;
	}
	void fromJson(json_t *json) override {
		json_t *mute = json_object_get(json, "MixMute");
		
		json_t *m1 = json_array_get(mute, 0);
		json_t *m2 = json_array_get(mute, 1);

		ch1m = !!json_integer_value(m1);
		ch2m = !!json_integer_value(m2);
	}*/
};


void Mix::step() {
	//https://developer.gnome.org/glib/stable/glib-Standard-Macros.html#CLAMP:CAPS
	#define clamp(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
/*
	// Channels
	for (var i = 0; i < lengthOf(CH_IN); i++) {
		// Inputs
		float ch = inputs[CH_IN[i]].value * params[CH1_P].value * clamp(inputs[CV1_VOL_IN].normalize(10.0f) / 10.0f, 0.0f, 1.0f);

		// Outputs
		outputs[CH_OUT[i]].value = ch;
	}

	// Main Out
	//float cv1_vol = fmaxf(inputs[CV1_VOL_IN].normalize(10.0f) / 10.0f, 0.0f);
	float cv_mix_vol = fmaxf(inputs[CV_MIX_VOL_IN].normalize(10.0f) / 10.0f, 0.0f);
	float mix = (ch1 + ch2) * params[MIX_P].value * cv_mix_vol; // ch ch[i]
	outputs[MIX_OUT].value = mix;

	lights[VU_LIGHT].value = mix;
*/
}


MixWidget::MixWidget() {
	Mix *module = new Mix();
	setModule(module);
	box.size = Vec(18 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Mix.svg")));
		addChild(panel);
	}

	//todo: SVGKnob, SVGSlider, SVGSwitch, SVGPort, SVGScrew, (SVGPanel), etc..  all in one svg, named? SpriteKnob..

	// Channels 
	
	for (int i = 0; i < 16; i++) {
		addInput(createInput<EO2_Port>(Vec(RACK_GRID_WIDTH/3, RACK_GRID_WIDTH/2), module, Mix::CH_IN));

		addInput(createInput<EO2_Port>(Vec(RACK_GRID_WIDTH/3, RACK_GRID_WIDTH*2), module, Mix::CH_IN));
		addInput(createInput<EO2_Port>(Vec(RACK_GRID_WIDTH/3, RACK_GRID_WIDTH*2.5), module, Mix::CH_IN));
		addInput(createInput<EO2_Port>(Vec(RACK_GRID_WIDTH/3, RACK_GRID_WIDTH*3), module, Mix::CH_IN));

		addParam(createParam<EO2_RedKnob>(Vec(1.5, RACK_GRID_WIDTH*4), module, Mix::CV_VOL, -0.1, 1.0, 0.0)); // gain..
		addParam(createParam<EO2_GreenKnob>(Vec(1.5, RACK_GRID_WIDTH*5), module, Mix::CV_VOL, -0.1, 1.0, 0.0));
		addParam(createParam<EO2_BlueKnob>(Vec(1.5, RACK_GRID_WIDTH*6), module, Mix::CV_PAN, -0.1, 1.0, 0.0));

		addParam(createParam<EO2_RedKnob>(Vec(1.5, RACK_GRID_WIDTH*8), module, Mix::CV_AUX, -0.1, 1.0, 0.0));
		addParam(createParam<EO2_GreenKnob>(Vec(1.5, RACK_GRID_WIDTH*9), module, Mix::CV_AUX, -0.1, 1.0, 0.0));
		addParam(createParam<EO2_BlueKnob>(Vec(1.5, RACK_GRID_WIDTH*10), module, Mix::CV_AUX, -0.1, 1.0, 0.0));
		addParam(createParam<EO2_YellowKnob>(Vec(1.5, RACK_GRID_WIDTH*11), module, Mix::CV_AUX, -0.1, 1.0, 0.0));

		addParam(createParam<EO2_RedKnob>(Vec(1.5, RACK_GRID_WIDTH*14), module, Mix::MIX_VOL, -0.1, 1.0, 0.0));
	}
	
	// Master
	//addParam(createParam<EO2_RedKnob>(Vec(1.5, RACK_GRID_WIDTH*14), module, Mix::MIX_VOL, -0.1, 1.0, 0.0));
}