#include "VideoFile.h"
VideoFile::VideoFile() {}

VideoFile::~VideoFile() {}

void VideoFile::setup() {
    ofLogVerbose() << "setting up VideoFile";

    string color_path = XmlHelper::getSingleton().XML.getAttribute("SETTINGS:VIDEO:test_video", "color_path", "");
    string depth_path = XmlHelper::getSingleton().XML.getAttribute("SETTINGS:VIDEO:test_video", "depth_path", "");

    color_video.loadMovie(color_path);
    depth_video.loadMovie(depth_path);

    if (!color_video.isLoaded()) 
        ofLogWarning() << "VideoFile::setup() could not load " + color_path;
    if (!depth_video.isLoaded()) 
        ofLogWarning() << "VideoFile::setup() could not load " + depth_path;

    color_video.setLoopState(OF_LOOP_NORMAL);
    depth_video.setLoopState(OF_LOOP_NORMAL);

    color_video.play();
    depth_video.play();

    ofLogVerbose() << "Color video info: numFrames: " << color_video.getTotalNumFrames();
    ofLogVerbose() << "Depth video info: numFrames: " << depth_video.getTotalNumFrames();
}

bool VideoFile::isFrameNew() {
    return color_video.isFrameNew() && depth_video.isFrameNew();
}

void VideoFile::update() {
    //if (!color_video.isPlaying())
    //    color_video.play();
    //if (!depth_video.isPlaying())
    //    depth_video.play();
    color_video.update();
    depth_video.update();
}

unsigned char* VideoFile::getFramePixels() {
    return color_video.getPixels();
}

unsigned char* VideoFile::getDepthPixels() {
    return depth_video.getPixels();
}

int VideoFile::getWidth() {
    return depth_video.getWidth();
}
int VideoFile::getHeight() {
    return depth_video.getHeight();
}
