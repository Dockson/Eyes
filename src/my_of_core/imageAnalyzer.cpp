#include "imageAnalyzer.h"
#include "XmlHelper.h"


void ImageAnalyzer::setup() {
    ofLogVerbose() << "imageAnalayzer setting up";
    allocateMemoryForWorkingSpaceImages();


    // TODO get from xml
    bUsingSegmentation = false; // ie we are using blobs
}

void ImageAnalyzer::allocateMemoryForWorkingSpaceImages() {
    ofLogVerbose() << "imageAnalayzer setting up depth";

    near_threshold     = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:near_threshold", 0);
    far_threshold      = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:far_threshold", 0);

    m_width   = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:webcam_width", 640);
    m_height  = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:webcam_height", 480);

    grayImage.allocate(     m_width, m_height);
    grayThreshNear.allocate(m_width, m_height);
    grayThreshFar.allocate( m_width, m_height);
    
    m_alphaForegroundImage.allocate( m_width, m_height );
    m_alphaColorInput.allocate( m_width, m_height );
    invertedGrayImageForMask.allocate( m_width, m_height );
}

void ImageAnalyzer::setNearThreshold(int _near_threshold) {
    near_threshold = _near_threshold;
}

void ImageAnalyzer::setFarThreshold(int _far_threshold) {
    far_threshold = _far_threshold;
}

ofxCvAlphaColorImage& ImageAnalyzer::getForeground() {
    return m_alphaForegroundImage;
}

vector<ofxCvBlob>& ImageAnalyzer::getBlobs() {
    return contourFinder.blobs;
}

int ImageAnalyzer::getNBlobs() {
    return contourFinder.nBlobs;
}

void ImageAnalyzer::update(const unsigned char* colorInput, const unsigned char* depthInput) {
    updateOpenCvImages(colorInput, depthInput);
    performImageSegmentation();
    contourFinder.findContours(
                grayImage, 
                10, 
                (XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:width", 0)*
                 XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:height", 0)
                 )/2,
                20,
                false);
}

void ImageAnalyzer::updateOpenCvImages(const unsigned char* colorInput, const unsigned char* depthInput) {
    // if we use the kinect, we have a real grayscale image format, otherwise it is gray; encoded as color from video frame
    bool use_grayscale_raw = XmlHelper::getSingleton().XML.getValue("SETTINGS:VIDEO:usingKinect", 0);
    if(use_grayscale_raw) {
        grayImage.setFromPixels(depthInput, m_width, m_height);
    }
    else {
        m_depthInput.setFromPixels(depthInput, m_width, m_height);
    }

    m_colorInput.setFromPixels(colorInput, m_width, m_height);



    // m_colorInput.setFromPixels(colorInput, m_width, m_height);
    
    if(!use_grayscale_raw)
        cvCvtColor(m_depthInput.getCvImage(), grayThreshNear.getCvImage(), CV_RGB2GRAY);
    else
        grayThreshNear = grayImage;
}

void ImageAnalyzer::applyImageMorphologyOperations() {
    // we probably want to close, then open
    // https://www.cs.auckland.ac.nz/courses/compsci773s1c/lectures/ImageProcessing-html/topic4.htm
    // best results are usually heuristic , e.g., we might want to do a close x2, then 1x open, etc.
    
    imageMorphologyClose();
    imageMorphologyOpen();
}

void ImageAnalyzer::imageMorphologyClose() {
    // dilate, then erode
    imageMorphologyDilate();
    imageMorphologyErode();

}

void ImageAnalyzer::imageMorphologyOpen() {
    // erode, then dilate
    imageMorphologyErode();
    imageMorphologyDilate();

}

void ImageAnalyzer::imageMorphologyDilate() {
    cvDilate( grayImage.getCvImage(), grayImage.getCvImage() );

}

void ImageAnalyzer::imageMorphologyErode() {
    //cvErode(const CvArr* src, CvArr* dst, IplConvKernel* element=NULL, int iterations=1)
    cvErode( grayImage.getCvImage(), grayImage.getCvImage() );
}

void ImageAnalyzer::performImageSegmentation() {
    //perform thresholding on depth image, to isolate just the foreground in a monochannel
    performThresholding();

    //wipeout our color alpha foreground image
    
    cvSet(m_alphaForegroundImage.getCvImage(), cvScalar(0,0,0,0));
    
    // perform image morphology operations on our mask
    applyImageMorphologyOperations();
    
    // copy over the RGB to RGBA using our mono mask that has been cleaned up with CV morphology ops
    cvCopy(m_alphaColorInput.getCvImage(), m_alphaForegroundImage.getCvImage(), grayImage.getCvImage());
    m_alphaForegroundImage.flagImageChanged();
}

void ImageAnalyzer::performThresholding() {
    grayThreshFar = grayThreshNear;
    grayThreshNear.threshold(near_threshold, true);
    grayThreshFar.threshold(far_threshold);
    cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
    grayImage.flagImageChanged();
    
    cvCvtColor(m_colorInput.getCvImage(), m_alphaColorInput.getCvImage(), CV_BGR2BGRA);
    m_alphaColorInput.flagImageChanged();
}

ofPoint ImageAnalyzer::getCentroid() {
    return contourFinder.blobs[0].centroid;
}

ofRectangle* ImageAnalyzer::getBoundingRectPtr() {
    return &contourFinder.blobs[0].boundingRect;
}
