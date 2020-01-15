import sys
import os
import optparse
import glob
import string
import subprocess
#####
##   Parameters to be specified by the user
#####
# options 
usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-s', '--sample',        dest='sampleType'  ,      help='sample types, isSigExt, isDNN, isData or isHjtagger',      default='isSigExt',        type='string')
parser.add_option('-j', '--jec',        dest='jec'  ,      help='jec and met types, nominal, MetShiftUp, MetShiftDown, JESUp, JESDown, JERUp, or JERDown',      default='nominal',        type='string')
parser.add_option('-u', '--unc',        dest='jecsource'  ,      help='jec source types',      default='null',        type='string')
parser.add_option('-y', '--year',        dest='year'  ,      help='data taking period 2016, 2017, or 2018',      default='2018',        type='int')
parser.add_option('-n', '--nlep',        dest='nlep'  ,      help='number of selected leptons 2, 3 or 4',      default='2',        type='int')


#analysis and task
analysis = "ttH"
taskname = "EvtSel"
frameworkDir = "/publicfs/cms/data/TopQuark/cms13TeV/Binghuan/tWIHEPFramework/"
executable = "bin/ttH/ttH_generic.x"
configFile = "config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLepton.All.config"
#invPostfix = " -MCatNLO -mc -bTagReshape -PileUpWgt -ReCalPU -TriggerSFs -lepSFs -FakeRate -chargeMis -Prefire"
invPostfix = " -MCatNLO -mc -bTagReshape -PileUpWgt -ReCalPU -Prefire -TriggerSFs -FakeRate -lepSFs" # -chargeMis "
mcPostfix = " "
triggerName = "TTHLep_2L "
fileListDirectory = "config/files/ttH_Legacy/Tau2p1Jobs/mc/"
makeSkims = True

samples2016Data = [
'Legacy16V2_SEleBlockB', 'Legacy16V2_SEleBlockC', 'Legacy16V2_SEleBlockD', 'Legacy16V2_SEleBlockE', 'Legacy16V2_SEleBlockF', 'Legacy16V2_SEleBlockG', 'Legacy16V2_SEleBlockH', 'Legacy16V2_SMuBlockB', 'Legacy16V2_SMuBlockC', 'Legacy16V2_SMuBlockD',
'Legacy16V2_SMuBlockE', 'Legacy16V2_SMuBlockF', 'Legacy16V2_SMuBlockG', 'Legacy16V2_SMuBlockH', 'Legacy16V2_DblEGBlockB', 'Legacy16V2_DblEGBlockC', 'Legacy16V2_DblEGBlockD', 'Legacy16V2_DblEGBlockE', 'Legacy16V2_DblEGBlockF', 'Legacy16V2_DblEGBlockG',
'Legacy16V2_DblEGBlockH', 'Legacy16V2_DblMuBlockB', 'Legacy16V2_DblMuBlockC', 'Legacy16V2_DblMuBlockD', 'Legacy16V2_DblMuBlockE', 'Legacy16V2_DblMuBlockF', 'Legacy16V2_DblMuBlockG', 'Legacy16V2_DblMuBlockH', 'Legacy16V2_MuEGBlockB', 'Legacy16V2_MuEGBlockC',
'Legacy16V2_MuEGBlockD', 'Legacy16V2_MuEGBlockE', 'Legacy16V2_MuEGBlockF', 'Legacy16V2_MuEGBlockG', 
'Legacy16V2_MuEGBlockH',
]

samples2017Data = [
'Legacy17V2_SEleBlockB', 'Legacy17V2_SEleBlockC', 'Legacy17V2_SEleBlockD', 'Legacy17V2_SEleBlockE', 'Legacy17V2_SEleBlockF', 'Legacy17V2_SMuBlockB', 'Legacy17V2_SMuBlockC', 'Legacy17V2_SMuBlockD', 'Legacy17V2_SMuBlockE', 'Legacy17V2_SMuBlockF',
'Legacy17V2_DblEGBlockB', 'Legacy17V2_DblEGBlockC', 'Legacy17V2_DblEGBlockD', 'Legacy17V2_DblEGBlockE', 'Legacy17V2_DblEGBlockF', 'Legacy17V2_DblMuBlockB', 'Legacy17V2_DblMuBlockC', 'Legacy17V2_DblMuBlockD', 'Legacy17V2_DblMuBlockE', 'Legacy17V2_DblMuBlockF',
'Legacy17V2_MuEGBlockB', 'Legacy17V2_MuEGBlockC', 'Legacy17V2_MuEGBlockD', 'Legacy17V2_MuEGBlockE', 
'Legacy17V2_MuEGBlockF',
]

