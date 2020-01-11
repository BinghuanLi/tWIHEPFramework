#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys,os

treeName = "OutTree_"

datasets = [
# 2016
'Legacy16V2_SEleBlockB', 'Legacy16V2_SEleBlockC', 'Legacy16V2_SEleBlockD', 'Legacy16V2_SEleBlockE', 'Legacy16V2_SEleBlockF', 'Legacy16V2_SEleBlockG', 'Legacy16V2_SEleBlockH', 'Legacy16V2_SMuBlockB', 'Legacy16V2_SMuBlockC', 'Legacy16V2_SMuBlockD',
'Legacy16V2_SMuBlockE', 'Legacy16V2_SMuBlockF', 'Legacy16V2_SMuBlockG', 'Legacy16V2_SMuBlockH', 'Legacy16V2_DblEGBlockB', 'Legacy16V2_DblEGBlockC', 'Legacy16V2_DblEGBlockD', 'Legacy16V2_DblEGBlockE', 'Legacy16V2_DblEGBlockF', 'Legacy16V2_DblEGBlockG',
'Legacy16V2_DblEGBlockH', 'Legacy16V2_DblMuBlockB', 'Legacy16V2_DblMuBlockC', 'Legacy16V2_DblMuBlockD', 'Legacy16V2_DblMuBlockE', 'Legacy16V2_DblMuBlockF', 'Legacy16V2_DblMuBlockG', 'Legacy16V2_DblMuBlockH', 'Legacy16V2_MuEGBlockB', 'Legacy16V2_MuEGBlockC',
'Legacy16V2_MuEGBlockD', 'Legacy16V2_MuEGBlockE', 'Legacy16V2_MuEGBlockF', 'Legacy16V2_MuEGBlockG', 'Legacy16V2_MuEGBlockH',
# 2017
#'Legacy17V2_SEleBlockB', 'Legacy17V2_SEleBlockC', 'Legacy17V2_SEleBlockD', 'Legacy17V2_SEleBlockE', 'Legacy17V2_SEleBlockF', 'Legacy17V2_SMuBlockB', 'Legacy17V2_SMuBlockC', 'Legacy17V2_SMuBlockD', 'Legacy17V2_SMuBlockE', 'Legacy17V2_SMuBlockF',
#'Legacy17V2_DblEGBlockB', 'Legacy17V2_DblEGBlockC', 'Legacy17V2_DblEGBlockD', 'Legacy17V2_DblEGBlockE', 'Legacy17V2_DblEGBlockF', 'Legacy17V2_DblMuBlockB', 'Legacy17V2_DblMuBlockC', 'Legacy17V2_DblMuBlockD', 'Legacy17V2_DblMuBlockE', 'Legacy17V2_DblMuBlockF',
#'Legacy17V2_MuEGBlockB', 'Legacy17V2_MuEGBlockC', 'Legacy17V2_MuEGBlockD', 'Legacy17V2_MuEGBlockE', 'Legacy17V2_MuEGBlockF',
# 2018
#'Legacy18V2_SMuBlockA', 'Legacy18V2_SMuBlockB', 'Legacy18V2_SMuBlockC', 'Legacy18V2_SMuBlockD', 'Legacy18V2_EleGBlockA', 'Legacy18V2_EleGBlockB', 'Legacy18V2_EleGBlockC', 'Legacy18V2_EleGBlockD', 
#'Legacy18V2_DblMuBlockA', 
#'Legacy18V2_DblMuBlockB','Legacy18V2_DblMuBlockC', 'Legacy18V2_DblMuBlockD', 'Legacy18V2_MuEGBlockA', 'Legacy18V2_MuEGBlockB', 'Legacy18V2_MuEGBlockC', 'Legacy18V2_MuEGBlockD',
]


#datasets = [
#'Legacy18V2_EleGBlockC', 'Legacy18V2_EleGBlockD'
#]

