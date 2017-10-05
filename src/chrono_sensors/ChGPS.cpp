//
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2013 Project Chrono
// All rights reserved.
//
//Author: Asher Elmquist
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file at the top level of the distribution
// and at http://projectchrono.org/license-chrono.txt.
//

#include "ChGPS.h"

#include <vector>
#include <cmath>
#include <stdio.h>
#include <iostream>

#include "chrono/physics/ChSystem.h"
#include "chrono/physics/ChBodyEasy.h"
#include "chrono/assets/ChTexture.h"
#include "chrono/assets/ChColorAsset.h"
#include "chrono/physics/ChLinkLock.h"


/// Constructor for a ChGPS
ChGPS::ChGPS (std::shared_ptr<chrono::ChBody> parent, double updateRate, bool visualize)
: ChSensor(parent,updateRate,visualize){


}
ChGPS::~ChGPS(){

}

/// Initialize the ChGPS
/// pass in: vertMinAngle, vertMaxAngle, vertSamples, horzMinAngle, horzMaxAngle,horzSamples,minRange,maxRange
void ChGPS::Initialize(chrono::ChCoordsys<double> offsetPose){

}

void ChGPS::Update(){
//UPDATE THE GPS IF IT HAS BEEN ENOUGH TIME SINCE PREVIOUS UPDATE
	if(this->parent->GetChTime()>=timeLastUpdated + 1.0/updateRate){
		currPos = this->parent->GetPos();
		timeLastUpdated = this->parent->GetChTime();
	}
}

chrono::ChVector<double> ChGPS::GetData(){

	return currPos;
}
