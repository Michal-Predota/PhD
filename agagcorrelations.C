
using namespace std;

int agagcorrelations()
{
	
	gStyle->SetOptStat(0000);
	
	TFile *f = new TFile("./jobs/agag_analysis.root","read");
	
	char SigName[20];
	char BckgName[20];

	TH1D *sigExp = new TH1D("PimSignal AgAg","PimSignal AgAg",1500,0,1500);
	TH1D *bckgExp = new TH1D("PimBackground AgAg","PimBackground AgAg",1500,0,1500);

	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			TH1D* tempSigAgAg = (TH1D*)f->Get(SigName);
			TH1D* tempBckgAgAg = (TH1D*)f->Get(BckgName);
			
			if(tempSigAgAg)
			{
				sigExp->Add(tempSigAgAg);
				bckgExp->Add(tempBckgAgAg);
				
				delete tempSigAgAg;
				delete tempBckgAgAg;
			}
		}
	}
	
	
	sigExp->Rebin(5);
	bckgExp->Rebin(5);
	
	sigExp->Sumw2(true);
	bckgExp->Sumw2(true);
	
	
	cout<<"sigExp "<<sigExp->GetEntries()<<" "<<sigExp->Integral()<<endl;
	cout<<"bckgExp "<<bckgExp->GetEntries()<<" "<<bckgExp->Integral()<<endl;
	
	double numint_div_denint = (double)bckgExp->Integral()/sigExp->Integral();
	
	cout<<"podzielone exp "<<numint_div_denint<<endl;
	
	
	TH1D* ExpNom = new TH1D(*sigExp);
	ExpNom->SetNameTitle("expNom","expNom");
	bckgExp->SetNameTitle("expDen","expDen");
//	ExpNom->Write();
//	bckgExp->Write();
	
	
	
	
	sigExp->Divide(bckgExp);
	sigExp->Scale(numint_div_denint, "nosw2");
	sigExp->SetNameTitle("Exp agag", "Exp agag");
	sigExp->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	sigExp->GetYaxis()->SetTitle("CF_{exp} Ag+Ag");
	sigExp->SetMarkerStyle(20);
	sigExp->SetMarkerColor(sigExp->GetLineColor());
	sigExp->SetMarkerSize(0.5);
	
	
	int cnt=0;
	double average=0;
	for(int i=sigExp->FindBin(100); i<=sigExp->FindBin(150); i++)
	{
		cnt++;
		average+=sigExp->GetBinContent(i);
	}
	average/=cnt;
	cout<<"srednia "<<average<<endl;

	sigExp->Scale(1/average);

	
	
	sigExp->Draw();

	return 0;
}