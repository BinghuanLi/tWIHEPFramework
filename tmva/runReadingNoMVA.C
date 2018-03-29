#include "/publicfs/cms/user/duncanleg/tW13TeV/framework/tmva/mvaTool.C"

void runReadingNoMVA(TString sampleName, TString inDir, TString outDir)
{
  //  gROOT->LoadMacro("/publicfs/cms/user/duncanleg/tW13TeV/tmva/mvaTool.C");
  
  std::cout << sampleName;
  mvaTool t = mvaTool();
  
  t.doReadingNoMVA(sampleName,inDir,outDir);
  //t.doReading("tW_top_nfh","tW/","output/");

}
