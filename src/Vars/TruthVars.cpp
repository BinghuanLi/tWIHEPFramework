/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/TruthVars.hpp"

#include <iostream>

//Test out a couple of variables, one Int_t and one float I guess
TruthVars::TruthVars(bool makeHistos){

  SetName("TruthVars");
  
  
  _floatVars["angle_bbpp_truth2l2b"] = -1.;
  _floatVars["cosa_bbpp_truth2l2b"] = -1.;
  _floatVars["truth_H_pt"] = -1.;
  _floatVars["truth_H_eta"] = -1.;
  _floatVars["truth_hadTop_pt"] = -1.;
  _floatVars["truth_hadTop_eta"] = -1.;
  _floatVars["truth_deta_2b"] = -1.;
  _floatVars["truth_cosa_2b"] = -1.;

  SetDoHists(makeHistos);

}

void TruthVars::Clear(){
   angle_bbpp_truth2l2b=-9; 
   cosa_bbpp_truth2l2b=-9; 
   truth_H_pt=-9; 
   truth_H_eta=-9; 
   truth_hadTop_pt=-9; 
   truth_hadTop_eta=-9; 
   truth_deta_2b=-9; 
   truth_cosa_2b=-9; 
}

void TruthVars::FillBranches(EventContainer * evtObj){

  //Initialise vectors;
  Clear();
  // find gen particles
  MCParticle b_fromtbar, b_fromt, lep_fromh, lep_fromt, lep_fromw, lep_fromz, Higgs, Top;
  MCParticle gen;
  // find genb
  for(auto bjet: evtObj -> MCBJets){
    if(b_fromt.Pt()>0.00001 && b_fromtbar.Pt() > 0.0001) break;
    gen = bjet;
    MCParticle genMother = gen.GetGenMotherNoFsr(gen, *(evtObj->mcParticlesPtr));
    MCParticle genGMother = genMother.GetGenMotherNoFsr(genMother, *(evtObj->mcParticlesPtr));
    MCParticle genGGMother = genGMother.GetGenMotherNoFsr(genGMother, *(evtObj->mcParticlesPtr));
    if(genMother.PdgId() == 6 || genGMother.PdgId() == 6 || genGGMother.PdgId() == 6){
        b_fromt = gen;
    }
    else if(genMother.PdgId() == -6 || genGMother.PdgId() == -6 || genGGMother.PdgId() == -6){
        b_fromtbar = gen;
    }
  }
  gen.Clear();
  // find gen muon 
  for(auto MCMu: evtObj -> MCMuons){
    if(lep_fromh.Pt()>0.0001 && lep_fromt.Pt() > 0.0001) break;
    if(MCMu.Status()!=1) continue;
    if(MCMu.Pt()<1) continue;
    gen = MCMu;
    MCParticle genMother = gen.GetGenMotherNoFsr(gen, *(evtObj->mcParticlesPtr));
    MCParticle genGMother = genMother.GetGenMotherNoFsr(genMother, *(evtObj->mcParticlesPtr));
    MCParticle genGGMother = genGMother.GetGenMotherNoFsr(genGMother, *(evtObj->mcParticlesPtr));
    if(lep_fromt.Pt()<1 && (fabs(genMother.PdgId()) == 6 || fabs(genGMother.PdgId()) == 6 || fabs(genGGMother.PdgId()) == 6)){
        lep_fromt = gen;
    }
    else if(lep_fromh.Pt()<1 && (fabs(genMother.PdgId()) == 25 || fabs(genGMother.PdgId()) == 25 || fabs(genGGMother.PdgId())) == 25){
        lep_fromh = gen;
    }
    else if(lep_fromz.Pt()<1 && (fabs(genMother.PdgId()) == 23 || fabs(genGMother.PdgId()) == 23 || fabs(genGGMother.PdgId()) == 23)){
        lep_fromz = gen;
    }
    else if(lep_fromw.Pt()<1 && (fabs(genMother.PdgId()) == 24 || fabs(genGMother.PdgId()) == 24 || fabs(genGGMother.PdgId()) == 24)){
        lep_fromw = gen;
    }
  }
  gen.Clear();
  // find gen ele 
  for(auto MCEle: evtObj -> MCElectrons){
    if(lep_fromh.Pt()>0.0001 && lep_fromt.Pt() > 0.0001) break;
    if(MCEle.Pt()<1) continue;
    if(MCEle.Status()!=1) continue;
    gen = MCEle;
    MCParticle genMother = gen.GetGenMotherNoFsr(gen, *(evtObj->mcParticlesPtr));
    MCParticle genGMother = genMother.GetGenMotherNoFsr(genMother, *(evtObj->mcParticlesPtr));
    MCParticle genGGMother = genGMother.GetGenMotherNoFsr(genGMother, *(evtObj->mcParticlesPtr));
    if(lep_fromt.Pt()<1 && (fabs(genMother.PdgId()) == 6 || fabs(genGMother.PdgId()) == 6 || fabs(genGGMother.PdgId()) == 6)){
        lep_fromt = gen;
    }
    else if(lep_fromh.Pt()<1 && (fabs(genMother.PdgId()) == 25 || fabs(genGMother.PdgId()) == 25 || fabs(genGGMother.PdgId())) == 25){
        lep_fromh = gen;
    }
    else if(lep_fromz.Pt()<1 && (fabs(genMother.PdgId()) == 23 || fabs(genGMother.PdgId()) == 23 || fabs(genGGMother.PdgId()) == 23)){
        lep_fromz = gen;
    }
    else if(lep_fromw.Pt()<1 && (fabs(genMother.PdgId()) == 24 || fabs(genGMother.PdgId()) == 24 || fabs(genGGMother.PdgId()) == 24)){
        lep_fromw = gen;
    }
  }
  // find gen H
  for(auto higgs: evtObj -> MCHs){
    if(Higgs.Pt() > 0.0001) break;
    if(higgs.Pt()<1) continue;
    Higgs = higgs;
    truth_H_pt = Higgs.Pt(); 
    truth_H_eta = Higgs.Eta(); 
  }
  // find gen Top:
  for(auto top: evtObj -> MCTops){
    if(Top.Pt() > 0.0001) break;
    if(top.PdgId() * lep_fromt.PdgId() <0) continue;
    if(top.Pt()<1) continue;
    Top = top;
    truth_hadTop_pt = Top.Pt(); 
    truth_hadTop_eta = Top.Eta(); 
  }
  
  // calculate lorentz angle
  TLorentzVector Lep1_CMS, Lep2_CMS, p1_CMS, p2_CMS, b1_CMS, b2_CMS;
  if(lep_fromh.Pt()>0.5){
    Lep1_CMS.SetPtEtaPhiE(lep_fromh.Pt() ,lep_fromh.Eta(),lep_fromh.Phi(),lep_fromh.E());
  }else if(lep_fromz.Pt()>0.5) {
    Lep1_CMS.SetPtEtaPhiE(lep_fromz.Pt() ,lep_fromz.Eta(),lep_fromz.Phi(),lep_fromz.E());
  }else if(lep_fromw.Pt()>0.5) {
    Lep1_CMS.SetPtEtaPhiE(lep_fromw.Pt() ,lep_fromw.Eta(),lep_fromw.Phi(),lep_fromw.E());
  }
  Lep2_CMS.SetPtEtaPhiE(lep_fromt.Pt() ,lep_fromt.Eta(),lep_fromt.Phi(),lep_fromt.E());
  b1_CMS.SetPtEtaPhiE(b_fromtbar.Pt() ,b_fromtbar.Eta(),b_fromtbar.Phi(),b_fromtbar.E());
  b2_CMS.SetPtEtaPhiE(b_fromt.Pt() ,b_fromt.Eta(),b_fromt.Phi(),b_fromt.E());
  p1_CMS.SetXYZM(0,0,-1,0.938); // proton mass 938MeV
  p2_CMS.SetXYZM(0,0,1,0.938); 
  
  if(fabs(Lep1_CMS.Pt())>0.0001 && fabs(Lep2_CMS.Pt())>0.0001 && fabs(b1_CMS.Pt())>0.0001 && fabs(b2_CMS.Pt())>0.0001) angle_bbpp_truth2l2b =get_boostedAngle(Lep1_CMS, Lep2_CMS, p1_CMS, p2_CMS, b1_CMS, b2_CMS, cosa_bbpp_truth2l2b); 
   // calculate 2b kinematics:
   truth_deta_2b = b1_CMS.Eta() - b2_CMS.Eta();
   double truth_angle_2b = getAngleOfVecs(b1_CMS, b2_CMS, truth_cosa_2b);
  
  _floatVars["angle_bbpp_truth2l2b"] = angle_bbpp_truth2l2b;
  _floatVars["cosa_bbpp_truth2l2b"] = cosa_bbpp_truth2l2b;
  _floatVars["truth_H_pt"] = truth_H_pt;
  _floatVars["truth_H_eta"] = truth_H_eta;
  _floatVars["truth_hadTop_pt"] = truth_hadTop_pt;
  _floatVars["truth_hadTop_eta"] = truth_hadTop_eta;
  _floatVars["truth_deta_2b"] = truth_deta_2b;
  _floatVars["truth_cosa_2b"] = truth_cosa_2b;



  if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

double TruthVars::getAngleOfVecs(TLorentzVector vectA, TLorentzVector vectB, float& cosa){
    double angle = -9;
    TVector3 v3A = vectA.Vect();
    TVector3 v3B = vectB.Vect();
    if(v3A.Mag()==0){
        angle = -5;
        cosa = -5;
        return angle; 
    }
    if(v3B.Mag()==0){
        angle = -5;
        cosa = -5;
        return angle; 
    }
    angle = v3A.Angle(v3B);
    cosa = v3A.Dot(v3B)/(v3A.Mag()*v3B.Mag());
    return angle;
};
  
/***************************************************************
 * void TruthVars::getAngleOfPlanes( )              *
 *                                                              * 
 * Calculate angle of two planes Tagger                                    *
 *                                                              *
 * Input:4 TVector3, each pair decide a plane                                     *
 * Output: None                                                *
 * **************************************************************/
double TruthVars::getAngleOfPlanes(TVector3 plane1_vectA, TVector3 plane1_vectB, TVector3 plane2_vectA, TVector3 plane2_vectB, float &cosa){
    double angle = -9;
    TVector3 plane1_norm = plane1_vectA.Cross(plane1_vectB);// get the vector perp to plane 1
    TVector3 plane2_norm = plane2_vectA.Cross(plane2_vectB);// get the vector perp to plane 2
    if(plane1_norm.Mag()==0){
        //std::cout<< "two vectors provided to plane1 cannot determine a plane" << std::endl;
        angle = -5;
        cosa = -5;
        return angle; 
    }
    if(plane2_norm.Mag()==0){
        //std::cout<< "two vectors provided to plane2 cannot determine a plane" << std::endl;
        angle = -5;
        cosa = -5;
        return angle; 
    }
    angle = plane1_norm.Angle(plane2_norm);
    cosa = plane1_norm.Dot(plane2_norm)/(plane1_norm.Mag()*plane2_norm.Mag());
    return angle; 
}

// Lorentz Boost
double TruthVars::get_boostedAngle(TLorentzVector Particle1_CMS, TLorentzVector Particle2_CMS, TLorentzVector plane1_vectA, TLorentzVector plane1_vectB, TLorentzVector plane2_vectA, TLorentzVector plane2_vectB, float& cosa){
    // Input : All six vectors are in lab frame
    //  Particle1_CMS and Particle2_CMS => rod frame
    //  plane1(2)_vectA and plane1(2)_vectB => vectors to determine plane 1 and plane 2
    // Output : the angle of plane1 and plane2 in the center of mass system of Particle1_CMS and Particle2_CMS
    // https://root-forum.cern.ch/t/how-to-use-boost-in-tlorentzvector/4102
    double angle = -9;
    TLorentzVector MyParticleCombi;
    MyParticleCombi.SetPxPyPzE(Particle1_CMS.Px()+Particle2_CMS.Px(),Particle1_CMS.Py()+Particle2_CMS.Py(), Particle1_CMS.Pz()+Particle2_CMS.Pz(), Particle1_CMS.E()+Particle2_CMS.E());
    TVector3  MyParticleCombi_BoostVector = MyParticleCombi.BoostVector();
    // minus because we boost from lab to rod
    plane1_vectA.Boost(-MyParticleCombi_BoostVector); 
    plane1_vectB.Boost(-MyParticleCombi_BoostVector); 
    plane2_vectA.Boost(-MyParticleCombi_BoostVector); 
    plane2_vectB.Boost(-MyParticleCombi_BoostVector); 

    angle = getAngleOfPlanes( plane1_vectA.Vect(),  plane1_vectB.Vect(),  plane2_vectA.Vect(),  plane2_vectB.Vect(), cosa);
    return angle;
}
  
