

int compareFunctions()
{
	gStyle->SetOptStat(0000);
	
	/*
	TFile *GT1NoCut= new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_NOCUT.root","read");
	TFile *GT1Hits = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS.root","read");
	TFile *GT1DPhi4_DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_DPhi4DTheta2.root","read");
	TFile *GT1HitsTopology = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY.root","read");
	TFile *GT1HitsDPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_DPhi4_DTheta2.root","read");
	TFile *GT1HitsTopologyDPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	TFile *GT1HitsTopologyDPhi10DTheta5 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DPhi10_DTheta5.root","read");
	TFile *GT1HitsTopologyDCA2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DCA2.root","read");
	TFile *GT1DPhi4Theta2VertexZ = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_DPhi4_DTheta2.root","read");
	
	TFile *GT2HitsTopologyDPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	TFile *GT3HitsTopologyDPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	TFile *GT4HitsTopologyDPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	TFile *GT5HitsTopologyDPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
	
	TFile *GT1DPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_DPhi4_DTheta2.root","read");
	TFile *GT2DPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_VertexZ_DPhi4_DTheta2.root","read");
	TFile *GT3DPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_VertexZ_DPhi4_DTheta2.root","read");
	TFile *GT4DPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_VertexZ_DPhi4_DTheta2.root","read");
	TFile *GT5DPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_VertexZ_DPhi4_DTheta2.root","read");
	
	TFile *GT1HITS = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_HITS.root","read");
	TFile *GT2HITS = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_VertexZ_HITS.root","read");
	TFile *GT3HITS = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_VertexZ_HITS.root","read");
	TFile *GT4HITS = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_VertexZ_HITS.root","read");
	TFile *GT5HITS = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_VertexZ_HITS.root","read");
	
	TFile *GT1TOPOLOGY = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_TOPOLOGY.root","read");
	TFile *GT2TOPOLOGY = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_TOPOLOGY.root","read");
	TFile *GT3TOPOLOGY = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_TOPOLOGY.root","read");
	TFile *GT4TOPOLOGY = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_TOPOLOGY.root","read");
	TFile *GT5TOPOLOGY = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_TOPOLOGY.root","read");
	
	TFile *GT1noCutVertexZ = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_noCut.root","read");
	TFile *GT2noCutVertexZ = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_VertexZ_noCut.root","read");
	TFile *GT3noCutVertexZ = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_VertexZ_noCut.root","read");
	TFile *GT4noCutVertexZ = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_VertexZ_noCut.root","read");
	TFile *GT5noCutVertexZ = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_VertexZ_noCut.root","read");
	
	TFile *GT1noCut = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_noCut.root","read");
	TFile *GT2noCut = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT2_noCut.root","read");
	TFile *GT3noCut = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT3_noCut.root","read");
	TFile *GT4noCut = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT4_noCut.root","read");
	TFile *GT5noCut = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_noCut.root","read");
	*/
	
//	TFile *GT0NoCutNoHash = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_HarshVertexCut_nTracksGT0_noCut_noHash.root","read");
//	TFile *GT1HarshVertexCutVertexZmixDPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmVertexX5mm_DPhi4_DTheta2.root","read");
	
//	TFile *PureSmashNoCutNoHash = new TFile("./jobs/smash/analysisPureKinePim_noCut_noHash.root","read");
	
//	TFile *analysisWiresBuffer10nTracksGT1HarshVertexCutVertexZ3mmMix500MomEnePimMomLT1500GT100SharedWiresLT1NoSharedMetaSignals = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_100mom1500_SharedWiresLT1NoSharedMetaSameSector_100k.root", "read");
//	TFile *analysisWiresBuffer10nTracksGT1HarshVertexCutVertexZ3mmMix500MomEneSharedWiresLT1NoSharedMetaSignals = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *idealBackground = new TFile("./jobs/smash/idealBackground_hgeantkine_noEventSelection_pxpyrotation.root","read");





/*	TFile *PureSmashNoCutPairHash = new TFile("./jobs/smash/analysisPureKinePim_noCut_PairHash.root","read");
	TFile *PureSmashNoCutEventHash = new TFile("./jobs/smash/analysisPureKinePim_noCut_EventHash.root","read");
	TFile *PureSmashNoCutBothHash = new TFile("./jobs/smash/analysisPureKinePim_noCut_BothHash.root","read");
	
	TFile *UrQMDNoCuNoHash = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_noHash.root","read");
	TFile *UrQMDNoCutPairHash = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_PairHash.root","read");
	TFile *UrQMDNoCutEventHash = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_EventHash.root","read");
	TFile *UrQMDNoCutBothHash = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_BothHash.root","read");
	
	
	TFile *PureSmashAgAGNoCutNoHash = new TFile("./jobs/smash/analysisAgAgPureKinePim_noCut_noHash.root","read");
	TFile *PureSmashAgAGNoCutPairHash = new TFile("./jobs/smash/analysisAgAgPureKinePim_noCut_PairHash.root","read");
	TFile *PureSmashAgAGNoCutEventHash = new TFile("./jobs/smash/analysisAgAgPureKinePim_noCut_EventCentralityPlateHash.root","read");
	TFile *PureSmashAgAGNoCutBothHash = new TFile("./jobs/smash/analysisAgAgPureKinePim_noCut_BothHash.root","read");


	TFile *ExpnTracksGT1DPhi4DTheta2 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_DPhi4_DTheta2_NEWMACRO.root","read");
	TFile *ExpnTracksGT1VerticesDPhi4DTheta2 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_fullstat.root","read");


	TFile *ExpnTracksGT5DPhi4DTheta2 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_DPhi4_DTheta2_NEWMACRO.root","read");
	TFile *ExpnTracksGT5VerticesDPhi4DTheta2 = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_HarshVertexCut_VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_fullstat.root","read");
	
	TFile *SmashGT1HarshVertexCutDPhi4DTheta2HitsRejectPimPimP = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_HarshVertexCut_nTracksGT1_-1VertexZ3mm_DPhi4_DTheta2_sharedHitsRejectionPimPipP.root","read");
	TFile *SmashGT1HarshVertexCutDPhi4DTheta2 = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmVertexX5mm_DPhi4_DTheta2.root","read");

	*/
/*

	TFile *metaHit = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
	TFile *vertexZ = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_VertexZQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
	TFile *avMom = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_averageMomentumQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
	TFile *avEne = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_averageEnergyQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
	
	TFile *vertexZMetaHitQ = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ5MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
	TFile *vertexZMetaHit = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ1.5mmMetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
	
	TFile *vertexZMetaHitQBeamTitlCorr = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ5MetaHitsQuantiles_beamTiltCorrection_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
	

	TFile *beamTilt = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_fullstat.root","read");
	TFile *beamTiltNoGoodEvent = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_fullstat.root","read");

	TFile *nTracksGT5SameSectorNoSharedWires = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1SameSector_beamTiltCorr_fullstat.root","read");
	TFile *nTracksGT5SameSector = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
	
	TFile *vertexZmix = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
	TFile *noEventHash = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_NoEventHashing_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
	TFile *metaMix = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_MetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
	TFile *energyMix = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_TotalEnergy200MeVMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
	TFile *momentumMix = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_TotalMomentum200MeVMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
	*/
	TFile *sector0 = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector0Pairs_beamTiltCorr_gen4_50k.root","read");
	TFile *sector1 = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector1Pairs_beamTiltCorr_gen4_50k.root","read");
	TFile *sector2 = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector2Pairs_beamTiltCorr_gen4_50k.root","read");
	TFile *sector3 = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector3Pairs_beamTiltCorr_gen4_50k.root","read");
	TFile *sector4 = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector4Pairs_beamTiltCorr_gen4_50k.root","read");
	TFile *sector5 = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector5Pairs_beamTiltCorr_gen4_50k.root","read");
	
	
	TFile *noCheckWires = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT0_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_NoPairCut_beamTiltCorr_gen4_50k.root","read");
	TFile *sharedWiresLT2 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT0_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
	TFile *sharedWiresLT1 = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
	
	TFile *sharedWiresLT1Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMetaSameSector_20k_gen4.root","read");

	TFile *wireDistanceGT1SmashSameSector = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT1AllLayersNoSharedMetaSameSector_20k_gen4.root ","read");
	TFile *wireDistanceGT2SmashSameSector = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT2AllLayersNoSharedMetaSameSector_20k_gen4.root ","read");
	TFile *wireDistanceGT3SmashSameSector = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMetaSameSector_20k_gen4.root ","read");
	TFile *wireDistanceGT4SmashSameSector = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT4AllLayersNoSharedMetaSameSector_20k_gen4.root ","read");

	TFile *wireDistanceGT0Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT0AllLayersNoSharedMeta_20k_gen4.root ","read");
	TFile *wireDistanceGT1Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT1AllLayersNoSharedMeta_20k_gen4.root ","read");
	TFile *wireDistanceGT2Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT2AllLayersNoSharedMeta_20k_gen4.root ","read");
	TFile *wireDistanceGT3Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");
	TFile *wireDistanceGT4Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT4AllLayersNoSharedMeta_20k_gen4.root ","read");
	TFile *wireDistanceGT10Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT10AllLayersNoSharedMeta_20k_gen4.root ","read");
	
	TFile *nTracksGT5WireDistanceGT3Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");
	TFile *nTracksGT5WireDistanceGT0Smash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT0AllLayersNoSharedMeta_20k_gen4.root ","read");


	TFile *differentSectorsSmash = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_AllLayersDifferentSectors_20k_gen4.root","read");

	
	
//	TFile *sector0 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector0Pairs_40k_gen4.root ","read");
//	TFile *sector1 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector1Pairs_40k_gen4.root ","read");
//	TFile *sector2 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector2Pairs_40k_gen4.root ","read");
//	TFile *sector3 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector3Pairs_40k_gen4.root ","read");
//	TFile *sector4 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector4Pairs_40k_gen4.root ","read");
//	TFile *sector5 = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector5Pairs_40k_gen4.root ","read");

//	TFile *sector0Wires = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector0SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *sector1Wires = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector1SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *sector2Wires = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector2SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *sector3Wires = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector3SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *sector4Wires = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector4SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *sector5Wires = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector5SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");


	TFile *nTracksGT1Rotate60Smash = new TFile("./jobs/smash/analysisSmashPim_rotatedBackground60deg_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_50k_gen4.root ","read");
	TFile *nTracksGT1Rotate180Smash = new TFile("./jobs/smash/analysisSmashPim_rotatedBackground180deg_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_50k_gen4.root ","read");
	TFile *nTracksGT5Rotate60Smash = new TFile("./jobs/smash/analysisSmashPim_rotatedBackground60deg_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_50k_gen4.root ","read");
	TFile *nTracksGT5RotateRandomFrom0To360Smash = new TFile("./jobs/smash/analysisSmashPim_rotatedBackgroundRandomFrom0To360deg_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_50k_gen4.root ","read");



	TFile *smashFileGT1 = new TFile("./jobs/smash/analysisPureKinePim_nRealTracksGT1_noCut_nTracksEventHash_kTyPairHash.root ","read");
	TFile *smashFileGT5 = new TFile("./jobs/smash/analysisPureKinePim_nRealTracksGT5_noCut_nTracksEventHash_kTyPairHash.root ","read");
	TFile *urqmdFileGT1 = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_buffer20_nTracksMix_nTracksGT1.root ","read");
	TFile *urqmdFileGT5 = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_buffer20_nTracksMix_nTracksGT5.root ","read");
	
	TFile *smashWireDistance3VertexzMetahits = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
	TFile *smashWireDistance3VertexzRMetahits = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
	TFile *smashWireDistance4VertexzRMetahits = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitsMix_wireDistanceGT4AllLayersNoSharedMeta_50k_gen4.root ","read");

	
	TFile *smashWireDistanceGT0NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT0NoSharedMetaAllLayers_fullstat_gen4.root","read");
	TFile *smashWireDistanceGT1NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT1NoSharedMetaAllLayers_fullstat_gen4.root","read");
	TFile *smashWireDistanceGT2NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT2NoSharedMetaAllLayers_fullstat_gen4.root","read");
	TFile *smashWireDistanceGT3NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT3NoSharedMetaAllLayers_fullstat_gen4.root","read");
	TFile *smashWireDistanceGT4NoSharedMetaAllLayers = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root","read");
	
	TFile *smashWireDistanceGT4nTracks = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitssMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
	TFile *smashWireDistanceGT4ChTracks = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");



//	vector<TFile *> files = {metaHit,vertexZ,avMom,avEne};
//	vector<TFile *> files = {metaHit,vertexZ,avMom,avEne};
//	vector<TFile *> files = {nTracksGT5SameSectorNoSharedWires,nTracksGT5SameSector};
//	vector<TFile *> files = {vertexZmix,noEventHash,metaMix,energyMix,momentumMix};
//	vector<TFile *> files = {sector0,sector1,sector2,sector3,sector4,sector5};
//	vector<TFile *> files = {urqmdFileGT1, urqmdFileGT5, smashFileGT1, smashFileGT5};
//	vector<TFile *> files = {smashWireDistance3VertexzMetahits, smashWireDistance3VertexzRMetahits};
	vector<TFile *> files = {smashWireDistanceGT4nTracks, smashWireDistanceGT4ChTracks};
//	vector<TFile *> files = {smashWireDistanceGT0NoSharedMetaAllLayers,smashWireDistanceGT1NoSharedMetaAllLayers,smashWireDistanceGT2NoSharedMetaAllLayers,smashWireDistanceGT3NoSharedMetaAllLayers,smashWireDistanceGT4NoSharedMetaAllLayers};
//	vector<TFile *> files = {differentSectorsSmash, sharedWiresLT1Smash, wireDistanceGT0Smash, wireDistanceGT1Smash, wireDistanceGT2Smash, wireDistanceGT3Smash, wireDistanceGT4Smash, wireDistanceGT10Smash};
//	vector<TFile *> files = {nTracksGT5WireDistanceGT0Smash, nTracksGT5WireDistanceGT3Smash, wireDistanceGT0Smash, wireDistanceGT3Smash};
//	vector<TFile *> files = {nTracksGT1Rotate60Smash, nTracksGT1Rotate180Smash, nTracksGT5Rotate60Smash, nTracksGT5RotateRandomFrom0To360Smash};
	vector<TH1D *> signals = {};
	vector<TH1D *> backgrounds = {};
	vector<TH1D *> CF = {};
	vector<int> colors = {kBlue+1, kRed, kMagenta+1, kGreen+1, kCyan+2, kYellow-2, kViolet+2, kBlue-9, kRed-3};
	
//	vector<char*> sigNames = {"sigsector0", "sigsector1","sigsector2","sigsector3","sigsector4","sigsector5"};
//	vector<char*> sigNames = {"sigUrqmdGT1", "sigUrqmdGT5", "sigSmashGT1", "sigSmashGT5"};
	vector<char*> sigNames = {"sig1","sig2","sig3","sig4","sig5"};
//	vector<char*> sigNames = {"sigDifferentSectorsSmash", "sigwireslt1", "wireDistanceGT0Smash", "wireDistanceGT1Smash", "wireDistanceGT2Smash", "wireDistanceGT3Smash", "wireDistanceGT4Smash", "wireDistanceGT10Smash"};
//	vector<char*> sigNames = {"signTracksGT1Rotate60", "signTracksGT1Rotate180", "signTracksGT5Rotate60", "signTracksGT5RotateRandom"};
//	vector<char*> bckgNames = {"bckgsector0","bckgsector1","bckgsector2","bckgsector3","bckgsector4","bckgsector5"};
//	vector<char*> bckgNames = {"bckgUrqmdGT1", "bckgUrqmdGT5", "bckgSmashGT1", "bckgSmashGT5"};
	vector<char*> bckgNames = {"bckg1", "bckg2","bckg3","bckg4","bckg5"};
//	vector<char*> bckgNames = {"bckgDifferentSectorsSmash", "bckgwireslt1", "bckgWireDistanceGT0Smash", "bckgWireDistanceGT1Smash", "bckgWireDistanceGT2Smash", "bckgWireDistanceGT3Smash", "bckgWireDistanceGT4Smash", "bckgWireDistanceGT10Smash"};
//	vector<char*> bckgNames = {"bckgnTracksGT1Rotate60", "bckgnTracksGT1Rotate180", "bckgnTracksGT5Rotate60", "bckgnTracksGT5RotateRandom"};
//	vector<char*> legNames = {"sector0","sector1","sector2","sector3","sector4","sector5"};
//	vector<char*> legNames = {"nTracksGT1 UrQMD", "nTracksGT5 UrQMD", "nTracksGT1 SMASH", "nTracksGT5 SMASH"};
	vector<char*> legNames = {"wire distance GT4 nTracks", "wire distance GT4 chargedTracks"};
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
		hEntries->SetBinContent(f+1, signals.at(f)->GetEntries());
		cout<<signals.at(f)->GetName()<<" "<<signals.at(f)->GetEntries()<<endl;
		signals.at(f)->Rebin(10);
		backgrounds.at(f)->Rebin(10);
		signals.at(f)->Sumw2(true);
		backgrounds.at(f)->Sumw2(true);
		CF.push_back(new TH1D(*signals.at(f)));
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
	t->Draw();
	cNom->cd();
	leg->Draw();
	cDen->cd();
	leg->Draw();
	
	
	
	TCanvas *cEntries = new TCanvas("cEntries","cEntries",800,800);
	hEntries->Draw();
	
	return 0;
}