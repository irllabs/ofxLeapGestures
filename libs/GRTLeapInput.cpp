//
//  GRTLeapInput.cpp
//  BeckonBot
//
//  Created by Shawn Xu on 4/3/15.
//  Copyright (c) 2015 Shawn Xu. All rights reserved.
//

#include "GRTLeapInput.h"

// Constructor with argument
BeckonListener::BeckonListener(bool realTime) {
    this->realTimeMode = realTime;
    recordingStarted = false;
}

// Default constructor
BeckonListener::BeckonListener() {
    this->realTimeMode = false;
    recordingStarted = false;
}

void BeckonListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
}

void BeckonListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void BeckonListener::onFrame(const Controller& controller) {
    // Get the most recent frame and report some basic information
    // Do that only when hands are present
    const Frame frame = controller.frame();
    HandList hands = frame.hands();
    if (!hands.isEmpty()) {
        
        // We only need the first hand
        const Hand hand = hands[0];
        bool aboveThreshold = isAboveThreshold(hand);
        
        // The hand should be moving beyond a base velocity to be recognized as a gesture
        if (aboveThreshold && !recordingStarted)  {
            
            // If the recording hasnt' started, start and put the current frame as initial frame
            recordingStarted = true;
            
            LeapMotionFeature fakeFeature(0);
            initialFeature = loadFeature(fakeFeature, hand);
            
            initialFrameID = frame.id();
            previousFrameID = initialFrameID;
            
            //this->statusLabelCallback("RECORDING");
            this->statusString = "RECORDING";

        } // end of if
        
        else if (aboveThreshold && recordingStarted && frame.id() == (previousFrameID + 1)) {
            //If all conditions match, record this frame
            
            LeapMotionFeature* newFeature;
            newFeature = loadFeature(*initialFeature, hand);
            featureCache.push_back(newFeature);
            
            //snippet.push_back(frame);
            
            previousFrameID = frame.id();
            
            std::cout << "Added new feature" << std::endl;
        } // end of else if
        
        else if (!isAboveThreshold(hand) && recordingStarted)
        {
            //If hand moves below threshold speed, stop recording and save the snippet so far.
            //If there are more than [leastNumberOfFrame] frame saved in the snippet, this snippet is valid

            std::cout << "Ended recording a sample" << std::endl;
            
            if (featureCache.size() > leastNumberOfFrames) {
                processFeature(featureCache, realTimeMode);
                featureCache.clear();
            };
            
            recordingStarted = false;
        } // end of else if
    }
}

// Determine if the current velocity of palm or any of the five fingers are above threshold
bool BeckonListener::isAboveThreshold(Hand hand) {
    // First check the palm
    if (hand.palmVelocity().magnitude() > minHandRecordingVelocity) {
        quoCounter = 0;
        return true;
    }

    // Then check the five fingers
    for (int f = 0; f < 5; f++) {
        if (hand.fingers()[f].tipVelocity().magnitude() > minFingerRecordingVelocity) {
            quoCounter = 0;
            return true;
        }
    }
    
    // The quoCounter is used to register the temporary "status quo", like the finger stopping briefly when moving up and down. Consider this as a buffer
    // Only when the quoCounter reaches a certain amount will the trigger a false (not above threshold)
    quoCounter++;
    
    if (quoCounter > quoThreshold) {
        return false;
    }
    else {
        return true;
    }
}

