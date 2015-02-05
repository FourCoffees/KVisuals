//
//  MyFlock.cpp
//  testingSurfaces
//
//  Created by georgia panagiotidou on 29/01/2015.
//
//

#include "MyFlock.h"
#include "ofApp.h"
#include "MyBoid.h"

MyFlock::MyFlock(){
    
    letter[0].loadFont("Quicksand-Light.otf",11,false, false, true);
    letter[1].loadFont("Quicksand-Regular.otf",12,false, false, true);
    letter[2].loadFont("Quicksand-BoldItalic.otf",11,false, false, true);
    letter[3].loadFont("Quicksand-Italic.otf",11,false, false, true);

    opac.reset(0.0);
    opac.setRepeatType(PLAY_ONCE);
    opac.setCurve(EXPONENTIAL_SIGMOID_PARAM);
    opac.animateTo( 255.0f );
    opac.setDuration(2);
    
    timeStamp = 0;
    updatingOpacity = true;
    updatingPosition = false;
    
    int dist = 50; // Change the frequence of appearance of the 'dots'
 
    float xnow = -2*WIDTH;
    float ynow = -2*HEIGHT;
    
    while(ynow< 2*HEIGHT){
        if(xnow < 2*WIDTH){
            xnow += dist;
        }else{
            xnow = -2*WIDTH;
            ynow +=dist;
        }
        
        char cch = 'a' + rand()%26;
        int rando = rand()%4;
        ofTTFCharacter pathTmp = letter[rando].getCharacterAsPoints(cch);
        
        MyBoid *b = new MyBoid(xnow, ynow, opac.val(), pathTmp);
        boids.push_back(b);
    }
    
    cout<< "Number of Boids: "<< boids.size()<<endl;
}

void MyFlock::hide(){
    
    opac.setDuration(5);
    opac.animateTo(0.0f);
    
    for(vector<MyBoid*>::iterator it=boids.begin();it!=boids.end(); it++ ){
        (*it)->updateOpacity(opac.val());
    }
    
    updatingOpacity = true;

}

void MyFlock::show(){
    
   opac.setDuration(2);
   opac.animateTo(255.0f);
    
   for(vector<MyBoid*>::iterator it=boids.begin();it!=boids.end(); it++ ){
       (*it)->updateOpacity(opac.val());
   }
   
    updatingOpacity = true;

}


void MyFlock::update(){
    
    opac.update( 1.0f/60.0f );
    
    for(vector<MyBoid*>::iterator it=boids.begin();it!=boids.end(); it++ ){
        
        if(updatingOpacity == true){
            (*it)->updateOpacity(opac.val());
        }
        (*it)->update();
    }
    
  //  checkEndofAnimation();
}

void MyFlock::draw(){
  
    for(vector<MyBoid*>::iterator it=boids.begin();it!=boids.end(); it++ ){
        
        (*it)->draw();
    }
}

/*
 Maybe not necessary check with real values (not with mouse)..
*/
void MyFlock::checkEndofAnimation(){
    
    if( ofGetElapsedTimeMillis() - timeStamp > 100) {
        updatingPosition = false;
    }
}

void MyFlock::resetPosition(){
    
    for(vector<MyBoid*>::iterator it=boids.begin();it!=boids.end(); it++ ){
        (*it)->returnToInit();
    }
    updatingOpacity = true;

}

void MyFlock::addHumanPoint( ofVec2f p ){
   

    for(vector<MyBoid*>::iterator it=boids.begin();it!=boids.end(); it++ ){
       
 
       /*  Not that good repulsion --> too linear
        float dis = ((*it)->positionCurrent.x - p.x );
        
        // !!maybe eventspace should be person width == test
        if( abs(dis)<= eventSpace){
            float displace;
        
            //Check if its on left or right
            if(dis >= 0){
                displace = ofMap(dis , 0 , eventSpace , personWidth/2, 0);
            }else{
                displace = ofMap(dis, -eventSpace, 0, 0,  -personWidth/2);
            }
        
            ofVec2f moveToPoint;
            moveToPoint.set((*it)->positionCurrent.x + displace,(*it)->positionCurrent.y);
        */

        float dis = p.distance((*it)->positionCurrent);
        
        if( abs(dis)<= personWidth){

            float displace, opacityUp;
            displace  = ofMap(dis, 0, personWidth, 1, 0);
            opacityUp = ofMap(dis, 0, personWidth, 0.4, 1);
          
            ofVec2f moveToPoint;
            moveToPoint = (*it)->positionInitial.getInterpolated(p, -displace);
            
            (*it)->moveTo(moveToPoint);
        //  (*it)->updateOpacity(opacityUp*255); //Possibly to make it look cooler?
            timeStamp = ofGetElapsedTimeMillis(); // Not needed if not using the ChechFinishedAnimation();
        }
    }
    
//  updatingPosition = true;
//  updatingOpacity = false;
}


void MyFlock::addRepulsionPoint( ofVec2f p ){
    
    for(vector<MyBoid*>::iterator it=boids.begin();it!=boids.end(); it++ ){
      
        float displace, diplaceY, opacityUp;
       // float dis = p.distance((*it)->positionInitial);
        float dis = abs(p.x - (*it)->positionInitial.x);
        float disY = p.y; // From 0 to COORIDOR_WIDTH
        
        if( abs(dis)<= eventSpace){
            
            displace = ofMap(dis, 0, eventSpace, 1, 0);
            diplaceY = ofMap(disY, 0, COORIDOR_WIDTH, 1 ,0 );
    //      opacityUp = ofMap(dis, 0, eventSpace, 0.4, 1);
            
            ofVec2f moveToPoint;
            moveToPoint = (*it)->positionInitial.getInterpolated(ofVec2f(p.x, HEIGHT/2), -displace*diplaceY);
            
            (*it)->moveTo(moveToPoint);
            //  (*it)->updateOpacity(opacityUp*255); //Possibly to make it look cooler?
            timeStamp = ofGetElapsedTimeMillis(); // Not needed if not using the ChechFinishedAnimation();
        }
        
    }
}

void MyFlock::addAttractionPoint( ofVec2f p ){
    
    
    for(vector<MyBoid*>::iterator it=boids.begin();it!=boids.end(); it++ ){
       
        float displace, diplaceY, opacityUp;
  //    float dis = p.distance((*it)->positionInitial);
        float dis = abs(p.x - (*it)->positionInitial.x);
        float disY = p.y; // From 0 to COORIDOR_WIDTH

        if( abs(dis)<= eventSpace){
            
            displace  = ofMap(dis, 0, eventSpace, 1, 0);
            diplaceY = ofMap(disY, 0, COORIDOR_WIDTH, 0.75 , 0 );

            // opacityUp = ofMap(dis, 0, eventSpace, 0.4, 1);
            
            ofVec2f moveToPoint;
            moveToPoint = (*it)->positionInitial.getInterpolated(ofVec2f(p.x, HEIGHT/2), displace*diplaceY);
            
            (*it)->moveTo(moveToPoint);
            //  (*it)->updateOpacity(opacityUp*255); //Possibly to make it look cooler?
            timeStamp = ofGetElapsedTimeMillis(); // Not needed if not using the ChechFinishedAnimation();
        }
    }
}


