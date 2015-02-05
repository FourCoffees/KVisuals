//
//  MyFlock.h
//  testingSurfaces
//
//  Created by georgia panagiotidou on 29/01/2015.
//
//

#ifndef __testingSurfaces__MyFlock__
#define __testingSurfaces__MyFlock__

#include <iostream>
#include "MyBoid.h"
#include "ofMain.h"
#include "ofxAnimatableFloat.h"


class MyFlock{
public:
    
    vector<MyBoid*> boids;
    
    bool updatingPosition;
    bool updatingOpacity;
    
    unsigned long long timeStamp;
    
    ofxAnimatableFloat opac;
    
    ofTrueTypeFont letter[4];
  
    MyFlock();
    void hide();
    void show();
    void draw();
    void update();
    void checkEndofAnimation();
    
    void addRepulsionPoint(ofVec2f p);
    void addAttractionPoint(ofVec2f p);
   
    void addHumanPoint( ofVec2f p );
    void resetPosition();
    
};


#endif /* defined(__testingSurfaces__MyFlock__) */
