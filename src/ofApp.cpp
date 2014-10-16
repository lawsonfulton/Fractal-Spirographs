#include "ofApp.h"

double armLength(int i);
double rotSpeed(int i);
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(500);
    ofSetVerticalSync(false);
    ofBackground(50);
    
    //Set up frame buffer for trails
    trailFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA );
    trailFbo.begin();
    ofClear(255,255,255, 0);
    trailFbo.end();
    
    //Pick a center for everything to rotate around
    center.set(ofGetWidth()*0.5, ofGetHeight()*0.5, 0);
        
    //initial values
    armCount = 10;
    armLengths.resize(armCount);
    armAngles.resize(armCount);
    rotSpeeds.resize(armCount);
    endPoints.resize(armCount);
    oldEndPoints.resize(armCount);
    
    for(int i = 0; i < armCount; i++) {
        armLengths[i] = armLength(i);
        armAngles[i] = 0.0;
        rotSpeeds[i] = rotSpeed(i);
    }
    
    
    //initialize endpoints
    updateEndpoints();
    saveOldEndpoints();
}

double armLength(int i) {
//    return 200.0 / ((i + 1) * (i+1));
    if(i == 0) return 200.0;
    
    return -armLength(i - 1) / 2.0;
}

double rotSpeed(int i) {
    if(i == 0) return 0.0005;
    
    return rotSpeed(i - 1) * 2.0;
}
//--------------------------------------------------------------
void ofApp::update(){
    updateArms();
    
    
    trailFbo.begin();
    drawTrail();
    trailFbo.end();
}

void ofApp::updateArms(){
    updateAngles();
    saveOldEndpoints();
    updateEndpoints();
}

void ofApp::updateAngles(){
    
    //Update angles
    for(int i = 0; i < armCount; i++) {
        armAngles[i] = rotSpeeds[i] * ofGetFrameNum();
        
        if(armAngles[i] >= TWO_PI) {
//TODO NEED T ROUND TO NEAREST PI            armAngles[i] = 0.0; //causes accuracy issues
        }
    }
    
}

void ofApp::saveOldEndpoints() {
    //Save the old endpoints
    for(int i = 0; i < armCount; i++) {
        oldEndPoints[i] = endPoints[i];
    }
}

void ofApp::updateEndpoints() {
    //Update endpoints
    ofPoint lastEndpoint = ofPoint(0,0,0);
    double cumulativeAngle = 0.0;
    for(int i = 0; i < armCount; i++) {
        cumulativeAngle += armAngles[i];//Add the current angle
        
        ofPoint offset;
        offset.set(0, armLengths[i], 0); //Starts straight up and down
        offset.rotateRad(0,0, cumulativeAngle); //Rotate it
        
        endPoints[i] = lastEndpoint + offset; //Vector sum
        lastEndpoint = endPoints[i]; //Start again
    }
}

//--------------------------------------------------------------
void ofApp::drawTrail() {
    ofTranslate(center);
    
    ofSetColor(255,255,0);
    ofSetLineWidth(1);

    ofPoint start = oldEndPoints.back();
    ofPoint end = endPoints.back();
    ofLine(start, end);
}

//--------------------------------------------------------------
void ofApp::draw(){
    string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 100,100);
    
    //cam.setTarget(center);
    //cam.begin();
    
    trailFbo.draw(0,0);

    //we translate everything to the center of the circle so it's easier to draw and understand.
    ofTranslate(center);
    
    //draw the yellow circle
    
    ofSetColor(0, 140, 255);
    ofSetLineWidth(3);
    
    ofPoint lastEndpoint = ofPoint(0,0,0);
    for(int i = 0; i < armCount; i++) {
        ofLine(lastEndpoint, endPoints[i]);
        lastEndpoint = endPoints[i];
    }
    
    //cam.end();
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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