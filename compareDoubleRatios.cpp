
TFile *coulomb = new TFile("./coulombs_LCMS_smallR.root","read");
	
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


void prepareFunctions(string s,vector<TFile *> files, vector<TH1D*> &CF)
{
	char SigName[20];
	char BckgName[20];
	char tmpSigName[20];
	char tmpBckgName[20];
	vector<TH1D *> signals = {};
	vector<TH1D *> CFGeV = {};
	vector<TH1D *> backgrounds = {};
	for(int f=0; f<files.size(); f++)
	{
		sprintf(SigName, "%snTracksGT%dSig",s.c_str(),f+1);
		sprintf(BckgName, "%snTracksGT%dBckg",s.c_str(),f+1);
		
		
		signals.push_back(new TH1D(SigName,SigName,1500,0,1500));
		backgrounds.push_back(new TH1D(BckgName,BckgName,1500,0,1500));
		for(int i=1; i<10; i++)
		{
			for(int j=1; j<10; j++)
			{
				sprintf(tmpSigName, "PimSig_%d%d",i,j);
				sprintf(tmpBckgName, "PimBckg_%d%d",i,j);
				
				TH1D* tmpSigExp = (TH1D*)files.at(f)->Get(tmpSigName);
				TH1D* tmpBckgExp = (TH1D*)files.at(f)->Get(tmpBckgName);
				
				if(tmpSigExp)
				{
				//	cout<<sigExp->GetNbinsX()<<" "<<tempSigExp->GetNbinsX()<<endl;
					signals.at(f)->Add(tmpSigExp);
					backgrounds.at(f)->Add(tmpBckgExp);
					
					delete tmpSigExp;
					delete tmpBckgExp;
				}
			}
		}
		signals.at(f)->Rebin(15);
		backgrounds.at(f)->Rebin(15);
		signals.at(f)->Sumw2(true);
		backgrounds.at(f)->Sumw2(true);
		CF.push_back(new TH1D(*signals.at(f)));
		CF.at(f)->Divide(backgrounds.at(f));
		int cnt=0;
		double average=0;
		for(int i=CF.at(f)->FindBin(300); i<=CF.at(f)->FindBin(350); i++)
		{
			cnt++;
			average+=CF.at(f)->GetBinContent(i);
		}
		average/=cnt;
		CF.at(f)->Scale(1/average);
	}
}


void fitPolynomials(vector<TH1D*> cf, vector<TF1*> &fits, int max)
{
	char fitName[50];
	for(int i=0; i<cf.size(); i++)
	{
		sprintf(fitName, "nTracksGT%dPolyFit",i+1);
		fits.push_back(new TF1(fitName, "[0]+[1]*x+[2]*x^2+[3]*x^3+[4]*x^4+[5]*x^5",0,max));
		
		cf.at(i)->Fit(fits.at(i), "REM0");
	}
}


void JJRatio(vector<TH1D*> &cf, vector<TF1*> &fit, int max)
{
	for(int c=0; c<cf.size(); c++)
	{
		for(int i=1;i<=cf.at(c)->GetNbinsX();i++)
		{
			const double *fErr = fit.at(c)->GetParErrors();
			const double *fPar = fit.at(c)->GetParameters();
			if(cf.at(c)->GetBinLowEdge(i)<max)
			{
				double x = cf.at(c)->GetBinCenter(i);
				
				double h = cf.at(c)->GetBinContent(i);
				double dh = cf.at(c)->GetBinError(i);
				
				double parA = fit.at(c)->GetParameter(0);
				double parB = fit.at(c)->GetParameter(1);
				double parC = fit.at(c)->GetParameter(2);
				double parD = fit.at(c)->GetParameter(3);
				double parE = fit.at(c)->GetParameter(4);
				double parF = fit.at(c)->GetParameter(5);
		
				double da = fErr[0];
				double db = fErr[1];
				double dc = fErr[2];
				double dd = fErr[3];
				double de = fErr[4];
				double df = fErr[5];
				
				
				const double *fErr = fit.at(c)->GetParErrors();
				const double *fPar = fit.at(c)->GetParameters();
			
				double valueF = fit.at(c)->Eval(x);
				
				double error = TMath::Sqrt(
					TMath::Power(1/(valueF)*dh, 2) +
					TMath::Power(h/(valueF)*da, 2) +
					TMath::Power(h/(valueF)*db ,2) + 
					TMath::Power(h/(valueF)*dc, 2) +
					TMath::Power(h/(valueF)*dd, 2) +
					TMath::Power(h/(valueF)*de, 2) +
					TMath::Power(h/(valueF)*df, 2)
				);
				cf.at(c)->SetBinError(i,error);
				cf.at(c)->SetBinContent(i, h/valueF);
			}
			else
			{
				cf.at(c)->SetBinContent(i,0);
				cf.at(c)->SetBinError(i,0);
			}
		}
	}
}


