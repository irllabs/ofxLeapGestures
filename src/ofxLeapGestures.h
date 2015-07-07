#ifndef __example__ofxLeapGestures__
#define __example__ofxLeapGestures__

#include <stdio.h>

#include "GRTBot.h"
#include "GetLeapWrapper.h"

class ofxLeapGestures {
    
public:
    
    GRTBot *worker;
    GetLeapWrapper *leapWrapper;
    
    void setup();
    
    void recieveNewLeapData(vector<Leap::Hand> hands);
    
    void setClassifyMode();
    void setRecordSamplesMode();
    void setClassID(int id);
    
    void trainAndClassify();
    
};

#endif