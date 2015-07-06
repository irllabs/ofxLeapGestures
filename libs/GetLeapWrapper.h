//
//  GetLeapInput.h
//  BeckonBot
//
//  Created by Shawn Xu on 4/3/15.
//  Copyright (c) 2015 Shawn Xu. All rights reserved.
//

#ifndef __BeckonBot__GetLeapInput__
#define __BeckonBot__GetLeapInput__


#include "GRTLeapInput.h"

class GetLeapWrapper {
    
public:
    int getInput();
    int stopInput();
    void setCurrentClassID(int classID);
    void setRealtimeMode(bool realtime);
    void connectStatusLabelCallback(void (^ myBlock) (string));
    GetLeapWrapper(bool realTime);
    
    string getStatusString();
    bool stopped;

private:
    BeckonListener listener;
    Controller controller;
};


#endif /* defined(__BeckonBot__GetLeapInput__) */