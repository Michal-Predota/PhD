
TFile *coulomb = new TFile("./coulomb_1_2_fm_LCMS.root","read");
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



using namespace std;

double DpolyDa(double x)
{
	return 1;
}

double DpolyDb(double x)
{
	return x;
}

double DpolyDc(double x)
{
	return x*x;
}

double DpolyDd(double x)
{
	return x*x*x;
}

double DpolyDe(double x)
{
	return x*x*x*x;
}
	
double DpolyDf(double x)
{
	return x*x*x*x*x;
}
	
double ErrorPropagationPoly(double x, double sa, double sb, double sc, double sd, double se, double sf)
{
	return TMath::Sqrt(DpolyDa(x)*DpolyDa(x)*sa*sa+ DpolyDb(x)*DpolyDb(x)*sb*sb+ DpolyDc(x)*DpolyDc(x)*sc*sc+ DpolyDd(x)*DpolyDd(x)*sd*sd+ DpolyDe(x)*DpolyDe(x)*se*se+ DpolyDf(x)*DpolyDf(x)*sf*sf);
}


double DsigmoidDa(double x, double a, double b)
{
	return TMath::Exp(b*x)/(1+TMath::Exp(b*x));
}


double DsigmoidDb(double x, double a, double b)
{
	return a*x*TMath::Exp(b*x)/TMath::Power((TMath::Exp(b*x)+1), 2);
}

	
double ErrorPropagationSigmoid(double x, double a, double b, double sa, double sb)
{
	return TMath::Sqrt(DsigmoidDa(x,a,b)*DsigmoidDa(x,a,b)*sa*sa + DsigmoidDb(x,a,b)*DsigmoidDb(x,a,b)*sb*sb);
}


double hermite4(double x)
{
	return 16*x*x*x*x-48*x*x+12;
}

double hermite6(double x)
{
	return 64*x*x*x*x*x*x-480*x*x*x*x+720*x*x-120;
}

double hermite8(double x)
{
	return 256*x*x*x*x*x*x*x*x-3584*x*x*x*x*x*x+13440*x*x*x*x-13440*x*x+1680;
}

double hermite10(double x)
{
	return 1024*x*x*x*x*x*x*x*x*x*x-23040*x*x*x*x*x*x*x*x+161280*x*x*x*x*x*x-403200*x*x*x*x+302400*x*x-30240;
}


double modifiedGausFitHermiteUpTo10(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(4 * 4*3*2)*hermite4(x[0]*pars[1]*scale) +
														   pars[4]/(8 * 6*5*4*3*2)*hermite6(x[0]*pars[1]*scale)+
														   pars[5]/(16 * 8*7*6*5*4*3*2)*hermite8(x[0]*pars[1]*scale)+
														   pars[6]/(32 * 10*9*8*7*6*5*4*3*2)*hermite10(x[0]*pars[1]*scale)));
	
}

double modifiedGausFitHermiteUpTo6(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(4 * 4*3*2)*hermite4(x[0]*pars[1]*scale) +
														   pars[4]/(8 * 6*5*4*3*2)*hermite6(x[0]*pars[1]*scale)));
	
}

double modifiedGausFitHermiteUpTo4(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(4 * 4*3*2)*hermite4(x[0]*pars[1]*scale)));
	
}







