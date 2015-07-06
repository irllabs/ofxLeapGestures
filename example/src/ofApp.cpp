#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    thread.init();
    worker = new GRTBot();
    recording = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofLog() << thread.wrapper->getStatusString();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (recording) {
        thread.stopInput();
        recording = false;
        //[statusLabel setStringValue:(@"PAUSED")];
    }
    else {
        //[statusLabel setStringValue:(@"RECORDING")];
        recordLeap();
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit() {
    
    thread.stopThread();
    
}

void ofApp::recordLeap() {
    recording = true;
    
    // The callbacks used to update the interface (Obj-C)
    /*void ( ^ statusLabelCallback) (string);
    
    statusLabelCallback = ^(string s) {
        [statusLabel setStringValue: [NSString stringWithCString:s.c_str()encoding:[NSString defaultCStringEncoding]]];
    };*/
    
    // Since leap listener runs in the background, we have a separate thread to deal with it
    // Otherwise the main GUI will get stuck
    //leapQueue = dispatch_queue_create("com.leapQueue", NULL);
    
    // The current gesture ID
    //int currentID = [_classLabel intValue];
    
    /*dispatch_async(leapQueue, ^{
        wrapper->setRealtimeMode(realtimeToggle.state);
        wrapper->connectStatusLabelCallback(statusLabelCallback);
        wrapper->setCurrentClassID(currentID);
        
        wrapper->getInput();
    });*/
    
    thread.startThread();
    
}