datasetID = {
# 2016
'Legacy16V2_SEleBlockB':201000, 'Legacy16V2_SEleBlockC':201000, 'Legacy16V2_SEleBlockD':201000, 'Legacy16V2_SEleBlockE':201000, 'Legacy16V2_SEleBlockF':201000, 'Legacy16V2_SEleBlockG':201000, 'Legacy16V2_SEleBlockH':201000, 
'Legacy16V2_SMuBlockB':202000, 'Legacy16V2_SMuBlockC':202000, 'Legacy16V2_SMuBlockD':202000,'Legacy16V2_SMuBlockE':202000, 'Legacy16V2_SMuBlockF':202000, 'Legacy16V2_SMuBlockG':202000, 'Legacy16V2_SMuBlockH':202000, 
'Legacy16V2_DblEGBlockB':204000, 'Legacy16V2_DblEGBlockC':204000, 'Legacy16V2_DblEGBlockD':204000, 'Legacy16V2_DblEGBlockE':204000, 'Legacy16V2_DblEGBlockF':204000, 'Legacy16V2_DblEGBlockG':204000,'Legacy16V2_DblEGBlockH':204000, 
'Legacy16V2_DblMuBlockB':203000, 'Legacy16V2_DblMuBlockC':203000, 'Legacy16V2_DblMuBlockD':203000, 'Legacy16V2_DblMuBlockE':203000, 'Legacy16V2_DblMuBlockF':203000, 'Legacy16V2_DblMuBlockG':203000, 'Legacy16V2_DblMuBlockH':203000, 
'Legacy16V2_MuEGBlockB':205000, 'Legacy16V2_MuEGBlockC':205000,'Legacy16V2_MuEGBlockD':205000, 'Legacy16V2_MuEGBlockE':205000, 'Legacy16V2_MuEGBlockF':205000, 'Legacy16V2_MuEGBlockG':205000, 'Legacy16V2_MuEGBlockH':205000,
# 2017
'Legacy17V2_SEleBlockB':301000, 'Legacy17V2_SEleBlockC':301000, 'Legacy17V2_SEleBlockD':301000, 'Legacy17V2_SEleBlockE':301000, 'Legacy17V2_SEleBlockF':301000, 
'Legacy17V2_SMuBlockB':302000, 'Legacy17V2_SMuBlockC':302000, 'Legacy17V2_SMuBlockD':302000, 'Legacy17V2_SMuBlockE':302000, 'Legacy17V2_SMuBlockF':302000,
'Legacy17V2_DblEGBlockB':304000, 'Legacy17V2_DblEGBlockC':304000, 'Legacy17V2_DblEGBlockD':304000, 'Legacy17V2_DblEGBlockE':304000, 'Legacy17V2_DblEGBlockF':304000, 
'Legacy17V2_DblMuBlockB':303000, 'Legacy17V2_DblMuBlockC':303000, 'Legacy17V2_DblMuBlockD':303000, 'Legacy17V2_DblMuBlockE':303000, 'Legacy17V2_DblMuBlockF':303000,
'Legacy17V2_MuEGBlockB':305000, 'Legacy17V2_MuEGBlockC':305000, 'Legacy17V2_MuEGBlockD':305000, 'Legacy17V2_MuEGBlockE':305000, 'Legacy17V2_MuEGBlockF':305000,
# 2018
'Legacy18V2_SMuBlockA':402000, 'Legacy18V2_SMuBlockB':402000, 'Legacy18V2_SMuBlockC':402000, 'Legacy18V2_SMuBlockD':402000, 
'Legacy18V2_EleGBlockA':404000, 'Legacy18V2_EleGBlockB':404000, 'Legacy18V2_EleGBlockC':404000, 'Legacy18V2_EleGBlockD':404000, 
'Legacy18V2_DblMuBlockA':403000, 'Legacy18V2_DblMuBlockB':403000,'Legacy18V2_DblMuBlockC':403000, 'Legacy18V2_DblMuBlockD':403000, 
'Legacy18V2_MuEGBlockA':405000, 'Legacy18V2_MuEGBlockB':405000, 'Legacy18V2_MuEGBlockC':405000, 'Legacy18V2_MuEGBlockD':405000,
    }

