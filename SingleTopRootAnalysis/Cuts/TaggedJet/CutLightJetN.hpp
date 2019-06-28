/******************************************************************************
 * CutLightJetN.hpp                                                                *
 *                                                                            *
 * Cuts on number of jets in an event                                         *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutLightJetN class                                   *
 *    CutLightJetN()                         -- Parameterized Constructor          *
 *    ~CutLightJetN()                        -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutLightJetN"                  *
 *                                                                            *
 * Private Data Members of CutLightJetN                                            *
 *    myTH1F* _hJetNumberBefore         -- Hist of Num of jets before cuts    *
 *    myTH1F* _hJetNumberAfter          -- Hist of Num of jets before cuts    *
 *    Int_t _JetNumberMin;              -- Minimum number of jets to require  *
 *    Int_t _JetNumberMax;              -- Maximum number of jets allowed     *
 *                                                                            *
 * History                                                                    *
 *       7 Nov 2006 - Created by R. Schwienhorst for ATLAS                    *
 *      10 Nov 2006 - Modified by P. Ryan - cleanup and reorganized           *
 *      11 Jan 2007 - Modified by P. Ryan - cleanup and reorganized           *
 *****************************************************************************/

#ifndef CutLightJetN_h
#define CutLightJetN_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class CutLightJetN : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLightJetN(EventContainer *EventContainerObj, Int_t nJetsDefault = -1);
  
  // Destructor
  ~CutLightJetN();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLightJetN"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hJetNumberBefore;    // Histogram number of jets before the cut
  myTH1F* _hJetNumberAfter;     // Histogram number of jets after the cut

  // Cut parameters
  Int_t _JetNumberMin;           // Minimum number of jets to require
  Int_t _JetNumberMax;           // Maximum number of jets allowed

};


#endif







