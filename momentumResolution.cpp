#include "TMath.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TF1.h"


double crystalBallSimple(double *x, double *pars)//doi.1603.08591v1
{
	double norm=pars[0], mean = pars[1], sigma = pars[2];//gaussian parameters
	double kL=pars[3], kH=pars[4];//"melting" parameters
	
	if(sigma<0. || -kL>kH) return 100000000000000000;//return large value (better for minimizer than 0? will be further away from the function)
	
	double z = (x[0]-mean)/sigma;
	
	if(z<=-kL)
		return norm*std::exp(kL*kL*0.5+kL*z);
	else if(z>kH)
		return norm*std::exp(kH*kH*0.5-kH*z);
	else
		return norm*std::exp(-0.5*z*z);
}


double polyMean(double *x, double *pars)
{
	double a=pars[0], b=pars[1], c=pars[2], d=pars[3], e=pars[4], f=pars[5], g=pars[6], h=pars[7], i=pars[8], j=pars[9], X=x[0];
	
	//return a*X*X*X + b*X*X + c*X + d;
	
	return a*X*X*X*X*X*X*X*X + b*X*X*X*X*X*X*X + c*X*X*X*X*X*X + d*X*X*X*X*X + e*X*X*X*X + f*X*X*X + g*X*X + h*X + i;
}

double polySigma(double *x, double *pars)
{
	double a=pars[0], b=pars[1], c=pars[2], d=pars[3], e=pars[4], f=pars[5], g=pars[6], h=pars[7], X=x[0];
	
	return a*X*X*X*X*X*X*X + b*X*X*X*X*X*X + c*X*X*X*X*X + d*X*X*X*X + e*X*X*X + f*X*X + g*X + h;
}

