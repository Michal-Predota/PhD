#include "TMath.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TBox.h"
#include <vector>

using namespace std;

int systematics()
{
    
	TFile *defaultFile = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");

    TFile *sigma1 = new TFile("./systematyki/pim/real/analysisPim_1sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius5.5mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *sigma3 = new TFile("./systematyki/pim/real/analysisPim_3sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius5.5mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *lowVertexZDown = new TFile("./systematyki/pim/real/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *lowVertexZUp = new TFile("./systematyki/pim/real/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-120VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *highVertexZDown = new TFile("./systematyki/pim/real/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-120_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *highVertexZUp = new TFile("./systematyki/pim/real/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-100_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *radiusDown = new TFile("./systematyki/pim/real/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius4.5mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *radiusUp = new TFile("./systematyki/pim/real/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius5.5mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *wireDistanceDown = new TFile("./systematyki/pim/real/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT3NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");
    TFile *wireDistanceUp = new TFile("./systematyki/pim/real/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT5NoSharedMetaAllLayers_beamTiltCorr_gen4FixedMagnetList_fullstat.root");

    vector<TFile*> files = {/*sigma1, sigma3,*/ lowVertexZDown, lowVertexZUp, highVertexZDown, highVertexZUp, radiusDown, radiusUp, wireDistanceDown, wireDistanceUp};
    vector<const char*> cfNames = {/*"sigma1", "sigma3",*/ "lowVertexZDown", "lowVertexZUp", "highVertexZDown", "highVertexZUp", "radiusDown", "radiusUp", "wireDistanceDown", "wireDistanceUp"};
    vector<TH1D*> variedSig;
    vector<TH1D*> variedBckg;
    vector<TH1D*> variedCF;

	TH1D *sigExp = new TH1D("signal","signal",1500,0,1500);
	TH1D *bckgExp = new TH1D("background","background",1500,0,1500);
	sigExp->Sumw2(true);
	bckgExp->Sumw2(true);

	char SigName[20];
	char BckgName[20];
    for(int i=1; i<10; i++)
	{
        for(int j=1; j<10; j++)
		{	
			if(std::string(defaultFile->GetName()).find("Pim")!=string::npos || std::string(defaultFile->GetName()).find("pim")!=string::npos)
			{
				sprintf(SigName, "PimSig_%d%d",i,j);
				sprintf(BckgName, "PimBckg_%d%d",i,j);
			}
			else if(std::string(defaultFile->GetName()).find("Pip")!=string::npos || std::string(defaultFile->GetName()).find("pip")!=string::npos)
			{
				sprintf(SigName, "PipSig_%d%d",i,j);
				sprintf(BckgName, "PipBckg_%d%d",i,j);
			}
			else if(std::string(defaultFile->GetName()).find("Proton")!=string::npos || std::string(defaultFile->GetName()).find("proton")!=string::npos)
			{
				sprintf(SigName, "ProtonSig_%d%d",i,j);
				sprintf(BckgName, "ProtonBckg_%d%d",i,j);
			}
			else
			{
				sprintf(SigName, "PimSig_%d%d",i,j);
				sprintf(BckgName, "PimBckg_%d%d",i,j);	
			}
			TH1D* tempSigExp = (TH1D*)defaultFile->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)defaultFile->Get(BckgName);
			
			if(tempSigExp)
			{
				sigExp->Add(tempSigExp);
				bckgExp->Add(tempBckgExp);
			}
		}
    }
	sigExp->Rebin(15);
	bckgExp->Rebin(15);
	
	TH1D *defaultCF = new TH1D(*sigExp);
	defaultCF->SetNameTitle("Exp", "Exp");
	defaultCF->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	defaultCF->GetYaxis()->SetTitle("CF");

	defaultCF->Divide(bckgExp);

    int cnt=0;
	double average=0;	
	for(int i=defaultCF->FindBin(250); i<=defaultCF->FindBin(350); i++)//for experimental data and SMASH
	{
		cnt++;
		average+=defaultCF->GetBinContent(i);
	}
	average/=cnt;
    defaultCF->Scale(1/average);


    //################################# cfs for systematic studies ###########################

    char cfName[50];
    for(int f=0; f<files.size(); f++)
    {
        sprintf(cfName,"%sSig", cfNames.at(f));
        variedSig.push_back(new TH1D(cfName,cfName,1500,0,1500));
        sprintf(cfName,"%sBckg", cfNames.at(f));
        variedBckg.push_back(new TH1D(cfName,cfName,1500,0,1500));
        
        variedSig.back()->Sumw2();
        variedBckg.back()->Sumw2();
        for(int i=1; i<10; i++)
	    {
            for(int j=1; j<10; j++)
		    {	
                if(std::string(files.at(f)->GetName()).find("Pim")!=string::npos || std::string(files.at(f)->GetName()).find("pim")!=string::npos)
                {
                    sprintf(SigName, "PimSig_%d%d",i,j);
                    sprintf(BckgName, "PimBckg_%d%d",i,j);
                }
                else if(std::string(files.at(f)->GetName()).find("Pip")!=string::npos || std::string(files.at(f)->GetName()).find("pip")!=string::npos)
                {
                    sprintf(SigName, "PipSig_%d%d",i,j);
                    sprintf(BckgName, "PipBckg_%d%d",i,j);
                }
                else if(std::string(files.at(f)->GetName()).find("Proton")!=string::npos || std::string(files.at(f)->GetName()).find("proton")!=string::npos)
                {
                    sprintf(SigName, "ProtonSig_%d%d",i,j);
                    sprintf(BckgName, "ProtonBckg_%d%d",i,j);
                }
                else
                {
                    sprintf(SigName, "PimSig_%d%d",i,j);
                    sprintf(BckgName, "PimBckg_%d%d",i,j);	
                }
                TH1D* tempSigExp = (TH1D*)files.at(f)->Get(SigName);
                TH1D* tempBckgExp = (TH1D*)files.at(f)->Get(BckgName);
                
                if(tempSigExp)
                {
                    variedSig.at(f)->Add(tempSigExp);
                    variedBckg.at(f)->Add(tempBckgExp);
                }
		    }
        }
        variedSig.at(f)->Rebin(15);
        variedBckg.at(f)->Rebin(15);
        variedCF.push_back(new TH1D(*variedSig.at(f)));
        variedCF.at(f)->Divide(variedBckg.at(f));
        double averageVar = 0;
        int cntVar = 0;
        
        for(int i=variedCF.at(f)->FindBin(250); i<=variedCF.at(f)->FindBin(350); i++)
        {
            averageVar += variedCF.at(f)->GetBinContent(i);
            cntVar++;
        }
        averageVar /= cntVar;
        variedCF.at(f)->Scale(1/averageVar);

    }



    //######################### calculate vector with systematic uncertainties #######################

    vector<vector<double>> differences(files.size());
    vector<double> errors;
    for(int f=0; f<files.size(); f++)
    {
        for(int i=1; i<=defaultCF->GetNbinsX(); i++)
        {
            double difference = defaultCF->GetBinContent(i) - variedCF.at(f)->GetBinContent(i);
            differences.at(f).push_back(difference);
        }
    }

    for(int i=0; i<differences.at(0).size(); i++)
    {
        double val = 0;
        for(int j=0; j<differences.size(); j++)
        {
            val += TMath::Power(differences.at(j).at(i), 2);
        }
        double error = TMath::Sqrt(val/differences.size());
        errors.push_back(error);
    }


for(int f = 0; f < differences.size(); f++)
{
    double maxDiff = 0;
    double sum2 = 0;
    int maxBin = 0;
    int zeroBins = 0;

    for(int i = 0; i < differences[f].size(); i++)
    {
        double d = abs(differences[f][i]);

        sum2 += d*d;

        if(d > maxDiff)
        {
            maxDiff = d;
            maxBin = i+1;
        }

        if(variedCF[f]->GetBinContent(i+1) == 0)
            zeroBins++;
    }

    cout << cfNames[f]
         << " | RMS = " << sqrt(sum2/differences[f].size())
         << " | max diff = " << maxDiff
         << " | max bin = " << maxBin
         << " | zero bins = " << zeroBins
         << endl;
}





    TH1D* sysHist = (TH1D*)defaultCF->Clone("sysHist");
    sysHist->Reset();

    for(int i = 1; i <= sysHist->GetNbinsX(); i++)
    {
      sysHist->SetBinContent(i, errors[i-1]);
    }


    TCanvas* c1 = new TCanvas("c1", "Correlation function", 1000, 800);

    defaultCF->SetMarkerStyle(20);
    defaultCF->SetMarkerSize(0.8);
    defaultCF->SetMarkerColor(kBlack);
    defaultCF->SetLineColor(kBlack);

    defaultCF->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
    defaultCF->GetYaxis()->SetTitle("CF");

    defaultCF->Draw("E1");

    // Systematic uncertainty boxes
    for(int i = 1; i <= defaultCF->GetNbinsX(); i++)
    {
        double x = defaultCF->GetBinCenter(i);
        double y = defaultCF->GetBinContent(i);
        double ex = defaultCF->GetBinWidth(i) / 2.0;
        double ey = sysHist->GetBinContent(i);

        TBox* box = new TBox(x-ex, y-ey, x+ex, y+ey);

        box->SetFillColor(TColor::GetColor("#E8A0A0"));
        box->SetFillStyle(1001);
        box->SetLineColor(TColor::GetColor("#D98B8B"));
        box->SetLineWidth(1);

        box->Draw("same");
    }

    // Draw statistical errors again on top
    defaultCF->Draw("E1 SAME");

   // c1->SaveAs("correlation_with_systematics.png");
    TCanvas *cVar = new TCanvas("cVar", "Systematic variations", 1000, 800);

    defaultCF->SetMarkerStyle(20);
    defaultCF->SetMarkerColor(kBlack);
    defaultCF->Draw("E1");

    int colors[] = {kRed, kRed+2, kBlue, kBlue+2, kGreen+2, kGreen+3, kMagenta, kMagenta+2};

    TLegend *legend = new TLegend(0.60, 0.60, 0.89, 0.89);
    for(int f = 0; f < variedCF.size(); f++)
    {
        variedCF[f]->SetLineColor(colors[f]);
        variedCF[f]->SetLineWidth(2);
        variedCF[f]->Draw("HIST SAME");
        legend->AddEntry(variedCF[f], cfNames[f], "lp");
    }

    defaultCF->Draw("H SAME");
    legend->Draw();  


    return 0;
}