samples2018Data = [
'Legacy18V2_SMuBlockA', 'Legacy18V2_SMuBlockB', 'Legacy18V2_SMuBlockC', 'Legacy18V2_SMuBlockD', 'Legacy18V2_EleGBlockA', 'Legacy18V2_EleGBlockB', 'Legacy18V2_EleGBlockC', 'Legacy18V2_EleGBlockD', 'Legacy18V2_DblMuBlockA', 'Legacy18V2_DblMuBlockB',
'Legacy18V2_DblMuBlockC', 'Legacy18V2_DblMuBlockD', 'Legacy18V2_MuEGBlockA', 'Legacy18V2_MuEGBlockB', 'Legacy18V2_MuEGBlockC', 
'Legacy18V2_MuEGBlockD',
]

samples2016MC=[
"Legacy16V2_ttHnobb", 
"Legacy16V2_TTH_ctcvcp", "Legacy16V2_THQ_TuneCP5_ctcvcp", "Legacy16V2_THW_TuneCP5_ctcvcp", "Legacy16V2_TTWJets", 
"Legacy16V2_TTWW", "Legacy16V2_TTZ_M1to10", "Legacy16V2_TTZ_M10_ext1", "Legacy16V2_TTZ_M10_ext2", "Legacy16V2_ST_sCh_lepDecay_PS", "Legacy16V2_ST_tCh_top", "Legacy16V2_ST_tCh_antitop_PS", "Legacy16V2_ST_tW_top", 
"Legacy16V2_ST_tW_antitop", "Legacy16V2_tWll", "Legacy16V2_TTGJets_v1", "Legacy16V2_TTGJets_ext", "Legacy16V2_TGJetsLep", 
"Legacy16V2_ZGToLLG", 
#"Legacy16V2_WGToLNuG_ext1", "Legacy16V2_WGToLNuG_ext2", "Legacy16V2_WGToLNuG_ext3", 
#"Legacy16V2_DYJets_M10to50", "Legacy16V2_DYJets_M50", #"Legacy16V2_W1JetsToLNu", "Legacy16V2_W2JetsToLNu_v1", "Legacy16V2_W2JetsToLNu_ext", "Legacy16V2_W3JetsToLNu_v1", "Legacy16V2_W3JetsToLNu_ext", "Legacy16V2_W4JetsToLNu_v1","Legacy16V2_W4JetsToLNu_ext", 
"Legacy16V2_WZG", "Legacy16V2_WWTo2LNu", "Legacy16V2_WZTo3LNu", "Legacy16V2_ZZTo4L",
"Legacy16V2_WW_DS", "Legacy16V2_WWW", "Legacy16V2_WWZ", "Legacy16V2_WZZ", "Legacy16V2_ZZZ", "Legacy16V2_TTTT", "Legacy16V2_tZq_ext", "Legacy16V2_WpWpJJ", "Legacy16V2_GGHToTauTau",
"Legacy16V2_VBFHToTauTau", "Legacy16V2_VHToNonbb", "Legacy16V2_ZHTobb", "Legacy16V2_ZHToTauTau", "Legacy16V2_ggHToTauTau_v3", "Legacy16V2_ggHToZZTo4L", "Legacy16V2_ggHToWWToLNuQQ", "Legacy16V2_ggHToWWTo2L2Nu", "Legacy16V2_ggHToMuMu", "Legacy16V2_ggHToBB_v2",
"Legacy16V2_ggHToBB_ext1", "Legacy16V2_ggHToGG", "Legacy16V2_VBFHToZZTo4L", "Legacy16V2_VBFHToWWToLNuQQ", "Legacy16V2_VBFHToWWTo2L2Nu", "Legacy16V2_VBFHToMuMu", "Legacy16V2_VBFHToBB_v1", "Legacy16V2_VBFHToBB_ext1", "Legacy16V2_VBFHToGG_ext1", "Legacy16V2_TTWH",
"Legacy16V2_TTZH", "Legacy16V2_ggHHTo2B2VTo2L2Nu_nodeSM", "Legacy16V2_ggHHTo2B2VTo2L2Nu_nodebox", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node1", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node2", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node3", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node4", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node5", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node6", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node7",
"Legacy16V2_ggHHTo2B2VTo2L2Nu_node8", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node9", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node10", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node11", "Legacy16V2_ggHHTo2B2VTo2L2Nu_node12", "Legacy16V2_ggHHTo2B2Tau_nodeSM", "Legacy16V2_ggHHTo2B2Tau_nodebox", "Legacy16V2_ggHHTo2B2Tau_node2", "Legacy16V2_ggHHTo2B2Tau_node9", "Legacy16V2_ggHHTo2B2Tau_node10",
"Legacy16V2_ggHHTo2B2Tau_node11", "Legacy16V2_ggHHTo2B2Tau_node12", "Legacy16V2_ggHHTo2B2Tau_node13", "Legacy16V2_ggHHTo4Tau_nodeSM", "Legacy16V2_ggHHTo4Tau_nodebox", "Legacy16V2_ggHHTo4Tau_node2", "Legacy16V2_ggHHTo4Tau_node3", "Legacy16V2_ggHHTo4Tau_node4", "Legacy16V2_ggHHTo4Tau_node5", "Legacy16V2_ggHHTo4Tau_node6",
"Legacy16V2_ggHHTo4Tau_node7", "Legacy16V2_ggHHTo4Tau_node8", "Legacy16V2_ggHHTo4Tau_node9", "Legacy16V2_ggHHTo4Tau_node10", "Legacy16V2_ggHHTo4Tau_node11", "Legacy16V2_ggHHTo4Tau_node12", "Legacy16V2_TTJets_DiLep_v1", 
"Legacy16V2_TTJets_DiLep_ext",
"Legacy16V2_TTJets_TToSingleLep_v1", "Legacy16V2_TTJets_TToSingleLep_ext", "Legacy16V2_TTJets_TbarToSingleLep_v1", "Legacy16V2_TTJets_TbarToSingleLep_ext", 
]

