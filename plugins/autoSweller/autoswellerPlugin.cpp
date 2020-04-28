#include <iostream>
#include "autoswellerPlugin.hpp"

START_NAMESPACE_DISTRHO
// -----------------------------------------------------------------------

AutoSwellPlugin::AutoSwellPlugin()
	: Plugin(paramCount, 1, 0) // 1 program, 0 states
{
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
    parameter.unit          = "%";
    parameter.ranges.def    = 0.5f;
    parameter.ranges.min    = 0.0f;
    parameter.ranges.max    = 1.0f;

    //parameter.name        = ""; //max 5 char
    //parameter.symbol      = ""; //max 5 char

	switch (index)
	{
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
	}
}

void AutoSwellPlugin::setParameterValue(uint32_t index, float value)
{
	switch (index)
	{
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

    for(int i = 0; i < frames; i++) {
//        output[i] = input[i];
        send[i] = input[i];
        output[i] = (input[i] + retrn[i]) * 0.5;
    }
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
	return new AutoSwellPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

