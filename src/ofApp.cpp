#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(20, 20, 20);
	ofSetWindowTitle("Minifab Schematic");
	ofSetFrameRate(60);//让图形边缘平滑

	uvled.led_Init();
	_plate.plate_Init();
	model.model_Init();
	platform.init();

	cam.setDistance(800);
	
	cam.orbit(0, 70, cam.getDistance());	
	cam.setDrag(0.5);
	ofEnableDepthTest();
	//ofVec3f point=ofVec3f(0, 0, 0);
	//cam.lookAt(point);
	//ofSetVerticalSync(true);//开启垂直同步


	// Directional Lights emit light based on their orientation, regardless of their position //
	light_Above.setDiffuseColor(ofColor(0.f, 0.f, 255.f));
	light_Above.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	light_Above.setDirectional();

	light_Above.setOrientation(ofVec3f(0, 90, 0));
}

//--------------------------------------------------------------
void ofApp::update(){
	switch (STATE)
	{
	case FINDHOME:
		{
			if (goState == UP)
			{
				_plate.setPlate_Up();
				model.setModelUp();
				cout << "going up" << endl;
			}
			if (goState == DOWN)
			{
				_plate.setPlate_Down();
				model.setModelDown();
				cout << "going down" << endl;
			}
			
			tempPosition = _plate.getPlateZ();
			if (tempPosition <= homePosition)
			{
				homeCount++;
				
				Sleep(stopTime);
				goState = UP;
				if (homeCount == 2)
				{
					STATE = PRINTCYCLE;
					goState = DOWN;
					cout << "I got home" << endl;
				}
			}
			if (tempPosition > normalHeight)
			{
				goState = DOWN;
			}
			break;
		}
	case PRINTCYCLE:
		{
			if (goState == UP)
			{
				_plate.setPlate_Up();
				model.setModelUp();
				cout << "going up" << endl;
			}
			if (goState == DOWN)
			{
				_plate.setPlate_Down();
				model.setModelDown();
				cout << "going down" << endl;
			}
			if (goState == STOP)
			{
				cout << "exposing" << endl;
				Sleep(stopTime);
				model.modelAppend();
				uvled.setLedOff();
				goState = UP;
			}
			tempPosition = _plate.getPlateZ();
			if (goState==DOWN&&tempPosition <= minimalHeight)
			{
				uvled.setLedOn();
				goState = STOP;
			}
			if (tempPosition > normalHeight)
			{
				goState = DOWN;
			}
			if (model.getModelHeight() >= 0.1)
			{
				STATE = FINISH;
			}
			break;
		}
			
	case FINISH:
		{
			_plate.setPlate_Up();
			model.setModelUp();
			tempPosition = _plate.getPlateZ();
			if (tempPosition >= maximalHeight)
			{
				STATE = FREE;
				std::cout << "finish" << endl;
			}
			break;
		}	
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	light_Above.enable();

	uvled.ledDraw();
	_plate.plateDraw();
	model.modelDraw();
	platform.platformDraw();

	light_Above.disable();
	cam.end();
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(), 2), 10, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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