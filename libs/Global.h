#ifndef __BeckonBot__Global__
#define __BeckonBot__Global__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <iomanip>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include "BeckonPrimitive.h"
#include "Leap.h"
#include "GRT.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define ADDRESS "127.0.0.1"
#define PORT 12345

#define OUTPUT_BUFFER_SIZE 1024

using namespace Leap;
using namespace GRT;
using namespace std;

// MODIFY THIS LINE FOR YOUR BASE DIR
const std::string baseDir = "/Users/bogo/Documents/leap_gesture/";

// Other global variable
const int trainingSampleSize = 10;
const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};
const float minHandRecordingVelocity = 120.0;
const float minFingerRecordingVelocity = 100.0;
const int leastNumberOfFrames = 80;
const int quoThreshold = 40;

#endif