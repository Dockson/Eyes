#ifndef VIDEO_HANDLER_H
#define VIDEO_HANDLER_H

#include "VideoSource.h"

#include "XmlHelper.h"

class Kinect;
class VideoFile;

class VideoHandler {
public:
    ~VideoHandler();
    void setup();
    bool isFrameNew();
    void update();   
    unsigned char* getFramePixels();
    unsigned char* getDepthPixels();
    int getWidth();
    int getHeight();
  
private:
    
    VideoSource *m_movieSource;
};


#endif