int doubleRatioSmashPim()
{
	
	gStyle->SetOptStat(0000);
	
	TFile *f_exp = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_ChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");//experiment
	TFile *f_sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitsMix_wireDistanceGT4AllLayersNoSharedMeta_50k_gen4.root","read");//simulation
	TFile *output = new TFile("./outputs/analysisWiresHarshVertexCut_nTracksGT5_-1VertexZ3mmMix_sharedWiresLT1NoSharedMetaSignals.root", "recreate");
	
	char SigName[20];
	char BckgName[20];
	
	TH1D *sigSMASH = new TH1D("pim_Signal_SMASH","pim_Signal_SMASH",1500,0,1500);
	TH1D *bckgSMASH = new TH1D("pim_Background_SMASH","pim_Background_SMASH",1500,0,1500);
	
	TH1D *sigExp = new TH1D("pim_Signal_PP","pim_Signal_PP",1500,0,1500);
	TH1D *bckgExp = new TH1D("pim_Background_PP","pim_Background_PP",1500,0,1500);
	
	
	TPaveText *t = new TPaveText(.5,1.4,0.8,1.6);
	t->SetTextAlign(12); // left horizontally, centered vertically
	t->AddText("p+p at #sqrt{s} = 3.46 GeV");
	t->AddText("HADES work in progress");
	t->AddText("No shared wires");
	t->AddText("nTrack#geq 6");
	t->SetBorderSize(0);
	t->SetFillStyle(0);
		
	TCanvas canvas("canvas");
	
	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			
			TH1D* tempsigSMASH = (TH1D*)f_sim->Get(SigName);
			TH1D* tempbckgSMASH = (TH1D*)f_sim->Get(BckgName);
			
			
			TH1D* tempSigExp = (TH1D*)f_exp->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f_exp->Get(BckgName);
			
			
			
			if(tempSigExp && tempsigSMASH)
			{
				canvas.cd();
				canvas.Clear();
				tempsigSMASH->SetNameTitle(SigName,SigName);
				tempsigSMASH->Draw();
				tempSigExp->SetLineColor(kRed);
				tempSigExp->Scale(tempsigSMASH->Integral()/tempSigExp->Integral());
				tempSigExp->Draw("samehist");
				
				
				TLegend *legendSig = new TLegend(0.9,0.9,0.65,0.75);
				legendSig->AddEntry(tempsigSMASH,"sig SMASH", "l");
				legendSig->AddEntry(tempSigExp,"sig Exp", "l");
				legendSig->Draw();
				
				
				//background
				canvas.cd();
				canvas.Clear();
				tempBckgExp->SetNameTitle("PimBckg","PimBckg");
				//tempBckgExp->GetYaxis()->SetRangeUser(0, 1.1*tempBckgExp->GetMaximum());
				//tempBckgExp->SetNameTitle(BckgName,BckgName);
				tempbckgSMASH->SetNameTitle(BckgName,BckgName);
				tempbckgSMASH->Draw();
				tempBckgExp->SetLineColor(kRed);
				tempBckgExp->Scale(tempbckgSMASH->Integral()/tempBckgExp->Integral());
				tempBckgExp->Draw("samehist");
				
				
				TLegend *legendBckg = new TLegend(0.9,0.9,0.65,0.75);
				legendBckg->AddEntry(tempbckgSMASH,"bckg pp", "l");
				legendBckg->AddEntry(tempBckgExp,"bckg AgAg", "l");
				legendBckg->Draw();
				
				
			//	cout<<sigSMASH->GetNbinsX()<<" "<<tempsigSMASH->GetNbinsX()<<endl;
				sigSMASH->Add(tempsigSMASH);
				bckgSMASH->Add(tempbckgSMASH);
				
				
				delete tempsigSMASH;
				delete tempbckgSMASH;
				delete tempSigExp;
				delete tempBckgExp;
				delete legendSig;
				delete legendBckg;
			}
		}
	}
	
	
	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			TH1D* tempSigExp = (TH1D*)f_exp->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f_exp->Get(BckgName);
			
			if(tempSigExp)
			{
			//	cout<<sigExp->GetNbinsX()<<" "<<tempSigExp->GetNbinsX()<<endl;
				sigExp->Add(tempSigExp);
				bckgExp->Add(tempBckgExp);
				
				delete tempSigExp;
				delete tempBckgExp;
			}
		}
	}
	
	
	
	sigExp->Rebin(15);
	bckgExp->Rebin(15);
	sigSMASH->Rebin(15);
	bckgSMASH->Rebin(15);	
	
	sigExp->Sumw2(true);
	bckgExp->Sumw2(true);
	sigSMASH->Sumw2(true);
	bckgSMASH->Sumw2(true);
	
	
	cout<<"exp "<<sigExp->GetEntries()<<" "<<bckgExp->GetEntries()<<endl;
	cout<<"SMASH "<<sigSMASH->GetEntries()<<" "<<bckgSMASH->GetEntries()<<endl;
	
	canvas.cd();
	canvas.Clear();
	
	double numint_div_denint_urqmd = (double)bckgSMASH->Integral()/sigSMASH->Integral();
	
	cout<<"podzielone SMASH "<<numint_div_denint_urqmd<<endl;
	
	
	
	cout<<"sigSMASH "<<sigSMASH->GetEntries()<<" "<<sigSMASH->Integral()<<endl;
	cout<<"bckgSMASH "<<bckgSMASH->GetEntries()<<" "<<bckgSMASH->Integral()<<endl;
	
	
	TH1D *sigSMASHCopy = new TH1D(*sigSMASH);
	sigSMASHCopy->SetNameTitle("SMASH_nom","SMASH_nom");
	bckgSMASH->SetNameTitle("SMASH_den","SMASH_den");
	sigSMASHCopy->Write();
	bckgSMASH->Write();

	sigSMASH->Divide(bckgSMASH);
	sigSMASH->Scale(numint_div_denint_urqmd, "");
	sigSMASH->SetNameTitle("SMASH", "SMASH");
	sigSMASH->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	sigSMASH->GetYaxis()->SetTitle("CF");
	sigSMASH->DrawCopy();
	
	bckgSMASH->Draw();
	
	canvas.cd();
	canvas.Clear();
	
	cout<<"sigExp "<<sigExp->GetEntries()<<" "<<sigExp->Integral()<<endl;
	cout<<"bckgExp "<<bckgExp->GetEntries()<<" "<<bckgExp->Integral()<<endl;
	
	double numint_div_denint = (double)bckgExp->Integral()/sigExp->Integral();
	
	cout<<"podzielone exp "<<numint_div_denint<<endl;
	
	
	TH1D* ExpNom = new TH1D(*sigExp);
	ExpNom->SetNameTitle("expNom","expNom");
	bckgExp->SetNameTitle("expDen","expDen");
	ExpNom->Write();
	bckgExp->Write();
	
	
	
	sigExp->Divide(bckgExp);
	sigExp->Scale(numint_div_denint, "");
	sigExp->SetNameTitle("Exp", "Exp");
	sigExp->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	sigExp->GetYaxis()->SetTitle("CF");
	sigExp->DrawCopy();


	//sigExp->Sumw2();
	//sigSMASH->Sumw2();


	TH1D* CopyExp = new TH1D(*sigExp);
	CopyExp->SetNameTitle("expCF","expCF");

	cout<<sigExp->GetNbinsX()<<" "<<sigSMASH->GetNbinsX()<<endl;


	int max=600;

	TF1* MyTanH = new TF1("MyTanH", "TMath::TanH([1]*x)", 0, max);
	TF1* MyLog = new TF1("MyLog", "TMath::Log([1]*x)", 0, max);
	TF1* MyPoly = new TF1("MyPoly","[0]+[1]*x+[2]*x^2+[3]*x^3+[4]*x^4+[5]*x^5",0,max);
	//TF1* MyPoly = new TF1("MyPoly","[0]+[1]*x+[2]*x^2+[3]*x^3",0,max);
	
	TF1* MySigmoid = new TF1("MySigmoid","[0]*e^([1]*x)/(1+e^([1]*x))",0,max);

