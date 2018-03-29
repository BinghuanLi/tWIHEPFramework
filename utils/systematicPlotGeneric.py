from ROOT import *
from random import *

#A bunch of global variables that are used in the drawing

gROOT.SetBatch()

from setTDRStyle import setTDRStyle

setTDRStyle()

latex = TLatex()
latex.SetNDC()
latex.SetTextAlign(31)

cmsTextFont = 61
extraTextFont = 52

latex2 = TLatex();
latex2.SetNDC();
latex2.SetTextSize(0.04);
latex2.SetTextAlign(31);

cmsText = "CMS"
extraText = "Preliminary"

def makeSystHist(nominalHist,upHist,downHist,canvasName,outDir):
#    canvasName = upHist.GetName().split("Up")[0]
    canvy = TCanvas(canvasName,canvasName,1000,800)
    canvy.cd()
    canvy.SetBottomMargin(0.3)
    nominalHist.SetLineColor(kBlack)
    histMax = 0.
    if upHist.GetMaximum() > histMax: histMax = upHist.GetMaximum() 
    if downHist.GetMaximum() > histMax: histMax = downHist.GetMaximum()
    nominalHist.SetMaximum(histMax*1.2)
    nominalHist.Draw("hist")
    upHist.SetLineColor(kRed)
    upHist.Draw("hist same")
    downHist.SetLineColor(kBlue)
    downHist.Draw("hist same")

    latex.SetTextSize(0.04)
    latex.SetTextFont(cmsTextFont)
    latex.DrawLatex(0.23, 0.95, cmsText )
    
    latex.SetTextFont(extraTextFont)
    latex.SetTextSize(0.04*0.76)
    latex.DrawLatex(0.35, 0.95 , extraText )
    
    latex2.DrawLatex(0.95, 0.95, canvasName);
    
    ratioCanvy = TPad("mva_ratio","mva_ratio",0.0,0.0,1.0,1.0)
    ratioCanvy.SetTopMargin(0.7)
    ratioCanvy.SetFillColor(0)
    ratioCanvy.SetFillStyle(0)
    ratioCanvy.SetGridy(1)
    ratioCanvy.Draw()
    ratioCanvy.cd(0)
    SetOwnership(ratioCanvy,False)
    

    
#    text2 = TLatex(0.45,0.98, "#mu channel " + canvasName)
#    text2.SetNDC()
#    text2.SetTextAlign(13)
#    text2.SetX(0.18)
#    text2.SetY(0.92)
#    text2.SetTextFont(42)
#    text2.SetTextSize(0.0610687)
#

    upHistRatio = upHist.Clone()
    upHistRatio.Divide(nominalHist)
    upHistRatio.SetMaximum(1.3)
    upHistRatio.SetMinimum(0.7)
    upHistRatio.Draw("hist same")
    downHistRatio = downHist.Clone()
    downHistRatio.Divide(nominalHist)
    downHistRatio.GetXaxis().SetTitle("BDT Discriminant")
    downHistRatio.Draw("hist same")

    canvy.SaveAs(outDir+canvasName+".png")

def makeStackPlot(nominal,systHists,region,outDir,savePost = ""):
    stack = THStack("mva_{0}".format(region),"mva_{0}".format(region))
    canvy = TCanvas("MVA_{0}".format(region),"MVA_{0}".format(region),1000,800)
    leggy = TLegend(0.8,0.6,0.95,0.9)
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)
    
    canvy.cd()
    if includeDataInStack: canvy.SetBottomMargin(0.3)
    dataHist = 0
    sumHist = nominal[nominal.keys()[0]].Clone()
    sumHist.Reset()
    for i in nominal.keys():
        if i == "data":
            dataHist = nominal["data"]
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            continue
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
#        stack.Add(nominal[i])
        sumHist.Add(nominal[i])
        #Do systematic estimation here when I get aorund to it)

    if "data" in nominal.keys():
        leggy.AddEntry(nominal['data'],"Data","p")
    for entry in legendOrder:
        leggy.AddEntry(nominal[entry],entry,"f")

    legendOrder.reverse()
    for entry in legendOrder:
        stack.Add(nominal[entry])

    maxi = stack.GetMaximum()
    if dataHist.GetMaximum() > stack.GetMaximum(): maxi = dataHist.GetMaximum()
    stack.SetMaximum(maxi)
    stack.Draw("hist")
    
    if includeDataInStack: dataHist.Draw("e1x0 same")
    leggy.Draw()

    if includeDataInStack:
        ratioCanvy = TPad("mva_ratio","mva_ratio",0.0,0.0,1.0,1.0)
        ratioCanvy.SetTopMargin(0.7)
        ratioCanvy.SetFillColor(0)
        ratioCanvy.SetFillStyle(0)
        ratioCanvy.SetGridy(1)
        ratioCanvy.Draw()
        ratioCanvy.cd(0)
        SetOwnership(ratioCanvy,False)

        sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
        sumHistoData.Sumw2()
        sumHistoData.Divide(sumHist)

        sumHistoData.GetYaxis().SetTitle("Data/MC")
        sumHistoData.GetYaxis().SetTitleOffset(1.3)
        ratioCanvy.cd()
        SetOwnership(sumHistoData,False)
        sumHistoData.SetMinimum(0.8)
        sumHistoData.SetMaximum(1.2)
        sumHistoData.GetXaxis().SetTitleOffset(1.2)
        sumHistoData.GetXaxis().SetLabelSize(0.04)
        sumHistoData.GetYaxis().SetNdivisions(6)
        sumHistoData.GetYaxis().SetTitleSize(0.03)
        sumHistoData.Draw("E1X0")

    canvy.SaveAs(outDir+"plots/mva{0}{1}.png".format(region,savePost))
    canvy.SaveAs(outDir+"plots/mva{0}{1}.root".format(region,savePost))

if __name__ == "__main__":
    #Do something to get your nominal and systUp/Down plots here
    nominalHist = TH1F("nominalHist","nominalHist",10,0,10)
    for i in range(100):
        nominalHist.Fill(randint(1,10))
    systUp = nominalHist.Clone("up")
    systDown = nominalHist.Clone("down")

    for i in range(1,11):
        systUp.SetBinContent(i,systUp.GetBinContent(i)+uniform(0,3))
        systUp.SetBinContent(i,systUp.GetBinContent(i)-uniform(0,3))

    #Whatever you want your canvas to be called
    name = "yourNameHere"
    #out directory
    outDir = "plots/"
    #And now make the systematic comparison plot
    
    makeSystHist(nominalHist,systUp,systDown,name,outDir)
