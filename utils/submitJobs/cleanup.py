import sys, os, subprocess
from threading import Thread
import ROOT
from ROOT import TFile


dirsToCheck = [f for f in os.listdir(".") if os.path.isdir(f)]

print dirsToCheck

ignoredDirs = [
"Rootplas",
]

def runDirCheck(dirToCheck):
    if dirToCheck in ignoredDirs:
        print "!!!!!!!!!!!!!!!!!!!! Ignore {0} directory manually !!!!!!!!!!!!!!!!!!!!!!!!!!!!".format(dirToCheck)
        return
    if not os.path.isdir(dirToCheck):
        print "!!!!!!!!!!!!!!!!!!!! Skipping {0} directory which doesn't exist !!!!!!!!!!!!!!!!!!!!!!!!!!!!".format(dirToCheck)
        skippedDirs.append(dirToCheck)
        return
    print ">>>>>>>>>>>>>>>>> Executing over {0} directory <<<<<<<<<<<<<<<<".format(dirToCheck)
    #    samplesToCheck = samples if not "Data" in dirToCheck else dataSamples
    samplesToCheck = [dirToCheck + "/" + f for f in os.listdir(dirToCheck) if os.path.isdir(dirToCheck + "/" + f)]
    #samplesToCheck = [dirToCheck + "/Legacy16V1_ttHnobb" ]
    for sample in samplesToCheck:
        print "Sample: {0}".format(sample)
        prefix = sample
        if os.path.isdir(prefix+"/hists"):
            os.system("rm -rf "+prefix+"/hists")
        if os.path.isdir(prefix+"/logs"):
            os.system("rm -rf "+prefix+"/logs")
        if os.path.isdir(prefix+"/scripts"):
            os.system("rm -rf "+prefix+"/scripts")


if __name__ == "__main__":
    threads = {}
    for dirToCheck in dirsToCheck:
        print dirToCheck
        threads[dirToCheck] = Thread(target = runDirCheck, args = (dirToCheck,) )
        threads[dirToCheck].start()
    for key in threads.keys():
        threads[key].join()
        
