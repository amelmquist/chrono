//
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2013 Project Chrono
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file at the top level of the distribution
// and at http://projectchrono.org/license-chrono.txt.
//

// A very simple example that can be used as template project for
// a Chrono::Engine simulator with 3D view.



#include "chrono/physics/ChSystemNSC.h"
#include "chrono/physics/ChBodyEasy.h"
#include "chrono/physics/ChLinkMate.h"
#include "chrono/assets/ChTexture.h"
#include "chrono/assets/ChColorAsset.h"
#include "chrono_irrlicht/ChIrrApp.h"

//#include "ChRayShape.h"

#include "chrono_sensors/ChGPS.h"
#include "chrono_sensors/ChIMU.h"
#include "chrono_sensors/ChRaySensor.h"

// Use the namespace of Chrono

using namespace chrono;
using namespace chrono::irrlicht;

// Use the main namespaces of Irrlicht

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

int main(int argc, char* argv[]) {
	// Set path to Chrono data directory
	/*SetChronoDataPath(CHRONO_DATA_DIR);*/

	// Create a Chrono physical system
	ChSystemNSC mphysicalSystem;
	//auto mphysicalSystem = std::make_shared<ChSystem>();

	// Create the Irrlicht visualization (open the Irrlicht device,
	// bind a simple user interface, etc. etc.)
	ChIrrApp application(&mphysicalSystem, L"A simple project template", core::dimension2d<u32>(800, 600),
			false);  // screen dimensions

	// Easy shortcuts to add camera, lights, logo and sky in Irrlicht scene:
	application.AddTypicalLogo();
	application.AddTypicalSky();
	application.AddTypicalLights();
	application.AddTypicalCamera(core::vector3df(3, 3, 5),
			core::vector3df(0, .5, 0));  // to change the position of camera
	// application.AddLightWithShadow(vector3df(1,25,-5), vector3df(0,0,0), 35, 0.2,35, 55, 512, video::SColorf(1,1,1));

	//======================================================================
	// 1-Create a floor that is fixed (that is used also to represent the absolute reference)

	auto floorBody = std::make_shared<ChBodyEasyBox>(100, 1, 100,  // x, y, z dimensions
			3000,       // density
			true,      // enable contact geometry
			true        // enable visualization geometry
	);
	floorBody->SetPos(ChVector<>(0, -1, 0));
	floorBody->SetBodyFixed(true);

	mphysicalSystem.Add(floorBody);

	// 2-Create a Box on the ground

	auto box = std::make_shared<ChBodyEasyBox>(2, 3, 1,  // x, y, z dimensions
			3000,         // density
			true,        // no contact geometry
			true          // enable visualization geometry
	);
	box->SetNameString("THIS BOX");
	box->SetPos(ChVector<>(2, 0, 0));
	box->SetBodyFixed(true);

	//box->SetPos_dt(ChVector<>(0, 0, 0));

	mphysicalSystem.Add(box);

	// Optionally, attach a RGB color asset to the floor, for better visualization
	auto color = std::make_shared<ChColorAsset>();
	color->SetColor(ChColor(0.4f, 0.2f, 0.2f));
	floorBody->AddAsset(color);

	// Optionally, attach a texture to the pendulum, for better visualization
	auto texture = std::make_shared<ChTexture>();
	texture->SetTextureFilename(GetChronoDataFile("cubetexture_bluwhite.png"));  // texture in ../data
	box->AddAsset(texture);



	//===============Test out MultiRayShape linking===============
	//auto rayshape = std::make_shared<ChRaySensor>();
	//rayshape->Init();
	//rayshape->~ChRaySensor();ChRaySensor ray = new ChRaySensor();
	//std::shared_ptr<ChRaySensor> rays = std::make_shared<ChRaySensor>(&mphysicalSystem);

	//ChRaySensor *rays = new ChRaySensor(mphysicalSystem);
	//	auto multiRayBox = std::make_shared<ChBodyEasyBox>(.1, .1, .1,  // x, y, z dimensions
	//			3000,         // density
	//			false,        // contact?
	//			true          // visual?
	//	);
	//	multiRayBox->SetNameString("THIS BOX");
	//	multiRayBox->SetPos(ChVector<>(2, 1, 0));
	//	multiRayBox->SetRot(Q_from_AngY(3.14)*Q_from_AngX(.707));
	//	multiRayBox->SetBodyFixed(true);
	//	//box->SetPos_dt(ChVector<>(0, 0, 0));
	//
	//	mphysicalSystem.Add(multiRayBox);
	//	auto colorMultiRayBox = std::make_shared<ChColorAsset>();
	//	colorMultiRayBox->SetColor(ChColor(0.4f, 0.2f, 0.2f));
	//	multiRayBox->AddAsset(colorMultiRayBox);

	auto lidarBox = std::make_shared<ChBodyEasyBox>(.1, .1, .1,  // x, y, z dimensions
			3000,         // density
			true,        // no contact geometry
			true          // enable visualization geometry
	);
	lidarBox->SetNameString("THIS BOX");
	lidarBox->SetPos(ChVector<>(0, 1, 0));
	lidarBox->SetRot(Q_from_AngY(3.14/2.0));
	lidarBox->SetBodyFixed(true);

	//box->SetPos_dt(ChVector<>(0, 0, 0));

	mphysicalSystem.Add(lidarBox);

	// Optionally, attach a texture to the pendulum, for better visualization
	auto texture1 = std::make_shared<ChTexture>();
	texture1->SetTextureFilename(GetChronoDataFile("cubetexture_bluwhite.png"));  // texture in ../data
	lidarBox->AddAsset(texture1);
	//lidar->SetBodyFixed(true);
	//lidar->SetPos({2,1,0});
	//mphysicalSystem.Add(lidar);


	std::shared_ptr<ChRaySensor> lidarSensor = std::make_shared<ChRaySensor>(lidarBox, 60, true);
	//lidarSensor->Initialize(1, 100, 0, 0, -3.14, 3.08, .01, 25); //old version of init
	lidarSensor->Initialize(chrono::ChCoordsys<double>(
			chrono::ChVector<double>({0,0,0}),	//offset x,y,z
			chrono::ChQuaternion<double>(Q_from_NasaAngles({0,0,0}))), //offset yaw,roll,pitch
			100, 1, -3.14, 3.14, -3.14, 3.14, .2, 3);
	//offset pose, z samples, y samples, z min angle, z max angle, min distance, max distance

	auto gpsBox = std::make_shared<ChBodyEasyBox>(.1, .1, .1,  // x, y, z dimensions
			3000,         // density
			true,        // no contact geometry
			true          // enable visualization geometry
	);
	gpsBox->SetNameString("GPS BOX");
	gpsBox->SetPos(ChVector<>(0, 2, 0));
	gpsBox->SetRot(Q_from_AngY(3.14/2.0));
	gpsBox->SetBodyFixed(true);

	//box->SetPos_dt(ChVector<>(0, 0, 0));

	mphysicalSystem.Add(gpsBox);

	gpsBox->AddAsset(texture1);

	std::shared_ptr<ChGPS> gpsSensor = std::make_shared<ChGPS>(gpsBox, 1, true);
	gpsSensor->Initialize(chrono::ChCoordsys<double>(
				chrono::ChVector<double>({0,0,0}),	//offset x,y,z
				chrono::ChQuaternion<double>(Q_from_NasaAngles({0,0,0})))); //offset yaw,roll,pitch









	//======================================================================

	// Use this function for adding a ChIrrNodeAsset to all items
	// Otherwise use application.AssetBind(myitem); on a per-item basis.
	application.AssetBindAll();

	// Use this function for 'converting' assets into Irrlicht meshes
	application.AssetUpdateAll();

	// Adjust some settings:
	application.SetTimestep(0.005);
	application.SetTryRealtime(false);

	//
	// THE SOFT-REAL-TIME CYCLE
	//

	while (application.GetDevice()->run()) {
		application.BeginScene();

		application.DrawAll();

		// This performs the integration timestep!
		application.DoStep();
		//rays.Update();

		//std::cout<<"Distance: "<<(box->GetPos()-ChVector<double>(2,1,0)).Length() - 1<<std::endl;
		//lidarBox->SetRot(lidarBox->GetRot()*Q_from_AngY(.01));
		//gpsBox->SetPos(gpsBox->GetPos() + chrono::ChVector<>(0.3,0.2,0.1));

		//lidar->SetRot(lidar->GetRot()*Q_from_AngX(.01));

		//lidar->SetRot(lidar->GetRot()*Q_from_AngZ(.01));
		//lidar->SetPos(lidar->GetPos() + ChVector<double>{.001,0,0.0});

		lidarSensor->Update();
		gpsSensor->Update();
		//imuSensor->Update();

		//std::cout<<gpsSensor->GetData().x<<", "<<gpsSensor->GetData().y<<", "<<gpsSensor->GetData().z<<std::endl;
		//std::cout<<mphysicalSystem.GetChTime()<<std::endl;

		application.EndScene();
	}

	return 0;
}
