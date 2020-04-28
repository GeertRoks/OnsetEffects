#include <iostream>
#include "onsetDistortionPlugin.hpp"

START_NAMESPACE_DISTRHO
// -----------------------------------------------------------------------

OnsetDistortionPlugin::OnsetDistortionPlugin()
	: Plugin(paramCount, 1, 0) // 1 program, 0 states
{
	// set default values
	loadProgram(0);

	// reset
	reset();
}

OnsetDistortionPlugin::~OnsetDistortionPlugin()
{
}

// -----------------------------------------------------------------------
// Init

void OnsetDistortionPlugin::initParameter(uint32_t index, Parameter& parameter)
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

void OnsetDistortionPlugin::initProgramName(uint32_t index, String& programName)
{
	if (index != 0)
		return;

	programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float OnsetDistortionPlugin::getParameterValue(uint32_t index) const
{
	switch (index)
	{
	}
}

void OnsetDistortionPlugin::setParameterValue(uint32_t index, float value)
{
	switch (index)
	{
	}
}

void OnsetDistortionPlugin::loadProgram(uint32_t index)
{
}

void OnsetDistortionPlugin::reset()
{
}

// -----------------------------------------------------------------------
// Process

void OnsetDistortionPlugin::activate()
{
}

void OnsetDistortionPlugin::deactivate()
{
}



void OnsetDistortionPlugin::run(const float** inputs, float** outputs, uint32_t frames)
{
	const float* input  = inputs[0];
	float*       output = outputs[0];
    distortion.process(input, output, frames);
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
	return new OnsetDistortionPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

