#include "ofxLeapGestures.h"

void ofxLeapGestures::setup(bool classifyMode) {
    
    leapWrapperThread.init();
    worker = new GRTBot();
    recording = false;
    
}

void ofxLeapGestures::setMode(LeapWrapperThread::LGMode mode) {
    
    leapWrapperThread.mode = mode;
    
}

void ofxLeapGestures::setClassID(int id) {
    
    leapWrapperThread.currentClassID = id;
    
}

void ofxLeapGestures::trainAndClassify() {
    
    worker->trainAndClassify();
    leapWrapperThread.stopThread();
    
}

void ofxLeapGestures::startRecording() {
    
    recording = true;
    
    leapWrapperThread.startThread();
    
}

void ofxLeapGestures::stopRecording() {
    
    recording = false;
    
    leapWrapperThread.stopInput();
    leapWrapperThread.stopThread();
    
}

bool ofxLeapGestures::isRecording() {
    
    return recording;
    
}

void ofxLeapGestures::cleanup() {
    
    leapWrapperThread.stopThread();
    
}