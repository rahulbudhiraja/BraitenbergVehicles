#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "demoParticle.h"

class testApp : public ofBaseApp{
	
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

		ofVideoGrabber grabber;
		ofImage capturedImage;

		int w,h;
		int findHue;

		ofxCvColorImage rgb,hsb,rotatedCapturedImage;
		ofImage croppedImage;
		ofxCvGrayscaleImage hue,sat,bri,filtered,filtered2,redFilter,yellowFilter,greenFilter,blueFilter;
		ofxCvContourFinder contours,redContours,greenContours,blueContours,yellowContours;

		/** Variables for the actual vehicles */
		particleMode currentMode;
		string currentModeStr;

		vector <demoParticle> p;
		vector <ofPoint> attractPoints;
		vector <ofPoint> attractPointsWithMovement;

		void resetParticles();

		//From oF forum
		void setPixelsSubRegion(ofxCvImage * orgImage, ofImage * targetImage,int x, int y,int width, int height, bool color);
    

};

#endif	

