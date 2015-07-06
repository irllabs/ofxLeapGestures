#pragma once

#include "ofMain.h"
#include "ofxLeapGestures.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
        void exit();
		
};
