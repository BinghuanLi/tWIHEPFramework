/******************************************************************************
 * HistogrammingTV.hpp                                                        *
 *                                                                            *
 * Fills a tree with specific variables.                                      *
 * Should be called after preselection cuts in bin/analysis                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of AnalysisMain class                              *
 *    HistogrammingTV()              -- Parameterized Constructor             *
 *    ~HistogrammingTV()             -- Destructor                            *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Fill histograms only (No Cuts)     *
 *    GetCutName()                      -- Returns "HistogrammingTV"          *
 *                                                                            *
 * Private Data Members of this class                                         *
 *        TFile *_skimFile                                                    *
 *        TTree *_skimTree;                                                   *
          Lots of variables, histograms                                       *
 *                                                                            *
 * History     
    // constructor
  // arguments: - pointer to input particles class
  //            - write: whether to write out the NN skim or not
  //            - name: name of the NNvars skim file
  //            - doSpin: whether to include top spin correlation vars in NN                                                           
 *****************************************************************************/

#ifndef HistogrammingTV_h
#define HistogrammingTV_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;


class HistogrammingTV : public HistoCut 
{

public:

  HistogrammingTV(EventContainer *obj,TFile *_skimFile);
  
  // destructor
  ~HistogrammingTV();

  // methods:
  void BookHistogram();
  bool Apply();
  
  inline std::string GetCutName (void) { return "HistogrammingTV"; };

private:
  // TFile *_skimFile;
  TTree *_skimTree;

  // skim tree variables
 
  //------------------------------------------------------
  // Event Weight
  //------------------------------------------------------
  Double_t _EventWeight;
  int _RunNumber;
  int _EventNumber;
  
  //------------------------------------------------------
  // System Mass Histograms
  //------------------------------------------------------
  Double_t _InvariantMass_AllJets;
  Double_t _InvariantMass_Jet1Jet2LeptonMET;
  Double_t _InvariantMass_AllJetsLeptonMET;
  Double_t _InvariantMass_LeptonMETBestJet;
  Double_t _InvariantMass_AllJets_MinusBestJet;
  Double_t _InvariantMass_AllJets_MinusBTaggedJet;
  Double_t _InvariantMass_Jet1Jet2;
  Double_t _TransverseMass_Jet1Jet2;
  Double_t _TransverseMass_Jet1Jet2_LEP;
  Double_t _Shat;
  Double_t _Neutrino_Mass;
  Double_t _Neutrino_Pz;
    
  //------------------------------------------------------
  // H Histograms
  //------------------------------------------------------
  Double_t _H_Jet1Jet2LeptonMET;
  Double_t _H_Jet1Jet2LeptonMET_MinusBJet;
  Double_t _H_AllJetsLeptonMET;
  Double_t _H_AllJets;
  Double_t _H_AllJets_MinusBestJet;
  Double_t _H_AllJets_MinusBTaggedJet;
  Double_t _H_Jet1Jet2;
    
  //------------------------------------------------------
  // Ht Histograms
  //------------------------------------------------------
  Double_t _HT; //I added this
  Double_t _HT_Jet1Jet2LeptonMET;
  Double_t _HT_LeptonMET;
  Double_t _HT_Jet1Jet2LeptonMET_MinusBJet;
  Double_t _HT_AllJetsLeptonMET;
  Double_t _HT_AllJetsLepton;
  Double_t _HT_AllJets;
  Double_t _HT_AllJets_MinusBestJet;
  Double_t _HT_AllJets_MinusBTaggedJet;
  Double_t _HT_Jet1Jet2;
  Double_t _Jet3Pt5Jet4Pt;
  Double_t _Jet1Pt4MET;

