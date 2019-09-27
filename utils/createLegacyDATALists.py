#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys,os

treeName = "OutTree_"

datasets = [
# 2016
'Legacy16V1_SEleBlockB', 'Legacy16V1_SEleBlockC', 'Legacy16V1_SEleBlockD', 'Legacy16V1_SEleBlockE', 'Legacy16V1_SEleBlockF', 'Legacy16V1_SEleBlockG', 'Legacy16V1_SEleBlockH', 'Legacy16V1_SMuBlockB', 'Legacy16V1_SMuBlockC', 'Legacy16V1_SMuBlockD',
'Legacy16V1_SMuBlockE', 'Legacy16V1_SMuBlockF', 'Legacy16V1_SMuBlockG', 'Legacy16V1_SMuBlockH', 'Legacy16V1_DblEGBlockB', 'Legacy16V1_DblEGBlockC', 'Legacy16V1_DblEGBlockD', 'Legacy16V1_DblEGBlockE', 'Legacy16V1_DblEGBlockF', 'Legacy16V1_DblEGBlockG',
'Legacy16V1_DblEGBlockH', 'Legacy16V1_DblMuBlockB', 'Legacy16V1_DblMuBlockC', 'Legacy16V1_DblMuBlockD', 'Legacy16V1_DblMuBlockE', 'Legacy16V1_DblMuBlockF', 'Legacy16V1_DblMuBlockG', 'Legacy16V1_DblMuBlockH', 'Legacy16V1_MuEGBlockB', 'Legacy16V1_MuEGBlockC',
'Legacy16V1_MuEGBlockD', 'Legacy16V1_MuEGBlockE', 'Legacy16V1_MuEGBlockF', 'Legacy16V1_MuEGBlockG', 'Legacy16V1_MuEGBlockH',
# 2017
'Legacy17V1_SEleBlockB', 'Legacy17V1_SEleBlockC', 'Legacy17V1_SEleBlockD', 'Legacy17V1_SEleBlockE', 'Legacy17V1_SEleBlockF', 'Legacy17V1_SMuBlockB', 'Legacy17V1_SMuBlockC', 'Legacy17V1_SMuBlockD', 'Legacy17V1_SMuBlockE', 'Legacy17V1_SMuBlockF',
'Legacy17V1_DblEGBlockB', 'Legacy17V1_DblEGBlockC', 'Legacy17V1_DblEGBlockD', 'Legacy17V1_DblEGBlockE', 'Legacy17V1_DblEGBlockF', 'Legacy17V1_DblMuBlockB', 'Legacy17V1_DblMuBlockC', 'Legacy17V1_DblMuBlockD', 'Legacy17V1_DblMuBlockE', 'Legacy17V1_DblMuBlockF',
'Legacy17V1_MuEGBlockB', 'Legacy17V1_MuEGBlockC', 'Legacy17V1_MuEGBlockD', 'Legacy17V1_MuEGBlockE', 'Legacy17V1_MuEGBlockF',
# 2018
'Legacy18V1_SMuBlockA', 'Legacy18V1_SMuBlockB', 'Legacy18V1_SMuBlockC', 'Legacy18V1_SMuBlockD', 'Legacy18V1_EleGBlockA', 'Legacy18V1_EleGBlockB', 'Legacy18V1_EleGBlockC', 'Legacy18V1_EleGBlockD', 'Legacy18V1_DblMuBlockA', 'Legacy18V1_DblMuBlockB',
'Legacy18V1_DblMuBlockC', 'Legacy18V1_DblMuBlockD', 'Legacy18V1_MuEGBlockA', 'Legacy18V1_MuEGBlockB', 'Legacy18V1_MuEGBlockC', 'Legacy18V1_MuEGBlockD',
]


#datasets = [
#'Legacy18V1_EleGBlockC', 'Legacy18V1_EleGBlockD'
#]

