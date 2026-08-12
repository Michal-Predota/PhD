
double linearFit(const double *x, const double *pars)
{
	return pars[0]*x[0]+pars[1];//pars[0]-slope, pars[1]-b
}




int calcSlope()
{
	
	TFile *KineSmashNoCutNoHash = new TFile("./jobs/smash/analysisPureKinePim_noCut_noHash.root","read");
	TFile *UrQMDNoCutNoHash = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_noHash.root","read");
	
	
	/*****************SMASH******************/
	
	TH1D *sigSmash = new TH1D("pim_Signal_SMASH","pim_Signal_SMASH",1500,0,1500);
	TH1D *bckgSmash = new TH1D("pim_Background_SMASH","pim_Background_SMASH",1500,0,1500);
	
	
	char SigName[20];
	char BckgName[20];
	
	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			TH1D* tempSig = (TH1D*)KineSmashNoCutNoHash->Get(SigName);
			TH1D* tempBckg = (TH1D*)KineSmashNoCutNoHash->Get(BckgName);
			
			if(tempSig)
			{
				sigSmash->Add(tempSig);
				bckgSmash->Add(tempBckg);
				
				delete tempSig;
				delete tempBckg;
			}
		}
	}
	
	
	sigSmash->Rebin(5);
	bckgSmash->Rebin(5);
	sigSmash->Sumw2(true);
	bckgSmash->Sumw2(true);
	
	
	
	/**************UrQMD************/
	
	TH1D *sigUrQMD = new TH1D("pim_Signal_UrQMD","pim_Signal_UrQMD",1500,0,1500);
	TH1D *bckgUrQMD = new TH1D("pim_Background_UrQMD","pim_Background_UrQMD",1500,0,1500);
	
	
	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			TH1D* tempSig = (TH1D*)UrQMDNoCutNoHash->Get(SigName);
			TH1D* tempBckg = (TH1D*)UrQMDNoCutNoHash->Get(BckgName);
			
			if(tempSig)
			{
				sigUrQMD->Add(tempSig);
				bckgUrQMD->Add(tempBckg);
				
				delete tempSig;
				delete tempBckg;
			}
		}
	}
	
	
	sigUrQMD->Rebin(5);
	bckgUrQMD->Rebin(5);
	sigUrQMD->Sumw2(true);
	bckgUrQMD->Sumw2(true);
	
	
	sigSmash->Divide(bckgSmash);
	sigUrQMD->Divide(bckgUrQMD);
	
	
	TF1 *linFitSMASH = new TF1("linFitSMASH",linearFit,0,150,2);
	TF1 *linFitUrQMD = new TF1("linFitUrQMD",linearFit,0,150,2);
	
	sigSmash->Scale(1/sigSmash->Integral());
	sigUrQMD->Scale(1/sigUrQMD->Integral());
	
	
	sigSmash->Fit(linFitSMASH, "rem0");
	sigUrQMD->Fit(linFitUrQMD, "rem0");
	
	TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
	TCanvas *c1 = new TCanvas("c1","c1");
	gStyle->SetOptStat(0000);
	sigSmash->SetNameTitle("","");
	sigSmash->GetXaxis()->SetRangeUser(0,400);
	linFitSMASH->SetLineColor(sigSmash->GetLineColor());
	sigSmash->Draw();
	linFitSMASH->Draw("same");
	sigUrQMD->GetXaxis()->SetRangeUser(0,400);
	sigUrQMD->SetLineColor(kRed);
	linFitUrQMD->SetLineColor(sigUrQMD->GetLineColor());
	sigUrQMD->Draw("same");
	linFitUrQMD->Draw("same");
	leg->AddEntry(sigSmash, "pure smash", "lp");
	leg->AddEntry(sigUrQMD, "pure UrQMD", "lp");
	leg->Draw();
	
	return 0;
}