samples2016MVA=[
"Legacy16V2_TTHnobb","Legacy16V2_THQ_Tune8M1_ctcvcp","Legacy16V2_THQ","Legacy16V2_THW_Tune8M1_ctcvcp","Legacy16V2_THW","Legacy16V2_TTTo2L_PS","Legacy16V2_TTToSemiLep_PS","Legacy16V2_TTToHad_PS","Legacy16V2_ttZ",
"Legacy16V2_ttW",
]

samples2017MC=[
"Legacy17V2_ttHnobb", 
"Legacy17V2_TTH_ctcvcp", "Legacy17V2_THQ_ctcvcp", "Legacy17V2_THW_ctcvcp", "Legacy17V2_TTW_PS", "Legacy17V2_TTWW", "Legacy17V2_TTZ_M1to10",
"Legacy17V2_TTZ_M10_PS", "Legacy17V2_ST_sCh_lepDecay_PS", "Legacy17V2_ST_tCh_top_PS", "Legacy17V2_ST_tCh_antitop_PS", "Legacy17V2_ST_tW_top_PS",
"Legacy17V2_ST_tW_antitop_PS", "Legacy17V2_tWll", "Legacy17V2_TTGJets_v1", 
"Legacy17V2_TTGJets_ext", "Legacy17V2_TGJetsLep", "Legacy17V2_ZGToLLG_01J", 
#"Legacy17V2_WGToLNuG_Tune", 
#"Legacy17V2_WJets_ext", "Legacy17V2_WJets_v1",
#"Legacy17V2_W1JetsToLNu", "Legacy17V2_W2JetsToLNu", "Legacy17V2_W3JetsToLNu", "Legacy17V2_W4JetsToLNu", 
#"Legacy17V2_DYJets_M10to50_v1", "Legacy17V2_DYJets_M10to50_ext", "Legacy17V2_DYJets_M50_v1", "Legacy17V2_DYJets_M50_ext", 
"Legacy17V2_WZG", "Legacy17V2_WWTo2LNu_v1", "Legacy17V2_WWTo2LNu_ext", "Legacy17V2_WZTo3LNu", "Legacy17V2_ZZTo4L_v1", "Legacy17V2_ZZTo4L_ext1", "Legacy17V2_ZZTo4L_ext2", 
"Legacy17V2_WW_DS", "Legacy17V2_WWW", "Legacy17V2_WWZ", "Legacy17V2_WZZ", "Legacy17V2_ZZZ", "Legacy17V2_TTTT_PS", "Legacy17V2_tZq", "Legacy17V2_WpWpJJ",
"Legacy17V2_GGHToTauTau_v1", "Legacy17V2_GGHToTauTau_ext", "Legacy17V2_VBFHToTauTau", "Legacy17V2_VHToNonbb", "Legacy17V2_ZHTobb", "Legacy17V2_ZHToTauTau", "Legacy17V2_ggHToZZTo4L_ext1", "Legacy17V2_ggHToZZTo4L_ext3", "Legacy17V2_ggHToZZTo4L_ext4", "Legacy17V2_ggHToZZTo2L2Q",
"Legacy17V2_ggHToWWToLNuQQ", "Legacy17V2_ggHToWWTo2L2Nu", "Legacy17V2_ggHToMuMu_v1", "Legacy17V2_ggHToMuMu_ext1", "Legacy17V2_ggHToBB", "Legacy17V2_ggHToGG", "Legacy17V2_VBFHToZZTo4L_ext2", "Legacy17V2_VBFHToZZTo4L_ext1", "Legacy17V2_VBFHToZZTo4L_v1", "Legacy17V2_VBFHToWWToLNuQQ", 
"Legacy17V2_VBFHToWWTo2L2Nu", "Legacy17V2_VBFHToMuMu", "Legacy17V2_VBFHToBB", "Legacy17V2_VBFHToGG", "Legacy17V2_TTWH", "Legacy17V2_TTZH", "Legacy17V2_ggHHTo2B2VTo2L2Nu_nodeSM", "Legacy17V2_ggHHTo2B2VTo2L2Nu_node2", "Legacy17V2_ggHHTo2B2VTo2L2Nu_node3", "Legacy17V2_ggHHTo2B2VTo2L2Nu_node7",
"Legacy17V2_ggHHTo2B2VTo2L2Nu_node9", "Legacy17V2_ggHHTo2B2VTo2L2Nu_node12", "Legacy17V2_ggHHTo2B2Tau_nodeSM", "Legacy17V2_ggHHTo2B2Tau_node2", "Legacy17V2_ggHHTo2B2Tau_node3", "Legacy17V2_ggHHTo2B2Tau_node4", "Legacy17V2_ggHHTo2B2Tau_node7", "Legacy17V2_ggHHTo2B2Tau_node9", "Legacy17V2_ggHHTo2B2Tau_node12", "Legacy17V2_ggHHTo4Tau_nodeSM",
"Legacy17V2_ggHHTo4Tau_node2", "Legacy17V2_ggHHTo4Tau_node3", "Legacy17V2_ggHHTo4Tau_node7", "Legacy17V2_ggHHTo4Tau_node9", "Legacy17V2_ggHHTo4Tau_node12", "Legacy17V2_ggHHTo2V2Tau_nodeSM", "Legacy17V2_ggHHTo2V2Tau_node2", "Legacy17V2_ggHHTo2V2Tau_node3", "Legacy17V2_ggHHTo2V2Tau_node4", "Legacy17V2_ggHHTo2V2Tau_node5",
"Legacy17V2_ggHHTo2V2Tau_node6", "Legacy17V2_ggHHTo2V2Tau_node7", "Legacy17V2_ggHHTo2V2Tau_node8", "Legacy17V2_ggHHTo2V2Tau_node9", "Legacy17V2_ggHHTo2V2Tau_node10", "Legacy17V2_ggHHTo2V2Tau_node11", "Legacy17V2_ggHHTo2V2Tau_node12", "Legacy17V2_ggHHTo4V_nodeSM", "Legacy17V2_ggHHTo4V_node2", "Legacy17V2_ggHHTo4V_node3",
"Legacy17V2_ggHHTo4V_node4", "Legacy17V2_ggHHTo4V_node5", "Legacy17V2_ggHHTo4V_node6", "Legacy17V2_ggHHTo4V_node7", "Legacy17V2_ggHHTo4V_node8", "Legacy17V2_ggHHTo4V_node9", "Legacy17V2_ggHHTo4V_node10", "Legacy17V2_ggHHTo4V_node11", "Legacy17V2_ggHHTo4V_node12", 
"Legacy17V2_TTJets_DiLep", 
"Legacy17V2_TTJets_TToSingleLep", "Legacy17V2_TTJets_TbarToSingleLep",
]