datasetID = {
# 2016
'Legacy16V1_SEleBlockB':201000, 'Legacy16V1_SEleBlockC':201000, 'Legacy16V1_SEleBlockD':201000, 'Legacy16V1_SEleBlockE':201000, 'Legacy16V1_SEleBlockF':201000, 'Legacy16V1_SEleBlockG':201000, 'Legacy16V1_SEleBlockH':201000, 
'Legacy16V1_SMuBlockB':202000, 'Legacy16V1_SMuBlockC':202000, 'Legacy16V1_SMuBlockD':202000,'Legacy16V1_SMuBlockE':202000, 'Legacy16V1_SMuBlockF':202000, 'Legacy16V1_SMuBlockG':202000, 'Legacy16V1_SMuBlockH':202000, 
'Legacy16V1_DblEGBlockB':204000, 'Legacy16V1_DblEGBlockC':204000, 'Legacy16V1_DblEGBlockD':204000, 'Legacy16V1_DblEGBlockE':204000, 'Legacy16V1_DblEGBlockF':204000, 'Legacy16V1_DblEGBlockG':204000,'Legacy16V1_DblEGBlockH':204000, 
'Legacy16V1_DblMuBlockB':203000, 'Legacy16V1_DblMuBlockC':203000, 'Legacy16V1_DblMuBlockD':203000, 'Legacy16V1_DblMuBlockE':203000, 'Legacy16V1_DblMuBlockF':203000, 'Legacy16V1_DblMuBlockG':203000, 'Legacy16V1_DblMuBlockH':203000, 
'Legacy16V1_MuEGBlockB':205000, 'Legacy16V1_MuEGBlockC':205000,'Legacy16V1_MuEGBlockD':205000, 'Legacy16V1_MuEGBlockE':205000, 'Legacy16V1_MuEGBlockF':205000, 'Legacy16V1_MuEGBlockG':205000, 'Legacy16V1_MuEGBlockH':205000,
# 2017
'Legacy17V1_SEleBlockB':301000, 'Legacy17V1_SEleBlockC':301000, 'Legacy17V1_SEleBlockD':301000, 'Legacy17V1_SEleBlockE':301000, 'Legacy17V1_SEleBlockF':301000, 
'Legacy17V1_SMuBlockB':302000, 'Legacy17V1_SMuBlockC':302000, 'Legacy17V1_SMuBlockD':302000, 'Legacy17V1_SMuBlockE':302000, 'Legacy17V1_SMuBlockF':302000,
'Legacy17V1_DblEGBlockB':304000, 'Legacy17V1_DblEGBlockC':304000, 'Legacy17V1_DblEGBlockD':304000, 'Legacy17V1_DblEGBlockE':304000, 'Legacy17V1_DblEGBlockF':304000, 
'Legacy17V1_DblMuBlockB':303000, 'Legacy17V1_DblMuBlockC':303000, 'Legacy17V1_DblMuBlockD':303000, 'Legacy17V1_DblMuBlockE':303000, 'Legacy17V1_DblMuBlockF':303000,
'Legacy17V1_MuEGBlockB':305000, 'Legacy17V1_MuEGBlockC':305000, 'Legacy17V1_MuEGBlockD':305000, 'Legacy17V1_MuEGBlockE':305000, 'Legacy17V1_MuEGBlockF':305000,
# 2018
'Legacy18V1_SMuBlockA':402000, 'Legacy18V1_SMuBlockB':402000, 'Legacy18V1_SMuBlockC':402000, 'Legacy18V1_SMuBlockD':402000, 
'Legacy18V1_EleGBlockA':404000, 'Legacy18V1_EleGBlockB':404000, 'Legacy18V1_EleGBlockC':404000, 'Legacy18V1_EleGBlockD':404000, 
'Legacy18V1_DblMuBlockA':403000, 'Legacy18V1_DblMuBlockB':403000,'Legacy18V1_DblMuBlockC':403000, 'Legacy18V1_DblMuBlockD':403000, 
'Legacy18V1_MuEGBlockA':405000, 'Legacy18V1_MuEGBlockB':405000, 'Legacy18V1_MuEGBlockC':405000, 'Legacy18V1_MuEGBlockD':405000,
    }

