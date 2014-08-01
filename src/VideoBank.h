#pragma once

#include "ofMain.h"
#include "ofxSimpleTimer.h"

// This class comes from ofxHelios. Originally, it was made to be a database of videos which played only one video at a time. I have altered it to also play all of its videos at once. 
//
// TODO add a delete to ofVideoPlayer pts in videos

class VideoBank {
public : 
    VideoBank( ) {lastRandomIndex=-1;currentVideo=-1;}
    ~VideoBank ( ) { } 

    void setup ( float x , float y , float timerDelay , bool bLoop ) ; 
    void loadFolder( string folderPath , float _volume = 1.0f ) ; 
    void addVideo( string videoPath , float _volume = 1.0f ) ;

    void updateAllVideos();
    void playAllVideos();
    void drawVideoAtIndex(int, int, int);
    void stopAllVideos();



    vector<ofVideoPlayer*> videos ; 




    // OLD PARTS
    void playVideoAt( int index ) ; 
    void update( ) ; 
    void draw( ) ; 
    void playRandomVideo( ) ; 
    void stop ( ) ; 
    void reset( ) ; 
    bool bLoop ; 
    float volume ; 
    float x , y ; 
    void videoDelayTimerComplete( int & args ) ; 
    ofxSimpleTimer videoDelayTimer ; 
    int currentVideo ; 
    int lastRandomIndex ; 
};
