#pragma once

#include "ofMain.h"
#include <vector>

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
        void updateArms();
        void updateAngles();
        void saveOldEndpoints();
        void updateEndpoints();
        void drawTrail();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofEasyCam cam;

    
        ofFbo trailFbo;
    
        ofPoint center;
    
        int armCount;
        std::vector<double> armLengths; //of units
        std::vector<double> armAngles; //Radians
        std::vector<double> rotSpeeds; //Radians per second
        std::vector<ofPoint> endPoints;
        std::vector<ofPoint> oldEndPoints;
};
