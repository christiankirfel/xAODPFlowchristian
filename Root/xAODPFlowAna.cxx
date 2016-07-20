// ASG status code check
#include <AsgTools/MessageCheck.h>

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"

#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <PFlowAna/xAODPFlowAnaEDM.h>
#include <PFlowAna/xAODPFlowAna.h>
#include <PFlowAna/PrintInfo.h>

#include <iostream>
#include <vector>
#include <utility> // The pair template is defined in the standard header <utility>
#include <algorithm> //min_element

//for jet cleaning ?
#include <TSystem.h> // used to define JERTool calibration path (you may already have this from the GRL part) ?????????


// this is needed to distribute the algorithm to the workers
ClassImp(xAODPFlowAna)



xAODPFlowAna :: xAODPFlowAna ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode xAODPFlowAna :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  //In order to tell EventLoop that we want to use the xAODRootAccess we initialize the algorithm to use the xAODRootAccess package
  job.useXAOD ();

  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  ANA_CHECK(xAOD::Init());

    
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode xAODPFlowAna :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.  

  h_jetPtdirty = new TH1F("h_jetPtdirty", "h_jetPtdirty", 25,0, 180);//versuch
  h_jetEtadirty = new TH1F("h_jetEtadirty", "h_jetEtadirty", 50,-5, 5);
  h_jetPhidirty = new TH1F("h_jetPhidirty", "h_jetPhidirty", 40, -4, 4);
  h_jetMdirty = new TH1F("h_jetMdirty", "h_jetMdirty",50, 0, 45000);
  h_jetEdirty = new TH1F("h_jetEdirty", "h_jetEdirty",25,0,180);

  wk()->addOutput (h_jetMdirty);
  wk()->addOutput (h_jetPhidirty);
  wk()->addOutput (h_jetPtdirty);
  wk()->addOutput (h_jetEtadirty);
  wk()->addOutput (h_jetEdirty);

  h_jetPt = new TH1F("h_jetPt", "h_jetPt", 25,0, 180);//versuch
  h_jetEta = new TH1F("h_jetEta", "h_jetEta", 50,-5, 5);
  h_jetPhi = new TH1F("h_jetPhi", "h_jetPhi", 40, -4, 4);
  h_jetM = new TH1F("h_jetM", "h_jetM",50, 0, 45000);
  h_jetE = new TH1F("h_jetE", "h_jetE",25,0,180);
  h_jetEMF = new TH1F("h_jetEMF", "h_jetEMF", 50, 0,1);
  h_jetHCF = new TH1F("h_jetHCF", "h_jetHCF", 50, 0, 1);

  wk()->addOutput (h_jetM);
  wk()->addOutput (h_jetPhi);
  wk()->addOutput (h_jetPt);
  wk()->addOutput (h_jetEta);
  wk()->addOutput (h_jetE);
  wk()->addOutput (h_jetEMF);
  wk()->addOutput (h_jetHCF);
  // Histograms after correction for checking the effects
  
  h_jetPtcorr = new TH1F("h_jetPtcorr", "h_jetPtcorr", 25,0, 400);//versuch
  h_jetEtacorr = new TH1F("h_jetEtacorr", "h_jetEtacorr", 50,-5, 5);
  h_jetPhicorr = new TH1F("h_jetPhicorr", "h_jetPhicorr", 40, -4, 4);
  h_jetMcorr = new TH1F("h_jetMcorr", "h_jetMcorr",50, 0, 45000);
  h_jetEcorr = new TH1F("h_jetEcorr", "h_jetEcorr",25, 0, 400);

  wk()->addOutput (h_jetMcorr);
  wk()->addOutput (h_jetPhicorr);
  wk()->addOutput (h_jetPtcorr);
  wk()->addOutput (h_jetEtacorr);
  wk()->addOutput (h_jetEcorr);

  h_ptemf = new TH2F("h_ptemf", "h_ptemf",50,0,1,25,0,200);
  h_dirtyptemf = new TH2F("h_dirtyptemf", "h_dirtyptemf",50,0,1,25,0,200);

  wk()->addOutput (h_ptemf);
  wk()->addOutput (h_dirtyptemf);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode xAODPFlowAna :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
 
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode xAODPFlowAna :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode xAODPFlowAna :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.
 
  //Called once, before the first event is executed 

  ANA_CHECK_SET_TYPE (EL::StatusCode);

  m_event = wk()->xaodEvent();
  Info("initialize()", "Number of events = %lli", m_event->getEntries() );
  
  m_eventCounter = 0; //Count number of events
  PrintDebug = false; //Printing message criteria
  
  GEV = 1000.; //Units
  
  //Initialize and configure the jet cleaning tool
  m_jetCleaning = new JetCleaningTool("JetCleaning");
  m_jetCleaning->msg().setLevel( MSG::DEBUG ); 
  ANA_CHECK(m_jetCleaning->setProperty( "CutLevel", "LooseBad"));
  ANA_CHECK(m_jetCleaning->setProperty("DoUgly", false));
  ANA_CHECK(m_jetCleaning->initialize());

  
  //Initialize the Jet Energy Resolution Tool
  //this is probably where the miskate is to e found
  //i gues the declaration is wrong
  //see also the declaration in the header
  m_JERTool = new JERTool("JERTool");
  ANA_CHECK(m_JERTool->setProperty("PlotFileName", "JetResolution/Prerec2015_xCalib_2012JER_ReducedTo9NP_Plots_v2.root") );
  ANA_CHECK(m_JERTool->setProperty("CollectionName", "AntiKt4EMTopoJets") );
  ANA_CHECK(m_JERTool->initialize());

  //Initialize the Smearing Tool
  /*
  m_JERSmearingTool = new  smearTool("JERSmearingTool");
  //smearTool.msg().setLevel(MSG::DEBUG);
  ToolHandle<IJERTool> jerHandle(JERTool.name());//i have no idea what this is for	   
  ANA_CHECK(m_JERSmearingTool->setProperty("JERTool", jerHandle) );
  ANA_CHECK(m_JERSmearingTool->setProperty("ApplyNominalSmearing", false) );
  ANA_CHECK(m_JERSmearingTool->setProperty("isMC", true) );
  ANA_CHECK(m_JERSmearingTool->setProperty("SystematicMode", "Full") );
  ANA_CHECK(m_JERSmearingTool->initialize());
  */

  //Initialize the JES Tool