samples2017MVA=[
"Legacy17V2_TTHnobb_v1","Legacy17V2_TTHnobb_ext","Legacy17V2_TTTo2L","Legacy17V2_TTTo2L_PS","Legacy17V2_TTToSemiLep","Legacy17V2_TTToSemiLep_PS","Legacy17V2_TTToHad","Legacy17V2_TTToHad_PS","Legacy17V2_ttZ_v1","Legacy17V2_ttZ_ext","Legacy17V2_ttW_v1","Legacy17V2_ttW_ext",
]

samples2018MC=[
"Legacy18V2_ttHToNonbb", 
"Legacy18V2_TTH_ctcvcp","Legacy18V2_THQ_ctcvcp", "Legacy18V2_THW_ctcvcp", "Legacy18V2_TTWJets", "Legacy18V2_TTWW_ext1", "Legacy18V2_TTWW_ext2", "Legacy18V2_TTZ_M1to10", "Legacy18V2_TTZ_M10",
"Legacy18V2_ST_sCh_lepDecay", "Legacy18V2_ST_tCh_top", "Legacy18V2_ST_tCh_antitop", "Legacy18V2_ST_tW_top", "Legacy18V2_ST_tW_antitop", "Legacy18V2_tWll",  "Legacy18V2_TTGJets", 
"Legacy18V2_TGJetsLep", "Legacy18V2_ZGToLLG_01J", 
#"Legacy18V2_WGToLNuG_Tune", 
#"Legacy18V2_W1JetsToLNu", "Legacy18V2_W2JetsToLNu", "Legacy18V2_W3JetsToLNu", "Legacy18V2_W4JetsToLNu", "Legacy18V2_DYJets_M10to50", "Legacy18V2_DYJets_M50_v1", "Legacy18V2_DYJets_M50_ext", "Legacy18V2_WJets", 
"Legacy18V2_WZG", "Legacy18V2_WWTo2LNu", "Legacy18V2_WZTo3LNu_v1", "Legacy18V2_WZTo3LNu_ext", "Legacy18V2_ZZTo4L_v1", "Legacy18V2_ZZTo4L_ext", 
"Legacy18V2_WW_DS", "Legacy18V2_WWW", "Legacy18V2_WWZ",
"Legacy18V2_WZZ", "Legacy18V2_ZZZ", "Legacy18V2_TTTT", "Legacy18V2_tZq", "Legacy18V2_WpWpJJ", "Legacy18V2_GGHToTauTau", "Legacy18V2_VBFHToTauTau", "Legacy18V2_VHToNonbb", "Legacy18V2_ZHTobb_v2", "Legacy18V2_ZHTobb_ext",
"Legacy18V2_ZHToTauTau", "Legacy18V2_ggHToZZTo4L", "Legacy18V2_ggHToZZTo2L2Q", "Legacy18V2_ggHToWWToLNuQQ", "Legacy18V2_ggHToWWTo2L2Nu", "Legacy18V2_ggHToMuMu_v2", "Legacy18V2_ggHToMuMu_ext1", "Legacy18V2_ggHToBB", "Legacy18V2_ggHToGG", "Legacy18V2_VBFHToZZTo4L",
"Legacy18V2_VBFHToWWToLNuQQ", "Legacy18V2_VBFHToWWTo2L2Nu", "Legacy18V2_VBFHToMuMu", "Legacy18V2_VBFHToBB", "Legacy18V2_VBFHToGG", "Legacy18V2_TTWH", "Legacy18V2_TTZH", "Legacy18V2_ggHTo2B2Tau_nodeSM", "Legacy18V2_ggHTo2B2Tau_node2", "Legacy18V2_ggHTo2B2Tau_node3",
"Legacy18V2_ggHTo2B2Tau_node4", "Legacy18V2_ggHTo2B2Tau_node5", "Legacy18V2_ggHTo2B2Tau_node6", "Legacy18V2_ggHTo2B2Tau_node7", "Legacy18V2_ggHTo2B2Tau_node8", "Legacy18V2_ggHTo2B2Tau_node9", "Legacy18V2_ggHTo2B2Tau_node10", "Legacy18V2_ggHTo2B2Tau_node11", "Legacy18V2_ggHTo2B2Tau_node12", 
"Legacy18V2_TTJets_TbarToSingleLep", "Legacy18V2_TTJets_TToSingleLep", 
"Legacy18V2_TTJets_DiLep",
]

