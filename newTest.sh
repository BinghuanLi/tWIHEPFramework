#!/bin/bash
bin/ttH/ttH_generic.x -config config/overall/ttH.MultiLeptons.EleMuSR.config -inlist config/files/ttH_test/ttH.list -hfile hists/TTHnobb0.hist.root -skimfile skims/TTHnobb0.skim.root -BkgdTreeName DiElectronPreTagTree -mc -UseTotalEvtFromFile -MCatNLO -lepSFs -bTagReshape -PileUpWgt -TriggerSFs -FakeRate -chargeMis -SelectTrigger TTHLep_2L 2>errorLog 
#-lepSFs -bTagReshape -PileUpWgt -chargeMis -FakeRate -TriggerSFs 2>errorLog