int momentumResolution()
{
	gStyle->SetOptStat(0000);
	
	TFile *file = new TFile("./jobs/smash/momentumResolution_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_gen4_40k.root");
//	TFile *file = new TFile("./jobs/smash/momentumResolution_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_gen4_40k.root");

	TH2D *inverseMomentaDifferenceVsKineMom = (TH2D*) file->Get("inverseMomentaDifferenceVsKineMom");
	TH2D *phiDifferenceVsKineMom = (TH2D*) file->Get("phiDifferenceVsKineMom");
	TH2D *thetaDifferenceVsKineMom = (TH2D*) file->Get("thetaDifferenceVsKineMom");
	
	inverseMomentaDifferenceVsKineMom->RebinX(50);
	phiDifferenceVsKineMom->RebinX(50);
	thetaDifferenceVsKineMom->RebinX(50);
	
	TH1D *means = new TH1D("means","mean;p_{kine} (MeV/c)",inverseMomentaDifferenceVsKineMom->GetNbinsX(), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(inverseMomentaDifferenceVsKineMom->GetNbinsX()));
	TH1D *sigmas = new TH1D("sigmas","sigma;p_{kine} (MeV/c)",inverseMomentaDifferenceVsKineMom->GetNbinsX(), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(inverseMomentaDifferenceVsKineMom->GetNbinsX()));
	TH1D *kL = new TH1D("kL","kL;p_{kine} (MeV/c)",inverseMomentaDifferenceVsKineMom->GetNbinsX(), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(inverseMomentaDifferenceVsKineMom->GetNbinsX()));
	TH1D *kH = new TH1D("kH","kH;p_{kine} (MeV/c)",inverseMomentaDifferenceVsKineMom->GetNbinsX(), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(inverseMomentaDifferenceVsKineMom->GetNbinsX()));
	
//	TH1D *means = new TH1D("means","means",inverseMomentaDifferenceVsKineMom->GetNbinsX(), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), 1500);
//	TH1D *sigmas = new TH1D("sigmas","sigmas",inverseMomentaDifferenceVsKineMom->GetNbinsX(), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), 1500);
//	TH1D *kL = new TH1D("kL","kL",inverseMomentaDifferenceVsKineMom->GetNbinsX(), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), 1500);
//	TH1D *kH = new TH1D("kH","kH",inverseMomentaDifferenceVsKineMom->GetNbinsX(), inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), 1500);
	
	TH1D *meansPhi = new TH1D("meansPhi","mean;p_{kine} (MeV/c)",phiDifferenceVsKineMom->GetNbinsX(), phiDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), phiDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(phiDifferenceVsKineMom->GetNbinsX()));
	TH1D *sigmasPhi = new TH1D("sigmasPhi","sigma;p_{kine} (MeV/c)",phiDifferenceVsKineMom->GetNbinsX(), phiDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), phiDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(phiDifferenceVsKineMom->GetNbinsX()));
	TH1D *kLPhi = new TH1D("kLPhi","kL;p_{kine} (MeV/c)",phiDifferenceVsKineMom->GetNbinsX(), phiDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), phiDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(phiDifferenceVsKineMom->GetNbinsX()));
	TH1D *kHPhi = new TH1D("kHPhi","kH;p_{kine} (MeV/c)",phiDifferenceVsKineMom->GetNbinsX(), phiDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), phiDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(phiDifferenceVsKineMom->GetNbinsX()));
	
	TH1D *meansTheta = new TH1D("meansTheta","mean;p_{kine} (MeV/c)",thetaDifferenceVsKineMom->GetNbinsX(), thetaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), thetaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(thetaDifferenceVsKineMom->GetNbinsX()));
	TH1D *sigmasTheta = new TH1D("sigmasTheta","sigma;p_{kine} (MeV/c)",thetaDifferenceVsKineMom->GetNbinsX(), thetaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), thetaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(thetaDifferenceVsKineMom->GetNbinsX()));
	TH1D *kLTheta = new TH1D("kLTheta","kL;p_{kine} (MeV/c)",thetaDifferenceVsKineMom->GetNbinsX(), thetaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), thetaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(thetaDifferenceVsKineMom->GetNbinsX()));
	TH1D *kHTheta = new TH1D("kHTheta","kH;p_{kine} (MeV/c)",thetaDifferenceVsKineMom->GetNbinsX(), thetaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(1), thetaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(thetaDifferenceVsKineMom->GetNbinsX()));
	
	std::vector<TH1D*> projections;
	std::vector<TH1D*> projectionsPhi;
	std::vector<TH1D*> projectionsTheta;
	std::vector<TF1*> fitsGausInvMom;
	std::vector<TF1*> fitsCBInvMom;
	std::vector<TF1*> fitsCBPhi;
	std::vector<TF1*> fitsGausPhi;
	std::vector<TF1*> fitsCBTheta;
	std::vector<TF1*> fitsGausTheta;
	
	char name[50];
	
	TCanvas canvas("canvas");
	TCanvas canvasPhi("canvasPhi");
	TCanvas canvasTheta("canvasTheta");
	
	canvas.Print("./outputs/invMomDiff.pdf["); 
	canvasPhi.Print("./outputs/phiDiff.pdf["); 
	canvasTheta.Print("./outputs/thetaDiff.pdf["); 
	for(int i=1; i<=inverseMomentaDifferenceVsKineMom->GetNbinsX(); i++)
	{
		int lowEdge = inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(i);
		int highEdge = inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinLowEdge(i)+inverseMomentaDifferenceVsKineMom->GetXaxis()->GetBinWidth(i);
		
		
		
		sprintf(name, "projection_%d_%dMeV",lowEdge,highEdge);;
		
		projections.push_back(inverseMomentaDifferenceVsKineMom->ProjectionY(name,i,i+1));
		projections.at(i-1)->SetNameTitle(name,name);
		
		double lowRange = projections.at(i-1)->GetMean()-3*projections.at(i-1)->GetRMS();
		double highRange = projections.at(i-1)->GetMean()+3*projections.at(i-1)->GetRMS();
		
		projections.at(i-1)->GetXaxis()->SetRangeUser(lowRange,highRange);
		
		sprintf(name, "fitGausInvMom_%d_%dMeV",lowEdge,highEdge);
		fitsGausInvMom.push_back(new TF1(name,"gaus",lowRange,highRange));
		projections.at(i-1)->Fit(fitsGausInvMom.at(i-1), "REMQ0");
		
		
		sprintf(name, "fitCBInvMom_%d_%dMeV",lowEdge,highEdge);
		TF1* f = new TF1(name,crystalBallSimple,lowRange,highRange,5);
		f->SetParNames("norm","mean","sigma","kL","kH");
		double norm  = fitsGausInvMom.at(i-1)->GetParameter(0);
		double mean  = fitsGausInvMom.at(i-1)->GetParameter(1);
		double sigma = fitsGausInvMom.at(i-1)->GetParameter(2);
		f->SetParameters(norm,mean,sigma,2,2);
		f->SetParLimits(1, mean-sigma, mean+sigma);
		f->SetParLimits(2, 0.1*sigma, 4*sigma);
		f->SetParLimits(3, 0, 5);
		f->SetParLimits(4, 0, 5);
		fitsCBInvMom.push_back(f);
		fitsCBInvMom.at(i-1)->SetLineColor(kGreen+1);
		projections.at(i-1)->Fit(fitsCBInvMom.at(i-1), "REMQ0");
		
		means->SetBinContent(i, f->GetParameter(1));
		means->SetBinError(i, f->GetParError(1));
		
		sigmas->SetBinContent(i, f->GetParameter(2));
		sigmas->SetBinError(i, f->GetParError(2));
		
		kL->SetBinContent(i, f->GetParameter(3));
		kL->SetBinError(i, f->GetParError(3));
		
		kH->SetBinContent(i, f->GetParameter(4));
		kH->SetBinError(i, f->GetParError(4));
		
		
		
		
		
		//############## PHI ################//
		sprintf(name, "projectionPhi_%d_%dMeV",lowEdge,highEdge);;
		
		projectionsPhi.push_back(phiDifferenceVsKineMom->ProjectionY(name,i,i+1));
		projectionsPhi.at(i-1)->SetNameTitle(name,name);
		
		lowRange = projectionsPhi.at(i-1)->GetMean()-3*projectionsPhi.at(i-1)->GetRMS();
		highRange = projectionsPhi.at(i-1)->GetMean()+3*projectionsPhi.at(i-1)->GetRMS();
		
		projectionsPhi.at(i-1)->GetXaxis()->SetRangeUser(lowRange,highRange);
		
		sprintf(name, "fitGausPhi_%d_%dMeV",lowEdge,highEdge);
		fitsGausPhi.push_back(new TF1(name,"gaus",lowRange,highRange));
		projectionsPhi.at(i-1)->Fit(fitsGausPhi.at(i-1), "REMQ0");
		
		sprintf(name, "fitCBPhi_%d_%dMeV",lowEdge,highEdge);
		TF1* fPhi = new TF1(name,crystalBallSimple,lowRange,highRange,5);
		fPhi->SetParNames("norm","mean","sigma","kL","kH");
		norm  = fitsGausPhi.at(i-1)->GetParameter(0);
		mean  = fitsGausPhi.at(i-1)->GetParameter(1);
		sigma = fitsGausPhi.at(i-1)->GetParameter(2);
		fPhi->SetParameters(norm,mean,sigma,2,2);
		fPhi->SetParLimits(1, mean-sigma, mean+sigma);
		fPhi->SetParLimits(2, 0.1*sigma, 4*sigma);
		fPhi->SetParLimits(3, 0, 5);
		fPhi->SetParLimits(4, 0, 5);
		fitsCBPhi.push_back(fPhi);
		fitsCBPhi.at(i-1)->SetLineColor(kGreen+1);
		projectionsPhi.at(i-1)->Fit(fitsCBPhi.at(i-1), "REMQ0");
		
		meansPhi->SetBinContent(i, fPhi->GetParameter(1));
		meansPhi->SetBinError(i, fPhi->GetParError(1));
		
		sigmasPhi->SetBinContent(i, fPhi->GetParameter(2));
		sigmasPhi->SetBinError(i, fPhi->GetParError(2));
		
		kLPhi->SetBinContent(i, fPhi->GetParameter(3));
		kLPhi->SetBinError(i, fPhi->GetParError(3));
		
		kHPhi->SetBinContent(i, fPhi->GetParameter(4));
		kHPhi->SetBinError(i, fPhi->GetParError(4));
		
		
		
		
		
		//############## THETA ################//
		sprintf(name, "projectionTheta_%d_%dMeV",lowEdge,highEdge);;
		
		projectionsTheta.push_back(thetaDifferenceVsKineMom->ProjectionY(name,i,i+1));
		projectionsTheta.at(i-1)->SetNameTitle(name,name);
		
		lowRange = projectionsTheta.at(i-1)->GetMean()-3*projectionsTheta.at(i-1)->GetRMS();
		highRange = projectionsTheta.at(i-1)->GetMean()+3*projectionsTheta.at(i-1)->GetRMS();
		
		projectionsTheta.at(i-1)->GetXaxis()->SetRangeUser(lowRange,highRange);
		
		sprintf(name, "fitGausTheta_%d_%dMeV",lowEdge,highEdge);
		fitsGausTheta.push_back(new TF1(name,"gaus",lowRange,highRange));
		projectionsTheta.at(i-1)->Fit(fitsGausTheta.at(i-1), "REMQ0");
		
		sprintf(name, "fitCBTheta_%d_%dMeV",lowEdge,highEdge);
		TF1* fTheta = new TF1(name,crystalBallSimple,lowRange,highRange,5);
		fTheta->SetParNames("norm","mean","sigma","kL","kH");
		norm  = fitsGausTheta.at(i-1)->GetParameter(0);
		mean  = fitsGausTheta.at(i-1)->GetParameter(1);
		sigma = fitsGausTheta.at(i-1)->GetParameter(2);
		fTheta->SetParameters(norm,mean,sigma,2,2);
		fTheta->SetParLimits(1, mean-sigma, mean+sigma);
		fTheta->SetParLimits(2, 0.1*sigma, 4*sigma);
		fTheta->SetParLimits(3, 0, 5);
		fTheta->SetParLimits(4, 0, 5);
		fitsCBTheta.push_back(fTheta);
		fitsCBTheta.at(i-1)->SetLineColor(kGreen+1);
		projectionsTheta.at(i-1)->Fit(fitsCBTheta.at(i-1), "REMQ0");
		
		meansTheta->SetBinContent(i, fTheta->GetParameter(1));
		meansTheta->SetBinError(i, fTheta->GetParError(1));
		
		sigmasTheta->SetBinContent(i, fTheta->GetParameter(2));
		sigmasTheta->SetBinError(i, fTheta->GetParError(2));
		
		kLTheta->SetBinContent(i, fTheta->GetParameter(3));
		kLTheta->SetBinError(i, fTheta->GetParError(3));
		
		kHTheta->SetBinContent(i, fTheta->GetParameter(4));
		kHTheta->SetBinError(i, fTheta->GetParError(4));
		

		
		canvas.Clear();
		projections.at(i-1)->Draw();	
		fitsGausInvMom.at(i-1)->Draw("same");
		fitsCBInvMom.at(i-1)->Draw("same");
		canvas.Print("./outputs/invMomDiff.pdf", "Q"); 
		
		canvasPhi.Clear();
		projectionsPhi.at(i-1)->Draw();	
		fitsGausPhi.at(i-1)->Draw("same");
		fitsCBPhi.at(i-1)->Draw("same");
		canvasPhi.Print("./outputs/phiDiff.pdf", "Q"); 
		
		canvasTheta.Clear();
		projectionsTheta.at(i-1)->Draw();	
		fitsGausTheta.at(i-1)->Draw("same");
		fitsCBTheta.at(i-1)->Draw("same");
		canvasTheta.Print("./outputs/thetaDiff.pdf", "Q"); 
	}
	
	canvas.Print("./outputs/invMomDiff.pdf]"); 
	canvasPhi.Print("./outputs/phiDiff.pdf]"); 
	canvasTheta.Print("./outputs/thetaDiff.pdf]"); 
	
	TF1 *meanPoly = new TF1("meanPoly", polyMean, 80, 2000, 9);
	TF1 *sigmaPoly = new TF1("sigmaPoly", polySigma, 80, 2000, 8);
	TF1 *kLPoly = new TF1("kLPoly", polyMean, 80, 2000, 9);
	TF1 *kHPoly = new TF1("kHPoly", polyMean, 80, 2000, 8);
	
	means->Fit(meanPoly, "REMQ0");
	sigmas->Fit(sigmaPoly, "REMQ0");
	kL->Fit(kLPoly, "REMQ0");
	kH->Fit(kHPoly, "REMQ0");
	
	TCanvas *c = new TCanvas("c","c",800,800);
	c->Divide(2,2);
	c->cd(1);
	means->SetMarkerStyle(8);
	means->SetMarkerSize(0.7);
	means->SetMarkerColor(kBlue+2);
	means->Draw();	
	meanPoly->Draw("same");
	c->cd(2);
	gPad->Clear();
	sigmas->SetMarkerStyle(8);
	sigmas->SetMarkerSize(0.7);
	sigmas->SetMarkerColor(kBlue+2);
	sigmas->Draw();
	sigmaPoly->Draw("same");
	c->cd(3);
	gPad->Clear();
	kL->SetMarkerStyle(8);
	kL->SetMarkerSize(0.7);
	kL->SetMarkerColor(kBlue+2);
	kL->Draw();
	kLPoly->Draw("same");
	c->cd(4);
	gPad->Clear();
	kH->SetMarkerStyle(8);
	kH->SetMarkerSize(0.7);
	kH->SetMarkerColor(kBlue+2);
	kH->Draw();
	kHPoly->Draw("same");
	
	TF1 *meanPolyPhi = new TF1("meanPolyPhi", polyMean, 50, 2000, 9);
	TF1 *sigmaPolyPhi = new TF1("sigmaPolyPhi", polySigma, 50, 2000, 8);
	TF1 *kLPhiPoly = new TF1("kLPhiPoly", polyMean, 50, 2000, 9);
	TF1 *kHPhiPoly = new TF1("kHPhiPoly", polyMean, 50, 2000, 8);
	
	meansPhi->Fit(meanPolyPhi, "REM0");
	sigmasPhi->Fit(sigmaPolyPhi, "REM0");
	kLPhi->Fit(kLPhiPoly, "REMQ0");
	kHPhi->Fit(kHPhiPoly, "REMQ0");
	
	
	TCanvas *cPhi = new TCanvas("cPhi","cPhi",800,800);
	cPhi->Divide(2,2);
	cPhi->cd(1);
	meansPhi->SetMarkerStyle(8);
	meansPhi->SetMarkerSize(0.7);
	meansPhi->SetMarkerColor(kBlue+2);
	meansPhi->Draw();
	meanPolyPhi->Draw("same");	
	cPhi->cd(2);
	sigmasPhi->SetMarkerStyle(8);
	sigmasPhi->SetMarkerSize(0.7);
	sigmasPhi->SetMarkerColor(kBlue+2);
	sigmasPhi->Draw();
	sigmaPolyPhi->Draw("same");	
	cPhi->cd(3);
	kLPhi->SetMarkerStyle(8);
	kLPhi->SetMarkerSize(0.7);
	kLPhi->SetMarkerColor(kBlue+2);
	kLPhi->Draw();
	kLPhiPoly->Draw("same");	
	cPhi->cd(4);
	kHPhi->SetMarkerStyle(8);
	kHPhi->SetMarkerSize(0.7);
	kHPhi->SetMarkerColor(kBlue+2);
	kHPhi->Draw();
	kHPhiPoly->Draw("same");	
	
	
	
	TF1 *meanPolyTheta = new TF1("meanPolyTheta", polyMean, 50, 2000, 9);
	TF1 *sigmaPolyTheta = new TF1("sigmaPolyTheta", polySigma, 50, 2000, 8);
	TF1 *kLThetaPoly = new TF1("kLThetaPoly", polyMean, 50, 2000, 9);
	TF1 *kHThetaPoly = new TF1("kHThetaPoly", polyMean, 50, 2000, 8);
	
	meansTheta->Fit(meanPolyTheta, "REM0");
	sigmasTheta->Fit(sigmaPolyTheta, "REM0");
	kLTheta->Fit(kLThetaPoly, "REMQ0");
	kHTheta->Fit(kHThetaPoly, "REMQ0");
	
	TCanvas *cTheta = new TCanvas("cTheta","cTheta",800,800);
	cTheta->Divide(2,2);
	cTheta->cd(1);
	meansTheta->SetMarkerStyle(8);
	meansTheta->SetMarkerSize(0.7);
	meansTheta->SetMarkerColor(kBlue+2);
	meansTheta->Draw();	
	meanPolyTheta->Draw("same");
	cTheta->cd(2);
	sigmasTheta->SetMarkerStyle(8);
	sigmasTheta->SetMarkerSize(0.7);
	sigmasTheta->SetMarkerColor(kBlue+2);
	sigmasTheta->Draw();
	sigmaPolyTheta->Draw("same");
	cTheta->cd(3);
	kLTheta->SetMarkerStyle(8);
	kLTheta->SetMarkerSize(0.7);
	kLTheta->SetMarkerColor(kBlue+2);
	kLTheta->Draw();
	kLThetaPoly->Draw("same");
	cTheta->cd(4);
	kHTheta->SetMarkerStyle(8);
	kHTheta->SetMarkerSize(0.7);
	kHTheta->SetMarkerColor(kBlue+2);
	kHTheta->Draw();
	kHThetaPoly->Draw("same");
	
	
	TFile *output = new TFile("./smearingFunctions_nTracksGT5.root","recreate");
	output->cd();
	meanPoly->Write();
	meanPolyPhi->Write();
	meanPolyTheta->Write();
	sigmaPoly->Write();
	sigmaPolyPhi->Write();
	sigmaPolyTheta->Write();
	kLPoly->Write();
	kLPhiPoly->Write();
	kLThetaPoly->Write();
	kHPoly->Write();
	kHPhiPoly->Write();
	kHThetaPoly->Write();
	
	
	output->Save();
	output->Close();


	
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_nTracksGT5_noPairCuts_crystalBall_acceptance_recalculatedEnergy_FemtoCoulombWeight_SmearTimes100_Tlv.root","read");
	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_nTracksGT5_noPairCuts_crystalBall_acceptance_recalculatedEnergy_FemtoCoulombWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_crystalBall_acceptance_recalculatedEnergy_NoWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_crystalBall_acceptance_recalculatedEnergy_OnlyFemtoWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_crystalBall_acceptance_recalculatedEnergy_CoulombWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_gauss_acceptance_FemtoCoulombWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_gauss_acceptance_recalculatedEnergy_FemtoCoulombWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_crystalBall_recalculatedEnergy_FemtoCoulombWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_nTracksGT5_noPairCuts_crystalBall_acceptance_recalculatedEnergy_OnlyFemtoWeight_smearTimesFive_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_crystalBall_acceptance_recalculatedEnergy_FemtoCoulombWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_crystalBall_recalculatedEnergy_acceptance_FemtoCoulombWeight_Tlv.root","read");


