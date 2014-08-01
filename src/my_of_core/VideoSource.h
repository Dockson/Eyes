#ifndef VIDEO_SOURCE_H
#define VIDEO_SOURCE_H

class VideoSource {
public:
    VideoSource() { }
    // Ensures to invoke actual object destructor
    virtual ~VideoSource() { }

    virtual void setup() = 0;
    virtual bool isFrameNew() = 0;
    virtual void update() = 0;
    virtual unsigned char* getFramePixels() = 0;
    virtual unsigned char* getDepthPixels() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    
};

#endif
