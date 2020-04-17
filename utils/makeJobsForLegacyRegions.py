#Make the job folders for all of the regions we want to study for the tW lepton+jets

import subprocess

Jecsources={
"2016":["FlavorQCD","RelativeBal","HF","BBEC1","EC2","Absolute","BBEC1_2016","EC2_2016","Absolute_2016","HF_2016","RelativeSample_2016"],
"2017":["FlavorQCD","RelativeBal","HF","BBEC1","EC2","Absolute","BBEC1_2017","EC2_2017","Absolute_2017","HF_2017","RelativeSample_2017"],
"2018":["FlavorQCD","RelativeBal","HF","BBEC1","EC2","Absolute","BBEC1_2018","EC2_2018","Absolute_2018","HF_2018","RelativeSample_2018"],
#"2016":["RelativeBal","HF","BBEC1","EC2","Absolute","BBEC1_2016","EC2_2016","Absolute_2016","HF_2016"],
#"2017":["RelativeBal","HF","BBEC1","EC2","Absolute","BBEC1_2017","EC2_2017","Absolute_2017","HF_2017"],
#"2018":["RelativeBal","HF","BBEC1","EC2","Absolute","BBEC1_2018","EC2_2018","Absolute_2018","HF_2018"],
#"2016":["FlavorQCD","RelativeSample_2016"],
#"2017":["FlavorQCD","RelativeSample_2017"],
#"2018":["FlavorQCD","RelativeSample_2018"],
}

Jersources = ["HEM","eta1p9","eta2p5","eta3lowpt","eta3highpt","eta5lowpt","eta5highpt"]

baseDir = "/publicfs/cms/data/TopQuark/cms13TeV/Binghuan/tWIHEPFramework/"

for i in ["2016","2017","2018"]:
    jecs = Jecsources[i]
    jecs.append("")
    for k in ["isSigExt","isData"]:
    #for k in ["isSigExt"]:
    #for k in ["isDNN","isHjtagger"]:
         #for j in ["JESUp","JESDown"]:
         #for j in ["nominal","JESUp","JESDown","JERUp","JERDown","MetShiftUp","MetShiftDown"]:
         for j in ["nominal"]:
            if k !="isSigExt" and j!="nominal":
                continue
            #for l in ["2","3","4"]:
            for l in ["2"]:
                if l!="2" and j!="nominal":
                    continue
                for jer in Jersources:
                    if j not in ["JERUp","JERDown"]:
                        continue
                    optstring = "-s %s -j %s -y %s -n %s -u %s"%(k,j,i,l,jer)
                    print "python "+baseDir+"utils/makeHEPSubmitLegacyV2.py "+optstring
                    subprocess.call( "python "+baseDir+"utils/makeHEPSubmitLegacyV2.py "+optstring, shell=True)
                    
                for u in jecs:
                    # skip overall jer if jer is splitted
                    if len(Jersources) > 0 and j in ["JERUp","JERDown"] and len(u)==0:
                        continue
                    if len(u)>0 and j not in ["JESUp","JESDown"]:
                        continue
                    if len(u)==0 and j in ["JESUp","JESDown"]:
                        continue
                    if len(u)>0:
                        optstring = "-s %s -j %s -y %s -n %s -u %s"%(k,j,i,l,u)
                        print "python "+baseDir+"utils/makeHEPSubmitLegacyV2.py "+optstring
                        subprocess.call( "python "+baseDir+"utils/makeHEPSubmitLegacyV2.py "+optstring, shell=True)
                    else:
                        optstring = "-s %s -j %s -y %s -n %s"%(k,j,i,l)
                        print "python "+baseDir+"utils/makeHEPSubmitLegacyV2.py "+optstring
                        subprocess.call( "python "+baseDir+"utils/makeHEPSubmitLegacyV2.py "+optstring, shell=True)

