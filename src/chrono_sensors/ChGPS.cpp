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

//************************************************************************
//NOTICE: this file is modified from it's original source. Original source
//		  is based on work done by Open Source Robotics Foundation
//************************************************************************

/*
 * Copyright (C) 2012-2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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
	//save a reference to the ChSystem
	//	this->parent = parent;
	//	this->visualize = visualize;

	//	this->SetDensity(.1);
	//	this->SetMass(.1);
	//	this->SetInertiaXX(ChVector<>(.1,.1,.1));
	//	auto vshape = std::make_shared<ChBoxShape>();
	//	vshape->GetBoxGeometry().SetLengths(ChVector<>(.05, .05, .05));
	//	this->AddAsset(vshape);

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
