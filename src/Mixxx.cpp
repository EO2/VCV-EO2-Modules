#include "EO2.hpp"


struct Mixxx : Module {
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


	Mixxx() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
		//reset();
	}
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
		json_t *mute = json_object_get(json, 'MixxxMute');
		
		json_t *m1 = json_array_get(mute, 0);
		json_t *m2 = json_array_get(mute, 1);

		ch1m = !!json_integer_value(m1);
		ch2m = !!json_integer_value(m2);
	}*/
};

//Mixxx::Mixxx() : Module(NUM_PMS, NUM_INS, NUM_OUTS) {
//	reset();
//}


void Mixxx::step() {
	#define clamp(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
	float ch1 = inputs[CH1_IN].value * params[CH1_P].value * clamp(inputs[CV1_VOL_IN].normalize(10.0f) / 10.0f, 0.0f, 1.0f);
	float ch2 = inputs[CH2_IN].value * params[CH2_P].value * clamp(inputs[CV1_VOL_IN].normalize(10.0f) / 10.0f, 0.0f, 1.0f);
	float cv1_vol = fmaxf(inputs[CV1_VOL_IN].normalize(10.0f) / 10.0f, 0.0f);
	float cv_mix_vol = fmaxf(inputs[CV_MIX_VOL_IN].normalize(10.0f) / 10.0f, 0.0f);
	float mix = (ch1 + ch2) * params[MIX_P].value * cv_mix_vol;

	outputs[CH1_OUT].value = ch1;
	outputs[CH2_OUT].value = ch2;
	outputs[MIX_OUT].value = mix;
}


struct MixxxWidget : ModuleWidget {
	MixxxWidget(Mixxx *module);
};

// either pass module, or create in here..
// MixxxWidget() { Mixxx *module = new Mixxx(); setModule(module); //... }

MixxxWidget::MixxxWidget(Mixxx *module) : ModuleWidget(module) {

	setPanel(SVG::load(assetPlugin(plugin, 'res/Mixxx.svg')));

	addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 365)));
	/*

	addParam(ParamWidget::create<RoundLargeBlackKnob>(Vec(52, 58), module, Mixxx::MIX_P, 0.0f, 1.0f, 0.5f));
	addParam(ParamWidget::create<RoundBlackKnob>(Vec(57, 139), module, Mixxx::CH1_P, 0.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<RoundBlackKnob>(Vec(57, 219), module, Mixxx::CH2_P, 0.0f, 1.0f, 0.0f));
	addParam(ParamWidget::create<RoundBlackKnob>(Vec(57, 300), module, Mixxx::CH3_P, 0.0f, 1.0f, 0.0f));

	addInput(Port::create<PJ301MPort>(Vec(16, 69), Port::INPUT, module, Mixxx::MIX_CV_IN));
	addInput(Port::create<PJ301MPort>(Vec(22, 129), Port::INPUT, module, Mixxx::CH1_IN));
	addInput(Port::create<PJ301MPort>(Vec(22, 160), Port::INPUT, module, Mixxx::CH1_CV_IN));

addOutput(Port::create<PJ301MPort>(Vec(110, 69), Port::OUTPUT, module, Mixxx::MIX_OUT));

	addOutput(Port::create<PJ301MPort>(Vec(110, 145), Port::OUTPUT, module, Mixxx::CH1_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(110, 225), Port::OUTPUT, module, Mixxx::CH2_OUTPUT));
	*/
}


Model *modelMixxx = Model::create<Mixxx, MixxxWidget>('EO2', 'Mixxx', 'Hardcore Mixxx', MIXER_TAG, AMPLIFIER_TAG);