  //------------------------------------------------------
  // Jet Histograms
  //------------------------------------------------------
  Double_t _Jet1Pt;
  Double_t _Jet2Pt;
  Double_t _Jet3Pt;
  Double_t _Jet4Pt;
  Double_t _Jet1Eta;
  Double_t _Jet2Eta;
  Double_t _Jet3Eta;
  Double_t _Jet4Eta;
  Double_t _Jet1Pt_NotBest;
  Double_t _Jet2Pt_NotBest;
  Double_t _Pt_Jet1Jet2;
  Double_t _Pt_AllJets_MinusBestJet;
  Double_t _Pt_AllJets_MinusBTaggedJet;
  Double_t _DeltaPt_Jet1Jet2;
  int _NJets;
  int _NGoodJets;
  int _NTaggedJets;
  int _NUntaggedJets;
  Double_t _BestJetPt;
  Double_t _DeltaRJet1Jet2;
  Double_t _DeltaPhiLeadingJetLepton;
  Double_t _DeltaPhiLeadingJetMissingEt;
  Double_t _DeltaRLeadingJetLepton;
  Double_t _Jet12_Centrality;
  Double_t _AllJetsLepton_Centrality;
  Double_t _MaxJetEta;
  Double_t _MinJetEta;

    
  //------------------------------------------------------
  // Missing Et Histograms
  //------------------------------------------------------
  Double_t _METPt;
  Double_t _MET;
    
  //------------------------------------------------------
  // W Histograms
  //------------------------------------------------------
  Double_t _WTransverseMass;
  Double_t _WTransverseMass_LEP;
  Double_t _WTransverseMassPrime;
  Double_t _WPt;
  int _WCharge;
  Double_t _DeltaPhi;
    
  //------------------------------------------------------
  // Top Histograms
  //------------------------------------------------------
  Double_t _BestTopMass;
  Double_t _BTaggedTopMass;
  Double_t _DeltaBestTopMass;
  Double_t _DeltaBTaggedTopMass;
  Double_t _LeadingJetTopMass;
    
  //------------------------------------------------------
  // Lepton Histograms
  //------------------------------------------------------
  Double_t _LeptonPt;
  Double_t _LeptonEta;
  Double_t _LeptonPhi;
  Double_t _QTimesEtaLepton;
    
  //------------------------------------------------------
  // UnTagged Jet Histograms
  //------------------------------------------------------
  Double_t _LeadingUntaggedJetPt;
  Double_t _SecondUntaggedJetPt;
  Double_t _LeadingUntaggedJetEta;
  Double_t _QTimesEta;
  Double_t _DeltaPt_tag_untag;
  Double_t _DeltaRLeadingUntaggedJetLepton;
  //------------------------------------------------------
  // b-Tagged Jet Histograms
  //------------------------------------------------------
  Double_t _LeadingBTaggedJetPt;
  Double_t _SecondBTaggedJetPt;
  Double_t _LeadingBTaggedJetEta;
  Double_t _SecondBTaggedJetEta;
  Double_t _DeltaRLeadingBTaggedJetLepton;
  Double_t _DeltaRSecondBTaggedJetLepton;
  Double_t _DeltaRBTaggedJet1BTaggedJet2;
  //------------------------------------------------------
  // Angular Variable Histograms
  //------------------------------------------------------
  Double_t _Cos_UntaggedJetLepton_BTaggedTop;
  Double_t _Cos_Jet1Lepton_LeadingTop;
  Double_t _Cos_Jet2Lepton_LeadingTop;
  Double_t _Cos_Jet3Lepton_LeadingTop;
  Double_t _Cos_Jet3Lepton_BestTop;
  Double_t _Cos_Jet1Lepton_Lab;
  Double_t _Cos_BTaggedJetLepton_Lab;
  Double_t _Cos_BestJetLepton_Lab;
  Double_t _Cos_Jet2Lepton_Lab;
  Double_t _Cos_Jet1AllJets_AllJets;
  Double_t _Cos_BTaggedJetAllJets_AllJets;
  Double_t _Cos_UntaggedJetAllJets_AllJets;
  Double_t _Cos_NotBestJetAllJets_AllJets;
  Double_t _Cos_Jet2AllJets_AllJets;
  Double_t _Cos_Jet1ZAxis_LeadingTop;
  Double_t _Cos_Jet1ZAxis_Lab;
  Double_t _Cos_Jet2ZAxis_Lab;
  Double_t _Cos_LeptonQZ_BestTop;
  Double_t _Cos_LeptonZpl_BestTop;
  Double_t _Cos_LeptonZmn_BestTop;
  Double_t _Cos_LeptonZpl_LeadingTop;
  Double_t _Cos_LeptonZmn_LeadingTop;
  Double_t _Cos_Jet1ThetaStar;

