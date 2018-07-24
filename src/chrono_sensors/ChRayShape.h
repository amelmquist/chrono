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



#ifndef CHRAYSHAPE_H
#define CHRAYSHAPE_H

#include "chrono/physics/ChSystem.h"
#include "chrono/core/ChCoordsys.h"
#include "chrono/core/ChVector.h"
#include "chrono/physics/ChBodyEasy.h"
#include "chrono/physics/ChBody.h"


#include <vector>
#include <math.h>
#include <stdio.h>

class ChRayShape
{
public:
	ChRayShape(std::shared_ptr<chrono::ChBody> parent, bool visualize);
	~ChRayShape();

	//update the ray collision
	void Update(bool updateCollision);

	//get the nearest intersection
	void GetIntersection(double &dist, std::string &entity);

	//set the ray based on starting and ending points relative to the body
	void SetPoints(const chrono::ChVector<double> &posStart,
		const chrono::ChVector<double> &posEnd);

	void SetLength(double len);

	double GetLength() const;

private:
	std::shared_ptr<chrono::ChBody> parent;
	bool visualize;

	double contactLen;

	//start position of the ray in global coordsys
	chrono::ChVector<double> globalStartPos;

	//end position of the ray in global coordsys
	chrono::ChVector<double> globalEndPos;

	chrono::ChVector<double> relativeStartPos;

	//end position of the ray in global coordsys
	chrono::ChVector<double> relativeEndPos;
	chrono::collision::ChCollisionSystem::ChRayhitResult rayCollision;

	std::shared_ptr<chrono::ChBodyEasySphere> rayEnd;
	std::shared_ptr<chrono::ChBodyEasySphere> rayStart;

};

#endif
