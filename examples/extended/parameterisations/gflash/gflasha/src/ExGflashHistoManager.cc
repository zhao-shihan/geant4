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
/// \file ExGflashHistoManager.cc
/// \brief Implementation of the ExGflasHistoManager class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExGflashHistoManager.hh"

#include "ExGflashDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExGflashHistoManager::ExGflashHistoManager(ExGflashDetectorConstruction* myDet)
  : fFileName("gflash01"), fDet(myDet)
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExGflashHistoManager::~ExGflashHistoManager() = default;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExGflashHistoManager::Book()
{
  G4AnalysisManager* fAnalysisManager = G4AnalysisManager::Instance();
  fAnalysisManager->SetDefaultFileType("root");
  fAnalysisManager->SetFileName(fFileName);
  fAnalysisManager->SetVerboseLevel(1);
  fAnalysisManager->SetActivation(true);  // enable inactivation of histograms
  //
  // Creating histograms
  //
  G4int nLbin = fDet->GetnLtot();
  G4int nRbin = fDet->GetnRtot();
  G4double dLradl = fDet->GetdLradl();
  G4double dRradl = fDet->GetdRradl();
  fVerbose = fDet->GetVerbose();

  fAnalysisManager->CreateH1("h0", "total energy deposit(percent of Einc)", 100, 85., 105.);

  fAnalysisManager->CreateH1("h1", "The number of Hits per event", 200, 0., 4.0e5);

  fAnalysisManager->CreateH1("h2", "The energy of Hit (in MeV)", 200, 0., 10.);

  fAnalysisManager->CreateP1("p0", "longit energy profile (% of E inc)", nLbin, 0., nLbin * dLradl,
                             0., 2000.);

  fAnalysisManager->CreateP1("p1", "radial energy profile (% of E inc)", nRbin, 0., nRbin * dRradl,
                             0., 2000.);

  fAnalysisManager->CreateP1("p2", "Comul longit energy profile (% of E inc)", nLbin, 0.,
                             nLbin * dLradl, 0., 20000.);

  fAnalysisManager->CreateP1("p3", "Cuml radial energy profile (% of E inc)", nRbin, 0.,
                             nRbin * dRradl, 0., 20000.);

  if (fVerbose > 1) G4cout << "\n----> Histogram file " << fFileName << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExGflashHistoManager::SetBinning()
{
  G4int nLbin = fDet->GetnLtot();
  G4int nRbin = fDet->GetnRtot();
  G4double dLradl = fDet->GetdLradl();
  G4double dRradl = fDet->GetdRradl();

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Redifine profiles
  analysisManager->SetP1(0, nLbin, 0., nLbin * dLradl, 0., 2000.);
  analysisManager->SetP1(1, nRbin, 0., nRbin * dRradl, 0., 2000.);
  analysisManager->SetP1(2, nLbin, 0., nLbin * dLradl, 0., 2000.);
  analysisManager->SetP1(3, nRbin, 0., nRbin * dRradl, 0., 2000.);
}
