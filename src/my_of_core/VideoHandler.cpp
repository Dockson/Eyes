#include "VideoHandler.h"

#include "VideoFile.h"
#include "Kinect.h"
#include "XmlHelper.h"

VideoHandler::~VideoHandler() {
    delete m_movieSource;
}

void VideoHandler::setup() {
    // TODO 
	bool usingKinect = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:usingKinect", 0);
	ofLogVerbose() << "VideoHandler::setup setting up video source";
    if(!usingKinect)
        m_movieSource = new VideoFile();
    else
        m_movieSource = new Kinect();

    m_movieSource->setup();
}

bool VideoHandler::isFrameNew() {
    return m_movieSource->isFrameNew();
}


void VideoHandler::update() {
    m_movieSource ->update();
}

unsigned char* VideoHandler::getFramePixels() {
    return m_movieSource ->getFramePixels();
}

unsigned char* VideoHandler::getDepthPixels() {
    return m_movieSource ->getDepthPixels();
}

int VideoHandler::getWidth() {
    return m_movieSource->getWidth();
}

int VideoHandler::getHeight() {
    return m_movieSource->getHeight();
}
