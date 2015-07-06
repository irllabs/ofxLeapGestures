//
//  BeckonPrimitive.h
//  BeckonBot
//
//  Created by Shawn Xu on 10/6/15.
//  Copyright (c) 2015 Shawn Xu. All rights reserved.
//

#ifndef __BeckonBot__BeckonPrimitive__
#define __BeckonBot__BeckonPrimitive__

#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>

class Point3D{
public:
    double x;
    double y;
    double z;
    Point3D(){}
    Point3D(double _x, double _y, double _z): x(_x), y(_y), z(_z){}
};

class LeapMotionFeature{
private:
    int finger_number;
    Point3D* finger_tips;
    Point3D* finger_directions;
    Point3D* finger_tip_velocities;
    Point3D  palm_direction;
    Point3D  palm_position;
    Point3D  palm_velocity;
    double   palm_yaw;
    double   palm_pitch;
    double   palm_roll;
    
public:
    // Constructor
    LeapMotionFeature(int fn);
    
    void set_palm_direction(double x, double y, double z);
    
    void set_palm_position(double x, double y, double z);
    
    void set_palm_velocity(double x, double y, double z);
    
    Point3D get_palm_position();
    
    Point3D get_palm_velocity();
    
    void set_palm_ypr(double y, double p, double r);
    
    void set_finger_tip(int idx, double x, double y, double z);
    
    void set_finger_direction(int idx, double x, double y, double z);
    
    void set_finger_velocities(int idx, double x, double y, double z);
    
    Point3D* get_finger_tips();
    
    Point3D* get_finger_velocities();
    
    int get_feature_vector_dimension();
    
    double* get_feature_vector();
    
    int get_finger_number();
    
};

#endif /* defined(__BeckonBot__BeckonPrimitive__) */