samples2018MVA=[
"Legacy18V2_TTHnobb","Legacy18V2_TTTo2L","Legacy18V2_TTToSemiLep","Legacy18V2_TTToHad","Legacy18V2_ttW_Tune","Legacy18V2_ttZ_Tune",
# the following sample should be split into 2/3 for training , 1/3 for signal extraction based on nEvent % 3 == 0 or not
"Legacy18V2_THQ_ctcvcp","Legacy18V2_THW_ctcvcp",
]

(opt, args) = parser.parse_args()
sampleType = opt.sampleType
jec = opt.jec
jecsource = opt.jecsource
year = opt.year
nlep = opt.nlep 


SamplesAll = {
"2016":{"isDNN":samples2016MVA,"isHjtagger":samples2016MVA,"isSigExt":samples2016MC,"isData":samples2016Data},
"2017":{"isDNN":samples2017MVA,"isHjtagger":samples2017MVA,"isSigExt":samples2017MC,"isData":samples2017Data},
"2018":{"isDNN":samples2018MVA,"isHjtagger":samples2018MVA,"isSigExt":samples2018MC,"isData":samples2018Data},
}

def SetPars(YEAR, JEC, JECSource, SampleType, NLEP): 
    InvPostfix = invPostfix
    Analysis = analysis
    TriggerName = triggerName
    ConfigFile = configFile
    FileListDirectory = fileListDirectory
    sYear = str(YEAR)
    Analysis +=  sYear
    if SampleType == "isDNN":
        Analysis += "TrainDNN"
        Sample = SamplesAll[sYear][SampleType]
        #InvPostfix += " -isTrainMVA -FakeRate"
        InvPostfix += " -isTrainMVA"  # always use -FakeRate, check the invPostfix 
        if JEC == "nominal" and NLEP==2:
            Analysis +=  "2L"
            TriggerName = "TTHLep_2L"
            ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton.TrainMVA.config"
        else:
            print (" SampleType isDNN, skip JEC type %s with NLEP %i"%(JEC,NLEP))
            sys.exit()
    elif SampleType == "isHjtagger":
        Analysis += "TrainHj"
        Sample = SamplesAll[sYear][SampleType]
        if JEC == "nominal" and NLEP==2:
            Analysis +=  "2L"
            TriggerName = "TTHLep_2L"
            ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton.All.config"
        else:
            print (" SampleType isHjtagger, skip JEC type %s with NLEP %i"%(JEC,NLEP))
            sys.exit()
    elif SampleType == "isSigExt":
        Sample = SamplesAll[sYear][SampleType]
        if JEC == "nominal":
            Analysis += "All"
            if NLEP==2:
                Analysis +=  "2L"
                TriggerName = "TTHLep_2L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton.All.config"
            elif NLEP==3:
                Analysis +=  "3L"
                TriggerName = "TTHLep_3L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.TriLepton.All.config"
            elif NLEP==4:
                Analysis +=  "4L"
                TriggerName = "TTHLep_4L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.QuaLepton.All.config"
            else:
                print (" SampleType isSigExt, skip JEC type %s with NLEP %i"%(JEC,NLEP))
                sys.exit()
                
        elif JEC in ["JERUp", "JERDown","MetShiftUp","MetShiftDown"]:
            Analysis += "SR"
            if NLEP==2:
                Analysis +=  "2L%s"%JEC
                TriggerName = "TTHLep_2L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton%s.SR.config"%JEC
            else:
                print (" SampleType isSigExt, skip JEC type %s with NLEP %i"%(JEC,NLEP))
                sys.exit()
        elif JEC in ["JESUp", "JESDown"]:
            Analysis += "SR"
            if NLEP==2:
                if JECSource in ["FlavorQCD","RelativeBal","HF","BBEC1","EC2","Absolute","BBEC1_2016","EC2_2016","Absolute_2016","HF_2016","RelativeSample_2016","BBEC1_2017","EC2_2017","Absolute_2017","HF_2017","RelativeSample_2017", "BBEC1_2018","EC2_2018","Absolute_2018","HF_2018","RelativeSample_2018"]:
                    if "_" in JECSource and sYear not in JECSource:
                        print (" Skip JecSource %s for era %s"%(JECSource, sYear))
                        sys.exit()
                    else:
                        Analysis +=  "2L%s_%s"%(JEC,JECSource)
                        TriggerName = "TTHLep_2L"
                        InvPostfix += " -JecSourceName %s"%JECSource  
                        ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton%s.SR.config"%JEC
            else:
                print (" SampleType isSigExt, skip JEC type %s with NLEP %i"%(JEC,NLEP))
                sys.exit()
        else:
            print (" SampleType isSigExt, skip JEC type %s with NLEP %i"%(JEC,NLEP))
            sys.exit()
    elif SampleType == "isData":
        InvPostfix = " -FakeRate -chargeMis"
        Analysis += "Data"
        Sample = SamplesAll[sYear][SampleType]
        FileListDirectory = "config/files/ttH_Legacy/Tau2p1Jobs/data/"
        if JEC == "nominal":
            if NLEP==2:
                Analysis +=  "2L"
                TriggerName = "TTHLep_2L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton.All.config"
            elif NLEP==3:
                InvPostfix = " -FakeRate"
                Analysis +=  "3L"
                TriggerName = "TTHLep_3L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.TriLepton.All.config"
            elif NLEP==4:
                InvPostfix = " -FakeRate"
                Analysis +=  "4L"
                TriggerName = "TTHLep_4L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.QuaLepton.All.config"
            else:
                print (" SampleType isData, skip JEC type %s with NLEP %i"%(JEC,NLEP))
                sys.exit()
        else:
            print (" SampleType isData, skip JEC type %s with NLEP %i"%(JEC,NLEP))
            sys.exit()
    else: 
        print (" SampleType %s, skip "%SampleType)
        sys.exit()
    return Analysis, Sample, TriggerName, ConfigFile, InvPostfix, FileListDirectory


