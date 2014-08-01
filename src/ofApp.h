#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
private:
    ofFbo fbo0;
    ofFbo fbo1;
    ofFbo fbo2;
    ofFbo fbo3;
};