//	sigSMASH->Fit(MySigmoid, "REMV");
	sigSMASH->Fit(MyPoly, "REM");

 
	TCanvas *c = new TCanvas("c","c",800,800);
	sigSMASH->Draw();
	//MyTanH->Draw("same");

	//sigExp->Divide(sigSMASH);

	sigSMASH->GetXaxis()->SetRangeUser(0,max);
	//sigSMASH->Draw();
	

	const double *fErr = MyPoly->GetParErrors();
	const double *fPar = MyPoly->GetParameters();
	
	
	/*
	for(int i=1;i<=sigExp->GetNbinsX();i++)
	{
		if(sigExp->GetBinLowEdge(i)<max)
		{
			double x = sigExp->GetBinCenter(i);
			
			double h = sigExp->GetBinContent(i);
			double dh = sigExp->GetBinError(i);
			
			double a = MyPoly->GetParameter(0);
			double b = MyPoly->GetParameter(1);
			double c = MyPoly->GetParameter(2);
			double d = MyPoly->GetParameter(3);
			double e = MyPoly->GetParameter(4);
			double f = MyPoly->GetParameter(5);
	
			double da = fErr[0];
			double db = fErr[1];
			double dc = fErr[2];
			double dd = fErr[3];
			double de = fErr[4];
			double df = fErr[5];
			
			double valueF = MyPoly->Eval(x);
			
			
			double error = TMath::Sqrt(TMath::Power(1/valueF*dh,2) + 
			TMath::Power(-h/(valueF*valueF)*da,2) + 
			TMath::Power(-h/(valueF*valueF)*x*db,2) + 
			TMath::Power(-h/(valueF*valueF)*x*x*dc,2) + 
			TMath::Power(-h/(valueF*valueF)*x*x*x*dd,2)+
			TMath::Power(-h/(valueF*valueF)*x*x*x*x*de,2)+
			TMath::Power(-h/(valueF*valueF)*x*x*x*x*x*df,2));
			
			
			double error1 = TMath::Sqrt(
				TMath::Power(1/(valueF)*dh, 2) +
				TMath::Power(h/(valueF)*da, 2) +
				TMath::Power(h/(valueF)*db ,2) + 
				TMath::Power(h/(valueF)*dc, 2) +
				TMath::Power(h/(valueF)*dd, 2) +
				TMath::Power(h/(valueF)*de, 2) +
				TMath::Power(h/(valueF)*df, 2)
			);
			
			cout<<error<<" "<<error1<<endl;
			
			sigExp->SetBinError(i,error1);
			sigExp->SetBinContent(i, h/valueF);
		}
		else
		{
			sigExp->SetBinContent(i,0);
			sigExp->SetBinError(i,0);
		}
	}
	*/
	sigExp->Divide(sigSMASH);
	
	
	
	int cnt=0;
	double average=0;
	for(int i=sigExp->FindBin(250); i<=sigExp->FindBin(350); i++)
	{
		cnt++;
		average+=sigExp->GetBinContent(i);
	}
	average/=cnt;
	cout<<"srednia "<<average<<endl;
	cout<<"cnt "<<cnt<<endl;

	sigExp->Scale(1/average);

	sigExp->SetNameTitle("doubleRatio","doubleRatio");
	sigExp->GetXaxis()->SetTitle("q_{inv} (MeV)");
	sigExp->GetYaxis()->SetTitle("CF_{exp}/CF_{SMASH}");
	sigExp->Draw();

	sigExp->GetXaxis()->SetRangeUser(0, max);
	sigExp->SetMarkerStyle(20);
	sigExp->SetMarkerColor(sigExp->GetLineColor());
	sigExp->SetMarkerSize(0.5);
	sigExp->Write(); 
	CopyExp->Write();
	sigSMASH->Write();
	
