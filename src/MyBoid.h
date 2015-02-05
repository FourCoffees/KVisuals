//
//  MyBoid.h
//  KalevalaVisuals
//
//  Created by georgia panagiotidou on 03/02/2015.
//
//

#ifndef __KalevalaVisuals__MyBoid__
#define __KalevalaVisuals__MyBoid__

#include <iostream>
#include "ofMain.h"
#include "ofxAnimatableFloat.h"


class MyBoid{
    
public:
    ofVec2f positionCurrent;
    ofVec2f positionInitial;

    ofxAnimatableFloat xAnimated;
    ofxAnimatableFloat yAnimated;
    
    float opacity;
    
    ofTTFCharacter charPath;
  
    MyBoid(float x, float y, float opac, ofTTFCharacter path);
    
    //app timebase, to send to all animatable objects
	float dt;
    
    void draw();
    void update();
    void updateOpacity(float opac);
    void moveTo(ofVec2f p);
    void returnToInit();

    void addAttractionForcePoint(ofVec2f p);
    void addRepulsionForcePoint(ofVec2f p);
};



#endif /* defined(__KalevalaVisuals__MyBoid__) */
