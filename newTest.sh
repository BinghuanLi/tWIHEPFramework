#!/bin/bash
bin/ttH/ttH_generic.x -config config/overall/ttH.MultiLeptons.DiLep.config -inlist config/files/ttH_2018/TTHnobb0.list -hfile hists/TTHnobb0.hist.root -skimfile skims/TTHnobb0.skim.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -FakeRate -TriggerSFs 2>errorLog

