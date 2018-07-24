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


#include "ChRayShape.h"

#include "chrono/physics/ChSystem.h"
#include "chrono/assets/ChTexture.h"
#include "chrono/assets/ChColorAsset.h"




ChRayShape::ChRayShape(std::shared_ptr<chrono::ChBody> parent, bool visualize){
	this->parent = parent;	//save reference to the ChSystem
	this->visualize = visualize;
	//this is set to -1 for now since they have not been used
	this->contactLen = -1;
}

ChRayShape::~ChRayShape(){

}

// update the ray collision
// this checks the ray and sets the appropriate ray length and hit object name
void ChRayShape::Update(bool updateCollision){

	this->globalStartPos = this->parent->GetPos() + this->parent->GetRot().Rotate(relativeStartPos);
	this->globalEndPos = this->parent->GetPos() + this->parent->GetRot().Rotate(relativeEndPos);

	if(updateCollision){
		// see if the ray collides with anything
		this->parent->GetSystem()->GetCollisionSystem()->RayHit(this->globalStartPos, this->globalEndPos, this->rayCollision);
		if(rayCollision.hit){
			//if the ray collides, set the length accordingly
			this->SetLength((rayCollision.abs_hitPoint-this->globalStartPos).Length());
		}
	}
	if(visualize){
		rayEnd->SetPos(globalEndPos);
		rayStart->SetPos(globalStartPos);
	}
}

///This finds the intersection of the ray and the colliding object
void ChRayShape::GetIntersection(double &dist, std::string &entity){
	//see if the ray collides with anything
	this->parent->GetSystem()->GetCollisionSystem()->RayHit(this->globalStartPos, this->globalEndPos, this->rayCollision);
	if(rayCollision.hit){
		dist = (rayCollision.abs_hitPoint-this->globalStartPos).Length();
		entity = rayCollision.hitModel->GetPhysicsItem()->GetNameString();
	}
}

// set the start and end point of the ray
void ChRayShape::SetPoints(const chrono::ChVector<double> &posStart,
		const chrono::ChVector<double> &posEnd){
	//set the global start and end points
	this->relativeStartPos = posStart;
	this->relativeEndPos = posEnd;
	this->globalStartPos = this->parent->GetPos() + this->parent->GetRot().Rotate(posStart);
	this->globalEndPos = this->parent->GetPos() + this->parent->GetRot().Rotate(posEnd);

	if(visualize){
		//insert a small sphere at the end of each ray for debugging purposes
		rayEnd = std::make_shared<chrono::ChBodyEasySphere>(.02, 3000, false, true);
		rayEnd->SetPos(chrono::ChVector<>(this->globalEndPos));
		rayEnd->SetBodyFixed(true);

		this->parent->GetSystem()->Add(rayEnd);

		auto color2 = std::make_shared<chrono::ChColorAsset>();
		color2->SetColor(chrono::ChColor(0.1f, 1.0f, .1f));
		rayEnd->AddAsset(color2);

		rayStart = std::make_shared<chrono::ChBodyEasySphere>(.02, 3000, false, true);
		rayStart->SetPos(chrono::ChVector<>(this->globalStartPos));
		rayStart->SetBodyFixed(true);

		this->parent->GetSystem()->Add(rayStart);

		auto color3 = std::make_shared<chrono::ChColorAsset>();
		color3->SetColor(chrono::ChColor(0.1f, 0.1f, 1.0f));
		rayStart->AddAsset(color3);
	}
}

// set the length of the ray
void ChRayShape::SetLength(double len){
	//set the length to the contact
	this->contactLen = len;

	chrono::ChVector<double> dir = this->relativeEndPos - this->relativeStartPos;
	dir.Normalize();

	// this was in gazebo RayShape or BulletRayShape but causes the end position to be incorrect the next time around
	this->relativeEndPos = dir*len + this->relativeStartPos;
}

// returns the length of the ray
double ChRayShape::GetLength() const{
	//return the length to contact
	return this->contactLen;

}
