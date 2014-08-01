#ifndef VIDEO_FILE_H
#define VIDEO_FILE_H


#include <iostream>
#include "ofMain.h"
#include "VideoSource.h"
#include "XmlHelper.h"

// depth is grayscale
// frame is color
class VideoFile : public VideoSource {
public:
    
    VideoFile();
    ~VideoFile();
    
    void setup();
    virtual bool isFrameNew();
    void update();
    unsigned char* getDepthPixels();
    unsigned char* getFramePixels();
    int getWidth();
    int getHeight();
    string convertIndex();

private:
    //ofImage frame_image;
    //ofImage depth_image;
    //string path;
    //string color_frame_names;
    //string depth_frame_names;
    //int num_images;
    //int index;

    ofVideoPlayer color_video;
    ofVideoPlayer depth_video;

};

#endif
