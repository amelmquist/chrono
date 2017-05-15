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

/**
 * This is based on ODEMultiRayShape.hh and MultiRayShape.hh
 *
 */
#ifndef CHIMU_H
#define CHIMU_H

#include "ChSensor.h"

#include "chrono/physics/ChSystem.h"
#include "chrono/core/ChCoordsys.h"
#include "chrono/core/ChVector.h"
#include "chrono/physics/ChBody.h"

#include <vector>
#include <math.h>
#include <stdio.h>



class ChIMU : public ChSensor{
	// \brief Constructor.
	/// \param[in] _parent Parent collision shape.
public:
	/// Constructor
	ChIMU(std::shared_ptr<chrono::ChBody> parent, double updateRate, bool visualize);

	/// Destructor
	~ChIMU();

	///Initialize the ChRaySensor
	void Initialize(chrono::ChCoordsys<double> offsetPose);
			/***TEMPORART PARENT OBJECT***/
			//,chrono::ChCoordsys<double> parentPose);

	void Update();
	chrono::ChVector<double> GetLinearAcc();
	chrono::ChQuaternion<double> GetAngularAcc();
	chrono::ChQuaternion<double> GetOrientation();


	/// Add a ray to the collision

private: chrono::ChCoordsys<double> offsetPose;
	chrono::ChVector<double> currLinAccel;
	chrono::ChQuaternion<double> currAngAccel;
	chrono::ChQuaternion<double> currOrientation;

};

#endif
