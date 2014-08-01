#include "ofApp.h"
#include "XmlHelper.h"

void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    //ofSetLogLevel(OF_LOG_NOTICE);
    
    ofSetWindowPosition(0, 0);
    ofSetWindowTitle("MAIN WINDOW");
    
    string xml_path = "settings.xml";
    if (XmlHelper::getSingleton().XML.loadFile(xml_path)) {
        ofLogVerbose() << xml_path + " loaded";
    } else {
        ofLogWarning() << "unable to load " + xml_path;
    }

    ofEnableAlphaBlending();
    ofSetVerticalSync(false);

    ofSetFrameRate(  XmlHelper::getSingleton().XML.getAttribute("settings:constants", "framerate", 15));
}

void ofApp::update() {
}

void ofApp::draw() {
}

void ofApp::mousePressed(int x, int y, int button) {
}