datasetDirs = {
# 2016
"Legacy16V1_DblEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockB/190709_090929/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockB/190709_090929/0000"],
"Legacy16V1_DblEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockC/190709_091151/0000"],
"Legacy16V1_DblEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockD/190709_091409/0000"],
"Legacy16V1_DblEGBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockE/190709_091626/0000"],
"Legacy16V1_DblEGBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockF/190709_091852/0000"],
"Legacy16V1_DblEGBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockG/190709_092119/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockG/190709_092119/0000"],
"Legacy16V1_DblEGBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockH/190709_092337/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleEG/crab_Legacy16V1_DblEGBlockH/190709_092337/0000"],
"Legacy16V1_DblMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockB/190709_092555/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockB/190709_092555/0000"],
"Legacy16V1_DblMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockC/190709_092828/0000"],
"Legacy16V1_DblMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockD/190709_093053/0000"],
"Legacy16V1_DblMuBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockE/190709_093318/0000"],
"Legacy16V1_DblMuBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockF/190709_093551/0000"],
"Legacy16V1_DblMuBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockG/190709_093811/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockG/190709_093811/0000"],
"Legacy16V1_DblMuBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockH/190709_094030/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/DoubleMuon/crab_Legacy16V1_DblMuBlockH/190709_094030/0000"],
"Legacy16V1_MuEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockB/190709_094252/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockB/190709_094252/0000"],
"Legacy16V1_MuEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockC/190709_094519/0000"],
"Legacy16V1_MuEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockD/190709_094748/0000"],
"Legacy16V1_MuEGBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockE/190910_101042/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockE/190910_101042/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockE/190910_101042/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockE_recover/190910_160913/0000"],
"Legacy16V1_MuEGBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockF/190709_095247/0000"],
"Legacy16V1_MuEGBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockG/190709_095516/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockG/190709_095516/0000"],
"Legacy16V1_MuEGBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockH/190709_095753/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/MuonEG/crab_Legacy16V1_MuEGBlockH/190709_095753/0000"],
"Legacy16V1_SEleBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockB/190709_083611/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockB/190709_083611/0000"],
"Legacy16V1_SEleBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockC/190709_083828/0000"],
"Legacy16V1_SEleBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockD/190709_084048/0000"],
"Legacy16V1_SEleBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockE/190709_084312/0000"],
"Legacy16V1_SEleBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockF/190709_084532/0000"],
"Legacy16V1_SEleBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockG/190709_084753/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockG/190709_084753/0000"],
"Legacy16V1_SEleBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockH/190709_085015/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleElectron/crab_Legacy16V1_SEleBlockH/190709_085015/0000"],
"Legacy16V1_SMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockB/190709_085238/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockB/190709_085238/0000"],
"Legacy16V1_SMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockC/190709_085506/0000"],
"Legacy16V1_SMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockD/190709_085727/0000"],
"Legacy16V1_SMuBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockE/190709_085949/0000"],
"Legacy16V1_SMuBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockF/190709_090212/0000"],
"Legacy16V1_SMuBlockG":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockG/190709_090437/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockG/190709_090437/0000"],
"Legacy16V1_SMuBlockH":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockH/190709_090700/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2016/data/SingleMuon/crab_Legacy16V1_SMuBlockH/190709_090700/0000"],
# 2017
"Legacy17V1_DblEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockB/190821_153721/0000"],
"Legacy17V1_DblEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockC/190821_154023/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockC/190821_154023/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockC_recover/190828_165753/0000"],
"Legacy17V1_DblEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockD/190821_154358/0000"],
"Legacy17V1_DblEGBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockE/190821_154846/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockE/190821_154846/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockE_recover/190828_170604/0000"],
"Legacy17V1_DblEGBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockF/190821_155211/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockF/190821_155211/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleEG/crab_Legacy17V1_DblEGBlockF_recover/190828_164517/0000"],
"Legacy17V1_DblMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockB/190821_155545/0000"],
"Legacy17V1_DblMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockC/190821_155923/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockC/190821_155923/0000"],
"Legacy17V1_DblMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockD/190821_160219/0000"],
"Legacy17V1_DblMuBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockE/190821_160608/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockE/190821_160608/0000"],
"Legacy17V1_DblMuBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockF/190821_160912/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockF/190821_160912/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/DoubleMuon/crab_Legacy17V1_DblMuBlockF_recover/190828_170242/0000"],
"Legacy17V1_MuEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockB/190821_161154/0000"],
"Legacy17V1_MuEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockC/190821_161436/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockC/190821_161436/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockC_recover/190828_164951/0000"],
"Legacy17V1_MuEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockD/190821_161727/0000"],
"Legacy17V1_MuEGBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockE/190821_162232/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockE/190821_162232/0000"],
"Legacy17V1_MuEGBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockF/190821_162618/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/MuonEG/crab_Legacy17V1_MuEGBlockF/190821_162618/0000"],
"Legacy17V1_SEleBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockB/190821_150345/0000"],
"Legacy17V1_SEleBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockC/190821_150824/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockC/190821_150824/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockC_recover/190828_162621/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockC_recover_v2/190830_125736/0000"],
"Legacy17V1_SEleBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockD/190821_151251/0000"],
"Legacy17V1_SEleBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockE/190821_151645/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockE/190821_151645/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockE_recover/190828_163335/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockE_recover_v2/190830_130007/0000"],
"Legacy17V1_SEleBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockF/190821_151935/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockF/190821_151935/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockF_recover/190828_163551/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleElectron/crab_Legacy17V1_SEleBlockF_recover_v2/190830_130242/0000"],
"Legacy17V1_SMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockB/190821_152219/0000"],
"Legacy17V1_SMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockC/190821_152509/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockC/190821_152509/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockC_recover/190828_163813/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockC_recover_v2/190830_130517/0000"],
"Legacy17V1_SMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockD/190821_152800/0000",],
"Legacy17V1_SMuBlockE":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockE/190821_153049/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockE/190821_153049/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockE_recover/190828_164039/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockE_recover_v2/190830_130749/0000"],
"Legacy17V1_SMuBlockF":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockF/190821_153357/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockF/190821_153357/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockF_recover/190828_164301/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2017/data/SingleMuon/crab_Legacy17V1_SMuBlockF_recover_v2/190830_131020/0000"],

