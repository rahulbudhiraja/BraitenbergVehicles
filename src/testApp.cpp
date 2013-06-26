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
	w = 240;
	h = 160;
#else
	w=240;
	h=320;

#endif

	findHue=120;

	rgb.allocate(w, h);
//	hsb.allocate(w, h);
//	hue.allocate(800,480);
//	sat.allocate(800,480);
//	bri.allocate(800,480);
//	filtered.allocate(800,480);
//	redFilter.allocate(800,480);

	hsb.allocate(82,63);
	hue.allocate(w,h);
	sat.allocate(w,h);
	bri.allocate(w,h);
	redFilter.allocate(w,h);

	// original //
	//croppedImage.allocate(235-72,290-165,OF_IMAGE_COLOR);// Portrait Image as seen by the phone .
	croppedImage.allocate(w,h,OF_IMAGE_COLOR);

#ifdef PORTRAIT
	rotatedCapturedImage.allocate(h,w);
#endif

	/* the braitenberg vehicle graphics */
	p.assign(1, demoParticle());
	currentMode = aggressive;

	resetParticles();

	ofSetFullscreen(true);
	counter=0;
#ifdef DEBUG
	HueValue="";
#endif
}

//--------------------------------------------------------------
void testApp::update(){
	grabber.update();

counter++;
	if(grabber.isFrameNew()&&counter%10==0)
	{
//		capturedImage.setFromPixels(grabber.getPixels(),grabber.getWidth(),grabber.getHeight(),OF_IMAGE_COLOR);
		//cop#
		counter=counter%10;

#ifndef PORTRAIT
				rgb.setFromPixels(grabber.getPixels(), 320,240);
#else
				rotatedCapturedImage.setFromPixels(grabber.getPixels(), h, w);
				rotatedCapturedImage.rotate(-90,h/2,w/2);
				rgb=rotatedCapturedImage;
#endif
				//rgb.rotate(-90,w/2,h/2); // portrait Mode,this works but...
			//	rgb.resize(800,480); // der
			//	setPixelsSubRegion(&rgb,&croppedImage,72+40,165,235-72,290-165,true); // der

				setPixelsSubRegion(&rgb,&croppedImage,37,78,82,63,true);

				croppedImage.resize(w,h);

				hsb.setFromPixels(croppedImage.getPixels(),croppedImage.getWidth(),croppedImage.getHeight());
				//hsb=rgb;

				//convert to hsb
				hsb.convertRgbToHsv();

				//store the three channels as grayscale images
				hsb.convertToGrayscalePlanarImages(hue, sat, bri);


				//filter image based on the hue value were looking for
				for (int i=0; i<w*h; i++)
				{
					redFilter.getPixels()[i] = ofInRange(hue.getPixels()[i],0,13) || ofInRange(hue.getPixels()[i],160,180)? 255 : 0; // red ..
//					ofLog()<<"Value of i"<<i;
				}

				ofLog()<<"The dimensions of the redFilter are"<<redFilter.getWidth()<<"  "<<redFilter.getHeight();
				redFilter.flagImageChanged();

				//run the contour finder on the filtered image to find blobs with a certain hue
				redContours.findContours(redFilter, 50, w*h/5, 1, false);
				//croppedImage.resize(800,480);
				//rgb.resize(800,480);
#ifdef DEBUG
				croppedImage.resize(800,480);
#endif
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

	    //rgb.resize(600,800); -- This wrks ...The exact size needs to be found though ...
#ifdef PORTRAIT
	    //rotatedCapturedImage.draw(0,320);
	   // ofRect(60,320,240,320);

#endif

	    ofPushMatrix();

	    ofTranslate(480,0); // DER

	    ofRotateZ(90);
	    ofDrawAxis(20);
	    //rgb.draw(0,0);
#ifdef DEBUG
	     croppedImage.draw(0,0);
#endif

	    ofSetColor(255,0,0);
	    //redContours.resize(800,480);
		ofSetHexColor(0x000000);

		ofLog()<<"Number of Blobs"<<redContours.nBlobs;

    if(redContours.nBlobs>0&&counter%10==0)
    {
//        if(contours.blobs[0].area>1000)
//        {
    	 // Some Sort of modification might be necessary ,maybe multiplying something like 480/320 *x,800/240*y .Probably something like that may work .
            p[0].sourceCenterX=redContours.blobs[0].centroid.x*2.5; //(800/320)
            p[0].sourceCenterY=redContours.blobs[0].centroid.y*2; // 480/240

            ofLog()<<"Source Center"<<p[0].sourceCenterX<<"     "<<p[0].sourceCenterY;
//        }
    }
		for(int i = 0; i <  p.size(); i++){
				p[i].drawp();
			}
		ofFill();
		ofSetColor(255,0,0);
		ofCircle(p[0].sourceCenterX,p[0].sourceCenterY,2); // Axis is reversed so y of the image is around 480 and x which is effectively downwards is 800

		  ofPopMatrix();
		  ofSetColor(0,255,0);


// debug
		 // ofRect(185,70,135,275);
//
		  ofSetLineWidth(10);
		  ofLine(0,0,480,0);
		  ofLine(0,0,0,800);
		  ofLine(479,0,479,800);
		  ofLine(0,799,480,799);


#ifdef DEBUG
		  ofDrawBitmapString("Hue value " + ofToString(hue.getPixels()[10*240+2]),20,20);
#endif
		  ofSetLineWidth(1);
		  //ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()),20,350);

		  ofLog()<<"The dimensions are"<<croppedImage.getWidth()<<"   "<<croppedImage.getHeight();

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
void testApp::mousePressed(int x, int y, int button)

{
	HueValue=""+ hue.getPixels()[0];
	ofLog()<<" Hue value"<<hue.getPixels()[y+(320*x)/480];
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::setPixelsSubRegion(ofxCvImage * orgImage, ofImage * targetImage,int x, int y,int width, int height, bool color)
		{
			unsigned char * pixels = orgImage->getPixels();
			int totalWidth = orgImage->getWidth();
			int subRegionLength = width * height;
			if(color) subRegionLength*=3; // rgb
			unsigned char subRegion[subRegionLength];

			int result_pix = 0;
			for (int i = y; i < y+height; i++)
			{
				for(int j = x; j < x+width; j++)
				{
					int base = (i * totalWidth) + j;
					if(color) base *= 3; // rgb

					subRegion[result_pix] = pixels[base];
					result_pix++;

					if(color)
					{
						subRegion[result_pix] = pixels[base+1];
						result_pix++;
						subRegion[result_pix] = pixels[base+2];
						result_pix++;
					}
				}
			}
			if(color)
				targetImage->setFromPixels(subRegion, width, height, OF_IMAGE_COLOR, true);
			else
				targetImage->setFromPixels(subRegion, width, height, OF_IMAGE_GRAYSCALE, false);
}

