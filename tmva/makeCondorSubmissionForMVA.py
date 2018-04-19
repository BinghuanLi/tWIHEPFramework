from ROOT import *

import subprocess, sys, os, time

#gROOT.ProcessLine(".L /publicfs/cms/user/duncanleg/tW13TeV/tmva/mvaTool.C+")

reducedttbarSet = False

onlySignal = False

useMVA = True

runMacro = "runMVAReading"
if not useMVA: runMacro = "runReadingNoMVA"

inputtWIHEPFrameworkDirectory = "tW"

nProcesserAtATime = 5

outDir = sys.argv[1]

thisDir = os.getcwd()

print thisDir

elePostfix = ""

samplesDataMu = ["SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG","SingMuH"]
samplesDataEle = ["SingEleB","SingEleC","SingEleD","SingEleE","SingEleF","SingEleG","SingEleH"]

samplesData = samplesDataMu
if reducedttbarSet: samplesData = []

if "ele" in sys.argv:
    elePostfix = "Ele"
    samplesData = samplesDataEle

#t = mvaTool()

samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMadgraph","wPlusJetsMCatNLO","ttbar","ttbarBU","wPlus0Jets","wPlus1Jets","wPlus2Jets"]
if reducedttbarSet: samples = ["ttbar"]

regions = ["3j1t","3j2t","2j1t","4j1t","4j2t"]
if useMVA: regions = [""]
if reducedttbarSet: regions = [""]
if onlySignal: regions = [""]

#samples = ["tW_top_nfh","tW_antitop_nfh"]

processes = []
systs = ["JESUp","JESDown","JERUp","JERDown"]
if reducedttbarSet or onlySignal: systs = []

systDir = ""
systDir = "tWSysts"+elePostfix
#if len(sys.argv) > 2:
#    systDir = sys.argv[2]
if reducedttbarSet or onlySignal or not useMVA: systDir = ""

if (not os.path.isdir(outDir+"/submit/")):
    subprocess.call("mkdir -p "+outDir + "/submit/",shell=True)
if (not os.path.isdir(outDir+"/logs/")):
    subprocess.call("mkdir -p "+outDir + "/logs/",shell=True)

for i in range(len(regions)):

    region = regions[i]
    
    if (not os.path.isdir(outDir+region)):
        subprocess.call("mkdir -p "+outDir+region+"/",shell=True)
    if (not os.path.isdir(outDir+"Systs"+region+"/")):
        subprocess.call("mkdir -p "+outDir+"Systs"+region+"/",shell=True)
    if (not os.path.isdir(outDir+"QCD"+region+"/")):
        subprocess.call("mkdir -p "+outDir+"QCD"+region+"/",shell=True)
    for syst in systs:
        if (not os.path.isdir(outDir+syst+region+"/")):
            subprocess.call("mkdir -p "+outDir+syst+region+"/",shell=True)

def prepareCshJob(submitFileName,directory,commandToRun):
    subFile      = file(submitFileName,"w")
    print >> subFile, "#!/bin/bash"
    print >> subFile, "/bin/hostname"
    print >> subFile, "gcc -v"
    print >> subFile, "pwd"
    print >> subFile, "source /afs/ihep.ac.cn/soft/CMS/64bit/root/profile/rootenv-entry 6.08.02"
    print >> subFile, "cd {0}".format(directory)
    print >> subFile, commandToRun
    subprocess.call("chmod 777 "+submitFileName,shell=True)

def makeSubmissionFiles(systDir):
    
    toRun = []

    for sample in samples:
            #    continue
        runSample = False
        for region in regions:
            if not os.path.exists(outDir+region+"/output_"+sample+".root") or os.stat(outDir+region+"/output_"+sample+".root").st_size < 350: runSample = True
        if runSample: toRun.append("root -b -q \"../../framework/tmva/"+runMacro+".C(\\\""+sample+"\\\",\\\"{0}".format(inputtWIHEPFrameworkDirectory)+elePostfix+"/\\\",\\\""+outDir+"\\\");\"")
        for syst in systs:
            runSysts = False
            for region in regions:
                if not os.path.exists(outDir+syst+region+"/output_"+sample+".root") or os.stat(outDir+syst+region+"/output_"+sample+".root").st_size < 350: runSysts = True
            if runSysts: toRun.append("root -b -q \"../../framework/tmva/"+runMacro+".C(\\\""+sample+"\\\",\\\"{0}".format(inputtWIHEPFrameworkDirectory)+syst+elePostfix+"/\\\",\\\""+outDir+syst+"\\\");\"")

    for sample in samplesData:
        #    continue
        runData = False
        for region in regions:
            if not os.path.exists(outDir+region+"/output_"+sample+".root") or os.stat(outDir+region+"/output_"+sample+".root").st_size < 350: runData = True
        if runData: toRun.append("root -b -q \"../../framework/tmva/"+runMacro+".C(\\\""+sample+"\\\",\\\"{0}Data".format(inputtWIHEPFrameworkDirectory)+elePostfix+"/\\\",\\\""+outDir+"\\\");\"")
        runQCD = False
        for region in regions:
            if not os.path.exists(outDir+"QCD"+region+"/output_"+sample+".root") or os.stat(outDir+"QCD"+region+"/output_"+sample+".root") < 350: runQCD = True
        if runQCD: toRun.append("root -b -q \"../../framework/tmva/"+runMacro+".C(\\\""+sample+"\\\",\\\"{0}InvData".format(inputtWIHEPFrameworkDirectory)+elePostfix+"/\\\",\\\""+outDir+"QCD\\\");\"")

    #And do the theory uncertainties if they exist
    if systDir:
        for sample in os.listdir(systDir):
            systDir = "{2}{0}Systs{1}/".format("",elePostfix,inputtWIHEPFrameworkDirectory)
            runSyst = False
            for region in regions:
                if not os.path.exists(outDir+"Systs"+region+"/output_"+sample+".root") or os.stat(outDir+"Systs"+region+"/output_"+sample+".root").st_size < 350: runSyst = True
            if runSyst: toRun.append("root -b -q \"../../framework/tmva/"+runMacro+".C(\\\""+sample+"\\\",\\\""+systDir+"/\\\",\\\""+outDir+"Systs\\\");\"")

    nFinished = 0
    nRunning = 0

    #Here we will make condor submission jobs instead of just running it locally because that just won't work anymore.
    submitAll = file(outDir+"/submit/submitAll.sh","w")
    print >> submitAll, "#!/bin/bash"
    dir_path = os.path.dirname(os.path.realpath(__file__))

    for runNum in range(len(toRun)):
        prepareCshJob(outDir+"/submit/submissionJob{0}.sh".format(runNum),thisDir,toRun[runNum])
        print >> submitAll, "hep_sub {0}/submit/submissionJob{1}.sh -o {0}/logs/job{1}.out -e {0}/logs/job{1}.error".format(outDir,runNum)
                      
    print "Made {0} submission files".format(len(toRun))

if __name__ == "__main__":
    makeSubmissionFiles(systDir)
    print "Made submission files"
