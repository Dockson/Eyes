#ifndef XML_HELPER_H
#define XML_HELPER_H

#include "common/Singleton.h"
#include "ofxXmlSettings.h"

class XmlHelper : public TheProgram::Singleton<XmlHelper> {
public:
    ofxXmlSettings XML;
    friend class TheProgram::Singleton<XmlHelper>;
};
#endif
