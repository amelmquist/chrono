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


#ifndef CHIMU_H
#define CHIMU_H

#include "ChSensor.h"


class ChIMU : public ChSensor{
public:
	// Constructor
	ChIMU(std::shared_ptr<chrono::ChBody> parent, double updateRate, bool visualize);

	// Destructor
	~ChIMU();

	//Initialize the ChRaySensor
	void Initialize(chrono::ChCoordsys<double> offsetPose);

	void Update();
	chrono::ChVector<double> GetLinearAcc();
	chrono::ChVector<double> GetAngularAcc();
	chrono::ChVector<double> GetOrientation();


private: chrono::ChCoordsys<double> offsetPose;
	chrono::ChVector<double> currLinAccel;
	chrono::ChVector<double> currAngAccel;
	chrono::ChVector<double> currOrientation;
	void AddNoise();

};

#endif
