#ifndef KINECT_H
#define KINECT_H


#include "ofxKinect.h"
#include "XmlHelper.h"
#include <iostream>
#include "VideoSource.h"

class Kinect : public VideoSource {
public:
    Kinect();
    ~Kinect();
    
    virtual void setup();
    virtual void update();
    virtual bool isFrameNew();
    virtual unsigned char* getFramePixels();
    virtual unsigned char* getDepthPixels();
    virtual int getWidth();
    virtual int getHeight();
    
private:
    ofxKinect kinect;
    int angle;

};

#endif

