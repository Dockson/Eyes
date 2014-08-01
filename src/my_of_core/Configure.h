/*
#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "ofMain.h"
#include "video/VideoHandler.h"

class ImageAnalyzer;

class Configure {
    public:
        void setup(VideoHandler*, ImageAnalyzer*);
        void update();
        void draw();
        void save();
        void quit();

        void increaseNearThreshold();
        void decreaseNearThreshold();

        void increaseFarThreshold();
        void decreaseFarThreshold();

    private:
        VideoHandler* video; // kinect, webcam or test video
        ImageAnalyzer* imageAnalyzer;
        
        string xml_path;
        int near_threshold;
        int far_threshold;

        bool isSaved;
        ofImage frame_image;
};

#endif
*/
