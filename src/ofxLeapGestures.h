#ifndef __example__ofxLeapGestures__
#define __example__ofxLeapGestures__

#include <stdio.h>

#include "GRTBot.h"
#include "GetLeapWrapper.h"

class LeapWrapperThread : public ofThread {
    
public:
    
    GetLeapWrapper *leapWrapper;
    bool classify;
    
    void init() {
        leapWrapper = new GetLeapWrapper(false);
        classify = false;
    }
    
    void stopInput() {
        leapWrapper->stopInput();
        leapWrapper->stopped = true;
    }
    
    void threadedFunction() {
        
        while(isThreadRunning()) {
            
            leapWrapper->setRealtimeMode(classify);
            leapWrapper->setCurrentClassID(0);
            
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
    
    
    
};

#endif