//	output->Save();








//fitting

	TFile *coulomb = new TFile("./coulomb_1_2_fm_LCMS.root","read");
	
	//TH1D *coulombCorrection = (TH1D*)coulomb->Get("Coulomb_R_0.680000");
	TH1D *coulombCorrection = (TH1D*)coulomb->Get("Coulomb_R_1.000000");


	
	TF1 *fitExp = new TF1("fitExp", coulombExpFit, 0.02, 0.4, 3);
	TF1 *hermite4Gaus = new TF1("fitGausHermite6", modifiedGausFitHermiteUpTo4, 0.03, 0.4, 4);
	
	
	TF1 *hermite6Gaus = new TF1("fitGausHermite6", modifiedGausFitHermiteUpTo6, 0.03, 0.4, 5);
	
	TF1 *fitGaus = new TF1("fitGaus", coulombGausFit, 0.02, 0.4, 3);
	
	hermite6Gaus->SetParName(0, "lambda");
	hermite6Gaus->SetParName(1, "R");
	hermite6Gaus->SetParName(2, "norm");
	
	hermite6Gaus->SetParameters(0.7,1,1,1,1);
	
	hermite6Gaus->SetParLimits(0,0,1);
	hermite6Gaus->SetParLimits(1,0.001,15);
	hermite6Gaus->SetParLimits(2,0.01,10);
	
	
	hermite4Gaus->SetParName(0, "lambda");
	hermite4Gaus->SetParName(1, "R");
	hermite4Gaus->SetParName(2, "norm");
	
	hermite4Gaus->SetParameters(0.7,1,1,1,1);
	
	hermite4Gaus->SetParLimits(0,0,1);
	hermite4Gaus->SetParLimits(1,0.001,15);
	hermite4Gaus->SetParLimits(2,0.01,10);
	
	
	fitGaus->SetParName(0, "lambda");
	fitGaus->SetParName(1, "R");
	fitGaus->SetParName(2, "norm");
	
	fitGaus->SetParameters(0.7,2,1,2);
	
	fitGaus->SetParLimits(0,0,1);
	fitGaus->SetParLimits(1,0.001,15);
	fitGaus->SetParLimits(2,0.01,10);
	fitGaus->SetParLimits(3,1,2);
	
	
	
	fitExp->SetParName(0, "lambda");
	fitExp->SetParName(1, "R");
	fitExp->SetParName(2, "norm");
	
	fitExp->SetParameters(0.7,2,1,2);
	
	fitExp->SetParLimits(0,0,1);
	fitExp->SetParLimits(1,0.001,15);
	fitExp->SetParLimits(2,0.01,10);
	fitExp->SetParLimits(3,1,2);
	
	
	
	
	TH1D *hGeV = new TH1D("doubleRatioCF","doubleRatioCF",sigExp->GetNbinsX(),0,sigExp->GetXaxis()->GetXmax()/1000);	
	hGeV->GetXaxis()->SetTitle("q_{inv} (GeV/c)");
	hGeV->GetYaxis()->SetTitle("CF_{exp}/fit_{SMASH}");
	
	for(int i=1;i<=sigExp->GetNbinsX();i++)
	{
		hGeV->SetBinContent(i,sigExp->GetBinContent(i));
		hGeV->SetBinError(i,sigExp->GetBinError(i));
	}
	cout<<endl<<endl<<"************ gaus ************"<<endl;
	hGeV->Fit(fitGaus, "REM0", "");
	double gausLow=0;
	double gausTop=0;
	fitGaus->GetRange(gausLow,gausTop);
	TF1 *gausExtrapolated = new TF1("gausExtrapolated", coulombGausFit, gausTop, gausTop+0.3, fitGaus->GetNpar());
	for(int i=0; i<fitGaus->GetNpar(); i++)
	{
		gausExtrapolated->SetParameter(i, fitGaus->GetParameter(i));
	}
	cout<<endl<<endl<<"N_gaus= "<<fitGaus->GetParameter(2)<<" ("<<fitGaus->GetParError(2)<<")"<<endl;
	cout<<"R_gaus= "<<fitGaus->GetParameter(1)<<" ("<<fitGaus->GetParError(1)<<")"<<endl;
	cout<<"lambda_gaus= "<<fitGaus->GetParameter(0)<<" ("<<fitGaus->GetParError(0)<<")"<<endl;
	
	hGeV->Fit(fitExp, "REM0", "");
	cout<<endl<<endl<<"N_exp= "<<fitExp->GetParameter(2)<<" ("<<fitExp->GetParError(2)<<")"<<endl;
	cout<<"R_exp scaled= "<<fitExp->GetParameter(1)/TMath::Pi()<<" ("<<fitExp->GetParError(1)/TMath::Pi()<<")"<<endl;
	cout<<"R_exp= "<<fitExp->GetParameter(1)<<" ("<<fitExp->GetParError(1)<<")"<<endl;
	cout<<"lambda_exp= "<<fitExp->GetParameter(0)<<" ("<<fitExp->GetParError(0)<<")"<<endl;
	
	cout<<endl<<endl<<"************ hermite 4 ************"<<endl;
	hGeV->Fit(hermite4Gaus, "REM0", "");
	double hermite4GausLow=0;
	double hermite4GausTop=0;
	hermite4Gaus->GetRange(hermite4GausLow,hermite4GausTop);
	TF1 *hermite4GausExtrapolated = new TF1("hermite4GausExtrapolated", modifiedGausFitHermiteUpTo4, hermite4GausTop, hermite4GausTop+0.3, hermite4Gaus->GetNpar());
	for(int i=0; i<hermite4Gaus->GetNpar(); i++)
	{
		hermite4GausExtrapolated->SetParameter(i, hermite4Gaus->GetParameter(i));
	}
	cout<<endl<<endl<<"N_gaus hermite4= "<<hermite4Gaus->GetParameter(2)<<" ("<<hermite4Gaus->GetParError(2)<<")"<<endl;
	cout<<"R_gaus hermite4= "<<hermite4Gaus->GetParameter(1)<<" ("<<hermite4Gaus->GetParError(1)<<")"<<endl;
	cout<<"lambda_gaus hermite4= "<<hermite4Gaus->GetParameter(0)<<" ("<<hermite4Gaus->GetParError(0)<<")"<<endl;
	
	
	cout<<endl<<endl<<"************ hermite 6 ************"<<endl;
	hGeV->Fit(hermite6Gaus, "REM0", "");
	double hermite6GausLow=0;
	double hermite6GausTop=0;
	hermite6Gaus->GetRange(hermite6GausLow,hermite6GausTop);
	TF1 *hermite6GausExtrapolated = new TF1("hermite6GausExtrapolated", modifiedGausFitHermiteUpTo6, hermite6GausTop, hermite6GausTop+0.3, hermite6Gaus->GetNpar());
	for(int i=0; i<hermite6Gaus->GetNpar(); i++)
	{
		hermite6GausExtrapolated->SetParameter(i, hermite6Gaus->GetParameter(i));
	}
	cout<<endl<<endl<<"N_gaus hermite6= "<<hermite6Gaus->GetParameter(2)<<" ("<<hermite6Gaus->GetParError(2)<<")"<<endl;
	cout<<"R_gaus hermite6= "<<hermite6Gaus->GetParameter(1)<<" ("<<hermite6Gaus->GetParError(1)<<")"<<endl;
	cout<<"lambda_gaus hermite6= "<<hermite6Gaus->GetParameter(0)<<" ("<<hermite6Gaus->GetParError(0)<<")"<<endl;
	hGeV->GetXaxis()->SetRangeUser(0,0.8);
	hGeV->GetYaxis()->SetRangeUser(0.6,1.6);
	hGeV->SetLineWidth(2);
	hGeV->SetMarkerStyle(8);
	hGeV->SetMarkerSize(0.7);
	hGeV->SetMarkerColor(hGeV->GetLineColor());
	hGeV->GetYaxis()->SetTitle("CF_{exp}/CF_{SMASH}");
	
	hGeV->SetNameTitle("","");
	hGeV->Draw();
	
	fitGaus->Draw("same");
	fitExp->SetLineColor(kOrange+1);
	
	cout<<"gaus chi2/ndf "<<fitGaus->GetChisquare()/fitGaus->GetNDF()<<endl;
	fitGaus->SetLineColor(kRed);
