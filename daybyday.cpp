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



int daybyday()
{
	gStyle->SetOptStat(0000);
	
	TFile *day32 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day32.root","read");
	TFile *day33 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day33.root","read");
	TFile *day34 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day34.root","read");
	TFile *day35 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day35.root","read");
	TFile *day36 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day36.root","read");
	TFile *day37 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day37.root","read");
	TFile *day38 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day38.root","read");
	TFile *day39 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day39.root","read");
	TFile *day40 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day40.root","read");
	TFile *day41 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day41.root","read");
	TFile *day42 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day42.root","read");
	TFile *day43 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day43.root","read");
	TFile *day44 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day44.root","read");
	TFile *day45 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day45.root","read");
	TFile *day46 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day46.root","read");
	TFile *day47 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day47.root","read");
	TFile *day48 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day48.root","read");
	TFile *day49 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day49.root","read");
	TFile *day50 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day50.root","read");
	TFile *day51 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day51.root","read");
	TFile *day52 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day52.root","read");
	TFile *day53 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day53.root","read");
	/*
	54
	55
	56
	57
	58
	************
	days 54-58 had no beam
	***********
	*/	
	
	TFile *day54 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day53.root","read");
	TFile *day55 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day53.root","read");
	TFile *day56 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day53.root","read");
	TFile *day57 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day53.root","read");
	TFile *day58 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day53.root","read");
	/*
	========
	========
	========
	*/
	
	
	TFile *day59 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day59.root","read");
	TFile *day60 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day60.root","read");
	TFile *day61 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day61.root","read");
	TFile *day62 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day62.root","read");
	TFile *day63 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day63.root","read");
	TFile *day64 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day64.root","read");
	TFile *day65 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day65.root","read");
	TFile *day66 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day66.root","read");
	
	
	

	
	vector<TFile *> files = {day32, day33, day34, day35, day36, day37, day38, day39, day40, day41, day42, day43, day44, day45, day46, day47, day48, day49, day50, day51, day52, day53, day54, day55, day56, day57, day58, day59, day60, day61, day62, day63, day64, day65, day66};
//	vector<TFile *> files = {UrQMD, UrQMD_noCut_noHash};
	vector<TH1D *> signals = {};
	vector<TH1D *> CFGeV = {};
	vector<TH1D *> backgrounds = {};
	vector<TH1D *> CF = {};
	vector<int> sigEntries = {};
//	vector<int> colors = {kBlue+1, kRed, kMagenta+1, kGreen+1, kCyan+2};
	vector<TF1*> fits = {};
	vector<TF1*> fitsExp = {};
	
	
	char SigName[20];
	char BckgName[20];
	char tmpSigName[20];
	char tmpBckgName[20];
	char CFName[20];
	char FitName[20];
	
	TCanvas *cCF = new TCanvas("cCF","cCF",1400,1000);
	TCanvas *cVertexXvsVertexY = new TCanvas("cVertexXvsVertexY","cVertexXvsVertexY",1400,1000);
	
	cCF->Divide(7,5);
	cVertexXvsVertexY->Divide(7,5);
	
	
	TPaveText *text = new TPaveText(0., 0., 1., 1.);
	text->AddText("No CF obtained");
	text->SetFillStyle(0);
	text->SetBorderSize(0);
	text->SetTextSize(0.08);
	text->SetTextFont(22);
	
	
	TPaveText *noBeam = new TPaveText(0., 0., 1., 1.);
	noBeam->AddText("No beam");
	noBeam->SetFillStyle(0);
	noBeam->SetBorderSize(0);
	noBeam->SetTextSize(0.08);
	noBeam->SetTextFont(22);
	
	
	
	
	for(int f=0; f<files.size(); f++)
	{
		sprintf(SigName, "day%dSig",f+32);
		sprintf(BckgName, "day%dBckg",f+32);
		sprintf(FitName, "day%d",f+32);
		
		fits.push_back(new TF1(FitName, coulombGausFit,0.02,0.45,3));
		
		
		fits.at(f)->SetParName(0, "lambda");
		fits.at(f)->SetParName(1, "R");
		fits.at(f)->SetParName(2, "norm");
		fits.at(f)->SetParameters(0.7,2,1,2);
		fits.at(f)->SetParLimits(0,0,1);
		fits.at(f)->SetParLimits(1,0.001,15);
		fits.at(f)->SetParLimits(2,0.01,10);
		fits.at(f)->SetParLimits(3,1,2);
		
		
		sprintf(FitName, "fitExpDay%d",f+32);
		fitsExp.push_back(new TF1(FitName, coulombExpFit,0.02,0.5,3));
		
		
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
		
		sprintf(CFName, "day%d",f+32);
		CFGeV.at(f)->SetNameTitle(CFName,CFName);
	//	CFGeV.at(f)->SetLineColor(colors.at(f));
	//	CFGeV.at(f)->SetMarkerColor(colors.at(f));
		CFGeV.at(f)->GetXaxis()->SetRangeUser(0,0.9);
	//	sprintf(CFName, "nTracks #geq %d",f+2);
	//	leg->AddEntry(CFGeV.at(f),CFName,"lp");
		
		cCF->cd(f+1);
		CFGeV.at(f)->GetYaxis()->SetRangeUser(0,2);
		if(f==0 || f==1)
		{
			cCF->cd(f+1);
			text->Draw();
			cVertexXvsVertexY->cd(f+1);
			TH2D *vertexYvsVertexX = (TH2D*)files.at(f)->Get("hVertexYvsVertexX");
			vertexYvsVertexX->GetXaxis()->SetRangeUser(-5,5);
			vertexYvsVertexX->GetYaxis()->SetRangeUser(-5,5);
			sprintf(CFName, "Day%d",f+32);
			vertexYvsVertexX->SetNameTitle(CFName,CFName);
			vertexYvsVertexX->Draw("colz");
			continue;
		}
		if(f>=23 && f<27)
		{
			cCF->cd(f+1);
			noBeam->Draw();
			cVertexXvsVertexY->cd(f+1);
			noBeam->Draw();
			continue;
		}
		
		CFGeV.at(f)->Draw();

		fits.at(f)->SetLineColor(kBlue);
	//	fits.at(f)->Draw("same");
		fitsExp.at(f)->SetLineColor(kRed);
	//	fitsExp.at(f)->Draw("same");
		
		cVertexXvsVertexY->cd(f+1);
		TH2D *vertexYvsVertexX = (TH2D*)files.at(f)->Get("hVertexYvsVertexX");
		vertexYvsVertexX->GetXaxis()->SetRangeUser(-5,5);
		vertexYvsVertexX->GetYaxis()->SetRangeUser(-5,5);
		sprintf(CFName, "Day%d",f+32);
		vertexYvsVertexX->SetNameTitle(CFName,CFName);
		vertexYvsVertexX->Draw("colz");
	}
	
	cCF->SaveAs("CFdaybyday.svg");
	cVertexXvsVertexY->SaveAs("vertexXYdaybyday.svg");
	
	return 0;
}