datasetDirs = {
# 2016
"Legacy16V2_DblEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockB/191101_114331/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockB/191101_114331/0000",],
"Legacy16V2_DblEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockC/191101_114557/0000",],
"Legacy16V2_DblEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockD/191101_114824/0000",],
"Legacy16V2_DblEGBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockE/191101_115056/0000",],
"Legacy16V2_DblEGBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockF/191101_115323/0000",],
"Legacy16V2_DblEGBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockG/191101_115554/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockG/191101_115554/0000",],
"Legacy16V2_DblEGBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockH/191101_115823/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleEG/crab_Legacy16V2_DblEGBlockH/191101_115823/0000",],
"Legacy16V2_DblMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockB/191101_120055/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockB/191101_120055/0000",],
"Legacy16V2_DblMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockC/191101_120324/0000",],
"Legacy16V2_DblMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockD/191101_120554/0000",],
"Legacy16V2_DblMuBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockF/191101_121044/0000",],
"Legacy16V2_DblMuBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockG/191101_121309/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockG/191101_121309/0000",],
"Legacy16V2_DblMuBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockH/191101_121533/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockH/191101_121533/0000",],
"Legacy16V2_MuEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockB/191101_121758/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockB/191101_121758/0000",],
"Legacy16V2_MuEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockC/191101_122023/0000",],
"Legacy16V2_MuEGBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockE/191101_122509/0000",],
"Legacy16V2_MuEGBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockG/191101_122956/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockG/191101_122956/0000",],
"Legacy16V2_MuEGBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockH/191101_123217/0000",],
"Legacy16V2_SEleBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockB/191101_110745/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockB/191101_110745/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockB/191101_093557/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockB/191101_093557/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockB/191101_102900/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockB/191101_102900/0000",],
"Legacy16V2_SEleBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockC/191101_111038/0000",],
"Legacy16V2_SEleBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockD/191101_111328/0000",],
"Legacy16V2_SEleBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockE/191101_111618/0000",],
"Legacy16V2_SEleBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockF/191101_111850/0000",],
"Legacy16V2_SEleBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockG/191101_112123/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockG/191101_112123/0000",],
"Legacy16V2_SEleBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockH/191101_112353/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleElectron/crab_Legacy16V2_SEleBlockH/191101_112353/0000",],
"Legacy16V2_SMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockB/191101_112620/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockB/191101_112620/0000",],
"Legacy16V2_SMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockC/191101_112845/0000",],
"Legacy16V2_SMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockD/191101_113113/0000",],
"Legacy16V2_SMuBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockE/191101_113343/0000",],
"Legacy16V2_SMuBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockF/191101_113607/0000",],
"Legacy16V2_SMuBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockG/191101_113836/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockG/191101_113836/0000",],
"Legacy16V2_SMuBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockH/191101_114103/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2016/data/SingleMuon/crab_Legacy16V2_SMuBlockH/191101_114103/0000",],
"Legacy16V2_DblMuBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2.1/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockE/191101_120820/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2.1/2016/data/DoubleMuon/crab_Legacy16V2_DblMuBlockE/191101_120821/0000",],
"Legacy16V2_MuEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2.1/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockD/191101_122245/0000",],
"Legacy16V2_MuEGBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2.1/2016/data/MuonEG/crab_Legacy16V2_MuEGBlockF/191101_122732/0000",],

# 2017
#"Legacy17V2_DblEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockB/191102_210240/0000",],
#"Legacy17V2_DblEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockC/191102_210452/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockC/191102_210452/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockC/191115_153021/0000",],
#"Legacy17V2_DblEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockD/191102_210654/0000",],
#"Legacy17V2_DblEGBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockE/191102_210903/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockE/191102_210903/0000",],
#"Legacy17V2_DblEGBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockF/191115_153239/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockF/191102_211122/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleEG/crab_Legacy17V2_DblEGBlockF/191102_211122/0000",],
#"Legacy17V2_DblMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockB/191102_211336/0000",],
#"Legacy17V2_DblMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockC/191102_211541/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockC/191102_211541/0000",],
#"Legacy17V2_DblMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockD/191102_211750/0000",],
#"Legacy17V2_DblMuBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockE/191102_211954/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockE/191102_211954/0000",],
#"Legacy17V2_DblMuBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockF/191102_212200/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockF/191102_212200/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/DoubleMuon/crab_Legacy17V2_DblMuBlockF/191115_153456/0000",],
#"Legacy17V2_MuEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/MuonEG/crab_Legacy17V2_MuEGBlockB/191102_212407/0000",],
#"Legacy17V2_MuEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/MuonEG/crab_Legacy17V2_MuEGBlockC/191102_212615/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/MuonEG/crab_Legacy17V2_MuEGBlockC/191102_212615/0000",],
#"Legacy17V2_MuEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/MuonEG/crab_Legacy17V2_MuEGBlockD/191102_212817/0000",],
#"Legacy17V2_MuEGBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/MuonEG/crab_Legacy17V2_MuEGBlockE/191102_213023/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/MuonEG/crab_Legacy17V2_MuEGBlockE/191102_213023/0000",],
#"Legacy17V2_MuEGBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/MuonEG/crab_Legacy17V2_MuEGBlockF/191102_213228/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/MuonEG/crab_Legacy17V2_MuEGBlockF/191102_213228/0000",],
#"Legacy17V2_SEleBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockB/191102_204130/0000",],
#"Legacy17V2_SEleBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockC/191115_151859/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockC/191102_204337/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockC/191102_204337/0000",],
#"Legacy17V2_SEleBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockD/191102_204545/0000",],
#"Legacy17V2_SEleBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockE/191102_204748/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockE/191102_204748/0000",],
#"Legacy17V2_SEleBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockF/191115_152117/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockF/191102_204959/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleElectron/crab_Legacy17V2_SEleBlockF/191102_204959/0000",],
#"Legacy17V2_SMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockB/191102_205204/0000",],
#"Legacy17V2_SMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockC/191102_205412/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockC/191102_205412/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockC/191115_152335/0000",],
#"Legacy17V2_SMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockD/191102_205615/0000",],
#"Legacy17V2_SMuBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockE/191102_205821/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockE/191102_205821/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockE/191115_152552/0000",],
#"Legacy17V2_SMuBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockF/191102_210027/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockF/191102_210027/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2017/data/SingleMuon/crab_Legacy17V2_SMuBlockF/191115_152807/0000",],

