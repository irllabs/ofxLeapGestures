#include "ofxLeapGestures.h"

void ofxLeapGestures::setup() {
    
    leapWrapper = new GetLeapWrapper(false);
    leapWrapper->setRealtimeMode(true);
    leapWrapper->setCurrentClassID(0);
    leapWrapper->stopped = false;
    
    worker = new GRTBot();
    
}

void ofxLeapGestures::recieveNewLeapData(vector<Leap::Hand> hands) {
    
    leapWrapper->listener.recieveNewLeapData(hands);
    
}

void ofxLeapGestures::setClassifyMode() {
    
    leapWrapper->setRealtimeMode(true);
    
}

void ofxLeapGestures::setRecordSamplesMode() {
    
    leapWrapper->setRealtimeMode(false);
    
}

void ofxLeapGestures::setClassID(int id) {
    
    leapWrapper->setCurrentClassID(id);
    
}

void ofxLeapGestures::trainAndClassify() {
    
    worker->trainAndClassify();
    
}