# 2018
"Legacy18V1_DblMuBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockA/190826_114819/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockA/190826_114819/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockA/190826_114819/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockA_recover/190901_143328/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockA_recoverv2/190904_093609/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockA_recoverv3/190904_230100/0000"],
"Legacy18V1_DblMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockB/190826_115341/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockB/190826_115341/0000"],
"Legacy18V1_DblMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockC/190826_120001/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockC/190826_120001/0000"],
"Legacy18V1_DblMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/DoubleMuon/crab_Legacy18V1_DblMuBlockD/190821_170941/0000"],
"Legacy18V1_EleGBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA/190826_112809/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA/190826_112809/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA/190826_112809/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA_recover/190901_142458/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA_recover/190901_142458/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA_recover/190901_142458/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA_recoverv2/190903_153742/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA_recoverv2/190903_153742/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA_recoverv3/190904_225905/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockA_recoverv3/190904_225905/0000"],
"Legacy18V1_EleGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockB/190826_113315/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockB/190826_113315/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockB_recover/190901_142706/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockB_recoverv2/190904_093333/0000",],
# this is found to be problematic , some root files are not close correclty
#"Legacy18V1_EleGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockC/190826_113814/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockC/190826_113814/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockC_recover/190901_142914/0000"],
#"Legacy18V1_EleGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190826_114323/0005","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190826_114323/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190826_114323/0006","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190826_114323/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190826_114323/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190826_114323/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190826_114323/0003","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD_recover/190901_143120/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD_recoverv2/190903_154225/0000"],
"Legacy18V1_EleGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockC/190922_131732/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockC/190922_131732/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockC/190922_131732/0000",],
"Legacy18V1_EleGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0005","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0006","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0007","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0008","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1.1/2018/data/EGamma/crab_Legacy18V1_EleGBlockD/190922_132650/0003",],
"Legacy18V1_MuEGBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/MuonEG/crab_Legacy18V1_MuEGBlockA/190826_120549/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/MuonEG/crab_Legacy18V1_MuEGBlockA/190826_120549/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/MuonEG/crab_Legacy18V1_MuEGBlockA/190826_120549/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/MuonEG/crab_Legacy18V1_MuEGBlockA_recover/190901_144015/0000"],
"Legacy18V1_MuEGBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/MuonEG/crab_Legacy18V1_MuEGBlockB/190826_121048/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/MuonEG/crab_Legacy18V1_MuEGBlockB/190826_121048/0000"],
"Legacy18V1_MuEGBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/MuonEG/crab_Legacy18V1_MuEGBlockC/190821_171615/0000"],
"Legacy18V1_MuEGBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/MuonEG/crab_Legacy18V1_MuEGBlockD/190821_171826/0000"],
"Legacy18V1_SMuBlockA":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA/190826_110917/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA/190826_110917/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA/190826_110917/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA_recover/190901_141833/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA_recover/190901_141833/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA_recoverv2/190903_153253/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA_recoverv2/190903_153253/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA_recoverv3/190904_225513/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA_recoverv3/190904_225513/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockA_recoverv3/190904_225513/0000"],
"Legacy18V1_SMuBlockB":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockB/190826_111325/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockB/190826_111325/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockB_recover/190901_142039/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockB_recoverv2/190903_153512/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockB_recoverv3/190904_225713/0000"],
"Legacy18V1_SMuBlockC":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockC/190826_111912/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockC/190826_111912/0000"],
"Legacy18V1_SMuBlockD":["/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockD/190826_112333/0005","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockD/190826_112333/0002","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockD/190826_112333/0006","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockD/190826_112333/0004","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockD/190826_112333/0001","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockD/190826_112333/0000","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockD/190826_112333/0003","/publicfs/cms/data/TopQuark/cms13TeV/Legacy_V1/2018/data/SingleMuon/crab_Legacy18V1_SMuBlockD_recover/190901_142243/0000"],

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
