#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include <vector>

int pureSmashFunctions()
{
	gStyle->SetOptStat(0);
	using namespace std;
	
	
//	TFile *f = new TFile("./jobs/smash/pureSmash_pim_analysis4.5GeV_buffer20_nChargedTracksMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pim_analysis4.5GeV_buffer20_nChargedTracksMix_nTracksGT5.root","read");

//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_nTracksMix_nTracksGT1.root","read");
	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_nTracksMix_nTracksGT5.root","read");

//	TFile *f = new TFile("./jobs/smash/pureSmash_proton_analysis4.5GeV_buffer20_nTracksMix_nTracksGT2.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_proton_analysis4.5GeV_buffer20_nTracksMix_nTracksGT5.root","read");
	
	TH1D *sigExp = new TH1D("signal","signal",1500,0,1500);
	TH1D *bckgExp = new TH1D("background","background",1500,0,1500);
	bool isPim=false, isPip=false, isProton=false;
	char SigName[20];
	char BckgName[20];
	char particleName[20];
	char numberOfTracks[20];
	char fileName[100];
	if(std::string(f->GetName()).find("Pim")!=string::npos || std::string(f->GetName()).find("pim")!=string::npos)
	{
		sprintf(particleName, "pim");
	}
	else if(std::string(f->GetName()).find("Pip")!=string::npos || std::string(f->GetName()).find("pip")!=string::npos)
	{
		sprintf(particleName, "pip");
	}
	else if(std::string(f->GetName()).find("Proton")!=string::npos || std::string(f->GetName()).find("proton")!=string::npos)
	{
		sprintf(particleName, "proton");
	}

	if(std::string(f->GetName()).find("nTracksGT1")!=string::npos)
	{
		sprintf(numberOfTracks, "nTracksGT1");
	}
	else if(std::string(f->GetName()).find("nTracksGT2")!=string::npos)
	{
		sprintf(numberOfTracks, "nTracksGT2");
	}
	else if(std::string(f->GetName()).find("nTracksGT3")!=string::npos)
	{
		sprintf(numberOfTracks, "nTracksGT3");
	}
	else if(std::string(f->GetName()).find("nTracksGT4")!=string::npos)
	{
		sprintf(numberOfTracks, "nTracksGT4");
	}
	else if(std::string(f->GetName()).find("nTracksGT5")!=string::npos)
	{
		sprintf(numberOfTracks, "nTracksGT5");
	}

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

	sprintf(fileName, "./randomShit/%sCF%s.pdf", particleName, numberOfTracks);
	TCanvas *cCF = new TCanvas("cCF","cCF",800,800);
	cCF->cd();
	hGeV->GetYaxis()->SetRangeUser(0.,2.);
	hGeV->GetXaxis()->SetRangeUser(0,0.8);
	hGeV->SetLineWidth(2);
	hGeV->SetMarkerStyle(8);
	hGeV->SetMarkerSize(0.7);
	hGeV->SetMarkerColor(hGeV->GetLineColor());
	hGeV->Draw();
	cCF->SaveAs(fileName);

	TH2D *kTySig = (TH2D*)f->Get("kTySig");
	TH2D *kTyBckg = (TH2D*)f->Get("kTyBckg");
	TH2D * totalKtVsTotalRapidity = (TH2D*)f->Get("totalKtVsTotalRapidity");
	TH2D *pairProductionTypeVsQinvSig = (TH2D*)f->Get("pairProductionTypeVsQinvSig");
	TH2D *pairProductionTypeVsQinvBckg = (TH2D*)f->Get("pairProductionTypeVsQinvBckg");

	vector<TH1D*> sigProjections;
	vector<TH1D*> bckgProjections;
	vector<TH2D*> singleParticlePtY;
	vector<TCanvas*> pTyCanvases;
	vector<TCanvas*> pairProductionCfCanvases;
	vector<TPaveText*> pairProductionCfPaves;

	if(isPim)
	{
		TCanvas *cMesonMeson = new TCanvas("cMesonMeson","cMesonMeson",800,800);
		TH1D *mesonMesonSig = pairProductionTypeVsQinvSig->ProjectionX("mesonMesonSig",0,1);
		int mesonMesonSigEntries = mesonMesonSig->GetEntries();
		TCanvas *cMesonN = new TCanvas("cMesonN","cMesonN",800,800);
		TH1D *mesonNSig = pairProductionTypeVsQinvSig->ProjectionX("mesonNSig",1,2);
		int mesonNSigEntries = mesonNSig->GetEntries();
		TCanvas *cMesonD = new TCanvas("cMesonD","cMesonD",800,800);
		TH1D *mesonDSig = pairProductionTypeVsQinvSig->ProjectionX("mesonDSig",2,3);
		int mesonDSigEntries = mesonDSig->GetEntries();
		TCanvas *cNN = new TCanvas("cNN","cNN",800,800);
		TH1D *NNSig = pairProductionTypeVsQinvSig->ProjectionX("NNSig",3,4);
		int NNSigEntries = NNSig->GetEntries();
		TCanvas *cND = new TCanvas("cND","cND",800,800);
		TH1D *NDSig = pairProductionTypeVsQinvSig->ProjectionX("NDSig",4,5);
		int NDSigEntries = NDSig->GetEntries();
		
		int sum = mesonMesonSigEntries+mesonNSigEntries+mesonDSigEntries+NNSigEntries+NDSigEntries;
		double mesonMesonPercentage = (double)mesonMesonSigEntries/sum;
		double mesonNPercentage = (double)mesonNSigEntries/sum;
		double mesonDPercentage = (double)mesonDSigEntries/sum;
		double NNPercentage = (double)NNSigEntries/sum;
		double NDPercentage = (double)NDSigEntries/sum;

		TH1D *mesonMesonBckg = pairProductionTypeVsQinvBckg->ProjectionX("mesonMesonBckg",0,1);
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

		char mesonMesonPaveText[20];
		sprintf(mesonMesonPaveText, "Meson-Meson: %.2f%%", mesonMesonPercentage*100);
		TPaveText *mesonMesonPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		mesonMesonPave->AddText(mesonMesonPaveText);

		char mesonNPaveText[20];
		sprintf(mesonNPaveText, "Meson-N: %.2f%%", mesonNPercentage*100);
		TPaveText *mesonNPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		mesonNPave->AddText(mesonNPaveText);

		char mesonDPaveText[20];
		sprintf(mesonDPaveText, "Meson-D: %.2f%%", mesonDPercentage*100);
		TPaveText *mesonDPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		mesonDPave->AddText(mesonDPaveText);

		char NNPaveText[20];
		sprintf(NNPaveText, "N-N: %.2f%%", NNPercentage*100);
		TPaveText *NNPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		NNPave->AddText(NNPaveText);

		char NDPaveText[20];
		sprintf(NDPaveText, "N-D: %.2f%%", NDPercentage*100);
		TPaveText *NDPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		NDPave->AddText(NDPaveText);


		sigProjections.push_back(mesonMesonSig);
		sigProjections.push_back(mesonNSig);
		sigProjections.push_back(mesonDSig);
		sigProjections.push_back(NNSig);
		sigProjections.push_back(NDSig);

		bckgProjections.push_back(mesonMesonBckg);
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

		pairProductionCfPaves.push_back(mesonMesonPave);
		pairProductionCfPaves.push_back(mesonNPave);
		pairProductionCfPaves.push_back(mesonDPave);
		pairProductionCfPaves.push_back(NNPave);
		pairProductionCfPaves.push_back(NDPave);
	}

	else if(isPip)
	{
		TCanvas *cMesonD = new TCanvas("cMesonD","cMesonD",800,800);
		TH1D *mesonDSig = pairProductionTypeVsQinvSig->ProjectionX("mesonDSig",0,1);
		int mesonDSigEntries = mesonDSig->GetEntries();
		TCanvas *cND = new TCanvas("cND","cND",800,800);
		TH1D *NDSig = pairProductionTypeVsQinvSig->ProjectionX("NDSig",1,2);
		int NDSigEntries = NDSig->GetEntries();
		TCanvas *cDD = new TCanvas("cDD","cDD",800,800);
		TH1D *DDSig = pairProductionTypeVsQinvSig->ProjectionX("DDSig",2,3);
		int DDSigEntries = DDSig->GetEntries();
		
		int sum = mesonDSigEntries+NDSigEntries+DDSigEntries;
		double mesonDPercentage = (double)mesonDSigEntries/sum;
		double NDPercentage = (double)NDSigEntries/sum;
		double DDPercentage = (double)DDSigEntries/sum;

		TH1D *mesonDBckg = pairProductionTypeVsQinvBckg->ProjectionX("mesonDBckg",0,1);
		TH1D *NDBckg = pairProductionTypeVsQinvBckg->ProjectionX("NDBckg",1,2);
		TH1D *DDBckg = pairProductionTypeVsQinvBckg->ProjectionX("DDBckg",2,3);

		TCanvas *cSingleParticlePtY = new TCanvas("cSingleParticlePtY","cSingleParticlePtY",800,800);
		TH2D* pTySingleParticle = (TH2D*)f->Get("pTySingleParticle");
		TCanvas *cSingleParticlePtYPrimary = new TCanvas("cSingleParticlePtYPrimary","cSingleParticlePtYPrimary",800,800);
		TH2D *pTySingleParticlePrimary = (TH2D*)f->Get("pTySingleParticlePrimary");
		TCanvas *cSingleParticlePtYMeson = new TCanvas("cSingleParticlePtYMeson","cSingleParticlePtYMeson",800,800);
		TH2D* pTySingleParticleMeson = (TH2D*)f->Get("pTySingleParticleMeson");
		TCanvas *cSingleParticlePtYN = new TCanvas("cSingleParticlePtYN","cSingleParticlePtYN",800,800);
		TH2D *pTySingleParticleN = (TH2D*)f->Get("pTySingleParticleN");
		TCanvas *cSingleParticlePtYDelta = new TCanvas("cSingleParticlePtYDelta","cSingleParticlePtYDelta",800,800);
		TH2D *pTySingleParticleDelta = (TH2D*)f->Get("pTySingleParticleDelta");

		
		char mesonDPaveText[20];
		sprintf(mesonDPaveText, "Meson-D: %.2f%%", mesonDPercentage*100);
		TPaveText *mesonDPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		mesonDPave->AddText(mesonDPaveText);

		char NDPaveText[20];
		sprintf(NDPaveText, "N-D: %.2f%%", NDPercentage*100);
		TPaveText *NDPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		NDPave->AddText(NDPaveText);

		char DDPaveText[20];
		sprintf(DDPaveText, "D-D: %.2f%%", DDPercentage*100);
		TPaveText *DDPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		DDPave->AddText(DDPaveText);

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

		pTyCanvases.push_back(cSingleParticlePtY);
		pTyCanvases.push_back(cSingleParticlePtYPrimary);
		pTyCanvases.push_back(cSingleParticlePtYMeson);
		pTyCanvases.push_back(cSingleParticlePtYN);
		pTyCanvases.push_back(cSingleParticlePtYDelta);

		pairProductionCfCanvases.push_back(cMesonD);
		pairProductionCfCanvases.push_back(cND);
		pairProductionCfCanvases.push_back(cDD);

		pairProductionCfPaves.push_back(mesonDPave);
		pairProductionCfPaves.push_back(NDPave);
		pairProductionCfPaves.push_back(DDPave);
	}

	else if(isProton)
	{
		TCanvas *cNPrimary = new TCanvas("cNPrimary","cNPrimary",800,800);
		TH1D *nPrimarySig = pairProductionTypeVsQinvSig->ProjectionX("nPrimarySig",0,1);
		int nPrimarySigEntries = nPrimarySig->GetEntries();
		TCanvas *cDPrimary = new TCanvas("cDPrimary","cDPrimary",800,800);
		TH1D *dPrimarySig = pairProductionTypeVsQinvSig->ProjectionX("dPrimarySig",1,2);
		int dPrimarySigEntries = dPrimarySig->GetEntries();
		TCanvas *cND = new TCanvas("cND","cND",800,800);
		TH1D *NDSig = pairProductionTypeVsQinvSig->ProjectionX("NDS",2,3);
		int NDSigEntries = NDSig->GetEntries();
		TCanvas *cDD = new TCanvas("cDD","cDD",800,800);
		TH1D *DDSig = pairProductionTypeVsQinvSig->ProjectionX("DDsig",3,4);
		int DDSigEntries = DDSig->GetEntries();

		int sum = nPrimarySigEntries+dPrimarySigEntries+NDSigEntries+DDSigEntries;
		double NPrimaryPercentage = (double)nPrimarySigEntries/sum;
		double DPrimaryPercentage = (double)dPrimarySigEntries/sum;
		double NDPercentage = (double)NDSigEntries/sum;
		double DDPercentage = (double)DDSigEntries/sum;

		TH1D *nPrimaryBckg = pairProductionTypeVsQinvBckg->ProjectionX("nPrimaryBckg",0,1);
		TH1D *dPrimaryBckg = pairProductionTypeVsQinvBckg->ProjectionX("dPrimaryBckg",1,2);
		TH1D *NDBckg = pairProductionTypeVsQinvBckg->ProjectionX("NDBckg",2,3);
		TH1D *DDBckg = pairProductionTypeVsQinvBckg->ProjectionX("DDBckg",3,4);

		TCanvas *cSingleParticlePtY = new TCanvas("cSingleParticlePtY","cSingleParticlePtY",800,800);
		TH2D* pTySingleParticle = (TH2D*)f->Get("pTySingleParticle");
		TCanvas *cSingleParticlePtYPrimary = new TCanvas("cSingleParticlePtYPrimary","cSingleParticlePtYPrimary",800,800);
		TH2D *pTySingleParticlePrimary = (TH2D*)f->Get("pTySingleParticlePrimary");
		TCanvas *cSingleParticlePtYN = new TCanvas("cSingleParticlePtYN","cSingleParticlePtYN",800,800);
		TH2D *pTySingleParticleN = (TH2D*)f->Get("pTySingleParticleN");
		TCanvas *cSingleParticlePtYDelta = new TCanvas("cSingleParticlePtYDelta","cSingleParticlePtYDelta",800,800);
		TH2D *pTySingleParticleDelta = (TH2D*)f->Get("pTySingleParticleDelta");

		char NPrimaryPaveText[20];
		sprintf(NPrimaryPaveText, "N-Primary: %.2f%%", NPrimaryPercentage*100);
		TPaveText *NPrimaryPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		NPrimaryPave->AddText(NPrimaryPaveText);

		char DPrimaryPaveText[20];
		sprintf(DPrimaryPaveText, "D-Primary: %.2f%%", DPrimaryPercentage*100);
		TPaveText *DPrimaryPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		DPrimaryPave->AddText(DPrimaryPaveText);

		char NDPaveText[20];
		sprintf(NDPaveText, "D-Primary: %.2f%%", NDPercentage*100);
		TPaveText *NDPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		NDPave->AddText(NDPaveText);

		char DDPaveText[20];
		sprintf(DDPaveText, "D-Primary: %.2f%%", DDPercentage*100);
		TPaveText *DDPave = new TPaveText(0.2,0.7,0.4,0.9,"NDC");
		DDPave->AddText(DDPaveText);



		sigProjections.push_back(nPrimarySig);
		sigProjections.push_back(dPrimarySig);
		sigProjections.push_back(NDSig);
		sigProjections.push_back(DDSig);

		bckgProjections.push_back(nPrimaryBckg);
		bckgProjections.push_back(dPrimaryBckg);
		bckgProjections.push_back(NDBckg);
		bckgProjections.push_back(DDBckg);

		singleParticlePtY.push_back(pTySingleParticle);
		singleParticlePtY.push_back(pTySingleParticlePrimary);
		singleParticlePtY.push_back(pTySingleParticleN);
		singleParticlePtY.push_back(pTySingleParticleDelta);

		pTyCanvases.push_back(cSingleParticlePtY);
		pTyCanvases.push_back(cSingleParticlePtYPrimary);
		pTyCanvases.push_back(cSingleParticlePtYN);
		pTyCanvases.push_back(cSingleParticlePtYDelta);

		pairProductionCfCanvases.push_back(cNPrimary);
		pairProductionCfCanvases.push_back(cDPrimary);
		pairProductionCfCanvases.push_back(cND);
		pairProductionCfCanvases.push_back(cDD);

		pairProductionCfPaves.push_back(NPrimaryPave);
		pairProductionCfPaves.push_back(DPrimaryPave);
		pairProductionCfPaves.push_back(NDPave);
		pairProductionCfPaves.push_back(DDPave);
	}

	for(int i=0; i<pairProductionCfCanvases.size(); i++)
	{
		pairProductionCfCanvases[i]->cd();
		sigProjections[i]->Rebin(15);
		bckgProjections[i]->Rebin(15);
		sigProjections[i]->Scale(bckgProjections[i]->GetEntries());
		bckgProjections[i]->Scale(sigProjections[i]->GetEntries());
		sigProjections[i]->Divide(bckgProjections[i]);
		sigProjections[i]->GetXaxis()->SetRangeUser(0,800);
		sigProjections[i]->GetYaxis()->SetRangeUser(0.,2.);
		sigProjections[i]->SetLineWidth(2);
		sigProjections[i]->SetMarkerStyle(8);
		sigProjections[i]->SetMarkerColor(sigProjections[i]->GetLineColor());
		sigProjections[i]->SetMarkerSize(0.7);
		sigProjections[i]->Draw();

		pairProductionCfPaves[i]->SetFillStyle(0);
		pairProductionCfPaves[i]->SetBorderSize(0);
		pairProductionCfPaves[i]->Draw();

		sprintf(fileName, "./randomShit/%s%s%s.pdf", particleName, (pairProductionCfCanvases.at(i))->GetTitle(), numberOfTracks);
		pairProductionCfCanvases.at(i)->SaveAs(fileName);
	}

	for(int i=0; i<pTyCanvases.size(); i++)
	{
		pTyCanvases[i]->cd();
		singleParticlePtY[i]->GetXaxis()->SetRangeUser(-1.5, 1.5);
		singleParticlePtY[i]->Draw("colz");

		sprintf(fileName, "./randomShit/%s%s%s.png", particleName, singleParticlePtY.at(i)->GetName(), numberOfTracks);
		pTyCanvases.at(i)->SaveAs(fileName);
	}
/* 
	TCanvas *cKtVsRapidity = new TCanvas("cKtVsRapidity","cKtVsRapidity",800,800);
	cKtVsRapidity->cd();
	totalKtVsTotalRapidity->Draw("colz"); */

	TCanvas *ckTvsRapiditySig = new TCanvas("ckTvRapiditySig","ckTvRapiditySig",800,800);
	ckTvsRapiditySig->cd();
	kTySig->GetXaxis()->SetRangeUser(-1.5, 1.5);
	kTySig->Draw("colz");

	TCanvas *ckTvsRapidityBckg = new TCanvas("ckTvRapidityBckg","ckTvRapidityBckg",800,800);
	ckTvsRapidityBckg->cd();
	kTyBckg->GetXaxis()->SetRangeUser(-1.5, 1.5);
	kTyBckg->Draw("colz");


	return 0;
}