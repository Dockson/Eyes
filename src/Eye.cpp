#include "Eye.h"

void Eye::setup(string eye_path, string pupil_path, float _maj_r, float _min_r, int _x, int _y) {
    eye_img.loadImage(eye_path);
    pupil_img.loadImage(pupil_path);

    maj_r = _maj_r;
    min_r = _min_r;

    eye_pos.set(_x, _y);
    pupil_pos.set(0,0);
}

void Eye::update(ofPoint& point_to_track) {
    // TODO make this algo/calculation
    if (point_to_track.x < eye_pos.x) {
        eye_pos.x = (-0.33 * maj_r );
    } else {
        eye_pos.x = (0.33 * maj_r );
    }
    eye_pos.y = 0;
}

void Eye::draw() {
    ofPushMatrix();
        ofTranslate(eye_pos);
        eye_img.draw(0,0);
        ofPushMatrix();
            ofTranslate(maj_r, min_r); // now the middle of the eye is (0,0) 
            pupil_img.draw(pupil_pos);
        ofPopMatrix();
    ofPopMatrix();


}

