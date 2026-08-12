
using namespace std;

int divide()
{
	
	gStyle->SetOptStat(0000);
	
	TFile *f = new TFile("./jobs/UrQMD_analysis4.5GeV_weights.root","read");
	TFile *f1 = new TFile("./jobs/analysis_nocut_50k.root","read");
	TFile *output = new TFile("./outputs/expUrQMDanalysisPim4.5GeV_weights.root", "recreate");
	
	char SigName[20];
	char BckgName[20];
	
	TH1D *sigUrQMD = new TH1D("Pim_Signal_UrQMD","Pim_Signal_UrQMD",1500,0,1500);
	TH1D *bckgUrQMD = new TH1D("Pim_Background_UrQMD","Pim_Background_UrQMD",1500,0,1500);
	
	TH1D *sigExp = new TH1D("Pim_Signal_PP","Pim_Signal_PP",1500,0,1500);
	TH1D *bckgExp = new TH1D("Pim_Background_PP","Pim_Background_PP",1500,0,1500);
	
	
	
	TH2D *ptyPimExp = (TH2D*)f1->Get("pTyPim");
	TH2D *ptyPimUrQMD = (TH2D*)f->Get("hpTyPim");
	
	TH1D *evtCntExp = (TH1D*)f1->Get("evtCnt");
	TH1D *evtCntUrQMD = (TH1D*)f->Get("eventCounter");
	
	
	for(int i=0; i<=ptyPimExp->GetNbinsX(); i++)
	{
		for(int j=0; j<=ptyPimExp->GetNbinsY(); j++)
		{
			if(ptyPimExp->GetBinContent(i,j)/ptyPimExp->GetEntries()<0.000001)
			{
				ptyPimExp->SetBinContent(i,j,0);
			}
		}
	}
	
	
	
	ptyPimUrQMD->Scale(1/evtCntExp->GetEntries());
	ptyPimExp->Scale(1/evtCntUrQMD->GetEntries());
	
	
	
	TH2D *ptyPimExpCopy = new TH2D(*ptyPimExp);
	
	ptyPimExp->Divide(ptyPimUrQMD);
	
	ptyPimExp->Scale(1/ptyPimExp->GetMaximum());
	

//	ptyPimExp->SetNameTitle("PimWeights","PimWeights");
//	TFile *weights = new TFile("weights.root","recreate");
//	weights->cd();
//	ptyPimExpCopy->Write();
//	ptyPimUrQMD->Write();
//	ptyPimExp->Write();
//	weights->Save();
//	weights->Close();
	
	
		
	TCanvas canvas("canvas");
	canvas.Print("./divided 4.5GeV.pdf["); 
	
	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			sprintf(SigName, "PimSig_%d%d",i,j);
			sprintf(BckgName, "PimBckg_%d%d",i,j);
			
			
			TH1D* tempSigUrQMD = (TH1D*)f->Get(SigName);
			TH1D* tempBckgUrQMD = (TH1D*)f->Get(BckgName);
			
			
			TH1D* tempSigExp = (TH1D*)f1->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f1->Get(BckgName);
			
			
			
			if(tempSigExp && tempSigUrQMD)
			{
			//	tempSigUrQMD->Rebin(5);
			//	tempBckgUrQMD->Rebin(5);
				//signal
				canvas.cd();
				canvas.Clear();
			//	tempSigPP->SetNameTitle("PimSig","PimSig");
			//	tempSigPP->GetYaxis()->SetRangeUser(0, 1.1*tempSigAgAg->GetMaximum());
				tempSigUrQMD->SetNameTitle(SigName,SigName);
				tempSigUrQMD->Draw();
				tempSigExp->SetLineColor(kRed);
				tempSigExp->Scale(tempSigUrQMD->Integral()/tempSigExp->Integral());
				tempSigExp->Draw("samehist");
				
				
				TLegend *legendSig = new TLegend(0.9,0.9,0.65,0.75);
				legendSig->AddEntry(tempSigUrQMD,"sig UrQMD", "l");
				legendSig->AddEntry(tempSigExp,"sig Exp", "l");
				legendSig->Draw();
				canvas.Print("./divided 4.5GeV.pdf"); 
				
				
				//background
				canvas.cd();
				canvas.Clear();
				tempBckgExp->SetNameTitle("PimBckg","PimBckg");
				//tempBckgExp->GetYaxis()->SetRangeUser(0, 1.1*tempBckgExp->GetMaximum());
				//tempBckgExp->SetNameTitle(BckgName,BckgName);
				tempBckgUrQMD->SetNameTitle(BckgName,BckgName);
				tempBckgUrQMD->Draw();
				tempBckgExp->SetLineColor(kRed);
				tempBckgExp->Scale(tempBckgUrQMD->Integral()/tempBckgExp->Integral());
				tempBckgExp->Draw("samehist");
				
				
				TLegend *legendBckg = new TLegend(0.9,0.9,0.65,0.75);
				legendBckg->AddEntry(tempBckgUrQMD,"bckg pp", "l");
				legendBckg->AddEntry(tempBckgExp,"bckg AgAg", "l");
				legendBckg->Draw();
				canvas.Print("./divided 4.5GeV.pdf"); 
				
				
				
				sigUrQMD->Add(tempSigUrQMD);
				bckgUrQMD->Add(tempBckgUrQMD);
				
				
				delete tempSigUrQMD;
				delete tempBckgUrQMD;
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
			
			TH1D* tempSigExp = (TH1D*)f1->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f1->Get(BckgName);
			
			if(tempSigExp)
			{
				sigExp->Add(tempSigExp);
				bckgExp->Add(tempBckgExp);
				
				delete tempSigExp;
				delete tempBckgExp;
			}
		}
	}
	
	
	
	sigExp->Rebin(5);
	bckgExp->Rebin(5);
	sigUrQMD->Rebin(5);
	bckgUrQMD->Rebin(5);	
	
	sigExp->Sumw2(true);
	bckgExp->Sumw2(true);
	sigUrQMD->Sumw2(true);
	bckgUrQMD->Sumw2(true);
	
	
	cout<<"exp "<<sigExp->GetEntries()<<" "<<bckgExp->GetEntries()<<endl;
	cout<<"UrQMD "<<sigUrQMD->GetEntries()<<" "<<bckgUrQMD->GetEntries()<<endl;
	
	canvas.cd();
	canvas.Clear();
	
	double numint_div_denint_urqmd = (double)bckgUrQMD->Integral()/sigUrQMD->Integral();
	
	cout<<"podzielone UrQMD "<<numint_div_denint_urqmd<<endl;
	
	
	
		
	TH1D *sigUrQMDCopy = new TH1D(*sigUrQMD);
	sigUrQMDCopy->SetNameTitle("UrQMD_nom","UrQMD_nom");
	bckgUrQMD->SetNameTitle("UrQMD_den","UrQMD_den");
	sigUrQMDCopy->Write();
	bckgUrQMD->Write();
	
	
	
	
	
	cout<<"sigUrQMD "<<sigUrQMD->GetEntries()<<" "<<sigUrQMD->Integral()<<endl;
	cout<<"bckgUrQMD "<<bckgUrQMD->GetEntries()<<" "<<bckgUrQMD->Integral()<<endl;
	

	sigUrQMD->Divide(bckgUrQMD);
	sigUrQMD->Scale(numint_div_denint_urqmd, "");
	sigUrQMD->SetNameTitle("UrQMD", "UrQMD");
	sigUrQMD->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	sigUrQMD->GetYaxis()->SetTitle("CF");
	sigUrQMD->DrawCopy();
	canvas.Print("./divided 4.5GeV.pdf"); 
	
	bckgUrQMD->Draw();
	
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
	canvas.Print("./divided 4.5GeV.pdf"); 




	//sigExp->Sumw2();
	//sigUrQMD->Sumw2();


	TH1D* CopyExp = new TH1D(*sigExp);
	CopyExp->SetNameTitle("expCF","expCF");

	cout<<sigExp->GetNbinsX()<<" "<<sigUrQMD->GetNbinsX()<<endl;

	sigExp->Divide(sigUrQMD);
	//sigExp->Scale(2);/**********				Czemu trzeba przeskalować przez 2????				******************/
						/************ 			skalowanie przez 1/average rozwiązuje chyba problem			 ********************/



	output->cd();
	
	
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
	sigExp->SetNameTitle("doubleRatio","doubleRatio");
	sigExp->GetXaxis()->SetTitle("q_{inv} (MeV)");
	sigExp->GetYaxis()->SetTitle("CF_{exp}/CF_{UrQMD}");


	sigExp->Write();
	CopyExp->Write();
	sigUrQMD->Write();
	
	output->Save();





	canvas.Print("./divided 4.5GeV.pdf]"); 

