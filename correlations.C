
using namespace std;

int correlations()
{
	
	gStyle->SetOptStat(0000);
	
	TFile *f = new TFile("UrQMD_analysis30GeV.root","read");
	TFile *f1 = new TFile("agagjobtest.root","read");
	
	char SigName[20];
	char BckgName[20];
	
	TH1D *sigPP = new TH1D("PimSignal pp","PimSignal pp",300,0,1500);
	TH1D *bckgPP = new TH1D("PimBackground pp","PimBackground pp",300,0,1500);
	
	TH1D *sigAgAg = new TH1D("PimSignal AgAg","PimSignal AgAg",300,0,1500);
	TH1D *bckgAgAg = new TH1D("PimBackground AgAg","PimBackground AgAg",300,0,1500);
	
	TCanvas canvas("canvas");
	canvas.Print("./UrQMD correlations 30GeV.pdf["); 
	
	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			
			TH1D* tempSigPP = (TH1D*)f->Get(SigName);
			TH1D* tempBckgPP = (TH1D*)f->Get(BckgName);
			
			TH1D* tempSigAgAg = (TH1D*)f1->Get(SigName);
			TH1D* tempBckgAgAg = (TH1D*)f1->Get(BckgName);
			
			
			
			if(tempSigPP)
			{
				
				//signal
				canvas.cd();
				canvas.Clear();
			//	tempSigPP->SetNameTitle("PimSig","PimSig");
			//	tempSigPP->GetYaxis()->SetRangeUser(0, 1.1*tempSigAgAg->GetMaximum());
				tempSigPP->Draw();
				tempSigAgAg->SetLineColor(kRed);
				tempSigAgAg->Scale(tempSigPP->Integral()/tempSigAgAg->Integral());
			//	tempSigAgAg->Draw("samehist");
				
				
				TLegend *legendSig = new TLegend(0.9,0.9,0.65,0.75);
				legendSig->AddEntry(tempSigPP,"sig pp", "l");
				legendSig->AddEntry(tempSigAgAg,"sig AgAg", "l");
			//	legendSig->Draw();
				canvas.Print("./UrQMD correlations 30GeV.pdf"); 
				
				
				//background
				canvas.cd();
				canvas.Clear();
			//	tempBckgPP->SetNameTitle("PimBckg","PimBckg");
			//	tempBckgPP->GetYaxis()->SetRangeUser(0, 1.1*tempBckgAgAg->GetMaximum());
				tempBckgPP->Draw();
				tempBckgAgAg->SetLineColor(kRed);
				tempBckgAgAg->Scale(tempBckgPP->Integral()/tempBckgAgAg->Integral());
			//	tempBckgAgAg->Draw("samehist");
				
				
				TLegend *legendBckg = new TLegend(0.9,0.9,0.65,0.75);
				legendBckg->AddEntry(tempBckgPP,"bckg pp", "l");
				legendBckg->AddEntry(tempBckgAgAg,"bckg AgAg", "l");
			//	legendBckg->Draw();
				canvas.Print("./UrQMD correlations 30GeV.pdf"); 
				
				
				
				sigPP->Add(tempSigPP);
				bckgPP->Add(tempBckgPP);
				
				
				delete tempSigPP;
				delete tempBckgPP;
				delete tempSigAgAg;
				delete tempBckgAgAg;
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
			
			TH1D* tempSigAgAg = (TH1D*)f1->Get(SigName);
			TH1D* tempBckgAgAg = (TH1D*)f1->Get(BckgName);
			
			if(tempSigAgAg)
			{
				sigAgAg->Add(tempSigAgAg);
				bckgAgAg->Add(tempBckgAgAg);
				
				delete tempSigAgAg;
				delete tempBckgAgAg;
			}
		}
	}
	
	canvas.cd();
	canvas.Clear();
	sigPP->SetNameTitle("sig pp/sig AgAg ","sig pp/sig AgAg");
//	sigPP->GetYaxis()->SetRangeUser(0, 1.1*sigAgAg->GetMaximum());
	sigPP->Divide(sigAgAg);
	sigPP->DrawCopy();
//	sigAgAg->SetNameTitle("Total PimSig AgAg","Total PimSig");
//	sigAgAg->Scale(sigPP->Integral()/sigAgAg->Integral());
//	sigAgAg->SetLineColor(kRed);
//	sigAgAg->DrawCopy("samehist");
//	TLegend *legendSig = new TLegend(0.9,0.9,0.65,0.75);
//	legendSig->AddEntry(sigPP,"signal pp", "l");
//	legendSig->AddEntry(sigAgAg,"signal AgAg", "l");
//	legendSig->Draw();
//	canvas.Print("./UrQMD correlations.pdf"); 
	
	
	canvas.cd();
	canvas.Clear();
	bckgPP->SetNameTitle("bckg pp/bckg AgAg","bckg pp/bckg AgAg");
//	bckgPP->GetYaxis()->SetRangeUser(0, 1.1*bckgAgAg->GetMaximum());	
	bckgPP->Divide(bckgAgAg);
	bckgPP->Draw();
//	bckgAgAg->SetNameTitle("Total PimBckg AgAg","Total PimBckg");
//	bckgAgAg->Scale(bckgPP->Integral()/bckgAgAg->Integral());
//	bckgAgAg->SetLineColor(kRed);
//	bckgAgAg->Draw("samehist");
//	TLegend *legendBckg = new TLegend(0.9,0.9,0.65,0.75);
//	legendBckg->AddEntry(bckgPP,"background pp", "l");
//	legendBckg->AddEntry(bckgAgAg,"background AgAg", "l");
//	legendBckg->Draw();
//	canvas.Print("./UrQMD correlations.pdf"); 
	

	sigPP->Divide(bckgPP);
	sigAgAg->Divide(bckgAgAg);

	
	canvas.cd();
	canvas.Clear();
	sigPP->SetNameTitle("divided total pp","divided pim UrQMD	");
//	sigPP->GetYaxis()->SetRangeUser(0, 1.1*sigAgAg->GetMaximum());
	sigPP->DrawCopy();
	sigAgAg->SetNameTitle("divided total AgAg","divided total PimBckg");
/*	sigAgAg->Scale(sigPP->Integral()/sigAgAg->Integral());
	sigAgAg->SetLineColor(kRed);
	sigAgAg->Draw("samehist");
	TLegend *legenddiv = new TLegend(0.9,0.9,0.65,0.75);
	legenddiv->AddEntry(sigPP,"divided pp", "l");
	legenddiv->AddEntry(sigAgAg,"divided AgAg", "l");
	legenddiv->Draw();*/
	canvas.Print("./UrQMD correlations 30GeV.pdf"); 

	
	canvas.Print("./UrQMD correlations 30GeV.pdf]"); 
	

	return 0;
}