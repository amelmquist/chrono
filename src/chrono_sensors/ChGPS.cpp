// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Asher Elmquist
// =============================================================================
//
//
// =============================================================================


#include "ChGPS.h"

// Constructor for a ChGPS
ChGPS::ChGPS (std::shared_ptr<chrono::ChBody> parent, double updateRate, bool visualize)
: ChSensor(parent,updateRate,visualize){

}
ChGPS::~ChGPS(){

}

// Initialize the ChGPS
// pass in: vertMinAngle, vertMaxAngle, vertSamples, horzMinAngle, horzMaxAngle,horzSamples,minRange,maxRange
void ChGPS::Initialize(chrono::ChCoordsys<> offsetPose, chrono::ChVector<> originGPS){
	m_originGPS = originGPS;
}

void ChGPS::Update(){
//UPDATE THE GPS IF IT HAS BEEN ENOUGH TIME SINCE PREVIOUS UPDATE
	if(this->parent->GetChTime()>=timeLastUpdated + 1.0/updateRate){
		currPos = this->parent->GetPos();
		timeLastUpdated = this->parent->GetChTime();
	}
}

chrono::ChVector<> ChGPS::GetData(){
	return toGPSCoords(currPos);
}

chrono::ChVector<> ChGPS::toGPSCoords(chrono::ChVector<> cart){
	//convert from cartesian to gps coordinates assuming a sphere
	//TODO: something is wrong in this formula, try reversing the haversine formula (bookmarked) - Asher
	double lat = (cart.y() / earthRadius) *180.0 / chrono::CH_C_PI + m_originGPS.y();
	double lon = (cart.x() / (earthRadius*cos(lat*chrono::CH_C_PI/180.0))) *180.0 / chrono::CH_C_PI + m_originGPS.x();
	double alt = cart.z() + m_originGPS.z();

	//sanitize the new gps coordinates
	if(lat < -90.0){
		//NOT A GOOD APPROXIMATION NEAR THE POLES ANYWAY
	}
	else if(lat > 90){
		//NOT A GOOD APPROXIMATION NEAR THE POLES ANYWAY
	}

	if(lon < -180.0){
		lon = lon + 360.0;
	}
	else if(lon > 180.0){
		lon = lon - 360.0;
	}







	return chrono::ChVector<>({lon, lat, alt});
}