  //------------------------------------------------------
  // NN output
  //------------------------------------------------------
  Double_t _NN_e_tb_wbb;
  Double_t _NN_e_tb_lepjets;
  Double_t _NN_e_tqb_wbb;
  Double_t _NN_e_tqb_lepjets;
 

  // Histograms declaration 
  //
  ////////////////////////////////////////////////////////
  // define some histograms to be filled
  //////////////////////////

  //------------------------------------------------------
  // System Mass Histograms
  //------------------------------------------------------
  myTH1F* _hInvariantMass_AllJets;
  myTH1F* _hInvariantMass_Jet1Jet2LeptonMET;
  myTH1F* _hInvariantMass_AllJetsLeptonMET;
  //myTH1F* _hInvariantMass_LeptonMETBestJet;
  myTH1F* _hInvariantMass_AllJets_MinusBestJet;
  myTH1F* _hInvariantMass_AllJets_MinusBTaggedJet;
  myTH1F* _hInvariantMass_Jet1Jet2;
  myTH1F* _hTransverseMass_Jet1Jet2;
  //myTH1F* _hTransverseMass_Jet1Jet2_LEP;
  myTH1F* _hShat;
  myTH1F* _hNeutrino_Mass;
  myTH1F* _hNeutrino_Pz;
  //------------------------------------------------------
  // H Histograms
  //------------------------------------------------------
  myTH1F* _hH_Jet1Jet2LeptonMET;
  //myTH1F* _hH_Jet1Jet2LeptonMET_MinusBJet;
  myTH1F* _hH_AllJetsLeptonMET;
  myTH1F* _hH_AllJets;
  myTH1F* _hH_AllJets_MinusBestJet;
  myTH1F* _hH_AllJets_MinusBTaggedJet;
  myTH1F* _hH_Jet1Jet2;
    
  //------------------------------------------------------
  // Ht Histograms
  //------------------------------------------------------
    myTH1F* _hHT_Jet1Jet2LeptonMET;
  myTH1F* _hHT_LeptonMET;
  //myTH1F* _hHT_Jet1Jet2LeptonMET_MinusBJet;
  myTH1F* _hHT_AllJetsLeptonMET;
  myTH1F* _hHT_AllJetsLepton;
  myTH1F* _hHT_AllJets;
  myTH1F* _hHT_AllJets_MinusBestJet;
  myTH1F* _hHT_AllJets_MinusBTaggedJet;
  myTH1F* _hHT_Jet1Jet2;
  //myTH1F* _hJet3Pt5Jet4Pt;
  //myTH1F* _hJet1Pt4MET;

  //------------------------------------------------------
  // Jet Histograms
  //------------------------------------------------------
  myTH1F* _hJet1Pt;
  myTH1F* _hJet2Pt;
  myTH1F* _hJet3Pt;
  myTH1F* _hJet4Pt;
  myTH1F* _hJet1Eta;
  myTH1F* _hJet2Eta;
  myTH1F* _hJet3Eta;
  myTH1F* _hJet4Eta;
  myTH1F* _hJet1Pt_NotBest;
  myTH1F* _hJet2Pt_NotBest;
  myTH1F* _hPt_Jet1Jet2;
  myTH1F* _hPt_AllJets_MinusBestJet;
  myTH1F* _hPt_AllJets_MinusBTaggedJet;
  myTH1F* _hDeltaPt_Jet1Jet2;
  myTH1F* _hNJets;
  myTH1F* _hNGoodJets;
  myTH1F* _hNTaggedJets;
  myTH1F* _hNUntaggedJets;
  myTH1F* _hBestJetPt;
  myTH1F* _hDeltaRJet1Jet2;
  //myTH1F* _hDeltaPhiLeadingJetLepton;
  //myTH1F* _hDeltaPhiLeadingJetMissingEt;
  myTH1F* _hDeltaRLeadingJetLepton;
  myTH1F* _hJet12_Centrality;
  myTH1F* _hAllJetsLepton_Centrality;
  myTH1F* _hMaxJetEta;
  myTH1F* _hMinJetEta;
  //------------------------------------------------------
  // Missing Et Histograms
  //------------------------------------------------------
  //myTH1F* _hMETPt;
  myTH1F* _hMET;
  //------------------------------------------------------
  // W Histograms
  //------------------------------------------------------
  myTH1F* _hWTransverseMass;
  //myTH1F* _hWTransverseMass_LEP;
  //myTH1F* _hWTransverseMassPrime;
  //myTH1F* _hWPt;
  myTH1F* _hWCharge;
  //myTH1F* _hDeltaPhi;
    