analysis, sample, triggerName, configFile, invPostfix, fileListDirectory =  SetPars(year, jec, jecsource, sampleType, nlep)

#for the queue
workpath    = os.getcwd()+"/"+analysis +"/"
jobDir      = workpath+"/"+"Jobs"
smallerJobs = True
AnalyzerDir = workpath+"/"+"Analyzer"

#####
##   The script itsself
#####
#cshFilePath = jobDir+"/"+"sh"
#logFilePath = jobDir+"/"+"log"
if os.path.exists(jobDir):
    os.popen('rm -fr '+jobDir)
if os.path.exists(AnalyzerDir):
        os.popen('rm -fr '+AnalyzerDir)
#os.popen('mkdir -p '+cshFilePath)
#os.popen('mkdir -p '+logFilePath)
allSubmit = 0
allMerge = 0
if os.path.exists(os.getcwd()+"/all.sh"):
    allSubmit = open(os.getcwd()+"/all.sh","a")
    allMerge = open(os.getcwd()+"/mergeAll.sh","a")
else:
    allSubmit = open(os.getcwd()+"/all.sh","w")
    allMerge = open(os.getcwd()+"/mergeAll.sh","w")
    allSubmit.write("#!/bin/bash\n")
    allMerge.write("#!/bin/bash\n")
