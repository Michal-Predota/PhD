

int qtest()
{
	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_5MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");

	TH2D *averageEvsAverageP = (TH2D*)f->Get("AverageEvsAverageP");
	TH2D *metaVsNTracks = (TH2D*)f->Get("MetaHitsVsNTracksnPimGT1");
	TH1D *metaHits = metaVsNTracks->ProjectionY();
	TH1D *vertexZ = (TH1D*)f->Get("vertexZnPimGT1");
	TH1D *vertexX = (TH1D*)f->Get("vertexXnPimGT1");
	TH1D *vertexY = (TH1D*)f->Get("vertexYnPimGT1");
	TH1D *averageE = averageEvsAverageP->ProjectionY();
	TH1D *averageP = averageEvsAverageP->ProjectionX();

	std::array<float, 6> metaHitsQuantilesnPimGT1  = {0,4.6541,5.63784,6.66823,8.15849,50};
	std::array<float, 6> vertexXQuantilesnPimGT1  = {-10,-1.15336,0.148828,1.25418,2.46926,9.96};
	std::array<float, 6> vertexYQuantilesnPimGT1  = {-10,-3.32427,-2.29754,-1.25912,0.115317,9.96};
	std::array<float, 16> vertexZQuantilesnPimGT1  = {-150,-142.12,-139.166,-136.191,-133.203,-130.208,-127.217,-124.226,-121.233,-118.232,-115.236,-112.212,-109.179,-106.135,-103.068,-1};			
	std::array<float, 6> averageEnergyQuantilesnPimGT1  = {0,858.128,985.042,1085.39,1216.57,2000};
	std::array<float, 6> averageMomentumQuantilesnPimGT1  = {0,437.983,549.982,661.416,807.474,1998};
	
	TH1D *distMeta = new TH1D("distMeta","distMeta",20,0,20);
	TH1D *distX = new TH1D("distX","distX",20,0,20);
	TH1D *distY = new TH1D("distY","distY",20,0,20);
	TH1D *distZ = new TH1D("distZ","distZ",20,0,20);
	TH1D *distE = new TH1D("distE","distE",20,0,20);
	TH1D *distP = new TH1D("distP","distP",20,0,20);
	
	for(int i=0; i<1000000; i++)
	{
		int r = metaHits->GetRandom();	
		std::size_t q = std::lower_bound(metaHitsQuantilesnPimGT1.begin(), metaHitsQuantilesnPimGT1.end(), r) - metaHitsQuantilesnPimGT1.begin(); 	
		distMeta->Fill(q);
		
		r = vertexX->GetRandom();
		q = std::lower_bound(vertexXQuantilesnPimGT1.begin(), vertexXQuantilesnPimGT1.end(), r) - vertexXQuantilesnPimGT1.begin(); 	
		distX->Fill(q);
		
		r = vertexY->GetRandom();
		q = std::lower_bound(vertexYQuantilesnPimGT1.begin(), vertexYQuantilesnPimGT1.end(), r) - vertexYQuantilesnPimGT1.begin(); 	
		distY->Fill(q);
		
		r = vertexZ->GetRandom();
		q = std::lower_bound(vertexZQuantilesnPimGT1.begin(), vertexZQuantilesnPimGT1.end(), r) - vertexZQuantilesnPimGT1.begin(); 	
		distZ->Fill(q);
		
		r = averageE->GetRandom();
		q = std::lower_bound(averageEnergyQuantilesnPimGT1.begin(), averageEnergyQuantilesnPimGT1.end(), r) - averageEnergyQuantilesnPimGT1.begin(); 	
		distE->Fill(q);
		
		r = averageP->GetRandom();
		q = std::lower_bound(averageMomentumQuantilesnPimGT1.begin(), averageMomentumQuantilesnPimGT1.end(), r) - averageMomentumQuantilesnPimGT1.begin(); 	
		distP->Fill(q);
	}
	
	TCanvas *cm = new TCanvas("cm","cm",800,800);
	distMeta->Draw();
	TCanvas *cx = new TCanvas("cX","cX",800,800);
	distX->Draw();
	TCanvas *cy = new TCanvas("cY","cY",800,800);
	distY->Draw();
	TCanvas *cz = new TCanvas("cZ","cZ",800,800);
	distZ->Draw();
	TCanvas *cE = new TCanvas("cE","cE",800,800);
	distE->Draw();
	TCanvas *cP = new TCanvas("cP","cP",800,800);
	distP->Draw();
	
	
	return 0;
}