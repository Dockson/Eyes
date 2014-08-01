#ifndef EYE_H
#define EYE_H

#include "ofMain.h"

class Eye {
    public:
        void setup(string eye_path, string pupil_path, float _maj_r, float _min_r, int _x, int _y);
        void update(ofPoint& point_to_track);
        void draw();
    private:
        float maj_r; // major radius  -- width/2
        float min_r; // minor radius  -- height/2
        ofPoint eye_pos;
        ofPoint pupil_pos; // relative to eye_pos -- see draw()
        ofImage eye_img;
        ofImage pupil_img;
};
#endif