allSubmit.write("bash "+analysis+"Submit.sh\n")
allMerge.write("bash "+analysis+"merge.sh\n")
allSubmit.close()
allMerge.close()

allJobFileName = analysis+"Submit.sh"
allJobFile      = file(allJobFileName,"w")
print >> allJobFile, "#!/bin/bash"
print >> allJobFile, "cd ",analysis

MergeFileName = analysis+"merge.sh"
MergeFile      = file(MergeFileName,"w")
MergeSourceFile = " "
def prepareSubmitJob(submitFileName,cshFileName, outPutFileName, errorFileName):
    cshFile      = file(submitFileName,"w")
    print >> cshFile, "Universe     = vanilla"
    print >> cshFile, "getenv       = true"
    print >> cshFile, "Executable   = ",cshFileName
    print >> cshFile, "Output       = ",outPutFileName
    print >> cshFile, "Error        = ",errorFileName
    print >> cshFile, "Queue"

def prepareCshJob(sample,shFile,frameworkDir,workpath,samplePost=""):
        subFile      = file(shFile,"w")
        print >> subFile, "#!/bin/bash"
        print >> subFile, "/bin/hostname"
        print >> subFile, "source /cvmfs/sft.cern.ch/lcg/views/LCG_93/x86_64-slc6-gcc62-opt/setup.sh"
        print >> subFile, "gcc -v"
        print >> subFile, "pwd"
    #print >> subFile, "cd /publicfs/cms/data/TopQuark/cms13TeV/software/root/bin/"
    #print >> subFile, "source thisroot.csh"
    #print >> subFile, "cd /publicfs/cms/user/libh/CMSSW_5_3_9/src/ttH_13Tev"
    #print >> subFile, "setenv SCRAM_ARCH slc5_amd64_gcc462"
    #print >> subFile, "source /cvmfs/cms.cern.ch/cmsset_default.csh"
    #print >> subFile, "source  /afs/ihep.ac.cn/soft/CMS/64bit/root/profile/rootenv-entry 5.34.18"
    #print >> subFile, "source  source /afs/ihep.ac.cn/soft/CMS/64bit/root/profile/rootenv-entry 6.08.02"
        #print >> subFile, "source /cvmfs/cms.cern.ch/cmsset_default.sh"
        #print >> subFile, "cd /cvmfs/cms.cern.ch/slc6_amd64_gcc493/cms/cmssw/CMSSW_7_6_3/src/"
        #print >> subFile, "cmsenv"
        #print >> subFile, "cd -"

        #print >> subFile, "eval \`scramv1 runtime -sh\`"
        print >> subFile, "cd "+frameworkDir
    #print >> subFile, "cp ${jobDir}/getAhist.C ."
#   print >> subFile, frameworkDir+"bin/Wt/Wt_generic.x -config "+frameworkDir+"SingleTop.Wt.LP.mm1+j.muonMSSmeardown.config -inlist "+frameworkDir+"config/files/"+fileListDirectory+sample+samplePost+".list -hfile "+workpath+"/"+sample+"/hists/"+sample+samplePost+"hists.root -skimfile "+workpath+"/"+sample+"/skims/"+sample+samplePost+"Skim.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger Muon -PileUpWgt -BWgt"
        skimString =""
        if makeSkims: skimString = " -skimfile "+workpath+"/"+sample+"/skims/"+sample+samplePost+"Skim.root "
    #print >> subFile, frameworkDir+executable+" -config "+frameworkDir+configFile+" -inlist "+frameworkDir+fileListDirectory+sample+samplePost+".list -hfile "+workpath+"/"+sample+"/hists/"+sample+samplePost+"hists.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger " + triggerName + invPostfix + mcPostfix + skimString + " -nJets {0} -nbJets {1}".format(nJets,nbJets)
        print >> subFile, frameworkDir+executable+" -config "+frameworkDir+configFile+" -inlist "+frameworkDir+fileListDirectory+sample+"_"+samplePost+".list -hfile "+workpath+"/"+sample+"/hists/"+sample+samplePost+"hists.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger " + triggerName + invPostfix + mcPostfix + skimString
        #print >> subFile, "root -b -q -l "+rootplizer+"'(\""+input+"\",\""+output+"\")'"
        subprocess.call("chmod 777 "+shFile, shell=True)