  //------------------------------------------------------
  // Top Histograms
  //------------------------------------------------------
  myTH1F* _hBestTopMass;
  myTH1F* _hBTaggedTopMass;
  //myTH1F* _hDeltaBestTopMass;
  //myTH1F* _hDeltaBTaggedTopMass;
  myTH1F* _hLeadingJetTopMass;
    
  //------------------------------------------------------
  // Lepton Histograms
  //------------------------------------------------------
  myTH1F* _hLeptonPt;
  //myTH1F* _hLeptonEta;
  //myTH1F* _hLeptonPhi;
  //myTH1F* _hQTimesEtaLepton;
    
  //------------------------------------------------------
  // UnTagged Jet Histograms
  //------------------------------------------------------
  myTH1F* _hLeadingUntaggedJetPt;
  myTH1F* _hSecondUntaggedJetPt;
  myTH1F* _hLeadingUntaggedJetEta;
  myTH1F* _hQTimesEta;
  myTH1F* _hDeltaPt_tag_untag;
  myTH1F* _hDeltaRLeadingUntaggedJetLepton;
  //------------------------------------------------------
  // b-Tagged Jet Histograms
  //------------------------------------------------------
  myTH1F* _hLeadingBTaggedJetPt;
  myTH1F* _hSecondBTaggedJetPt;
  myTH1F* _hLeadingBTaggedJetEta;
  myTH1F* _hSecondBTaggedJetEta;
  myTH1F* _hDeltaRLeadingBTaggedJetLepton;
  myTH1F* _hDeltaRSecondBTaggedJetLepton;
  myTH1F* _hDeltaRBTaggedJet1BTaggedJet2;
  //------------------------------------------------------
  // Angular Variable Histograms
  //------------------------------------------------------
  myTH1F* _hCos_UntaggedJetLepton_BTaggedTop;
  //myTH1F* _hCos_Jet1Lepton_LeadingTop;
  //myTH1F* _hCos_Jet2Lepton_LeadingTop;
  //myTH1F* _hCos_Jet3Lepton_LeadingTop;
  //myTH1F* _hCos_Jet3Lepton_BestTop;
  //myTH1F* _hCos_Jet1Lepton_Lab;
  //myTH1F* _hCos_BTaggedJetLepton_Lab;
  //myTH1F* _hCos_BestJetLepton_Lab;
  //myTH1F* _hCos_Jet2Lepton_Lab;
  myTH1F* _hCos_Jet1AllJets_AllJets;
  myTH1F* _hCos_BTaggedJetAllJets_AllJets;
  myTH1F* _hCos_UntaggedJetAllJets_AllJets;
  myTH1F* _hCos_NotBestJetAllJets_AllJets;
  //myTH1F* _hCos_Jet2AllJets_AllJets;
  //myTH1F* _hCos_Jet1ZAxis_LeadingTop;
  //myTH1F* _hCos_Jet1ZAxis_Lab;
  //myTH1F* _hCos_Jet2ZAxis_Lab;
  myTH1F* _hCos_LeptonQZ_BestTop;
  //myTH1F* _hCos_LeptonZpl_BestTop;
  //myTH1F* _hCos_LeptonZmn_BestTop;
  //myTH1F* _hCos_LeptonZpl_LeadingTop;
  //myTH1F* _hCos_LeptonZmn_LeadingTop;
  myTH1F* _hCos_Jet1ThetaStar;

  

  myTH1F* _hHT;  // the sum of the ETs of the lepton, MET, and all jets.

  // NN output histograms
  myTH1F* _hNN_e_tb_wbb; 
  myTH1F* _hNN_e_tb_lepjets; 
  myTH2F* _hNN_e_tb_wbb_lepjets; 

  myTH1F* _hNN_e_tqb_wbb; 
  myTH1F* _hNN_e_tqb_lepjets; 
  myTH2F* _hNN_e_tqb_wbb_lepjets; 

  myTH2F* _hNN_e_tb_tqb_ttcut;  // tb-wbb versus tqb-wbb filter after tt cut of 0.4 


};


#endif


