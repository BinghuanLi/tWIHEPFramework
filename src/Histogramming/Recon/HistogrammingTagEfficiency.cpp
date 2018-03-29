/******************************************************************************
 * HistogrammingTagEfficiency.cpp                                                       *
 *                                                                            *
 * Books and fills histograms                                                 *
 * Used for events passing cuts applied in other classes                      *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of AnalysisMain class                              *
 *    HistogrammingTagEfficiency()              -- Parameterized Constructor            *
 *    ~HistogrammingTagEfficiency()             -- Destructor                           *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Fill histograms only (No Cuts)     *
 *    GetCutName()                      -- Returns "HistogrammingTagEfficiency"         *
 *                                                                            *
 * Private Data Members of this class                                         *
 *    myTH1F* _hNPvtx                   -- Hist of MET                          *
 *                                                                            *
 * History                                                                    *
 *      14 Nov 2006 - Created by R. Schwienhorst for ATLAS                    *
 *      20 Nov 2006 - Modified by Bernard Pope                                *
 *      21 Mar 2007 - RS: Fill from event container, add sumET, mex, mey      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Histogramming/Recon/HistogrammingTagEfficiency.hpp"
#include<iostream>

using namespace std;

/******************************************************************************
 * HistogrammingTagEfficiency::HistogrammingTagEfficiency(EventContainer *obj)                     *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Particle class                                                     *
 * Output: None                                                               *
 ******************************************************************************/
HistogrammingTagEfficiency::HistogrammingTagEfficiency(EventContainer *obj)
{
  SetEventContainer(obj);
  _bLooseTagCut = 0.5426;
  _bMediumTagCut = 0.8484;
} //HistogrammingTagEfficiency()

