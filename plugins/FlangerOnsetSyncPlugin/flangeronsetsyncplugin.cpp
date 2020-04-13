#include <iostream>
#include "flangeronsetsyncplugin.hpp"

START_NAMESPACE_DISTRHO
// -----------------------------------------------------------------------

FlangerOnsetSyncPlugin::FlangerOnsetSyncPlugin()
	: Plugin(paramCount, 1, 0) // 1 program, 0 states
{
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
    parameter.ranges.def    = 0.5f;
    parameter.ranges.min    = 0.0f;
    parameter.ranges.max    = 1.0f;

    //parameter.name        = ""; //max 5 char
    //parameter.symbol      = ""; //max 5 char

	switch (index)
	{
        case paramDelay:
            parameter.name          = "Delay";
            parameter.symbol        = "delay";
            parameter.ranges.def    = 50.0f;
            parameter.ranges.min    = 1.0f;
            parameter.ranges.max    = 960.0f;
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
        case paramDelay:
            return 0.0f;
	}
}

void FlangerOnsetSyncPlugin::setParameterValue(uint32_t index, float value)
{
	switch (index)
	{
        case paramDelay:
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

