#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simpleHands;
    
    vector <int> fingersFound;
    ofEasyCam cam;
    
    ofSoundPlayer  drums1;
    ofSoundPlayer  drums2;
    ofSoundPlayer  drums3;
    ofSoundPlayer  snare1;
    ofSoundPlayer  snare2;
    ofSoundPlayer  snare3;
    ofSoundPlayer  snare4;
    ofSoundPlayer  snare5;
    ofSoundPlayer  kick1;
    ofSoundPlayer  kick2;
    ofSoundPlayer  kick3;
    ofSoundPlayer  crash;
    ofSoundPlayer  bass;
    ofSoundPlayer  synth;
    ofSoundPlayer  sax;
    
    ofImage kickImage;
    ofImage snareImage;
    ofImage synthImage;
    ofImage cymbalImage;
    ofImage saxImage;
    ofImage drumkitImage;
    
    bool BPMswitch;
    
};