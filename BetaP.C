
#include "TH1D.h"
#include "TCanvas.h"

using namespace std;


auto *bp_pip = new TF1("pip","x/(TMath::Sqrt(139*139+x*x))",0,2000);
auto *bp_pim = new TF1("pim","-x/(TMath::Sqrt(139*139+x*x))",-2000,0);
auto *bp_p = new TF1("p","x/(TMath::Sqrt(938*938+x*x))",0,3500);



Int_t BetaP()
{
	
	
	
	TFile *inFile = new TFile("./jobs/analysis_NewMixer.root", "READ");
	TFile *pimFile = new TFile("./pimRoughCut.root", "READ");
	TFile *pipFile = new TFile("./pipRoughCut.root", "READ");
	
	TH2D* hist = (TH2D*) inFile->Get("bvsp");
	TCutG* pimRoughCut = (TCutG*) pimFile->Get("pimCutRough");
	TCutG* pipRoughCut = (TCutG*) pipFile->Get("pipCutRough");
	
	
	vector<TF1* > pim_gaus;
	vector<TF1* > pip_gaus;
	vector<TF1* > p_gaus;
	
	
	char name_pim[100];
	char name_pip[100];
	char name_p[100];
	
	TCanvas canvas("canvas");
	canvas.Print("./pimproj.pdf["); 
	TCanvas canvas1("canvas1");
	canvas1.Print("./pipproj.pdf["); 


	TH1D* tempProj = hist->ProjectionX();


	
	int min =100;
	int max =1999;

	int NbinsX=0;

	for(int i=0; i<tempProj->GetNbinsX(); i++)
	{
		if(tempProj->GetBinLowEdge(i)>min && tempProj->GetBinContent(i)<max)
			break;
		
		NbinsX++;
	}	
	
	
	//int nFits =1000;
	int nFits = NbinsX;

	int nBinsPerFit = NbinsX/nFits;
	cout<<nBinsPerFit<<endl;



	
	for(int i=1; i<nFits; i++)
	{
		sprintf(name_pim, "pim%d", i+1);
		sprintf(name_pip, "pip%d", i+1);
		sprintf(name_p, "p%d", i+1);
		
		TH1D *projection_pim = hist->ProjectionY(name_pim, 0+i*nBinsPerFit, 0+(i+1)*nBinsPerFit, "[pimCutRough]");
		TH1D *projection_pip = hist->ProjectionY(name_pip, 2160+i*nBinsPerFit, 2160+(i+1)*nBinsPerFit, "[pipCutRough]");
		TH1D *projection_p = hist->ProjectionY(name_p, 250+i*nBinsPerFit, 250+(i+1)*nBinsPerFit);
		
		
	//	cout<<0+i*nBinsPerFit<<" "<<0+(i+1)*nBinsPerFit<<endl;
		
		
		
		
		TF1* fit_pim = new TF1("gauspim","gaus",0.8*bp_pim->Eval(0+i*nBinsPerFit+5), 1.2*bp_pim->Eval(0+i*nBinsPerFit+5));
		TF1* fit_pip = new TF1("gauspip","gaus",0.8*bp_pip->Eval(100+i*10+5), 1.2*bp_pip->Eval(100+i*10+5));
		TF1* fit_p = new TF1("gausp","gaus",0.8*bp_p->Eval(100+i*10+5), 1.2*bp_p->Eval(100+i*10+5));
		
		fit_pim->SetParameter(1,bp_pim->Eval(0+i*nBinsPerFit+5));
		
		
		fit_pip->SetParameter(1,bp_pip->Eval(250+i*10+5));
		fit_p->SetParameter(1,bp_p->Eval(250+i*10+5));
		
		
		fit_pim->SetParLimits(2,0,100);
		fit_pip->SetParLimits(2,0,100);
		fit_p->SetParLimits(2,0,100);
		
		
		projection_pim->Fit(fit_pim, "q");
		projection_pip->Fit(fit_pip, "q");
		
	//	cout<<fit_pim->GetParameter(2)<<endl;
		if(fit_pim->GetParameter(2)>0.04)
			break;
		
		pim_gaus.push_back(fit_pim);
		pip_gaus.push_back(fit_pip);
		p_gaus.push_back(fit_p);	
		
		
		canvas.Clear();
		projection_pim->Draw();
		
	//	canvas.Print("./pimproj.pdf", "Q"); 
		
		canvas1.Clear();
		projection_pip->Draw();
		
	//	canvas1.Print("./pipproj.pdf", "Q"); 
		
	}
	
	nFits=pim_gaus.size();
	
	canvas.Print("./pimproj.pdf]"); 
	canvas1.Print("./pipproj.pdf]"); 
	
	
	TCutG *pim_cut_1s = new TCutG();
	pim_cut_1s->SetVarX("x");
	pim_cut_1s->SetVarY("y");
	pim_cut_1s->SetNameTitle("pim_cut_1s", "pim_cut_1s");
	
	
	TCutG *pip_cut_1s = new TCutG();
	pip_cut_1s->SetVarX("x");
	pip_cut_1s->SetVarY("y");
	pip_cut_1s->SetNameTitle("pip_cut_1s", "pip_cut_1s");

	
	
	TCutG *pim_cut_2s = new TCutG();
	pim_cut_2s->SetVarX("x");
	pim_cut_2s->SetVarY("y");
	pim_cut_2s->SetNameTitle("pim_cut_2s", "pim_cut_2s");



	TCutG *pip_cut_2s = new TCutG();
	pip_cut_2s->SetVarX("x");
	pip_cut_2s->SetVarY("y");
	pip_cut_2s->SetNameTitle("pip_cut_2s", "pip_cut_2s");

	TCutG *p_cut_2s = new TCutG();
	p_cut_2s->SetVarX("x");
	p_cut_2s->SetVarY("y");
	p_cut_2s->SetNameTitle("p_cut_2s", "p_cut_2s");




	TCutG *pim_cut_3s = new TCutG();
	pim_cut_3s->SetVarX("x");
	pim_cut_3s->SetVarY("y");
	pim_cut_3s->SetNameTitle("pim_cut_3s", "pim_cut_3s");


	TCutG *pip_cut_3s = new TCutG();
	pip_cut_3s->SetVarX("x");
	pip_cut_3s->SetVarY("y");
	pip_cut_3s->SetNameTitle("pip_cut_3s", "pip_cut_3s");


	TCutG *p_cut_3s = new TCutG();
	p_cut_3s->SetVarX("x");
	p_cut_3s->SetVarY("y");
	p_cut_3s->SetNameTitle("p_cut_3s", "p_cut_3s");


	double nBins = (double)TMath::Abs(min-max)/(double)pip_gaus.size();
//	cout<<min<<" "<<max<<" "<<pim_gaus.size()<<endl;
//	cout<<"nbins "<<nBins<<endl;

	int counter=0;
	int which_fit=0;
	int mult=0;
	
	for(Int_t i=min; i<max; i++)
	{
		double currentSigma=pip_gaus.at(TMath::Floor(which_fit/nBins))->GetParameter(2);	
		//double currentSigma=1;	
		double nextSigma;
		if(TMath::Floor(which_fit/nBins)+1<pip_gaus.size())
		{
		//	cout<<TMath::Floor(which_fit/nBins)+1<<endl;
			nextSigma=pip_gaus.at(TMath::Floor(which_fit/nBins)+1)->GetParameter(2);
		}
		else
			nextSigma=currentSigma;
		

		
		double difference =nextSigma-currentSigma;
		double step=difference/(nBins);
		
		cout<<counter<<" "<<TMath::Floor(which_fit/nBins)<<" "<<which_fit<<" "<<i<<endl;
		
		pip_cut_1s->SetPoint(counter, i, bp_pip->Eval(i)+(pip_gaus.at(TMath::Floor(which_fit/nBins))->GetParameter(2)));
		pip_cut_2s->SetPoint(counter, i, bp_pip->Eval(i)+2*(pip_gaus.at(TMath::Floor(which_fit/nBins))->GetParameter(2)));
		pip_cut_3s->SetPoint(counter, i, bp_pip->Eval(i)+3*(pip_gaus.at(TMath::Floor(which_fit/nBins))->GetParameter(2)));
		counter++;
		which_fit++;
		mult++;
		if(mult==nBins)
			mult=0;
		if(i==max)
			break;
	}
//	cout<<endl<<endl<<endl;
	which_fit-=1;

	for(Int_t i=max; i>min; i--)
	{
		double currentSigma=pip_gaus.at(TMath::Floor(which_fit/nBins))->GetParameter(2);	
		double nextSigma;
		if(TMath::Floor(which_fit/nBins)+1<pip_gaus.size())
			nextSigma=pip_gaus.at(TMath::Floor(which_fit/nBins)+1)->GetParameter(2);
		else
			nextSigma=currentSigma;
		
		
		double difference =nextSigma-currentSigma;
		double step=difference/(nBins);
		
		pip_cut_1s->SetPoint(counter, i, bp_pip->Eval(i)-(pip_gaus.at(TMath::Floor(which_fit/nBins))->GetParameter(2)));
		pip_cut_2s->SetPoint(counter, i, bp_pip->Eval(i)-2*(pip_gaus.at(TMath::Floor(which_fit/nBins))->GetParameter(2)));
		pip_cut_3s->SetPoint(counter, i, bp_pip->Eval(i)-3*(pip_gaus.at(TMath::Floor(which_fit/nBins))->GetParameter(2)));
		counter++;
	//	cout<<TMath::Floor(which_fit/nBins)<<endl;
		which_fit--;
		mult++;
		if(mult==nBins)
			mult=0;
	}
	
	
	pip_cut_2s->SetPoint(counter, min, bp_pip->Eval(min)+2*pip_gaus.at(0)->GetParameter(2));
	pip_cut_3s->SetPoint(counter, min, bp_pip->Eval(min)+3*pip_gaus.at(0)->GetParameter(2));



	TFile *outFile = new TFile("Newcuts.root", "RECREATE");

	outFile->cd();
	pip_cut_1s->Write();
	pip_cut_2s->Write();
	pip_cut_3s->Write();
//	outFile->Close();



	TFile *compFile = new TFile("cuts.root", "READ");
	TCutG *oldCut = (TCutG*)compFile->Get("pip_cut_2s");
	oldCut->SetLineColor(kRed);

	TCanvas *c = new TCanvas("c","c",800,800);
	hist->Draw("colz");
	pip_cut_2s->SetLineColor(kGreen);
	pip_cut_2s->Draw("same");
	pip_cut_1s->SetLineColor(kAzure-3);
	pip_cut_1s->Draw("same");
	pip_cut_3s->SetLineColor(kMagenta+1);
	pip_cut_3s->Draw("same");
	oldCut->Draw("same");
	pipRoughCut->Draw("same");
	
	




	return 1;
}
