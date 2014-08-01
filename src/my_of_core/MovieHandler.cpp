#include "MovieHandler.h"

void MovieHandler::load(string path) {
    movie.loadMovie(path);
	if (!movie.isLoaded())
        ofLogWarning() << "MovieHandler::setup could not load " + path + ".";
}

void MovieHandler::play() {
    movie.firstFrame();
    movie.play();
}

bool MovieHandler::isMovieDoneAndUpdate() {
    movie.update();
    if (movie.getIsMovieDone())
        return true;
    else 
        return false;
}

void MovieHandler::draw(float x, float y, float w, float h) {
    movie.draw(x,y,w,h);
}
