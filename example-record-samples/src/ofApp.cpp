#include "ofApp.h"

void ofApp::setup(){
    
    leapGestures.setup(false);
    leapGestures.setMode(LeapWrapperThread::RECORD_SAMPLES);
    leapGestures.setClassID(1);
    
    leapGestures.startRecording();
    
}

void ofApp::update(){
    
    
    
}

void ofApp::draw(){

    
    
}

void ofApp::keyReleased(int key){

    if(key == 't') {
        
        leapGestures.trainAndClassify();

    } else if(key == 'r') {
        
        if (leapGestures.isRecording()) {
            leapGestures.stopRecording();
            ofLog() << "Stopped recording";
        }
        else {
            leapGestures.startRecording();
            ofLog() << "Started recording";
        }
        
    } else {
        
        if(key >= 48 && key <= 57) {
            int newID = key - 48;
            ofLog() << "Set current class ID to " << newID << ".";
            leapGestures.setClassID(newID);
        }
        
    }
    
}

void ofApp::exit() {
    
    leapGestures.cleanup();
    
}
