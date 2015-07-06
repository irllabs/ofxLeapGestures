//
//  BeckonPrimitive.cpp
//  BeckonBot
//
//  Created by Shawn Xu on 10/6/15.
//  Copyright (c) 2015 Shawn Xu. All rights reserved.
//

#include "BeckonPrimitive.h"

LeapMotionFeature::LeapMotionFeature(int fn): finger_number(fn), finger_tips(NULL), finger_directions(NULL), finger_tip_velocities(NULL){
    if(finger_number){
        finger_tips = new Point3D[finger_number];
        finger_directions = new Point3D[finger_number];
        finger_tip_velocities = new Point3D[finger_number];
    }
}

void LeapMotionFeature::set_palm_direction(double x, double y, double z){
    palm_direction.x = x;
    palm_direction.y = y;
    palm_direction.z = z;
}

void LeapMotionFeature::set_palm_position(double x, double y, double z){
    palm_position.x = x;
    palm_position.y = y;
    palm_position.z = z;
}

void LeapMotionFeature::set_palm_velocity(double x, double y, double z){
    palm_velocity.x = x;
    palm_velocity.y = y;
    palm_velocity.z = z;
}

Point3D LeapMotionFeature::get_palm_position() {
    return palm_position;
}

Point3D LeapMotionFeature::get_palm_velocity() {
    return palm_velocity;
}

void LeapMotionFeature::set_palm_ypr(double y, double p, double r){
    palm_yaw = y;
    palm_pitch = p;
    palm_roll = r;
}

void LeapMotionFeature::set_finger_direction(int idx, double x, double y, double z){
    assert(idx < finger_number);
    finger_directions[idx].x = x;
    finger_directions[idx].y = y;
    finger_directions[idx].z = z;
}

void LeapMotionFeature::set_finger_velocities(int idx, double x, double y, double z){
    assert(idx < finger_number);
    finger_tip_velocities[idx].x = x;
    finger_tip_velocities[idx].y = y;
    finger_tip_velocities[idx].z = z;
}

void LeapMotionFeature::set_finger_tip(int idx, double x, double y, double z){
    assert(idx < finger_number);
    finger_tips[idx].x = x;
    finger_tips[idx].y = y;
    finger_tips[idx].z = z;
}

Point3D* LeapMotionFeature::get_finger_tips() {
    return finger_tips;
}

Point3D* LeapMotionFeature::get_finger_velocities() {
    return finger_tip_velocities;
}

int LeapMotionFeature::get_feature_vector_dimension(){
    return 3 * 5 * 2 + 3 + 3 + 3;
}

double* LeapMotionFeature::get_feature_vector(){
    double* feature = new double[get_feature_vector_dimension()](); // Initially zero
    int offset = 0;
    for(int i = 0; i < finger_number; i++){
        feature[i * 3] = finger_tips[i].x;
        feature[i * 3 + 1] = finger_tips[i].y;
        feature[i * 3 + 2] = finger_tips[i].z;
    }
    
    offset = 15;
    for(int i = 0; i < finger_number; i++){
        feature[offset + i * 3] = finger_directions[i].x;
        feature[offset + i * 3 + 1] = finger_directions[i].y;
        feature[offset + i * 3 + 2] = finger_directions[i].z;
    }
    
    offset = 30;
    
    feature[offset] = palm_position.x;
    feature[offset + 1] = palm_position.y;
    feature[offset + 2] = palm_position.z;
    
    feature[offset + 3] = palm_direction.x;
    feature[offset + 4] = palm_direction.y;
    feature[offset + 5] = palm_direction.z;
    
    feature[offset + 6] = palm_yaw;
    feature[offset + 7] = palm_pitch;
    feature[offset + 8] = palm_roll;
    
    return feature;
}

int LeapMotionFeature::get_finger_number(){
    return finger_number;
}