# 2018
#"Legacy18V2_DblMuBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2.1/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockA/191209_141249/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2.1/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockA/191209_141249/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2.1/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockA/191209_141249/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2.1/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockA/191209_141249/0003",],
###"Legacy18V2_DblMuBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockA/191017_130841/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockA/191017_130841/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockA/191030_111048/0000",],
#"Legacy18V2_DblMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockB/191017_131104/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockB/191030_111309/0000",],
#"Legacy18V2_DblMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockC/191030_111532/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockC/191017_131328/0000",],
#"Legacy18V2_DblMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockD/191030_111750/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockD/191030_111750/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockD/191017_131552/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockD/191017_131552/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockD/191017_131552/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockD/191017_131552/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/DoubleMuon/crab_Legacy18V2_DblMuBlockD/191017_131552/0003",],
#"Legacy18V2_EleGBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191030_110358/0005","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191030_110358/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191030_110358/0006","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191030_110358/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191030_110358/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191030_110358/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191030_110358/0003","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191017_125910/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockA/191017_125910/0000",],
#"Legacy18V2_EleGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockB/191017_130136/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockB/191030_110614/0000",],
#"Legacy18V2_EleGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockC/191017_130406/0000",],
#"Legacy18V2_EleGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191017_130622/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191017_130622/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191017_130622/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191017_130622/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191017_130622/0003","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191030_110831/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191030_110831/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191030_110831/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/EGamma/crab_Legacy18V2_EleGBlockD/191030_110831/0003",],
#"Legacy18V2_MuEGBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockA/191030_112012/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockA/191017_131817/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockA/191017_131817/0000",],
#"Legacy18V2_MuEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockB/191030_112250/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockB/191030_112250/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockB/191030_112250/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockB/191017_132058/0000",],
#"Legacy18V2_MuEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockC/191017_132324/0000",],
#"Legacy18V2_MuEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191030_112508/0005","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191030_112508/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191030_112508/0006","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191030_112508/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191030_112508/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191030_112508/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191030_112508/0003","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191017_132559/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191017_132559/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191017_132559/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191017_132559/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/MuonEG/crab_Legacy18V2_MuEGBlockD/191017_132559/0003",],
#"Legacy18V2_SMuBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockA/191017_121828/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockA/191017_121828/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockA/191030_105703/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockA/191030_105703/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockA/191030_105703/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockA/191030_105703/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockA/191030_105703/0003",],
#"Legacy18V2_SMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockB/191017_125213/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockB/191030_105921/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockB/191030_105921/0000",],
#"Legacy18V2_SMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockC/191017_125431/0000",],
#"Legacy18V2_SMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockD/191030_110140/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockD/191017_125650/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockD/191017_125650/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockD/191017_125650/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockD/191017_125650/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V2/2018/data/SingleMuon/crab_Legacy18V2_SMuBlockD/191017_125650/0003",],

}


#datasetDirs = {"TTHnobb":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/FullMorV2_ttHnobb/170530_161519/0000/"],
#"TTWToLNuext2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/FullMorV2_amcTTWJetsToLNuext2/170531_182459/0000/"]
#}

import sys, math, mmap, subprocess

namesPerFile = float(raw_input("How many files to run over per job? "))
if namesPerFile == 0:
    print "You idiot, we can't divide by 0"
    sys.exit()
outputDirectory = raw_input("Output directory: ")

finishCopyScripts = raw_input("File for additional copies: ")
copyScript = 0
if finishCopyScripts:
    copyScript = file(finishCopyScripts,"w")
    print copyScript.write("#!/bin/bash\n")

for dataset in datasets:
    
    fileList = []
    for datasetDir in datasetDirs[dataset]:
        dataDir = datasetDir
        fileList += [os.path.join(dataDir,f) for f in os.listdir(dataDir) if ".root" in f]
    nJobs = int(math.ceil(len(fileList)/namesPerFile))
    print ("Dataset: {0}, ID: {1}. Number of jobs created = {2}".format(dataset,datasetID[dataset],nJobs))
    nFile = 0
    for i in range(nJobs):
        currentFile = open(outputDirectory + dataset + "_"+ str(i) + ".list","w")
        currentFile.write("Name: " + dataset)
        currentFile.write("\nNumber: " + str(datasetID[dataset]) + "_1\n")
        for j in range(int(namesPerFile)):
            if nFile >= len(fileList): continue
            currentFile.write(fileList[nFile]+"\n")
            nFile+=1
        currentFile.close()
        
    continue

        

    
print "Thank you for using the create jobs program. Have a nice day"
