#include "VideoBank.h"


void VideoBank::setup ( float _x , float _y , float videoDelay , bool _bLoop ) {
    // I believe that x and y don't do anything
    x = _x ; 
    y = _y ; 
    bLoop = _bLoop ; 
    videoDelayTimer.setup( videoDelay ) ;
    ofAddListener( videoDelayTimer.TIMER_COMPLETE , this , &VideoBank::videoDelayTimerComplete ) ; 
}

void VideoBank::videoDelayTimerComplete( int &args ) {
    if ( bLoop == true ) 
        playRandomVideo( ) ; 
}
 
void VideoBank::loadFolder( string folderPath , float _volume ) {
    x = 0 ; 
    y = 0 ; 
    volume = _volume ; 

    ofDirectory dir ; 
    dir.allowExt( "mov" ) ; 
    dir.allowExt( "mp4" ) ; 

    dir = ofDirectory( folderPath ) ; 
    dir.listDir( ) ; 

    if ( dir.size() < 1 ) {
        ofLogError( "VideoBank::loadFolder" ) << folderPath << " could not be loaded ! " << endl ; 
    }
    else {
        for (unsigned int i = 0 ; i < dir.size() ; i++ ) {
            addVideo( dir.getPath( i ) , volume ) ; 
        }
    }
}

void VideoBank::addVideo( string videoPath , float _volume ) {
    int index = videos.size() ; 
    videos.push_back ( new ofVideoPlayer() ) ; 
    bool bLoaded = videos[ index ]->loadMovie( videoPath ) ; 
    ofLogVerbose() <<  "VideoBank::addVideo " + videoPath + " RESULT : " + ofToString(bLoaded);
    videos[ index ]->setVolume( _volume ) ; 
    videos[ index ]->setLoopState( OF_LOOP_NORMAL ) ; 
}

void VideoBank::updateAllVideos() {
    for (unsigned int i=0; i<videos.size(); i++) {
        videos[ i ]->update();
        if (videos[ i ]->getIsMovieDone() == true) {
        }
    }
}

void VideoBank::playAllVideos() {
    ofLogVerbose() << "VideoBank::playAllVideos playing all videos";
    for (unsigned int i=0; i<videos.size(); i++) {
        // videos[ i ]->firstFrame() ;  // don't need if stop is used
        videos[ i ]->play() ;
    }

}

void VideoBank::drawVideoAtIndex( int idx, int _x, int _y ) {
    //ofPushMatrix() ; 
    //ofTranslate( _x , _y , 0 ) ; 
    videos[ idx ]->draw( 0 ,0 ) ; 
    //ofPopMatrix() ; 
}

void VideoBank::stopAllVideos() {
    ofLogVerbose() << "VideoBank::stopAllVideos stopping all videos";
    for (unsigned int i=0; i<videos.size(); i++) {
        videos[ i ]->stop(); 
    }
}

// below are the old parts. I'm updating it. 
void VideoBank::playVideoAt( int index )  {
    currentVideo = index ; 
    lastRandomIndex = index ;
    //videos[ currentVideo ]->setVolume( volume ) ; 
    videos[ currentVideo ]->firstFrame() ; 
    videos[ currentVideo ]->play() ;
}

void VideoBank::update( ) 
{
    if ( currentVideo >= 0 ) 
    {
        videos[ currentVideo ]->update( ) ;
        
        if ( videos[ currentVideo ]->getIsMovieDone() == true && videoDelayTimer.bIsRunning == false )
        {
            videos[ currentVideo ]->firstFrame() ; 
            videos[ currentVideo ]->update() ; 
            videos[ currentVideo ]->stop() ; 
            
            //cout << " STARTING TIMER @"  << ofGetElapsedTimeMillis() << " when delay is " << videoDelayTimer.delayMillis <<  endl ; 
            videoDelayTimer.start( false , true ) ; 
        }
    }
    videoDelayTimer.update( ) ;
}

void VideoBank::draw( ) {
    ofPushMatrix( ) ; 
    //  ofTranslate( x , y , 0 ) ; 
        if ( currentVideo >= 0 ) 
        {
            //cout << "drawing ! !" << currentVideo << endl ;
            videos[ currentVideo ]->draw( 0 ,0 ) ; 
        }
    ofPopMatrix( ) ; 
}

void VideoBank::playRandomVideo( ) 
{
    if ( videos.size() == 0 ) 
    {
        ofLogError( "VideoBank::playRandomVideo()" ) << " is empty ! Not loading any sounds" << endl ; 
        return ; 
    }

    if ( currentVideo > 0 ) 
    {
        if ( videos[ currentVideo ]->isPlaying() == true ) 
        {
            ofLogError( " CURRENT VIDEO IS PLAYING. ABORT" ) ; 
            return ;
        }
    }

    //We wouldn't want to play the same random sound 2x in a row
    int randomIndex = lastRandomIndex ;
    if ( videos.size() > 1 ) 
    {
            while ( randomIndex == lastRandomIndex )
            {
                randomIndex = ofWrap( (int)floor( ofRandom( 0 , videos.size() ) ) , 0 , videos.size() ) ;
            }
    }

    currentVideo = randomIndex ; 
    lastRandomIndex = randomIndex ;
    ofLogVerbose( "VideoBank::playRandomVideo" )  << " random index was : " << randomIndex << " of : " << (videos.size()-1) << endl ;
    //videos[ currentVideo ]->setVolume( volume ) ; 
    //videos[ currentVideo ]->firstFrame() ;  
    videos[ currentVideo ]->play() ;
}




void VideoBank::stop ( )  {
    for ( unsigned int i = 0 ; i < videos.size() ; i++ ) 
    {
        videos[ i ]->stop( ); 
    }

    currentVideo = -1 ; 
    videoDelayTimer.stop() ; 
}
    
void VideoBank::reset( )
{
    for ( unsigned int i = 0 ; i < videos.size() ; i++ ) {
        // This seems like overkill but it will prevent the white texture showing up at the beginning 
        //  and is overall better for seamlessness
        videos[ i ]->stop( ); 
        videos[ i ]->firstFrame() ; 
        /*setFrame( 0 ) ; 
        videos[ i ]->play( ) ; 
        videos[ i ]->update( ) ; 
        videos[ i ]->stop( ) ; */
    }

    videoDelayTimer.stop() ; 
    currentVideo = -1 ;
}
