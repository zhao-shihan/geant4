//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//

#ifndef G4PSCylinderSurfaceFlux3D_h
#define G4PSCylinderSurfaceFlux3D_h 1

#include "G4PSCylinderSurfaceFlux.hh"
///////////////////////////////////////////////////////////////////////////////
// (Description)
//   This is a primitive scorer class for scoring Surface Flux.
//  This Flux version assumes only for G4Tubs shape, and the surface
//  is defined at the Rmin plane of the box.
//   The current is given in the unit of area.
//    e.g.  (Number of tracks)/mm2.
//
// Surface is defined at the -Z surface.
// Direction                  Rmin Rmax
//   0  IN || OUT            ->|<-  |      fFlux_InOut
//   1  IN                   ->|    |      fFlux_In
//   2  OUT                    |<-  |      fFlux_Out
//
//
// Created: 2008-08-14  Tsukasa ASO
// 2010-07-22   Introduce Unit specification.
///////////////////////////////////////////////////////////////////////////////

class G4PSCylinderSurfaceFlux3D : public G4PSCylinderSurfaceFlux
{
 public:
  G4PSCylinderSurfaceFlux3D(const G4String& name, G4int direction, G4int ni = 1,
                            G4int nj = 1, G4int nk = 1, G4int di = 2,
                            G4int dj = 1, G4int dk = 0);
  G4PSCylinderSurfaceFlux3D(const G4String& name, G4int direction,
                            const G4String& unit, G4int ni = 1, G4int nj = 1,
                            G4int nk = 1, G4int di = 2, G4int dj = 1,
                            G4int dk = 0);
  ~G4PSCylinderSurfaceFlux3D() override = default;

 protected: 
  G4int GetIndex(G4Step*) override;

 private:
  G4int fDepthi, fDepthj, fDepthk;
};
#endif
