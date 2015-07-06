//
//  GRTbot.cpp
//  Beckon-bot
//
//  Created by Shawn Xu on 4/3/15.
//  Copyright (c) 2015 Shawn Xu. All rights reserved.
//

#include "GRTBot.h"

int GRTBot::trainAndClassify() {
    //Get all the training data, and concat to one file
    vector<string> dataFiles;
   
    DIR* dirFile = opendir( (ofToDataPath("Training/")).c_str() );
    if ( dirFile )
    {
        ofLog() << "ddd";
        
        struct dirent* hFile;
        errno = 0;
        while (( hFile = readdir( dirFile )) != NULL )
        {
            ofLog() << "eee";
            
            if ( !strcmp( hFile->d_name, "."  )) continue;
            if ( !strcmp( hFile->d_name, ".." )) continue;
            
            // dirFile.name is the name of the file. Do whatever string comparison
            // you want here. Something like:
            if ( strstr( hFile->d_name, ".txt" )) {
                printf( "found a .txt file: %s", hFile->d_name );
                dataFiles.push_back(ofToDataPath("Training/") + hFile->d_name);
            }
        } 
        closedir( dirFile );
    }
    
    // Get dimension
    TimeSeriesClassificationData tempData;
    tempData.load(dataFiles[0]);
    
    //Load the training data
    TimeSeriesClassificationData trainingData;
    trainingData.setNumDimensions(tempData.getNumDimensions());
    
    for(std::vector<string>::size_type i = 0; i != dataFiles.size(); i++) {
        TimeSeriesClassificationData dataPart;
        dataPart.load(dataFiles[i]);
        for (int n = 0; n < dataPart.getNumSamples(); n++) {
            for (int k = 0; k < trainingSampleSize; k++) {
                trainingData.addSample(dataPart[n].getClassLabel(), dataPart[n].getData());
            }
        }
    }
    
    //Remove 20% of the training data to use as test data
    TimeSeriesClassificationData testData = trainingData.partition( 80 );
    
    //Create a new HMM instance
    HMM hmm;
    
    //Set the HMM as a Continuous HMM
    hmm.setHMMType( HMM_CONTINUOUS );
    
    //Set the downsample factor, a higher downsample factor will speed up the prediction time, but might reduce the classification accuracy
    hmm.setDownsampleFactor( 5 );
    
    //Set the committee size, this sets the (top) number of models that will be used to make a prediction
    hmm.setCommitteeSize( 10 );
    
    hmm.enableScaling( true );
    
    //Tell the hmm algorithm that we want it to estimate sigma from the training data
    hmm.setAutoEstimateSigma( true );
    
    //Set the minimum value for sigma, you might need to adjust this based on the range of your data
    //If you set setAutoEstimateSigma to false, then all sigma values will use the value below
    hmm.setSigma( 0.5 );
    
    //Set the HMM model type to LEFTRIGHT with a delta of 1, this means the HMM can only move from the left-most state to the right-most state
    //in steps of 1
    hmm.setModelType( HMM_LEFTRIGHT );
    hmm.setDelta( 1 );
    
    //Train the HMM model
    if( !hmm.train( trainingData ) ){
        cout << "ERROR: Failed to train the HMM model!\n";
        return false;
    }
    
    //Save the HMM model to a file
    if( !hmm.save( ofToDataPath("Model/HMMModel.grt") ) ){
        cout << "ERROR: Failed to save the model to a file!\n";
        return false;
    }
    
    //Load the HMM model from a file
    if( !hmm.load( ofToDataPath("Model/HMMModel.grt") ) ){
        cout << "ERROR: Failed to load the model from a file!\n";
        return false;
    }
    
    //Compute the accuracy of the HMM models using the test data
    double numCorrect = 0;
    double numTests = 0;
    for(UINT i=0; i<testData.getNumSamples(); i++){
        
        UINT classLabel = testData[i].getClassLabel();
        hmm.predict( testData[i].getData() );
        
        if( classLabel == hmm.getPredictedClassLabel() ) numCorrect++;
        numTests++;
        
        VectorDouble classLikelihoods = hmm.getClassLikelihoods();
        VectorDouble classDistances = hmm.getClassDistances();
        
        cout << "ClassLabel: " << classLabel;
        cout << " PredictedClassLabel: " << hmm.getPredictedClassLabel();
        cout << " MaxLikelihood: " << hmm.getMaximumLikelihood();
        
        cout << "  ClassLikelihoods: ";
        for(UINT k=0; k<classLikelihoods.size(); k++){
            cout << classLikelihoods[k] << "\t";
        }
        
        cout << "ClassDistances: ";
        for(UINT k=0; k<classDistances.size(); k++){
            cout << classDistances[k] << "\t";
        }
        cout << endl;
    }
    
    cout << "Test Accuracy: " << numCorrect/numTests*100.0 << endl;
    
    return true;
}
