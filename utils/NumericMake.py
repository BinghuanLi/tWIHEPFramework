import os
import re
import sys
import commands
import subprocess

#########################
############### Information provided by user
#################################

# Path you run this script
workpath = "/publicfs/cms/user/libh/Test/Rootplizer/analyzer"
#Specify needed variables
#  Type   Reading  Saving  Example
#  CaseA   Yes      Yes     Jet_pt: you want to save it and need also to read it (using SetBranchStatus+CopyEntries would require more processing time) 
#  CaseB   Yes      No      Jet_muonEnergyFraction: you want to read it to define jet ID, but may not want to save it  
#  CaseC   No       Yes     Jet_LooseID: you can not read it from ntuplas if there is not, but you want to save in rootplas 

# Variable Case
Case = "CaseA"
#Case = "CaseB"
#Case = "CaseC"
# Variable Definition


VariableType  = "double"
VariableNames = [
"leadLep_corrpt","secondLep_corrpt","massll","Sum2lCharge", "Jet_numLoose",
"Jet_numbLoose","Jet_numbMedium","mht", "Met_type1PF_pt", "metLD",
"Bin2l","Dilep_bestMVA","Dilep_worseMVA", "Dilep_pdgId", "Dilep_htllv",
"Dilep_mtWmin", "Dilep_nTight","HighestJetCSV","leadJetCSV","secondJetCSV",
"thirdJetCSV","fourthJetCSV","HtJet", "ttbarBDT_2lss","ttvBDT_2lss",
"ThirdCorrptNAV","Mt_metleadlep", "NAV","maxeta","leadLep_jetdr",
"secondLep_jetdr","minMllAFOS","minMllAFAS","minMllSFOS","nLepFO",
"nLepTight","Tau_numLooseNAV","nBestVtxNAV","puWeight","bWeight",
"TriggerSF","lepSF","leadLep_chargeNAV","leadLep_dxyNAV","leadLep_dzNAV",
"leadLep_mvaIdNAV","leadLep_etaNAV","leadLep_jetcsvNAV","leadLep_minIsoNAV","leadLep_minIsoChNAV",
"leadLep_minIsoNeuNAV","leadLep_BDT","leadLep_pdgIdNAV","leadLep_ptNAV","leadLep_phiNAV",
"leadLep_ptratioNAV","leadLep_ptrelNAV","leadLep_segmentNAV","leadLep_sig3dNAV","secondLep_chargeNAV",
"secondLep_dxyNAV","secondLep_dzNAV","secondLep_mvaIdNAV","secondLep_etaNAV","secondLep_jetcsvNAV",
"secondLep_minIsoNAV","secondLep_minIsoChNAV","secondLep_minIsoNeuNAV","secondLep_BDT","secondLep_pdgIdNAV",
"secondLep_ptNAV","secondLep_ptratioNAV","secondLep_ptrelNAV","secondLep_segmentNAV","secondLep_phiNAV",
"secondLep_sig3dNAV",
]
VariablesBin={
"leadLep_corrpt":10,"secondLep_corrpt":10,"massll":10,"Sum2lCharge":2, "Jet_numLoose":4,
"Jet_numbLoose":6,"Jet_numbMedium":6,"mht":10, "Met_type1PF_pt":10, "metLD":10,
"Bin2l":8,"Dilep_bestMVA":8,"Dilep_worseMVA":8, "Dilep_pdgId":3, "Dilep_htllv":10,
"Dilep_mtWmin":10, "Dilep_nTight":3,"HighestJetCSV":15,"leadJetCSV":15,"secondJetCSV":15,
"thirdJetCSV":15,"fourthJetCSV":15,"HtJet":10, "ttbarBDT_2lss":10,"ttvBDT_2lss":10,
"ThirdCorrptNAV":20,"Mt_metleadlep":10, "NAV":10,"maxeta":10,"leadLep_jetdr":10,
"secondLep_jetdr":10,"minMllAFOS":10,"minMllAFAS":10,"minMllSFOS":10,"nLepFO":6,
"nLepTight":6,"Tau_numLooseNAV":3,"nBestVtxNAV":10,"puWeight":30,"bWeight":30,
"TriggerSF":30,"lepSF":30,"leadLep_chargeNAV":3,"leadLep_dxyNAV":10,"leadLep_dzNAV":10,
"leadLep_mvaIdNAV":10,"leadLep_etaNAV":10,"leadLep_jetcsvNAV":10,"leadLep_minIsoNAV":10,"leadLep_minIsoChNAV":10,
"leadLep_minIsoNeuNAV":10,"leadLep_BDT":10,"leadLep_pdgIdNAV":4,"leadLep_ptNAV":10,"leadLep_phiNAV":4,
"leadLep_ptratioNAV":10,"leadLep_ptrelNAV":10,"leadLep_segmentNAV":10,"leadLep_sig3dNAV":10,"secondLep_chargeNAV":3,
"secondLep_dxyNAV":10,"secondLep_dzNAV":10,"secondLep_mvaIdNAV":10,"secondLep_etaNAV":10,"secondLep_jetcsvNAV":10,
"secondLep_minIsoNAV":10,"secondLep_minIsoChNAV":10,"secondLep_minIsoNeuNAV":10,"secondLep_BDT":10,"secondLep_pdgIdNAV":4,
"secondLep_ptNAV":10,"secondLep_ptratioNAV":10,"secondLep_ptrelNAV":10,"secondLep_segmentNAV":10,"secondLep_phiNAV":4,
"secondLep_sig3dNAV":10,
    }
