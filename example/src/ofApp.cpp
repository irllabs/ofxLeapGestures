#include "ofApp.h"

void ofApp::setup(){
    
    leapWrapperThread.init();
    worker = new GRTBot();
    recording = false;
    
    leapWrapperThread.classify = true;
    
}

void ofApp::update(){
    
    
    
}

void ofApp::draw(){

    ofSetColor(0,0,0);
    ofDrawBitmapString(leapWrapperThread.leapWrapper->getStatusString(), 100, 100);
    
    if(leapWrapperThread.classify) {
        ofDrawBitmapString("classify mode", 100, 120);
    } else {
        ofDrawBitmapString("create class mode", 100, 120);
    }
    ofDrawBitmapString("'t' to train and classify", 100, 160);
    ofDrawBitmapString("'r' to start/stop recording", 100, 180);
    
}

void ofApp::keyReleased(int key){

    if(key == 't') {
        worker->trainAndClassify();
        leapWrapperThread.stopThread();
    }
    
    if(key == 'r') {
        if (recording) {
            leapWrapperThread.stopInput();
            leapWrapperThread.stopThread();
            recording = false;
            //[statusLabel setStringValue:(@"PAUSED")];
        }
        else {
            //[statusLabel setStringValue:(@"RECORDING")];
            recording = true;
            leapWrapperThread.startThread();
        }
    }
    
}

void ofApp::exit() {
    
    leapWrapperThread.stopThread();
    
}
