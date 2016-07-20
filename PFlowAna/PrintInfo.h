#ifndef PFlowAna_xAODPFlowAnaPrintInfo_H
#define PFlowAna_xAODPFlowAnaPrintInfo_H

//EDM includes
#include "xAODEventInfo/EventInfo.h"
//Truth includes
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertexContainer.h"
//TrackParticle Includes
#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/TrackParticleContainer.h"
//Jets and clusters
#include "xAODJet/JetContainer.h"
#include "xAODCaloEvent/CaloCluster.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
//PFO
#include "xAODPFlow/PFOContainer.h"
#include "xAODPFlow/PFO.h"
//CalCellInfo include
#include "xAODCalCellInfo/CalCellInfo.h"
#include "xAODCalCellInfo/CalCellInfoContainer.h"


//Variables
const float GEV = 1000.;

// Functions

void PrintTruthInfo(const xAOD::TruthParticleContainer*,const xAOD::TruthVertexContainer*, bool);
void PrintTrackInfo (const xAOD::TrackParticleContainer*, bool);
void PrintPFOInfo(const xAOD::PFOContainer*, const xAOD::PFOContainer*, bool);
void PrintClusterInfo(const xAOD::CaloClusterContainer*, const xAOD::CaloClusterContainer*, bool);
void PrintCalCellInfo(const xAOD::CalCellInfoContainer* , const xAOD::CalCellInfoContainer*, bool);
void PrintJetCollections(const xAOD::JetContainer*, const xAOD::JetContainer*, bool);



#endif //PFlowAna_xAODPFlowAnaPrintInfo_H
