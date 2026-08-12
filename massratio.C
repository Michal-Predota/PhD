



int massratio()
{
	
	TFile *f1 = new TFile("./outputs/invMassPimpAnalysis_gt0.root","read");
	TFile *f2 = new TFile("./outputs/invMassPimpAnalysisSim_gt0.root","read");
	
	
	
	TH1D *exp = (TH1D*)f1->Get("divided");
	TH1D *smash = (TH1D*)f2->Get("divided");
	
	
	exp->Scale(1/exp->Integral(),"nosw2");
	smash->Scale(1/smash->Integral(),"nosw2");
	
	
	exp->Divide(smash);
	
	
	exp->Draw();
	
	
	return 0;
}