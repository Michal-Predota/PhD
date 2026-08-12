
double myGaus(const double *x, const double *pars)
{
	double exp = TMath::Exp(-x[0]*x[0]/(2*pars[0]*pars[0]));
	
	
	return pars[1]*1/TMath::Sqrt(2*TMath::Pi()*pars[0]*pars[0])*exp;
}



double myCauchy(const double *x, const double *pars)
{
	return pars[1]*1/(TMath::Pi()*pars[0]*(1+(x[0]/pars[0]*x[0]/pars[0])));
}




int sourceFunctions()
{
	
	TFile *f = new TFile("./outputs/fit_LCMS_HITS.root","READ");
	
	TH1D *h = (TH1D*) f->Get("CF");
	TF1 *fitGaus = (TF1*)f->Get("fitGaus");
	TF1 *fitExp = (TF1*)f->Get("fitExp");
	
	
	TF1 *sourceGaus = new TF1("sourceGaus", myGaus, 0, 10, 2);
	sourceGaus->SetParameter(0,fitGaus->GetParameter(1));
	sourceGaus->SetParameter(1,1);
	
	TF1 *sourceCauchy = new TF1("sourceCauchy", myCauchy, 0, 10, 2);
	sourceCauchy->SetParameter(0,fitExp->GetParameter(1));
	sourceCauchy->SetParameter(1,1);
	
	double min=0, max=10;
	double integralGaus=0, integralCauchy=0;
	for(int i=0; i<10000; i++)
	{
		integralGaus+=sourceGaus->Eval((max-min)/i);
		integralCauchy+=sourceCauchy->Eval((max-min)/i);
	}
	
	
	sourceGaus->SetParameter(1, 1/sourceGaus->Integral(0,100));
	sourceCauchy->SetParameter(1, 1/sourceCauchy->Integral(0,100));
	
	
	cout<<"gaus R: "<<fitGaus->GetParameter(1)<<" cauchy R: "<<fitExp->GetParameter(1)<<endl;
	sourceGaus->SetLineColor(kBlue+1);
	sourceGaus->Draw();
	sourceCauchy->SetLineColor(kRed);
	sourceCauchy->Draw("same");
	
	
	
	return 0;
}