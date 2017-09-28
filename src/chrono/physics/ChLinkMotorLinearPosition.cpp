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
// Authors: Alessandro Tasora
// =============================================================================

#include "chrono/physics/ChLinkMotorLinearPosition.h"

namespace chrono {


// Register into the object factory, to enable run-time dynamic creation and persistence
CH_FACTORY_REGISTER(ChLinkMotorLinearPosition)


ChLinkMotorLinearPosition::ChLinkMotorLinearPosition() {
    
    // default motion function : a ramp
    this->f_pos = std::make_shared<ChFunction_Ramp>(
        0.0,   // default y(0)
        1.0    // default dy/dx , i.e.   1 [m/s]
        );
    
    pos_offset = 0;
}

ChLinkMotorLinearPosition::ChLinkMotorLinearPosition(const ChLinkMotorLinearPosition& other) : ChLinkMotorLinear(other) {
   this->f_pos = other.f_pos;
   this->pos_offset = other.pos_offset;
}

ChLinkMotorLinearPosition::~ChLinkMotorLinearPosition() {
    
}


void ChLinkMotorLinearPosition::Update(double mytime, bool update_assets) {
    
    // Inherit parent class:
    ChLinkMotorLinear::Update(mytime, update_assets);

    this->f_pos->Update(mytime); // call callbacks if any

    // Add the time-dependent term in residual C as 
    //   C = d_error - d_setpoint - d_offset
    // with d_error = x_pos_A- x_pos_B, and d_setpoint = x(t)
    C->ElementN(0) = this->mpos  - this->f_pos->Get_y(this->GetChTime()) - this->pos_offset;
}

void ChLinkMotorLinearPosition::IntLoadConstraint_Ct(const unsigned int off_L, ChVectorDynamic<>& Qc, const double c) {

    double mCt = - this->f_pos->Get_y_dx(this->GetChTime());
    if (mask->Constr_N(0).IsActive()) {
        Qc(off_L + 0) += c * mCt;
    }
}


void ChLinkMotorLinearPosition::ConstraintsBiLoad_Ct(double factor) {
    if (!this->IsActive())
        return;

    double mCt = - this->f_pos->Get_y_dx(this->GetChTime());
    if (mask->Constr_N(0).IsActive()) {
            mask->Constr_N(0).Set_b_i(mask->Constr_N(0).Get_b_i() + factor * mCt);
    }
}



void ChLinkMotorLinearPosition::ArchiveOUT(ChArchiveOut& marchive) {
    // version number
    marchive.VersionWrite<ChLinkMotorLinearPosition>();

    // serialize parent class
    ChLinkMotorLinear::ArchiveOUT(marchive);

    // serialize all member data:
    marchive << CHNVP(f_pos);
    marchive << CHNVP(pos_offset);
}

/// Method to allow de serialization of transient data from archives.
void ChLinkMotorLinearPosition::ArchiveIN(ChArchiveIn& marchive) {
    // version number
    int version = marchive.VersionRead<ChLinkMotorLinearPosition>();

    // deserialize parent class
    ChLinkMotorLinear::ArchiveIN(marchive);

    // deserialize all member data:
    marchive >> CHNVP(f_pos);
    marchive >> CHNVP(pos_offset);
}






}  // end namespace chrono
