#define mvaTool_cxx
#include "mvaTool.h"

mvaTool::mvaTool(Int_t channel){
  
  _channel = channel;

  //  regionNames = {"3j1t","3j2t","2j1t","4j1t","4j2t"};
  regionNames = {""};
  //Start by initialising the list of variables we will base the MVA on

    //varList.push_back("M_Pt_Jet1_2040e24");

    //    varList.push_back("largestCSV");varList.push_back("M_nJet2040");
    //  varList.push_back("M_firstJetPt");
  //I don't understand these guys' implementations, so I'm ignoring them for now.
  //  varList.push_back("likelihood_BJet2040");
  //varList.push_back("likelihood_BJet4000");    varList.push_back("M_HT");
    //varList.push_back("M_nJet3040");
    //  varList.push_back("M_nJet2040e24");
    //    varList.push_back("M_hadronicWPt");
    //    varList.push_back("M_hadronicWPhi");
  
  baseName = "";
    
    /*
    varList.push_back("M_nJet2040");
  //    varList.push_back("M_HT");
    varList.push_back("M_DeltaRBJetLepton");
    varList.push_back("M_DeltaRlightjets");
    varList.push_back("M_topMass2_lep");
        varList.push_back("M_Pt_Lepton");
    varList.push_back("M_Pt_AllJetsLeptonMET");
    varList.push_back("M_DeltaRLeptonJet1");
    
    varList.push_back("M_Mass_Jet1Jet2Jet3LeptonMET");
    varList.push_back("M_hadronicWmass");

    //    varList.push_back("M_TMass_Jet1Jet2Jet3"); 
    varList.push_back("lightJet1CSV");

    //varList.push_back("M_nJet3040e24");
    //    varList.push_back("M_E_Jet1MET");
    //varList.push_back("M_Jet1Jet2Jet3_Centrality");
    //  varList.push_back("M_Pt_Jet1_2040");
    */
    
    //varList.push_back("M_hadronicWEta");
    //varList.push_back("M_DeltaRBJethadronicW");
    //varList.push_back("M_Pt_sys");
    //varList.push_back("M_cosThetaStar");
    //varList.push_back("M_cosThetaStar_lepOnly");
    //varList.push_back("lightJet2CSV");
    //varList.push_back("M_Pt_AllJets2040");
    //varList.push_back("M_Pt_BJet1_4000");
//varList.push_back("M_hadronicWEta");
    //varList.push_back("M_DeltaRBJethadronicW");
    //varList.push_back("M_Pt_sys");

    varList.push_back("leadLep_corrpt");
    varList.push_back("secondLep_corrpt");
    varList.push_back("massll");
    varList.push_back("Sum2lCharge");
    varList.push_back("Jet_numLoose");
    varList.push_back("Jet_numbLoose");
    varList.push_back("Jet_numbMedium");
    varList.push_back("mht");
    varList.push_back("Met_type1PF_pt");
    varList.push_back("metLD");
    varList.push_back("Bin2l");
    varList.push_back("Dilep_bestMVA");
    varList.push_back("Dilep_worseMVA");
    varList.push_back("Dilep_pdgId");
    varList.push_back("Dilep_htllv");
    varList.push_back("Dilep_mtWmin");
    varList.push_back("Dilep_nTight");
    varList.push_back("HighestJetCSV");
    varList.push_back("leadJetCSV");
    varList.push_back("secondJetCSV");
    varList.push_back("thirdJetCSV");
    varList.push_back("fourthJetCSV");
    varList.push_back("HtJet");
    varList.push_back("ttbarBDT_2lss");
    varList.push_back("ttvBDT_2lss");
    varList.push_back("Mt_metleadlep");
    varList.push_back("maxeta");
    varList.push_back("leadLep_jetdr");
    varList.push_back("secondLep_jetdr");
    varList.push_back("minMllAFOS");
    varList.push_back("minMllAFAS");
    varList.push_back("minMllSFOS");
    varList.push_back("nLepFO");
    varList.push_back("nLepTight");
    varList.push_back("puWeight");
    varList.push_back("bWeight");
    varList.push_back("TriggerSF");
    varList.push_back("lepSF");
    varList.push_back("leadLep_BDT");
    varList.push_back("secondLep_BDT");

  //The list of samples. this is used by the reading, not the training.
  samplelist.push_back("tW_top_nfh");
  
  //At some point this should be filled out with the names of the systematics so that we can read those too
  systlist.push_back("");
  systlist.push_back("_PU_up");
  systlist.push_back("_PU_down");
  systlist.push_back("_LSF_up");
  systlist.push_back("_LSF_down");
  systlist.push_back("_Trig_up");
  systlist.push_back("_Trig_down");
  systlist.push_back("_bTag_up");
  systlist.push_back("_bTag_down");
  /*
  systlist.push_back("_mistag_up");
  systlist.push_back("_mistag_down");
  systlist.push_back("_PDF_up");
  systlist.push_back("_PDF_down");
  */
}

void mvaTool::doBothTraining(TString inDir){
  doTraining(inDir,true);
  doTraining(inDir,false);
}

