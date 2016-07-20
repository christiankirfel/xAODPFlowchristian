#include "PFlowAna/PrintInfo.h"

//////////////////////////
// Print Information
//////////////////////////


void  PrintTruthInfo(const xAOD::TruthParticleContainer* tp,const xAOD::TruthVertexContainer* tv, bool PrintDebug){
  //void xAODPFlowAna :: PrintTruthInfo(){
   
   Info("", "------------------- ");
   Info("", "   TruthParticles   ");
   Info("", "------------------- ");
      
   Info("PrintTruthInfo", "Number of truth particles = %lu",tp->size());
   if(PrintDebug){
     xAOD::TruthParticleContainer::const_iterator tp_itr = tp->begin();
     xAOD::TruthParticleContainer::const_iterator tp_end = tp->end();
     for( ; tp_itr != tp_end; ++tp_itr ) {
       int tp_index = std::distance(tp->begin(),tp_itr);
       Info("PrintTruthParticlesInfo () ", "Truth Particle index = %d barcode = %i E = %.2f GeV  pt = %.2f GeV eta = %.2f  phi =  %.2f",
   	    tp_index,
   	    (*tp_itr)->barcode(),
   	    (*tp_itr)->e()/GEV,
   	    (*tp_itr)->pt()/GEV,
   	    (*tp_itr)->eta(),
   	    (*tp_itr)->phi());
       
       // const xAOD::TruthVertex*  prodVtx =  (*tp_itr)->prodVtx();
       // if(prodVtx) Info("PrintTruthParticlesInfo", "Vtx (x,y,z) = (%.2f,%.2f,%.2f)",
       // 			prodVtx->x(),
       // 			prodVtx->y(),
       // 			prodVtx->z());
       // else Info("PrintTruthParticlesInfo", "No Vtx for mc particle");
     }
   }

   Info("", "------------------- ");
   Info("", "   TruthVertex      ");
   Info("", "------------------- ");
  
   Info("PrintTruthInfo", "Truth PV Vertex size = %lu ",tv->size());
   if(PrintDebug){
   Info("PrintTruthInfo", " Truth PV Vertex information (x,y,z) = (%.2lf,%.2lf,%.2lf)",
   	tv->at(0)->x(),
   	tv->at(0)->y(),
   	tv->at(0)->z());
   }
  return;
}
 
 void  PrintTrackInfo (const xAOD::TrackParticleContainer* idtrk, bool PrintDebug){
 
   Info("", "-------------------- ");
   Info("", " InDetTrackParticles ");
   Info("", "-------------------- ");
   
   Info("PrintTrackInfo", "Number of InDetTrackParticles = %lu",idtrk->size());
   if(PrintDebug){
     xAOD::TrackParticleContainer::const_iterator idtrk_itr = idtrk->begin();
     xAOD::TrackParticleContainer::const_iterator idtrk_end = idtrk->end();
     for( ; idtrk_itr != idtrk_end; ++idtrk_itr ) {
       Info("PrintTrackInfo", "InDetTrackParticles charge = %f  E  = %.2f GeV  pt = %.2f GeV  eta = %.2f  phi = %.2f ",
	    (*idtrk_itr)->charge(),
	    (*idtrk_itr)->e()/GEV,
	    (*idtrk_itr)->pt()/GEV,
	    (*idtrk_itr)->eta(),
	    (*idtrk_itr)->phi());
     }
   }
   return;
 }


