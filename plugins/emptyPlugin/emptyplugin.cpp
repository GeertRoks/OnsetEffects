#include <iostream>
#include "emptyplugin.hpp"

START_NAMESPACE_DISTRHO
// -----------------------------------------------------------------------

EmptyPlugin::EmptyPlugin()
	: Plugin(paramCount, 1, 0) // 1 program, 0 states
{
	// set default values
	loadProgram(0);

	// reset
	reset();
}

EmptyPlugin::~EmptyPlugin()
{
}

// -----------------------------------------------------------------------
// Init

void EmptyPlugin::initParameter(uint32_t index, Parameter& parameter)
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

void EmptyPlugin::initProgramName(uint32_t index, String& programName)
{
	if (index != 0)
		return;

	programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float EmptyPlugin::getParameterValue(uint32_t index) const
{
	switch (index)
	{
	}
}

void EmptyPlugin::setParameterValue(uint32_t index, float value)
{
	switch (index)
	{
	}
}

void EmptyPlugin::loadProgram(uint32_t index)
{
}

void EmptyPlugin::reset()
{
}

// -----------------------------------------------------------------------
// Process

void EmptyPlugin::activate()
{
}

void EmptyPlugin::deactivate()
{
}



void EmptyPlugin::run(const float** inputs, float** outputs, uint32_t frames)
{
	const float* input  = inputs[0];
	float*       output = outputs[0];
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
	return new EmptyPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

