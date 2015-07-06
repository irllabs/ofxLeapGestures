//
//  GRTLeapInput.h
//  BeckonBot
//
//  Created by Shawn Xu on 4/3/15.
//  Copyright (c) 2015 Shawn Xu. All rights reserved.
//

#ifndef __BeckonBot__GRTLeapInput__
#define __BeckonBot__GRTLeapInput__

#include "Global.h"
#include "ofMain.h"

typedef void(^callBackFunctionPtrString)(string);

class BeckonListener : public Listener {
public:
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onFrame(const Controller&);

    void setClassID(int classID);
    void setRealtimeMode(bool realtime);
    void setStatusLabelCallback(void (^ callback) (string));
    void setCurrentDisplayValue(int value);
    bool isAboveThreshold(Hand hand);
    LeapMotionFeature* loadFeature(LeapMotionFeature initialFeature, Hand hand);
    void processFeature(vector<LeapMotionFeature*> features, bool realtime);
    
    BeckonListener(bool realTime);
    BeckonListener();
    
    string statusString;

private:
    int classID;
    callBackFunctionPtrString statusLabelCallback;
    bool realTimeMode = false;
    int quoCounter = 0;
    vector<LeapMotionFeature*> featureCache;
    TimeSeriesClassificationData data;
    bool recordingStarted;
    int64_t initialFrameID; 
    int64_t previousFrameID;
    LeapMotionFeature *initialFeature;
};





#endif /* defined(__BeckonBot__GRTLeapInput__) */