void  PrintPFOInfo (const xAOD::PFOContainer* cpfo, const xAOD::PFOContainer* npfo, bool PrintDebug){

   Info("", "----------------- ");
   Info("", " Charged PFO      ");
   Info("", "----------------- ");
   
  Info("PrintPFOInfo", "Number of ChargedParticleFlowObjects = %lu",cpfo->size());
  if(PrintDebug){
    xAOD::PFOContainer::const_iterator cpfo_itr = cpfo->begin();
    xAOD::PFOContainer::const_iterator cpfo_end = cpfo->end();
    for( ; cpfo_itr != cpfo_end; ++cpfo_itr ) {
      int cpfo_index = std::distance(cpfo->begin(),cpfo_itr);
      Info("PrintPFOInfo", "Charged PFO %d E = %.2f GeV  pt = %.2f GeV  eta = %.2f  phi = %.2f",
	   cpfo_index, (*cpfo_itr)->e()/GEV,
	   (*cpfo_itr)->pt()/GEV,
	   (*cpfo_itr)->eta(),
	   (*cpfo_itr)->phi());     
      
      //Associated cluster
      const xAOD::CaloCluster* matchedCluster = (*cpfo_itr)->cluster(0);
      // raw = "UNCALIBRATED” – electromagnetic energy scale, cluster energy is cell energy sum including possible topological weights from cluster splitting
      if(matchedCluster)
      	Info("PrintPFOInfo", "MatchedCluster_E  = %.3f, eta = %.3f, phi = %.3f ",matchedCluster->rawE(), matchedCluster->eta(), matchedCluster->phi());
      else Info("PrintPFOInfo", "No cluster matched to the cPFO");
    }
  }

  Info("", "----------------- ");
  Info("", " Neutral PFO      ");
  Info("", "----------------- ");
  
  Info("PrintPFOInfo", "Number of NeutralParticleFlowObjects = %lu", npfo->size());
  if(PrintDebug){
    xAOD::PFOContainer::const_iterator npfo_itr = npfo->begin();
    xAOD::PFOContainer::const_iterator npfo_end = npfo->end();
    for( ; npfo_itr != npfo_end; ++npfo_itr ) {
      int npfo_index = std::distance(npfo->begin(),npfo_itr);
      Info("PrintPFOInfo", "Neutral PFO %d E = %.2f GeV  pt  = %.2f GeV eta = %.2f  phi =  %.2f",
	   npfo_index,
	   (*npfo_itr)->e()/GEV,
	   (*npfo_itr)->pt()/GEV,
	   (*npfo_itr)->eta(),
	   (*npfo_itr)->phi());  
      
      // Associated clusters
      const xAOD::CaloCluster* matchedCluster = (*npfo_itr)->cluster(0);
      if (matchedCluster)
      	Info("PrintPFOInfo", "MatchedCluster_E  = %.3f, eta = %.3f, phi = %.3f ",matchedCluster->rawE(), matchedCluster->eta(), matchedCluster->phi());
      else Info("PrintPFOInfo", "No cluster matched to the nPFO");
      //The energy at different layers can be gotten using clusterN->eSample(xAOD::CaloCluster::CaloSample::EMB1);
    }
  }
  return;
}

void  PrintClusterInfo (const xAOD::CaloClusterContainer* CaloCluster, const xAOD::CaloClusterContainer* pfoCluster, bool PrintDebug){
  
  Info("", "----------------- ");
  Info("", " TopoClusters     ");
  Info("", "----------------- ");

 Info("execute()", "Number of TopoClusters = %lu",CaloCluster->size());
 if(PrintDebug){
   xAOD::CaloClusterContainer::const_iterator CaloCluster_itr = CaloCluster->begin();
   xAOD::CaloClusterContainer::const_iterator CaloCluster_end = CaloCluster->end();
   for( ; CaloCluster_itr != CaloCluster_end; ++CaloCluster_itr  ) {
     int CaloCluster_index = std::distance(CaloCluster->begin(),CaloCluster_itr);
     Info("PrintTopoClusterInfo", "CaloClusterContainer %d E_em = %.2f GeV E_cal = %.2f GeV  pt  = %.2f GeV eta = %.2f  phi =  %.2f",
	  CaloCluster_index,
	  (*CaloCluster_itr)->rawE()/GEV,
	 (*CaloCluster_itr)->calE()/GEV,
	  (*CaloCluster_itr)->pt()/GEV,
	  (*CaloCluster_itr)->eta(),
	  (*CaloCluster_itr)->phi()); 
   }
 }
 Info("", "----------------- ");
  Info("", "  PFOCluster      ");
  Info("", "----------------- ");
  
  Info("PrintTopoClusterInfo", "Number of PFOClusters = %lu", pfoCluster->size());
  if(PrintDebug){
    xAOD::CaloClusterContainer::const_iterator pfo_cl_itr = pfoCluster->begin();
    xAOD::CaloClusterContainer::const_iterator pfo_cl_end = pfoCluster->end();
    for( ; pfo_cl_itr != pfo_cl_end; ++pfo_cl_itr ) {
      int pfo_cl_index = std::distance(pfoCluster->begin(),pfo_cl_itr);
      Info("PrintTopoClusterInfo", "PFO cluster %d E = %.2f GeV  pt  = %.2f GeV eta = %.2f  phi =  %.2f",
	   pfo_cl_index,
	   (*pfo_cl_itr)->e()/GEV,
	   (*pfo_cl_itr)->pt()/GEV,
	   (*pfo_cl_itr)->eta(),
	   (*pfo_cl_itr)->phi());
    }
  }
  return;
}

