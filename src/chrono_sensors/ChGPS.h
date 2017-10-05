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


#ifndef CHGPS_H
#define CHGPS_H

#include "ChSensor.h"

#include "chrono/physics/ChSystem.h"
#include "chrono/core/ChCoordsys.h"
#include "chrono/core/ChVector.h"
#include "chrono/physics/ChBody.h"

#include <vector>
#include <math.h>
#include <stdio.h>



class ChGPS : public ChSensor{
	// \brief Constructor.
	/// \param[in] _parent Parent collision shape.
public:
	/// Constructor
	ChGPS(std::shared_ptr<chrono::ChBody> parent, double updateRate, bool visualize);

	/// Destructor
	~ChGPS();

	///Initialize the ChGPS - Simulation assumed to be x east-west, y north-south, z normal to surface
	void Initialize(chrono::ChCoordsys<> offsetPose, chrono::ChVector<> originGPS);
			/***TEMPORART PARENT OBJECT***/
			//,chrono::ChCoordsys<double> parentPose);

	/// Update the rays
	void Update();
	chrono::ChVector<double> GetData();
private:
	chrono::ChVector<> toGPSCoords(chrono::ChVector<> cart);
	chrono::ChVector<> currPos;
	chrono::ChVector<> m_originGPS;
	//const double earthRadius = 6371000.6;	//using the authalic radius of the earth
	const double earthRadius = 6371000.0;	//using the authalic radius of the earth
};

#endif
