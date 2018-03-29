// Example displaying two histograms and their ratio.
// Author: Olivier Couet
void ratioplot(TString Input, TString Output) {
   //Call input file
   TFile *inputfile = TFile::Open(Input);
   TH2F *LooselightFlavNum = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hLooseTagEff_lightFlavNum");
   TH2F *LooselightFlavDwn = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hLooseTagEff_lightFlavDwn");
   TH2F *LoosebFlavNum = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hLooseTagEff_bFlavNum");
   TH2F *LoosebFlavDwn = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hLooseTagEff_bFlavDwn");
   TH2F *LoosecFlavNum = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hLooseTagEff_cFlavNum");
   TH2F *LoosecFlavDwn = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hLooseTagEff_cFlavDwn");
  
   TH2F *MediumlightFlavNum = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hMediumTagEff_lightFlavNum");
   TH2F *MediumlightFlavDwn = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hMediumTagEff_lightFlavDwn");
   TH2F *MediumbFlavNum = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hMediumTagEff_bFlavNum");
   TH2F *MediumbFlavDwn = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hMediumTagEff_bFlavDwn");
   TH2F *MediumcFlavNum = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hMediumTagEff_cFlavNum");
   TH2F *MediumcFlavDwn = (TH2F*) inputfile->Get("00_HistogrammingTagEfficiency/hMediumTagEff_cFlavDwn");
   
   
   //Define output file
   TFile *newfile = new TFile(Output,"recreate");
   newfile->cd();
   
   TH2F *LooselightFlavPass = (TH2F*)LooselightFlavNum->Clone("LooselightFlavPass");
   TH2F *LooselightFlavTotal = (TH2F*)LooselightFlavDwn->Clone("LooselightFlavTotal");
   TH2F *LooselightFlavEff = (TH2F*)LooselightFlavNum->Clone("LooselightFlavEff");
   LooselightFlavEff->SetTitle("Efficiency of light Flavor jets passin b-jet requirement");
   LooselightFlavEff->Divide(LooselightFlavTotal);
   
   TH2F *LoosecFlavPass = (TH2F*)LoosecFlavNum->Clone("LoosecFlavPass");
   TH2F *LoosecFlavTotal = (TH2F*)LoosecFlavDwn->Clone("LoosecFlavTotal");
   TH2F *LoosecFlavEff = (TH2F*)LoosecFlavNum->Clone("LoosecFlavEff");
   LoosecFlavEff->SetTitle("Efficiency of c Flavor jets passin b-jet requirement");
   LoosecFlavEff->Divide(LoosecFlavTotal);
   
   TH2F *LoosebFlavPass = (TH2F*)LoosebFlavNum->Clone("LoosebFlavPass");
   TH2F *LoosebFlavTotal = (TH2F*)LoosebFlavDwn->Clone("LoosebFlavTotal");
   TH2F *LoosebFlavEff = (TH2F*)LoosebFlavNum->Clone("LoosebFlavEff");
   LoosebFlavEff->SetTitle("Efficiency of b Flavor jets passin b-jet requirement");
   LoosebFlavEff->Divide(LoosebFlavTotal);
   
   TH2F *MediumlightFlavPass = (TH2F*)MediumlightFlavNum->Clone("MediumlightFlavPass");
   TH2F *MediumlightFlavTotal = (TH2F*)MediumlightFlavDwn->Clone("MediumlightFlavTotal");
   TH2F *MediumlightFlavEff = (TH2F*)MediumlightFlavNum->Clone("MediumlightFlavEff");
   MediumlightFlavEff->SetTitle("Efficiency of light Flavor jets passin b-jet requirement");
   MediumlightFlavEff->Divide(MediumlightFlavTotal);
   
   TH2F *MediumcFlavPass = (TH2F*)MediumcFlavNum->Clone("MediumcFlavPass");
   TH2F *MediumcFlavTotal = (TH2F*)MediumcFlavDwn->Clone("MediumcFlavTotal");
   TH2F *MediumcFlavEff = (TH2F*)MediumcFlavNum->Clone("MediumcFlavEff");
   MediumcFlavEff->SetTitle("Efficiency of c Flavor jets passin b-jet requirement");
   MediumcFlavEff->Divide(MediumcFlavTotal);
   
   TH2F *MediumbFlavPass = (TH2F*)MediumbFlavNum->Clone("MediumbFlavPass");
   TH2F *MediumbFlavTotal = (TH2F*)MediumbFlavDwn->Clone("MediumbFlavTotal");
   TH2F *MediumbFlavEff = (TH2F*)MediumbFlavNum->Clone("MediumbFlavEff");
   MediumbFlavEff->SetTitle("Efficiency of b Flavor jets passin b-jet requirement");
   MediumbFlavEff->Divide(MediumbFlavTotal);
   
   newfile->Write();
   newfile->Close();
  
} 
