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


#include "ChRaySensor.h"

using namespace chrono;

// Constructor for a ChRaySensor
ChRaySensor::ChRaySensor (std::shared_ptr<ChBody> parent, double updateRate, bool visualize)
: ChSensor(parent,updateRate,visualize){

}
ChRaySensor::~ChRaySensor(){
	this->rays.clear();
}

// Initialize the ChRaySensor
void ChRaySensor::Initialize(chrono::ChCoordsys<double> offsetPose,
		int aboutYSamples, int aboutZSamples,
		double aboutYMinAngle, double aboutYMaxAngle,
		double aboutZMinAngle, double aboutZMaxAngle,
		double minRange, double maxRange){

	this->minRange = minRange;
	this->maxRange = maxRange;

	if(aboutZSamples < 1) aboutZSamples = 1;
	if(aboutYSamples < 1) aboutYSamples = 1;

	chrono::ChVector<double> start, end, axis;
	double yawAngle, pitchAngle;
	chrono::ChQuaternion<double> ray;
	double yDiff = aboutYMaxAngle - aboutYMinAngle;
	double pDiff = aboutZMaxAngle - aboutZMinAngle;

	for(int j=0; j< aboutZSamples; ++j){
		for(int i=0; i<aboutYSamples; ++i){

			yawAngle = (aboutYSamples == 1) ? 0 :
					i * yDiff / (aboutYSamples - 1) + aboutYMinAngle;

			pitchAngle = (aboutZSamples == 1) ? 0 :
					j * pDiff / (aboutZSamples - 1) + aboutZMinAngle;

			//Yaw, Roll, Pitch according to ChQuaternion.h
			ray.Q_from_NasaAngles(chrono::ChVector<double>(yawAngle, 0.0, -pitchAngle));

			axis = (offsetPose.rot * ray).Rotate(chrono::ChVector<double>(1.0,0,0));

			start = (axis * minRange) + offsetPose.pos;
			end = (axis * maxRange) + offsetPose.pos;

			this->AddRay(start,end);
		}
	}
}

void ChRaySensor::UpdateRays(){

}

void ChRaySensor::AddRay(const chrono::ChVector<double> &_start,
		const chrono::ChVector<double> &_end){
	std::shared_ptr<ChRayShape> ray = std::make_shared<ChRayShape>(this->parent, visualize);

	ray->SetPoints(_start, _end);
	this->rays.push_back(ray);

}

double ChRaySensor::GetRange(unsigned int _index){
	if(_index >= this->rays.size()){
		return -1;
	}
	//add min range because we measured from min range
	return this->minRange + this->rays[_index]->GetLength();

}

std::vector<double> ChRaySensor::Ranges(){
	std::vector<double> ranges = std::vector<double>();
	for(int i=0; i<this->rays.size(); i++){
		ranges.push_back(this->minRange + rays[i]->GetLength());
	}
	return ranges;
}

void ChRaySensor::Update(){

	double fullRange = this->maxRange - this->minRange;

	bool updateCollisions = false;
	if(this->parent->GetChTime()>=timeLastUpdated + 1.0/updateRate){
		updateCollisions = true;
		timeLastUpdated = this->parent->GetChTime();
		for(unsigned int i = 0; i<this->rays.size(); i++){
			this->rays[i]->SetLength(fullRange);
		}
	}
	std::vector<std::shared_ptr<ChRayShape>>::iterator iter;
	for(iter = this->rays.begin(); iter != this->rays.end(); ++iter){
		(*iter)->Update(updateCollisions);
	}
}