void fitBS(vector<TH1D*> CFs, vector<TF1*> &fits)
{
	char fitName[50];
	for(int c=0; c<CFs.size(); c++)
	{
		sprintf(fitName, "fitGausGT%d",c+1);
		
		fits.push_back(new TF1(fitName, coulombGausFit,0.02,0.4,3));
		
		
		fits.at(c)->SetParName(0, "lambda");
		fits.at(c)->SetParName(1, "R");
		fits.at(c)->SetParName(2, "norm");
		fits.at(c)->SetParameters(0.7,2,1,2);
		fits.at(c)->SetParLimits(0,0,1);
		fits.at(c)->SetParLimits(1,0.001,15);
		fits.at(c)->SetParLimits(2,0.01,10);
		CFs.at(c)->Fit(fits.at(c), "REM0");
	}
}

vector<TH1D*> scaleToGeV(vector<TH1D*> &CFsMeV)
{
	char name[40];
	vector<TH1D*> CFsGeV;
	for(int c=0; c<CFsMeV.size(); c++)
	{
		sprintf(name, "CFnTracksGT%d", c+1);
		TH1D *hGeV = new TH1D(name,name,CFsMeV.at(c)->GetNbinsX(),0,CFsMeV.at(c)->GetXaxis()->GetXmax()/1000);
		hGeV->GetXaxis()->SetTitle("q_{inv} (GeV/c)");
		hGeV->GetYaxis()->SetTitle("CF");
	
		for(int i=1;i<=hGeV->GetNbinsX();i++)
		{
			hGeV->SetBinContent(i,CFsMeV.at(c)->GetBinContent(i));
			hGeV->SetBinError(i,CFsMeV.at(c)->GetBinError(i));
		}
		CFsGeV.push_back(hGeV);
	}
	
	return CFsGeV;
}


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





