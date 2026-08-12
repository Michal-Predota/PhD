

int SmashDivide()
{
	//gStyle->SetErrorX(0);
	
	
	
	TFile *file1 = new TFile("./outputs/SMASHratio_gt1.root", "read");
	TFile *file2 = new TFile("./outputs/SMASHratioKine_gt1.root", "read");
	
	
	TH1D *SmashCF = (TH1D*)file1->Get("SMASH");
	TH1D *SmashCFKine = (TH1D*)file2->Get("SMASH");
	TH1D *ExpCF = (TH1D*)file2->Get("expCF");
	
	
	
	
	SmashCF->Divide(SmashCFKine);
	SmashCF->SetNameTitle("reco/kine", "reco/kine");
	SmashCF->GetYaxis()->SetTitle("CF_{reco}/CF_{kine}");
	
	ExpCF->Divide(SmashCF);
	ExpCF->SetNameTitle("exp/(reco/kine)","exp/(reco/kine)");
	ExpCF->GetYaxis()->SetTitle("CF_{exp}/(CF_{reco}/CF_{kine})");
	
	
	ExpCF->Draw();
	
	
	
	return 0;
}