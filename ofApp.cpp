#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->mouse_down_count = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->fbo.begin();

	if (ofGetMousePressed()) {

		ofSetColor(0);
		ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 30);
		this->mouse_down_count++;
	}

	this->fbo.end();
	this->fbo.readToPixels(this->pix);
}

//--------------------------------------------------------------
void ofApp::draw() {

	//this->fbo.draw(0, 0);

	while (circles.size() < mouse_down_count * 5){

		int x = ofRandom(ofGetWidth());
		int y = ofRandom(ofGetHeight());

		ofColor pix_color = this->pix.getColor(x, y);
		if (pix_color != ofColor(0)) {

			continue;
		}

		ofColor color;
		color.setHsb(ofRandom(255), 255, 255);
		ofPoint point = ofPoint(x, y);
		float radius = ofRandom(2, 35);

		bool flag = true;
		for (int i = 0; i < circles.size(); i++) {

			if (point.distance(get<1>(circles[i])) < get<2>(circles[i]) + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			circles.push_back(make_tuple(color, point, radius));
		}
	}

	for (int circles_index = 0; circles_index < circles.size(); circles_index++) {

		ofColor color = get<0>(circles[circles_index]);
		ofPoint point = get<1>(circles[circles_index]);
		float radius = get<2>(circles[circles_index]);

		ofSetColor(color);
		ofDrawCircle(point, radius);
	}

	ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	this->fbo.begin();
	ofClear(0);
	this->fbo.end();

	this->mouse_down_count = 0;
	this->circles.clear();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}