#include <iostream>
#include "randomDelayPlugin.hpp"

START_NAMESPACE_DISTRHO
// -----------------------------------------------------------------------

RandomDelayPlugin::RandomDelayPlugin()
	: Plugin(paramCount, 1, 0) // 1 program, 0 states
{
	// set default values
	loadProgram(0);

	// reset
	reset();
}

RandomDelayPlugin::~RandomDelayPlugin()
{
}

// -----------------------------------------------------------------------
// Init

void RandomDelayPlugin::initParameter(uint32_t index, Parameter& parameter)
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

void RandomDelayPlugin::initProgramName(uint32_t index, String& programName)
{
	if (index != 0)
		return;

	programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float RandomDelayPlugin::getParameterValue(uint32_t index) const
{
	switch (index)
	{
	}
}

void RandomDelayPlugin::setParameterValue(uint32_t index, float value)
{
	switch (index)
	{
	}
}

void RandomDelayPlugin::loadProgram(uint32_t index)
{
}

void RandomDelayPlugin::reset()
{
}

// -----------------------------------------------------------------------
// Process

void RandomDelayPlugin::activate()
{
}

void RandomDelayPlugin::deactivate()
{
}



void RandomDelayPlugin::run(const float** inputs, float** outputs, uint32_t frames)
{
	const float* input  = inputs[0];
	float*       output = outputs[0];
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
	return new RandomDelayPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

