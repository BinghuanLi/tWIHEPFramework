/******************************************************************************
 * EventContainer.cpp                                                         *
 *                                                                            *
 * Read in variables from EventTree and put them into an Object               *
 *                                                                            *
 * Public Members of EventContainer    class                                  *
 *    EventContainer()                  -- Default Constructor                *
 *    ~EventContainer()                 -- Destructor                         *
 *    GetSourceName()                   -- Get name of source being run on    *
 *    GetSourceNumber()                 -- Get number of source being run on  *
 *    GetTargetTopMass()                -- Get Top Quark Mass                 *
 *    SetSourceName()                   -- Set name of source being run on    *
 *    SetSourceNumber()                 -- Set number of source being run on  *
 *    SetTargetTopMass()                -- Set Top Quark Mass                 *
 *    Initialize()                      -- Initialize class                   *
 *    MakeTopQuarks()                   -- Reconstruct Top in several ways    *
 *    GetNextEvent()                    -- Set up particles for next event    *
 *    SetEventCount()                   -- Set counter for specific event     *
 *    GetCollectionTree()               -- Get the collection tree            *
 *    GetEventTree()                    -- Get the event tree                 *
 *    GetTruthTree()                    -- Get the truth tree                 *
 *    GetTruthAllTree()                    -- Get the truth tree              *
 *    GetTriggerTree()                  -- Get the trigger tree               *
 *    GetFastSimTree()                  -- Get the fastsim tree               *
 *    GetDebugLevel()                   -- Get debug level                    *
 *    SetDebugLevel()                   -- Set debug level                    *
 *    SetDoTrigger()                    -- Set if trigger tree                *
 *    SetDoTruthAll()                   -- Set if TruthAll tree               *
 *    SetDoTruth()                      -- Set if Truth tree                  *
 *    DoTrigger()                       -- If trigger tree                    *
 *    DoTruthAll()                      -- If TruthAll tree                   *
 *    DoTruth()                         -- If Truth tree                      *
 *    GetEventWeight()                  -- Get Event Weight                   *
 *    GetOutputEventWeight()            -- Get Output EventWeight             *
 *    GetTreeEventWeight()              -- Get Tree Event Weight              *
 *    GetGlobalEventWeight()            -- Get Global EventWeight             *
 *    SetGlobalEventWeight()            -- Set global event weight            *
 *    SetOutputEventWeight()            -- Set output event weight            *
 *    GetConfig()                       -- Get Configuration                  *
 *    ApplyJESShift()                   -- scale jet energies                 * 
 *                                                                            *
 *    Int_t ReadEvent()                 -- Create TLorentz Vectors            *
 *    Bool_t CreateFinalState()         -- Create final state particles       *
 *    Int_t runNumber                   -- Run number from the root tree      *
 *    Int_t eventNumber                 -- Event number from the root tree    *
 *    vector<Electron> electrons        -- Electron Vector                    *
 *    vector<Muon>     muons            -- Muon Vector                        *
 *    vector<Muon>     isolatedmuons    -- Isolated Muon Vector               *
 *    vector<Muon>     unisolatedmuons  -- UnIsolated Muon Vector             *
 *    vector<Tau>      looseTaus             -- Tau Vector                         *
 *    vector<Tau>      taus             -- Tau Vector                         *
 *    vector<Jet>      jets             -- Jet Vector                         *
 *    vector<Jet>      taggedJets       -- taggedJet Vector                   *
 *    vector<Jet>      untaggedJets     -- untaggedJet Vector                 *
 *    vector<Jet>       bLabeledJets    -- jet id'ed with MC B quark          *
 *    vector<Jet>       cLabeledJets    -- jet id'ed with MC C quark          *
 *    vector<Jet>      tauLabeledJets   -- jet id'ed with MC tau              *
 *    vector<Jet> lightQuarkLabeledJets -- jet not id'ed with MC B, C, or tau *
 *    vector<MCParticle> MCParticles    -- MC Particle Vector                 *
 *    vector<MCMuon>   MCmuons          -- MC Muon Vector                     *
 *    vector<MCElectron>   MCElectrons  -- MC Electron Vector                 *
 *    vector<MCTau>   MCTaus            -- MC Tau Vector                      *
 *    vector<MCJet>   MCJets            -- MC Jet Vector                      *
 *    vector<MCJet>   MCBJets           -- MC BJet Vector                     *
 *    vector<MCJet>   MCCJets           -- MC CJet Vector                     *
 *    vector<MCJet>   MCLightQuarkJets  -- MC LightJetJet Vector              *
 *    vector<MCTop>   MCTops            -- MC Top Vector                      *
 *    vector<MCW>     MCWs              -- MC W Vector                        * 
 *    vector<MCAllParticle> MCAllParticles -- MCAllParticle Vector            *
 *    vector<MCAllMuon> MCAllMuons      -- MCAllMuon Vector                   *
 *    vector<MCAllElectron> MCAllElectrons -- MCAll Electron Vector           *
 *    vector<MCAllJet> MCAllJets         -- MCAll Jet Vector                  *
 *    vector<MCAllTau> MCAllTaus         -- MCAll Tau Vector                  *
 *    vector<MCAllChargedPion> MCAllChargedPions -- MCAll Charged Pion Vector *
 *    vector<MCAllChargedK> MCAllChargedKs -- MCAll Charged K Vector          *
 *                                                                            *
 * Protected Members of EventContainer class                                  *
 *    Int_t debugLevel                  -- Debug level                        *
 *    TEnv _config                      -- Used to read configuration         *
 *                                                                            *
 * Private Members of EventContainer class                                    *
 *    Double_t _targetTopMass           -- Target top mass                    *
 *    CollectionTree *_collectionTree   -- Collection tree                    *
 *    EventTree *_eventTree             -- Event tree                         *
 *    TruthTree *_thruthTree            -- Truth tree                         *
 *    Int_t    _eventCount              -- Location in event chain            *
 *    TString  _sourceName              -- Name of source being read          *
 *    TString _sourceNumber             -- Number of source being read        *
 *    Double_t _globalEventWeight       -- Global Event Weight                *
 *    Double_t _treeEventWeight         -- Tree Event Weight                  *
 *    Double_t _outputEventWeight       -- Output Event Weight                *
 *                                                                            *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutJetN"                  *
 *                                                                            *
 * Private Data Members of CutJetN                                            *
 *    myTH1F* _hNJetsBefore              -- Hist of Num of jets before cuts   *
 *    myTH1F* _hNJetsAfter               -- Hist of Num of jets before cuts   *
 *    Int_t _nJetsMin;                   -- Minimum number of jets to require *
 *    Int_t _nJetsMax;                   -- Maximum number of jets allowed    *
 *                                                                            *
 * History                                                                    *
 *      16 June 2015 - Created by Huaqiao ZHANG(zhanghq@ihep.ac.cn) for CMS   *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"
#include <iostream>
#include <string>
#include <fstream>

#include <TLeaf.h>

#include "SingleTopRootAnalysis/Base/Histograms/utils.hpp"

using namespace std;
//using namespace Analysis;
// Integrate classes into the Root system
ClassImp(EventContainer)

//-----------------------------------------------------------------------------------------
// Get the next event.
// It reads in the next event from the current chain and 
// Creates final state particles.
// This method returns -1 when there are no more events.
// It returns the total event count if successful.
//
Int_t EventContainer::GetNextEvent(){

  //cout << "<EventContainer::GetNextEvent Start> " << endl;
  Int_t countOffSet=0;
  if (! DoFastSim()   && _eventTree      == NULL) return -1;
  if (DoTruth()       && _truthTree      == NULL) return -1;
  if (DoFastSim()     && _fastSimTree    == NULL) return -1;

  // now Set things up
  Int_t bytesReadTru;
  Int_t bytesReadEv;

  // ************************
  // FastSim
  // ************************
  if(DoFastSim()) {
    bytesReadEv = _fastSimTree->fChain->GetEntry(_eventCount);
  } else {
    // normal running, get the next eventin the event tree
    bytesReadEv = _eventTree->fChain->GetEntry(_eventCount);
  } 

  if(0 == bytesReadEv) {
    if(DoFastSim()){
      cout << "<EventContainer> Read 0 bytes from fast sim tree." << endl;
      return -1;
    }else  {
      cout << "<EventContainer> Read 0 bytes from event tree." << endl;
      return -1;
    }
  } //if
  // ************************
  // Truth
  // ************************
  if(DoTruth()) {
    Int_t bytesReadTruth = _truthTree->fChain->GetEntry(_eventCount);
    if(0 == bytesReadTruth) {
    cout << "<EventContainer> Read 0 bytes from truth tree." << endl;
    return -1;
    } //if
  } //if
  
  // ************************
  // Skimming
  // ************************
  if(DoSkim()){
    Int_t bytesReadTri =0;
    bytesReadTri = _eventTree->fChain->GetEntry(_eventCount);
    if(0 == bytesReadTri) {
      cout << "<EventContainer> Read 0 bytes from LooseTopInputs tree." << endl;
      return -1;
    }
    if (_truthTree!=NULL){
      bytesReadTri = _truthTree->fChain->GetEntry(_eventCount);
      if(0 == bytesReadTri) {
	cout << "<EventContainer> Read 0 bytes from Truth tree." << endl;
	return -1;
      }
    }

  }

  // Create 4-vectors
  //cout << "<EventContainer::GetNextEvent::ReadEvent Start> " << endl;
  ReadEvent();         //The object selections and corrections are here
  //cout << "<EventContainer::GetNextEvent::CreateFinalState Start> " << endl;
  CreateFinalState();  // the event selections are here
  //cout << "<EventContainer::GetNextEvent::MakeTopQuarks Start> " << endl;
  MakeTopQuarks();
  //cout << "<EventContainer::GetNextEvent::MakeTopQuarks End> " << endl;
  // set ttH flags
  set_TTHFlags();
  // and finally increment the internal event counter
  _eventCount++;
  if(GetIsFirstEvent() == true) SetIsFirstEvent(false); // not the first event
  return(countOffSet + _eventCount-1);
} // end of GetNextEvent
  
/******************************************************************************
 * EventContainer::EventContainer()                                           *
 *                                                                            *
 * Default Constructor                                                        *
 * Initializes many private data members                                      *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
EventContainer::EventContainer(): 
  //_collectionTree(NULL), 
  _eventTree(NULL), _truthTree(NULL), 
  _eventCount(0),   _targetTopMass(175.),
  _debugLevel(0),   _doFastSim(false),_doSkim(false),
  _sourceName("NONE"),
  _globalEventWeight(1.), _treeEventWeight(1.), _outputEventWeight(1.),_EventPileupWeight(-1),
  _EventPileupMinBiasUpWeight(-1),_EventPileupMinBiasDownWeight(-1),
  _config("Configuration"), _JESconfig("JESConfiguration"),_jesError(0.), _jesShift(0), _bTagAlgo("default"), _bTagCut(999), _misTagCut(999), jeteoverlap(kFALSE),closeindex(999),ejordr(999), bestjetdr(999), _isFirstEvent(true), isSimulation(kTRUE), _badJetEvent(kFALSE),  _celloutShift(0),_softjetShift(0),_pileupShift(0),_larShift(0),_metShift(0), _JESconfigread(false),_jesUShift(0),_jesPtShift(0),_jesEtaShift(0),_useUnisolatedLeptons(kFALSE),_trigID(0)
{
 
} //EventContainer()


/******************************************************************************
 * EventContainer::~EventContainer()                                          *
 *                                                                            *
 * Destructor                                                                 *
 * Sets pointers to NULL                                                      *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
EventContainer::~EventContainer()
{

  // Event Tree
  if(_eventTree) delete _eventTree;
  _eventTree = NULL;

  // Truth Tree
  if(_truthTree) delete _truthTree;
  _truthTree = NULL;

  // Fast Sim Tree
  // This causes a seg fault - don't know why
  //if(_fastSimTree) delete _fastSimTree;
  //_fastSimTree = NULL;

} //~EventContainer()

/******************************************************************************
 * void EventContainer::Initialize()                                          *
 *                                                                            *
 * Initialize class                                                           *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
//void EventContainer::Initialize(CollectionTree* collectionTree,EventTree* eventTree, TruthTree* truthTree)
//
void EventContainer::Initialize( EventTree* eventTree, TruthTree* truthTree)
{

  _eventTree       = eventTree;
  _truthTree       = truthTree;
//  // now Set up the internal variables:
  SetIsFirstEvent(true);
  actualIntPerXing = 0;
  averageIntPerXing = 0 ;
//  Pvtxall_n = -999;
  isSimulation = kTRUE;

  _eventCount = 0;
  electrons.clear();
  tightElectrons.clear();
  vetoElectrons.clear();
  ptetaElectrons.clear();
  isolatedElectrons.clear();
  unIsolatedElectrons.clear();
  muons.clear();
  tightMuons.clear();
  vetoMuons.clear();
  ptetaMuons.clear();
  isolatedMuons.clear();
  unIsolatedMuons.clear();
  looseLeptons.clear();
  fakeLeptons.clear();
  tightLeptons.clear();
  looseTaus.clear();
  taus.clear();
  jets.clear();
  alljets.clear();
  taggedJets.clear();
  unTaggedJets.clear();
  bLabeledJets.clear();
  cLabeledJets.clear();
  tauLabeledJets.clear();
  lightQuarkLabeledJets.clear();
  neutrinos.clear();
  MCParticles.clear();
  MCMuons.clear();
  MCElectrons.clear();
  MCTaus.clear();
  MCJets.clear();
  MCBJets.clear();
  MCCJets.clear();
  MCLightQuarkJets.clear();
  MCLightJets.clear();
  MCTops.clear();
  MCWs.clear();
  MCHs.clear();
  MCZs.clear();
  MCPhotons.clear();
  MCNeutrinos.clear();
//  MCBQuarks.clear();
//  MCCQuarks.clear();
//
//  JER tool  
//  myJER = new JERProvider("AntiKt4TopoJES", "Truth", "config/JER/JERProviderPlots.root");
//  myJER->init();//for JER if not flat shift

//  electron energy scale and resolution
//  int elecEnergyScale = _config.GetValue("ObjectID.ElecEnergyScale.shift",0);
//  int elecEnergySmear = _config.GetValue("ObjectID.ElecEnergySmear.shift",0);
//  string mcWithConstantTerm = _config.GetValue("ObjectID.ElecEnergySmear.mcWithConstantTerm","True");
//  useElecEnergyScale = elecEnergyScale;
//  useElecEnergySmear = elecEnergySmear;

//  if(mcWithConstantTerm=="True") {
//    useMCWithConstantTerm = true;
//  } else {
//    useMCWithConstantTerm = false;
//  }
//
//  //taggername = "SV0";
//  taggername = "Jet1FitterCOMBNN";
//  CalibROOT = new CalibrationDataInterfaceROOT(taggername, "config/btag/BTagCalibration.env", ""); 
//  CalibVar.jetAuthor = "AntiKt4Topo";
//  uncertainty = Total;
//
  
  // Check for any systematic uncertainties we may be calculating
  _metShift = _config.GetValue("Systs.metShift",0);
  _channelName = _config.GetValue("ChannelName","");
  _sync = _config.GetValue("SyncType",0);
  TTHLep_2Mu =0;
  TTHLep_2Ele =0;
  TTHLep_MuEle =0;
  TTHLep_2L =0;
  metLD = -999.;
  mht = -999.;
  mhtT = -999.;
  mht_met = -999.;
  mhtT_met = -999.;
  massL = -999.;
  massL_SFOS = -999.;
  mass_diele = -999.;
  HadTop_BDT = -999.;
  set_hadTopMVA();
  set_ttHDiLepMVA();

  return;
} //Initialize()

/******************************************************************************
 * void EventContainer::SetupObjectDefinitions(TEnv config)                   *
 *                                                                            *
 * Sets up the different object definitions for each object                   *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void EventContainer::SetupObjectDefinitions(){
  newMuon.SetCuts(GetConfig(),"Tight");
  newMuon.SetCuts(GetConfig(),"All");
  newMuon.SetCuts(GetConfig(),"UnIsolated");
  newMuon.SetCuts(GetConfig(),"Veto");

  newElectron.SetCuts(GetConfig(),"Tight");
  newElectron.SetCuts(GetConfig(),"All");
  newElectron.SetCuts(GetConfig(),"Veto");
  newElectron.SetCuts(GetConfig(),"UnIsolated");

  newLepton.SetCuts(GetConfig(),"MuTight");
  newLepton.SetCuts(GetConfig(),"MuFake");
  newLepton.SetCuts(GetConfig(),"MuLoose");
  newLepton.SetCuts(GetConfig(),"EleTight");
  newLepton.SetCuts(GetConfig(),"EleFake");
  newLepton.SetCuts(GetConfig(),"EleLoose");
  
  newTau.SetCuts(GetConfig());
  newJet.SetCuts(GetConfig());

  newLepton.set_lepMVAreader(GetConfig());
  newJet.set_HjMVAreader(GetConfig());
}

/******************************************************************************
 * void EventContainer::SetUseUnisolatedLeptons(                              *
 *           Bool_t useUnisolatedLeptons, int whichtrig)                      *
 *                                                                            *
 * Used to switch between QCD estimation and non. This is important for       *
 * the jet cleaning algorithm						      *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/

void EventContainer::SetUseUnisolatedLeptons(const Bool_t& useUnisolatedLeptons, int whichtrig){
  _useUnisolatedLeptons = useUnisolatedLeptons;
  _trigID = whichtrig;
  electronsToUsePtr = &tightElectrons;
  muonsToUsePtr = &tightMuons;
  leptonsToUsePtr = &tightLeptons;
  if (_trigID == 0 && _useUnisolatedLeptons){
    electronsToUsePtr = &unIsolatedElectrons;
  }
  else if (_trigID == 1 && useUnisolatedLeptons){
    muonsToUsePtr = &unIsolatedMuons;
  }
  
  electronsVetoPtr = &vetoElectrons;
  muonsVetoPtr = &vetoMuons;
  looseleptonsVetoPtr = &looseLeptons;
  fakeleptonsVetoPtr = &fakeLeptons;
  tausVetoPtr = &looseTaus;
  
  mcParticlesPtr = &MCParticles;

  //For the synch excercise we want it to always be tight leptons, so I'm gonna add here the ability to just make it all tight.
  //  if (GetChannelName() == "ee" || GetChannelName() == "emu" || GetChannelName() == "mumu"){
  // }
} //SetUseUnisolatedLeptons

/******************************************************************************
 * void EventContainer::InitializeFastSim()                                   *
 *                                                                            *
 * Initialize class                                                           *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
//void EventContainer::InitializeFastSim(FastSimTree* fsTree, TruthTree* truthTree)
//{
//  return;
//} //Initialize()


/******************************************************************************
 * Int_t EventContainer::ReadEvent()                                          *
 *                                                                            *
 * Fill objects with event info                                               *
 *                                                                            *
 * Input:  None                                                               *
 * Output: Return 0                                                           *
 ******************************************************************************/
