#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    flock = new MyFlock();
    ofBackground(0);
    
    once = false;
    mouseMove = false;
    
    prevMouseX = mouseX;
    prevMouseY = mouseY;
    
}

//--------------------------------------------------------------
void ofApp::update(){
  
    flock->update();

}

//--------------------------------------------------------------
void ofApp::draw(){

    flock->draw();
    
    // Check that it happens not when the movement stops but continuasley
    // not possible with the pouse at this point.. since mouseX resets when the movement ends
   
    if((prevMouseX!=mouseX && prevMouseY != mouseY)){
        
        flock->resetPosition();
        
     //   if(abs(prevMouseX - mouseX)>jitter && abs(prevMouseY - mouseY)>jitter){
            once = false;
     //   }
    }
    
    if(!once){
        flock->addHumanPoint(ofVec2f(mouseX, mouseY));
        once = true;
    }
  
    prevMouseX = mouseX;
    prevMouseY = mouseY;
    mouseMove = false;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   
    float mappedY = ofMap(mouseY, 0, HEIGHT, 0, COORIDOR_WIDTH);
    flock->addAttractionPoint(ofVec2f(mouseX,mappedY));

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    float mappedY = ofMap(mouseY, 0, HEIGHT, 0, COORIDOR_WIDTH);
    flock->addRepulsionPoint(ofVec2f(x,mappedY));

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
