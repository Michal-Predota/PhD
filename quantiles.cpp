#include <vector>

int quantiles()
{
	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_5MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
	TH2D *metaVsNTracks = (TH2D*)f->Get("MetaHitsVsNTracksnPimGT1");
	TH2D *averageEvsAverageP = (TH2D*)f->Get("AverageEvsAverageP");
	TH1D *vertexX = (TH1D*)f->Get("vertexXnPimGT1");
	TH1D *vertexY = (TH1D*)f->Get("vertexYnPimGT1");
	TH1D *vertexZ = (TH1D*)f->Get("vertexZnPimGT1");
	//TH1D *vertexZ = (TH1D*)f-> Get("vertexZ");

	TH1D *metaHits = metaVsNTracks->ProjectionY();
	TH1D *averageE = averageEvsAverageP->ProjectionY();
	TH1D *averageP = averageEvsAverageP->ProjectionX();
	
	
	TH1D *h = new TH1D(*metaHits);
	
	const Int_t nq = 5;
	Double_t p[nq];  // probabilities where to evaluate the quantiles in [0,1]
	Double_t xp[nq]; // array of positions X to store the resulting quantiles
	for (Int_t i=0;i<nq;i++)
		p[i] = Float_t(i+1)/nq;
	h->GetQuantiles(nq,xp,p);
	
	TCanvas *c1 = new TCanvas("c1","c1",10,10,700,900);
	c1->Divide(1,2);
	c1->cd(1);
	h->Draw();
 
	// show the quantiles in the bottom pad
	c1->cd(2);
	gPad->SetGrid();
	TGraph *gr = new TGraph(nq,xp,p);
	gr->GetXaxis()->SetRangeUser(h->GetXaxis()->GetBinLowEdge(1),h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()));
	gr->SetMarkerStyle(21);
	gr->GetXaxis()->SetTitle("x");
	gr->GetYaxis()->SetTitle("p");
	gr->Draw("alp");
	
	for(int i=0; i<nq; i++)
		std::cout<<xp[i]<<std::endl;
	
	std::vector<int> counts;
	int cnt1=0;
	int cnt2=0;
	int cnt3=0;
	int cnt4=0;
	int cnt5=0;
	int whichQ=0;
	for(int i=1;i<h->GetNbinsX();i++)
	{
		if(h->GetBinCenter(i)<xp[0])
			cnt1++;
		if(h->GetBinCenter(i)<xp[1] && h->GetBinCenter(i)>xp[0])
			cnt2++;
		if(h->GetBinCenter(i)<xp[2] && h->GetBinCenter(i)>xp[1])
			cnt3++;
		if(h->GetBinCenter(i)<xp[3] && h->GetBinCenter(i)>xp[2])
			cnt4++;
		if(h->GetBinCenter(i)<xp[4] && h->GetBinCenter(i)>xp[3])
			cnt5++;
	}
	cout<<cnt1<<endl;
	cout<<cnt2<<endl;
	cout<<cnt3<<endl;
	cout<<cnt4<<endl;
	cout<<cnt5<<endl;
	
	
	return 0;
}