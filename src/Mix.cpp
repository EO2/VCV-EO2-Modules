#include "EO2.hpp"


struct Mix : Module {
	enum ParamIds {
		MIX_P,
		CH1_P,
		CH2_P,
		CH3_P,
		CH4_P,
		AUX1_P,
		AUX2_P,
		AUX3_P,
		AUX4_P,
		VOLUME_P,
		BALANCE_P,
		MUTE_P,
		SOLO_P,
		SEND_P,
		RECEIVE_P,
		VU_P,
		GROUP_P,
		NUM_PARAMS
	};
	enum InputIds {
		CH1_IN,
		CH2_IN,
		CH3_IN,
                CH4_IN,
                CH5_IN,
                CH6_IN,
                CH7_IN,
                CH8_IN,
                CH9_IN,
                CH10_IN,
                CH11_IN,
                CH12_IN,
                CH13_IN,
                CH14_IN,
                CH15_IN,
                CH16_IN,
		AUX1_IN, // L + R ?
		AUX2_IN,
		AUX3_IN,
		AUX4_IN,
		CV1_VOL_IN,
		CV1_BAL_IN,
		CV1_MUT_IN,
		CV1_SOL_IN,
		CV1_AUX1_IN, // CH1 Send1
		CV1_AUX2_IN,
		CV1_AUX3_IN,
		CV1_AUX4_IN,
		CV_MIX_VOL_IN,
		LINK_IN,
		NUM_INPUTS
	};
	enum OutputIds {
		MIX_OUT,
		L_OUT,
		R_OUT,
                CH1_OUT,
                CH2_OUT,
                CH3_OUT,
                CH4_OUT,
                CH5_OUT,
                CH6_OUT,
                CH7_OUT,
                CH8_OUT,
                CH9_OUT,
                CH10_OUT,
                CH11_OUT,
                CH12_OUT,
                CH13_OUT,
                CH14_OUT,
                CH15_OUT,
                CH16_OUT,
                AUX1_OUT,
                AUX2_OUT,
                AUX3_OUT,
                AUX4_OUT,
		L_REC_OUT,
		R_REC_OUT,
		L_MON_OUT,
		R_MON_OUT,
		BUS1_OUT,
		BUS2_OUT,
		BUS3_OUT,
		BUS4_OUT,
		LINK_OUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		VU_LIGHT,
		MUTE_LIGHT,
		NUM_LIGHTS
	};


	Mix() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
	
	//SchmittTrigger ch1mute;
	//SchmittTrigger ch2mute;

	float ch1m = false;
	float ch2m = false;

	float mixL = 0.0f;
	float mixR = 0.0f;
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
	//todo: fix missing clamp
	//https://developer.gnome.org/glib/stable/glib-Standard-Macros.html#CLAMP:CAPS
	#define clamp(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

	float ch1 = inputs[CH1_IN].value * params[CH1_P].value * clamp(inputs[CV1_VOL_IN].normalize(10.0f) / 10.0f, 0.0f, 1.0f);
	float ch2 = inputs[CH2_IN].value * params[CH2_P].value * clamp(inputs[CV1_VOL_IN].normalize(10.0f) / 10.0f, 0.0f, 1.0f);
	float cv1_vol = fmaxf(inputs[CV1_VOL_IN].normalize(10.0f) / 10.0f, 0.0f);
	float cv_mix_vol = fmaxf(inputs[CV_MIX_VOL_IN].normalize(10.0f) / 10.0f, 0.0f);
	float mix = (ch1 + ch2) * params[MIX_P].value * cv_mix_vol;

	outputs[CH1_OUT].value = ch1;
	outputs[CH2_OUT].value = ch2;
	outputs[MIX_OUT].value = mix;

	// lights
	lights[VU_LIGHT].value = mix;
}


MixWidget::MixWidget() {
	Mix *module = new Mix();
	setModule(module);
	box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Mix.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addParam(createParam<Davies1900hBlackKnob>(Vec(28, 87), module, Mix::MIX_P, -3.0, 3.0, 0.0));

	addInput(createInput<PJ301MPort>(Vec(33, 186), module, Mix::CV_MIX_VOL_IN));

	addOutput(createOutput<PJ301MPort>(Vec(33, 275), module, Mix::MIX_OUT));

	addChild(createLight<MediumLight<RedLight>>(Vec(41, 59), module, Mix::VU_LIGHT));
}
