#include <iostream>
#include "flangeronsetsyncplugin.hpp"

START_NAMESPACE_DISTRHO
// -----------------------------------------------------------------------

FlangerOnsetSyncPlugin::FlangerOnsetSyncPlugin()
	: Plugin(paramCount, 1, 0) // 1 program, 0 states
{
    flanger.setSamplerate(getSampleRate());

	// set default values
	loadProgram(0);

	// reset
	reset();
}

FlangerOnsetSyncPlugin::~FlangerOnsetSyncPlugin()
{
}

// -----------------------------------------------------------------------
// Init

void FlangerOnsetSyncPlugin::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints         = kParameterIsAutomable;
    parameter.unit          = "%";
    parameter.ranges.def    = 50.0f;
    parameter.ranges.min    = 0.0f;
    parameter.ranges.max    = 100.0f;

    //parameter.name        = ""; //max 5 char
    //parameter.symbol      = ""; //max 5 char

	switch (index)
	{
        case paramRate:
            parameter.name          = "Rate";
            parameter.symbol        = "rate";
            parameter.unit          = "Hz";
            parameter.ranges.def    = 0.5f;
            parameter.ranges.min    = 0.0001f;
            parameter.ranges.max    = 5.0f;
            break;
        case paramDepth:
            parameter.name          = "Depth";
            parameter.symbol        = "depth";
            parameter.unit          = "ms";
            parameter.ranges.def    = 6.0f;
            parameter.ranges.max    = 10.0f;
            break;
        case paramFeedback:
            parameter.name          = "Feedback";
            parameter.symbol        = "feedback";
            parameter.ranges.def    = 80.0f;
            parameter.ranges.max    = 99.0f;
            break;
        case paramPredelay:
            parameter.name          = "PreDelay";
            parameter.symbol        = "predelay";
            parameter.unit          = "ms";
            parameter.ranges.def    = 1.0f / getSampleRate();
            parameter.ranges.min    = 1.0f / getSampleRate();
            parameter.ranges.max    = 4.0f / getSampleRate();
            break;
	}
}

void FlangerOnsetSyncPlugin::initProgramName(uint32_t index, String& programName)
{
	if (index != 0)
		return;

	programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float FlangerOnsetSyncPlugin::getParameterValue(uint32_t index) const
{
	switch (index)
	{
        case paramRate:
            return flanger.getRate();
        case paramDepth:
            return flanger.getDepth();
        case paramFeedback:
            return flanger.getFeedback();
        case paramPredelay:
            return flanger.getPredelay();
	}
}

void FlangerOnsetSyncPlugin::setParameterValue(uint32_t index, float value)
{
	switch (index)
	{
        case paramRate:
            flanger.setRate(value);
            break;
        case paramDepth:
            flanger.setDepth(value);
            break;
        case paramFeedback:
            flanger.setFeedback(value);
            break;
        case paramPredelay:
            flanger.setPredelay(value);
            break;
	}
}

void FlangerOnsetSyncPlugin::loadProgram(uint32_t index)
{
}

void FlangerOnsetSyncPlugin::reset()
{
}

// -----------------------------------------------------------------------
// Process

void FlangerOnsetSyncPlugin::activate()
{
}

void FlangerOnsetSyncPlugin::deactivate()
{
}



void FlangerOnsetSyncPlugin::run(const float** inputs, float** outputs, uint32_t frames)
{
	const float* input  = inputs[0];
	float*       output = outputs[0];
    flanger.process(input, output, frames);
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
	return new FlangerOnsetSyncPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

