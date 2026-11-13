#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TCanvas.h"
#include <vector>

int pureSmashFunctions()
{
	using namespace std;
	
	
	TFile *f = new TFile("./jobs/smash/pureSmash_pim_analysis4.5GeV_buffer20_nChargedTracksMix_nTracksGT1.root","read");
	
	TH1D *sigExp = new TH1D("signal","signal",1500,0,1500);
	TH1D *bckgExp = new TH1D("background","background",1500,0,1500);
	bool isPim=false, isPip=false, isProton=false;
	char SigName[20];
	char BckgName[20];
	for(int i=1; i<10; i++)
	{
		sprintf(SigName, "sigExpKtBin%d", i);
		sprintf(BckgName, "BckgExpKtBin%d", i);
		
		for(int j=1; j<10; j++)
		{	
			if(std::string(f->GetName()).find("Pim")!=string::npos || std::string(f->GetName()).find("pim")!=string::npos)
			{
				isPim=true;
				sprintf(SigName, "PimSig_%d%d",i,j);
				sprintf(BckgName, "PimBckg_%d%d",i,j);
			}
			else if(std::string(f->GetName()).find("Pip")!=string::npos || std::string(f->GetName()).find("pip")!=string::npos)
			{
				isPip=true;
				sprintf(SigName, "PipSig_%d%d",i,j);
				sprintf(BckgName, "PipBckg_%d%d",i,j);
			}
			else if(std::string(f->GetName()).find("Proton")!=string::npos || std::string(f->GetName()).find("proton")!=string::npos)
			{
				isProton=true;
				sprintf(SigName, "ProtonSig_%d%d",i,j);
				sprintf(BckgName, "ProtonBckg_%d%d",i,j);
			}
			else
			{
				isPim=true;
				sprintf(SigName, "PimSig_%d%d",i,j);
				sprintf(BckgName, "PimBckg_%d%d",i,j);	
			}

			TH1D* tempSigExp = (TH1D*)f->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f->Get(BckgName);
			
			if(tempSigExp)
			{
				sigExp->Add(tempSigExp);
				bckgExp->Add(tempBckgExp);
			}
		}
	}
	
	sigExp->Sumw2(true);
	bckgExp->Sumw2(true);
	sigExp->Rebin(15);
	bckgExp->Rebin(15);
	TH1D *hCF = new TH1D(*sigExp);
	hCF->Divide(bckgExp);
	int cnt=0;
	double average=0;	
	for(int i=hCF->FindBin(250); i<=hCF->FindBin(350); i++)//for experimental data and SMASH
	{
		cnt++;
		average+=hCF->GetBinContent(i);
	}
	average/=cnt;
	hCF->Scale(1/average);

	TH1D *hGeV = new TH1D("hGeV",";q_{inv} (GeV/c);CF",hCF->GetNbinsX(),0,hCF->GetXaxis()->GetXmax()/1000);
	
	for(int i=1;i<=hCF->GetNbinsX();i++)
	{
		hGeV->SetBinContent(i,hCF->GetBinContent(i));
		hGeV->SetBinError(i,hCF->GetBinError(i));
	}

	TCanvas *cCF = new TCanvas("cCF","cCF",800,800);
	hGeV->GetYaxis()->SetRangeUser(0.6,1.6);
	hGeV->GetXaxis()->SetRangeUser(0,0.8);
	hGeV->SetLineWidth(2);
	hGeV->SetMarkerStyle(8);
	hGeV->SetMarkerSize(0.7);
	hGeV->SetMarkerColor(hGeV->GetLineColor());
	hGeV->Draw();

	TH1D *kTySig = (TH1D*)f->Get("kTySig");
	TH1D *kTyBckg = (TH1D*)f->Get("kTyBckg");
	TH2D * totalKtVsTotalRapidity = (TH2D*)f->Get("totalKtVsTotalRapidity");
	TH2D *pairProductionTypeVsQinvSig = (TH2D*)f->Get("pairProductionTypeVsQinvSig");
	TH2D *pairProductionTypeVsQinvBckg = (TH2D*)f->Get("pairProductionTypeVsQinvBckg");

	vector<TH1D*> sigProjections;
	vector<TH1D*> bckgProjections;
	vector<TH2D*> singleParticlePtY;
	vector<TCanvas*> pTyCanvases;
	vector<TCanvas*> pairProductionCfCanvases;

	if(isPim)
	{
		TCanvas *cMesonMeson = new TCanvas("cMesonMeson","cMesonMeson",800,800);
		TH1D *mesonMesonSig = pairProductionTypeVsQinvSig->ProjectionX("mesonMesonSig",0,1);
		TCanvas *cMesonN = new TCanvas("cMesonN","cMesonN",800,800);
		TH1D *mesonNSig = pairProductionTypeVsQinvSig->ProjectionX("mesonNSig",1,2);
		TCanvas *cMesonD = new TCanvas("cMesonD","cMesonD",800,800);
		TH1D *mesonDSig = pairProductionTypeVsQinvSig->ProjectionX("mesonDSig",2,3);
		TCanvas *cNN = new TCanvas("cNN","cNN",800,800);
		TH1D *NNSig = pairProductionTypeVsQinvSig->ProjectionX("NNSig",3,4);
		TCanvas *cND = new TCanvas("cND","cND",800,800);
		TH1D *NDSig = pairProductionTypeVsQinvSig->ProjectionX("NDSig",4,5);

		TH1D *mesonMesonBg = pairProductionTypeVsQinvBckg->ProjectionX("mesonMesonBckg",0,1);
		TH1D *mesonNBckg = pairProductionTypeVsQinvBckg->ProjectionX("mesonNBckg",1,2);
		TH1D *mesonDBckg = pairProductionTypeVsQinvBckg->ProjectionX("mesonDBckg",2,3);
		TH1D *NNBckg = pairProductionTypeVsQinvBckg->ProjectionX("NNBckg",3,4);
		TH1D *NDBckg = pairProductionTypeVsQinvBckg->ProjectionX("NDBckg",4,5);

		TCanvas *cSingleParticlePtY = new TCanvas("cSingleParticlePtY","cSingleParticlePtY",800,800);
		TH2D *pTySingleParticle = (TH2D*)f->Get("pTySingleParticle");
		TCanvas *cSingleParticlePtYPrimary = new TCanvas("cSingleParticlePtYPrimary","cSingleParticlePtYPrimary",800,800);
		TH2D *pTySingleParticlePrimary = (TH2D*)f->Get("pTySingleParticlePrimary");
		TCanvas *cSingleParticlePtYMeson = new TCanvas("cSingleParticlePtYMeson","cSingleParticlePtYMeson",800,800);
		TH2D *pTySingleParticleMeson = (TH2D*)f->Get("pTySingleParticleMeson");
		TCanvas *cSingleParticlePtYN = new TCanvas("cSingleParticlePtYN","cSingleParticlePtYN",800,800);
		TH2D *pTySingleParticleN = (TH2D*)f->Get("pTySingleParticleN");
		TCanvas *cSingleParticlePtYDelta = new TCanvas("cSingleParticlePtYDelta","cSingleParticlePtYDelta",800,800);
		TH2D *pTySingleParticleDelta = (TH2D*)f->Get("pTySingleParticleDelta");

		sigProjections.push_back(mesonMesonSig);
		sigProjections.push_back(mesonNSig);
		sigProjections.push_back(mesonDSig);
		sigProjections.push_back(NNSig);
		sigProjections.push_back(NDSig);

		bckgProjections.push_back(mesonMesonBg);
		bckgProjections.push_back(mesonNBckg);
		bckgProjections.push_back(mesonDBckg);
		bckgProjections.push_back(NNBckg);
		bckgProjections.push_back(NDBckg);

		singleParticlePtY.push_back(pTySingleParticle);
		singleParticlePtY.push_back(pTySingleParticlePrimary);
		singleParticlePtY.push_back(pTySingleParticleMeson);
		singleParticlePtY.push_back(pTySingleParticleN);
		singleParticlePtY.push_back(pTySingleParticleDelta);

		pTyCanvases.push_back(cSingleParticlePtY);
		pTyCanvases.push_back(cSingleParticlePtYPrimary);
		pTyCanvases.push_back(cSingleParticlePtYMeson);
		pTyCanvases.push_back(cSingleParticlePtYN);
		pTyCanvases.push_back(cSingleParticlePtYDelta);

		pairProductionCfCanvases.push_back(cMesonMeson);
		pairProductionCfCanvases.push_back(cMesonN);
		pairProductionCfCanvases.push_back(cMesonD);
		pairProductionCfCanvases.push_back(cNN);
		pairProductionCfCanvases.push_back(cND);
	}

	else if(isPip)
	{
		TH1D *mesonDSig = pairProductionTypeVsQinvSig->ProjectionX("mesonDSig",0,1);
		TH1D *NDSig = pairProductionTypeVsQinvSig->ProjectionX("NDSig",1,2);
		TH1D *DDSig = pairProductionTypeVsQinvSig->ProjectionX("DDSig",2,3);

		TH1D *mesonDBckg = pairProductionTypeVsQinvBckg->ProjectionX("mesonDBckg",0,1);
		TH1D *NDBckg = pairProductionTypeVsQinvBckg->ProjectionX("NDBckg",1,2);
		TH1D *DDBckg = pairProductionTypeVsQinvBckg->ProjectionX("DDBckg",2,3);

		TH2D* pTySingleParticle = (TH2D*)f->Get("pTySingleParticle");
		TH2D *pTySingleParticlePrimary = (TH2D*)f->Get("pTySingleParticlePrimary");
		TH2D* pTySingleParticleMeson = (TH2D*)f->Get("pTySingleParticleMeson");
		TH2D *pTySingleParticleN = (TH2D*)f->Get("pTySingleParticleN");
		TH2D *pTySingleParticleDelta = (TH2D*)f->Get("pTySingleParticleDelta");


		sigProjections.push_back(mesonDSig);
		sigProjections.push_back(NDSig);
		sigProjections.push_back(DDSig);

		bckgProjections.push_back(mesonDBckg);
		bckgProjections.push_back(NDBckg);
		bckgProjections.push_back(DDBckg);

		singleParticlePtY.push_back(pTySingleParticle);
		singleParticlePtY.push_back(pTySingleParticlePrimary);
		singleParticlePtY.push_back(pTySingleParticleMeson);
		singleParticlePtY.push_back(pTySingleParticleN);
		singleParticlePtY.push_back(pTySingleParticleDelta);
	}

	else if(isProton)
	{
		TH1D *nPrimarySig = pairProductionTypeVsQinvSig->ProjectionX("nPrimarySig",0,1);
		TH1D *dPrimarySig = pairProductionTypeVsQinvSig->ProjectionX("dPrimarySig",1,2);
		TH1D *NDSig = pairProductionTypeVsQinvSig->ProjectionX("NDS",2,3);
		TH1D *DDsig = pairProductionTypeVsQinvSig->ProjectionX("DDsig",2,3);

		TH1D *nPrimaryBckg = pairProductionTypeVsQinvBckg->ProjectionX("nPrimaryBckg",0,1);
		TH1D *dPrimaryBckg = pairProductionTypeVsQinvBckg->ProjectionX("dPrimaryBckg",1,2);
		TH1D *NDBckg = pairProductionTypeVsQinvBckg->ProjectionX("NDBckg",2,3);
		TH1D *DDBckg = pairProductionTypeVsQinvBckg->ProjectionX("DDBckg",2,3);

		TH2D* pTySingleParticle = (TH2D*)f->Get("pTySingleParticle");
		TH2D *pTySingleParticlePrimary = (TH2D*)f->Get("pTySingleParticlePrimary");
		TH2D *pTySingleParticleN = (TH2D*)f->Get("pTySingleParticleN");
		TH2D *pTySingleParticleDelta = (TH2D*)f->Get("pTySingleParticleDelta");


		sigProjections.push_back(nPrimarySig);
		sigProjections.push_back(dPrimarySig);
		sigProjections.push_back(NDSig);
		sigProjections.push_back(DDsig);

		bckgProjections.push_back(nPrimaryBckg);
		bckgProjections.push_back(dPrimaryBckg);
		bckgProjections.push_back(NDBckg);
		bckgProjections.push_back(DDBckg);

		singleParticlePtY.push_back(pTySingleParticle);
		singleParticlePtY.push_back(pTySingleParticlePrimary);
		singleParticlePtY.push_back(pTySingleParticleN);
		singleParticlePtY.push_back(pTySingleParticleDelta);
	}


	return 0;
}