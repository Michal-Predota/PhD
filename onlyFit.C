

//TFile *coulomb = new TFile("./coulombs_LCMS_smallR.root","read");
TFile *coulomb = new TFile("./coulomb_1_2_fm.root","read");
	
//TH1D *coulombCorrection = (TH1D*)coulomb->Get("Coulomb_R_0.680000");
TH1D *coulombCorrection = (TH1D*)coulomb->Get("Coulomb_R_1.000000");


double coulombGausFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+gaus));//pars[0]-lambda, pars[1]-R, pars[2]-normalization
}


double coulombExpFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+exp));//pars[0]-lambda, pars[1]-R, pars[2]-normalization
}



double slopeCoulombGausFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+gaus))*(pars[3]*x[0]+pars[4]);//pars[0]-lambda, pars[1]-R, pars[2]-normalization, pars[3]-slope, pars[4]-b
}


double slopeCoulombExpFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+exp))*(pars[3]*x[0]+pars[4]);//pars[0]-lambda, pars[1]-R, pars[2]-normalization, pars[3]-slope, pars[4]-b
}




int onlyFit()
{
	
	TFile *f = new TFile("./outputs/analysisWiresHarshVertexCut_nTracksGT1_-1VertexZ3mmMix_sharedWiresLT1NoSharedMetaSignals.root","read");
	
	TH1D *doubleRatio = (TH1D*)f->Get("doubleRatio");
	
	
	
	int cnt=0;
	double average=0;
	for(int i=doubleRatio->FindBin(250); i<=doubleRatio->FindBin(300); i++)
	{
		cnt++;
		average+=doubleRatio->GetBinContent(i);
	}
	average/=cnt;
	cout<<"srednia "<<average<<endl;
	cout<<"cnt "<<cnt<<endl;

//	doubleRatio->Scale(1/average);
	
//	TF1 *fitGaus = new TF1("fitGaus", coulombGausFit, 0.02, 0.4, 3);
	TF1 *fitGaus = new TF1("fitGaus", slopeCoulombGausFit, 0.02, 0.4, 5);
//	TF1 *fitGaus = new TF1("fitGaus", gausFit, 0.01, 0.25, 3);
	
//	TF1 *fitExp = new TF1("fitExp", coulombExpFit, 0.02, 0.4, 3);
	TF1 *fitExp = new TF1("fitExp", slopeCoulombExpFit, 0.02, 0.4, 5);
//	TF1 *fitExp = new TF1("fitExp", expFit, 0.01, 0.25, 3);
	
	fitGaus->SetParName(0, "lambda");
	fitGaus->SetParName(1, "R");
	fitGaus->SetParName(2, "norm");
	
	fitGaus->SetParameters(0.7,2,1,2);
	
	fitGaus->SetParLimits(0,0,1);
	fitGaus->SetParLimits(1,0.001,15);
	fitGaus->SetParLimits(2,0.01,10);
//	fitGaus->SetParLimits(3,-5,0);
	
	
	
	fitExp->SetParName(0, "lambda");
	fitExp->SetParName(1, "R");
	fitExp->SetParName(2, "norm");
	
	fitExp->SetParameters(0.7,2,1,2);
	
	fitExp->SetParLimits(0,0,1);
	fitExp->SetParLimits(1,0.001,15);
	fitExp->SetParLimits(2,0.01,10);
//	fitExp->SetParLimits(3,-5,0);
	
	
	
	TH1D *hGeV = new TH1D("expCF","expCF",doubleRatio->GetNbinsX(),0,doubleRatio->GetXaxis()->GetXmax()/1000);	
	hGeV->GetXaxis()->SetTitle("q_{inv} (GeV/c)");
	hGeV->GetYaxis()->SetTitle("CF");
	
	for(int i=1;i<=doubleRatio->GetNbinsX();i++)
	{
		hGeV->SetBinContent(i,doubleRatio->GetBinContent(i));
		hGeV->SetBinError(i,doubleRatio->GetBinError(i));
	}
	
	hGeV->GetXaxis()->SetRangeUser(0.0,0.6);
	gStyle->SetOptStat(0000);
	
	cout<<endl<<endl<<"************ gaus ************"<<endl;
	hGeV->Fit(fitGaus, "REM0", "");
	double gausLow=0;
	double gausTop=0;
	fitGaus->GetRange(gausLow,gausTop);
	TF1 *gausExtrapolated = new TF1("gausExtrapolated", coulombGausFit, gausTop, 0.75, 3);
	gausExtrapolated->SetParameters(fitGaus->GetParameter(0),fitGaus->GetParameter(1),fitGaus->GetParameter(2));
	cout<<endl<<endl<<"N_gaus= "<<fitGaus->GetParameter(2)<<" ("<<fitGaus->GetParError(2)<<")"<<endl;
	cout<<"R_gaus= "<<fitGaus->GetParameter(1)<<" ("<<fitGaus->GetParError(1)<<")"<<endl;
	cout<<"lambda_gaus= "<<fitGaus->GetParameter(0)<<" ("<<fitGaus->GetParError(0)<<")"<<endl;
	
	
	cout<<endl<<endl<<"************ exp ************"<<endl;
	hGeV->Fit(fitExp, "REM0", "");
	double expLow=0;
	double expTop=0;
	fitExp->GetRange(expLow,expTop);
	TF1 *expExtrapolated = new TF1("expExtrapolated", coulombExpFit, expTop, 0.75, 3);
	expExtrapolated->SetParameters(fitExp->GetParameter(0),fitExp->GetParameter(1),fitExp->GetParameter(2));
	cout<<endl<<endl<<"N_exp= "<<fitExp->GetParameter(2)<<" ("<<fitExp->GetParError(2)<<")"<<endl;
	//cout<<"R_exp= "<<fitExp->GetParameter(1)/TMath::Pi()<<" ("<<fitExp->GetParError(1)/TMath::Pi()<<")"<<endl;
	cout<<"R_exp= "<<fitExp->GetParameter(1)<<" ("<<fitExp->GetParError(1)<<")"<<endl;
	cout<<"lambda_exp= "<<fitExp->GetParameter(0)<<" ("<<fitExp->GetParError(0)<<")"<<endl;
	
	
	hGeV->SetNameTitle("CF","CF");
	hGeV->Draw();
	cout<<endl<<endl;
	
	
	coulombCorrection->SetLineColor(kGreen+1);
	coulombCorrection->Draw("same");
	
	
	cout<<"gaus chi2/ndf "<<fitGaus->GetChisquare()/fitGaus->GetNDF()<<endl;
	fitGaus->SetLineColor(kRed);
	fitGaus->Draw("same");
	
	gausExtrapolated->SetLineColor(fitGaus->GetLineColor());
	gausExtrapolated->SetLineStyle(kDashed);
	gausExtrapolated->Draw("same");
	
	cout<<"exp chi2/ndf "<<fitExp->GetChisquare()/fitExp->GetNDF()<<endl;
	fitExp->SetLineColor(kOrange+1);
	fitExp->Draw("same");
	
	expExtrapolated->SetLineColor(fitExp->GetLineColor());
	expExtrapolated->SetLineStyle(kDashed);
	expExtrapolated->Draw("same");
	


	char name[100];
	sprintf(name, "%s fm",coulombCorrection->GetName());
	
	TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
	leg->AddEntry(hGeV, "CF", "lp");
	leg->AddEntry(coulombCorrection, name, "lp");
	leg->AddEntry(fitGaus, "Gaussian fit", "l");
	leg->AddEntry(fitExp, "Exponential fit", "l");
	leg->Draw();
	
	
	
	return 0;
}