/*
#include "Configure.h"
#include "XmlHelper.h"
#include "imageAnalyzer.h"

void Configure::setup(VideoHandler* _video, ImageAnalyzer* _imageAnalyzer) {
    ofLogVerbose() << "Entering configuration";

    video = _video;
    imageAnalyzer = _imageAnalyzer;

    xml_path = XmlHelper::getSingleton().XML.getValue("SETTINGS:CONSTANTS:xml_path","");
    near_threshold = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:near_threshold",0);
    far_threshold = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:far_threshold",0);

    isSaved = true;
}

void Configure::update() {
    // does nothing
    imageAnalyzer->update( video->getFramePixels(), video->getDepthPixels() );
}

void Configure::draw() {

    // kinect depth pixels use OF_IMAGE_GRAYSCALE
    // test video pixels use OF_IMAGE_COLOR
    frame_image.setFromPixels( video->getFramePixels(), video->getWidth(), video->getHeight(), OF_IMAGE_COLOR );
    frame_image.draw(10  ,10  ,320,240);
    imageAnalyzer->getForeground().draw(340,10, 320, 240);

    // instructions
    stringstream reportStream;
    reportStream << "To configure: " << endl
        << "1. Have a person stand at the closest distance you want and for their body to still show up on the screen. " << endl
        << "   This means that if they are any closer to the kinect, their camera will not detect their body. " << endl
        << "   You can refer to the left screen to see what objects will show up. If the body appears on the screen, " << endl
        << "   then objects at the same distance from the camera as the body will also show up"  << endl
        << "2. Alter the threshold so that the body shows up, but if the person takes a step forward, they do not." << endl
        << "   You can increase the threshold by pressing the '+' key and decrease the threshold by pressing the '-' key." << endl
        << "   In our tests, a value of around 90-100 worked best, but the value can vary depending on the lighting" << endl
        << "3. Once you have the threshold set, press the 's' key to save." << endl
        << "4. If you don't like that threshold, keep messing with it until it looks right - you can save as many times as you want" << endl
        << "5. Once you are finished, press the 'q' key to quit the configuration. Any changes that are not saved will be forgotten." << endl 
        << endl << endl
        << "Change threshold (- +)" << endl
        << "Press 's' to save" <<  endl
        << "Press 'q' to quit" << endl;

    ofDrawBitmapString(reportStream.str(), 20, 360);
}

void Configure::save() {
    ofLogNotice() << "Saving configure settings";

    near_threshold  = XmlHelper::getSingleton().XML.setValue("SETTINGS:VIDEO:near_threshold",near_threshold);
    far_threshold   = XmlHelper::getSingleton().XML.setValue("SETTINGS:VIDEO:far_threshold",far_threshold);

    XmlHelper::getSingleton().XML.saveFile( xml_path );

    isSaved = true;
}

void Configure::quit() {
    if ( !isSaved ) {
        ofLogNotice() << "Quitting configure without saving. Reverting to last saved settings";
        // we need to revert imageAnalyzer to its values in the XML sheet
        imageAnalyzer->setNearThreshold(XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:near_threshold",0));
        imageAnalyzer->setFarThreshold (XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:far_threshold",0));
    }
}

void Configure::increaseNearThreshold() {
    near_threshold++;
    imageAnalyzer->setNearThreshold(near_threshold);
    isSaved = false;
}

void Configure::decreaseNearThreshold() {
    near_threshold--;
    imageAnalyzer->setNearThreshold(near_threshold);
    isSaved = false;
}

void Configure::increaseFarThreshold() {
    far_threshold++;
    imageAnalyzer->setFarThreshold(far_threshold);
    isSaved = false;
}
void Configure::decreaseFarThreshold() {
    far_threshold--;
    imageAnalyzer->setFarThreshold(far_threshold);
    isSaved = false;
}

*/
