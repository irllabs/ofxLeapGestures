#include "ofApp.h"

void ofApp::setup(){
    
    leapGestures.setup(false);
    leapGestures.setMode(LeapWrapperThread::CLASSIFY);
    
}

void ofApp::update(){
    
    
    
}

void ofApp::draw(){

    
    
}

void ofApp::keyReleased(int key){

    if(key == 't') {
        leapGestures.trainAndClassify();
    }
    
    if(key == 'r') {
        if (leapGestures.isRecording()) {
            leapGestures.stopRecording();
        }
        else {
            leapGestures.startRecording();
        }
    }
    
}

void ofApp::exit() {
    
    leapGestures.cleanup();
    
}
