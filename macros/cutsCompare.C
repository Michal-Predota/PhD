

int cutsCompare()
{
	gStyle->SetOptStat(0000);
	
	
	TFile *GT1NoCut= new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_NOCUT.root","read");
	TFile *GT1Hits = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS.root","read");
	TFile *GT1DPhi4_DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_DPhi4DTheta2.root","read");
	TFile *GT1HitsTopology = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY.root","read");
	TFile *GT1HitsDPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_DPhi4_DTheta2.root","read");
	TFile *GT1HitsTopologyDPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	TFile *GT1HitsTopologyDPhi10DTheta5 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DPhi10_DTheta5.root","read");
	TFile *GT1HitsTopologyDCA2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DCA2.root","read");
	TFile *GT1DPhi4Theta2VertexZ = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_DPhi4_DTheta2.root","read");
	
	TFile *GT2HitsTopologyDPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	TFile *GT3HitsTopologyDPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	TFile *GT4HitsTopologyDPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	TFile *GT5HitsTopologyDPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	
	TFile *GT1DPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_DPhi4_DTheta2.root","read");
	TFile *GT2DPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_VertexZ_DPhi4_DTheta2.root","read");
	TFile *GT3DPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_VertexZ_DPhi4_DTheta2.root","read");
	TFile *GT4DPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_VertexZ_DPhi4_DTheta2.root","read");
	TFile *GT5DPhi4DTheta2 = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_VertexZ_DPhi4_DTheta2.root","read");
	
	TFile *GT1HITS = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_HITS.root","read");
	TFile *GT2HITS = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_VertexZ_HITS.root","read");
	TFile *GT3HITS = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_VertexZ_HITS.root","read");
	TFile *GT4HITS = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_VertexZ_HITS.root","read");
	TFile *GT5HITS = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_VertexZ_HITS.root","read");
	
	TFile *GT1noCutVertexZ = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_noCut.root","read");
	TFile *GT2noCutVertexZ = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_VertexZ_noCut.root","read");
	TFile *GT3noCutVertexZ = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_VertexZ_noCut.root","read");
	TFile *GT4noCutVertexZ = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_VertexZ_noCut.root","read");
	TFile *GT5noCutVertexZ = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_VertexZ_noCut.root","read");
	
	
	TFile *GT1noCut = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_noCut.root","read");
	TFile *GT2noCut = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_noCut.root","read");
	TFile *GT3noCut = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_noCut.root","read");
	TFile *GT4noCut = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_noCut.root","read");
	TFile *GT5noCut = new TFile("../jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_noCut.root","read");
	
	
	
//	vector<TFile *> files = {GT1NoCut, GT1Hits, GT1DPhi4_DTheta2, GT1HitsTopology, GT1HitsDPhi4DTheta2, GT1HitsTopologyDPhi4DTheta2, GT1HitsTopologyDPhi10DTheta5,GT1HitsTopologyDCA2,GT1DPhi4Theta2VertexZ};
//	vector<TFile *> files = {GT1HitsTopologyDPhi4DTheta2,GT2HitsTopologyDPhi4DTheta2,GT3HitsTopologyDPhi4DTheta2,GT4HitsTopologyDPhi4DTheta2,GT5HitsTopologyDPhi4DTheta2};
//	vector<TFile *> files = {GT1DPhi4DTheta2,GT2DPhi4DTheta2,GT3DPhi4DTheta2,GT4DPhi4DTheta2,GT5DPhi4DTheta2};
	vector<TFile *> files = {GT1HITS,GT2HITS,GT3HITS,GT4HITS,GT5HITS};
//	vector<TFile *> files = {GT1noCutVertexZ,GT2noCutVertexZ,GT3noCutVertexZ,GT4noCutVertexZ,GT5noCutVertexZ};
	vector<TFile *> filesNoCut = {GT1noCut,GT2noCut,GT3noCut,GT4noCut,GT5noCut};
	vector<TH1D *> signals = {};
	vector<TH1D *> signalsNoCut = {};
	vector<TH1D *> backgrounds = {};
	vector<TH1D *> backgroundsNoCut = {};
	vector<TH1D *> CF = {};
	vector<TH1D *> CFNoCut = {};
	vector<int> colours = {kBlue+2, kRed+2, kMagenta+2, kGreen+2, kCyan+2, kYellow+2, kViolet+2};
	vector<int> coloursNoCut = {kBlue, kRed, kMagenta, kGreen, kCyan, kYellow, kViolet};
	
//	vector<char*> sigNames = {"sigGT1NoCut", "sigGT1Hits", "sigGT1DPhi4DTheta2", "sigGT1HitsTopology", "sigGT1HitsDPhi4DTheta2", "sigGT1HitsDPhi4DTheta2", "sigGT1HitsTopologyDPhi10DTheta5","sigGT1HitsTopologyDCA","sigGT1DPhi4Theta2VertexZ"};
//	vector<char*> bckgNames = {"bckgGT1NoCut", "bckgGT1Hits", "bckgGT1DPhi4DTheta2","bckgGT1HitsTopology","bckgGT1HitsDPhi4DTheta2","bckgGT1HitsTopologyDPhi4DTheta2", "bckgGT1HitsDPhi10DTheta5", "bckgGT1HitsTopologyDCA","bckgGT1DPhi4Theta2VertexZ"};
//	vector<char*> legNames = {"nTracks #geq 2 no pair cuts", "nTracks #geq 2 Hits", "nTracks #geq 2 DPhi #GT 4 DTheta #GT 2", "nTracks #geq 2 Hits Topology","nTracks #geq 2 Hits DPhi #GT 4 DTheta #GT 2","nTracks #geq 2 Hits Topology DPhi #GT 4 DTheta #GT 2", "nTracks #geq 2 Hits DPhi #GT 10 DTheta #GT 5", "nTracks #geq 2 Hits Topology DCA #GT 2", "nTracks #GT 1 DPhi #GT 4 DTheta #GT 2 VertexZ"};
	
//	vector<char*> sigNames = {"sigGT1HitsTopologyDPhi4DTheta2","sigGT2HitsTopologyDPhi4DTheta2","sigGT3HitsTopologyDPhi4DTheta2","sigGT4HitsTopologyDPhi4DTheta2","sigGT5HitsTopologyDPhi4DTheta2"};
//	vector<char*> bckgNames = {"bckgGT1HitsTopologyDPhi4DTheta2","bckgGT2HitsTopologyDPhi4DTheta2","bckgGT3HitsTopologyDPhi4DTheta2","bckgGT4HitsTopologyDPhi4DTheta2","bckgGT5HitsTopologyDPhi4DTheta2"};
//	vector<char*> legNames = {"GT1HitsTopologDPhi4DTheta2","GT2HitsTopologyDPhi4DTheta2","GT3HitsTopologyDPhi4DTheta2","GT4HitsTopologyDPhi4DTheta2","GT5HitsTopologyDPhi4DTheta2"};
	
	
//	vector<char*> sigNames = {"sigGT1DPhi4DTheta2","sigGT2DPhi4DTheta2","sigGT3DPhi4DTheta2","sigGT4DPhi4DTheta2","sigGT5DPhi4DTheta2"};
//	vector<char*> bckgNames = {"bckgGT1DPhi4DTheta2","bckgGT2DPhi4DTheta2","bckgGT3DPhi4DTheta2","bckgGT4DPhi4DTheta2","bckgGT5DPhi4DTheta2"};
//	vector<char*> legNames = {"GT1DPhi4DTheta2","GT2DPhi4DTheta2","GT3DPhi4DTheta2","GT4DPhi4DTheta2","GT5DPhi4DTheta2"};
	
	
	vector<char*> sigNames = {"sigGT1HITS","sigGT2HITS","sigGT3HITS","sigGT4HITS","sigGT5HITS"};
	vector<char*> bckgNames = {"bckgGT1HITS","bckgGT2HITS","bckgGT3HITS","bckgGT4HITS","bckgGT5HITS"};
	vector<char*> legNames = {"GT1HITS","GT2HITS","GT3HITS","GT4HITS","GT5HITS"};
	
	
//	vector<char*> sigNames = {"sigGT1noCutVertexZ","sigGT2noCutVertexZ","sigGT3noCutVertexZ","sigGT4noCutVertexZ","sigGT5noCutVertexZ"};
//	vector<char*> bckgNames = {"bckgGT1noCutVertexZ","bckgGT2noCutVertexZ","bckgGT3noCutVertexZ","bckgGT4noCutVertexZ","bckgGT5noCutVertexZ"};
//	vector<char*> legNames = {"GT1noCutVertexZ","GT2noCutVertexZ","GT3noCutVertexZ","GT4noCutVertexZ","GT5noCutVertexZ"};
	
	
	vector<char*> sigNamesNoCut = {"sigGT1noCut","sigGT2noCut","sigGT3noCut","sigGT4noCut","sigGT5noCut"};
	vector<char*> bckgNamesNoCut = {"bckgGT1noCut","bckgGT2noCut","bckgGT3noCut","bckgGT4noCut","bckgGT5noCut"};
	vector<char*> legNamesNoCut = {"GT1noCut","GT2noCut","GT3noCut","GT4noCut","GT5noCut"};
	
	
	char tmpSigName[20];
	char tmpBckgName[20];
	char CFName[20];
	
	TCanvas *c = new TCanvas("c","c",800,800);
	TLegend *leg = new TLegend(0.9,0.65,0.6,0.9);
	TLegend *legNoCut = new TLegend(0.6,0.2,0.9,0.4);
	
	for(int f=0; f<filesNoCut.size(); f++)
	{	
		signalsNoCut.push_back(new TH1D(sigNamesNoCut.at(f),sigNamesNoCut.at(f),1500,0,1500));
		backgroundsNoCut.push_back(new TH1D(bckgNamesNoCut.at(f),bckgNamesNoCut.at(f),1500,0,1500));
		
		for(int i=1; i<10; i++)
		{
			for(int j=1; j<10; j++)
			{
				sprintf(tmpSigName, "PimSig_%d%d",i,j);
				sprintf(tmpBckgName, "PimBckg_%d%d",i,j);
				
				TH1D* tmpSigExp = (TH1D*)filesNoCut.at(f)->Get(tmpSigName);
				TH1D* tmpBckgExp = (TH1D*)filesNoCut.at(f)->Get(tmpBckgName);
				
				if(tmpSigExp)
				{
				//	cout<<sigExp->GetNbinsX()<<" "<<tempSigExp->GetNbinsX()<<endl;
					signalsNoCut.at(f)->Add(tmpSigExp);
					backgroundsNoCut.at(f)->Add(tmpBckgExp);
					
					delete tmpSigExp;
					delete tmpBckgExp;
				}
			}
		}
		signalsNoCut.at(f)->Rebin(5);
		backgroundsNoCut.at(f)->Rebin(5);
		signalsNoCut.at(f)->Sumw2(true);
		backgroundsNoCut.at(f)->Sumw2(true);
		CFNoCut.push_back(signalsNoCut.at(f));
		CFNoCut.at(f)->Divide(backgroundsNoCut.at(f));
		
		int cnt=0;
		double average=0;
		for(int i=CFNoCut.at(f)->FindBin(300); i<=CFNoCut.at(f)->FindBin(350); i++)
		{
			cnt++;
			average+=CFNoCut.at(f)->GetBinContent(i);
		}
		average/=cnt;
		CFNoCut.at(f)->Scale(1/average);
		
		
		sprintf(CFName, "");
		CFNoCut.at(f)->SetNameTitle(CFName,CFName);
		CFNoCut.at(f)->SetLineColor(coloursNoCut.at(f));
		CFNoCut.at(f)->SetMarkerColor(coloursNoCut.at(f));
		CFNoCut.at(f)->GetXaxis()->SetRangeUser(0,400);
		sprintf(CFName, "nTracks #geq %d",f+2);
		legNoCut->AddEntry(CFNoCut.at(f),legNamesNoCut.at(f),"lp");
		
		
		if(f==0)
		{
			CFNoCut.at(f)->GetYaxis()->SetRangeUser(0,2);
			CFNoCut.at(f)->Draw();
			//cout<<CF.at(f)->GetTitle()<<endl;
		}
		else
			CFNoCut.at(f)->Draw("same");

	}
	
	
	
	for(int f=0; f<files.size(); f++)
	{	
		signals.push_back(new TH1D(sigNames.at(f),sigNames.at(f),1500,0,1500));
		backgrounds.push_back(new TH1D(bckgNames.at(f),bckgNames.at(f),1500,0,1500));
		
		for(int i=1; i<10; i++)
		{
			for(int j=1; j<10; j++)
			{
				sprintf(tmpSigName, "PimSig_%d%d",i,j);
				sprintf(tmpBckgName, "PimBckg_%d%d",i,j);
				
				TH1D* tmpSigExp = (TH1D*)files.at(f)->Get(tmpSigName);
				TH1D* tmpBckgExp = (TH1D*)files.at(f)->Get(tmpBckgName);
				
				if(tmpSigExp)
				{
				//	cout<<sigExp->GetNbinsX()<<" "<<tempSigExp->GetNbinsX()<<endl;
					signals.at(f)->Add(tmpSigExp);
					backgrounds.at(f)->Add(tmpBckgExp);
					
					delete tmpSigExp;
					delete tmpBckgExp;
				}
			}
		}
		signals.at(f)->Rebin(5);
		backgrounds.at(f)->Rebin(5);
		signals.at(f)->Sumw2(true);
		backgrounds.at(f)->Sumw2(true);
		CF.push_back(signals.at(f));
		CF.at(f)->Divide(backgrounds.at(f));
		
		int cnt=0;
		double average=0;
		for(int i=CF.at(f)->FindBin(300); i<=CF.at(f)->FindBin(350); i++)
		{
			cnt++;
			average+=CF.at(f)->GetBinContent(i);
		}
		average/=cnt;
		CF.at(f)->Scale(1/average);
		
		
		sprintf(CFName, "");
		CF.at(f)->SetNameTitle(CFName,CFName);
		CF.at(f)->SetLineColor(colours.at(f));
		CF.at(f)->SetMarkerColor(colours.at(f));
		CF.at(f)->GetXaxis()->SetRangeUser(0,400);
		sprintf(CFName, "nTracks #geq %d",f+2);
		leg->AddEntry(CF.at(f),legNames.at(f),"lp");
		
		
		CF.at(f)->GetYaxis()->SetRangeUser(0,2);
		CF.at(f)->Draw("same");

	}
	
	
	
	
	
	
	
	legNoCut->Draw();
	leg->Draw();
	
	
	
	
	
	return 0;
}