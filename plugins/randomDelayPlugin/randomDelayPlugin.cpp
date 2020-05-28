#include <iostream>
#include "randomDelayPlugin.hpp"

START_NAMESPACE_DISTRHO
// -----------------------------------------------------------------------

RandomDelayPlugin::RandomDelayPlugin()
	:   Plugin(paramCount, 1, 0), // 1 program, 0 states
        //rng(rand_dev()), range(std::uniform_int_distribution<>(50, 700)) //random number generator initialization with delay range from 50ms to 700ms
        rng(rand_dev()), range(std::uniform_int_distribution<>(1,1000)) //random number generator init
{
    // Get the samplerate
    samplerate = getSampleRate();

    // Initialization for the delay
    delay.setSamplerate(samplerate);

    // Initialization for Aubio onset detector optimal for guitars
    onset_detector.setOnsetMethod("complex");
    onset_detector.setSilenceThreshold(-30.0f);
    onset_detector.setOnsetThreshold(0.6f);

    // random number generator init
    rng.seed(::time(NULL));

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
//    parameter.hints         = kParameterIsAutomable;
//    parameter.unit          = "%";
//    parameter.ranges.def    = 0.5f;
//    parameter.ranges.min    = 0.0f;
//    parameter.ranges.max    = 1.0f;

    //parameter.name        = ""; //max 5 char
    //parameter.symbol      = ""; //max 5 char

	switch (index)
	{
        case paramBpm:
            parameter.unit = "bpm";
            parameter.name = "BPM";
            parameter.symbol = "bpm";
            parameter.ranges.def = 120;
            parameter.ranges.min = 30;
            parameter.ranges.max = 240;
            break;
        case paramMin:
            parameter.hints = kParameterIsInteger;
            parameter.unit = "";
            parameter.name = "Min";
            parameter.symbol = "min";
            parameter.ranges.def = 1;
            parameter.ranges.min = 1;
            parameter.ranges.max = 9;
            break;
        case paramMax:
            parameter.hints = kParameterIsInteger;
            parameter.unit = "";
            parameter.name = "Max";
            parameter.symbol = "max";
            parameter.ranges.def = 6;
            parameter.ranges.min = 1;
            parameter.ranges.max = 9;
            break;
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
        case paramBpm:
            return bpm;
        case paramMin:
            return this->noteMin;
        case paramMax:
            return this->noteMax;
	}
}

void RandomDelayPlugin::setParameterValue(uint32_t index, float value)
{
	switch (index)
	{
        case paramBpm:
            bpm = value;
            break;
        case paramMin:
            if (value > this->noteMax) {
                //this->noteMax = value;
            }
            this->noteMin = value;
            break;
        case paramMax:
            if (value < this->noteMin){
                //this->noteMin = value;
            }
            this->noteMax = value;
            break;
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

    bool is_onset = onset_detector.process(input);
    if(is_onset) {
        int note_choice = ceil(range(rng)/(1000/(abs(noteMax - noteMin) + 1))) + noteMin;
        int delaytime = (60000/bpm) * 4; // time in ms that 4 beats (1 bar) takes
        switch(note_choice) {
            case 1:
                // sixteenth note
                delaytime = delaytime * 1/16;
                break;
            case 2:
                // dotted sixteenthnote
                delaytime = delaytime * 3/32;
                break;
            case 3:
                // eighth note
                delaytime = delaytime * 1/8;
                break;
            case 4:
                // dotted eighth note
                delaytime = delaytime * 3/16;
                break;
            case 5:
                // quarter note
                delaytime = delaytime * 1/4;
                break;
            case 6:
                // dotted quarter note
                delaytime = delaytime * 3/8;
                break;
            case 7:
                // half note
                delaytime = delaytime * 1/2;
                break;
            case 8:
                // dotted half note
                delaytime = delaytime * 3/4;
                break;
            case 9:
                // whole note
                delaytime = delaytime * 1;
                break;
        }

        delay.setDelayLength(delaytime);
    }

    delay.process(input,output,frames);
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
	return new RandomDelayPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

