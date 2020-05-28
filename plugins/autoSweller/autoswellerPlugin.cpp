#include <iostream>
#include "autoswellerPlugin.hpp"

START_NAMESPACE_DISTRHO
// -----------------------------------------------------------------------

AutoSwellPlugin::AutoSwellPlugin()
	: Plugin(paramCount, 1, 0) // 1 program, 0 states
{
    samplerate = getSampleRate();

    adsr.setAttackRate(2.0f * samplerate);
    adsr.setDecayRate(0.0f);
    adsr.setReleaseRate(0.8f * samplerate);
    adsr.setSustainLevel(1.0f);
    adsr.setTargetRatioA(100.0f);
    adsr.setTargetRatioDR(100.0f);

    onset_detector.setOnsetMethod("complex");
    onset_detector.setSilenceThreshold(-30.0f);
    onset_detector.setOnsetThreshold(0.7f);

	// set default values
	loadProgram(0);

	// reset
	reset();
}

AutoSwellPlugin::~AutoSwellPlugin()
{
}

// -----------------------------------------------------------------------
// Init

void AutoSwellPlugin::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints         = kParameterIsAutomable;
    parameter.unit          = "S";
    parameter.ranges.def    = 0.5f;
    parameter.ranges.min    = 0.0f;
    parameter.ranges.max    = 1.0f;

    //parameter.name        = ""; //max 5 char
    //parameter.symbol      = ""; //max 5 char

	switch (index)
	{
        case paramAttack:
            parameter.name          = "Attack";
            parameter.symbol        = "attack";
            parameter.ranges.def    = 2.0f;
            parameter.ranges.min    = 0.1f;
            parameter.ranges.max    = 5.0f;
            break;
        case paramRelease:
            parameter.name          = "Release";
            parameter.symbol        = "release";
            parameter.ranges.def    = 0.8f;
            parameter.ranges.min    = 0.1f;
            parameter.ranges.max    = 5.1f;
            break;
        case paramPreFx:
//            parameter.hints         = kParameterIsAutomable | kParameterIsBoolean;
            parameter.name          = "PreFx";
            parameter.symbol        = "prefx";
            parameter.ranges.def    = 1.0f;
            parameter.ranges.min    = 0.0f;
            parameter.ranges.max    = 1.0f;
            break;
	}
}

void AutoSwellPlugin::initProgramName(uint32_t index, String& programName)
{
	if (index != 0)
		return;

	programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float AutoSwellPlugin::getParameterValue(uint32_t index) const
{
	switch (index)
	{
        case paramAttack:
            return adsr.getAttackRate() / samplerate;
        case paramRelease:
            return adsr.getReleaseRate() / samplerate;
        case paramPreFx:
            return this->adsrPreFx;
	}
}

void AutoSwellPlugin::setParameterValue(uint32_t index, float value)
{
	switch (index)
	{
        case paramAttack:
            adsr.setAttackRate(value * samplerate);
            break;
        case paramRelease:
            adsr.setReleaseRate(value * samplerate);
            if (value >= 5.0f) {
                noRelease = true;
            } else {
                noRelease = false;
            }
            releaseRate = value;
            break;
        case paramPreFx:
            adsrPreFx = value;
            break;
	}
}

void AutoSwellPlugin::loadProgram(uint32_t index)
{
}

void AutoSwellPlugin::reset()
{
}

// -----------------------------------------------------------------------
// Process

void AutoSwellPlugin::activate()
{
}

void AutoSwellPlugin::deactivate()
{
}



void AutoSwellPlugin::run(const float** inputs, float** outputs, uint32_t frames)
{
	const float* input  = inputs[0];
	float*       output = outputs[0];

    const float* retrn   = inputs[1];
    float*       send  = outputs[1];

    float is_onset = onset_detector.process(input);
    if (is_onset) {
        if (noRelease) {
            adsr.setReleaseRate(0.01f * samplerate);
            adsr.gate(false);
        }
        adsr.gate(true);
        adsr.setReleaseRate(releaseRate * samplerate);
    }

    for(int i = 0; i < frames; i++) {
        if ((adsr.getState() == ADSR::env_decay || adsr.getState() == ADSR::env_sustain) && noRelease == false) {
            adsr.gate(false);
        }
        if (adsrPreFx >= 0.5f) {
            send[i] = adsr.process_tanh() * input[i];
            output[i] = (input[i] + retrn[i]) * 0.5;
        } else {
            send[i] = input[i];
            output[i] = (input[i] + (retrn[i] * adsr.process_tanh())) * 0.5;
        }
    }
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
	return new AutoSwellPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

