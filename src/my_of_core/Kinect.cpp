#include "Kinect.h"

Kinect::Kinect() {}
Kinect::~Kinect() {}

void Kinect::setup() {
    ofLogVerbose() << "setting up kinect";
    // angle = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:kinect_initial_angle", 0);
    angle = XmlHelper::getSingleton().XML.getAttribute("SETTINGS:VIDEO:kinect","angle", 0);


    kinect.setRegistration(true);
    kinect.init();
    kinect.open();  

    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
    kinect.setCameraTiltAngle(angle);
}

bool Kinect::isFrameNew() {
    return kinect.isFrameNewDepth() && kinect.isFrameNewVideo();

}

void Kinect::update() {
    kinect.update();
}

unsigned char* Kinect::getFramePixels() {
    //return kinect.getDepthPixels();
    return kinect.getPixels();
}

unsigned char* Kinect::getDepthPixels() {
    return kinect.getDepthPixels();
}

int Kinect::getWidth() {
    return kinect.getWidth();
}
int Kinect::getHeight() {
    return kinect.getHeight();
}