VariablesInRange={
"leadLep_corrpt":0,"secondLep_corrpt":0,"massll":0,"Sum2lCharge":-2, "Jet_numLoose":3.5,
"Jet_numbLoose":-0.5,"Jet_numbMedium":-0.5,"mht":0, "Met_type1PF_pt":0, "metLD":0,
"Bin2l":0.5,"Dilep_bestMVA":0.6,"Dilep_worseMVA":0.6, "Dilep_pdgId":-0.5, "Dilep_htllv":0,
"Dilep_mtWmin":0, "Dilep_nTight":-0.5,"HighestJetCSV":0,"leadJetCSV":0,"secondJetCSV":0,
"thirdJetCSV":0,"fourthJetCSV":0,"HtJet":0, "ttbarBDT_2lss":-1,"ttvBDT_2lss":-1,
"ThirdCorrptNAV":0,"Mt_metleadlep":0, "NAV":0.5,"maxeta":0,"leadLep_jetdr":0,
"secondLep_jetdr":0,"minMllAFOS":0,"minMllAFAS":0,"minMllSFOS":0,"nLepFO":-0.5,
"nLepTight":-0.5,"Tau_numLooseNAV":-0.5,"nBestVtxNAV":-0.5,"puWeight":0.6,"bWeight":0.6,
"TriggerSF":0.88,"lepSF":0.6,"leadLep_chargeNAV":-1.5,"leadLep_dxyNAV":0,"leadLep_dzNAV":0,
"leadLep_mvaIdNAV":0,"leadLep_etaNAV":-2.5,"leadLep_jetcsvNAV":0,"leadLep_minIsoNAV":0,"leadLep_minIsoChNAV":0,
"leadLep_minIsoNeuNAV":0,"leadLep_BDT":-1,"leadLep_pdgIdNAV":-1,"leadLep_ptNAV":0,"leadLep_phiNAV":-3.2,
"leadLep_ptratioNAV":0,"leadLep_ptrelNAV":0,"leadLep_segmentNAV":0,"leadLep_sig3dNAV":0,"secondLep_chargeNAV":-1.5,
"secondLep_dxyNAV":0,"secondLep_dzNAV":0,"secondLep_mvaIdNAV":0,"secondLep_etaNAV":-2.5,"secondLep_jetcsvNAV":0,
"secondLep_minIsoNAV":0,"secondLep_minIsoChNAV":0,"secondLep_minIsoNeuNAV":0,"secondLep_BDT":-1,"secondLep_pdgIdNAV":-1,
"secondLep_ptNAV":0,"secondLep_ptratioNAV":0,"secondLep_ptrelNAV":0,"secondLep_segmentNAV":0,"secondLep_phiNAV":-3.2,
"secondLep_sig3dNAV":0,
    }
