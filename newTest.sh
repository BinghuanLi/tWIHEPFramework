#!/bin/bash

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2016/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/Legacy17V1_data_test.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2016.root -BkgdTreeName DiElectronPreTagTree  -SelectTrigger TTHLep_2L -chargeMis -FakeRate 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2016/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/ttH_2016.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2016.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2017/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/ttH_2017.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2017.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2018.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/ttW_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttWDiLep_2018.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/VH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/VHDiLep_2018.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLepton.SR.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2018_SRtest.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLeptonMetShiftUp.SR.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLepMetShiftUp_2018_SRtest.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLeptonMetShiftDown.SR.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLepMetShiftDown_2018_SRtest.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2018_test.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLeptonJESUp.All.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLepJesUp_2018_test.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLeptonJESUp.All.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLepJesUpFlavorQCD_2018_test.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge -JecSourceName FlavorQCD 2>errorLog 

bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLeptonJESDown.All.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLepJesDownFlavorQCD_2018_test.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge -JecSourceName FlavorQCD 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2017/ttH.MultiLeptons.DiLeptonJESUp.SR.config -inlist config/files/ttH_test/Legacy17V2_TTJets_DiLep_11.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttJDiLepJesUpFlavorQCD_2017_test.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge -JecSourceName FlavorQCD 2>errorLog 


#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLeptonJESUp.All.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLepJesUpTotal_2018_test.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -ReCalPU -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge -JecSourceName Total 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2016/ttH.MultiLeptons.DiLepton.TrainMVA.config -inlist config/files/ttH_test/ttH_2016.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2016.root  -mc -UseTotalEvtFromFile -BkgdTreeName DiElectronPreTagTree  -SelectTrigger TTHLep_2L -chargeMis -FakeRate -isTrainMVA #2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2017/ttH.MultiLeptons.DiLepton.TrainMVA.config -inlist config/files/ttH_test/ttH_2017.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2017.root  -mc -UseTotalEvtFromFile -BkgdTreeName DiElectronPreTagTree  -SelectTrigger TTHLep_2L -chargeMis -FakeRate -isTrainMVA #2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLepton.TrainMVA.config -inlist config/files/ttH_test/ttH_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2018.root  -mc -UseTotalEvtFromFile -BkgdTreeName DiElectronPreTagTree  -SelectTrigger TTHLep_2L -chargeMis -FakeRate -isTrainMVA #2>errorLog 


#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2016/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/ttH_2016.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2016.root  -mc -UseTotalEvtFromFile -BkgdTreeName DiElectronPreTagTree  -SelectTrigger TTHLep_2L -chargeMis -FakeRate -isTrainMVA #2>errorLog 

#bin/ttH/ttH_generic.x -config /publicfs/cms/data/TopQuark/cms13TeV/Binghuan/tWIHEPFramework/config/overall/ttHRunII/2016/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/Legacy16V1_ttH_test.list -hfile hists/Legacy16V1_ttHnobb0hists.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger TTHLep_2L -MCatNLO -mc -bTagReshape -PileUpWgt  -skimfile skims/Legacy16V1_ttHnobb0Skim.root

#/publicfs/cms/data/TopQuark/cms13TeV/Binghuan/tWIHEPFramework/bin/ttH/ttH_generic.x -config /publicfs/cms/data/TopQuark/cms13TeV/Binghuan/tWIHEPFramework/config/overall/ttHRunII/2016/ttH.MultiLeptons.DiLepton.All.config -inlist /publicfs/cms/data/TopQuark/cms13TeV/Binghuan/tWIHEPFramework/config/files/ttH_Legacy/SmallJobs/mc/Legacy16V1_tWll_0.list -hfile /publicfs/cms/data/TopQuark/cms13TeV/Binghuan/ttH2019/condorStuff/skims_LegacyAll_20190917/ttH2016All2L//Legacy16V1_tWll/hists/Legacy16V1_tWll0hists.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger TTHLep_2L -MCatNLO -mc -bTagReshape -PileUpWgt  -skimfile skims/Legacy16V1_tWll0Skim.root



#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2016/ttH.MultiLeptons.DiLepton.TrainMVA.config -inlist config/files/ttH_test/ttH_2016.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_noReCalPU_2016.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -bTagReshape -Prefire -PileUpWgt -isTrainMVA 2>errorLog 

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2017/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/RD_2017.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/RD_2017.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger TTHLep_2L -chargeMis -FakeRate

#bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2018/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/RD_2018.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/RD_2018.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger TTHLep_2L -chargeMis -FakeRate

