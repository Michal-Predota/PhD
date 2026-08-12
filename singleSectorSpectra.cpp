
#include "TMath.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TF1.h"


int singleSectorSpectra()
{
	
	TFile *f = new TFile("./jobs/singleSectorSpectra_10k.root","read");
	
	vector<TH2D*> pxvspy2D;
	vector<TH2D*> pzvsE2D;
	vector<TH2D*> betavsmomentum2D;
	vector<TH2D*> pty2D;
	
	vector<TH1D*> totalMomenta;
	vector<TH1D*> px;
	vector<TH1D*> py;
	vector<TH1D*> pz;
	vector<TH1D*> E;
	vector<TH1D*> pt;
	vector<TH1D*> y;
	
	TCanvas *cPx = new TCanvas("cPx","cPx");
	TCanvas *cPy = new TCanvas("cPy","cPy");
	TCanvas *cPz = new TCanvas("cPz","cPz");
	TCanvas *cP = new TCanvas("cP","cP");
	TCanvas *cE = new TCanvas("cE","cE");
	TCanvas *cPt = new TCanvas("cPt","cPt");
	TCanvas *cy = new TCanvas("cy","cy");
	
	
	vector<int> colors = {kBlue+1, kRed, kMagenta+1, kGreen+1, kCyan+2, kYellow+3};
	char name[50];
	TLegend *lPx= new TLegend(0.6,0.2,0.9,0.4);
	lPx->SetBorderSize(0);
	lPx->SetFillStyle(0);
	TLegend *lPy= new TLegend(0.6,0.2,0.9,0.4);
	lPy->SetBorderSize(0);
	lPy->SetFillStyle(0);
	TLegend *lPz= new TLegend(0.6,0.2,0.9,0.4);
	lPz->SetBorderSize(0);
	lPz->SetFillStyle(0);
	TLegend *lE= new TLegend(0.6,0.2,0.9,0.4);
	lE->SetBorderSize(0);
	lE->SetFillStyle(0);
	TLegend *lTotMom= new TLegend(0.6,0.2,0.9,0.4);
	lTotMom->SetBorderSize(0);
	lTotMom->SetFillStyle(0);
	TLegend *lPt= new TLegend(0.6,0.2,0.9,0.4);
	lPt->SetBorderSize(0);
	lPt->SetFillStyle(0);
	TLegend *ly= new TLegend(0.6,0.2,0.9,0.4);
	ly->SetBorderSize(0);
	ly->SetFillStyle(0);
	
	for(int i=0; i<=5; i++)
	{
		sprintf(name, "betaMomentumSector%d", i);
		betavsmomentum2D.push_back((TH2D*)f->Get(name));
		
		sprintf(name, "hPyVsPxSector%d", i);
		pxvspy2D.push_back((TH2D*)f->Get(name));
		
		sprintf(name, "hPzVsESector%d", i);
		pzvsE2D.push_back((TH2D*)f->Get(name));
		
		sprintf(name, "hPtYSector%d", i);
		pty2D.push_back((TH2D*)f->Get(name));
		
		sprintf(name, "hMomentumSector%d", i);
		totalMomenta.push_back((TH1D*)f->Get(name));
		totalMomenta.at(i)->Rebin(10);
		totalMomenta.at(i)->SetNameTitle(name, name);
		totalMomenta.at(i)->SetMarkerStyle(20);
		totalMomenta.at(i)->SetMarkerSize(0.5);
		totalMomenta.at(i)->SetMarkerColor(colors.at(i));
		totalMomenta.at(i)->SetLineColor(colors.at(i));
		totalMomenta.at(i)->Scale(1/totalMomenta.at(i)->Integral());
		totalMomenta.at(i)->SetLineWidth(2);
		lTotMom->AddEntry(totalMomenta.at(i),name,"lp");
		cP->cd();
		if(i==0)
			totalMomenta.at(i)->Draw("hist");
		else
			totalMomenta.at(i)->Draw("histsame");
		
		sprintf(name, "pxSector%d", i);
		px.push_back(pxvspy2D.at(i)->ProjectionX());
		px.at(i)->Rebin(10);
		px.at(i)->SetNameTitle(name, name);
		px.at(i)->SetMarkerStyle(20);
		px.at(i)->SetMarkerSize(0.5);
		px.at(i)->SetMarkerColor(colors.at(i));
		px.at(i)->SetLineColor(colors.at(i));
		px.at(i)->SetLineWidth(2);
		px.at(i)->Scale(1/px.at(i)->Integral());
		lPx->AddEntry(px.at(i),name,"lp");
		cPx->cd();
		if(i==0)
			px.at(i)->Draw("hist");
		else
			px.at(i)->Draw("histsame");
		sprintf(name, "pySector%d", i);
		py.push_back(pxvspy2D.at(i)->ProjectionY());
		py.at(i)->Rebin(10);
		py.at(i)->SetNameTitle(name, name);
		py.at(i)->SetMarkerStyle(20);
		py.at(i)->SetMarkerSize(0.5);
		py.at(i)->SetMarkerColor(colors.at(i));
		py.at(i)->SetLineColor(colors.at(i));
		py.at(i)->SetLineWidth(2);
		py.at(i)->Scale(1/py.at(i)->Integral());
		lPy->AddEntry(py.at(i),name,"lp");
		cPy->cd();
		if(i==0)
			py.at(i)->Draw("hist");
		else
			py.at(i)->Draw("histsame");
		
		
		sprintf(name, "pzSector%d", i);
		pz.push_back(pzvsE2D.at(i)->ProjectionY());
		pz.at(i)->Rebin(10);
		pz.at(i)->SetNameTitle(name, name);
		pz.at(i)->SetMarkerStyle(20);
		pz.at(i)->SetMarkerSize(0.5);
		pz.at(i)->SetLineWidth(2);
		pz.at(i)->SetMarkerColor(colors.at(i));
		pz.at(i)->SetLineColor(colors.at(i));
		pz.at(i)->Scale(1/pz.at(i)->Integral());
		lPz->AddEntry(pz.at(i),name,"lp");
		cPz->cd();
		if(i==0)
			pz.at(i)->Draw("hist");
		else
			pz.at(i)->Draw("histsame");
		sprintf(name, "ESector%d", i);
		E.push_back(pzvsE2D.at(i)->ProjectionX());
		E.at(i)->Rebin(10);
		E.at(i)->SetNameTitle(name, name);
		E.at(i)->SetMarkerStyle(20);
		E.at(i)->SetMarkerSize(0.5);
		E.at(i)->SetMarkerColor(colors.at(i));
		E.at(i)->SetLineWidth(2);
		E.at(i)->SetLineColor(colors.at(i));
		E.at(i)->Scale(1/E.at(i)->Integral());
		lE->AddEntry(E.at(i),name,"lp");
		cE->cd();
		if(i==0)
			E.at(i)->Draw("hist");
		else
			E.at(i)->Draw("histsame");
		
		
		sprintf(name, "ptSector%d", i);
		pt.push_back(pty2D.at(i)->ProjectionY());
		pt.at(i)->Rebin(10);
		pt.at(i)->SetNameTitle(name, name);
		pt.at(i)->SetMarkerStyle(20);
		pt.at(i)->SetMarkerSize(0.5);
		pt.at(i)->SetLineWidth(2);
		pt.at(i)->SetMarkerColor(colors.at(i));
		pt.at(i)->SetLineColor(colors.at(i));
		pt.at(i)->Scale(1/pt.at(i)->Integral());
		lPt->AddEntry(pt.at(i),name,"lp");
		cPt->cd();
		if(i==0)
			pt.at(i)->Draw("hist");
		else
			pt.at(i)->Draw("histsame");
		sprintf(name, "ySector%d", i);
		y.push_back(pty2D.at(i)->ProjectionX());
		y.at(i)->SetNameTitle(name, name);
		y.at(i)->SetMarkerStyle(20);
		y.at(i)->SetMarkerSize(0.5);
		y.at(i)->SetMarkerColor(colors.at(i));
		y.at(i)->SetLineWidth(2);
		y.at(i)->SetLineColor(colors.at(i));
		y.at(i)->Scale(1/y.at(i)->Integral());
		ly->AddEntry(y.at(i),name,"lp");
		cy->cd();
		if(i==0)
			y.at(i)->Draw("hist");
		else
			y.at(i)->Draw("histsame");
	}
	
	cPx->cd();
	lPx->Draw();
	cPy->cd();
	lPy->Draw();
	cPz->cd();
	lPz->Draw();
	cE->cd();
	lE->Draw();
	cP->cd();
	lTotMom->Draw();
	cPt->cd();
	lPt->Draw();
	cy->cd();
	ly->Draw();
	
	
	return 0;
}