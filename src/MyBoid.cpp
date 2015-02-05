//
//  MyBoid.cpp
//  KalevalaVisuals
//
//  Created by georgia panagiotidou on 03/02/2015.
//
//

#include "MyBoid.h"
#include "ofApp.h"
#include <cmath>


MyBoid::MyBoid(float xinit, float yinit, float opac, ofTTFCharacter path){
    
    positionCurrent.x = xinit;
    positionCurrent.y = yinit;
    
    positionInitial.x = xinit;
    positionInitial.y = yinit;
    
    xAnimated.reset(xinit);
    yAnimated.reset(yinit);
    
    opacity = opac;
    
    charPath = path;

}


void MyBoid::draw(){
   
    float maxDistance;

    ofSetColor(255, 255, 255, opacity);
    
    //This shoudlnt be here...
    ofVec2f min, max;
    min.set(0,0);
    max.set(2*WIDTH, 2*HEIGHT);
    maxDistance= min.distance(max);
    ///

    
    
    if(xAnimated.isOrWillBeAnimating() || yAnimated.isOrWillBeAnimating()){
        
        positionCurrent.set(xAnimated.val(), yAnimated.val());
    }
    
    
    //Draw only the ones in the view
    if( opacity > 0 && positionCurrent.x <  WIDTH && positionCurrent.x>0 && positionCurrent.y<HEIGHT && positionCurrent.y>0){
        
        ofPushMatrix();
        ofTranslate(positionCurrent.x, positionCurrent.y);
        
      
        charPath.draw();
    
        /*     
            vector <ofPolyline> polylines = charPath.getOutline();

            // for every polyline, draw every fifth point
            
            for (int j = 0; j < polylines.size(); j++){
                for (int k = 0; k < polylines[j].size(); k+=1){         // draw every "fifth" point
                    ofCircle( polylines[j][k], 1);
                }
            }
       
       */
        ofPopMatrix();

       
    //  ofNoFill();
    //  ofCircle(positionCurrent.x, positionCurrent.y, 2);
        
        
/*
        ofVec2f tmp = positionCurrent.getInterpolated(ofVec2f(WIDTH/2, HEIGHT/2),0.1);
        float dist = positionCurrent.distance(ofVec2f(WIDTH/2, HEIGHT/2));
        float distMap = ofMap(dist, 0, maxDistance,1,0.5);
        tmp.interpolate(positionCurrent, distMap);
        
        ofSetLineWidth(4);
        ofLine(positionCurrent.x, positionCurrent.y, tmp.x, tmp.y);
  */
  }
    
    //!TO DO!
    //Check if the values are in the showing plane else dont draw them
    // for faster fps
    
}

void MyBoid::update(){
    
    dt = 1.0f / 60.0f;
    
    xAnimated.update(dt);
    yAnimated.update(dt);
    
    
}

void MyBoid::returnToInit(){
    
    xAnimated.animateToAfterDelay( positionInitial.x, 0.1);
    yAnimated.animateToAfterDelay( positionInitial.y, 0.1);
    
    xAnimated.setDuration(0.2);
    yAnimated.setDuration(0.2);

}



void MyBoid::updateOpacity(float opac){
    
    opacity = opac;
}

void MyBoid::addAttractionForcePoint(ofVec2f p){

}


void MyBoid::addRepulsionForcePoint(ofVec2f p){
 
}

void MyBoid::moveTo(ofVec2f p){
    
    xAnimated.animateTo(p.x);
    yAnimated.animateTo(p.y);
    
    xAnimated.setCurve(SWIFT_GOOGLE);
    yAnimated.setCurve(SWIFT_GOOGLE);

    
    xAnimated.setDuration(0.1);
    yAnimated.setDuration(0.1);
    
}