//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_crystalBall_acceptance_FemtoCoulombWeight_Tlv.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_recalculatedEnergy_FemtoCoulombWeight_UParticle.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_acceptance_recalculatedEnergy_FemtoCoulombWeight_UrQMD.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_recalculatedEnergy_FemtoCoulombWeight_UrQMD.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_acceptance_FemtoCoulombWeight_UrQMD.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_UrQMD.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_acceptance_recalculatedEnergy_UrQMD.root","read");
//	TFile *smearCF = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_recalculatedEnergy_UrQMD.root","read");


	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_nTracksGT5_noPairCuts_acceptance_FemtoCoulombWeight_Tlv.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_acceptance_NoWeight_Tlv.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_acceptance_OnlyFemtoWeight_Tlv.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_acceptance_CoulombWeight_Tlv.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_UParticle.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_Tlv.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_acceptance_FemtoCoulombWeight_UrQMD.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_UrQMD.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_acceptance_UrQMD.root","read");
//	TFile *mcCF = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_UrQMD.root","read");



	TH1D *sigSmear = new TH1D("pim_Signal_smear","pim_Signal_smear",1500,0,1500);
	TH1D *bckgSmear = new TH1D("pim_Background_smear","pim_Background_smear",1500,0,1500);

	TH1D *sigMC = new TH1D("pim_Signal_mc","pim_Signal_mc",1500,0,1500);
	TH1D *bckgMC = new TH1D("pim_Background_mc","pim_Background_mc",1500,0,1500);
	
	
	char SigName[20];
	char BckgName[20];
	
		
	vector<TH1D *>sigKtBinSmear;
	vector<TH1D *>sigRapidityBinSmear;
	vector<TH1D *>bckgKtBinSmear;
	vector<TH1D *>bckgRapidityBinSmear;
	
		
	vector<TH1D *>sigKtBinMC;
	vector<TH1D *>sigRapidityBinMC;
	vector<TH1D *>bckgKtBinMC;
	vector<TH1D *>bckgRapidityBinMC;
	
	for(int i=1; i<10; i++)
	{
		sprintf(SigName, "sigSmearKtBin%d", i);
		sprintf(BckgName, "BckgSmearKtBin%d", i);
		
		sigKtBinSmear.push_back(new TH1D(SigName, SigName,1500,0,1500));
		bckgKtBinSmear.push_back(new TH1D(BckgName, BckgName,1500,0,1500));
		for(int j=1; j<10; j++)
		{	
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			TH1D* tempSig = (TH1D*)smearCF->Get(SigName);
			TH1D* tempBckg = (TH1D*)smearCF->Get(BckgName);
			
			if(tempSig)
			{
				
				sigSmear->Add(tempSig);
				bckgSmear->Add(tempBckg);
				sigKtBinSmear.at(i-1)->Add(tempSig);
				bckgKtBinSmear.at(i-1)->Add(tempBckg);
				
				delete tempSig;
				delete tempBckg;
			}
		}
	}
	
	for(int i=1; i<10; i++)
	{
		sprintf(SigName, "sigMcKtBin%d", i);
		sprintf(BckgName, "BckgMcKtBin%d", i);
		
		sigKtBinMC.push_back(new TH1D(SigName, SigName,1500,0,1500));
		bckgKtBinMC.push_back(new TH1D(BckgName, BckgName,1500,0,1500));
		for(int j=1; j<10; j++)
		{	
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			TH1D* tempSig = (TH1D*)mcCF->Get(SigName);
			TH1D* tempBckg = (TH1D*)mcCF->Get(BckgName);
			
			if(tempSig)
			{
				cout<<SigName<<endl;
				sigMC->Add(tempSig);
				cout<<"tempSig "<<tempSig->GetEntries()<<endl;
				cout<<"bin50 "<<tempSig->GetBinContent(50)<<endl;
				cout<<"mean "<<tempSig->GetMean()<<endl;
				cout<<"sigma "<<tempSig->GetRMS()<<endl;
				cout<<"sigMC "<<sigMC->GetEntries()<<endl<<endl;
				bckgMC->Add(tempBckg);
				sigKtBinMC.at(i-1)->Add(tempSig);
				bckgKtBinMC.at(i-1)->Add(tempBckg);
				
				delete tempSig;
				delete tempBckg;
			}
		}
	}
	
	
	sigMC->Rebin(15);
	bckgMC->Rebin(15);
	sigSmear->Rebin(15);
	bckgSmear->Rebin(15);
	sigMC->Sumw2(true);
	bckgMC->Sumw2(true);
	sigSmear->Sumw2(true);
	bckgSmear->Sumw2(true);
	
	
	TH1D *sigRatio = new TH1D(*sigSmear);
	TH1D *bckgRatio = new TH1D(*bckgSmear);
	sigRatio->Divide(sigMC);
	bckgRatio->Divide(bckgMC);
	
	cout<<sigMC->GetEntries()<<endl;
	cout<<sigMC->GetMean()<<endl;
	cout<<bckgMC->GetEntries()<<endl;
	TH1D *sigMCOriginal = new TH1D(*sigMC);
	TH1D *sigSmearOriginal = new TH1D(*sigSmear);
	
	sigMC->Divide(bckgMC);
	sigSmear->Divide(bckgSmear);
	
	TH1D *sigMCCopy = new TH1D(*sigMC);
	sigMCCopy->Divide(sigSmear);
	
	TCanvas *cWeights = new TCanvas("cWeights","cWeights",800,800);
	sigMCCopy->Draw();
	
	TCanvas *cHistos = new TCanvas("cHistos","cHistos",800,800);
	cHistos->Divide(1,2);
	cHistos->cd(1);
	sigMC->SetNameTitle("CF MC","CF MC");
	sigMC->Draw();
	cHistos->cd(2);
	sigSmear->SetNameTitle("CF Smear","CF Smear");
	sigSmear->Draw();
	
	sigMCCopy->SetNameTitle("momentumResolutionCorrection_nTracksGT5","momentumResolutionCorrection_nTracksGT5");
	sigMCCopy->SaveAs("./outputs/momentumResolutionCorrection_nTracksGT5.root");
	
	TCanvas *cSig = new TCanvas("cSig","cSig",800,800);
	TCanvas *cBckg = new TCanvas("cBckg","cBckg",800,800);
	sigSmearOriginal->SetLineColor(kRed);
	bckgSmear->SetLineColor(kRed);
	
	
	TLegend *legSig = new TLegend(0.6,0.2,0.9,0.4);
	TLegend *legBckg = new TLegend(0.6,0.2,0.9,0.4);
	
	cSig->cd();
	sigMCOriginal->Draw();
	sigSmearOriginal->Draw("same");
	legSig->AddEntry(sigMCOriginal, "unsmeared signal", "lp");
	legSig->AddEntry(sigSmearOriginal, "smeared signal", "lp");
	legSig->SetBorderSize(0);
	legSig->SetFillStyle(0);
	legSig->Draw();


	cBckg->cd();
	bckgMC->Draw();
	bckgSmear->Draw("same");
	legBckg->AddEntry(bckgMC, "unsmeared background", "lp");
	legBckg->AddEntry(bckgSmear, "smeared background", "lp");
	legBckg->SetBorderSize(0);
	legBckg->SetFillStyle(0);
	legBckg->Draw();
	
	TCanvas *cRatios = new TCanvas("cRatios","cRatios",800,800);
	cRatios->Divide(1,2);
	sigRatio->SetNameTitle("sigSmear/sigMC","sigSmear/sigMC");
	bckgRatio->SetNameTitle("bckgSmear/bckgMC","bckgSmear/bckgMC");
	cRatios->cd(1);
	sigRatio->Draw();
	cRatios->cd(2);
	bckgRatio->Draw();
	
	return 0;
}