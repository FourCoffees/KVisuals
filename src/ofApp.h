#pragma once

#include "ofMain.h"
#include "MyFlock.h"


#define WIDTH 1920
#define HEIGHT 1024
#define personWidth 140
#define eventSpace 640
#define jitter 5 // For final project if not steady..
#define COORIDOR_WIDTH 1000 // Arbitory number to make calculations easier --> this is the Y of the kinect image


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

    
        void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        bool once;
        MyFlock *flock;
    
        int prevMouseX;
        int prevMouseY;
        bool mouseMove;

};