/******************************************************************************
 * HistogrammingTagEfficiency::~HistogrammingTagEfficiency()                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
HistogrammingTagEfficiency::~HistogrammingTagEfficiency()
{
  
} //HistogrammingTagEfficiency

/******************************************************************************
 * void HistogrammingTagEfficiency::BookHistogram()                                          *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void HistogrammingTagEfficiency::BookHistogram(){

  //Declare by 2D histograms
  _hLooseTagEff_bFlavNum = DeclareTH2F("hLooseTagEff_bFlavNum","Number of b flavour jets passing b-taggin requirements",100,0.,400.,20,0.,2.4);
  _hLooseTagEff_bFlavNum->SetXAxisTitle("JetPt");
  _hLooseTagEff_bFlavNum->SetYAxisTitle("Eta");

  _hLooseTagEff_bFlavDen = DeclareTH2F("hLooseTagEff_bFlavDwn","Number of b flavour jets",100,0.,400.,20,0.,2.4);
  _hLooseTagEff_bFlavDen->SetXAxisTitle("JetPt");
  _hLooseTagEff_bFlavDen->SetYAxisTitle("Eta");

  //Declare by 2D histograms
  _hLooseTagEff_cFlavNum = DeclareTH2F("hLooseTagEff_cFlavNum","Number of c flavour jets passing b-taggin requirements",100,0.,400.,20,0.,2.4);
  _hLooseTagEff_cFlavNum->SetXAxisTitle("JetPt");
  _hLooseTagEff_cFlavNum->SetYAxisTitle("Eta");

  _hLooseTagEff_cFlavDen = DeclareTH2F("hLooseTagEff_cFlavDwn","Number of c flavour jets",100,0.,400.,20,0.,2.4);
  _hLooseTagEff_cFlavDen->SetXAxisTitle("JetPt");
  _hLooseTagEff_cFlavDen->SetYAxisTitle("Eta");

  //Declare by 2D histograms
  _hLooseTagEff_lightFlavNum = DeclareTH2F("hLooseTagEff_lightFlavNum","Number of light flavour jets passing b-taggin requirements",100,0.,400.,20,0.,2.4);
  _hLooseTagEff_lightFlavNum->SetXAxisTitle("JetPt");
  _hLooseTagEff_lightFlavNum->SetYAxisTitle("Eta");

  _hLooseTagEff_lightFlavDen = DeclareTH2F("hLooseTagEff_lightFlavDwn","Number of light flavour jets",100,0.,400.,20,0.,2.4);
  _hLooseTagEff_lightFlavDen->SetXAxisTitle("JetPt");
  _hLooseTagEff_lightFlavDen->SetYAxisTitle("Eta");

  //Declare by 2D histograms
  _hMediumTagEff_bFlavNum = DeclareTH2F("hMediumTagEff_bFlavNum","Number of b flavour jets passing b-taggin requirements",100,0.,400.,20,0.,2.4);
  _hMediumTagEff_bFlavNum->SetXAxisTitle("JetPt");
  _hMediumTagEff_bFlavNum->SetYAxisTitle("Eta");

  _hMediumTagEff_bFlavDen = DeclareTH2F("hMediumTagEff_bFlavDwn","Number of b flavour jets",100,0.,400.,20,0.,2.4);
  _hMediumTagEff_bFlavDen->SetXAxisTitle("JetPt");
  _hMediumTagEff_bFlavDen->SetYAxisTitle("Eta");

  //Declare by 2D histograms
  _hMediumTagEff_cFlavNum = DeclareTH2F("hMediumTagEff_cFlavNum","Number of c flavour jets passing b-taggin requirements",100,0.,400.,20,0.,2.4);
  _hMediumTagEff_cFlavNum->SetXAxisTitle("JetPt");
  _hMediumTagEff_cFlavNum->SetYAxisTitle("Eta");

  _hMediumTagEff_cFlavDen = DeclareTH2F("hMediumTagEff_cFlavDwn","Number of c flavour jets",100,0.,400.,20,0.,2.4);
  _hMediumTagEff_cFlavDen->SetXAxisTitle("JetPt");
  _hMediumTagEff_cFlavDen->SetYAxisTitle("Eta");

  //Declare by 2D histograms
  _hMediumTagEff_lightFlavNum = DeclareTH2F("hMediumTagEff_lightFlavNum","Number of light flavour jets passing b-taggin requirements",100,0.,400.,20,0.,2.4);
  _hMediumTagEff_lightFlavNum->SetXAxisTitle("JetPt");
  _hMediumTagEff_lightFlavNum->SetYAxisTitle("Eta");

  _hMediumTagEff_lightFlavDen = DeclareTH2F("hMediumTagEff_lightFlavDwn","Number of light flavour jets",100,0.,400.,20,0.,2.4);
  _hMediumTagEff_lightFlavDen->SetXAxisTitle("JetPt");
  _hMediumTagEff_lightFlavDen->SetYAxisTitle("Eta");
} //BookHistogram

/******************************************************************************
 * Bool_t HistogrammingTagEfficiency::Apply()                                         *
 *                                                                            *
 * Fill histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t HistogrammingTagEfficiency::Apply()
{
  //cout<<"Begin of HistogrammingTagEfficiency::Apply()"<<endl;
  
  EventContainer *evc = GetEventContainer();

  //std::cout << evc->alljets.size() << " " << evc->taggedJets.size() << std::endl;
  
  //Loop over the jet collection and fill in the efficiency histograms as required
  for (auto const & jet : evc->jets){
    if (fabs(jet.Eta()) > 2.4) continue;
    //    std::cout << jet.hadronFlavour() << " " << jet.GetbDiscriminator() << " " << jet.IsTagged() << " " << jet.tagged() << std::endl;
    switch (int(jet.hadronFlavour())){
    case 5: //b flavour quark
      _hLooseTagEff_bFlavDen->FillWithoutWeight(jet.Pt(),jet.Eta());
      _hMediumTagEff_bFlavDen->FillWithoutWeight(jet.Pt(),jet.Eta());
      if (jet.GetbDiscriminator() > _bLooseTagCut) _hLooseTagEff_bFlavNum->FillWithoutWeight(jet.Pt(),jet.Eta());
      if (jet.GetbDiscriminator() > _bMediumTagCut) _hMediumTagEff_bFlavNum->FillWithoutWeight(jet.Pt(),jet.Eta());
      break;
    case 4:
      _hLooseTagEff_cFlavDen->FillWithoutWeight(jet.Pt(),jet.Eta());
      _hMediumTagEff_cFlavDen->FillWithoutWeight(jet.Pt(),jet.Eta());
      if (jet.GetbDiscriminator() > _bLooseTagCut) _hLooseTagEff_cFlavNum->FillWithoutWeight(jet.Pt(),jet.Eta());
      if (jet.GetbDiscriminator() > _bMediumTagCut) _hMediumTagEff_cFlavNum->FillWithoutWeight(jet.Pt(),jet.Eta());
      break;
    default:
      _hLooseTagEff_lightFlavDen->FillWithoutWeight(jet.Pt(),jet.Eta());
      _hMediumTagEff_lightFlavDen->FillWithoutWeight(jet.Pt(),jet.Eta());
      if (jet.GetbDiscriminator() > _bLooseTagCut) _hLooseTagEff_lightFlavNum->FillWithoutWeight(jet.Pt(),jet.Eta());
      if (jet.GetbDiscriminator() > _bMediumTagCut) _hMediumTagEff_lightFlavNum->FillWithoutWeight(jet.Pt(),jet.Eta());
      
    }
  }

  //cout<<"End of HistogrammingTagEfficiency::Apply()"<<endl;
  return kTRUE;  
  
} //Apply












