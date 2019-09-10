/******************************************************************************
 * TruthVars.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the BDT to the skim tree                  *
 * 
 * History
 *      25 Nov 2016 - Created by D. Leggat
 ******************************************************************************/

#ifndef TruthVars_h
#define TruthVars_h

#include "SingleTopRootAnalysis/Base/Dictionary/VarBase.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp" 
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCParticle.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCMuon.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCH.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCTop.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCElectron.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCTau.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCJet.hpp"
#include "TLorentzVector.h"
#include <TEnv.h>


class TruthVars: public VarBase {
  
public:
  TruthVars(bool makeHistos = false);
  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
  
private:
    void Clear();
    // evalutate angle of two LorentzVecotr
    double getAngleOfVecs(TLorentzVector vectA, TLorentzVector vectB, float& cosa) ;
    // evalutate angle of two plane
    double getAngleOfPlanes(TVector3 plane1_vectA, TVector3 plane1_vectB, TVector3 plane2_vectA, TVector3 plane2_vectB, float &cosa);
    // calculate Lorentz boosted angle
    double get_boostedAngle(TLorentzVector Particle1_CMS, TLorentzVector Particle2_CMS, TLorentzVector plane1_vectA, TLorentzVector plane1_vectB, TLorentzVector plane2_vectA, TLorentzVector plane2_vectB, float& cosa);

    Float_t angle_bbpp_truth2l2b ;
    Float_t cosa_bbpp_truth2l2b ;
   
    Float_t truth_H_pt;
    Float_t truth_H_eta;
    Float_t truth_hadTop_pt;
    Float_t truth_hadTop_eta;
    Float_t truth_deta_2b; 
    Float_t truth_cosa_2b; 

};

#endif