int compareDoubleRatios()
{
	gStyle->SetOptStat(0000);
	
//	TFile *nTracksGT1Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");
//	TFile *nTracksGT2Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");
//	TFile *nTracksGT3Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");
//	TFile *nTracksGT4Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");
//	TFile *nTracksGT5Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");



//	TFile *nTracksGT1Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *nTracksGT2Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *nTracksGT3Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *nTracksGT4Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *nTracksGT5Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");



//	TFile *nTracksGT1Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");
//	TFile *nTracksGT2Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");
//	TFile *nTracksGT3Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");
//	TFile *nTracksGT4Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");
//	TFile *nTracksGT5Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");


	

//	TFile *nTracksGT1Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *nTracksGT2Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *nTracksGT3Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *nTracksGT4Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *nTracksGT5Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");

	
	
//	TFile *nTracksGT1Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");
//	TFile *nTracksGT2Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");
//	TFile *nTracksGT3Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");
//	TFile *nTracksGT4Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");
//	TFile *nTracksGT5Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");

	
//	TFile *nTracksGT1Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");
//	TFile *nTracksGT2Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");
//	TFile *nTracksGT3Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");
//	TFile *nTracksGT4Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");
//	TFile *nTracksGT5Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");


	TFile *nTracksGT1Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
	TFile *nTracksGT2Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
	TFile *nTracksGT3Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
	TFile *nTracksGT4Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
	TFile *nTracksGT5Exp = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");



	TFile *nTracksGT1Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");
	TFile *nTracksGT2Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");
	TFile *nTracksGT3Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");
	TFile *nTracksGT4Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");
	TFile *nTracksGT5Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");



//	TFile *sector0Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector0Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *sector1Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector1Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *sector2Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector2Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *sector3Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector3Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *sector4Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector4Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *sector5Exp = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector5Pairs_beamTiltCorr_gen4_50k.root","read");
	
	
	
//	TFile *sector0Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector0Pairs_40k_gen4.root ","read");
//	TFile *sector1Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector1Pairs_40k_gen4.root ","read");
//	TFile *sector2Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector2Pairs_40k_gen4.root ","read");
//	TFile *sector3Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector3Pairs_40k_gen4.root ","read");
//	TFile *sector4Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector4Pairs_40k_gen4.root ","read");
//	TFile *sector5Sim = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector5Pairs_40k_gen4.root ","read");



	
	vector<TFile *> expFiles = {nTracksGT1Exp, nTracksGT2Exp, nTracksGT3Exp, nTracksGT4Exp, nTracksGT5Exp};
	vector<TFile *> simFiles = {nTracksGT1Sim, nTracksGT2Sim, nTracksGT3Sim, nTracksGT4Sim, nTracksGT5Sim};
	
//	vector<TFile *> expFiles = {sector0Exp, sector1Exp, sector2Exp, sector3Exp, sector4Exp, sector5Exp};
//	vector<TFile *> simFiles = {sector0Sim, sector1Sim, sector2Sim, sector3Sim, sector4Sim, sector5Sim};
	
	vector<TH1D *> expSignals = {};
	vector<TH1D *> expCFGeV = {};
	vector<TH1D *> expBackgrounds = {};
	vector<TH1D *> expCF = {};
	vector<TH1D *> simCF = {};
	vector<int> expSigEntries = {};
	vector<int> colors = {kBlue+1, kRed, kMagenta+1, kGreen+1, kCyan+1, kYellow+3};
	vector<TF1*> fits = {};
	vector<TF1*> polyFits = {};
	vector<TF1*> fitsExp = {};
	
	char SigName[20];
	char BckgName[20];
	char tmpSigName[20];
	char tmpBckgName[20];
	char CFName[20];
	char FitName[20];
	
	TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
	TLegend *legSim= new TLegend(0.6,0.2,0.9,0.4);
	
	
	TPaveText *t = new TPaveText(.4,1.2,0.8,1.4);
	t->AddText("p+p at #sqrt{s} = 3.46 GeV");
	t->AddText("HADES work in progress");
	t->SetBorderSize(0);
	t->SetFillStyle(0);
	
	prepareFunctions("Exp", expFiles, expCF);
	
	prepareFunctions("Sim", simFiles, simCF);
	
	fitPolynomials(simCF,polyFits,600);
	
	//JJRatio(expCF, polyFits, 600);
	
	for(int i=0; i<expCF.size(); i++)
	{
		expCF.at(i)->Divide(simCF.at(i));
	}
	
	
	expCF = scaleToGeV(expCF);
	
	fitBS(expCF, fits);;
	
	char legName[20];
	TCanvas *cExpCF = new TCanvas("cExpCF","cExpCF",800,800);
	cExpCF->cd();
	expCF.at(0)->Draw();
	expCF.at(0)->SetLineColor(colors.at(0));
	expCF.at(0)->GetXaxis()->SetRangeUser(0,0.8);
	expCF.at(0)->GetYaxis()->SetRangeUser(0.6,1.4);
	expCF.at(0)->SetLineWidth(2);
	expCF.at(0)->SetMarkerStyle(8);
	expCF.at(0)->SetMarkerSize(0.7);
	expCF.at(0)->SetMarkerColor(colors.at(0));
	expCF.at(0)->SetNameTitle("","");
	fits.at(0)->SetLineColor(colors.at(0));
//	fits.at(0)->Draw("same");
		sprintf(legName, "nTracks#geq%d", 2);
	leg->AddEntry(expCF.at(0),legName,"lp");
	for(int i=1;i<=expFiles.size()-1;i++)
	{
		expCF.at(i)->SetLineColor(colors.at(i));
		expCF.at(i)->SetLineWidth(2);
		expCF.at(i)->SetMarkerStyle(8);
		expCF.at(i)->SetMarkerSize(0.7);
		expCF.at(i)->SetMarkerColor(colors.at(i));
		expCF.at(i)->Draw("same");
		fits.at(i)->SetLineColor(colors.at(i));
	//	fits.at(i)->Draw("same");
		sprintf(legName, "nTracks#geq%d", i+2);
		leg->AddEntry(expCF.at(i),legName,"lp");
	}
	
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
	leg->Draw();
	t->Draw();
	TLine *line = new TLine(0.02,1,0.8,1);
	line->SetLineColor(kAzure-3);
	line->SetLineStyle(9);
	line->Draw();
	
	
	
	TCanvas *cSimCF = new TCanvas("cSimCF","cSimCF",800,800);
	cSimCF->cd();
	simCF.at(0)->SetLineColor(colors.at(0));
	simCF.at(0)->Draw();
	polyFits.at(0)->SetLineColor(colors.at(0));
	polyFits.at(0)->Draw("same");
	legSim->AddEntry(simCF.at(0),simCF.at(0)->GetName(),"lp");
	for(int i=1;i<=expFiles.size()-1;i++)
	{
		simCF.at(i)->SetLineColor(colors.at(i));
		simCF.at(i)->Draw("same");
		polyFits.at(i)->SetLineColor(colors.at(i));
		polyFits.at(i)->Draw("same");
		legSim->AddEntry(simCF.at(i),simCF.at(i)->GetName(),"lp");
	}
	leg->Draw();
	
	
	
	
	
	TH1D *radii = new TH1D("radii","radii",5,1,6);
	radii->SetMarkerStyle(20);
	radii->SetMarkerColor(radii->GetLineColor());	
	
	TH1D *lambdas = new TH1D("lambdas","lambdas",5,1,6);
	lambdas->SetMarkerStyle(20);
	lambdas->SetMarkerColor(lambdas->GetLineColor());	
	
	
	for(int i=0; i<fits.size(); i++)
	{
		char CFName[20];
		sprintf(CFName, "nTracks#geq%d",i+2);
		radii->SetBinContent(i+1, fits.at(i)->GetParameter(1));
		radii->SetBinError(i+1, fits.at(i)->GetParError(1));
		radii->GetXaxis()->SetBinLabel(i+1, CFName);
		lambdas->SetBinContent(i+1, fits.at(i)->GetParameter(0));
		lambdas->SetBinError(i+1, fits.at(i)->GetParError(0));
		lambdas->GetXaxis()->SetBinLabel(i+1, CFName);
	}
	
	
	TCanvas *cRadii = new TCanvas("cRadii","cRadii",800,800);
	radii->Draw();
	radii->GetYaxis()->SetTitle("R (fm)");
	TCanvas *cLambdas = new TCanvas("cLambdas","cLambdas",800,800);
	lambdas->Draw();
	

	

	
	
	return 0;
}