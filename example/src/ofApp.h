#pragma once

#include "ofMain.h"
#include "GRTBot.h"
#include "GetLeapWrapper.h"

class MyThread : public ofThread {
    
public:
    
    GetLeapWrapper *wrapper;
    bool classify;
    
    void init() {
        
        wrapper = new GetLeapWrapper(false);
        classify = false;
        
    }
    
    void stopInput() {
        
        wrapper->stopInput();
        
    }
    
    // the thread function
    void threadedFunction() {
        
        // start
        
        while(isThreadRunning()) {
            
            wrapper->setRealtimeMode(classify);
            wrapper->setCurrentClassID(0);
            
            wrapper->getInput();
            
        }
        
        // done
    }
    
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();
    
        void recordLeap();
    
        GRTBot *worker;
    
        MyThread thread;
    
        int countdownTimer;
        int remainingTicks;
        bool recording;
		
};