#for iroot in range(nroot):
for k in sample:
    print k
    sampleName = k
    
    #First, let's get rid of any 

    os.popen('mkdir -p '+workpath + sampleName)
    os.popen('mkdir -p '+workpath + sampleName + "/scripts")
    os.popen('mkdir -p '+workpath + sampleName + "/hists")
    os.popen('mkdir -p '+workpath + sampleName + "/skims")
    os.popen('mkdir -p '+workpath + sampleName + "/logs")

    if not smallerJobs:

        submitFileName = workpath + sampleName + "/scripts/" + sampleName + ".submit"
        shFileName = workpath + sampleName + "/scripts/" + sampleName +  ".sh"
        logFileName = workpath + sampleName + "/logs/" + sampleName + ".log"
        errorFileName = workpath + sampleName + "/logs/" + sampleName + ".error"
        
#       prepareSubmitJob(submitFileName, shFileName, logFileName, errorFileName)
        prepareCshJob(sampleName,shFileName,frameworkDir,workpath)
        
        submitPath = sampleName + "/scripts/" + sampleName + ".submit"
        
        #print >> allJobFile, "condor_submit "+ submitPath + " -group cms -name job@schedd01.ihep.ac.cn"
        print >> allJobFile, "hep_sub "+ shFileName + " -o "+logFileName+ " -e "+errorFileName

    else:
        inputFiles  = [f for f in os.listdir(frameworkDir+fileListDirectory) if sampleName==f[:f.rfind('_')]]
        for j in range(len(inputFiles)):
#           submitFileName = workpath + sampleName + "/scripts/" + sampleName + str(j) + ".submit"
            shFileName = workpath + sampleName + "/scripts/" + sampleName + str(j) + ".sh"
            logFileName = workpath + sampleName + "/logs/" + sampleName + str(j) + ".log"
            errorFileName = workpath + sampleName + "/logs/" + sampleName + str(j) + ".error"
            
#           prepareSubmitJob(submitFileName, shFileName, logFileName, errorFileName)
            prepareCshJob(sampleName,shFileName,frameworkDir,workpath,str(j))

            submitPath = sampleName + "/scripts/" + sampleName + str(j) + ".submit"
            
#           print >> allJobFile, "hep_sub "+ submitPath + " -name job@schedd01.ihep.ac.cn"
            print >> allJobFile, "hep_sub "+ shFileName + " -o "+logFileName+ " -e "+errorFileName
#           print >> allJobFile, "condor_submit "+ submitPath + " -group cms -name job@schedd01.ihep.ac.cn"

    print >> MergeFile, "hadd -f "+analysis+"/"+sampleName + "/hists/merged"+sampleName+".root  "+analysis+"/"+sampleName + "/hists/"+sampleName+"*hists.root"
    print >> MergeFile, "hadd -f "+analysis+"/"+sampleName + "/skims/merged"+sampleName+".root  "+analysis+"/"+sampleName + "/skims/"+sampleName+"*Skim.root"

#print >> MergeFile, "cd",outputDirectory
#print >> MergeFile, "hadd Merged_rootplas.root",MergeSourceFile


#if mcPostfix == "":
#   lepton = "Mu"
#   if "electron" in sys.argv: lepton = "Ele"
#   print >> MergeFile, "mkdir -p "+analysis+"/single{0}/hists/".format(lepton)
#   print >> MergeFile, "hadd -f "+analysis+"/single{0}/hists/mergedsingle{0}.root ".format(lepton) + analysis+"/Sing{0}*/hists/merged*".format(lepton)
#   print >> MergeFile, "mkdir -p "+analysis+"/single{0}/skims/".format(lepton)
#   print >> MergeFile, "hadd -f "+analysis+"/single{0}/skims/mergedsingle{0}.root ".format(lepton) + analysis+"/Sing{0}*/skims/merged*".format(lepton)

print >> allJobFile, "cd -"
print "Finished",analysis
