#ifndef mvaTool_h
#define mvaTool_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>

#include <TLorentzVector.h>

#include <iostream>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <tuple>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TThread.h"

#include "TMVAGui.C"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"




class mvaTool {
 public :
  mvaTool(Int_t channel = 0);
  //  ~mvaTool();

  void doBothTraining(TString inDir);
  void doTraining(TString inDir, bool isttbar);
  void doReading(TString sampleName, TString inDir = "tW",TString outDir = "mvaOutput/", bool isData = false);
  void doReadingNoMVA(TString sampleName, TString inDir = "tW",TString outDir = "mvaOutput/", bool isData = false);

  void setChannel(Int_t channel){_channel = channel;};
  //  void doReading();

 private:

  Int_t _channel; //The channel we want to read
  std::vector<TString> regionNames;

  //Used to loop over things
  void processMCSample(TString sampleName,TString inDir,TString outDir, float * treevars, bool isData, bool doMVA = true);
  void loopInSample(TString dirName, TString sampleName, float* treevars, bool isData, bool doMVA = true);
  void createHists(TString sampleName);
  void fillHists(TString sampleName, float* treevars, double mvaValue, double mvawJets, double theweight, float met, float mtw, int theChannel);
  void saveHists(std::vector<TFile *> outFile);
  void setbTagVars(TChain* theTree); 

  void makeStatVariationHists(TString sampleName,std::vector<TFile*> outputFile);

  std::tuple<float,float> calculatebTagSyst(float,std::vector<float>);
  std::tuple<float,float> calculatebMistagSyst(float,std::vector<float>);

  std::map<TString,std::vector<std::vector<TH1F*> > > theHistoMap;
  std::map<TString,std::vector<std::vector<TH1F*> > > bdtHistoMap;
  std::map<TString,std::vector<TH2F*> > the2DHistoMap;

  std::vector<TString > varList;
  std::vector<TString > samplelist;
  std::vector<TString > systlist;
  TString baseName;
  std::vector<float> bTagSysts;

  TMVA::Reader *reader;

  float theweight;
  float mvaValue;
  float mvawJetsValue;
};

#endif