/*

	TFile *output = new TFile("expUrQMDanalysis4.5GeV.root", "recreate");
	output->cd();
	sigExp->Write();
	sigUrQMD->Write();
	TH1D* sigExpCopy = new TH1D(*sigExp);
	sigExpCopy->Add(sigUrQMD, -1);
	sigExpCopy->SetNameTitle("subtracted","subtracted");
	sigExpCopy->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	sigExpCopy->GetYaxis()->SetTitle("CF_{Exp}-CF_{UrQMD}");
	sigExpCopy->Write();




	canvas.cd();
	canvas.Clear();
	
	

	
	sigUrQMD->Scale(sigExp->Integral()/sigUrQMD->Integral());
	sigExp->Divide(sigUrQMD);
	sigExp->SetNameTitle("divided", "divided");
	sigExp->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	sigExp->GetYaxis()->SetTitle("CF_{Exp}/CF_{UrQMD}");
	//sigExp->GetXaxis()->SetRangeUser(0,100);
	sigExp->Draw();
	sigExp->Write();
	canvas.Print("./divided 4.5GeV.pdf"); 

	
	
	output->Save();
	
	TCanvas *c = new TCanvas("c","c",800,800);
	c->SetLeftMargin(0.15);
	bckgUrQMD->Draw();
	c->SaveAs("./obrazki/divided.png");
	*/
	
	

	return 0;
}