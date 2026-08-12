



int invmasspimp()
{
	
	TFile *f = new TFile("./jobs/invMassPimP_gt0.root","read");
	TFile *output = new TFile("./outputs/invMassPimpAnalysis_gt0.root", "recreate");
	
	
		
	char SigName[20];
	char BckgName[20];
	
	TH1D *sigExp = new TH1D("PimpSig","PimpSig",2000,1000,3000);
	TH1D *bckgExp = new TH1D("PimpBckg","PimpBckg",2000,1000,3000);
	
	
	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			
			
			TH1D* tempSigExp = (TH1D*)f->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f->Get(BckgName);
			if(tempSigExp)
			{
				sigExp->Add(tempSigExp);
				bckgExp->Add(tempBckgExp);
			}
		}
	}
	
	sigExp->Rebin(5);
	bckgExp->Rebin(5);
	
	sigExp->Sumw2();
	bckgExp->Sumw2();
	
	
	output->cd();
	sigExp->Write();
	bckgExp->Write();
	
	
	TH1D* copy = new TH1D(*sigExp);
	copy->Divide(bckgExp);
	
	copy->SetNameTitle("divided","divided");
	
	copy->Write();
	
	output->Close();
	
	
	return 0;
}