LeapMotionFeature* BeckonListener::loadFeature(LeapMotionFeature initialFeature, Hand hand) {
    LeapMotionFeature *lmf;
    lmf = new LeapMotionFeature(hand.fingers().count());
    
    for(int i = 0; i < hand.fingers().count(); i++){
        lmf->set_finger_direction(i, hand.finger(i).direction().x, hand.finger(i).direction().y, hand.finger(i).direction().z);
        lmf->set_finger_velocities(i, hand.finger(i).tipVelocity().x, hand.finger(i).tipVelocity().y, hand.finger(i).tipVelocity().z);
    }
    
    lmf->set_palm_direction(hand.palmNormal().x, hand.palmNormal().y, hand.palmNormal().z);
    lmf->set_palm_velocity(hand.palmVelocity().x, hand.palmVelocity().y, hand.palmVelocity().z);
    lmf->set_palm_ypr(hand.direction().pitch(), hand.direction().yaw(), hand.direction().roll());
    
    // If this is the initial feature, simply record absolute positions
    if (initialFeature.get_finger_number() == 0) {
        for(int i = 0; i < hand.fingers().count(); i++){
            lmf->set_finger_tip(i, hand.finger(i).tipPosition().x, hand.finger(i).tipPosition().y, hand.finger(i).tipPosition().z);
        }
        
        lmf->set_palm_position(hand.palmPosition().x, hand.palmPosition().y, hand.palmPosition().z);
    }
    
    // Else, record delta values (to offset the different start positions)
    else {
        for(int i = 0; i < hand.fingers().count(); i++){
            lmf->set_finger_tip(i, hand.finger(i).tipPosition().x - initialFeature.get_finger_tips()[i].x, hand.finger(i).tipPosition().y - initialFeature.get_finger_tips()[i].y, hand.finger(i).tipPosition().z - initialFeature.get_finger_tips()[i].z);
        }
        
        lmf->set_palm_position(hand.palmPosition().x - initialFeature.get_palm_position().x, hand.palmPosition().y - initialFeature.get_palm_position().y, hand.palmPosition().z - initialFeature.get_palm_position().z);
    }
    
    return lmf;
}


void BeckonListener::processFeature(vector<LeapMotionFeature*> features, bool realtime) {
    // First, extract the sequence from feature cache
    // Then, under mode 1 classification, get the correct label and ros send
    // Under mode 2, record the data to file on disk
    MatrixDouble sequence;
    for(int i = 0; i < features.size(); i++) {
        
        LeapMotionFeature* pFeature = features.at(i);
        VectorDouble sample(pFeature->get_feature_vector_dimension());
        double* featureArray = pFeature->get_feature_vector();
        
        for(int k = 0; k < pFeature->get_feature_vector_dimension(); k++){
            sample[k] = featureArray[k];
        }
        sequence.push_back(sample);
        
        delete[] featureArray;
    }
    
    // For mode 1, apply classification
    if (realtime) {
        HMM hmm;
        if( !hmm.loadModelFromFile(ofToDataPath("Model/HMMModel.grt")) ){
            cout << "Failed to load the classifier model!\n";
        }
        else {
            hmm.predict(sequence);
            int res = hmm.getPredictedClassLabel();
            
            std::cout << "The result is: " << res << std::endl;
            //this->statusLabelCallback("Recognition result: " + ofToString(res));
            
            //Send result via OSC
            UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
            
            char buffer[OUTPUT_BUFFER_SIZE];
            osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
            
            p << osc::BeginBundleImmediate << osc::BeginMessage( "/result" ) << res << osc::EndMessage << osc::EndBundle;
            
            transmitSocket.Send( p.Data(), p.Size() );
        }
    }
    
    // For mode 2, add to current data queue
    else {
        int dataSampleSize = data.getNumSamples();
        
        if (dataSampleSize == 0) {
            // Initialize the data set
            data.setNumDimensions(features.at(0)->get_feature_vector_dimension());
        }
        
        data.addSample(classID, sequence);
        std::cout << dataSampleSize + 1 << " samples in dataset" << std::endl;
        //this->statusLabelCallback(ofToString(dataSampleSize + 1) + " Samples recorded");
        
        // When it reaches the number of files to record, save to file
        if (dataSampleSize >= (trainingSampleSize - 1)) {
            std::cout << "Saved to file!" << endl;
            char fileName[80];
            std::sprintf(fileName, "Training/class_%d.txt", classID);
            data.saveDatasetToFile(ofToDataPath(fileName));
            data.clear();
        }
    }
    
};

void BeckonListener::setClassID(int classID) {
    this->classID = classID;
}

void BeckonListener::setRealtimeMode(bool realtime) {
    this->realTimeMode = realtime;
}

void BeckonListener::setStatusLabelCallback(void (^ callback) (string)) {
    this->statusLabelCallback = callback;
}
