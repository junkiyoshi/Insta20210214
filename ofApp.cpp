#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);

	this->cap.open("D:\\MP4\\wave2.mp4");
	this->cap_size = cv::Size(1280, 720);

	this->gray_image.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_GRAYSCALE);
	this->gray = cv::Mat(this->gray_image.getHeight(), this->gray_image.getWidth(), CV_MAKETYPE(CV_8U, this->gray_image.getPixels().getNumChannels()), this->gray_image.getPixels().getData(), 0);

	this->edge_image.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_GRAYSCALE);
	this->edge = cv::Mat(this->edge_image.getHeight(), this->edge_image.getWidth(), CV_MAKETYPE(CV_8U, this->edge_image.getPixels().getNumChannels()), this->edge_image.getPixels().getData(), 0);
}

//--------------------------------------------------------------
void ofApp::update() {

	cv::Mat cap_frame, resize_frame;
	this->cap >> cap_frame;
	if (cap_frame.empty()) {

		cap.set(cv::CAP_PROP_POS_FRAMES, 1);
		return;
	}
	cv::resize(cap_frame, resize_frame, this->cap_size);

	cv::cvtColor(resize_frame, this->gray, cv::COLOR_RGB2GRAY);
	this->gray.forEach<uchar>([](uchar& value, const int* position) -> void {

		value = floor(value / 50) * 50;
	});

	cv::Canny(this->gray, this->edge, 10, 200);

	this->gray_image.update();
	this->edge_image.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSetColor(239);
	string word = "PCD 2021";
	this->font.drawStringAsShapes(word, this->font.stringWidth(word) * -0.5, this->font.stringHeight(word) * 0.5);

	this->gray_image.draw(0, 0);
	this->edge_image.draw(0, 0);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}