VariablesEndRange = {
"leadLep_corrpt":200,"secondLep_corrpt":100,"massll":400,"Sum2lCharge":2, "Jet_numLoose":7.5,
"Jet_numbLoose":5.5,"Jet_numbMedium":5.5,"mht":400, "Met_type1PF_pt":400, "metLD":2,
"Bin2l":8.5,"Dilep_bestMVA":1,"Dilep_worseMVA":1, "Dilep_pdgId":2.5, "Dilep_htllv":600,
"Dilep_mtWmin":200, "Dilep_nTight":2.5,"HighestJetCSV":1,"leadJetCSV":1,"secondJetCSV":1,
"thirdJetCSV":1,"fourthJetCSV":1,"HtJet":1000, "ttbarBDT_2lss":1,"ttvBDT_2lss":1,
"ThirdCorrptNAV":100,"Mt_metleadlep":400, "NAV":4,"maxeta":2.5,"leadLep_jetdr":4,
"secondLep_jetdr":4,"minMllAFOS":300,"minMllAFAS":300,"minMllSFOS":300,"nLepFO":5.5,
"nLepTight":5.5,"Tau_numLooseNAV":2.5,"nBestVtxNAV":41.5,"puWeight":1.4,"bWeight":1.4,
"TriggerSF":1.12,"lepSF":1.4,"leadLep_chargeNAV":1.5,"leadLep_dxyNAV":0.1,"leadLep_dzNAV":0.1,
"leadLep_mvaIdNAV":1,"leadLep_etaNAV":2.5,"leadLep_jetcsvNAV":1,"leadLep_minIsoNAV":0.4,"leadLep_minIsoChNAV":0.4,
"leadLep_minIsoNeuNAV":0.4,"leadLep_BDT":1,"leadLep_pdgIdNAV":3,"leadLep_ptNAV":200,"leadLep_phiNAV":3.2,
"leadLep_ptratioNAV":1.2,"leadLep_ptrelNAV":40,"leadLep_segmentNAV":1,"leadLep_sig3dNAV":8,"secondLep_chargeNAV":1.5,
"secondLep_dxyNAV":0.1,"secondLep_dzNAV":0.1,"secondLep_mvaIdNAV":1,"secondLep_etaNAV":2.5,"secondLep_jetcsvNAV":1,
"secondLep_minIsoNAV":0.4,"secondLep_minIsoChNAV":0.4,"secondLep_minIsoNeuNAV":0.4,"secondLep_BDT":1,"secondLep_pdgIdNAV":3,
"secondLep_ptNAV":200,"secondLep_ptratioNAV":1.2,"secondLep_ptrelNAV":40,"secondLep_segmentNAV":1,"secondLep_phiNAV":3.2,
"secondLep_sig3dNAV":8,
}
#VariableType  = "int"
#VariableNames = [
# CaseA Variables
#"Muon_soft","Muon_loose","Muon_medium","Muon_tight","Muon_isHighPt",
#"Muon_POGisGood","Muon_pdgId","Muon_pf","Muon_isGlobal","Muon_isTrackerMuon",
#"Muon_tunePBestTrackType","Muon_gen_pdgId","Muon_gen_isPromptFinalState","Muon_gen_isDirectPromptTauDecayProductFinalState"

# CaseB Variables

# CaseC Variables
#]

# Create the variable file
Vectorname = VariableType+Case+"_Numeric.cc"
vector     = file (Vectorname,"w")

#ReadTreeptr & WriteTreeptr
RTreeptr = "readingtree"
WTreeptr = "newtree"

#Name of Current Entry
ParEntry = "tentry"
#Name of index in Push_back
ParSel = "gen_en"

###################
### Script itself
#################
if Case == "CaseA":
 for Variable in VariableNames:
     if not "NAV" in Variable:
        print >> vector, '    varList.push_back("'+Variable+'");'
 
 
 print >> vector, "//variables to be written"
 for Variable in VariableNames:
     if "NAV" in Variable:
         continue
     print >> vector,'      if(varList[i]== "'+Variable+'") {nbins= '+str(VariablesBin[Variable])+"; xmin= "+str(VariablesInRange[Variable])+"; xmax= "+str(VariablesEndRange[Variable])+";};" 
 

elif Case == "CaseB":
 print >> vector, "//This is Case B"
 print >> vector, "//Head file declaration"
 print >> vector, "//variables to be read"
 for Variable in VariableNames:
     print >> vector,VariableType+" r"+Variable+"; TBranch* b_r"+Variable+" =0;" 
 
 print >> vector, "//source file definition"
 print >> vector, "//read setbranchaddress"
 for Variable in VariableNames:
     print >> vector, " "+RTreeptr+'->SetBranchAddress("'+Variable+'",&r'+Variable+",&b_r"+Variable+");"
 
 print >> vector, "//GetEntry"
 for Variable in VariableNames:
     print >> vector, " b_r"+Variable+"->GetEntry("+ParEntry+");"

elif Case == "CaseC":
 print >> vector, "//This is Case C"
 print >> vector, "//Head file declaration"
 
 print >> vector, "//variables to be written"
 for Variable in VariableNames:
     print >> vector,VariableType+" "+Variable+";" 
 
 
 print >> vector, "//source file definition"
 print >> vector, "//Write setbranchaddress"
 for Variable in VariableNames:
     print >> vector, "    "+WTreeptr+'->Branch("'+Variable+'",&'+Variable+");"
 
 print >> vector, "//Initialize Number"
 for Variable in VariableNames:
     print >> vector, "    "+Variable+"= -999;"
 
 print >> vector, "//Write_variables"
 for Variable in VariableNames:
     print >> vector, "    "+Variable+" = r"+Variable+";"
else :
 print >> vector, "//!!!!!!Please specify a correct Case!!!!!!//"
