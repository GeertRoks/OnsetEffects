#ifndef SIMPLEDELAY_H
#define SIMPLEDELAY_H

class SimpleDelay {
public:
    SimpleDelay();
    ~SimpleDelay();

    void process(const float* input, float* output, int frames);

    void setDelayLength(int delay_ms);
    void setFeedback(float fdbck);

    int getDelayLength() const;
    float getFeedback() const;

    void setSamplerate(int samplerate);

private:
    void tick();

    float* delayBuffer;

    int samplerate = 48000;
    const int maxFs = 96000;

    int delay_smpl = int(400/*ms*/ * samplerate * 0.001);
    float fdbck = 0.5f;

    int writehead = 0;
    int readhead = 2*maxFs - delay_smpl;
};

#endif //SIMPLEDELAY_H
