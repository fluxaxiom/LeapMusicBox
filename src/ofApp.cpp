#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    leap.open();
    
    cam.setOrientation(ofPoint(-20, 0, 0));
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    drums1.loadSound("sounds/Drums 01.mp3");
    drums2.loadSound("sounds/Drums 02.mp3");
    drums3.loadSound("sounds/Drums 03.mp3");
    snare1.loadSound("sounds/Snare 01.mp3");
    snare2.loadSound("sounds/Snare 02.mp3");
    snare3.loadSound("sounds/Snare 03.mp3");
    snare4.loadSound("sounds/Snare 04.mp3");
    snare5.loadSound("sounds/Snare 05.mp3");
    kick1.loadSound("sounds/Kick 01.mp3");
    kick2.loadSound("sounds/Kick 02.mp3");
    kick3.loadSound("sounds/Kick 03.mp3");
    crash.loadSound("sounds/Crash.mp3");
    bass.loadSound("sounds/Bass.mp3");
    synth.loadSound("sounds/Synth.mp3");
    sax.loadSound("sounds/Sax.mp3");
    
    drums1.setLoop(true);
    drums1.setMultiPlay(false);
    drums1.setVolume(0.5);
    
    bass.setLoop(true);
    bass.setMultiPlay(false);
    bass.setVolume(1.0);
    
    sax.setLoop(false);
    sax.setMultiPlay(false);
    sax.setVolume(1.0);
    
    crash.setLoop(false);
    crash.setMultiPlay(false);
    crash.setVolume(1.0);
    
    kickImage.loadImage("images/kick.gif");
    snareImage.loadImage("images/snare.gif");
    synthImage.loadImage("images/synth.gif");
    cymbalImage.loadImage("images/cymbal.gif");
    saxImage.loadImage("images/sax.gif");
    drumkitImage.loadImage("images/drumkit.gif");




}

