/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/HadTopVars.hpp"

#include <iostream>

//Test out a couple of variables, one Int_t and one float I guess
HadTopVars::HadTopVars(bool makeHistos){

  SetName("HadTopVars");
  
  
  _floatVars["hadTop_BDT"] = -1.;
  _floatVars["hadTop_pt"] = -1.;
  _floatVars["bjet_resTop_index"] = -1.;
  _floatVars["wjet1_resTop_index"] = -1.;
  _floatVars["wjet2_resTop_index"] = -1.;
  _floatVars["hadTop_btagDisc_b"] = -1.;
  _floatVars["hadTop_btagDisc_Wj1"] = -1.;
  _floatVars["hadTop_btagDisc_Wj2"] = -1.;
  _floatVars["hadTop_qg_Wj1"] = -1.;
  _floatVars["hadTop_qg_Wj2"] = -1.;
  _floatVars["hadTop_m_Wj1Wj2_div_m_bWj1Wj2"] = -1.;
  _floatVars["hadTop_pT_Wj1Wj2"] = -1.;
  _floatVars["hadTop_dR_Wj1Wj2"] = -1.;
  _floatVars["hadTop_m_bWj1Wj2"] = -1.;
  _floatVars["hadTop_dR_bW"] = -1.;
  _floatVars["hadTop_m_bWj1"] = -1.;
  _floatVars["hadTop_m_bWj2"] = -1.;
  _floatVars["hadTop_mass_Wj1"] = -1.;
  _floatVars["hadTop_pT_Wj2"] = -1.;
  _floatVars["hadTop_mass_Wj2"] = -1.;
  _floatVars["hadTop_pT_b"] = -1.;
  _floatVars["hadTop_mass_b"] = -1.;
    
 
  _doubleVecs["Jet25_isToptag"] = {-0.1, 1.9 }; 

  SetDoHists(makeHistos);

}

void HadTopVars::Clear(){
  Jet25_isToptag.clear();
  hadTop_BDT= -9;
  hadTop_pt= -9;
  bjet_hadTop_index=-9;
  wjet1_hadTop_index=-9;
  wjet2_hadTop_index=-9;
  hadTop_btagDisc_b=-9;
  hadTop_btagDisc_Wj1=-9;
  hadTop_btagDisc_Wj2=-9;
  hadTop_qg_Wj1=-9;
  hadTop_qg_Wj2=-9;
  hadTop_m_Wj1Wj2_div_m_bWj1Wj2=-9;
  hadTop_pT_Wj1Wj2=-9;
  hadTop_dR_Wj1Wj2=-9;
  hadTop_m_bWj1Wj2=-9;
  hadTop_dR_bW=-9;
  hadTop_m_bWj1=-9;
  hadTop_m_bWj2=-9;
  hadTop_mass_Wj1=-9;
  hadTop_pT_Wj2=-9;
  hadTop_mass_Wj2=-9;
  hadTop_pT_b=-9;
  hadTop_mass_b=-9;
    
}

