#include "demoParticle.h"

/// Changed d- desired.length() to 2400 from 1200

//------------------------------------------------------------------
demoParticle::demoParticle(){
	attractPoints = NULL;
}

//------------------------------------------------------------------
void demoParticle::setMode(particleMode newMode){
	mode = newMode;
}

//------------------------------------------------------------------
void demoParticle::setAttractPoints( vector <ofPoint> * attract ){
	attractPoints = attract;
}

//------------------------------------------------------------------
void demoParticle::reset(){
		
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	
	accl.set (0,0);
    vel.set(0,0);
    r = 240.0;
    maxspeed = 17;
   /// maxforce = 2;

}

//------------------------------------------------------------------
void demoParticle::update(){

	if( mode == aggressive ){

//	target.set (ofGetMouseX(), ofGetMouseY());
	target.set (sourceCenterX,sourceCenterY);
    desired = target - pos;
	float d = desired.length();
    desired.normalize();
	float ang = desired.angle(vel);
	


		if (d < 2400 && d > 30) {
   
      float m = ofMap(d,2400,600,maxspeed/6,maxspeed/4);
	   m = ofMap(d,600,300,maxspeed/4,maxspeed/2);
	 m = ofMap(d,300,200,maxspeed/2,maxspeed);
	  
	  maxforce = ofMap(d,2400,1000,0,.001);
	  maxforce = ofMap(d,1000,600,.001, .006);
	  maxforce = ofMap(d,600,400,.006, .009);
	  maxforce = ofMap(d,600,400,.009, .01);
	  maxforce = ofMap(d,400,300,.01, .05);
	   maxforce = ofMap(d,300,200,.05, .08);
	   maxforce = ofMap(d,200,30,.08, .8);
      desired *=m;
	 // if (vel.length()<2.5 ) vel *= 1.5;
	  steer = (desired -vel);
	 
	    steer.limit(maxforce);
		accl += steer;

	vel += accl; 
	
	vel.limit(maxspeed);
    pos +=vel;
	accl *= 0;

    } 
		else if (d <= 30 && d>20){
			float  m = ofMap(d,30,20,maxspeed,0);
      desired *=m;
	  steer = (desired -vel);
	 
	    steer.limit(maxforce);
		accl += steer;

	vel += accl; 
	
	vel.limit(maxspeed);
    pos +=vel;
    accl *= 0;

		}
	

	}
	else if( mode == permlove){
			target.set (ofGetMouseX(), ofGetMouseY());
    desired = (target - pos);
	float d = desired.length();
    desired.normalize();
	if (d < 100) {
   
      float m = ofMap(d,40,100,0,maxspeed);
      desired *=m;
    } else {

      desired *= maxspeed;
    }
    
    steer = (desired -vel);
    steer.limit(maxforce);
	accl += steer;
	//accl *= 1/((desired.length()*desired.length()));

	vel += accl;
    vel.limit(maxspeed);
    pos +=vel;
    accl *= 0;
		}
	
	else if( mode == fear){
		
		 
	target.set (ofGetMouseX(), ofGetMouseY());
    desired = -(target - pos);
	float d = desired.length();
    desired.normalize();

	if (d < 2400 && d > 30) {
   
      float m = ofMap(d,2400,600,1.2*maxspeed,1.3* maxspeed);
	  m = ofMap(d,600,300,1.3* maxspeed,	1.5* maxspeed);
	 m = ofMap(d,300,200, 1.8* maxspeed, 1.8*maxspeed);
	  m = ofMap(d,200,30, 1.8* maxspeed, 2.2*maxspeed);
	  maxforce = ofMap(d,2400,1000,0,.001);
	  maxforce = ofMap(d,1000,600,.001, .006);
	  maxforce = ofMap(d,600,300,.006, .009);
	 // maxforce = ofMap(d,600,400,.009, .01);
	  maxforce = ofMap(d,300,200,.009, .05);
	   maxforce = ofMap(d,200,30,.05, .15);
	  // maxforce = ofMap(d,200,30,1.5, 2.5);
      desired *=m;
	  float angl = desired.angle(vel);
	  cout <<"vel0" << vel.length() <<endl;
	  if (vel.length()<3.5) vel *= 1.5;
	  //if (desired.length()<20) desired *= 1.3;
	   steer = desired +(vel);
	  
	    steer.limit(maxforce);
		accl += steer;
	
	
	vel += accl; 
	
	vel.limit(maxspeed);
    pos +=vel;
	accl *= 0;

    } 
		else if (d <= 30){
			float  m = ofMap(d,30,10, 2.2*maxspeed, 2.2*maxspeed);
			 maxforce = ofMap(d,30, 0,.15, .55);
      desired *=m;
	  steer = (desired  +vel);
	 
	    steer.limit(maxforce);
		accl += steer;

	vel += accl; 
	
	vel.limit(maxspeed);
    pos +=vel;
    accl *= 0;

		}
		else {
		//float m = ofMap(d,2400,1500,maxspeed/3,maxspeed/10);
	  maxforce = ofMap(d ,2400,1500,0,0);
	  
	  
	float m = ofMap(d,2400,1500,0.001, 0.001);
	desired *=m;

	//if (desired.normalize() != vel.normalize() && desired.normalize() != -(vel.normalize())){
	steer = (desired -vel);
	 
	    steer.limit(-maxforce);
		accl += steer;
	vel += accl; 
	vel.limit(maxspeed);
    pos +=vel;
    accl *= 0;

	
    }
		}
		
		

	else if( mode == templove){
				 
	target.set (ofGetMouseX(), ofGetMouseY());
    desired = -(target - pos);
	float d = desired.length();
    desired.normalize();
	

	if (d < 2400 && d > 50) {
   
    float m = ofMap(d,2400,600,1.2*maxspeed,1.3* maxspeed);
	m = ofMap(d,600,300,1.3* maxspeed,	1.5* maxspeed);
	m = ofMap(d,300,200, 1.8* maxspeed, 1.8*maxspeed);
	m = ofMap(d,200,20, 1.8* maxspeed, 2.2*maxspeed);
	maxforce = ofMap(d,2400,1000,0,.001);
	maxforce = ofMap(d,1000,600,.001, .006);
	maxforce = ofMap(d,600,300,.006, .009);
	 // maxforce = ofMap(d,600,400,.009, .01);
	maxforce = ofMap(d,300,200,.009, .05);
	maxforce = ofMap(d,200,20,.05, .25);
	  // maxforce = ofMap(d,200,30,1.5, 2.5);
      desired *=m;
	  float angl = desired.angle(vel);
	  cout <<"vel0" << vel.length() <<endl;
	  if (vel.length()<3.5 ) vel *= 1.5;
	  //if (desired.length()<20) desired *= 1.3;
	   steer = desired +(vel);
	  
	    steer.limit(maxforce);
		accl += steer;
	
	
	vel += accl; 
	
	vel.limit(maxspeed);
    pos +=vel;
	accl *= 0;

    } 
		else if (d <= .5){
			 maxforce = ofMap(d,.5, 0,.15, .55);
	   steer = desired +(vel);
		accl += steer;

	vel += accl; 
	
	pos +=vel;
    accl *= 0;

		}
	}


	  float x = pos.x;
    float y = pos.y; 
	if ( x < 10 ) {x = 10; vel /= 10;}
    if ( x > ofGetWidth()-10) x = ofGetWidth()-10;
	if ( y < 10 ) {y = 10; vel /= 10;} 
    if ( y > ofGetHeight()-10 ) y = ofGetHeight()-10;
    pos.set( x, y );


		
}

