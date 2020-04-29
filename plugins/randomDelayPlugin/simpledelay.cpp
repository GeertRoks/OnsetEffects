#include "simpledelay.hpp"
#include <iostream>

SimpleDelay::SimpleDelay() {
    delayBuffer = new float[2 * this->maxFs](); // Max length is 2 seconds with 96000Hz(the max sampling frequency)
}
SimpleDelay::~SimpleDelay() {
    delete [] delayBuffer;
    delayBuffer = nullptr;
}

void SimpleDelay::process(const float* input, float* output, int frames) {
    for(int i = 0; i < frames; i++) {
        output[i] = 0.5 * input[i] + 0.5 * delayBuffer[readhead];
        delayBuffer[writehead] = output[i] * this->fdbck;
        tick();
    }
}

void SimpleDelay::setDelayLength(int delay_ms) {
    this->delay_smpl = int(delay_ms * this->samplerate * 0.001);
}
void SimpleDelay::setFeedback(float fdbck) {
    this->fdbck = fdbck;
}

int SimpleDelay::getDelayLength() const{
    return (this->delay_smpl * 1000)/this->samplerate;
}
float SimpleDelay::getFeedback() const{
    return this->fdbck;
}

void SimpleDelay::tick() {
    writehead++;
    writehead = writehead % (2*maxFs);
    readhead = (2*maxFs) + writehead - delay_smpl;
    readhead = readhead % (2*maxFs);
}

void SimpleDelay::setSamplerate(int samplerate) {
    if (samplerate <= maxFs && samplerate >= 8000){
        this->samplerate = samplerate;
        this->setDelayLength(400);
    } else{
        std::cout << this->samplerate << " is not the the valid range. Choose a samplerate between 8000 and " << this->maxFs << "." << std::endl;
    }
}
