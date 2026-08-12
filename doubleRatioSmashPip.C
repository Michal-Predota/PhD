

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
	return TMath::Sqrt(DpolyDa(x)*sa*sa+DpolyDb(x)*sb*sb+DpolyDc(x)*sc*sc*DpolyDd(x)*sd*sd+DpolyDe(x)*se*se+DpolyDf(x)*sf*sf);
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



int doubleRatioSmashPip()
{
	
	gStyle->SetOptStat(0000);
	
	TFile *f = new TFile("./jobs/analysisSmashPip_gt1.root","read");
	TFile *f1 = new TFile("./jobs/analysis_pip_nocut_50k_gt1.root","read");
	TFile *output = new TFile("./outputs/SMASHratioPip_gt1.root", "recreate");
	
	char SigName[20];
	char BckgName[20];
	
	TH1D *sigSMASH = new TH1D("Pip_Signal_SMASH","Pip_Signal_SMASH",1500,0,1500);
	TH1D *bckgSMASH = new TH1D("Pip_Background_SMASH","Pip_Background_SMASH",1500,0,1500);
	
	TH1D *sigExp = new TH1D("Pip_Signal_PP","Pip_Signal_PP",1500,0,1500);
	TH1D *bckgExp = new TH1D("Pip_Background_PP","Pip_Background_PP",1500,0,1500);
	
	
		
	TCanvas canvas("canvas");
	
	for(int i=1; i<10; i++)
	{
		for(int j=1; j<10; j++)
		{
			sprintf(SigName, "PipSig_%d%d",i,j);
			sprintf(BckgName, "PipBckg_%d%d",i,j);
			
			
			TH1D* tempsigSMASH = (TH1D*)f->Get(SigName);
			TH1D* tempbckgSMASH = (TH1D*)f->Get(BckgName);
			
			
			TH1D* tempSigExp = (TH1D*)f1->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f1->Get(BckgName);
			
			
			
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
			sprintf(SigName, "PipSig_%d%d",i,j);
			sprintf(BckgName, "PipBckg_%d%d",i,j);
			
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
//	sigSMASH->Rebin(5);
//	bckgSMASH->Rebin(5);	
	
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


	int max=200;

	TF1* MyTanH = new TF1("MyTanH", "[0]*TMath::TanH([1]*x)", 0, max);
	TF1* MyPoly = new TF1("MyPoly","[0]+[1]*x+[2]*x^2+[3]*x^3+[4]*x^4+[5]*x^5+[6]*x^6",0,max);
	TF1* MyLog = new TF1("MyPoly","[0]*TMath::Log([1]*x)",0,max);
	
	TF1* MySigmoid = new TF1("MySigmoid","[0]*e^([1]*x)/(1+e^([1]*x))",0,max);

	sigSMASH->Fit(MyPoly, "REMN");

 
	TCanvas *c = new TCanvas("c","c",800,800);
	//sigSMASH->Draw();
	//MyTanH->Draw("same");

	sigExp->Divide(sigSMASH);


	sigSMASH->GetXaxis()->SetRangeUser(0,max);
	sigSMASH->Draw();
	
	const double *fErr = MySigmoid->GetParErrors();
	const double *fPar = MySigmoid->GetParameters();
	/*
	for(int i=1;i<=sigExp->GetNbinsX();i++)
	{
		if(sigExp->GetBinLowEdge(i)<max)
		{
			//cout<<sigExp->GetBinContent(i)<<" "<<MyPoly->Eval(sigExp->GetBinCenter(i))<<endl;
			sigExp->SetBinContent(i, sigExp->GetBinContent(i)/MyPoly->Eval(sigExp->GetBinCenter(i)));
			
			double valueH = sigExp->GetBinContent(i);
			double errorH = sigExp->GetBinError(i);
			
			double x = sigExp->GetBinCenter(i);
			
			double valueF = MySigmoid->Eval(x);
			double errorF = ErrorPropagationSigmoid(x, fPar[0], fPar[1], fErr[0], fErr[1]);
			
			
			double error = TMath::Sqrt((errorH*errorH)/(valueF*valueF) + ((valueH*valueH)*(errorF*errorF))/(valueF*valueF*valueF*valueF) - (2*valueH*errorH*errorF)/(valueF*valueF*valueF));
		//	cout<<error<<endl;
			sigExp->SetBinError(i, 0);
		}
		else
		{
			sigExp->SetBinContent(i,0);
			sigExp->SetBinError(i,0);
		}
	}*/
	//sigExp->Draw();
	//sigExp->Scale(2);/**********				Czemu trzeba przeskalować przez 2????				******************/
						/****		Kwestia tego że wcześnie nie skalowałem przez 1/average?		*****/
	
	int cnt=0;
	double average=0;
	for(int i=sigExp->FindBin(150); i<=sigExp->FindBin(200); i++)
	{
		cnt++;
		average+=sigExp->GetBinContent(i);
	}
	average/=cnt;
	cout<<"srednia "<<average<<endl;

	sigExp->Scale(1/average);


	sigExp->SetNameTitle("doubleRatio","doubleRatio");
	sigExp->GetXaxis()->SetTitle("q_{inv} (MeV)");
	sigExp->GetYaxis()->SetTitle("CF_{exp}/fit_{SMASH}");
	sigExp->GetXaxis()->SetRangeUser(0, max);
	sigExp->SetMarkerStyle(20);
	sigExp->SetMarkerColor(sigExp->GetLineColor());
	sigExp->SetMarkerSize(0.5);
	sigExp->Write(); 
	CopyExp->Write();
	sigSMASH->Write();
	
	output->Save();


	return 0;
}
