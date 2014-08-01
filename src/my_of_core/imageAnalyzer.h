// imageAnalayze.h 
#ifndef IMAGE_ANALYZER_H
#define IMAGE_ANALYZER_H

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvAlphaColorImage.h"

class ImageAnalyzer {
    public:
        void setup();
        void setNearThreshold(int);
        void setFarThreshold(int);

        void update(const unsigned char* colorInput, const unsigned char* depthInput);

        ofxCvAlphaColorImage& getForeground();
        vector<ofxCvBlob>& getBlobs();
        int getNBlobs();
    
        ofxCvImage* grayImagePtr;
    
        ofxCvGrayscaleImage grayImage; // the near thresholded image
        ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
        ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
        ofxCvGrayscaleImage grayDiff; // the far thresholded image
        ofxCvGrayscaleImage invertedGrayImageForMask;
        ofxCvContourFinder contourFinder;
    
        ofxCvColorImage m_colorInput;
        ofxCvColorImage m_depthInput;
    
    
        ofxCvAlphaColorImage m_alphaColorInput;
        ofxCvAlphaColorImage m_alphaForegroundImage;

        ofPoint getCentroid();
        ofRectangle* getBoundingRectPtr();
    private:
        //setup
        void allocateMemoryForWorkingSpaceImages();
    
        //update
        void updateOpenCvImages(const unsigned char* colorInput, const unsigned char* depthInput);
    
        void performImageSegmentation();
        void performThresholding();
    
        void applyImageMorphologyOperations();
        void imageMorphologyClose();
        void imageMorphologyOpen();
        void imageMorphologyDilate();
        void imageMorphologyErode();
    
    
        //ChromaKey chroma_key;
        int near_threshold;
        int far_threshold;
    
        int m_width;
        int m_height;

        bool bUsingSegmentation;
};

#endif