Int_t EventContainer::ReadEvent()
{
  // Set the event weight if there is any
  if(DoFastSim()) {
    // Will have to be updated when we have a fast sim tree
    _treeEventWeight = _fastSimTree -> eventWeight;
    runNumber   = _fastSimTree      -> runNumber;
    eventNumber = _fastSimTree      -> eventNumber;
    larError = 5;
    actualIntPerXing = 0;
    averageIntPerXing = 0 ;
    distns = -999;
    distbunch = -999;
    bcid = -999;
    safejetevent= -999;
    safejeteventup= -999;
    safejeteventdown= -999;
  }  else {
    _treeEventWeight = 1.0;
    runNumber          = _eventTree -> EVENT_run;
    eventNumber        = _eventTree -> EVENT_event;
    actualIntPerXing   = 1;//_eventTree -> 
    averageIntPerXing  = 1;//_eventTree -> 
    bcid               = 1;//_eventTree -> 
    distns = -999;
    distbunch = -999;
    safejetevent= -999;
    safejeteventup= -999;
    safejeteventdown= -999;
  }
  isSimulation = kTRUE;
  _badJetEvent = kFALSE;

  // Reset all of the particle vectors
  electrons.clear();
  tightElectrons.clear();
  vetoElectrons.clear();
  ptetaElectrons.clear();
  isolatedElectrons.clear();
  unIsolatedElectrons.clear();

  muons.clear();
  tightMuons.clear();
  vetoMuons.clear();
  ptetaMuons.clear();
  isolatedMuons.clear();
  unIsolatedMuons.clear();

  looseLeptons.clear();
  fakeLeptons.clear();
  tightLeptons.clear();
  looseTaus.clear();
  taus.clear();

  jets.clear();
  alljets.clear();
  taggedJets.clear();
  unTaggedJets.clear();
  bLabeledJets.clear();
  cLabeledJets.clear();
  tauLabeledJets.clear();
  lightQuarkLabeledJets.clear();
  neutrinos.clear();
  MCParticles.clear();
  MCMuons.clear();
  MCElectrons.clear();
  MCTaus.clear();
  MCJets.clear();
  MCBJets.clear();
  MCCJets.clear();
  MCLightQuarkJets.clear();
  MCLightJets.clear();
  MCTops.clear();
  MCWs.clear();
  MCHs.clear();
  MCZs.clear();
  MCPhotons.clear();
  MCNeutrinos.clear();

  metLD = -999.;
  mht = -999.;
  mhtT = -999.;
  mht_met = -999.;
  mhtT_met = -999.;
  massL = -999.;
  massL_SFOS = -999.;
  mass_diele = -999.;
  HadTop_BDT = -999.;
  ////////////////////////////////////////////////////
  // Fill objects
  ////////////////////////////////////////////////////

  bool useObj;  // decide whether to transfer this into our list of objects 

  //No cuts on MC particles, yet
  if(DoTruth()){
  } //if DoTruth
  // ***************************************************
  // Then from either the reconstruction tree or fast sim
  if(DoFastSim()) {
  } // end of filling from fastsim tree
  // ***************************************************
  // Reconstructed
  else {
    Int_t SourceNumber = GetSourceNumber();
    if(SourceNumber<20000)isSimulation = kTRUE;//_eventTree->isSimulation;
    else isSimulation = kFALSE;
    _badJetEvent = kFALSE;
    //must be done for each event
    // Electrons, Jets, Muons, missingEt
    Electrons_tlv.clear();
    Electrons_tlv_scaled.clear();
    Jets_tlv_scaled.clear();
    Jets_tlv.clear();
    Jets_JESup_tlv.clear();
    Jets_emscale_tlv.clear();
    Muons_tlv_scaled.clear();
    Muons_tlv.clear();
    Muons_ms_tlv_scaled.clear();
    Muons_ms_tlv.clear();
    Muons_track_tlv_scaled.clear();
    Muons_track_tlv.clear();
    missingEt = -888;
    ///////////////////////////////////////////  
    // Number of vertices
    ///////////////////////////////////////////  
    int ncount = 0;
    //for(int i=0; i<_eventTree->Vertex_n; i++){
    //  //events will be rejected if this isn't true for i == 0 (cut class applied later) but other vertices still allowed
    //  if((_eventTree->Vertex_type->at(i) == 1 || _eventTree->Vertex_type->at(i) == 3) && _eventTree->Vertex_track_n->at(i) >= 5) ncount++;
    //  //  for(int i=0; i<_eventTree->Vertex_n; i++){
    //  // if(_eventTree->Vertex_track_n->at(i) > 4) ncount++;
    //}
    //nPvtx = ncount;
    //Pvtxall_n = _eventTree->Vertex_n;

    ///////////////////////////////////////////
    // Fill MET info 
    ///////////////////////////////////////////
    // Should I update this to use PUPPI information?!?
    missingEt = _eventTree->Met_type1PF_pt;
    missingEx = _eventTree->Met_type1PF_px;
    missingPhi = _eventTree->Met_type1PF_phi;
    missingEy = _eventTree->Met_type1PF_py;

    missingEt_xy = _eventTree->Met_type1PFxy_pt;
    missingEx_xy = _eventTree->Met_type1PFxy_px;
    missingPhi_xy = _eventTree->Met_type1PFxy_phi;
    missingEy_xy = _eventTree->Met_type1PFxy_py;

    passesMETFilters = _eventTree->Flag_METFilters;

    //Fill pvtx information
    nPvtx = _eventTree->nBestVtx;
    trueInteractions = _eventTree->trueInteractions;
    npuVertices = _eventTree->npuVertices;
    
    // Systematic variations on met to be re-calculated here.
    if (_metShift != 0){
      float oldEt = missingEt;
      missingEt = (_metShift == 1) ? _eventTree->Met_type1PF_shiftedPtUp : _eventTree->Met_type1PF_shiftedPtDown;

      float ratioSF = missingEt/oldEt;
      missingEx *= ratioSF;
      missingEy *= ratioSF;

      missingEt_xy *= ratioSF;
      missingEx_xy *= ratioSF;
      missingEy_xy *= ratioSF;
    }

    missingEtVec.SetPtEtaPhiE(missingEt,0.,missingPhi,missingEt);
    missingEtVec_xy.SetPtEtaPhiE(missingEt_xy,0.,missingPhi_xy,missingEt_xy);


    ///////////////////////////////////////////
    // Muons
    ///////////////////////////////////////////  
    //NOTE: although the missingEt is sent into all the muon loops, it is ONLY shifted in the all muons loop
    // All muon
    Bool_t amu = kFALSE;
    for(Int_t io = 0;io < _eventTree -> Muon_pt->size(); io++) {
      newMuon.Clear();
      useObj = newMuon.Fill(_eventTree, io,"All", isSimulation);
      if(useObj) {
	muons.push_back(newMuon);
      } // if useObj

      newMuon.Clear();
      useObj = newMuon.Fill(_eventTree, io,"Tight", isSimulation);
      if(useObj) {
        tightMuons.push_back(newMuon);
      } // if useObj

      newMuon.Clear();
      useObj = newMuon.Fill(_eventTree, io,"Veto", isSimulation);
      if(useObj) {
        vetoMuons.push_back(newMuon);
      } // if useObj

      newMuon.Clear();
      useObj = newMuon.Fill(_eventTree, io,"UnIsolated", isSimulation);
      if(useObj) {
	    unIsolatedMuons.push_back(newMuon);
      } // if useObj

      newLepton.Clear();
      useObj = newLepton.Fill(*muonsVetoPtr, _eventTree, io,"MuLoose", isSimulation, SourceNumber ,13);// 13 means Muon
      if(useObj) {
	    looseLeptons.push_back(newLepton);
        if(!amu && _sync == 11){
          std::cout << eventNumber << " " << newLepton.Pt() << " " << newLepton.Eta() << " " << newLepton.Phi() << " "<< newLepton.E() << " "<<newLepton.pdgId()<<" "<< newLepton.charge()<< " "<< newLepton.lepjetchtrks()<<" "<< newLepton.miniIsoRel()<< " "<< newLepton.miniIsoCh()<< " "<< newLepton.miniIsoPUsub() << " "<< newLepton.ptrel()<< " "<< newLepton.jetcsv()<< " "<< newLepton.jetptratio() << " "<< newLepton.IP3Dsig()<< " "<< newLepton.dxy() << " " << newLepton.dz() << " "<< newLepton.mvaValue_HZZ() << " " << newLepton.BDT() << std::endl;
          amu = kTRUE;
        }
      } // if useObj
      
      newLepton.Clear();
      useObj = newLepton.Fill(*muonsVetoPtr, _eventTree, io,"MuFake", isSimulation, SourceNumber ,13);// 13 means Muon
      if(useObj) {
	    fakeLeptons.push_back(newLepton);
        if(!amu && _sync == 12){
          std::cout << eventNumber << " " << newLepton.Pt() << " " << newLepton.Eta() << " " << newLepton.Phi() << " "<< newLepton.E() << " "<<newLepton.pdgId()<<" "<< newLepton.charge()<< " "<< newLepton.lepjetchtrks()<<" "<< newLepton.miniIsoRel()<< " "<< newLepton.miniIsoCh()<< " "<< newLepton.miniIsoPUsub() << " "<< newLepton.ptrel()<< " "<< newLepton.jetcsv()<< " "<< newLepton.jetptratio() << " "<< newLepton.IP3Dsig()<< " "<< newLepton.dxy() << " " << newLepton.dz() << " "<< newLepton.segmentCompatibility() << " " << newLepton.BDT() << std::endl;
          amu = kTRUE;
        }
      } // if useObj
       
      newLepton.Clear();
      useObj = newLepton.Fill(*muonsVetoPtr, _eventTree, io,"MuTight", isSimulation, SourceNumber ,13);// 13 means Muon
      if(useObj) {
	    tightLeptons.push_back(newLepton);
        if(!amu && _sync == 13){
          std::cout << eventNumber << " " << newLepton.Pt() << " " << newLepton.Eta() << " " << newLepton.Phi() << " "<< newLepton.E() << " "<<newLepton.pdgId()<<" "<< newLepton.charge()<< " "<< newLepton.lepjetchtrks()<<" "<< newLepton.miniIsoRel()<< " "<< newLepton.miniIsoCh()<< " "<< newLepton.miniIsoPUsub() << " "<< newLepton.ptrel()<< " "<< newLepton.jetcsv()<< " "<< newLepton.jetptratio() << " "<< newLepton.IP3Dsig()<< " "<< newLepton.dxy() << " " << newLepton.dz() << " "<< newLepton.segmentCompatibility() << " " << newLepton.BDT() << std::endl;
          amu = kTRUE;
        }
      } // if useObj
       
    } //for muon loop
    
    
    ///////////////////////////////////////////
    // Electrons-->refilled and sorted later in method!!
    ///////////////////////////////////////////

    Bool_t aele = kFALSE;
    // All electrons
    for(Int_t io = 0; io < _eventTree->patElectron_pt->size(); io++) {
      newElectron.Clear();
      useObj=newElectron.Fill(*muonsVetoPtr, _eventTree, io,"All",isSimulation);
      if(useObj) { 
	electrons.push_back(newElectron);
      }  
      //if(_eventTree->Electron_tight->at(io) == 1 && _eventTree->Electron_pt->at(io)>10000){
      //  TLorentzVector a(0,0,0,0);
      //  a.SetPtEtaPhiE(_eventTree->Electron_pt->at(io), _eventTree->Electron_eta->at(io), _eventTree->Electron_phi->at(io), 0);
      //  Electrons_tlv.push_back(a);
      //  a.SetPtEtaPhiE(_eventTree->Electron_pt->at(io)*newElectron.E()*1000/_eventTree->Electron_cluster_E->at(io),newElectron.Eta(), newElectron.Phi(),newElectron.E()*1000); 
      //  Electrons_tlv_scaled.push_back(a);
      //} else{
      //  TLorentzVector a(0,0,0,0);
      //  Electrons_tlv.push_back(a);
      //  Electrons_tlv_scaled.push_back(a);
      //}

      newElectron.Clear();
      useObj=newElectron.Fill(*muonsVetoPtr, _eventTree,  io,"Tight",isSimulation);
      if(useObj) {
        tightElectrons.push_back(newElectron);
      }

      newElectron.Clear();
      useObj=newElectron.Fill(*muonsVetoPtr, _eventTree,  io,"Veto",isSimulation);
      if(useObj) {
        vetoElectrons.push_back(newElectron);
      }

      newElectron.Clear();
      useObj=newElectron.Fill(*muonsVetoPtr, _eventTree,  io,"UnIsolated",isSimulation);
      if(useObj) {
        unIsolatedElectrons.push_back(newElectron);
      }
      
      newLepton.Clear();
      useObj = newLepton.Fill(*muonsVetoPtr, _eventTree, io,"EleLoose", isSimulation, SourceNumber ,11);// 11 means Electron
      if(useObj) {
	    looseLeptons.push_back(newLepton);
        if(!aele && _sync == 21){
          std::cout << eventNumber << " " << newLepton.Pt() << " " << newLepton.Eta() << " " << newLepton.Phi() << " "<< newLepton.E() << " "<<newLepton.pdgId()<<" "<< newLepton.charge()<< " "<< newLepton.lepjetchtrks()<<" "<< newLepton.miniIsoRel()<< " "<< newLepton.miniIsoCh()<< " "<< newLepton.miniIsoPUsub() << " "<< newLepton.ptrel()<< " "<< newLepton.jetcsv()<< " "<< newLepton.jetptratio() << " "<< newLepton.IP3Dsig()<< " "<< newLepton.dxy() << " " << newLepton.dz() << " "<< newLepton.mvaValue_HZZ() << " " << newLepton.BDT() << std::endl;
          aele = kTRUE;
        }
      }
      
      newLepton.Clear();
      useObj = newLepton.Fill(*muonsVetoPtr, _eventTree, io,"EleFake", isSimulation, SourceNumber ,11);// 11 means Electron
      if(useObj) {
	    fakeLeptons.push_back(newLepton);
        if(!aele && _sync == 22){
          std::cout << eventNumber << " " << newLepton.Pt() << " " << newLepton.Eta() << " " << newLepton.Phi() << " "<< newLepton.E() << " "<<newLepton.pdgId()<<" "<< newLepton.charge()<< " "<< newLepton.lepjetchtrks()<<" "<< newLepton.miniIsoRel()<< " "<< newLepton.miniIsoCh()<< " "<< newLepton.miniIsoPUsub() << " "<< newLepton.ptrel()<< " "<< newLepton.jetcsv()<< " "<< newLepton.jetptratio() << " "<< newLepton.IP3Dsig()<< " "<< newLepton.dxy() << " " << newLepton.dz() << " "<< newLepton.mvaValue_HZZ() << " " << newLepton.BDT() << std::endl;
          aele = kTRUE;
        }
      }

      newLepton.Clear();
      useObj = newLepton.Fill(*muonsVetoPtr, _eventTree, io,"EleTight", isSimulation, SourceNumber ,11);// 11 means Electron
      if(useObj) {
	    tightLeptons.push_back(newLepton);
        if(!aele && _sync == 23){
          std::cout << eventNumber << " " << newLepton.Pt() << " " << newLepton.Eta() << " " << newLepton.Phi() << " "<< newLepton.E() << " "<<newLepton.pdgId()<<" "<< newLepton.charge()<< " "<< newLepton.lepjetchtrks()<<" "<< newLepton.miniIsoRel()<< " "<< newLepton.miniIsoCh()<< " "<< newLepton.miniIsoPUsub() << " "<< newLepton.ptrel()<< " "<< newLepton.jetcsv()<< " "<< newLepton.jetptratio() << " "<< newLepton.IP3Dsig()<< " "<< newLepton.dxy() << " " << newLepton.dz() << " "<< newLepton.mvaValue_HZZ() << " " << newLepton.BDT() <<" " << newLepton.passTightCharge()<<" " << newLepton.passMissHit() << " "<< newLepton.passConversionVeto() <<std::endl;
          aele = kTRUE;
        }
      }

    } //for

    ///////////////////////////////////////////
    // Taus
    //////////////////////////////////////////
    Bool_t atau = kFALSE;
    for(Int_t io = 0;io < _eventTree -> Tau_pt->size(); io++) {
      
      newTau.Clear();
      useObj = newTau.Fill(*looseleptonsVetoPtr, _eventTree, io,"Loose");
      if(useObj) {
	    looseTaus.push_back(newTau);
        if(!atau && _sync == 31){
            std::cout << eventNumber << " "<<newTau.Pt() << " "<<newTau.Eta()<< " "<< newTau.Phi()<< " "<< newTau.E()<< " "<< newTau.charge() << " " << newTau.dxy() << " " << newTau.dz() << " " << newTau.decayModeFinding() << " " <<newTau.isMedium() << " "<<std::endl;
            atau = kTRUE;
        }
      }//use Obj

      newTau.Clear();
      useObj = newTau.Fill(*looseleptonsVetoPtr, _eventTree, io,"Medium");
      if(useObj) {
	    taus.push_back(newTau);
        if(!atau && _sync == 32){
            std::cout << eventNumber << " "<<newTau.Pt() << " "<<newTau.Eta()<< " "<< newTau.Phi()<< " "<< newTau.E()<< " "<< newTau.charge() << " " << newTau.dxy() << " " << newTau.dz() << " " << newTau.decayModeFinding() << " " <<newTau.isMedium() << " "<<std::endl;
            atau = kTRUE;
        }
      }//use Obj

    }


    // lepton are sorted by conept, unless specified by Pt
    sort(looseLeptons.begin(), looseLeptons.end(), byPt);
    sort(fakeLeptons.begin(), fakeLeptons.end());
    sort(tightLeptons.begin(), tightLeptons.end());

    ///////////////////////////////////////////
    // Jets
    ///////////////////////////////////////////
    closeindex = 999;
    ejordr = 999;
    bestjetdr = 999;
    jeteoverlap = kFALSE;
    //cout <<"EVENT"<<endl;

    Double_t ejoverlap = GetConfig() -> GetValue("ObjectID.Jet.ElectronDeltaRMin", 0.0);
    Bool_t ajet = kFALSE;
    for(Int_t io = 0;io < _eventTree -> Jet_pt->size(); io++) {
      newJet.Clear();
      jeteoverlap = kFALSE;
      closeindex = 999;
      ejordr = 999;
      bestjetdr = 999;
      //      missingEt = -888; 
      useObj = newJet.Fill(1.0,1.0, *fakeleptonsVetoPtr, *tausVetoPtr , _eventTree, io, &missingEtVec);
      //      useObj = newJet.Fill(1.0,1.0, _eventTree, io);
      
      missingEt = TMath::Sqrt(pow(missingEx,2) + pow(missingEy,2));//so MET gets JES adjustment toogEx=top_met.MET_ExMiss();
      /////////////////////////////////////
      
      alljets.push_back(newJet);
      if(useObj) {
	        jets.push_back(newJet);
            if(!ajet && _sync == 41){
            std::cout << eventNumber << " " << newJet.Pt() << " " << newJet.Eta() << " " << newJet.Phi() << " "<< newJet.E() << " " << newJet.bDiscriminator() << " "<< newJet.qg()<<" "<< newJet.lepdrmin() << " " << newJet.lepdrmax() <<" "<< newJet.HjDisc() << " "<< missingEt <<" "<< missingPhi << std::endl;
            ajet = kTRUE;
            }
            
	        if(newJet.IsTagged()) taggedJets.push_back(newJet);
	        else unTaggedJets.push_back(newJet);
   
        //NOTE: PdgId of +/-1 is used for light quark jets when charge information is available and 
	//uncharged particles that are not labeled as b, c, or tau are given an ID of 0
	//Currently no charge information is available so all particles in this catagory have an
	//PgdId of 0.
	//NOTE: This PDGId() method returns the flavor of the MC particle associated
	//with the jet (wrt position).  It is NOT nessesarily the jet's flavor, but
	//a reasonable assumption BASED ON MC AND RECO INFORMATION
	
	//if(newJet.GetAbsPdgId() == 5)    bLabeledJets.push_back(newJet);
	//if(newJet.GetAbsPdgId() == 4)    cLabeledJets.push_back(newJet);
	//if(newJet.GetAbsPdgId() == 15)   tauLabeledJets.push_back(newJet);
	//if((newJet.GetAbsPdgId() == 1) || (newJet.GetAbsPdgId() == 0) )  lightQuarkLabeledJets.push_back(newJet);
      } // if useObj
    } //jets

  if(isSimulation){
    int motherIndex =0;
    int daughtIndex =0;
    // Gen particles 
    for(Int_t io = 0;io < _eventTree -> Gen_pt->size(); io++) {
      newMCParticle.Clear();
      newMCParticle.Fill(_eventTree, io, motherIndex, daughtIndex);
      MCParticles.push_back(newMCParticle);
      if(newMCParticle.isMuon()){
          MCMuons.push_back(newMCParticle);
          if(_sync == 61){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isElectron()){
          MCElectrons.push_back(newMCParticle);
          if(_sync == 62){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isTau()){
          MCTaus.push_back(newMCParticle);
          if(_sync == 63){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isBJet()){
          MCBJets.push_back(newMCParticle);
          if(_sync == 64){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isCJet()){
          MCCJets.push_back(newMCParticle);
          if(_sync == 65){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isLightJet()){
          MCLightJets.push_back(newMCParticle);
          if(_sync == 66){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isTop()){
          MCTops.push_back(newMCParticle);
          if(_sync == 67){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isW()){
          MCWs.push_back(newMCParticle);
          if(_sync == 68){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isH()){
          MCHs.push_back(newMCParticle);
          if(_sync == 69){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isZ()){
          MCZs.push_back(newMCParticle);
          if(_sync == 70){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
      if(newMCParticle.isPhoton()){
          MCPhotons.push_back(newMCParticle);
          if(_sync == 71){
             std::cout << eventNumber << " " << newMCParticle.Index() << " "<< newMCParticle.Pt() << " " << newMCParticle.Eta() << " "<< newMCParticle.Phi() << " "<< newMCParticle.E() << " " << newMCParticle.PdgId() << " " <<newMCParticle.BmotherIndex() <<" " << newMCParticle.motherpdg_id() << " " << newMCParticle.numMother() << " "<< newMCParticle.numDaught() << std::endl;
          }
      }
    }
    /*
    if(_sync == 62){
        for(auto const MCP: MCParticles){
              if(!(MCP.isElectron()))continue;
              //std::cout << " GenMotherFsr " << MCP.GetGenMotherNoFsr(MCP, *mcParticlesPtr).Index()<< std::endl;
              std::cout << " IsFromB " << MCP.isFromB(MCP, *mcParticlesPtr)<< std::endl;
        }
    }
    */
    if(_sync == 61){
        for(auto const MCP: MCMuons){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 62){
        for(auto const MCP: MCElectrons){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            std::cout << " GenMotherFsr " << MCP.GetGenMotherNoFsr(MCP, *mcParticlesPtr).Index()<< std::endl;
            std::cout << " IsFromB " << MCP.isFromB(MCP, *mcParticlesPtr)<< std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 63){
        for(auto const MCP: MCTaus){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 64){
        for(auto const MCP: MCBJets){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            MCJet Mother = MCP.GetGenMotherNoFsr(MCP, *mcParticlesPtr);
            MCJet GrandMother = Mother.GetGenMotherNoFsr(Mother, *mcParticlesPtr);
            std::cout << " GenMotherFsr " << Mother.Index() << " "<< Mother.PdgId()<< " GrandMother "<<GrandMother.Index()<<" " <<GrandMother.PdgId() << std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 65){
        for(auto const MCP: MCCJets){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 66){
        for(auto const MCP: MCLightJets){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 67){
        for(auto const MCP: MCTops){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 68){
        for(auto const MCP: MCWs){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 69){
        for(auto const MCP: MCHs){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 70){
        for(auto const MCP: MCZs){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
    }
    if(_sync == 71){
        for(auto const MCP: MCPhotons){
            std::cout << eventNumber << " " << MCP.Index() << " "<<  std::endl;
            for(auto const MCMother: MCP.BmotherIndices()){
                std::cout << " mother " << MCMother << std::endl;
            }
            for(auto const MCDaught: MCP.BdaughtIndices()){
                std::cout << " daught " << MCDaught << std::endl;
            }
        }
     }

   } 
    
    /*
    missingEx = _eventTree -> MissingEt_etx / 1000.0;
    missingEy = _eventTree -> MissingEt_ety / 1000.0;
    missingEt = TMath::Sqrt(pow(missingEx,2) + pow(missingEy,2));//so MET gets adjustment by the muon smearing
    ///////////////////////////////////////////  
    // Missing ET-->Passed to objects for shifting: MUST BE CALCULATED AFTER ALL OBJECTS ARE SMEARED
    ///////////////////////////////////////////  
    top_met.Reset();
  
    Float_t mystupidfloat=0;
    top_met.Set_METComposition(_eventTree->MissingEt_etx, _eventTree->MissingEt_ety, _eventTree->MissingEt_sumet, mystupidfloat, mystupidfloat, mystupidfloat, mystupidfloat, mystupidfloat, mystupidfloat, mystupidfloat, mystupidfloat, mystupidfloat, _eventTree->MissingEt_SoftJets_sumet, _eventTree->MissingEt_SoftJets_etx, _eventTree->MissingEt_SoftJets_ety, _eventTree->MissingEt_CellOut_sumet, _eventTree->MissingEt_CellOut_etx, _eventTree->MissingEt_CellOut_ety, mystupidfloat, mystupidfloat, mystupidfloat);

    top_met.Set_METWeights(_eventTree->Electron_MissingEt_wpx, _eventTree->Electron_MissingEt_wpy, _eventTree->Electron_MissingEt_wet, 0, 0, 0, _eventTree->Jet_MissingEt_wpx, _eventTree->Jet_MissingEt_wpy, _eventTree->Jet_MissingEt_wet, _eventTree->Muon_MissingEt_statusWord, _eventTree->Muon_MissingEt_wpx, _eventTree->Muon_MissingEt_wpy, _eventTree->Muon_MissingEt_wet);
    double mex=0;
    double mey=0;

    for (int muo=0;muo!=_eventTree->Muon_pt->size();muo++){
	TLorentzVector a(0,0,0,0);
	a.SetPtEtaPhiE(_eventTree->Muon_pt->at(muo), 0, _eventTree->Muon_phi->at(muo), 0);
	Muons_tlv.push_back(a);
	a.SetPtEtaPhiE(_eventTree->Muon_ms_pt->at(muo), 0, _eventTree->Muon_ms_phi->at(muo), 0);
	//cout<<"muo "<<muo<<"  "<<_eventTree->Muon_ms_phi->at(muo)<<endl;
	Muons_ms_tlv.push_back(a);
	a.SetPtEtaPhiE(_eventTree->Muon_pt->at(muo), 0, _eventTree->Muon_phi->at(muo), 0);
	Muons_track_tlv.push_back(a);
    }
      // Muon_ms_tlv_scaled = TLorentzVector(Muon_ms_pt*Muon_me_pt_scaled/Muon_me_pt, 0, Muon_ms_phi, 0)
      // Muon_track_tlv_scaled = TLorentzVector(Muon_track_pt*Muon_id_pt_scaled/Muon_id_pt, 0, Muon_track_phi, 0) 
    for (int muo =0;muo!=muons.size();muo++){
	TLorentzVector a(0,0,0,0);
	a.SetPtEtaPhiE(muons.at(muo).Pt()*1000, 0, muons.at(muo).Phi(), 0);
	Muons_tlv_scaled.push_back(a);
	//event tree pts are in MeV, muons.blah are in GeV.  Tool takes MeV
	a.SetPtEtaPhiE(1000*_eventTree->Muon_ms_pt->at(muo)*muons.at(muo).GetptMS()/_eventTree->Muon_me_pt->at(muo), 0, _eventTree->Muon_ms_phi->at(muo), 0);
	//	cout<<"muo "<<muo<<"  "<<_eventTree->Muon_ms_pt->at(muo)<<"  "<<muons.at(muo).GetptMS()<<"  "<<_eventTree->Muon_me_pt->at(muo)<<"  "<< _eventTree->Muon_ms_phi->at(muo)<<endl;
	Muons_ms_tlv_scaled.push_back(a);
	a.SetPtEtaPhiE(1000*_eventTree->Muon_pt->at(muo)*muons.at(muo).GetptID()/_eventTree->Muon_id_pt->at(muo), 0, _eventTree->Muon_phi->at(muo), 0);
	Muons_track_tlv_scaled.push_back(a);

    }
    top_met.Set_Electrons(Electrons_tlv_scaled, Electrons_tlv);
    top_met.Set_Jets(Jets_tlv_scaled, Jets_tlv, Jets_emscale_tlv);
    top_met.Set_Muons(Muons_tlv_scaled, Muons_tlv, Muons_ms_tlv_scaled, Muons_ms_tlv, Muons_track_tlv_scaled, Muons_track_tlv);
    top_met.ApplyCellOutUncertainty(celloutShift(),0);
    top_met.ApplySoftJetUncertainty(softjetShift(),Jets_JESup_tlv,0);
    top_met.ApplyPileupUncertainty(pileupShift());
      
    missingPhi = top_met.MET_MetPhi();
    missingE1x=top_met.MET_ExMiss()/1000;
    missingEy=top_met.MET_EyMiss()/1000;      
    sumEt=top_met.MET_SumEt()/1000;
 
    missingEt = -888;
    //so 0 jet events also have defined missing Et
    missingEt = top_met.MET_EtMiss()/1000;

    //sorts moved here because of particle index useage in top met tool.  sorts use scaled/smeared pt's
    sort(jets.begin(), jets.end());
    sort(alljets.begin(), alljets.end());
    sort(jetms.begin(), jetms.end());
    sort(taggedJets.begin(), taggedJets.end());
    sort(unTaggedJets.begin(), unTaggedJets.end());
    
    sort(electrons.begin(), electrons.end());
    sort(tightElectrons.begin(), tightElectrons.end());
    sort(vetoElectrons.begin(), vetoElectrons.end());
    sort(ptetaElectrons.begin(), ptetaElectrons.end());
    sort(isolatedElectrons.begin(), isolatedElectrons.end());
    sort(unIsolatedElectrons.begin(), unIsolatedElectrons.end());
    
    sort(muons.begin(), muons.end());
    sort(tightMuons.begin(), tightMuons.end());
    sort(vetoMuons.begin(), vetoMuons.end());    
    sort(ptetaMuons.begin(), ptetaMuons.end());    
    sort(isolatedMuons.begin(), isolatedMuons.end());
    sort(unIsolatedMuons.begin(), unIsolatedMuons.end());    

    ///////////////////////////////////////////
    ////////////////////////////////////////
    // HT and MTotal not in v13.0.30
    // Set to -999 for now.
    ////////////////////////////////////////
    //particleHT     = _eventTree->HT/1000;
    //particleMTotal = _eventTree->MTotal;
    particleHT     = -999.0;
    particleMTotal = -999.0;
    // SetIsFirstEvent(kFALSE);//finished reading first event
    */
  } // end of else: filling from reco tree
  
  //
  // Create a neutrino, including nu_pzn calculation
  Neutrino newNeutrino;
  newNeutrino.Fill(tightMuons, tightElectrons,missingEx,missingEy);
  neutrinos.push_back(newNeutrino);

  //////////////////////
  // Following are variables used for ttH cuts
  // I should probably write a new class and fill them in that class
  // but I'm not doing that now
  ////////////////////////////  
  // ht and St
  TLorentzVector mht_lv(0,0,0,0);
  TLorentzVector mhtT_lv(0,0,0,0);
  for(auto lepton : looseLeptons){
      TLorentzVector lv(0.,0.,0.,0.);
      lv.SetPtEtaPhiE(lepton.Pt(),lepton.Eta(),lepton.Phi(),lepton.E());
      mht_lv = mht_lv + lv;
      if(lepton.isTight()==1){
          mhtT_lv = mhtT_lv + lv;
      }
  }
  for(auto tau : looseTaus){
      TLorentzVector lv(0.,0.,0.,0.);
      lv.SetPtEtaPhiE(tau.Pt(),tau.Eta(),tau.Phi(),tau.E());
      mht_lv = mht_lv + lv;
      if(tau.isMedium()==1){
          mhtT_lv = mhtT_lv + lv;
      }
  }
  for(auto jet : jets){
      TLorentzVector lv(0.,0.,0.,0.);
      lv.SetPtEtaPhiE(jet.Pt(),jet.Eta(),jet.Phi(),jet.E());
      mht_lv = mht_lv + lv;
      mhtT_lv = mhtT_lv + lv;
  }
  mht = mht_lv.Pt();
  mhtT = mhtT_lv.Pt();
  mht_met = mht + missingEt;
  mhtT_met = mhtT + missingEt;
  metLD =  0.00397*missingEt+0.00265*mht;  

  Cal_dilep_mass();
 
  return 0;
  
} //ReadEvent

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * Bool_t EventContainer::CreateFinalState()                                  *
 *                                                                            *
 * Create final state particles                                               *
 * Require at least 2 jets and 1 isolated lepton.  Make cuts if necessary.    *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTRUE if requirements fulfilled                                    *
 ******************************************************************************/
 Bool_t EventContainer::CreateFinalState()
{

  ///////////////////////////////////////
  // Prepare final state particles
  //////////////////////////////////////
  // There should only be one lepton.  If this is the case use that lepton
  if(      1 == tightMuons.size() && 0 == tightElectrons.size()){
    finalLepton = tightMuons[0];
    finalLeptonPDGID = 13;
  }
  else if( 0 == tightMuons.size() && 1 == tightElectrons.size()){
    finalLepton = tightElectrons[0];
    finalLeptonPDGID = 11;
  }
  // If it is the case where there is more than 1 lepton 
  // If more than 1 muon and no electron use leading muon. If more than 1 electron and no muons use leading electron
  else if( tightMuons.size()     > 0 && 0 == tightElectrons.size()){
    finalLepton = tightMuons[0];
    finalLeptonPDGID = 13;
  }
  else if( tightElectrons.size() > 0 && 0 == tightMuons.size()){
     finalLepton = tightElectrons[0];
     finalLeptonPDGID = 11;
  }
  // If there is 1 or more muon and 1 or more electron use lepton with highest pT
  else if( tightMuons.size() > 0 && tightElectrons.size() > 0 ){
    if( tightMuons[0].Pt() > tightElectrons[0].Pt() ){
      finalLepton = tightMuons[0];
      finalLeptonPDGID = 13;
    }
    else{
      finalLepton = tightElectrons[0];
      finalLeptonPDGID = 11;
    }
  } //if
  // If there are no leptons set finalLepton to 0
  else if( 0 == tightMuons.size() && 0 == tightElectrons.size()){
    finalLepton = TLorentzVector(0.0,0.0,0.0,0.0);
    finalLeptonPDGID = 0;
    //    std::cout << "WARNING: <EventContainer::CreateFinalState>" << " O Muons and 0 Electrons in Final State." << std::endl;
  } //else
  // Default (just in case) is to set finalLepton to 0
  else{
    finalLepton = TLorentzVector(0.0,0.0,0.0,0.0);
    finalLeptonPDGID = 0;
  }

  ///////////////////////////////////////////////////////////
  // Reconstruct Neutrino (Pretend that momentum is unknown)
  //NEED TO USE MET, MEX, MEY information to get top eta, etc.
  ///////////////////////////////////////////////////////////
  // Initialize neutrino with negative px and negative py from lepton
  Double_t finalNeutrino_Px = -finalLepton.Px();
  Double_t finalNeutrino_Py = -finalLepton.Py();

  // Truth neutrino pz
  Double_t truthNeutrino_Pz;
  if(MCNeutrinos.size() > 0) truthNeutrino_Pz = MCNeutrinos[0].Pz();
  else truthNeutrino_Pz = 0.0;
			
  // Loop over jets and add negative of jet px and py
  finalJetVector = jets;
  for(Int_t i = 0; i < finalJetVector.size(); i++){
    finalNeutrino_Px += -finalJetVector[i].Px();
    finalNeutrino_Py += -finalJetVector[i].Py();
  } //for

  // Calculate Neutrino pz   
  // 6th parameter: Large negative scale factor means that no scale factor is used
  // 7th parameter: Truth neutrino - not needed for pz calculation (does nothing in Neutrino_Pz())
  Double_t scaleFactor = -999999.0;
  // Double_t finalNeutrino_Pz = Neutrino_Pz(finalNeutrino_Px, finalNeutrino_Py, finalLepton.Px(), finalLepton.Py(), finalLepton.Pz(), finalLepton.E(), scaleFactor, truthNeutrino_Pz);
 Double_t finalNeutrino_Pz = Neutrino_Pz(missingEx, missingEy, finalLepton.Px(), finalLepton.Py(), finalLepton.Pz(), finalLepton.E(), scaleFactor, truthNeutrino_Pz);
  // Calculate final Neutrino Energy
  //Double_t finalNeutrino_E = sqrt(finalNeutrino_Px * finalNeutrino_Px + finalNeutrino_Py * finalNeutrino_Py + finalNeutrino_Pz * finalNeutrino_Pz);
 Double_t finalNeutrino_E = sqrt((missingEx*missingEx) + (missingEy*missingEy) + (finalNeutrino_Pz * finalNeutrino_Pz));
  // Set 4 vector and Id
  // finalNeutrino.SetPxPyPzE(finalNeutrino_Px, finalNeutrino_Py, finalNeutrino_Pz, finalNeutrino_E);
 finalNeutrino.SetPxPyPzE(missingEx,missingEy, finalNeutrino_Pz, finalNeutrino_E);
  // finalNeutrino.SetPdgId(-12); // Not implemented for reconstructed particles

  //  nu_pz=Neutrino_Pz(missingEx, missingEy,leadlep_px,leadlep_py,leadlep_pz,leadlep_e,scf,1.0);
  //  nu_e=sqrt(missingEx*missingEx + missingEy*missingEy + nu_pz*nu_pz);
  //  SetPxPyPzE(missingEx,missingEy,nu_pz,nu_e);
  
  ///////////////////////////////////////////////////////////
  // Reconstruct W 
  ///////////////////////////////////////////////////////////
  finalW = finalNeutrino;
  finalW += finalLepton;
  
  ///////////////////////////////////////////////////////////
  // Reconstruct CM system (add lepton, neutrino, and jets)
  ///////////////////////////////////////////////////////////
  finalCM = finalLepton + finalNeutrino;
  for(Int_t i = 0; i < finalJetVector.size(); i++){
    finalCM = finalCM + finalJetVector[i];
  } //for

  return kTRUE;

} //CreateFinalState() 

/******************************************************************************
 * void EventContainer::MakeTopQuarks()                                       *
 *                                                                            *
 * Make top quarks from W and several jets                                    *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void EventContainer::MakeTopQuarks()
{
  //  std::cout<<"MAKING TOP QUARKS"<<endl;

  ///////////////////////////////////////////////////////////
  // Set everything related to Top Quark jets to 0 
  ///////////////////////////////////////////////////////////
  finalTop_leadingJet.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0);
  finalTop_bestJet.SetPxPyPzE(    0.0, 0.0, 0.0, 0.0);
  finalTop_bestJet12.SetPxPyPzE(  0.0, 0.0, 0.0, 0.0);
  finalTop_bgJet.SetPxPyPzE(      0.0, 0.0, 0.0, 0.0);

  bgJet.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);

  bestJet12Ptr      = NULL;
  nonBestJet12Ptr   = NULL;
  bestJetPtr        = NULL;
  bgJetbJetPtr      = NULL;
  nonBgJetPtr       = NULL;
  bgJetGluonPtr     = NULL;
  taggedJetPtr      = NULL;
  untaggedPtJetPtr  = NULL;
  untaggedEtaJetPtr = NULL;
  forwardJetPtr     = NULL;
  leadingJetPtr     = NULL;

  ///////////////////////////////////////////////////////////
  // Set Jet pointers
  ///////////////////////////////////////////////////////////
  // Set tagger Jet ptr to leading b-tagged jet 
  if(taggedJets.size() > 0) taggedJetPtr = &(taggedJets[0]);
  // Set untaggedPtJetPtr to the leading un-tagged jet ordered in pT (is this correct?)
  if(unTaggedJets.size() > 0) untaggedPtJetPtr = &(unTaggedJets[0]);


  ///////////////////////////////////////////////////////////
  // Create Several Top Quarks
  // Make top quarks from the W and several possible jets. 
  ///////////////////////////////////////////////////////////
  iBestJet = 0;  // index of best jet
  
  // The leading jet from the Top is the W plus the leading jet
  if( finalJetVector.size() > 0){
    finalTop_leadingJet = finalW + finalJetVector[0];
  } //if
  else{
    //std::cout<<"No Jets in this event, particle reconstruction unclear"<<endl;
  } //else

  // Determine Best Jet (one which reconstructs closest to Target Top Mass )
  // findBestJet returns 0 if there are no jets in the event.  But in this case, finalJetVector is empty.  So check number of jets first.
  iBestJet = findBestJet(finalJetVector.size(), finalJetVector, finalW, _targetTopMass);
  if(finalJetVector.size() > 0){
    bestJetPtr = &(finalJetVector[iBestJet]);
    finalTop_bestJet = finalW + *bestJetPtr;
  }
  
  // Determine Best Jet from only the 2 leading jets
  Int_t nJets12 = finalJetVector.size() > 2 ? 2: finalJetVector.size();
  iBestJet = findBestJet(nJets12, finalJetVector, finalW, _targetTopMass);
  if(finalJetVector.size() > 0){
     bestJet12Ptr = &(finalJetVector[iBestJet]);
     finalTop_bestJet12 = finalW + *(bestJet12Ptr);
   }
 
  if(finalJetVector.size() >= 2) nonBestJet12Ptr = &(finalJetVector[1-iBestJet]);  // What if iBestJet > 1 ?
  else nonBestJet12Ptr = NULL;

  // Leading Jet
  if(finalJetVector.size() > 0) leadingJetPtr = &(finalJetVector[0]);


  //   //cout<<"add in a possible gluon"<<endl;
//   // add in the gluon if it is close to this jet
//   // and then determine the best jet

  std::vector<Jet> tmpJetVector;
  // Add gluon if it is close to the jet and then determine the best jet
  // If 2 or less jets use the bestJet12
  if((finalJetVector.size() <= 2)&&(finalJetVector.size() > 0)) {
    finalTop_bgJet = finalTop_bestJet12;
    bgJet          = *bestJet12Ptr;
    bgJetbJetPtr   = bestJet12Ptr;
    nonBgJetPtr    = nonBestJet12Ptr;
  } //if
  
  // For 3 or more jets, pair each of the leading 2 jets with the gluon and then find the best jet
  // Gluon is finalJetVector[2] (how do we know this)
  else if (finalJetVector.size() > 2){
    tmpJetVector = finalJetVector;
  
    // Not sure if this is correct
    // Old version used a 4-element array even if 4th jet did not exist
    // This version only fills 4th element if 4th jet exists
    for(Int_t i = 0; i < 2 ;i++) {
      tmpJetVector[i]   =  finalJetVector[i];
      if( tmpJetVector.size() > i+2 ) tmpJetVector[i+2] =  finalJetVector[i] + finalJetVector[2];
    } // for over jets 1,2

    // Find best jet out of 4
    // Replaced 4 by tmpJetVector.size()
    
    iBestJet       = findBestJet(tmpJetVector.size(), tmpJetVector, finalW, _targetTopMass);
    finalTop_bgJet = tmpJetVector[iBestJet] + finalW;
    bgJet          = tmpJetVector[iBestJet];
    
    // Determine if gluon needs to be included

    if(iBestJet >= 2) {
      bgJetbJetPtr  = &(finalJetVector[iBestJet-2]);
      nonBgJetPtr   = &(finalJetVector[1-(iBestJet-2)]);
      bgJetGluonPtr = &(finalJetVector[2]);
    }  //if
    else {
      bgJetbJetPtr  = &(finalJetVector[iBestJet]);
      nonBgJetPtr   = &(finalJetVector[1-(iBestJet)]);
      bgJetGluonPtr = 0;
    }
    
  } // else: try to include the gluon


  // Final top from tagged jet and W
  if(taggedJetPtr != NULL) {
    finalTop_taggedJet = *taggedJetPtr + finalW;
    
    // and the W using a top mass constraint:
    // the neutrino from the top mass constraint
    // also use a constraint on the top mass rather than the smaller of the two
    // solutions.

    // cout<<"True Top mass is "<<tlt.M()<<" e= "<<tlt.E()<<", px= "<<tlt.Px()<<", py= "<<tlt.Py()<<", pz= "<<tlt.Pz()<<endl;

    // Truth neutrino pz
    Double_t truthNeutrino_Pz;
    if(MCNeutrinos.size() > 0) truthNeutrino_Pz = MCNeutrinos[0].Pz();
    else truthNeutrino_Pz = 0.0;

    Double_t finalNeutrino_Pz = Neutrino_Pz_Top(finalNeutrino.Px(), finalNeutrino.Py(),
						finalLepton.Px(), finalLepton.Py(), finalLepton.Pz(), finalLepton.E(),
						taggedJetPtr -> Px(), taggedJetPtr -> Py(), taggedJetPtr -> Pz(), taggedJetPtr -> E(),
						truthNeutrino_Pz );
    
    
     Double_t finalNeutrino_E = sqrt( pow(finalNeutrino.Px(),2) + pow(finalNeutrino.Py(),2) + finalNeutrino_Pz*finalNeutrino_Pz);
     finalNeutrinoTopC.SetPxPyPzE(finalNeutrino.Px(), finalNeutrino.Py(), finalNeutrino_Pz, finalNeutrino_E);
     //     finalNeutrinoTopC.SetPdgId(-12);  // Does not work at the moment
    
     // The final lepton from top constraint on neutrino
     finalWTopC = finalNeutrinoTopC + finalLepton;
     finalTop_taggedJetTopC = *taggedJetPtr + finalWTopC;
  } //if

   else{
     finalTop_taggedJet.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);
     finalTop_taggedJetTopC.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);

   } //else

  return;
} //MakeTopQuark

/////TTH Flags
void EventContainer::set_TTHFlags(){
    //set TTH Triggers
    if( _eventTree -> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ==1 || _eventTree -> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ==1 ||_eventTree -> HLT_IsoMu22==1 || _eventTree -> HLT_IsoTkMu22==1 || _eventTree -> HLT_IsoMu22_eta2p1==1 || _eventTree -> HLT_IsoTkMu22_eta2p1 ==1||_eventTree -> HLT_IsoMu24 ==1 || _eventTree -> HLT_IsoTkMu24==1)TTHLep_2Mu=1;
    else TTHLep_2Mu=0;
    if( _eventTree -> HLT_Ele27_WPTight_Gsf==1 || _eventTree -> HLT_Ele25_eta2p1_WPTight_Gsf==1 || _eventTree -> HLT_Ele27_eta2p1_WPLoose_Gsf==1 || _eventTree -> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ==1 )TTHLep_2Ele=1;
    else TTHLep_2Ele=0;
    if( _eventTree -> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL ==1 || _eventTree -> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ==1 || _eventTree -> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL ==1 || _eventTree -> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ ==1 
    || _eventTree -> HLT_IsoMu22==1 || _eventTree -> HLT_IsoTkMu22==1 || _eventTree -> HLT_IsoMu22_eta2p1==1 || _eventTree -> HLT_IsoTkMu22_eta2p1 ==1||_eventTree -> HLT_IsoMu24 ==1 || _eventTree -> HLT_IsoTkMu24==1 
    || _eventTree -> HLT_Ele27_WPTight_Gsf==1 || _eventTree -> HLT_Ele25_eta2p1_WPTight_Gsf==1 || _eventTree -> HLT_Ele27_eta2p1_WPLoose_Gsf==1
    ) TTHLep_MuEle=1;
    else TTHLep_MuEle=0;
    if(TTHLep_MuEle ==1 || TTHLep_2Mu ==1 || TTHLep_2Ele ==1) TTHLep_2L =1;
    else TTHLep_2L =0;
};


/////hadTOp
/***************************************************************
 * void EventContainer::set_hadTopMVA()                       *
 *                                                              * 
 * Set up the MVA xml file && bMeidum Cuts                      *
 *                                                              *
 * Input: TEnv* config                                          *
 * Output: None                                                 *
 * **************************************************************/
 
void EventContainer::set_hadTopMVA()
{
    hadTop_reader_loose = new TMVA::Reader( "!Color:!Silent" );

    hadTop_reader_loose->AddVariable( "b_from_leptop_bdt.csv", &varbjet_lepTop_csv );
    hadTop_reader_loose->AddVariable( "b_from_hadtop_bdt.csv", &varbjet_hadTop_csv );
    hadTop_reader_loose->AddVariable( "hadTop_tlv_bdt.Pt()", &varreco_hadTop_pt );
    hadTop_reader_loose->AddVariable( "w_from_hadtop_tlv_bdt.M()", &varreco_WhadTop_mass );
    hadTop_reader_loose->AddVariable( "hadTop_tlv_bdt.M()", &varreco_hadTop_mass );
    hadTop_reader_loose->AddVariable( "lep_from_leptop_bdt.obj.pt()/lep_from_higgs_bdt.obj.pt()", &varPtRatio_leptOverleph );
    hadTop_reader_loose->AddVariable( "dr_lepFromTop_bFromLepTop", &varDr_lept_bfromlTop );
    hadTop_reader_loose->AddVariable( "dr_lepFromTop_bFromHadTop", &varDr_lept_bfromhTop );
    hadTop_reader_loose->AddVariable( "dr_lepFromHiggs_bFromLepTop", &varDr_leph_bfromlTop );
    hadTop_reader_loose->BookMVA("BDTG method", _config.GetValue("Include.HadTopMVA.bLooseFile","null"));

    hadTop_reader_tight = new TMVA::Reader( "!Color:!Silent" );

    hadTop_reader_tight->AddVariable( "b_from_leptop_bdt.csv", &varbjet_lepTop_csv );
    hadTop_reader_tight->AddVariable( "b_from_hadtop_bdt.csv", &varbjet_hadTop_csv );
    hadTop_reader_tight->AddVariable( "hadTop_tlv_bdt.Pt()", &varreco_hadTop_pt );
    hadTop_reader_tight->AddVariable( "w_from_hadtop_tlv_bdt.M()", &varreco_WhadTop_mass );
    hadTop_reader_tight->AddVariable( "hadTop_tlv_bdt.M()", &varreco_hadTop_mass );
    hadTop_reader_tight->AddVariable( "lep_from_leptop_bdt.obj.pt()/lep_from_higgs_bdt.obj.pt()", &varPtRatio_leptOverleph );
    hadTop_reader_tight->AddVariable( "dr_lepFromTop_bFromLepTop", &varDr_lept_bfromlTop );
    hadTop_reader_tight->AddVariable( "dr_lepFromTop_bFromHadTop", &varDr_lept_bfromhTop );
    hadTop_reader_tight->AddVariable( "dr_lepFromHiggs_bFromLepTop", &varDr_leph_bfromlTop );
    hadTop_reader_tight->BookMVA("BDTG method", _config.GetValue("Include.HadTopMVA.bTightFile","null"));
};

/***************************************************************
 * void EventContainer::set_ttHDiLepMVA()                       *
 *                                                              * 
 * Set up the MVA xml file for event BDT                      *
 *                                                              *
 * Input: None                                                 *
 * Output: None                                                 *
 * **************************************************************/
void EventContainer::set_ttHDiLepMVA()
{
    // 2l ttbar BDT
    Dilepttbar_reader_ = new TMVA::Reader("!Color:!Silent");
    Dilepttbar_reader_->AddVariable("max(abs(LepGood_eta[iLepFO_Recl[0]]),abs(LepGood_eta[iLepFO_Recl[1]]))",&Dilepttbar_maxlepeta);
    Dilepttbar_reader_->AddVariable("nJet25_Recl",&Dilepttbar_numJets);
    Dilepttbar_reader_->AddVariable("mindr_lep1_jet",&Dilepttbar_mindrlep1jet);
    Dilepttbar_reader_->AddVariable("mindr_lep2_jet",&Dilepttbar_mindrlep2jet);
    Dilepttbar_reader_->AddVariable("MT_met_lep1",&Dilepttbar_Mtmetlep1);
    Dilepttbar_reader_->AddVariable("max(-1.1,BDTv8_eventReco_mvaValue)",&Dilepttbar_HadTopBDT);
    Dilepttbar_reader_->AddSpectator("iLepFO_Recl[0]",&Dilepttbar_mindrlep1jet);
    Dilepttbar_reader_->AddSpectator("iLepFO_Recl[1]",&Dilepttbar_mindrlep2jet);
    Dilepttbar_reader_->AddSpectator("iLepFO_Recl[2]",&Dilepttbar_maxlepeta);
    Dilepttbar_reader_->BookMVA("BDTG method",  _config.GetValue("Include.DiLepBDT.ttbarFile","null"));
 
    // 2l ttv BDT
    Dilepttv_reader_ = new TMVA::Reader("!Color:!Silent");
    Dilepttv_reader_->AddVariable("max(abs(LepGood_eta[iLepFO_Recl[0]]),abs(LepGood_eta[iLepFO_Recl[1]]))",&Dilepttv_maxlepeta);
    Dilepttv_reader_->AddVariable("nJet25_Recl",&Dilepttv_numJets);
    Dilepttv_reader_->AddVariable("mindr_lep1_jet",&Dilepttv_mindrlep1jet);
    Dilepttv_reader_->AddVariable("mindr_lep2_jet",&Dilepttv_mindrlep2jet);
    Dilepttv_reader_->AddVariable("MT_met_lep1",&Dilepttv_Mtmetlep1);
    Dilepttv_reader_->AddVariable("LepGood_conePt[iLepFO_Recl[1]]",&Dilepttv_ptlep2);
    Dilepttv_reader_->AddVariable("LepGood_conePt[iLepFO_Recl[0]]",&Dilepttv_ptlep1);
    Dilepttv_reader_->AddVariable("max(-1.1,BDTv8_eventReco_Hj_score)",&Dilepttv_Hj1BDT);
    Dilepttv_reader_->AddSpectator("iLepFO_Recl[0]",&Dilepttv_mindrlep1jet);
    Dilepttv_reader_->AddSpectator("iLepFO_Recl[1]",&Dilepttv_mindrlep2jet);
    Dilepttv_reader_->AddSpectator("iLepFO_Recl[2]",&Dilepttv_ptlep1);
    Dilepttv_reader_->BookMVA("BDTG method", _config.GetValue("Include.DiLepBDT.ttvFile","null")); 

    // 2D Map
    TFile* MapFile = TFile::Open( GetConfig() -> GetValue("Include.2DBDT.MapFile","null"),"READ");
    if (!MapFile) std::cout << "TTH 2D BDT Mapping file not found!" << std::endl;
    hBinning2l = (TH2F*)MapFile->Get( GetConfig() -> GetValue("Event.2DBDTHistName","null"))->Clone();
    hBinning2l->SetDirectory(0);
    MapFile->Close();
}
/***************************************************************
 * void EventContainer::Cal_dilep_mass()              *
 *                                                              * 
 * Calculate different dilep mass                               *
 *                                                              *
 * Input: None                                                  *
 * Output: None                                                *
 * **************************************************************/
void EventContainer::Cal_dilep_mass(){
    double diloosemass = 999;
    double lSFOSmass = 999;
    double dielemass = 999;
    if (looseLeptons.size()<2)return;
    TLorentzVector Lep0(0,0,0,0); 
    TLorentzVector Lep1(0,0,0,0);
    TLorentzVector FakeLep0(0,0,0,0); 
    TLorentzVector FakeLep1(0,0,0,0);
    // dilep mass
    for(uint lep_en =0; lep_en < looseLeptons.size(); lep_en++){
        Lep0.SetPtEtaPhiE(looseLeptons.at(lep_en).Pt(), looseLeptons.at(lep_en).Eta(), looseLeptons.at(lep_en).Phi(), looseLeptons.at(lep_en).E());
        for(uint l_en =lep_en+1; l_en < looseLeptons.size(); l_en++){
            Lep1.SetPtEtaPhiE(looseLeptons.at(l_en).Pt(), looseLeptons.at(l_en).Eta(), looseLeptons.at(l_en).Phi(), looseLeptons.at(l_en).E());
            if(diloosemass > (Lep0+Lep1).M()) 
                diloosemass = (Lep0+Lep1).M();
            if(fabs(lSFOSmass-91.2)>fabs((Lep0+Lep1).M()-91.2)
                && (looseLeptons.at(lep_en).pdgId()+looseLeptons.at(l_en).pdgId())==0)
                lSFOSmass = (Lep0+Lep1).M(); 
        }
    }
    massL = diloosemass;
    massL_SFOS = lSFOSmass;
    if (fakeLeptons.size()>=2){
        Lepton fakelep0 = fakeLeptons.at(0);
        Lepton fakelep1 = fakeLeptons.at(1);
        FakeLep0.SetPtEtaPhiE(fakelep0.conept(),fakelep0.Eta(),fakelep0.Phi(),fakelep0.E());
        FakeLep1.SetPtEtaPhiE(fakelep1.conept(),fakelep1.Eta(),fakelep1.Phi(),fakelep1.E());
        if(fabs(fakelep0.pdgId())==11 && fabs(fakelep1.pdgId())==11)
            dielemass = (FakeLep0+FakeLep1).M();
        mass_diele = dielemass;
    }
};
