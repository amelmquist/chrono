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



#include "ChIMU.h"

// Constructor for a ChIMU
ChIMU::ChIMU (std::shared_ptr<chrono::ChBody> parent, double updateRate, bool visualize)
	: ChSensor(parent,updateRate,visualize){


}
ChIMU::~ChIMU(){

}

// Initialize the ChIMU
// pass in: vertMinAngle, vertMaxAngle, vertSamples, horzMinAngle, horzMaxAngle,horzSamples,minRange,maxRange
void ChIMU::Initialize(chrono::ChCoordsys<double> offsetPose){


}

void ChIMU::Update(){
	//UPDATE THE IMU IF IT HAS BEEN ENOUGH TIME SINCE PREVIOUS UPDATE
	if(m_parent->GetChTime()>=m_timeLastUpdated + 1.0/m_updateRate){
		currLinAccel = m_parent->GetPos_dtdt();
		currAngAccel = m_parent->GetWacc_loc();
		currOrientation = m_parent->GetRot().Q_to_Euler123();
		m_timeLastUpdated = m_parent->GetChTime();
		AddNoise();
	}
}
chrono::ChVector<double> ChIMU::GetLinearAcc(){
	return currLinAccel;
}
chrono::ChVector<double> ChIMU::GetAngularAcc(){
	return currAngAccel;
}
chrono::ChVector<double> ChIMU::GetOrientation(){
	return currOrientation;
}

void ChIMU::AddNoise(){
	switch(m_noiseType){
		case ChSensor::NONE:
			//std::cout<<"NO NOISE MODEL TO ADD\n";
			break;
		case ChSensor::GAUSSIAN:
			//std::cout<<"GAUSSIAN NOISE MODEL TO ADD\n";
			break;
		default:
			//std::cout<<"INVALID NOISE MODEL TYPE\n";
			break;
	}
}
