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


#ifndef CHRAYSENSOR_H
#define CHRAYSENSOR_H

#include "ChRayShape.h"
#include "ChSensor.h"

class ChRaySensor : public ChSensor{
public:
	// Constructor
	ChRaySensor(std::shared_ptr<chrono::ChBody> parent, double updateRate, bool visualize);

	// Destructor
	~ChRaySensor();

	//Initialize the ChRaySensor
	void Initialize(chrono::ChCoordsys<double> offsetPose,
			int horzSamples, int vertSamples,
			double horzMinAngle, double horzMaxAngle,
			double vertMinAngle, double vertMaxAngle,
			double minRange, double maxRange);

	// Update the rays
	void UpdateRays();

	double GetRange(unsigned int _index);
	std::vector<double> Ranges();

	void Update();

private:
	void AddRay(const chrono::ChVector<double> &start, const chrono::ChVector<double> &end);

	std::vector<std::shared_ptr<ChRayShape>> rays;

	chrono::ChCoordsys<double> offsetPose;

	double minRange = -1;
	double maxRange = -1;
};

#endif
