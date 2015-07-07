#include "ofApp.h"

void ofApp::setup(){
    
    leap.open();
    
    leapGestures.setup();
    leapGestures.setRecordSamplesMode();
    
}

void ofApp::update(){
    
    if(leap.isFrameNew()) {
        leapGestures.recieveNewLeapData(leap.getLeapHands());
    }
    leap.markFrameAsOld();
    
}

void ofApp::draw(){

    
    
}

void ofApp::keyReleased(int key){

    if(key == 't') {
        leapGestures.trainAndClassify();
    }
    
}