//------------------------------------------------------------------
void demoParticle::drawp(){

	ofNoFill ();
	ofSetColor(103, 160, 237);
	ofEllipse (ofGetMouseX(), ofGetMouseY(), 40, 40);
	ofVec2f Xaxix; Xaxix.set(1,0);
	float heading = -vel.angle(ofVec2f(1,0));
	heading = heading - PI/2;
	//float theta = vel.angle(Xaxix)-PI/2;
    ofFill();
	ofSetColor(103, 160, 237);

    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotateZ(heading);
    
	ofSetColor(0);
    ofFill();
	ofSetColor(103, 160, 237);

    ofRect( -14, 0, 28, 14);

    ofSetColor(0);
    ofFill();
	ofSetColor(0, 128, 0);
    ofEllipse( -14, 0, 10, 10 );  // left wheel
    ofEllipse( -14, 14, 10, 10 ); // right wheel 

    // show the sensor/wheel connections
    ofNoFill();
	if (mode == aggressive || mode == fear) ofSetColor(0, 128, 0);
	else ofSetColor(128, 0, 0);
    if (mode == templove|| mode == fear) ofBezier(-7*2, 0,  0, 3*2, 0, 3*2, 7*2, 0);
    else ofBezier(-7*2, 0,  0, 5*2, 0, 5*2, 7*2, 7*2);
    
    
    if (mode == templove || mode == fear) ofBezier(-7*2, 7*2,  0, 4*2, 0, 4*2, 7*2, 7*2);
    else ofBezier(-7*2, 7*2, 0, 2*2, 0, 2*2, 7*2, 0);

	ofSetColor(255, 255, 255);
    ofBezier(7*2+7,5,  7*2, 0, 7*2, 0, 7*2+7, -5);
	ofBezier(7*2+7,5+7*2,  7*2, 7*2, 7*2,7*2,  7*2+7, 7*2 -5);
	path.arc(7, 0,  5, 5, PI/2, PI/2+PI);
    path.arc(7, 7, 5, 5, PI/2, PI/2+PI);  


    ofPopMatrix();
}


