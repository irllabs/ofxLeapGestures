//
//  GetLeapInput.cpp
//  BeckonBot
//
//  Created by Shawn Xu on 4/3/15.
//  Copyright (c) 2015 Shawn Xu. All rights reserved.
//

#include "GetLeapWrapper.h"


//BeckonListener listener;
//Controller controller;

int GetLeapWrapper::getInput() {
    
    controller.addListener(listener);
    
    // Keep this process running until Enter is pressed
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();
    
    return EXIT_SUCCESS;
}

int GetLeapWrapper::stopInput() {
    
    // Remove the sample listener when done
    controller.removeListener(listener);
    
    return EXIT_SUCCESS;
}

void GetLeapWrapper::setCurrentClassID(int classID) {
    listener.setClassID(classID);
}

void GetLeapWrapper::setRealtimeMode(bool realtime) {
    listener.setRealtimeMode(realtime);
}


void GetLeapWrapper::connectStatusLabelCallback(void (^ myBlock) (string)){
    listener.setStatusLabelCallback(myBlock);
}

string GetLeapWrapper::getStatusString() {
    return listener.statusString;
}

// Constructor
GetLeapWrapper::GetLeapWrapper(bool realTime) {
    std::cout << "Constructor called" << std::endl;
    listener = *new BeckonListener(realTime);
    controller = *new Controller();
}