void mvaTool::doTraining(TString inDir, bool isttbar = true){
  
  //This needs to be done first
  TMVA::Tools::Instance();

  //Create the output file that will store the training results
  std::string postfix1 = "_ttbar";
  if (!isttbar) postfix1 = "_wJets";
  TString outfileName("training/tWLepJets_training_BDT"+postfix1+".root");
  TFile* outFile = TFile::Open(outfileName, "RECREATE");

  //Create the factory
  TMVA::Factory *factory = new TMVA::Factory("tWLepJet_training",outFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");

  //Create a data loader
  TMVA::DataLoader loader{"loader"};
  
  //Make TChains for signal and background
  TChain signal("TNT/BOOM");
  TChain bkg_ttbar("TNT/BOOM");
  TChain bkg_wJets("TNT/BOOM");

    //From the inDir, add all skim files to the trees
  signal.Add(inDir+"tW_top_nfh/skims/tW_top*Skim.root");
  signal.Add(inDir+"tW_antitop_nfh/skims/tW_antitop*Skim.root");
  bkg_ttbar.Add(inDir+"ttbar/skims/ttbar*Skim.root");
  //  bkg_ttbar.Add(inDir+"ttbarBU/skims/ttbarBU*Skim.root");
  bkg_wJets.Add(inDir+"wPlusJetsMCatNLO/skims/wPlusJetsMCatNLO*Skim.root");
  
  //Grab the input files now
  //  TFile * sigFile = TFile::Open("../condorStuff/skims20161129_bdtVariables/tW/tW_top/skims/tW_top0Skim.root"); //Not the final one, of course. Will probably need to sum the skims
  //  TFile * bkgFile = TFile::Open("../condorStuff/skims20161129_bdtVariables/tW/ttbar/skims/ttbar0Skim.root");

  //signal.Add("tW/tW_antitop_nfh/skims/tW_antitop_nfh0Skim.root");
  //bkg_ttbar.Add("tW/ttbar/skims/ttbar0Skim.root");

  //Get the trees
  //TTree *signal = (TTree*)sigFile->Get("TNT/BOOM");
  //TTree *bkg_ttbar = (TTree*)bkgFile->Get("TNT/BOOM");

  //Add the trees to the factory
  loader.AddSignalTree    (&signal,    1.);
  if (isttbar){
    loader.AddBackgroundTree(&bkg_ttbar,1.);
  }
  else {
    loader.AddBackgroundTree(&bkg_wJets,1.);
  }
  
  for (unsigned int i=0; i < varList.size(); i++) loader.AddVariable(varList[i].Data(),'F');

  loader.SetSignalWeightExpression("EventWeight");
  loader.SetBackgroundWeightExpression("EventWeight");

  TCut mycutsSig = "channel == 0 && (M_nBJet3040 + M_nBJet4000) == 1 ";
  TCut mycutsBkg = "channel == 0 && (M_nBJet3040 + M_nBJet4000) == 1 ";

  loader.PrepareTrainingAndTestTree( mycutsSig, mycutsBkg,"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

  TString postfix = "_ttbar";
  if (!isttbar) postfix = "_wJets";

  //  factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_200_10", "!H:!V:NTrees=200:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=10:PruneMethod=NoPruning" );
  //  factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_200_5", "!H:!V:NTrees=200:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=5:PruneMethod=NoPruning" );
    factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_1000_20_0.1"+postfix, "!H:!V:NTrees=1000:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:Shrinkage=0.1" );
  //  factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_400_10", "!H:!V:NTrees=400:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=10:PruneMethod=NoPruning" );
  //factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_400_5", "!H:!V:NTrees=400:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=5:PruneMethod=NoPruning" );
  //factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_200_10", "!H:!V:NTrees=200:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=10:PruneMethod=NoPruning" );
  //factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_200_5", "!H:!V:NTrees=200:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=5:PruneMethod=NoPruning" );
  //factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_400_10", "!H:!V:NTrees=400:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=10:PruneMethod=NoPruning" );

  // Train MVAs using the set of training events                  
  factory->TrainAllMethods();

  // ---- Evaluate all MVAs using the set of test events          
  factory->TestAllMethods();

  // ----- Evaluate and compare performance of all configured MVAs
  factory->EvaluateAllMethods();

  outFile->Close();

  delete factory;

}

void mvaTool::doReading(TString sampleName, TString inDir, TString outDir, bool isData){
  
  std::cout << "Entering reading routine" << std::endl;
  TMVA::Tools::Instance();

  //Get the reader object
  reader = new TMVA::Reader( "!Color:!Silent" );
  unsigned int varsize = varList.size();
  float treevars[varsize];

  std::cout << "Entering variable adding" << std::endl;
  for (unsigned int i=0; i<varsize;i++){
    treevars[i] = 0;
    std::cout << "[Variable loop] Adding variable: " << varList[i].Data() << std::endl;
    reader->AddVariable( varList[i].Data(), &(treevars[i]) );
  }

  reader->BookMVA( "BDT_ttbar", baseName+"loader/weights/tWLepJet_training_BDT_Grad_1000_20_0.1_ttbar.weights.xml" );
  //  reader->BookMVA( "BDT_wJets", baseName+"loader/weights/tWLepJet_training_BDT_Grad_1000_20_0.1_wJets.weights.xml" );

  std::cout << "Finished reading BDT training" << std::endl;

  std::cout << "Processing sample: " << sampleName << std::endl;
  
  processMCSample(sampleName,inDir,outDir,treevars, isData);
  
  std::cout << "Finished processing " << sampleName << std::endl;
  
}

void mvaTool::doReadingNoMVA(TString sampleName, TString inDir, TString outDir, bool isData){
  
  std::cout << "Entering reading routine" << std::endl;

  unsigned int varsize = varList.size();
  float treevars[varsize];

  std::cout << "Entering variable adding" << std::endl;
  for (unsigned int i=0; i<varsize;i++){
    treevars[i] = 0;
    std::cout << "[Variable loop] Adding variable: " << varList[i].Data() << std::endl;
  }


  std::cout << "Finished reading BDT training" << std::endl;

  std::cout << "Processing sample: " << sampleName << std::endl;
  
  processMCSample(sampleName,inDir,outDir,treevars, isData, false);
  
  std::cout << "Finished processing " << sampleName << std::endl;
  
}


//Do the thing
void mvaTool::processMCSample(TString sampleName, TString inDir, TString outDir, float * treevars,bool isData, bool doMVA){

  TString dirWithTrees = inDir+sampleName+"/skims/"+sampleName+"*Skim.root";
//  TFile *input = new TFile( (inDir+sampleName+"/hists/merged"+sampleName+".root").Data(), "READ");
  std::vector<TFile*> theoutputfiles;
  for (auto const regionName : regionNames){
    std::cout << "Createing file " << outDir+regionName+"/output_"+sampleName+".root" <<std::endl;
    TFile *theoutputfile = new TFile( (outDir+regionName+"/output_"+sampleName+".root").Data(), "RECREATE");
    theoutputfiles.push_back(theoutputfile);
  }

  std::cout << "Files have been create" << std::endl;
  //  TFile *thetreefile = new TFile( (outDir+"bdtTree_"+sampleName+".root").Data(), "RECREATE");
  //theTreeOutputFileMap[sampleName] = thetreefile;
  
  //------------------------
  // Systematic loop
  //------------------------
  // WIP. This will include the additional files at some point
  

  for (unsigned int j=0; j < systlist.size(); j++){
    if (isData && systlist[j] != "") continue;
    createHists(sampleName+systlist[j]);
  }

  loopInSample(dirWithTrees,sampleName,treevars,isData,doMVA);
  //makeStatVariationHists(sampleName,theoutputfiles); //We do this in processMCSample so that we have the output file to save the stat variations into.
  
  saveHists(theoutputfiles);
    
  for (auto const outputfile: theoutputfiles){
    outputfile->Close();
    delete outputfile;
  }
}

//Loop over the events in the desired sample
void mvaTool::loopInSample(TString dirWithTrees, TString sampleName, float* treevars, bool isData, bool doMVA){

  unsigned int varsize = varList.size();

  TChain* theTree = new TChain("TNT/BOOM");
  theTree->Add(dirWithTrees);
  std::cout << "[loopInSample] Added "<<dirWithTrees << " to TChain" << std::endl;
  
  for (unsigned int ivar=0; ivar<varsize; ivar++) theTree->SetBranchAddress( varList[ivar].Data(), &(treevars[ivar]));

  

  std::cout << "[loopInSample] Finished assigning variables" << std::endl;
  theweight=0.;
  theTree->SetBranchAddress( "EventWeight", &theweight );

  //Get the systematic weights here. We will then fill hists separately as a result of this.
  float puWeight=0., puWeightUp = 0., puWeightDown = 0.;
  float lepSFWeight=0., lepSFWeightUp = 0., lepSFWeightDown = 0.;
  float trigSFWeight=0., trigSFWeightUp = 0., trigSFWeightDown = 0.;
  float bWeight=0., bWeighthfs1Up = 0., bWeighthfs1Down = 0., bWeighthfs2Up = 0., bWeighthfs2Down = 0., bWeightcferr1Up = 0., bWeightcferr1Down = 0., bWeightcferr2Up = 0., bWeightcferr2Down = 0., bWeightjerUp = 0., bWeightjerDown = 0., bWeightlfUp = 0., bWeightlfDown = 0.;
  float mistagWeight=0., mistagWeighthfs1Up = 0., mistagWeighthfs1Down = 0., mistagWeighthfs2Up = 0., mistagWeighthfs2Down = 0., mistagWeightcferr1Up = 0., mistagWeightcferr1Down = 0., mistagWeightcferr2Up = 0., mistagWeightcferr2Down = 0., mistagWeightjerUp = 0., mistagWeightjerDown = 0., mistagWeightlfUp = 0., mistagWeightlfDown = 0.;
  double pdfUp = 0., pdfDown = 0.;
  
  int nbJets3040 = 0., nbJets4000 = 0.;

  double met = -100.,metPhi = 100.;
  float lepPt = -100., lepPhi = 100.;

  int theChannel = -1;
  /*
  theTree->SetBranchAddress( "M_Pt_Lepton",&lepPt);
  theTree->SetBranchAddress( "M_Phi_Lepton",&lepPhi);
  theTree->SetBranchAddress( "Met_type1PFxy_pt",&met);
  theTree->SetBranchAddress( "Met_type1PFxy_phi",&metPhi);
  */
  if (doMVA){
    theTree->SetBranchAddress( "channel",&theChannel);
    theTree->SetBranchAddress( "M_nBJet3040",&nbJets3040);
    theTree->SetBranchAddress( "M_nBJet4000",&nbJets4000);
  }

  if (!isData){
    theTree->SetBranchAddress( "puWeight", &puWeight );
    theTree->SetBranchAddress( "puWeight_SysUp", &puWeightUp );
    theTree->SetBranchAddress( "puWeight_SysDown", &puWeightDown );
  
    std::cout << "[loopInSample] Finished assigning pileup weights" << std::endl;

    theTree->SetBranchAddress( "lepSF", &lepSFWeight );
    theTree->SetBranchAddress( "lepSF_SysUp", &lepSFWeightUp );
    theTree->SetBranchAddress( "lepSF_SysDown", &lepSFWeightDown );

    theTree->SetBranchAddress( "trigSF", &trigSFWeight );
    theTree->SetBranchAddress( "trigSF_SysUp", &trigSFWeightUp );
    theTree->SetBranchAddress( "trigSF_SysDown", &trigSFWeightDown );
    
    theTree->SetBranchAddress( "bWeight_central", &bWeight );
    theTree->SetBranchAddress( "bWeight_up_hfstats1", &bWeighthfs1Up );
    theTree->SetBranchAddress( "bWeight_down_hfstats1", &bWeighthfs1Down );
    theTree->SetBranchAddress( "bWeight_up_hfstats2", &bWeighthfs2Up );
    theTree->SetBranchAddress( "bWeight_down_hfstats2", &bWeighthfs2Down );
    theTree->SetBranchAddress( "bWeight_up_cferr1", &bWeightcferr1Up );
    theTree->SetBranchAddress( "bWeight_down_cferr1", &bWeightcferr1Down );
    theTree->SetBranchAddress( "bWeight_up_cferr2", &bWeightcferr2Up );
    theTree->SetBranchAddress( "bWeight_down_cferr2", &bWeightcferr2Down );
    theTree->SetBranchAddress( "bWeight_up_jes", &bWeightjerUp );
    theTree->SetBranchAddress( "bWeight_down_jes", &bWeightjerDown );
    theTree->SetBranchAddress( "bWeight_up_lf", &bWeightlfUp );
    theTree->SetBranchAddress( "bWeight_down_lf", &bWeightlfDown );
    /*
    theTree->SetBranchAddress( "misTagWeight_central", &mistagWeight );
    theTree->SetBranchAddress( "misTagWeight_up_hfstats1", &mistagWeighthfs1Up );
    theTree->SetBranchAddress( "misTagWeight_down_hfstats1", &mistagWeighthfs1Down );
    theTree->SetBranchAddress( "misTagWeight_up_hfstats2", &mistagWeighthfs2Up );
    theTree->SetBranchAddress( "misTagWeight_down_hfstats2", &mistagWeighthfs2Down );
    theTree->SetBranchAddress( "misTagWeight_up_cferr1", &mistagWeightcferr1Up );
    theTree->SetBranchAddress( "misTagWeight_down_cferr1", &mistagWeightcferr1Down );
    theTree->SetBranchAddress( "misTagWeight_up_cferr2", &mistagWeightcferr2Up );
    theTree->SetBranchAddress( "misTagWeight_down_cferr2", &mistagWeightcferr2Down );
    theTree->SetBranchAddress( "misTagWeight_up_jes", &mistagWeightjerUp );
    theTree->SetBranchAddress( "misTagWeight_down_jes", &mistagWeightjerDown );
    theTree->SetBranchAddress( "misTagWeight_up_lf", &mistagWeightlfUp );
    theTree->SetBranchAddress( "misTagWeight_down_lf", &mistagWeightlfDown );
     
    theTree->SetBranchAddress( "EVENT_PDFtthbbWeightUp",&pdfUp );
    theTree->SetBranchAddress( "EVENT_PDFtthbbWeightDown",&pdfDown );
    */
    std::cout << "[loopInSample] Finished assigning lepton weights" << std::endl;
  }
  
  //  std::vector<float> bTagSysts;
  //  setbTagVars(theTree);
  
  if (theTree ==0) cout << "No TTree found for " << sampleName << "!" << std::endl;

  std::tuple<float,float> bSysts (std::make_pair(1.,1.));
  std::tuple<float,float> mistagSysts (std::make_pair(1.,1.));

  //Loop over the events
  std::cout << theTree->GetEntries() << " events in loop for sample " << sampleName << std::endl; 
  for (int i = 0; i < theTree->GetEntries(); i++){
    
    //if (i > 20000) break;
    if (i%500 == 0){
      printf ("Processing event %i\r", i);
      fflush(stdout);
    }
    theTree->GetEntry(i);

    //    if (theChannel != _channel) continue;

    if (theChannel < 0 || theChannel > 4) continue;

    if (theChannel == 0){ // A backup because I messed up the channel flag in the first reprocessing.
      //      std::cout << "Zero! njets are: " << nbJets4000 << " " << nbJets3040 <<std::endl;
      if ((nbJets4000 + nbJets3040) != 1) continue;
    }

    if (doMVA)  mvaValue = reader->EvaluateMVA("BDT_ttbar");
    else {
      mvaValue = 0.;
      theChannel = 0;
    }
    //    mvawJetsValue = reader->EvaluateMVA("BDT_wJets");
    mvawJetsValue = 0.;

    float mtw = std::sqrt(2*met*lepPt*(1-cos(metPhi-lepPhi)));

    //    std::cout << met << " " << lepPt << " " << metPhi << " " << lepPhi << " " << mtw << std::endl;

    fillHists(sampleName,treevars,mvaValue,mvawJetsValue,theweight,met,mtw,theChannel);
    //Now fill the weight-based systematic histograms
    if (!isData){
      fillHists(sampleName+"_PU_up",treevars,mvaValue,mvawJetsValue,theweight * (puWeightUp/puWeight),met,mtw,theChannel);
      fillHists(sampleName+"_PU_down",treevars,mvaValue,mvawJetsValue,theweight * (puWeightDown/puWeight),met,mtw,theChannel);
      fillHists(sampleName+"_LSF_up",treevars,mvaValue,mvawJetsValue,theweight * (lepSFWeightUp/lepSFWeight),met,mtw,theChannel);
      fillHists(sampleName+"_LSF_down",treevars,mvaValue,mvawJetsValue,theweight * (lepSFWeightDown/lepSFWeight),met,mtw,theChannel);
      fillHists(sampleName+"_Trig_up",treevars,mvaValue,mvawJetsValue,theweight * (trigSFWeightUp/trigSFWeight),met,mtw,theChannel);
      fillHists(sampleName+"_Trig_down",treevars,mvaValue,mvawJetsValue,theweight * (trigSFWeightDown/trigSFWeight),met,mtw,theChannel);
      bSysts = calculatebTagSyst(bWeight,{bWeighthfs1Up,bWeighthfs1Down,bWeighthfs2Up,bWeighthfs2Down,bWeightcferr1Up,bWeightcferr1Down,bWeightcferr2Up,bWeightcferr2Down,bWeightjerUp,bWeightjerDown,bWeightlfUp,bWeightlfDown});
      //      std::cout << "btag systs: " << std::get<0>(bSysts) << " " << std::get<1>(bSysts) << std::endl;
      fillHists(sampleName+"_bTag_up",treevars,mvaValue,mvawJetsValue,theweight * std::get<0>(bSysts),met,mtw,theChannel);
      fillHists(sampleName+"_bTag_down",treevars,mvaValue,mvawJetsValue,theweight * std::get<1>(bSysts),met,mtw,theChannel);
      mistagSysts = calculatebTagSyst(mistagWeight,{mistagWeighthfs1Up,mistagWeighthfs1Down,mistagWeighthfs2Up,mistagWeighthfs2Down,mistagWeightcferr1Up,mistagWeightcferr1Down,mistagWeightcferr2Up,mistagWeightcferr2Down,mistagWeightjerUp,mistagWeightjerDown,mistagWeightlfUp,mistagWeightlfDown});
      //      std::cout << "mistag systs: " << std::get<0>(mistagSysts) << " " << std::get<1>(mistagSysts) << std::endl;
      /*
      fillHists(sampleName+"_mistag_up",treevars,mvaValue,mvawJetsValue,theweight * std::get<0>(mistagSysts),met,mtw,theChannel);
      fillHists(sampleName+"_mistag_down",treevars,mvaValue,mvawJetsValue,theweight * std::get<1>(mistagSysts),met,mtw,theChannel);
      fillHists(sampleName+"_PDF_up",treevars,mvaValue,mvawJetsValue,theweight*pdfUp,met,mtw,theChannel);
      fillHists(sampleName+"_PDF_down",treevars,mvaValue,mvawJetsValue,theweight*pdfDown,met,mtw,theChannel);
      */
    }
  }

} 

void mvaTool::createHists(TString sampleName){

  for (unsigned int region = 0; region < regionNames.size(); region++){


    std::vector<TH1F*> histovect;
    std::vector<TH1F*> bdtVect;

    //Make a histogram per variable
    for (unsigned int i = 0; i<varList.size(); i++){
      int nbins = 1;
      double xmin = -1000;
      double xmax = 1000;
      /*
      if (varList[i] ==  "M_DeltaRBJetLepton") {nbins = 20; xmin = 0; xmax = 6.;};
      if (varList[i] ==  "M_DeltaRlightjets") {nbins = 20; xmin = 0; xmax = 6.;};
      if (varList[i] == "M_topMass2_lep") {nbins = 20; xmin = 0.; xmax = 600.;};
      if (varList[i] == "M_Pt_AllJets2040") {nbins = 20; xmin = 0; xmax = 160;};
      if (varList[i] == "M_Pt_Lepton") {nbins = 20; xmin = 0.; xmax = 300.;};
      if (varList[i] == "M_Pt_AllJetsLeptonMET") {nbins = 20; xmin = 0.; xmax = 300.;};
      if (varList[i] == "M_E_Jet1MET") {nbins = 20; xmin = 0.; xmax = 300.;};
      if (varList[i] == "M_Jet1Jet2Jet3_Centrality") {nbins = 20; xmin = 0.; xmax = 1.;};
      if (varList[i] == "M_DeltaRLeptonJet1") {nbins = 20; xmin = 0.; xmax = 6.;};
      if (varList[i] == "M_nJet3040e24") {nbins = 10; xmin = 0.; xmax = 10.;};
      if (varList[i] == "M_nJet2040") {nbins = 10; xmin = 0.; xmax = 10.;};
      if (varList[i] == "M_Mass_Jet1Jet2Jet3LeptonMET") {nbins = 20; xmin = 0.; xmax = 1500.;};
      if (varList[i] == "M_Pt_BJet1_4000") {nbins = 20; xmin = 40.; xmax = 200.;};
      if (varList[i] == "M_Pt_Jet1_2040") {nbins = 20; xmin = 20.; xmax = 40.;};
      if (varList[i] == "M_hadronicWmass") {nbins = 20; xmin = 0.; xmax = 500.;};
      if (varList[i] == "M_hadronicWEta") {nbins = 20; xmin = -6.; xmax = 6.;};
      if (varList[i] == "M_DeltaRBJethadronicW") {nbins = 20; xmin = 0.; xmax = 6.;};
      if (varList[i] == "M_Pt_sys") {nbins = 20; xmin = 0.; xmax = 300.;};
      if (varList[i] == "M_HT") {nbins = 20; xmin = 0.; xmax = 900.;};
      if (varList[i] == "M_TMass_Jet1Jet2Jet3") {nbins = 20; xmin = 0.; xmax = 1400.;};
      if (varList[i] == "M_cosThetaStar") {nbins = 20; xmin = -1.; xmax = 1.;};
      if (varList[i] == "M_cosThetaStar_lepOnly") {nbins = 20; xmin = -1.; xmax = 1.;};
      if (varList[i] == "lightJet1CSV") {nbins = 20; xmin = 0.; xmax = 1.;};
      if (varList[i] == "lightJet2CSV") {nbins = 20; xmin = 0.; xmax = 1.;};
      */
      if(varList[i]== "leadLep_corrpt") {nbins= 10; xmin= 0; xmax= 200;};
      if(varList[i]== "secondLep_corrpt") {nbins= 10; xmin= 0; xmax= 100;};
      if(varList[i]== "massll") {nbins= 10; xmin= 0; xmax= 400;};
      if(varList[i]== "Sum2lCharge") {nbins= 2; xmin= -2; xmax= 2;};
      if(varList[i]== "Jet_numLoose") {nbins= 4; xmin= 3.5; xmax= 7.5;};
      if(varList[i]== "Jet_numbLoose") {nbins= 6; xmin= -0.5; xmax= 5.5;};
      if(varList[i]== "Jet_numbMedium") {nbins= 6; xmin= -0.5; xmax= 5.5;};
      if(varList[i]== "mht") {nbins= 10; xmin= 0; xmax= 400;};
      if(varList[i]== "Met_type1PF_pt") {nbins= 10; xmin= 0; xmax= 400;};
      if(varList[i]== "metLD") {nbins= 10; xmin= 0; xmax= 2;};
      if(varList[i]== "Bin2l") {nbins= 8; xmin= 0.5; xmax= 8.5;};
      if(varList[i]== "Dilep_bestMVA") {nbins= 8; xmin= 0.6; xmax= 1;};
      if(varList[i]== "Dilep_worseMVA") {nbins= 8; xmin= 0.6; xmax= 1;};
      if(varList[i]== "Dilep_pdgId") {nbins= 3; xmin= -0.5; xmax= 2.5;};
      if(varList[i]== "Dilep_htllv") {nbins= 10; xmin= 0; xmax= 600;};
      if(varList[i]== "Dilep_mtWmin") {nbins= 10; xmin= 0; xmax= 200;};
      if(varList[i]== "Dilep_nTight") {nbins= 3; xmin= -0.5; xmax= 2.5;};
      if(varList[i]== "HighestJetCSV") {nbins= 15; xmin= 0; xmax= 1;};
      if(varList[i]== "leadJetCSV") {nbins= 15; xmin= 0; xmax= 1;};
      if(varList[i]== "secondJetCSV") {nbins= 15; xmin= 0; xmax= 1;};
      if(varList[i]== "thirdJetCSV") {nbins= 15; xmin= 0; xmax= 1;};
      if(varList[i]== "fourthJetCSV") {nbins= 15; xmin= 0; xmax= 1;};
      if(varList[i]== "HtJet") {nbins= 10; xmin= 0; xmax= 1000;};
      if(varList[i]== "ttbarBDT_2lss") {nbins= 10; xmin= -1; xmax= 1;};
      if(varList[i]== "ttvBDT_2lss") {nbins= 10; xmin= -1; xmax= 1;};
      if(varList[i]== "Mt_metleadlep") {nbins= 10; xmin= 0; xmax= 400;};
      if(varList[i]== "maxeta") {nbins= 10; xmin= 0; xmax= 2.5;};
      if(varList[i]== "leadLep_jetdr") {nbins= 10; xmin= 0; xmax= 4;};
      if(varList[i]== "secondLep_jetdr") {nbins= 10; xmin= 0; xmax= 4;};
      if(varList[i]== "minMllAFOS") {nbins= 10; xmin= 0; xmax= 300;};
      if(varList[i]== "minMllAFAS") {nbins= 10; xmin= 0; xmax= 300;};
      if(varList[i]== "minMllSFOS") {nbins= 10; xmin= 0; xmax= 300;};
      if(varList[i]== "nLepFO") {nbins= 6; xmin= -0.5; xmax= 5.5;};
      if(varList[i]== "nLepTight") {nbins= 6; xmin= -0.5; xmax= 5.5;};
      if(varList[i]== "puWeight") {nbins= 30; xmin= 0.6; xmax= 1.4;};
      if(varList[i]== "bWeight") {nbins= 30; xmin= 0.6; xmax= 1.4;};
      if(varList[i]== "TriggerSF") {nbins= 30; xmin= 0.88; xmax= 1.12;};
      if(varList[i]== "lepSF") {nbins= 30; xmin= 0.6; xmax= 1.4;};
      if(varList[i]== "leadLep_BDT") {nbins= 10; xmin= -1; xmax= 1;};
      if(varList[i]== "secondLep_BDT") {nbins= 10; xmin= -1; xmax= 1;};

      TH1F* histo = new TH1F((varList[i] + "_" + sampleName).Data(), (varList[i] + "_" + sampleName).Data(),nbins,xmin,xmax);
      histo->Sumw2();
      histovect.push_back(histo);
    }
    //Add in some plots for met and mtw for control/fitting
    TH1F* histomtw = new TH1F(("mTW_" + sampleName).Data(), ("mTW_" + sampleName).Data(),20,0.,200.);
    histomtw->Sumw2();
    histovect.push_back(histomtw);
    TH1F* histomet = new TH1F(("met_" + sampleName).Data(), ("met_" + sampleName).Data(),20,0.,200.);
    histomet->Sumw2();
    histovect.push_back(histomet);
    for (int nBins = 10; nBins <= 100; nBins+=10){
      TH1F* histo = new TH1F(("MVA_ttbar_bin"+std::to_string(nBins)+"_"+sampleName).Data(),("MVA_ttbar_bin"+std::to_string(nBins)+"_"+sampleName).Data(),nBins,-0.8,0.8);
      histo->Sumw2();
      bdtVect.push_back(histo);
    }
    int nBins = 1000;
    TH1F* histo = new TH1F(("MVA_ttbar_bin"+std::to_string(nBins)+"_"+sampleName).Data(),("MVA_ttbar_bin"+std::to_string(nBins)+"_"+sampleName).Data(),nBins,-0.8,0.8);
    histo->Sumw2();
    bdtVect.push_back(histo);
    TH1F* histo2 = new TH1F(("MVA_wJets_"+sampleName).Data(),("MVA_wJets_"+sampleName).Data(),20,-0.3,0.3);
    histo2->Sumw2();
    histovect.push_back(histo2);

    TH2F* bdt2D = new TH2F(("MVA_2D_"+sampleName).Data(),("MVA_2D_"+sampleName).Data(),20,-0.8,0.8,20,-0.3,0.3);
    bdt2D->Sumw2();
    the2DHistoMap[sampleName].push_back(bdt2D);

    theHistoMap[sampleName].push_back(histovect);
    bdtHistoMap[sampleName].push_back(bdtVect);
  }
  std::cout << "hist maps are this long: " << the2DHistoMap[sampleName].size() << " " << theHistoMap[sampleName].size() << " " << bdtHistoMap[sampleName].size() << std::endl;
}

void mvaTool::fillHists(TString sampleName, float* treevars, double mvaValue, double mvawJetsValue, double theweight, float met, float mtw, int theChannel){

  std::vector<std::vector<TH1F*> > histovect = theHistoMap[sampleName];
  std::vector<std::vector<TH1F*> > bdtVector = bdtHistoMap[sampleName];


  for (unsigned int i=0; i < varList.size(); i++) histovect[theChannel][i]->Fill(treevars[i],theweight);
  for (unsigned int j = 0; j < bdtVector[theChannel].size(); j++) bdtVector[theChannel][j]->Fill(mvaValue,theweight);
   
  histovect[theChannel][histovect[theChannel].size() - 3]->Fill(mtw,theweight);
  histovect[theChannel][histovect[theChannel].size() - 2]->Fill(met,theweight);

  if (histovect[theChannel].size() > 1){
    //    histovect[histovect.size()-2]->Fill(mvaValue,theweight);
     histovect[theChannel][histovect[theChannel].size()-1]->Fill(mvawJetsValue,theweight);
  }
  the2DHistoMap[sampleName][theChannel]->Fill(mvaValue,mvawJetsValue,theweight);

}

void mvaTool::saveHists(std::vector<TFile*> outFile){
  for (unsigned int i = 0; i < regionNames.size(); i++){
    outFile[i]->cd();
    for (auto histoMapElement: theHistoMap){
      for (auto hist: (histoMapElement.second)[i]) hist->Write();
    }
    for (auto histoMapElement: bdtHistoMap){
      for (auto hist: (histoMapElement.second)[i]) hist->Write();
    }
    
    for (auto hist2D: the2DHistoMap){
      (hist2D.second)[i]->Write();
    }
  }
}

void mvaTool::setbTagVars(TChain * theTree){
  std::cout << "[setbTagVars] Entered setbTagVars" << std::endl;
  //  std::vector<TString> bTagSystNames = {"cferr1","cferr2","hfstats1","hfstats2","jes","lf"};
  //  std::vector<TString> bTagSystNames = {"cferr1","cferr2","hfstats2"};
  std::vector<TString> bTagSystNames = {"jes","hfstats1","lf","hfstats2","cferr1"};
  std::vector<TString> upDown = {"up","down"};
  bTagSysts.push_back(0.);
  std::cout << "[setbTagVars] Assigned central variable " << std::endl;
  theTree->SetBranchAddress( "bWeight_central", &(bTagSysts[0]) );
  std::cout << "[setbTagVars] Assigned central variable to tree " << std::endl;
  int i = 1;
  for (auto bName: bTagSystNames){
    std::cout << "[setbTageVars] Booking " << bName << " variable: " << std::endl;
    for (auto ud: upDown){
      bTagSysts.push_back(0.);
      std::cout << ("     [setbTageVars] bWeight_"+ud+"_"+bName).Data() << std::endl;
      theTree->SetBranchAddress( ("bWeight_"+ud+"_"+bName).Data(), &(bTagSysts[i]));
      i++;
    }
  }
}

std::tuple<float,float> mvaTool::calculatebTagSyst(float bCentral, std::vector<float> bWeightsSyst){
  float systUp = 0., systDown = 0.;
  for (unsigned int i = 1; i < bWeightsSyst.size(); i++){
      if (i%2 == 0){//Down systs
	systDown += pow((bWeightsSyst[i]/bCentral)-1,2);
	//	std::cout << (bWeightsSyst[i]/bCentral)-1 << ",";
      }
      else{
	systUp += pow((bWeightsSyst[i]/bCentral)-1,2);
	//std::cout << (bWeightsSyst[i]/bCentral)-1 << ",";
      }
    }
  //  std::cout << std::endl;
  return std::make_tuple(1+sqrt(systUp),1-sqrt(systDown));
}

/*std::tuple<float,float> mvaTool::calculateMistagSyst(float bCentral, std::vector<float> bWeightsSyst){
  float systUp = 0., systDown = 0.;
  for (unsigned int i = 1; i < bWeightsSyst.size(); i++){
      if (i%2 == 0){//Down systs
	systDown += pow((bWeightsSyst[i]/bCentral)-1,2);
      }
      else{
	systUp += pow((bWeightsSyst[i]/bCentral)-1,2);
      }
    }
  return std::make_tuple(1+sqrt(systUp),1-sqrt(systDown));
  }*/
  
void mvaTool::makeStatVariationHists(TString sampleName, std::vector<TFile *> outputFile){
  for (unsigned int i = 0; i < regionNames.size(); i++){
    TH1F * theDefaultMVA = theHistoMap[sampleName][i].back(); //We only need to do this to nominal.
    outputFile[i]->cd();
    std::ostringstream histNameStream;
    std::string histName;             
    
    for (int i = 1; i <= theDefaultMVA->GetXaxis()->GetNbins();i++){
      histNameStream.str("");
      histNameStream << "MVA_" << sampleName << "_statbin"<<i<<"_up";
      histName = histNameStream.str();
      TH1F* tempMVAUp = (TH1F*)theDefaultMVA->Clone(histName.c_str());
      histNameStream.str("");
      histNameStream << "MVA_" << sampleName << "_statbin"<<i<<"_down";
      histName = histNameStream.str();
      TH1F* tempMVADown = (TH1F*)theDefaultMVA->Clone(histName.c_str());
      float binToChange = theDefaultMVA->GetBinContent(i);
      //This is the bit I'm not sure of, but can edit later with any luck.
      float uncert = sqrt(binToChange);
      tempMVAUp->SetBinContent(i,binToChange+uncert);
      tempMVADown->SetBinContent(i,binToChange-uncert);
      tempMVAUp->Write();
      tempMVADown->Write();
    }
  }
}
