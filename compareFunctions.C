

int compareFunctions()
{
	gStyle->SetOptStat(0000);

	TFile *smashWireDistance3VertexzMetahits = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
	TFile *smashWireDistance3VertexzRMetahits = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
	TFile *smashWireDistance4VertexzRMetahits = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitsMix_wireDistanceGT4AllLayersNoSharedMeta_50k_gen4.root ","read");

	
//	TFile *smashWireDistanceGT0NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT0NoSharedMetaAllLayers_fullstat_gen4.root","read");
//	TFile *smashWireDistanceGT1NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT1NoSharedMetaAllLayers_fullstat_gen4.root","read");
//	TFile *smashWireDistanceGT2NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT2NoSharedMetaAllLayers_fullstat_gen4.root","read");
//	TFile *smashWireDistanceGT3NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT3NoSharedMetaAllLayers_fullstat_gen4.root","read");
//	TFile *smashWireDistanceGT4NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root","read");
	
	TFile *smashWireDistanceGT0NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT0NoSharedMetaAllLayers_50k_gen4.root","read");
	TFile *smashWireDistanceGT1NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT1NoSharedMetaAllLayers_50k_gen4.root","read");
	TFile *smashWireDistanceGT2NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT2NoSharedMetaAllLayers_50k_gen4.root","read");
	TFile *smashWireDistanceGT3NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT3NoSharedMetaAllLayers_50k_gen4.root","read");
	TFile *smashWireDistanceGT4NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_50k_gen4.root","read");
	TFile *smashWireDistanceGT5NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT5NoSharedMetaAllLayers_50k_gen4.root","read");
	TFile *smashWireDistanceGT6NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT6NoSharedMetaAllLayers_50k_gen4.root","read");

	
	TFile *smashWireDistanceGT4VertexRadiusnTracks = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitssMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
	TFile *smashWireDistanceGT4VertexRadiusChTracks = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
	TFile *smashWireDistanceGT4VertexChTracks = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");

	TFile *smashVertexZmetaHits = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT4NoSharedMetaAllLayers_50k_gen4.root ","read");
	TFile *smashVertexZchargedTracks = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_50k_gen4.root ","read");
	TFile *smashVertexZchargedTracksWireDistanceAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4AllLayers_50k_gen4.root ","read");


	TFile *pureSmashPipnTracksMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_nTracksMix_nTracksGT1.root","read");
	TFile *pureSmashPipChargedTracksMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_chargedTracksMix_nTracksGT1.root","read");
	TFile *pureSmashPipTotalChargeMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalChargeMix_nTracksGT1.root","read");
	TFile *pureSmashPipTotalPositiveChargeMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalPositiveChargeMix_nTracksGT1.root","read");
	TFile *pureSmashPipTotalPositiveAndNegativeMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_TotalPositiveAndNegativeChargeMix_nTracksGT1.root","read");
	TFile *pureSmashPipnPipMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_nPipMix_nTracksGT1.root","read");
	TFile *pureSmashPipnPipnPimMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_positiveAndNegativePionsMix_nTracksGT1.root","read");
	TFile *pureSmashPipTotalMomentumMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalMomentumMix_nTracksGT1.root","read");
	TFile *pureSmashPipTotalMomentumChargedTracksMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalMomentumAndChargedTracksMix_nTracksGT1.root","read");
	TFile *pureSmashPipTotalKtAndRapidityMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalKtAndRapidityMix_nTracksGT1.root","read");
	TFile *pureSmashPipTotalKtMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalKtMix_nTracksGT1.root","read");
	TFile *pureSmashPipTotalRapidityMix = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalRapidityMix_nTracksGT1.root","read");
	TFile *pureSmashPipChargedTracksMixGT5 = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_nChargedTracksMix_nTracksGT5.root","read");
	TFile *pureSmashPipNumberOfTracksMixGT5 = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_nTracksMix_nTracksGT5.root","read");
	
	
	TFile *pureSmashPimChargedTraksMixGT1 = new TFile("./jobs/smash/pureSmash_pim_analysis4.5GeV_buffer20_nChargedTracksMix_nTracksGT1.root","read");
	TFile *pureSmashPimNumberOfTracksMixGT1 = new TFile("./jobs/smash/pureSmash_pim_analysis4.5GeV_buffer20_nTracksMix_nTracksGT1.root","read");


	TFile *expWireDistanceGT6nTracksGT1 = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmChargedTracksMix_WireDistanceGT6NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");
	TFile *expWireDistanceGT6nTracksGT5 = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmChargedTracksMix_WireDistanceGT6NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");
	
	TFile *simWireDistanceGT4nTracksGT1 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_50k_gen4.root","read");
	TFile *simWireDistanceGT4nTracksGT5 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_50k_gen4.root","read");
	
	TFile *expRadiusMixWireDistanceGT4nTracksGT1 = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");
	TFile *expRadiusMixWireDistanceGT4nTracksGT5 = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");
	
	TFile* pipGT1 = new TFile("./jobs/wires/analysisPip_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","red");
	TFile* pipGT5 = new TFile("./jobs/wires/analysisPip_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","red");



//	vector<TFile *> files = {metaHit,vertexZ,avMom,avEne};
//	vector<TFile *> files = {metaHit,vertexZ,avMom,avEne};
//	vector<TFile *> files = {nTracksGT5SameSectorNoSharedWires,nTracksGT5SameSector};
//	vector<TFile *> files = {vertexZmix,noEventHash,metaMix,energyMix,momentumMix};
//	vector<TFile *> files = {sector0,sector1,sector2,sector3,sector4,sector5};
//	vector<TFile *> files = {urqmdFileGT1, urqmdFileGT5, smashFileGT1, smashFileGT5};
//	vector<TFile *> files = {smashWireDistance3VertexzMetahits, smashWireDistance3VertexzRMetahits};
//	vector<TFile *> files = {smashVertexZchargedTracks, smashVertexZchargedTracksWireDistanceAllLayers};
/*	vector<TFile *> files = {pureSmashPipnTracksMix, pureSmashPipChargedTracksMix, pureSmashPipTotalChargeMix, pureSmashPipTotalPositiveChargeMix, 
							 pureSmashPipTotalPositiveAndNegativeMix, pureSmashPipnPipMix, pureSmashPipnPipnPimMix, pureSmashPipTotalMomentumMix, 
							 pureSmashPipTotalMomentumChargedTracksMix, pureSmashPipTotalKtAndRapidityMix, pureSmashPipTotalKtMix, pureSmashPipTotalRapidityMix,
							 pureSmashPipChargedTracksMixGT5, pureSmashPipNumberOfTracksMixGT5};
							 */
							 
/*	vector<TFile *> files = {smashWireDistanceGT0NoSharedMetaAllLayers,smashWireDistanceGT1NoSharedMetaAllLayers,smashWireDistanceGT2NoSharedMetaAllLayers,
							 smashWireDistanceGT3NoSharedMetaAllLayers,smashWireDistanceGT4NoSharedMetaAllLayers, smashWireDistanceGT5NoSharedMetaAllLayers, 
							 smashWireDistanceGT6NoSharedMetaAllLayers};*/
//	vector<TFile *> files = {differentSectorsSmash, sharedWiresLT1Smash, wireDistanceGT0Smash, wireDistanceGT1Smash, wireDistanceGT2Smash, wireDistanceGT3Smash, wireDistanceGT4Smash, wireDistanceGT10Smash};
//	vector<TFile *> files = {nTracksGT5WireDistanceGT0Smash, nTracksGT5WireDistanceGT3Smash, wireDistanceGT0Smash, wireDistanceGT3Smash};
	vector<TFile *> files = {pipGT1, pipGT5};
	vector<TH1D *> signals = {};
	vector<TH1D *> backgrounds = {};
	vector<TH1D *> CF = {};
	vector<int> colors = {kBlue+1, kRed, kMagenta+1, kGreen+1, kCyan+2, kYellow-2, kViolet+2, kBlue-9, kRed-3, kPink+10, kPink-7, kViolet+3, kBlue-5, kCyan-2};
	
//	vector<char*> sigNames = {"sigsector0", "sigsector1","sigsector2","sigsector3","sigsector4","sigsector5"};
//	vector<char*> sigNames = {"sigUrqmdGT1", "sigUrqmdGT5", "sigSmashGT1", "sigSmashGT5"};
	vector<char*> sigNames = {"sig1","sig2","sig3","sig4","sig5","sig6","sig7","sig8","sig9","sig10","sig11","sig12","sig13","sig14"};
//	vector<char*> sigNames = {"sigDifferentSectorsSmash", "sigwireslt1", "wireDistanceGT0Smash", "wireDistanceGT1Smash", "wireDistanceGT2Smash", "wireDistanceGT3Smash", "wireDistanceGT4Smash", "wireDistanceGT10Smash"};
//	vector<char*> sigNames = {"signTracksGT1Rotate60", "signTracksGT1Rotate180", "signTracksGT5Rotate60", "signTracksGT5RotateRandom"};
//	vector<char*> bckgNames = {"bckgsector0","bckgsector1","bckgsector2","bckgsector3","bckgsector4","bckgsector5"};
//	vector<char*> bckgNames = {"bckgUrqmdGT1", "bckgUrqmdGT5", "bckgSmashGT1", "bckgSmashGT5"};
	vector<char*> bckgNames = {"bckg1", "bckg2","bckg3","bckg4","bckg5","bckg6","bkg7","bckg8","bckg9","bckg10","bckg11","bckg12","bckg13","bckg14"};
//	vector<char*> bckgNames = {"bckgDifferentSectorsSmash", "bckgwireslt1", "bckgWireDistanceGT0Smash", "bckgWireDistanceGT1Smash", "bckgWireDistanceGT2Smash", "bckgWireDistanceGT3Smash", "bckgWireDistanceGT4Smash", "bckgWireDistanceGT10Smash"};
//	vector<char*> bckgNames = {"bckgnTracksGT1Rotate60", "bckgnTracksGT1Rotate180", "bckgnTracksGT5Rotate60", "bckgnTracksGT5RotateRandom"};
//	vector<char*> legNames = {"sector0","sector1","sector2","sector3","sector4","sector5"};
//	vector<char*> legNames = {"nTracksGT1 UrQMD", "nTracksGT5 UrQMD", "nTracksGT1 SMASH", "nTracksGT5 SMASH"};
//	vector<char*> legNames = {"nTracksMix", "chargedTracksMix"};
/*	vector<char*> legNames = {"nTracks mix", "charged tracks mix", "total charge mix", "total positive charge mix", "total positive and negative charge mix", "nPip", 
							  "nPip nPim", "total momentum","totalMomentum chargedTracks","totalKt totalRapidity","totalKt","totalRapidity","chargedTracks nTracksGT5",
							   "nTracksMix nTracksGT5"};*/
//	vector<char*> legNames = {"wireDistanceGT0", "wireDistanceGT1", "wireDistanceGT2", "wireDistanceGT3", "wireDistanceGT4", "wireDistanceGT5", "wireDistanceGT6"};
	vector<char*> legNames = {"nTracksGT1", "nTracksGT5"};
							   
//	vector<char*> legNames = {"wire distance GT0","wire distance GT1","wire distance GT2","wire distance GT3","wire distance GT4"};
//	vector<char*> legNames = {"different sectors", "no shared wires", "wire distance GT0", "wire distance GT1", "wire distance GT2", "wire distance GT3", "wire distance GT4", "wire distance GT10"};
//	vector<char*> legNames = {"nTracksGT5WireDistanceGT0Smash", "nTracksGT5WireDistanceGT3Smash", "nTracksGT0WireDistanceGT0Smash", "nTracksGT0WireDistanceGT3Smash"};
//	vector<char*> legNames = {"ntracksGT1 rotate 60", "nTracksGT1 rotate 180", "ntracksGT5 rotate 60", "nTracksGT5 rotate random	"};
	
	TH1D *hEntries = new TH1D("entriesInSector","entriesInSector", files.size(),0,files.size());
	
	char tmpSigName[20];
	char tmpBckgName[20];
	char CFName[20];
	TPaveText *t = new TPaveText(250,1.6,400,1.8);
	t->SetTextAlign(12); // left horizontally, centered vertically
	t->AddText("p+p at #sqrt{s} = 3.46 GeV");
	t->AddText("HADES work in progress");
//	t->AddText("Raw correlation function");
//	t->AddText("No shared wires");
//	t->AddText("nTrack#geq 6");
	t->SetBorderSize(0);
	t->SetFillStyle(0);
	
	TCanvas *c = new TCanvas("c","c",800,800);	
	TCanvas *cNom = new TCanvas("cNom","cNom", 800, 800);
	TCanvas *cDen = new TCanvas("cDen","cDen", 800, 800);
	
	TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
	
	for(int f=0; f<files.size(); f++)
	{	
		
		signals.push_back(new TH1D(sigNames.at(f),sigNames.at(f),1500,0,1500));
		backgrounds.push_back(new TH1D(bckgNames.at(f),bckgNames.at(f),1500,0,1500));
		signals.at(f)->Sumw2(true);
		backgrounds.at(f)->Sumw2(true);
		
		for(int i=1; i<10; i++)
		{
			for(int j=1; j<10; j++)
			{
				if(std::string(files.at(f)->GetName()).find("Pim")!=string::npos || std::string(files.at(f)->GetName()).find("pim")!=string::npos)
				{
					sprintf(tmpSigName, "PimSig_%d%d",i,j);
					sprintf(tmpBckgName, "PimBckg_%d%d",i,j);
				}
				else if(std::string(files.at(f)->GetName()).find("Pip")!=string::npos || std::string(files.at(f)->GetName()).find("pip")!=string::npos)
				{
					sprintf(tmpSigName, "PipSig_%d%d",i,j);
					sprintf(tmpBckgName, "PipBckg_%d%d",i,j);
				}
				else
				{
					sprintf(tmpSigName, "PimSig_%d%d",i,j);
					sprintf(tmpBckgName, "PimBckg_%d%d",i,j);	
				}
				
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
		hEntries->SetBinContent(f+1, signals.at(f)->GetEntries());
		cout<<signals.at(f)->GetName()<<" "<<signals.at(f)->GetEntries()<<endl;
		signals.at(f)->Rebin(15);
		backgrounds.at(f)->Rebin(15);
		CF.push_back(new TH1D(*signals.at(f)));
		CF.at(f)->Divide(backgrounds.at(f));
		
		
		int cnt=0;
		double average=0;
		for(int i=CF.at(f)->FindBin(250); i<=CF.at(f)->FindBin(350); i++)
		{
			cnt++;
			average+=CF.at(f)->GetBinContent(i);
		}
		average/=cnt;
		CF.at(f)->Scale(1/average);
		
		
		sprintf(CFName, "");
		CF.at(f)->SetNameTitle(CFName,CFName);
		CF.at(f)->SetLineColor(colors.at(f));
		CF.at(f)->SetMarkerColor(colors.at(f));
		CF.at(f)->GetXaxis()->SetRangeUser(0,400);
		CF.at(f)->SetLineWidth(2);
		CF.at(f)->SetMarkerStyle(8);
		CF.at(f)->SetMarkerSize(0.7);
		CF.at(f)->SetMarkerColor(colors.at(f));
		CF.at(f)->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
		CF.at(f)->GetYaxis()->SetTitle("CF");
		sprintf(CFName, "nTracks #geq %d",f+2);
		leg->AddEntry(CF.at(f),legNames.at(f),"lp");
		
		signals.at(f)->SetLineColor(colors.at(f));
		signals.at(f)->SetMarkerColor(colors.at(f));
		backgrounds.at(f)->SetLineColor(colors.at(f));
		backgrounds.at(f)->SetMarkerColor(colors.at(f));
	
		if(f==0)
		{
			c->cd();
			CF.at(f)->GetYaxis()->SetRangeUser(0,2);
			CF.at(f)->Draw();
			//cout<<CF.at(f)->GetTitle()<<endl;
			cNom->cd();
			signals.at(f)->Scale(1/signals.at(f)->Integral());
			signals.at(f)->Draw();
			cDen->cd();
			backgrounds.at(f)->Scale(1/backgrounds.at(f)->Integral());
			backgrounds.at(f)->Draw();
		}
		else
		{
			c->cd();
			CF.at(f)->Draw("same");
			cNom->cd();
			signals.at(f)->Scale(1/signals.at(f)->Integral());
			signals.at(f)->Draw("same");
			cDen->cd();
			backgrounds.at(f)->Scale(1/backgrounds.at(f)->Integral());
			backgrounds.at(f)->Draw("same");
		}
	}
	
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
	c->cd();
	leg->Draw();
	TLine *line = new TLine(0.02,1,400,1);
	line->SetLineColor(kAzure-3);
	line->SetLineStyle(9);
	line->Draw();
//	t->Draw();
	cNom->cd();
	leg->Draw();
	cDen->cd();
	leg->Draw();
	
	
	
	TCanvas *cEntries = new TCanvas("cEntries","cEntries",800,800);
	hEntries->Draw();
	
	return 0;
}