//	fitGaus->Draw("same");
	
	gausExtrapolated->SetLineColor(fitGaus->GetLineColor());
	gausExtrapolated->SetLineStyle(kDashed);
	gausExtrapolated->Draw("same");
	
	
	cout<<"hermite6Gaus chi2/ndf "<<hermite6Gaus->GetChisquare()/hermite6Gaus->GetNDF()<<endl;
	hermite6Gaus->SetLineColor(kOrange+1);
	hermite6Gaus->Draw("same");
	
	hermite6GausExtrapolated->SetLineColor(hermite6Gaus->GetLineColor());
	hermite6GausExtrapolated->SetLineStyle(kDashed);
	hermite6GausExtrapolated->Draw("same");
	
	
	cout<<"hermite4Gaus chi2/ndf "<<hermite4Gaus->GetChisquare()/hermite4Gaus->GetNDF()<<endl;
	hermite4Gaus->SetLineColor(kMagenta+1);
	hermite4Gaus->Draw("same");
	
	hermite4GausExtrapolated->SetLineColor(hermite4Gaus->GetLineColor());
	hermite4GausExtrapolated->SetLineStyle(kDashed);
//	fitExp->Draw("same");
	
	coulombCorrection->SetLineColor(kGreen+1);
//	coulombCorrection->Draw("same");
	
	
	TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
	leg->AddEntry(hGeV, "CF", "lp");
//	leg->AddEntry(coulombCorrection, name, "lp");
//	leg->AddEntry(coulombCorrection, "Coulomb potential, 1 fm", "lp");
	leg->AddEntry(fitGaus, "Bowler-Sinyukov", "l");
	leg->AddEntry(hermite4Gaus, "Bowler-Sinyukov + H_{4}", "l");
	leg->AddEntry(hermite6Gaus, "Bowler-Sinyukov + H_{4} + H_{6}", "l");
//	leg->AddEntry(fitExp, "Exponential fit", "l");
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
	leg->Draw();
	t->Draw();
	TLine *line = new TLine(0.02,1,0.8,1);
	line->SetLineColor(kAzure-3);
	line->SetLineStyle(9);
	line->Draw();
	return 0;
}
