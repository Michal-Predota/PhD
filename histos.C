




int histos()
{
	TFile *exp = new TFile("./jobs/analysis_NewCuts_2sigma_PE200MeV_nTracksGTc.root","read");
	TFile *sim = new TFile("./jobs/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4.root","read");
	TFile *output = new TFile("./outputs/SMASHratioPim_NewCuts_2sigma_P200MeV_nTracksGT4.root","read");
	
	
	TH1D* expNom = (TH1D*)output->Get("expNom");
	TH1D* expDen = (TH1D*)output->Get("expDen");
	TH1D* simNom = (TH1D*)output->Get("SMASH_nom");
	TH1D* simDen = (TH1D*)output->Get("SMASH_den");
	
	
	expNom->Divide(expDen);
	simNom->Divide(simDen);
	
	//expNom->Divide(simNom);
	
	//TCanvas *cNom = new TCanvas("cNom","cNom",800,800);
	expNom->GetXaxis()->SetRangeUser(0,600);
	expNom->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	expNom->GetYaxis()->SetRangeUser(0,0.01);
	expNom->Draw();
	simNom->SetLineColor(kRed);
	simNom->Draw("same");
	TLegend *legNom = new TLegend(0.9,0.9,0.7,0.7);
	legNom->AddEntry(expNom, "exp CF", "l");
	legNom->AddEntry(simNom, "sim CF", "l");
	legNom->Draw();
	
	
	TCanvas *cExp = new TCanvas("cExp","cExp",1350,800);
	TH2D* dtdpExpSig = (TH2D*) exp->Get("DThetaDPhiPimSig");
	TH2D* dtdpExpBckg = (TH2D*) exp->Get("DThetaDPhiPimBckg");
	dtdpExpSig->Divide(dtdpExpBckg);
	gStyle->SetOptStat(0000);
	dtdpExpSig->Rebin2D(2,2);
	dtdpExpSig->GetXaxis()->SetRangeUser(-20,20);
	dtdpExpSig->GetYaxis()->SetRangeUser(-20,20);
	dtdpExpSig->GetXaxis()->SetTitle("#Delta#Phi(deg)");
	dtdpExpSig->GetYaxis()->SetTitle("#Delta#Theta(deg)");
	dtdpExpSig->SetTitle("Exp merging");
	dtdpExpSig->Draw("colz");

	
	TCanvas *cSim = new TCanvas("cSim","cSim",1300,800);
	TH2D* dtdpSimSig = (TH2D*) sim->Get("DThetaDPhiPimSig");
	TH2D* dtdpSimBckg = (TH2D*) sim->Get("DThetaDPhiPimBckg");
	dtdpSimSig->Divide(dtdpSimBckg);
	gStyle->SetOptStat(0000);
	dtdpSimSig->Rebin2D(2,2);
	dtdpSimSig->GetXaxis()->SetRangeUser(-20,20);
	dtdpSimSig->GetYaxis()->SetRangeUser(-20,20);
	dtdpSimSig->GetXaxis()->SetTitle("#Delta#Phi(deg)");
	dtdpSimSig->GetYaxis()->SetTitle("#Delta#Theta(deg)");
	dtdpSimSig->SetTitle("Sim merging");
	dtdpSimSig->Draw("colz");
	
	
	
	
	//*************Dużo porównań**************//
	
	TFile *expLT15 = new TFile("./jobs/analysis_NewCuts_2sigma_PE200MeV_nTracksLT15.root","read");
	TFile *simLT15 = new TFile("./jobs/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksLT15.root","read");
	TFile *outputLT15 = new TFile("./outputs/SMASHratioPim_NewCuts_2sigma_P200MeV_nTracksLT15.root","read");
	
	
	TFile *expLT10 = new TFile("./jobs/analysis_NewCuts_2sigma_PE200MeV_nTracksLT10.root","read");
	TFile *simLT10 = new TFile("./jobs/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksLT10.root","read");
	TFile *outputLT10 = new TFile("./outputs/SMASHratioPim_NewCuts_2sigma_P200MeV_nTracksLT10.root","read");
	
	
	TFile *expLT5 = new TFile("./jobs/analysis_NewCuts_2sigma_PE200MeV_nTracksLT5.root","read");
	TFile *simLT5 = new TFile("./jobs/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksLT5.root","read");
	TFile *outputLT5 = new TFile("./outputs/SMASHratioPim_NewCuts_2sigma_P200MeV_nTracksLT5.root","read");
	
	
	TFile *expGT2 = new TFile("./jobs/analysis_NewCuts_2sigma_PE200MeV_nTracksGT2.root","read");
	TFile *simGT2 = new TFile("./jobs/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2.root","read");
	TFile *outputGT2 = new TFile("./outputs/SMASHratioPim_NewCuts_2sigma_P200MeV_nTracksGT2.root","read");
	
	
	TFile *expGT3 = new TFile("./jobs/analysis_NewCuts_2sigma_PE200MeV_nTracksGT3.root","read");
	TFile *simGT3 = new TFile("./jobs/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3.root","read");
	TFile *outputGT3 = new TFile("./outputs/SMASHratioPim_NewCuts_2sigma_P200MeV_nTracksGT3.root","read");
	
	
	TFile *expGT4 = new TFile("./jobs/analysis_NewCuts_2sigma_PE200MeV_nTracksGT4.root","read");
	TFile *simGT4 = new TFile("./jobs/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4.root","read");
	TFile *outputGT4 = new TFile("./outputs/SMASHratioPim_NewCuts_2sigma_P200MeV_nTracksGT4.root","read");
	
	
	TH1D* expNomLT15 = (TH1D*)outputLT15->Get("expNom");
	TH1D* expDenLT15 = (TH1D*)outputLT15->Get("expDen");
	TH1D* expCFLT15 = (TH1D*)outputLT15->Get("expCF");
	TH1D* simNomLT15 = (TH1D*)outputLT15->Get("SMASH_nom");
	TH1D* simDenLT15 = (TH1D*)outputLT15->Get("SMASH_den");
	TH1D* simCFLT15 = (TH1D*)outputLT15->Get("SMASH");
	TH1D* DRLT15 = (TH1D*)outputLT15->Get("doubleRatio");
	
	TH1D* expNomLT10 = (TH1D*)outputLT10->Get("expNom");
	TH1D* expDenLT10 = (TH1D*)outputLT10->Get("expDen");
	TH1D* expCFLT10 = (TH1D*)outputLT10->Get("expCF");
	TH1D* simNomLT10 = (TH1D*)outputLT10->Get("SMASH_nom");
	TH1D* simDenLT10 = (TH1D*)outputLT10->Get("SMASH_den");
	TH1D* simCFLT10 = (TH1D*)outputLT10->Get("SMASH");
	TH1D* DRLT10 = (TH1D*)outputLT10->Get("doubleRatio");
	
	TH1D* expNomLT5 = (TH1D*)outputLT5->Get("expNom");
	TH1D* expDenLT5 = (TH1D*)outputLT5->Get("expDen");
	TH1D* expCFLT5 = (TH1D*)outputLT5->Get("expCF");
	TH1D* simNomLT5 = (TH1D*)outputLT5->Get("SMASH_nom");
	TH1D* simDenLT5 = (TH1D*)outputLT5->Get("SMASH_den");
	TH1D* simCFLT5 = (TH1D*)outputLT5->Get("SMASH");
	TH1D* DRLT5 = (TH1D*)outputLT5->Get("doubleRatio");
	
	TH1D* expNomGT2 = (TH1D*)outputGT2->Get("expNom");
	TH1D* expDenGT2 = (TH1D*)outputGT2->Get("expDen");
	TH1D* expCFGT2 = (TH1D*)outputGT2->Get("expCF");
	TH1D* simNomGT2 = (TH1D*)outputGT2->Get("SMASH_nom");
	TH1D* simDenGT2 = (TH1D*)outputGT2->Get("SMASH_den");
	TH1D* simCFGT2 = (TH1D*)outputGT2->Get("SMASH");
	TH1D* DRGT2 = (TH1D*)outputGT2->Get("doubleRatio");
	
	TH1D* expNomGT3 = (TH1D*)outputGT3->Get("expNom");
	TH1D* expDenGT3 = (TH1D*)outputGT3->Get("expDen");
	TH1D* expCFGT3 = (TH1D*)outputGT3->Get("expCF");
	TH1D* simNomGT3 = (TH1D*)outputGT3->Get("SMASH_nom");
	TH1D* simDenGT3 = (TH1D*)outputGT3->Get("SMASH_den");
	TH1D* simCFGT3 = (TH1D*)outputGT3->Get("SMASH");
	TH1D* DRGT3 = (TH1D*)outputGT3->Get("doubleRatio");
	
	TH1D* expNomGT4 = (TH1D*)outputGT4->Get("expNom");
	TH1D* expDenGT4 = (TH1D*)outputGT4->Get("expDen");
	TH1D* expCFGT4 = (TH1D*)outputGT4->Get("expCF");
	TH1D* simNomGT4 = (TH1D*)outputGT4->Get("SMASH_nom");
	TH1D* simDenGT4 = (TH1D*)outputGT4->Get("SMASH_den");
	TH1D* simCFGT4 = (TH1D*)outputGT4->Get("SMASH");
	TH1D* DRGT4 = (TH1D*)outputGT4->Get("doubleRatio");
	
	
	
	/**********liczniki eksperyment**************/
	expNomLT15->SetTitle("exp sig N_{tracks}#in<2#;15)");
	expNomLT10->SetTitle("exp sig N_{tracks}#in<2#;#infty)");
	expNomLT5->SetTitle("exp sig N_{tracks}#in<2#;5)");
	expNomGT2->SetTitle("exp sig N_{tracks}#in<2#;#infty)");
	expNomGT3->SetTitle("exp sig N_{tracks}#in<3#;#infty)");
	expNomGT4->SetTitle("exp sig N_{tracks}#in<4#;#infty)");
	
	expNomLT15->GetXaxis()->SetTitle("q_{inv} (MeV/c)");

	TCanvas *cNomExp= new TCanvas("cNomExp","cNomExp",1300,800);
	expNomLT15->Scale(1./expNomLT15->Integral());
	expNomLT15->SetTitle("Experimental nominators comparison (normalized)");
	expNomLT15->Draw();
	
	expNomLT10->Scale(1./expNomLT10->Integral());
	expNomLT10->SetLineColor(kRed);
	expNomLT10->Draw("same");
	
	expNomLT5->Scale(1./expNomLT5->Integral());
	expNomLT5->SetLineColor(kGreen+1);
	expNomLT5->Draw("same");
	
	expNomGT2->Scale(1./expNomGT2->Integral());
	expNomGT2->SetLineColor(kMagenta+1);
	expNomGT2->Draw("same");
	
	expNomGT3->Scale(1./expNomGT3->Integral());
	expNomGT3->SetLineColor(kCyan+1);
	expNomGT3->Draw("same");
	
	expNomGT4->Scale(1./expNomGT4->Integral());
	expNomGT4->SetLineColor(kOrange+2);
	expNomGT4->Draw("same");
	
	
	TLegend *legNomExp = new TLegend(0.9,0.9,0.7,0.7);
	legNomExp->AddEntry(expNomLT15, "N_{tracks}<15", "l");
	legNomExp->AddEntry(expNomLT10, "N_{tracks}<10", "l");
	legNomExp->AddEntry(expNomLT5, "N_{tracks}<5", "l");
	legNomExp->AddEntry(expNomGT2, "N_{tracks}>2", "l");
	legNomExp->AddEntry(expNomGT3, "N_{tracks}>3", "l");
	legNomExp->AddEntry(expNomGT4, "N_{tracks}>4", "l");
	legNomExp->Draw();
	
	
	
	/**********Mianownik eksperyment**********/
	expDenLT15->SetTitle("exp bckg N_{tracks}#in<2#;15)");
	expDenLT10->SetTitle("exp bckg N_{tracks}#in<2#;#infty)");
	expDenLT5->SetTitle("exp bckg N_{tracks}#in<2#;5)");
	expDenGT2->SetTitle("exp bckg N_{tracks}#in<2#;#infty)");
	expDenGT3->SetTitle("exp bckg N_{tracks}#in<3#;#infty)");
	expDenGT4->SetTitle("exp bckg N_{tracks}#in<4#;#infty)");
	
	expDenLT15->GetXaxis()->SetTitle("q_{inv} (MeV/c)");

	TCanvas *cDenExp= new TCanvas("cDenExp","cDenExp",1300,800);
	expDenLT15->Scale(1./expDenLT15->Integral());
	expDenLT15->SetTitle("Experimental Deninators comparison (normalized)");
	expDenLT15->Draw();
	
	expDenLT10->Scale(1./expDenLT10->Integral());
	expDenLT10->SetLineColor(kRed);
	expDenLT10->Draw("same");
	
	expDenLT5->Scale(1./expDenLT5->Integral());
	expDenLT5->SetLineColor(kGreen+1);
	expDenLT5->Draw("same");
	
	expDenGT2->Scale(1./expDenGT2->Integral());
	expDenGT2->SetLineColor(kMagenta+1);
	expDenGT2->Draw("same");
	
	expDenGT3->Scale(1./expDenGT3->Integral());
	expDenGT3->SetLineColor(kCyan+1);
	expDenGT3->Draw("same");
	
	expDenGT4->Scale(1./expDenGT4->Integral());
	expDenGT4->SetLineColor(kOrange+2);
	expDenGT4->Draw("same");
	
	
	TLegend *legDenExp = new TLegend(0.9,0.9,0.7,0.7);
	legDenExp->AddEntry(expDenLT15, "N_{tracks}<15", "l");
	legDenExp->AddEntry(expDenLT10, "N_{tracks}<10", "l");
	legDenExp->AddEntry(expDenLT5, "N_{tracks}<5", "l");
	legDenExp->AddEntry(expDenGT2, "N_{tracks}>2", "l");
	legDenExp->AddEntry(expDenGT3, "N_{tracks}>3", "l");
	legDenExp->AddEntry(expDenGT4, "N_{tracks}>4", "l");
	legDenExp->Draw();
	
	
	
	/**********liczniki smash**************/
	simNomLT15->SetTitle("sim sig N_{tracks}#in<2#;15)");
	simNomLT10->SetTitle("sim sig N_{tracks}#in<2#;#infty)");
	simNomLT5->SetTitle("sim sig N_{tracks}#in<2#;5)");
	simNomGT2->SetTitle("sim sig N_{tracks}#in<2#;#infty)");
	simNomGT3->SetTitle("sim sig N_{tracks}#in<3#;#infty)");
	simNomGT4->SetTitle("sim sig N_{tracks}#in<4#;#infty)");
	
	simNomLT15->GetXaxis()->SetTitle("q_{inv} (MeV/c)");

	TCanvas *cNomsim= new TCanvas("cNomsim","cNomsim",1300,800);
	simNomLT15->Scale(1./simNomLT15->Integral());
	simNomLT15->SetTitle("Simulated nominators comparison (normalized)");
	simNomLT15->Draw();
	
	simNomLT10->Scale(1./simNomLT10->Integral());
	simNomLT10->SetLineColor(kRed);
	simNomLT10->Draw("same");
	
	simNomLT5->Scale(1./simNomLT5->Integral());
	simNomLT5->SetLineColor(kGreen+1);
	simNomLT5->Draw("same");
	
	simNomGT2->Scale(1./simNomGT2->Integral());
	simNomGT2->SetLineColor(kMagenta+1);
	simNomGT2->Draw("same");
	
	simNomGT3->Scale(1./simNomGT3->Integral());
	simNomGT3->SetLineColor(kCyan+1);
	simNomGT3->Draw("same");
	
	simNomGT4->Scale(1./simNomGT4->Integral());
	simNomGT4->SetLineColor(kOrange+2);
	simNomGT4->Draw("same");
	
	
	TLegend *legNomsim = new TLegend(0.9,0.9,0.7,0.7);
	legNomsim->AddEntry(simNomLT15, "N_{tracks}<15", "l");
	legNomsim->AddEntry(simNomLT10, "N_{tracks}<10", "l");
	legNomsim->AddEntry(simNomLT5, "N_{tracks}<5", "l");
	legNomsim->AddEntry(simNomGT2, "N_{tracks}>2", "l");
	legNomsim->AddEntry(simNomGT3, "N_{tracks}>3", "l");
	legNomsim->AddEntry(simNomGT4, "N_{tracks}>4", "l");
	legNomsim->Draw();
	
	
	
	/**********Mianownik smash**********/
	simDenLT15->SetTitle("sim bckg N_{tracks}#in<2#;15)");
	simDenLT10->SetTitle("sim bckg N_{tracks}#in<2#;#infty)");
	simDenLT5->SetTitle("sim bckg N_{tracks}#in<2#;5)");
	simDenGT2->SetTitle("sim bckg N_{tracks}#in<2#;#infty)");
	simDenGT3->SetTitle("sim bckg N_{tracks}#in<3#;#infty)");
	simDenGT4->SetTitle("sim bckg N_{tracks}#in<4#;#infty)");
	
	simDenLT15->GetXaxis()->SetTitle("q_{inv} (MeV/c)");

	TCanvas *cDensim= new TCanvas("cDensim","cDensim",1300,800);
	simDenLT15->Scale(1./simDenLT15->Integral());
	simDenLT15->SetTitle("Simulated Deninators comparison (normalized)");
	simDenLT15->Draw();
	
	simDenLT10->Scale(1./simDenLT10->Integral());
	simDenLT10->SetLineColor(kRed);
	simDenLT10->Draw("same");
	
	simDenLT5->Scale(1./simDenLT5->Integral());
	simDenLT5->SetLineColor(kGreen+1);
	simDenLT5->Draw("same");
	
	simDenGT2->Scale(1./simDenGT2->Integral());
	simDenGT2->SetLineColor(kMagenta+1);
	simDenGT2->Draw("same");
	
	simDenGT3->Scale(1./simDenGT3->Integral());
	simDenGT3->SetLineColor(kCyan+1);
	simDenGT3->Draw("same");
	
	simDenGT4->Scale(1./simDenGT4->Integral());
	simDenGT4->SetLineColor(kOrange+2);
	simDenGT4->Draw("same");
	
	
	TLegend *legDensim = new TLegend(0.9,0.9,0.7,0.7);
	legDensim->AddEntry(simDenLT15, "N_{tracks}<15", "l");
	legDensim->AddEntry(simDenLT10, "N_{tracks}<10", "l");
	legDensim->AddEntry(simDenLT5, "N_{tracks}<5", "l");
	legDensim->AddEntry(simDenGT2, "N_{tracks}>2", "l");
	legDensim->AddEntry(simDenGT3, "N_{tracks}>3", "l");
	legDensim->AddEntry(simDenGT4, "N_{tracks}>4", "l");
	legDensim->Draw();
	
	
	
	/**********CF Exp**************/
	expCFLT15->SetTitle("exp CF N_{tracks}#in<2#;15)");
	expCFLT10->SetTitle("exp CF N_{tracks}#in<2#;#infty)");
	expCFLT5->SetTitle("exp CF N_{tracks}#in<2#;5)");
	expCFGT2->SetTitle("exp CF N_{tracks}#in<2#;#infty)");
	expCFGT3->SetTitle("exp CF N_{tracks}#in<3#;#infty)");
	expCFGT4->SetTitle("exp CF N_{tracks}#in<4#;#infty)");
	
	expCFLT15->GetXaxis()->SetTitle("q_{inv} (MeV/c)");

	TCanvas *cCFexp= new TCanvas("cCFexp","cCFexp",1300,800);
//	expCFLT15->Scale(1./expCFLT15->Integral());
	expCFLT15->SetTitle("Experimental Correlation Functions comparison");
	expCFLT15->Draw();
	
//	expCFLT10->Scale(1./expCFLT10->Integral());
	expCFLT10->SetLineColor(kRed);
	expCFLT10->Draw("same");
	
//	expCFLT5->Scale(1./expCFLT5->Integral());
	expCFLT5->SetLineColor(kGreen+1);
	expCFLT5->Draw("same");
	
//	expCFGT2->Scale(1./expCFGT2->Integral());
	expCFGT2->SetLineColor(kMagenta+1);
	expCFGT2->Draw("same");
	
//	expCFGT3->Scale(1./expCFGT3->Integral());
	expCFGT3->SetLineColor(kCyan+1);
	expCFGT3->Draw("same");
	
//	expCFGT4->Scale(1./expCFGT4->Integral());
	expCFGT4->SetLineColor(kOrange+2);
	expCFGT4->Draw("same");
	
	
	TLegend *legCFexp = new TLegend(0.9,0.9,0.7,0.7);
	legCFexp->AddEntry(expCFLT15, "N_{tracks}<15", "l");
	legCFexp->AddEntry(expCFLT10, "N_{tracks}<10", "l");
	legCFexp->AddEntry(expCFLT5, "N_{tracks}<5", "l");
	legCFexp->AddEntry(expCFGT2, "N_{tracks}>2", "l");
	legCFexp->AddEntry(expCFGT3, "N_{tracks}>3", "l");
	legCFexp->AddEntry(expCFGT4, "N_{tracks}>4", "l");
	legCFexp->Draw();
	
	
	
	/**********CF smash**********/
	simCFLT15->SetTitle("sim CF N_{tracks}#in<2#;15)");
	simCFLT10->SetTitle("sim CF N_{tracks}#in<2#;#infty)");
	simCFLT5->SetTitle("sim CF N_{tracks}#in<2#;5)");
	simCFGT2->SetTitle("sim CF N_{tracks}#in<2#;#infty)");
	simCFGT3->SetTitle("sim CF N_{tracks}#in<3#;#infty)");
	simCFGT4->SetTitle("sim CF N_{tracks}#in<4#;#infty)");
	
	simCFLT15->GetXaxis()->SetTitle("q_{inv} (MeV/c)");

	TCanvas *cCFsim= new TCanvas("cCFsim","cCFsim",1300,800);
//	simCFLT15->Scale(1./simCFLT15->Integral());
	simCFLT15->SetTitle("Simulated Correlation Functions comparison ");
	simCFLT15->GetFunction("MyPoly")->SetLineColor(simCFLT15->GetLineColor());
	simCFLT15->GetFunction("MyPoly")->SetBit(TF1::kNotDraw);
	simCFLT15->Draw("0");
	
//	simCFLT10->Scale(1./simCFLT10->Integral());
	simCFLT10->SetLineColor(kRed);
	simCFLT10->GetFunction("MyPoly")->SetLineColor(kRed);
	simCFLT10->GetFunction("MyPoly")->SetBit(TF1::kNotDraw);
	simCFLT10->Draw("same0");
	
//	simCFLT5->Scale(1./simCFLT5->Integral());
	simCFLT5->SetLineColor(kGreen+1);
	simCFLT5->GetFunction("MyPoly")->SetLineColor(kGreen+1);
	simCFLT5->GetFunction("MyPoly")->SetBit(TF1::kNotDraw);
	simCFLT5->Draw("same0");
	
//	simCFGT2->Scale(1./simCFGT2->Integral());
	simCFGT2->SetLineColor(kMagenta+1);
	simCFGT2->GetFunction("MyPoly")->SetLineColor(kMagenta+1);
	simCFGT2->GetFunction("MyPoly")->SetBit(TF1::kNotDraw);
	simCFGT2->Draw("same0");
	
//	simCFGT3->Scale(1./simCFGT3->Integral());
	simCFGT3->SetLineColor(kCyan+1);
	simCFGT3->GetFunction("MyPoly")->SetLineColor(kCyan+1);
	simCFGT3->GetFunction("MyPoly")->SetBit(TF1::kNotDraw);
	simCFGT3->Draw("same0");
	
//	simCFGT4->Scale(1./simCFGT4->Integral());
	simCFGT4->SetLineColor(kOrange+2);
	simCFGT4->GetFunction("MyPoly")->SetLineColor(kOrange+2);
	simCFGT4->GetFunction("MyPoly")->SetBit(TF1::kNotDraw);
	simCFGT4->Draw("same0");
	
	
	TLegend *legCFsim = new TLegend(0.9,0.9,0.7,0.7);
	legCFsim->AddEntry(simCFLT15, "N_{tracks}<15", "l");
	legCFsim->AddEntry(simCFLT10, "N_{tracks}<10", "l");
	legCFsim->AddEntry(simCFLT5, "N_{tracks}<5", "l");
	legCFsim->AddEntry(simCFGT2, "N_{tracks}>2", "l");
	legCFsim->AddEntry(simCFGT3, "N_{tracks}>3", "l");
	legCFsim->AddEntry(simCFGT4, "N_{tracks}>4", "l");
	legCFsim->Draw();
	
	
	
	/**********Double Ratio**********/
	DRLT15->SetTitle(" DR N_{tracks}#in<2#;15)");
	DRLT10->SetTitle(" DR N_{tracks}#in<2#;#infty)");
	DRLT5->SetTitle(" DR N_{tracks}#in<2#;5)");
	DRGT2->SetTitle(" DR N_{tracks}#in<2#;#infty)");
	DRGT3->SetTitle(" DR N_{tracks}#in<3#;#infty)");
	DRGT4->SetTitle(" DR N_{tracks}#in<4#;#infty)");
	
	DRLT15->GetXaxis()->SetTitle("q_{inv} (MeV/c)");

	TCanvas *cDR= new TCanvas("cDR","cDR",1300,800);
//	DRLT15->Scale(1./DRLT15->Integral());
	DRLT15->GetYaxis()->SetRangeUser(0,1.25);
	DRLT15->SetTitle("Double Ratios comparison ");
	DRLT15->Draw("0");
	
//	DRLT10->Scale(1./DRLT10->Integral());
	DRLT10->SetLineColor(kRed);
	DRLT10->SetMarkerColor(kRed);
	DRLT10->Draw("same0");
	
//	DRLT5->Scale(1./DRLT5->Integral());
	DRLT5->SetLineColor(kGreen+1);
	DRLT5->SetMarkerColor(kGreen+1);
	DRLT5->Draw("same0");
	
//	DRGT2->Scale(1./DRGT2->Integral());
	DRGT2->SetLineColor(kMagenta+1);
	DRGT2->SetMarkerColor(kMagenta+1);
	DRGT2->Draw("same0");
	
//	DRGT3->Scale(1./DRGT3->Integral());
	DRGT3->SetLineColor(kCyan+1);
	DRGT3->SetMarkerColor(kCyan+1);
	DRGT3->Draw("same0");
	
//	DRGT4->Scale(1./DRGT4->Integral());
	DRGT4->SetLineColor(kOrange+2);
	DRGT4->SetMarkerColor(kOrange+2);
	DRGT4->Draw("same0");
	
	
	TLegend *legDR = new TLegend(0.9,0.9,0.7,0.7);
	legDR->AddEntry(DRLT15, "N_{tracks}<15", "l");
	legDR->AddEntry(DRLT10, "N_{tracks}<10", "l");
	legDR->AddEntry(DRLT5, "N_{tracks}<5", "l");
	legDR->AddEntry(DRGT2, "N_{tracks}>2", "l");
	legDR->AddEntry(DRGT3, "N_{tracks}>3", "l");
	legDR->AddEntry(DRGT4, "N_{tracks}>4", "l");
	legDR->Draw();
	
	
	
	
	
	return 0;
}