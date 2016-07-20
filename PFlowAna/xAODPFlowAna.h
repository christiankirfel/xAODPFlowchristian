#ifndef PFlowAna_xAODPFlowAna_H
#define PFlowAna_xAODPFlowAna_H

#include <EventLoop/Algorithm.h>

#include "xAODRootAccess/TEvent.h"
#include "JetSelectorTools/JetCleaningTool.h"
#include "xAODJet/JetContainer.h"
#include "JetCalibTools/JetCalibrationTool.h"


//Jet Energy Resolution Tool
#include "JetResolution/JERTool.h"

#include "JetResolution/JERSmearingTool.h"

#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertexContainer.h"
#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODCaloEvent/CaloCluster.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODPFlow/PFOContainer.h"
#include "xAODPFlow/PFO.h"
#include "xAODCalCellInfo/CalCellInfo.h"
#include "xAODCalCellInfo/CalCellInfoContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "MuonMomentumCorrections/MuonCalibrationAndSmearingToll.h"
//added by ckirfel
#include <TH1.h>




class xAODPFlowAna : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
 public:
  //added by ckirfel
  TH1 *h_jetPt; //!
  TH1 *h_jetEta; //!
  TH1 *h_jetPhi; //!
  TH1 *h_jetM; //!
  TH1 *h_jetE; //!
  TH1 *h_jetEMF; //!
  TH1 *h_jetHCF; //!

  TH1 *h_jetPtdirty; //!
  TH1 *h_jetEtadirty; //!
  TH1 *h_jetPhidirty; //!
  TH1 *h_jetMdirty; //!
  TH1 *h_jetEdirty; //!

  TH1 *h_jetPtcorr; //!
  TH1 *h_jetEtacorr; //!
  TH1 *h_jetPhicorr; //!
  TH1 *h_jetMcorr; //!
  TH1 *h_jetEcorr; //!

  TH2 *h_jetR; //!
  
  TH2 *h_dirtyptemf; //!
  TH2 *h_ptemf; //!

  // jet cleaning also by christian
  JetCleaningTool *m_jetCleaning; //! 
  // JET RESOLUTION
   JERTool *m_JERTool; //!
   // JET Smearing
   JERSmearingTool *m_JERSmearingTool; //!
   //Jet Calibration Tool
   JetCalibrationTool *m_jetCalibration; //!
   //Tool for Muon-Calibration
   CP::MuonCalibrationAndSmearingTool *m_muonCalibrationAndSmearingTool; //! 
  
  
  
  
  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
  
  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();
  xAODPFlowAna ();
 
  
 private:
  
  float GEV; //!
  float PrintDebug;//!
  
  xAOD::TEvent *m_event;//!
  int m_eventCounter; //!
 

  // Tree *myTree; //!
  // TH1 *myHist; //!

  
  //Bad jet scan
  void BadJetsScan(const xAOD::Jet& jet);
  
  // JetMatching
  void MatchJetCollections(const xAOD::JetContainer*, const xAOD::JetContainer* );
  bool HasPFlowJetMatched(const xAOD::Jet& jet); //return a true is has been matched
  int WhichPFlowJetMatched(const xAOD::Jet& jet); //return the index of the PFlowJet matched
  
public:

  // this is needed to distribute the algorithm to the workers
  ClassDef(xAODPFlowAna, 1);
};

#endif
