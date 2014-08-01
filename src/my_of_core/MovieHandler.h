#ifndef MOVIE_HANDLER_H
#define MOVIE_HANDLER_H
#include "ofMain.h" 
#include "XmlHelper.h"


// TODO 


class MovieHandler {
public:
    // TODO maybe move startMovie and isOver into update
    // and have update return bool
    
    void load(string); 
    void play();
    bool isMovieDoneAndUpdate();
    void draw(float, float, float, float);

private:
    ofVideoPlayer movie;
};
#endif
