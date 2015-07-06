#ifndef __example__ofxLeapGestures__
#define __example__ofxLeapGestures__

#include <stdio.h>

#include "GRTBot.h"
#include "GetLeapWrapper.h"

class LeapWrapperThread : public ofThread {
    
public:
    
    GetLeapWrapper *leapWrapper;
    
    enum LGMode {
        CLASSIFY,
        RECORD_SAMPLES
    };
    LGMode mode;
    int currentClassID;
    
    void init() {
        leapWrapper = new GetLeapWrapper(false);
    }
    
    void stopInput() {
        leapWrapper->stopInput();
        leapWrapper->stopped = true;
    }
    
    void threadedFunction() {
        
        while(isThreadRunning()) {
            
            if(mode == CLASSIFY) {
                leapWrapper->setRealtimeMode(true);
            }
            if(mode == RECORD_SAMPLES) {
                leapWrapper->setCurrentClassID(false);
            }
            
            leapWrapper->stopped = false;
            leapWrapper->getInput();
            
        }
        
    }
    
};

class ofxLeapGestures {
    
private:
    
    GRTBot *worker;
    LeapWrapperThread leapWrapperThread;
    
    bool recording;
    
public:
    
    void setup(bool classifyMode);
    
    void setMode(LeapWrapperThread::LGMode mode);
    void setClassID(int id);
    
    void startRecording();
    void stopRecording();
    
    void trainAndClassify();
    
    void cleanup();
    
    bool isRecording();
    
};

#endif