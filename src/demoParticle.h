#pragma once
#include "ofMain.h"

enum particleMode{
	aggressive = 0,
	permlove,
	templove,
	fear
};

class demoParticle{

	public:
		demoParticle();
		
		void setMode(particleMode newMode);	
		void setAttractPoints( vector <ofPoint> * attract );

		void reset();
		void update();
		void drawp();		
		
		ofVec2f pos;
		ofVec2f vel;
		ofVec2f accl;
	
		float r;
		float maxforce;
		float maxspeed;

		ofVec2f target;
		ofVec2f desired;
		ofVec2f steer;

		float angle;
		particleMode mode;
		
		ofPath path;

		vector <ofPoint> * attractPoints; 

        int sourceCenterX,sourceCenterY;
};