const std::string name = "xAODPFlowAna"; //string describing the current thread, for logging
  TString jetAlgo =	"AntiKt4EMTopo" ;  //String describing your jet collection, for example AntiKt4EMTopo or AntiKt4LCTopo (see below)
  TString config ="JES_MC15cRecommendation_May2016.config" ; //Path to global config used to initialize the tool (see below)
  TString calibSeq ="JetArea_Residual_Origin_EtaJES_GSC" ; //String describing the calibration sequence to apply (see below)
  bool isData = false; //bool describing if the events are data or from simulation
  
  m_jetCalibration = new JetCalibrationTool(name);
  ANA_CHECK(m_jetCalibration->setProperty("JetCollection",jetAlgo.Data()));
  ANA_CHECK(m_jetCalibration->setProperty("ConfigFile",config.Data()));
  ANA_CHECK(m_jetCalibration->setProperty("CalibSequence",calibSeq.Data()));
  ANA_CHECK(m_jetCalibration->setProperty("IsData",isData));
  
  // Initialize the tool
  ANA_CHECK(m_jetCalibration->initializeTool(name));

 return EL::StatusCode::SUCCESS;
}



EL::StatusCode xAODPFlowAna :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  
  //called once, before the first event is executed 
  ANA_CHECK_SET_TYPE (EL::StatusCode);
    
  if( (m_eventCounter % 1) == 0 ){
    Info("execute()", "----------------" );
    Info("execute()", "   Event %i   ", m_eventCounter );
    Info("execute()", "----------------" );
  }
  m_eventCounter++;
 
 
  //----------------------------
  // Event information
  //--------------------------- 
  const xAOD::EventInfo* eventInfo = 0;
  ANA_CHECK(m_event->retrieve( eventInfo, "EventInfo"));  
  
  // check if the event is data or MC
  bool isMC = false;
  double EvtWeight = 1.0;
  
  if( eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) )
    isMC = true; 
   
  if( isMC ) { EvtWeight = eventInfo->mcEventWeight();}
  Info("execute()", "Event number = %llu  Event weight = %.2f  isMC = %s",eventInfo->eventNumber(), EvtWeight, (isMC ? "true" : "false"));
  
  //---------------------------
  // Truth particles & vertices
  //---------------------------
  m_TruthParticles = 0;
  ANA_CHECK(m_event->retrieve( m_TruthParticles,"TruthParticles"));
  m_TruthVertices = 0;
  ANA_CHECK(m_event->retrieve(m_TruthVertices,"TruthVertices"));
  PrintTruthInfo(m_TruthParticles, m_TruthVertices, PrintDebug);

  //---------------------------
  // Track Collection
  //---------------------------
  m_InDetTrackParticles  = 0;
  ANA_CHECK(m_event->retrieve( m_InDetTrackParticles ,"InDetTrackParticles"));
  PrintTrackInfo(m_InDetTrackParticles,PrintDebug);
  
  //---------------------------
  // cPFO and nPFO
  //---------------------------
  m_JetETMissChargedParticleFlowObjects  = 0;
  ANA_CHECK(m_event->retrieve( m_JetETMissChargedParticleFlowObjects ,"JetETMissChargedParticleFlowObjects"));
  m_JetETMissNeutralParticleFlowObjects = 0;
  ANA_CHECK(m_event->retrieve(m_JetETMissNeutralParticleFlowObjects,"JetETMissNeutralParticleFlowObjects"));
  PrintPFOInfo( m_JetETMissChargedParticleFlowObjects,m_JetETMissNeutralParticleFlowObjects, PrintDebug);

  //---------------------------
  // EMTopoCluster and PFO cluster
  //---------------------------
  m_topocluster = 0;
  ANA_CHECK(m_event->retrieve( m_topocluster, "CaloCalTopoClusters"));
  m_PFOcluster = 0;
  ANA_CHECK(m_event->retrieve( m_PFOcluster, "PFOClusters_JetETMiss"));
  PrintClusterInfo(m_topocluster,m_PFOcluster, PrintDebug);
  
  //---------------------------
  // CalCellInfo_TopoCluster
  //---------------------------
  m_CalCellInfo_TopoCluster = 0;
  ANA_CHECK(m_event->retrieve(m_CalCellInfo_TopoCluster, "CalCellInfo_TopoCluster"));
  m_CalCellInfo = 0; //CalCellInfo PFO
  ANA_CHECK(m_event->retrieve(m_CalCellInfo, "CalCellInfo"));
  PrintCalCellInfo(m_CalCellInfo_TopoCluster,m_CalCellInfo, PrintDebug);
  
  //----------------------------
  // Jet information
  //--------------------------- 
  m_Jets = 0;
  m_PFlowJets = 0;
  ANA_CHECK(m_event->retrieve( m_Jets, "AntiKt4EMTopoJets" ));
  Info("execute()", "  number of jets = %lu", m_Jets->size());
  ANA_CHECK(m_event->retrieve( m_PFlowJets, "AntiKt4EMPFlowJets" ));
  //name of container
  Info("execute()", "  number of PFlow jets = %lu", m_PFlowJets->size());
  PrintJetCollections(m_Jets,m_PFlowJets, PrintDebug);
  
  
  /*
  MatchJetCollections(m_Jets, m_PFlowJets);*/
  
