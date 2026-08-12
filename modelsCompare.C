
int modelsCompare()
{
	gStyle->SetErrorX(0);	
	
	TFile *file1 = new TFile("./outputs/expUrQMDanalysisPim4.5GeV_weights_gt1.root", "read");
	TFile *file2 = new TFile("./outputs/SMASHratioPim_gt1.root", "read");
	TFile *file3 = new TFile("./outputs/SMASHratioKinePim_gt1.root", "read");
	TFile *file4 = new TFile("./outputs/expUrQMDanalysisPim4.5GeV_noweights.root", "read");
	
	
	
	TH2D *doubleRatioUrQMDWeights = (TH2D*)file1->Get("doubleRatio");
	TH2D *doubleRatioUrQMDNoWeights = (TH2D*)file4->Get("doubleRatio");
	TH2D *doubleRatioSMASH = (TH2D*)file2->Get("doubleRatio");
	TH2D *doubleRatioSMASHKine = (TH2D*)file3->Get("doubleRatio");
	
	
	
	TCanvas *c = new TCanvas("c","c",800,800);
	
	
	
	doubleRatioUrQMDWeights->SetNameTitle("Double Ratios Comparison", "Double Ratios Comparison");
	doubleRatioUrQMDWeights->GetYaxis()->SetTitle("Double Ratio");
	doubleRatioUrQMDWeights->SetLineWidth(2);
	doubleRatioUrQMDWeights->SetMarkerStyle(20);
	doubleRatioUrQMDWeights->SetMarkerSize(1);
	doubleRatioUrQMDWeights->SetMarkerColor(doubleRatioUrQMDWeights->GetLineColor());
	doubleRatioUrQMDWeights->GetXaxis()->SetRangeUser(0, 400);
	doubleRatioUrQMDWeights->GetYaxis()->SetRangeUser(0, 2);
	doubleRatioUrQMDWeights->Draw();
	
	
	
	
	doubleRatioSMASH->SetLineColor(kRed);
	doubleRatioSMASH->SetLineWidth(2);
	doubleRatioSMASH->SetMarkerStyle(20);
	doubleRatioSMASH->SetMarkerSize(1);
	doubleRatioSMASH->SetMarkerColor(doubleRatioSMASH->GetLineColor());
	doubleRatioSMASH->Draw("same");
	
	
	doubleRatioSMASHKine->SetLineColor(kGreen);
	doubleRatioSMASHKine->SetLineWidth(2);
	doubleRatioSMASHKine->SetMarkerStyle(20);
	doubleRatioSMASHKine->SetMarkerSize(1);
	doubleRatioSMASHKine->SetMarkerColor(doubleRatioSMASHKine->GetLineColor());
	doubleRatioSMASHKine->Draw("same");
	
	
	doubleRatioUrQMDNoWeights->SetLineColor(kCyan+1);
	doubleRatioUrQMDNoWeights->SetLineWidth(2);
	doubleRatioUrQMDNoWeights->SetMarkerStyle(20);
	doubleRatioUrQMDNoWeights->SetMarkerColor(doubleRatioUrQMDNoWeights->GetLineColor());
//	doubleRatioUrQMDNoWeights->Draw("same");
	
	
	
	TLegend *legend = new TLegend(0.9,0.9,0.65,0.75);
	legend->AddEntry(doubleRatioUrQMDWeights,"double ratio UrQMD with \"reco\"", "l");
	legend->AddEntry(doubleRatioSMASH,"double ratio SMASH", "l");
	legend->AddEntry(doubleRatioSMASHKine,"double ratio SMASH kine", "l");
	legend->Draw();
	
	
	
	return 0;
}