void  PrintCalCellInfo (const xAOD::CalCellInfoContainer* CalCellInfoTopoCl,  const xAOD::CalCellInfoContainer* CalCellInfo, bool PrintDebug) {
  
  Info("", "--------------------------- ");
  Info("", "  CalCellInfoTopoCluster    ");
  Info("", "--------------------------- ");
   
  Info("PrintCalCellInfo", "Number of CalCellInfo_TopoCluster = %lu",CalCellInfoTopoCl->size());
  if(PrintDebug){
    xAOD::CalCellInfoContainer::const_iterator CalCellInfoTopoCl_itr = CalCellInfoTopoCl->begin();
    xAOD::CalCellInfoContainer::const_iterator CalCellInfoTopoCl_end = CalCellInfoTopoCl->end();
    for( ; CalCellInfoTopoCl_itr != CalCellInfoTopoCl_end; ++CalCellInfoTopoCl_itr ) {
      int index = std::distance(CalCellInfoTopoCl->begin(),CalCellInfoTopoCl_itr);
      Info("PrintCalCellInfo", "CalCellInfo TopoCluster %d  barcode = %i  particleID =  %i cl_E  = %.2f GeV  cell_eta =  %.2f  cell_phi = %.2f  EMEnergy = %.2f GeV   nonEMEnergy = %.2f GeV",
	   index,
	   (*CalCellInfoTopoCl_itr)->barcode(),
	   (*CalCellInfoTopoCl_itr)->particleID(),
	   (*CalCellInfoTopoCl_itr)->clusterRecoEnergy()/GEV,
	   (*CalCellInfoTopoCl_itr)->cellEta(),
	   (*CalCellInfoTopoCl_itr)->cellPhi(),
	   (*CalCellInfoTopoCl_itr)->EMEnergy()/GEV,
	   (*CalCellInfoTopoCl_itr)->nonEMEnergy()/GEV);
    }
  }

  Info("PrintCalCellInfo", "Number of CalCellInfo = %lu", CalCellInfo->size());
  
  return;
}


void  PrintJetCollections (const xAOD::JetContainer* Jets, const xAOD::JetContainer* PFlowJets, bool PrintDebug) {
  
  Info("", "--- Jet Collections ---");
  
  Info("PrintJetCollections", "Number of TopoJets = %lu", Jets->size());
  if(PrintDebug){
    xAOD::JetContainer::const_iterator Jets_itr = Jets->begin();
    xAOD::JetContainer::const_iterator Jets_end = Jets->end();
    for( ; Jets_itr != Jets_end; ++Jets_itr ) {
      int index = std::distance(Jets->begin(),Jets_itr);
      Info("PrintJetCollections", "TopoJets  %d  E  = %.2f GeV  pt =  %.2f  eta = %.2f  phi = %.2f GeV",
	   index,
	   (*Jets_itr)->e()/GEV,
	   (*Jets_itr)->pt()/GEV,
	   (*Jets_itr)->eta(),
	   (*Jets_itr)->phi());
    }
  }

  Info("PrintJetCollections", "Number of PFlowJets = %lu", PFlowJets->size());
  if(PrintDebug){
    xAOD::JetContainer::const_iterator PFlowJets_itr = PFlowJets->begin();
    xAOD::JetContainer::const_iterator PFlowJets_end = PFlowJets->end();
    for( ; PFlowJets_itr != PFlowJets_end; ++PFlowJets_itr ) {
	int index = std::distance(PFlowJets->begin(),PFlowJets_itr);
	Info("PrintJetCollections", "PFlowJets  %d  E  = %.2f GeV  pt =  %.2f  eta = %.2f  phi = %.2f GeV",
	     index, 
	     (*PFlowJets_itr)->e()/GEV,
	     (*PFlowJets_itr)->pt()/GEV,
	     (*PFlowJets_itr)->eta(),
	     (*PFlowJets_itr)->phi());
    }
  }
  
  return;
}
  
