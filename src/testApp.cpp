#include "testApp.h"
#include "ofxAndroidVideoGrabber.h"

//# define PORTRAIT

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(120);


	ofBackground(0,0,0);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetOrientation(OF_ORIENTATION_DEFAULT);
	grabber.setDeviceID(1);
	grabber.initGrabber(320,240);
	grabber.listDevices();

//	capturedImage.allocate(320, 240, OF_IMAGE_COLOR);

#ifndef PORTRAIT
	w = 320;
	h = 240;
#else
	w=240;
	h=320;

#endif

	findHue=120;

	rgb.allocate(w, h);
	hsb.allocate(w, h);
	hue.allocate(w, h);
	sat.allocate(w, h);
	bri.allocate(w, h);
	filtered.allocate(w, h);
	redFilter.allocate(w, h);
	greenFilter.allocate(w, h);
	blueFilter.allocate(w, h);
	yellowFilter.allocate(w, h);
#ifdef PORTRAIT
	rotatedCapturedImage.allocate(h,w);
#endif

	/* the braitenberg vehicle graphics */
	p.assign(1, demoParticle());
	currentMode = aggressive;

	resetParticles();

	ofSetFullscreen(true);
}

//--------------------------------------------------------------
void testApp::update(){
	grabber.update();
	if(grabber.isFrameNew())
	{
//		capturedImage.setFromPixels(grabber.getPixels(),grabber.getWidth(),grabber.getHeight(),OF_IMAGE_COLOR);
		//cop#

#ifndef PORTRAIT
				rgb.setFromPixels(grabber.getPixels(), w, h);
#else
				rotatedCapturedImage.setFromPixels(grabber.getPixels(), h, w);
				rotatedCapturedImage.rotate(-90,h/2,w/2);
				rgb=rotatedCapturedImage;
#endif
				//rgb.rotate(-90,w/2,h/2); // portrait Mode,this works but...


				//mirror horizontal
				//rgb.mirror(false, true);

				//duplicate rgb
				hsb = rgb;

				//convert to hsb
				hsb.convertRgbToHsv();

				//store the three channels as grayscale images
				hsb.convertToGrayscalePlanarImages(hue, sat, bri);

//				hue.resize(800,480);

				//filter image based on the hue value were looking for
				for (int i=0; i<w*h; i++)
				{
					redFilter.getPixels()[i] = ofInRange(hue.getPixels()[i],0,13 ) ? 255 : 0; // red ..
//				//	greenFilter.getPixels()[i] = ofInRange(hue.getPixels()[i],75,82 ) ? 255 : 0; // green
//					blueFilter.getPixels()[i] = ofInRange(hue.getPixels()[i],90,125) ? 255 : 0; // blue
//					yellowFilter.getPixels()[i] = ofInRange(hue.getPixels()[i],37,45 ) ? 255 : 0; // yellow
				}
				filtered.flagImageChanged();

				//run the contour finder on the filtered image to find blobs with a certain hue
				redContours.findContours(redFilter, 50, w*h/5, 1, false);
//				greenContours.findContours(greenFilter, 50, w*h/5, 1, false);
//				blueContours.findContours(blueFilter, 50, w*h/5, 1, false);
//				yellowContours.findContours(yellowFilter, 50, w*h/5, 1, false);
        
				rgb.resize(800,480);


			}

	for(int i = 0; i <  p.size(); i++){
			p[i].setMode(currentMode);
			p[i].update();
		}

	ofLog()<<"The dimensions are"<<ofGetScreenWidth()<<"  "<<ofGetScreenHeight();
	}


//--------------------------------------------------------------
void testApp::draw(){




	    ofSetHexColor(0xFFFFFF);
		//grabber.draw(0,00);
		//capturedImage.resize(640, 480);
		//capturedImage.draw(0,0);

	    //rgb.resize(600,800); -- This wrks ...The exact size needs to be found though ...
#ifdef PORTRAIT
	    //rotatedCapturedImage.draw(0,320);
	   // ofRect(60,320,240,320);

#endif

	    ofPushMatrix();

	    ofTranslate(480,0);
	    ofRotateZ(90);
	    ofDrawAxis(10);

	    rgb.draw(0,0);
	    ofSetColor(255,0,0);
	    //redContours.resize(800,480);
		redContours.draw(0,0);
		ofSetColor(255,255,255);
		//ofSetColor(0,255,0);
		//rgb.draw(w,0);
		ofSetColor(0,0,255);
		//blueContours.draw(0,0);
		ofSetColor(0,255,0);
		//greenContours.draw(0,0);
		ofSetColor(255,255,51);
		//yellowContours.draw(0,0);
		ofSetHexColor(0x000000);

		//ofRect(0,0,250,400);

    if(redContours.nBlobs>0)
    {
//        if(contours.blobs[0].area>1000)
//        {

    	 // Some Sort of modification might be necessary ,maybe multiplying something like 480/320 *x,800/240*y .Probably something like that may work .
            p[0].sourceCenterX=redContours.blobs[0].centroid.x*2.5; //(800/320)
            p[0].sourceCenterY=redContours.blobs[0].centroid.y*(480/240); // 480/240
//        }
    }
		for(int i = 0; i <  p.size(); i++){
				p[i].drawp();
			}
ofFill();
ofSetColor(255,0,0);
ofCircle(p[0].sourceCenterX,p[0].sourceCenterY,20); // Axis is reversed so y of the image is around 480 and x which is effectively downwards is 800

		  ofPopMatrix();
		  ofSetColor(255,0,0);
		  ofSetLineWidth(10);
		  ofLine(0,0,480,0);
		  ofLine(0,0,0,800);
		  ofLine(479,0,479,800);
		  ofLine(0,799,480,799);



		  ofSetLineWidth(1);
		  ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()),20,350);

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

void testApp::resetParticles(){


	for(int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].reset();
	}
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

