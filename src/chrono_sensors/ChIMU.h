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


private: chrono::ChCoordsys<double> offsetPose;
	chrono::ChVector<double> currLinAccel;
	chrono::ChQuaternion<double> currAngAccel;
	chrono::ChQuaternion<double> currOrientation;

};

#endif