//--------------------------------------------------------------
void ofApp::update(){
    
    fingersFound.clear();
    
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        
        for(int i = 0; i < simpleHands.size(); i++){
            for (int f=0; f<5; f++) {
                int id = simpleHands[i].fingers[ fingerTypes[f] ].id;
                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;
                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;
                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;
                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;
                fingersFound.push_back(id);
            }
        }
    }

    
    leap.markFrameAsOld();
    
    ofSoundUpdate();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofBackgroundGradient(ofColor(20,20,100), ofColor(20, 100, 20),  OF_GRADIENT_BAR);
    
    if (leap.isConnected()){
        ofSetColor(0,200,0);
        ofDrawBitmapString("Frank's Leap Music\nLeap Connected ", 20, 20);
        ofDrawBitmapString("To change sounds use keyboard\nKick: 1 2 3\nSnare: Q W E R T\nDrumloop: A S D\nKill Loop: Z\nToggle BPM mode: X", 20,60);

    }
    else{
        ofSetColor(200,200,200);
        ofDrawBitmapString("Frank's Leap Music\nPlease connect Leap Controller! ", 20, 20);
    }

    ofEnableAlphaBlending();
    
    cam.begin();
    
    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
    
    
    // draw hands
    for(int i = 0; i < simpleHands.size(); i++){
        bool isLeft        = simpleHands[i].isLeft;
        ofPoint handPos    = simpleHands[i].handPos;
        ofPoint handNormal = simpleHands[i].handNormal;
        
        if (isLeft){
            if (synth.getIsPlaying()){
                synthImage.draw(-1000,200,-2000);
                ofSetColor(100, 0, 0);
            }
            else{
                ofSetColor(0, 0, 100);
                synthImage.draw(-1000,200,-2100);
            }
            if (handPos.z<0){
                ofSetColor(200, 200, 200);
                kickImage.draw(-400, -200,-100);
            }
            if (handPos.z>0){
                kickImage.draw(-500, -200, -200);
            }
        }
        else{
            if (sax.getIsPlaying()){
                saxImage.draw(-1000,-5000,-4000);
                ofSetColor(0, 0, 200);
            }
            else{
                ofSetColor(100, 100, 100);
            }
            if (handPos.y>-50){
                if (handPos.z<0){
                    ofSetColor(200, 200, 200);
                    cymbalImage.draw(400, -1000,-1900);
                }
                if (handPos.z>0){
                    cymbalImage.draw(400, -1000,-2000);
                }
            }
            if (handPos.y<-50){
                if (handPos.z<0){
                    ofSetColor(200, 200, 200);
                    snareImage.draw(400,-1500,-1400);
                }
                if (handPos.z>0){
                    snareImage.draw(400,-1500,-1500);
                }
            }

        }
        
        ofDrawSphere(handPos.x, handPos.y, handPos.z, 20);
        ofSetColor(handPos.x, handPos.y, handPos.z);
        ofDrawArrow(handPos, handPos + 100*handNormal);
        
        for (int f=0; f<5; f++) {
            ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;
            ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;
            ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;
            ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;
            
            ofSetColor(0, 0, 100);
            ofDrawSphere(mcp.x, mcp.y, mcp.z, 12);
            ofDrawSphere(pip.x, pip.y, pip.z, 12);
            ofDrawSphere(dip.x, dip.y, dip.z, 12);
            ofDrawSphere(tip.x, tip.y, tip.z, 12);
            
            if (isLeft){
                ofSetColor(handPos.x,handPos.z,handPos.x*(-1.0));
            }
            else{
                ofSetColor(handPos.y, handPos.y*(-1.0), handPos.z);
            }
            ofSetLineWidth(5);
            ofLine(mcp.x, mcp.y, mcp.z, pip.x, pip.y, pip.z);
            ofLine(pip.x, pip.y, pip.z, dip.x, dip.y, dip.z);
            ofLine(dip.x, dip.y, dip.z, tip.x, tip.y, tip.z);
        }
        
        
        // trigger sounds

        
        // right hand
        if (!isLeft){
            if (BPMswitch){
            drums1.setSpeed(handPos.y*.009);
            bass.setSpeed(handPos.y*.009);
            }
            if (handPos.x<-50){
                sax.play();
            }
            if (handPos.y>-50){
                if (handPos.z>0){
                    crash.play();
                }
            }
            if (handPos.y<-50){
                if (handPos.z>0){
                    snare1.play();
                }
            }
        }
  
        // left hand
        if (isLeft){
            if (handPos.x>0&&handPos.y<0){
                drums1.stop();
                bass.stop();
                drumkitImage.clear();
            }
            if (!drums1.getIsPlaying()){
                if (handPos.x>0){
                    drums1.play();
                    bass.play();
                }
            }
            if (handPos.z>0){
                kick1.play();
            }
            if (handPos.y>100){
            if (synth.getIsPlaying()){
                synth.setPan(handPos.x*.025);
            }
            else {
                synth.play();
                synth.setPan(handPos.x*.025);
            }
            }
            else {
                synth.stop();
            }
            if (sax.getIsPlaying()){
                sax.setPan(handPos.z*.025);
            }
        }

        if (drums1.getIsPlaying()){
            ofSetColor(200,200,200);
            drumkitImage.draw(100,100,0);
        }
        
 //debug stringouts
 /*
        if (isLeft){
            ofSetColor(150, 150, 150);
            ofDrawBitmapString("X " + ofToString(handPos.x), -100, 100);
            ofDrawBitmapString("Y " + ofToString(handPos.y), -100, 120);
            ofDrawBitmapString("Z " + ofToString(handPos.z), -100, 140);
        }
        else{
            ofSetColor(150, 150, 150);
            ofDrawBitmapString("X " + ofToString(handPos.x), 20, 100);
            ofDrawBitmapString("Y " + ofToString(handPos.y), 20, 120);
            ofDrawBitmapString("Z " + ofToString(handPos.z), 20, 140);
        }
  */
        

    }
    
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key=='1'){
        kick1.loadSound("sounds/Kick 01.mp3");
    }
    if (key=='2'){
        kick1.loadSound("sounds/Kick 02.mp3");
    }
    if (key=='3'){
        kick1.loadSound("sounds/Kick 03.mp3");
    }
    if (key=='q'){
        snare1.loadSound("sounds/Snare 01.mp3");
    }
    if (key=='w'){
        snare1.loadSound("sounds/Snare 02.mp3");
    }
    if (key=='e'){
        snare1.loadSound("sounds/Snare 03.mp3");
    }
    if (key=='r'){
        snare1.loadSound("sounds/Snare 04.mp3");
    }
    if (key=='t'){
        snare1.loadSound("sounds/Snare 05.mp3");
    }
    if (key=='a'){
        drums1.loadSound("sounds/Drums 01.mp3");
        bass.loadSound("sounds/Bass.mp3");
    }
    if (key=='s'){
        drums1.loadSound("sounds/Drums 02.mp3");
        bass.loadSound("sounds/Bass.mp3");
    }
    if (key=='d'){
        drums1.loadSound("sounds/Drums 03.mp3");
        bass.loadSound("sounds/Bass.mp3");
    }
    if (key=='z'){
        drums1.loadSound("sounds/Drums 01.mp3");
        bass.loadSound("sounds/Bass.mp3");
    }
    if (key=='x'){
        if (BPMswitch){
            BPMswitch=0;
        }
        else {
            BPMswitch=1;
        }
        
    }
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

//--------------------------------------------------------------
void ofApp::exit(){
    leap.close();
}