// loop over the jets by christian

int numGoodJets = 0;

  xAOD::JetContainer::const_iterator jet_itr = m_Jets->begin();
  xAOD::JetContainer::const_iterator jet_end = m_Jets->end();
  // xAOD::JetContainer::const_iterator jet_itrcorr = 0;



  for( ; jet_itr != jet_end; ++jet_itr ) {


    /*
    Info("execute()", "emf = %.2f ",((*jet_itr)->auxdata< float >("EMFrac")));
    Info("execute()", "hecf = %.2f ",((*jet_itr)->auxdata< float >("HECFrac")));
    Info("execute()", "larq = %.2f ",((*jet_itr)->auxdata< float >("LArQuality")));
    Info("execute()", "hecq = %.2f ",((*jet_itr)->auxdata< float >("HECQuality")));
    Info("execute()", "fmax = %.2f ",((*jet_itr)->auxdata< float >("FracSamplingMax")));
    // Info("execute()", "sumpttrk = %.2f ",((*jet_itr)->auxdata< float >("SumPtTrkPt500")));
    Info("execute()", "negE = %.2f ",((*jet_itr)->auxdata< float >("NegativeE")));
    Info("execute()", "AverageLArQF = %.2f ",((*jet_itr)->auxdata< float >("AverageLArQF")));
    
    Info("execute()", " dirty jet pt = %.2f GeV", ((*jet_itr)->pt()*0.001));
    h_jetPtdirty->Fill( ( (*jet_itr)->pt()*0.001));
    Info("execute()", "dirty jet eta = %.2f ", ((*jet_itr)->eta()));
    h_jetEtadirty->Fill( ( (*jet_itr)->eta()));
    Info("execute()", "dirty jet phi = %.2f ", ((*jet_itr)->phi()));
    h_jetPhidirty->Fill( ( (*jet_itr)->phi()));
    Info("execute()", "dirty jet m = %.2f ", ((*jet_itr)->m()));
    h_jetMdirty->Fill( ( (*jet_itr)->m()));
    Info("execute()", "dirty jet energy = %.2f GeV", ((*jet_itr)->e()*0.001));
    h_jetEdirty->Fill( ( (*jet_itr)->e()*0.001));
    */
    //Cleaning
    h_dirtyptemf->Fill(((*jet_itr)->auxdata< float >("EMFrac")),((*jet_itr)->pt()*0.001));

    
     if( !m_jetCleaning->accept( **jet_itr )) continue; //only keep good clean jets
     numGoodJets++;

   Info("execute()", " jet pt = %.2f GeV", ((*jet_itr)->pt()*0.001));
    h_jetPt->Fill( ( (*jet_itr)->pt()*0.001));
    Info("execute()", " jet eta = %.2f ", ((*jet_itr)->eta()));
    h_jetEta->Fill( ( (*jet_itr)->eta()));
    Info("execute()", " jet phi = %.2f ", ((*jet_itr)->phi()));
    h_jetPhi->Fill( ( (*jet_itr)->phi()));
    Info("execute()", " jet m = %.2f ", ((*jet_itr)->m()));
    h_jetM->Fill( ( (*jet_itr)->m()));
    Info("execute()", "jet energy = %.2f GeV", ((*jet_itr)->e()*0.001));
    h_jetE->Fill( ( (*jet_itr)->e()*0.001));

    
    //another hist
    
    //Jet Energy Resolution
    if(isMC){ // assuming isMC flag has been set based on eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) 
        // Get the MC resolution
        double mcRes = m_JERTool->getRelResolutionMC(*jet_itr);
        // Get the resolution uncertainty
        double uncert = m_JERTool->getUncertainty(*jet_itr); // you can provide a second argument specify which nuisance parameter, the default is all 
        Info("execute()", "jet mcRes = %f , uncert = %f", mcRes, uncert);
     } // end if MC

    // virtual CP::CorrectionCode applyCorrection(xAOD::Jet& **jet_itr);

    //JES by Christian
    
 xAOD::Jet * jet = 0;
  m_jetCalibration->calibratedCopy(**jet_itr,jet); //make a calibrated copy

    Info("execute()", " jet pt = %.2f GeV", ((jet)->pt()*0.001));
    h_jetPtcorr->Fill( ( (jet)->pt()*0.001));
    Info("execute()", " jet eta = %.2f ", ((jet)->eta()));
    h_jetEtacorr->Fill( ( (jet)->eta()));
    Info("execute()", " jet phi = %.2f ", ((jet)->phi()));
    h_jetPhicorr->Fill( ( (jet)->phi()));
    Info("execute()", " jet m = %.2f ", ((jet)->m()));
    h_jetMcorr->Fill( ( (jet)->m()));
    Info("execute()", "jet energy corrected = %.2f ", ((jet)->e()*0.001));
    h_jetEcorr->Fill( ( (jet)->e()*0.001));
    
    h_jetEMF->Fill((jet)->auxdata< float >("EMFrac"));
    h_jetHCF->Fill((jet)->auxdata< float >("HECFrac"));

    h_ptemf->Fill(((*jet_itr)->auxdata< float >("EMFrac")),((*jet_itr)->pt()*0.001));

    delete jet;

  }

  //end of loop by christian
   /*
=======
   //Jet matching
  MatchJetCollections(m_Jets, m_PFlowJets);

 
  /*
  //int numGoodJets = 0;
  //int numBadJets = 0;
>>>>>>> 3e81e3a1ad04c784dd62794f8d3a8e113f94abe9
  // loop over the jets in the container
  xAOD::JetContainer::const_iterator jet_itr = m_Jets->begin();
  xAOD::JetContainer::const_iterator jet_end = m_Jets->end();
  for( ; jet_itr != jet_end; ++jet_itr ) {

    // Bad Jets
    if(!m_jetCleaning->accept( **jet_itr )) {
      BadJetsScan(**jet_itr);
      numBadJets++;
    }
    
    // Good jets 
    if( !m_jetCleaning->accept( **jet_itr )) continue; //only keep good clean jets
    numGoodJets++;
    Info("execute()", " GOOD jet pt = %.2f GeV", ((*jet_itr)->pt()/GEV)); // just to print out something
    }
    
  Info("execute()", "  number of jets = %lu numGoodJets = %i  numBadJets = %i", m_Jets->size(), numGoodJets, numBadJets);
  */
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode xAODPFlowAna :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode xAODPFlowAna :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
 
  // finalize(): called once, after the final event has completed 
  
  ANA_CHECK_SET_TYPE (EL::StatusCode);


  if( m_jetCleaning ) {
    delete m_jetCleaning;
    m_jetCleaning = 0;
  }

  if(m_JERTool){
   delete m_JERTool;
   m_JERTool = 0;
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode xAODPFlowAna :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}


void xAODPFlowAna :: BadJetsScan (const xAOD::Jet& jet) {
  
  Info("", "--- Bad Jets Scanning ---");
  Info("BadJetsScan", "jet E = %.2f GeV  pt  = %.2f GeV eta = %.2f  phi =  %.2f",
       jet.e()/GEV, jet.pt()/GEV, jet.phi(), jet.eta());
  
  // if(HasPFlowJetMatched(jet)){
  //   Info("BadJetsScan", "PFlow jet matched  %d E = %.2f GeV  pt  = %.2f GeV eta = %.2f  phi =  %.2f",
  // 	 jet.e()/GEV, jet.pt()/GEV, jet.phi(), jet.eta());
  // }

   
  return;
}