void HadTopVars::FillBranches(EventContainer * evtObj){

  //Initialise vectors;
  Clear();
  
  Reco_hadTop(evtObj);
  
  _floatVars["hadTop_BDT"] = hadTop_BDT;
  _floatVars["hadTop_pt"] = hadTop_pt;
  _floatVars["bjet_hadTop_index"] = bjet_hadTop_index;
  _floatVars["wjet1_hadTop_index"] = wjet1_hadTop_index;
  _floatVars["wjet2_hadTop_index"] = wjet2_hadTop_index;
  _floatVars["hadTop_btagDisc_b"] = hadTop_btagDisc_b;
  _floatVars["hadTop_btagDisc_Wj1"] = hadTop_btagDisc_Wj1;
  _floatVars["hadTop_btagDisc_Wj2"] = hadTop_btagDisc_Wj2;
  _floatVars["hadTop_qg_Wj1"] = hadTop_qg_Wj1;
  _floatVars["hadTop_qg_Wj2"] = hadTop_qg_Wj2;
  _floatVars["hadTop_m_Wj1Wj2_div_m_bWj1Wj2"] = hadTop_m_Wj1Wj2_div_m_bWj1Wj2;
  _floatVars["hadTop_pT_Wj1Wj2"] = hadTop_pT_Wj1Wj2;
  _floatVars["hadTop_dR_Wj1Wj2"] = hadTop_dR_Wj1Wj2;
  _floatVars["hadTop_m_bWj1Wj2"] = hadTop_m_bWj1Wj2;
  _floatVars["hadTop_dR_bW"] = hadTop_dR_bW;
  _floatVars["hadTop_m_bWj1"] = hadTop_m_bWj1;
  _floatVars["hadTop_m_bWj2"] = hadTop_m_bWj2;
  _floatVars["hadTop_mass_Wj1"] = hadTop_mass_Wj1;
  _floatVars["hadTop_pT_Wj2"] = hadTop_pT_Wj2;
  _floatVars["hadTop_mass_b"] = hadTop_mass_b;

  evtObj->HadTop_BDT = hadTop_BDT;

  Int_t jet_index=-1;
  for(uint jet_en=0; jet_en< evtObj->jets.size();jet_en++){
    jet_index++;
    Double_t isTagged = 0.;
    if(jet_index == bjet_hadTop_index || jet_index == wjet1_hadTop_index || jet_index == wjet2_hadTop_index)isTagged=1.;
    evtObj->jets.at(jet_en).SetisToptag(isTagged);
    Jet25_isToptag.push_back(isTagged);
  }
  
  _doubleVecs["Jet25_isToptag"] = Jet25_isToptag; 

  if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

/***************************************************************
 * void HadTopVars::Reco_hadTop( )              *
 *                                                              * 
 * Calculate HadTop Tagger                                    *
 *                                                              *
 * Input: selected Leptons and Jets                                    *
 * Output: None                                                *
 * **************************************************************/
void HadTopVars::Reco_hadTop(EventContainer *EvtObj){
 Int_t bjet_hadTop_INDEX= -9;
 Int_t wjet1_hadTop_INDEX= -9;
 Int_t wjet2_hadTop_INDEX= -9;
 std::vector<Lepton> selectedLeptons = EvtObj->fakeLeptons;
 std::vector<Jet> Jets = EvtObj->jets;
 int njets = Jets.size();
 //std::sort(Jets.begin(),Jets.end(),[](const Jet &a, const Jet &b){return a.pfDeepCSVBJetTags() > b.pfDeepCSVBJetTags();});
  for (int i1=0; i1<njets; i1++) {
    for (int i2=0; i2<njets; i2++){
      for (int i3=0; i3<njets; i3++){
        if(i1==i2 || i1==i3 || i2==i3) continue;
        Jet bjet = Jets.at(i1);
        Jet w1jet = Jets.at(i2);
        Jet w2jet = Jets.at(i3);
        
        EvtObj->var_btagDisc_b = max(bjet.pfDeepCSVBJetTags(),0.);
        EvtObj->var_btagDisc_Wj1 = max(w1jet.pfDeepCSVBJetTags(), 0.);
        EvtObj->var_btagDisc_Wj2 = max(w2jet.pfDeepCSVBJetTags(),0.);
        EvtObj->var_qg_Wj1 = max(w1jet.qg(),0.);
        EvtObj->var_qg_Wj2 = max(w2jet.qg(),0.);
        EvtObj->var_m_Wj1Wj2_div_m_bWj1Wj2 = (w1jet + w2jet +bjet).M()>0? (w1jet + w2jet).M()/(w1jet + w2jet +bjet).M() : -1;
        EvtObj->var_pT_Wj1Wj2 = (w1jet + w2jet).Pt(); 
        EvtObj->var_dR_Wj1Wj2 = w1jet.DeltaR(w2jet);
        EvtObj->var_m_bWj1Wj2 = (w1jet + w2jet +bjet).M();
        EvtObj->var_dR_bW = bjet.DeltaR(w1jet + w2jet);
        EvtObj->var_m_bWj1 = (bjet+w1jet).M();
        EvtObj->var_m_bWj2 = (bjet+w2jet).M();
        EvtObj->var_mass_Wj1 = w1jet.M();
        EvtObj->var_pT_Wj2 = w2jet.Pt();
        EvtObj->var_mass_Wj2 = w2jet.M();
        EvtObj->var_pT_b = bjet.Pt();
        EvtObj->var_mass_b = bjet.M();
     
        float xgbOutput = EvtObj->hadTop_reader->EvaluateMVA("BDTG method");
        float score = 1/(1+sqrt((1-xgbOutput)/(1+xgbOutput)));   
    
        if(EvtObj -> _sync == 51 && EvtObj->eventNumber == 166766){                                                                      
          std::cout << " nEvent "<< EvtObj->eventNumber << std::endl;
          std::cout << " xgbOutput "<< xgbOutput << std::endl;
          std::cout << " hadTop_BDT "<< score << std::endl;
          std::cout << " hadTop_pt "<< (w1jet + w2jet +bjet).Pt() << std::endl;
          std::cout << " bjet_hadTop_index "<< bjet.index()  << std::endl;
          std::cout << " wjet1_hadTop_index "<< w1jet.index() << std::endl;
          std::cout << " wjet2_hadTop_index "<< w2jet.index() << std::endl;
          std::cout << " hadTop_btagDisc_b "<< EvtObj->var_btagDisc_b << std::endl;
          std::cout << " hadTop_btagDisc_Wj1 "<< EvtObj->var_btagDisc_Wj1 << std::endl;
          std::cout << " hadTop_btagDisc_Wj2 "<< EvtObj->var_btagDisc_Wj2 << std::endl;
          std::cout << " hadTop_qg_Wj1 "<< EvtObj->var_qg_Wj1 << std::endl;
          std::cout << " hadTop_qg_Wj2 "<< EvtObj->var_qg_Wj2 << std::endl;
          std::cout << " hadTop_m_Wj1Wj2_div_m_bWj1Wj2 "<< EvtObj->var_m_Wj1Wj2_div_m_bWj1Wj2 << std::endl;
          std::cout << " hadTop_pT_Wj1Wj2 "<< EvtObj->var_pT_Wj1Wj2 << std::endl;
          std::cout << " hadTop_dR_Wj1Wj2 "<< EvtObj->var_dR_Wj1Wj2 << std::endl;
          std::cout << " hadTop_m_bWj1Wj2 "<< EvtObj->var_m_bWj1Wj2 << std::endl;
          std::cout << " hadTop_dR_bW "<< EvtObj->var_dR_bW << std::endl;
          std::cout << " hadTop_m_bWj1 "<< EvtObj->var_m_bWj1 << std::endl;
          std::cout << " hadTop_m_bWj2 "<< EvtObj->var_m_bWj2 << std::endl;
          std::cout << " hadTop_mass_Wj1 "<< EvtObj->var_mass_Wj1 << std::endl;
          std::cout << " hadTop_pT_Wj2 "<< EvtObj->var_pT_Wj2 << std::endl;
          std::cout << " hadTop_mass_Wj2 "<< EvtObj->var_mass_Wj2 << std::endl;
          std::cout << " hadTop_pT_b "<< EvtObj->var_pT_b << std::endl;
          std::cout << " hadTop_mass_b "<< EvtObj->var_mass_b << std::endl;
        }                          
    
    
        if(score > hadTop_BDT){
            hadTop_BDT = score;
            hadTop_pt = (w1jet + w2jet +bjet).Pt();

            bjet_hadTop_index = bjet.index();
            wjet1_hadTop_index = w1jet.index();
            wjet2_hadTop_index = w2jet.index();
            hadTop_btagDisc_b  = EvtObj->var_btagDisc_b;
            hadTop_btagDisc_Wj1  = EvtObj->var_btagDisc_Wj1;
            hadTop_btagDisc_Wj2  = EvtObj->var_btagDisc_Wj2;
            hadTop_qg_Wj1  = EvtObj->var_qg_Wj1;
            hadTop_qg_Wj2  = EvtObj->var_qg_Wj2;
            hadTop_m_Wj1Wj2_div_m_bWj1Wj2  = EvtObj->var_m_Wj1Wj2_div_m_bWj1Wj2;
            hadTop_pT_Wj1Wj2  = EvtObj->var_pT_Wj1Wj2;
            hadTop_dR_Wj1Wj2  = EvtObj->var_dR_Wj1Wj2;
            hadTop_m_bWj1Wj2  = EvtObj->var_m_bWj1Wj2;
            hadTop_dR_bW  = EvtObj->var_dR_bW;
            hadTop_m_bWj1  = EvtObj->var_m_bWj1;
            hadTop_m_bWj2  = EvtObj->var_m_bWj2;
            hadTop_mass_Wj1  = EvtObj->var_mass_Wj1;
            hadTop_pT_Wj2  = EvtObj->var_pT_Wj2;
            hadTop_mass_b  = EvtObj->var_mass_b;

        }
      }
    }
  }
}
