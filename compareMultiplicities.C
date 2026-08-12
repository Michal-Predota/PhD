
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


int compareMultiplicities()
{
	gStyle->SetOptStat(0000);
	
	
//	TFile *nTracksGT1 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_LCMS_HITS.root","read");
//	TFile *nTracksGT2 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT2_LCMS_HITS.root","read");
//	TFile *nTracksGT3 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT3_LCMS_HITS.root","read");
//	TFile *nTracksGT4 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT4_LCMS_HITS.root","read");
//	TFile *nTracksGT5 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_LCMS_HITS.root","read");
	
	
//	TFile *nTracksGT1 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_LCMS_HITS_DPhi4_DTheta2.root","read");
//	TFile *nTracksGT2 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT2_LCMS_HITS_DPhi4_DTheta2.root","read");
//	TFile *nTracksGT3 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT3_LCMS_HITS_DPhi4_DTheta2.root","read");
//	TFile *nTracksGT4 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT4_LCMS_HITS_DPhi4_DTheta2.root","read");
//	TFile *nTracksGT5 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_LCMS_HITS_DPhi4_DTheta2.root","read");

	
	
//	TFile *nTracksGT1 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_LCMS_TOPOLOGY.root","read");
//	TFile *nTracksGT2 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT2_TOPOLOGY_50k.root","read");
//	TFile *nTracksGT3 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT3_TOPOLOGY_50k.root","read");
//	TFile *nTracksGT4 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT4_TOPOLOGY_50k.root","read");
//	TFile *nTracksGT5 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_LCMS_TOPOLOGY.root","read");

	
//	TFile *nTracksGT1 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *nTracksGT2 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *nTracksGT3 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *nTracksGT4 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *nTracksGT5 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");



	TFile *nTracksGT1 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
	TFile *nTracksGT2 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
	TFile *nTracksGT3 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
	TFile *nTracksGT4 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
	TFile *nTracksGT5 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");


	
	
	vector<TFile *> files = {nTracksGT1, nTracksGT2, nTracksGT3, nTracksGT4, nTracksGT5};
//	vector<TFile *> files = {/*nTracksEQ2,*/ /*nTracksEQ3,*/ nTracksEQ4, nTracksEQ6, nTracksEQ8, nTracksEQ10/*, nTracksEQ12*/};
//	vector<TFile *> files = {UrQMD, UrQMD_noCut_noHash};
	vector<TH1D *> signals = {};
	vector<TH1D *> CFGeV = {};
	vector<TH1D *> backgrounds = {};
	vector<TH1D *> CF = {};
	vector<int> sigEntries = {};
	vector<int> colors = {kBlue+1, kRed, kMagenta+1, kGreen+1, kCyan+2, kYellow+3};
	vector<TF1*> fits = {};
	vector<TF1*> fitsExp = {};
	
	char SigName[20];
	char BckgName[20];
	char tmpSigName[20];
	char tmpBckgName[20];
	char CFName[20];
	char FitName[20];
	
	TCanvas *c = new TCanvas("c","c",800,800);
	TCanvas *cExp = new TCanvas("cExp","cExp",800,800);
	TCanvas *cSignals = new TCanvas("cSignals","cSignals",800,800);
	TCanvas *cBackgrounds = new TCanvas("cBackgrounds","cBackgrounds",800,800);
	TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
	TLegend *legExp = new TLegend(0.6,0.2,0.9,0.4);
	
	
	
	TH1D *lambdas = new TH1D("lambdas","lambdas",5,1,6);
	lambdas->SetMarkerStyle(20);
	lambdas->SetMarkerColor(lambdas->GetLineColor());
	
	TH1D *lambdasExp = new TH1D("lambdasExp","lambdasExp",5,1,6);
	lambdasExp->SetMarkerStyle(20);
	lambdasExp->SetMarkerColor(lambdasExp->GetLineColor());
	
	
	TH1D *radii = new TH1D("radii","radii",5,1,6);
	radii->SetMarkerStyle(20);
	radii->SetMarkerColor(radii->GetLineColor());
	
	TH1D *radiiExp = new TH1D("radiiExp","radiiExp",5,1,6);
	radiiExp->SetMarkerStyle(20);
	radiiExp->SetMarkerColor(radiiExp->GetLineColor());
	
	TH1D *sigStat = new TH1D("sigStat","sigStat",5,1,6);
	sigStat->SetMarkerStyle(20);
	sigStat->SetMarkerColor(sigStat->GetLineColor());
	
	TH1D *bckgStat = new TH1D("bckgStat","bckgStat",5,1,6);
	bckgStat->SetMarkerStyle(20);
	bckgStat->SetMarkerColor(bckgStat->GetLineColor());
	
	
	TPaveText *t = new TPaveText(.4,1.6,0.8,2.);
	t->AddText("p+p at #sqrt{s} = 3.46 GeV");
	t->AddText("HADES work in progress");
	t->SetBorderSize(0);
	t->SetFillStyle(0);
	
	
//	cout<<files.at(4)->GetName()<<endl;
	
	
	for(int f=0; f<files.size(); f++)
	{
		sprintf(SigName, "nTracksGT%dSig",f+1);
		sprintf(BckgName, "nTracksGT%dBckg",f+1);
		sprintf(FitName, "fitGausGT%d",f+1);
		
		fits.push_back(new TF1(FitName, coulombGausFit,0.02,0.3,3));
		
		
		fits.at(f)->SetParName(0, "lambda");
		fits.at(f)->SetParName(1, "R");
		fits.at(f)->SetParName(2, "norm");
		fits.at(f)->SetParameters(0.7,2,1,2);
		fits.at(f)->SetParLimits(0,0,1);
		fits.at(f)->SetParLimits(1,0.001,15);
		fits.at(f)->SetParLimits(2,0.01,10);
		fits.at(f)->SetParLimits(3,1,2);
		
		
		sprintf(FitName, "fitExpGT%d",f+1);
		fitsExp.push_back(new TF1(FitName, coulombExpFit,0.05,0.5,3));
		
		
		fitsExp.at(f)->SetParName(0, "lambda");
		fitsExp.at(f)->SetParName(1, "R");
		fitsExp.at(f)->SetParName(2, "norm");
		fitsExp.at(f)->SetParameters(0.7,2,1,2);
		fitsExp.at(f)->SetParLimits(0,0,1);
		fitsExp.at(f)->SetParLimits(1,0.001,15);
		fitsExp.at(f)->SetParLimits(2,0.01,10);
		fitsExp.at(f)->SetParLimits(3,1,2);
		
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
		sigEntries.push_back(signals.at(f)->GetEntries());
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
		
		
		CFGeV.push_back(new TH1D("expCFGeV","expCFGeV",CF.at(f)->GetNbinsX(),0,CF.at(f)->GetXaxis()->GetXmax()/1000));	
		CFGeV.at(f)->GetXaxis()->SetTitle("q_{inv} (GeV/c)");
		CFGeV.at(f)->GetYaxis()->SetTitle("CF");	
		for(int i=1;i<=CFGeV.at(f)->GetNbinsX();i++)
		{
			CFGeV.at(f)->SetBinContent(i,CF.at(f)->GetBinContent(i));
			CFGeV.at(f)->SetBinError(i,CF.at(f)->GetBinError(i));
		}
		
		
		CFGeV.at(f)->Fit(fits.at(f), "REM0");
		CFGeV.at(f)->Fit(fitsExp.at(f), "REM0");
		
		sprintf(CFName, "CF_nTracksGT%d",f+1);
		//sprintf(CFName, "nTracks = %d",2*f+2);
		if(f==1)sprintf(CFName, "nTracks = 3");
		
		CFGeV.at(f)->SetNameTitle(CFName,CFName);
		CFGeV.at(f)->SetLineColor(colors.at(f));
		CFGeV.at(f)->SetMarkerColor(colors.at(f));
		CFGeV.at(f)->GetXaxis()->SetRangeUser(0,400);
		CFGeV.at(f)->SetLineWidth(2);
		CFGeV.at(f)->SetMarkerStyle(8);
		CFGeV.at(f)->SetMarkerSize(0.7);
		CFGeV.at(f)->SetMarkerColor(colors.at(f));
		sprintf(CFName, "nTracks #geq %d",f+2);
		//sprintf(CFName, "nTracks = %d",2*f+2);
		leg->AddEntry(CFGeV.at(f),CFName,"lp");
		
		lambdas->SetBinContent(f+1, fits.at(f)->GetParameter(0));
		lambdas->SetBinError(f+1, fits.at(f)->GetParError(0));
		radii->SetBinContent(f+1, fits.at(f)->GetParameter(1));
		radii->SetBinError(f+1, fits.at(f)->GetParError(1));
		
		lambdas->GetXaxis()->SetBinLabel(f+1, CFName);
		radii->GetXaxis()->SetBinLabel(f+1, CFName);
		
		lambdasExp->SetBinContent(f+1, fitsExp.at(f)->GetParameter(0));
		lambdasExp->SetBinError(f+1, fitsExp.at(f)->GetParError(0));
		radiiExp->SetBinContent(f+1, fitsExp.at(f)->GetParameter(1));
		radiiExp->SetBinError(f+1, fitsExp.at(f)->GetParError(1));
		
		lambdasExp->GetXaxis()->SetBinLabel(f+1, CFName);
		radiiExp->GetXaxis()->SetBinLabel(f+1, CFName);
		
		sigStat->SetBinContent(f+1, signals.at(f)->GetEntries());
		bckgStat->SetBinContent(f+1, backgrounds.at(f)->GetEntries());
		
		sigStat->GetXaxis()->SetBinLabel(f+1, CFName);
		bckgStat->GetXaxis()->SetBinLabel(f+1, CFName);
		
		if(f==0)
		{
			c->cd();
			CFGeV.at(f)->GetYaxis()->SetRangeUser(0,2);
			CFGeV.at(f)->GetXaxis()->SetRangeUser(0,0.8);
			CFGeV.at(f)->SetNameTitle("","");
			CFGeV.at(f)->Draw();
			//cout<<CF.at(f)->GetTitle()<<endl;
			cExp->cd();
			CFGeV.at(f)->GetYaxis()->SetRangeUser(0,2);
			CFGeV.at(f)->GetXaxis()->SetRangeUser(0,0.8);
			CFGeV.at(f)->Draw();
			cSignals->cd();
			signals.at(f)->Scale(1/signals.at(f)->Integral());
			signals.at(f)->SetLineColor(colors.at(f));
			signals.at(f)->SetLineWidth(2);
			signals.at(f)->SetMarkerStyle(8);
			signals.at(f)->SetMarkerSize(0.7);
			signals.at(f)->SetMarkerColor(colors.at(f));
			signals.at(f)->Draw();
			cBackgrounds->cd();
			backgrounds.at(f)->Scale(1/backgrounds.at(f)->Integral());
			backgrounds.at(f)->SetLineColor(colors.at(f));
			backgrounds.at(f)->Draw();
		}
		else
		{
			c->cd();
			CFGeV.at(f)->Draw("same");
			cExp->cd();
			CFGeV.at(f)->Draw("same");
			cSignals->cd();
			signals.at(f)->Scale(1/signals.at(f)->Integral());
			signals.at(f)->SetLineColor(colors.at(f));
			signals.at(f)->Draw("same");
			cBackgrounds->cd();
			backgrounds.at(f)->Scale(1/backgrounds.at(f)->Integral());
			backgrounds.at(f)->SetLineColor(colors.at(f));
			backgrounds.at(f)->Draw("same");
		}
		c->cd();
		fits.at(f)->SetLineColor(colors.at(f));
	//	fits.at(f)->Draw("same");
		cExp->cd();
		fitsExp.at(f)->SetLineColor(colors.at(f));
	//	fitsExp.at(f)->Draw("same");
	}
	
	
	
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
	
	
	c->cd();
	leg->Draw();
	t->Draw();
	TLine *line = new TLine(0.02,1,0.8,1);
	line->SetLineColor(kAzure-3);
	line->SetLineStyle(9);
	line->Draw();
	
	cExp->cd();
	leg->Draw();
	t->Draw();
	
	cExp->cd();
	leg->Draw();
	t->Draw();
	
	cSignals->cd();
	leg->Draw();
	t->Draw();
	
	
	
	for(int f=0; f<files.size(); f++)
	{
		cout<<CFGeV.at(f)->GetName()<<endl;
	//	TH1D* evtCnt = (TH1D*)files.at(f)->Get("allEvtCnt");
	//	cout<<"events: "<<evtCnt->GetEntries()<<endl;
		cout<<"sig entries: "<<sigEntries.at(f)<<endl;
		cout<<"bckg entries: "<<backgrounds.at(f)->GetEntries()<<endl;
	}
	
	
	
	TLine *lowLine = new TLine(300,0.95,300,1.05);
	lowLine->SetLineWidth(2);
	//lowLine->SetLineColor(k);
	lowLine->Draw();
	TLine *highLine = new TLine(350,0.95,350,1.05);
	highLine->SetLineWidth(2);
	highLine->Draw();
	
	TCanvas *cRadii = new TCanvas("cRadii","cRadii",800,800);
	radii->Draw();
	radii->GetYaxis()->SetTitle("R (fm)");
	TCanvas *cLambdas = new TCanvas("cLambdas","cLambdas",800,800);
	lambdas->Draw();
	
	TCanvas *cRadiiExp = new TCanvas("cRadiiExp","cRadiiExp",800,800);
	radiiExp->Draw();
	radiiExp->GetYaxis()->SetTitle("R (fm)");
	TCanvas *cLambdasExp = new TCanvas("cLambdasExp","cLambdasExp",800,800);
	lambdasExp->Draw();
	
	TCanvas *cSigStat = new TCanvas("cSigStat","cSigStat",800,800);
	sigStat->Draw();
	TCanvas *cBckgStat = new TCanvas("cBckgStat","cBckgStat",800,800);
	bckgStat->Draw();
	
	
	
	return 0;
}