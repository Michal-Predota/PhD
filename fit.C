
#include "TMath.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TF1.h"

//TFile *coulomb = new TFile("./coulombs_LCMS_smallR.root","read");
//TFile *coulomb = new TFile("./coulomb_1_2_fm.root","read");
TFile *coulomb = new TFile("./coulomb_1_2_fm_LCMS.root","read");
	
//TH1D *coulombCorrection = (TH1D*)coulomb->Get("Coulomb_R_0.680000");
TH1D *coulombCorrection = (TH1D*)coulomb->Get("Coulomb_R_1.000000");


double coulombGausFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+gaus));//pars[0]-lambda, pars[1]-R, pars[2]-normalization
}


double coulombQuadraticGausFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	//if(x[0]<0.4)
	//	return pars[2]*(1-pars[0]+pars[0]*kF*(1+gaus));//pars[0]-lambda, pars[1]-R, pars[2]-normalization
	//else	
		return pars[2]*(1-pars[0]+pars[0]*kF*(1+gaus))+(pars[3]*x[0]*x[0]+pars[4]*x[0]+pars[5]);//pars[0]-lambda, pars[1]-R, pars[2]-normalization, ax^2+bx+c
}


double coulombLinearGausFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+gaus))+(pars[3]*x[0]+pars[4]);//pars[0]-lambda, pars[1]-R, pars[2]-normalization, ax+b
}


double coulombExpFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+exp));//pars[0]-lambda, pars[1]-R, pars[2]-normalization
}



double coulombQuadraticExpFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+exp))+(pars[3]*x[0]*x[0]+pars[4]*x[0]+pars[5]);//pars[0]-lambda, pars[1]-R, pars[2]-normalization, ax^2+bx+c
}



double coulombLinearExpFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*(1-pars[0]+pars[0]*kF*(1+exp))+(pars[3]*x[0]+pars[4]);//pars[0]-lambda, pars[1]-R, pars[2]-normalization, ax+b
}



double gausFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	
	return pars[2]*(1+pars[0]*gaus);//pars[0]-lambda, pars[1]-R, pars[2]-normalization
}


double expFit(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double exp = TMath::Exp(-pars[1]*x[0]*scale);
	
	return pars[2]*(1+pars[0]*exp);//pars[0]-lambda, pars[1]-R, pars[2]-normalization
}


double hermite3(double x)
{
	return 8*x*x*x - 12*x;
}

double hermite4(double x)
{
	return 16*x*x*x*x-48*x*x+12;
}

double hermite5(double x)
{
	return 32*x*x*x*x*x-160*x*x*x+120*x;
}	

double hermite6(double x)
{
	return 64*x*x*x*x*x*x-480*x*x*x*x+720*x*x-120;
}

double hermite8(double x)
{
	return 256*x*x*x*x*x*x*x*x-3584*x*x*x*x*x*x+13440*x*x*x*x-13440*x*x+1680;
}

double hermite10(double x)
{
	return 1024*x*x*x*x*x*x*x*x*x*x-23040*x*x*x*x*x*x*x*x+161280*x*x*x*x*x*x-403200*x*x*x*x+302400*x*x-30240;
}


double modifiedGausFitHermiteUpTo10(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(4 * 4*3*2)*hermite4(x[0]*pars[1]*scale) +
														   pars[4]/(8 * 6*5*4*3*2)*hermite6(x[0]*pars[1]*scale)+
														   pars[5]/(16 * 8*7*6*5*4*3*2)*hermite8(x[0]*pars[1]*scale)+
														   pars[6]/(32 * 10*9*8*7*6*5*4*3*2)*hermite10(x[0]*pars[1]*scale)));
	
}

double modifiedGausFitHermiteUpTo6(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(4 * 4*3*2)*hermite4(x[0]*pars[1]*scale) +
														   pars[4]/(8 * 6*5*4*3*2)*hermite6(x[0]*pars[1]*scale)));
	
}

double modifiedGausFitHermiteUpTo4(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(4 * 4*3*2)*hermite4(x[0]*pars[1]*scale)));
}


double hermiteFitFrom3To4(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(3*2*1)*hermite3(TMath::Sqrt(2)*x[0]*pars[1]*scale) +
																	pars[4]/(4*3*2*1)*hermite4(TMath::Sqrt(2)*x[0]*pars[1]*scale)));
}


double hermiteFitFrom3To6(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(3*2*1)*hermite3(TMath::Sqrt(2)*x[0]*pars[1]*scale) +
																	pars[4]/(4*3*2*1)*hermite4(TMath::Sqrt(2)*x[0]*pars[1]*scale) +
																	pars[5]/(5*4*3*2*1)*hermite5(TMath::Sqrt(2)*x[0]*pars[1]*scale) +
																	pars[6]/(6*5*4*3*2*1)*hermite6(TMath::Sqrt(2)*x[0]*pars[1]*scale)));
}


double hermiteFitOnlyH4(const double *x, const double *pars)
{
	double scale = 5.068;
	double gaus = TMath::Exp(-pars[1]*pars[1]*x[0]*x[0]*scale*scale);
	double kF = coulombCorrection->GetBinContent(coulombCorrection->FindBin(x[0]));
	
	return pars[2]*((1-pars[0]) + pars[0]*kF + pars[0]*kF*gaus*(1 + pars[3]/(4*3*2*1)*hermite4(TMath::Sqrt(2)*x[0]*pars[1]*scale)));
}

using namespace std;


int fit()
{
	gStyle->SetOptStat(0000);

/*****************experimental p+p********************/

	
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_VertexZ_DPhi4_DTheta2_10k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_LCMS_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_VertexZ_DPhi4_DTheta2_10k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_LCMS_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_LCMS_HITS.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_LCMS_HITS_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5LT11_DPhi4_DTheta2_10k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5LT12_DPhi4_DTheta2_10k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5LT13_DPhi4_DTheta2_10k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5LT21_DPhi4_DTheta2_10k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/unlikeSign_2sigma_noRing_nTracksGT0_LCMS_HITS_50k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/unlikeSign_2sigma_noRing_nTracksGT5_LCMS_HITS.root","read");
//	TFile *f = new TFile("./jobs/LCMS/unlikeSign_2sigma_noRing_nTracksGT1_LCMS_DPhi4_DTheta2_50k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_HarshVertexCut_DPhi4_DTheta2_50k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_HarshVertexCut_DPhi4_DTheta2_10k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_HarshVertexCut_DPhi4_DTheta2_TOPOLOGY_20k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/unlikeSign_2sigma_noRing_nTracksGT1_LCMS_DPhi4_DTheta2_50k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_HarshVertexCut_VertexZ3mmMix_NOCUT.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_HarshVertexCut_VertexZ3mmMix_NOCUT_NEWMACRO.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_DPhi4_DTheta2_NEWMACRO.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_DPhi4_DTheta2_NEWMACRO.root","read");


//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_HarshVertexCut_VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_fullstat.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_fullstat.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_HarshVertexCut_VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_20k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_HarshVertexCut_VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_fullstat.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_EinsteinEne_fullstat.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_HarshVertexCut_-1VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_EinsteinEne_20k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_EinsteinEne_MomCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT5_HarshVertexCut_-1VertexZ3mmMix_DPhi4_DTheta2_NEWMACRO_MomCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_LCMS_HITS_DCA2.root","read");

//	TFile* f = new TFile("./jobs/LCMS/analysis_2sigma_noRing_nTracksGT1_LCMS_HITS.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_noRing_wires_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_sharedWiresLT2_10k.root","read");//no entries in bckg
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_noRing_wires_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_noCut_10k.root","read");//no entries in bckg
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_noRing_wires_nTracksGT1_HarshVertexCut_nTracksOnlyMix_noCut_10k.root","read");//works
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_noRing_wires_nTracksGT1_HarshVertexCut_nTracksOnlyMix_noCut_50k.root","read");//works
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_noRing_wires_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_sharedWiresLt2_10k.root","read");//works
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_noRing_wires_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_sharedWiresLt2SameSector_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_noRing_wires_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_sharedWiresLt2NoSharedMetaSameSector_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_SharedWiresLt2NoSharedMetaSameSector_20k.root","read");

//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_SharedWiresLt2NoSharedMetaSameSector_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_noRing_nTracksGT2_HarshVertexCut_-1VertexZ3mmMix_SharedWiresLt2NoSharedMetaSameSector_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_noRing_nTracksGT3_HarshVertexCut_-1VertexZ3mmMix_SharedWiresLt2NoSharedMetaSameSector_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_noRing_nTracksGT4_HarshVertexCut_-1VertexZ3mmMix_SharedWiresLt2NoSharedMetaSameSector_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_noRing_nTracksGT5_HarshVertexCut_-1VertexZ3mmMix_SharedWiresLt2NoSharedMetaSameSector_fullstat.root","read");
	
	
	
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_noRing_nTracksGT5_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_SharedWiresLt1NoSharedMetaSameSector_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1LT10_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_SharedWiresLt2NoSharedMetaSameSector_20k.root ","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT5LT15_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_SharedWiresLt1NoSharedMetaSameSector_50k","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT5LT15_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_SharedWiresLT2NoSharedMetaSameSector_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT5_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_DifferentSectors_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_DifferentSectors_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT5_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_DifferentSectors_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_SharedWiresLT1NoSharedMetaSameSector_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_SharedWiresLT1NoSharedMetaSameSector_10k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_100mom1500_SharedWiresLT1NoSharedMetaSameSector_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix500MeVMomEne_100mom1500_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT5_HarshVertexCut_-1VertexZ3mmMixAverageMomEne200Mev_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
	
	
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmMix_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ1.5mmMetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nokIsUsed_nTracksGT5_HarshVertexCut_-1VertexZ3mmMixAverageMomEne200Mev_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT5_HarshVertexCut_-1VertexZ3mmAverageMomEneMetahitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmAverageMomEneMetahitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmAverageMomEneMetahitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmAverageMomEneMetahitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ1.5mmMetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");

//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_VertexZQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_averageMomentumQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_averageEnergyQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ5MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ5MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_betterZ_20k.root","read");

//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ_SharedWiresLT1NoSharedMetaSameSector_20k_betterZ.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_5VertexXQuantiles_beamTiltCorrection_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_5AvMom_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");



//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_5VertexYQuantiles_beamTiltCorrection_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");

//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_-1VertexZ1.5mmMetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");

//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ5MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_5MetaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_5AverageMomentumQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ5AverageMomentumQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ5VertexX5VertexYQuantiles_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_HarshVertexCut_15VertexZ5MetaHitsQuantiles_beamTiltCorrection_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_-140vertexZ-110_5metaHitsQuantiles_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");




//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_gen4_emptyTarget_noCuts_noEventHash.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_-140vertexZ-110_vertexZ1.5mmMetaHitsMix_beamTiltCorrection_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");



//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistToVertexXYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_100k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_fullstat.root","read");



//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day32.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day33.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day34.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day35.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day36.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day37.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day38.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day39.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day40.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day41.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day42.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day43.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day44.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noRing_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_day48.root","read");



//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT1_maxDistTo0XYis5_-140vertexZ-110_-1VertexZ1mmMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT1_VertexZGT-9999_maxDistTo0XYis5_MetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT1_VertexZGT-9999_maxDistTo0XYis5_MetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT5_VertexZGT-9999_maxDistTo0XYis5_MetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_20k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT1_VertexZGT-9999_maxDistTo0XYis5_MetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMetaSameSector_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCut_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_noIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMetaHits_beamTiltCorr_wrongDoubleCorrection_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_IsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCut_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMom200Ene200Mix_NoSharedWiresNoSharedMeta_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZMetaHitsQuantiles_NoSharedWiresNoSharedMeta_beamTiltCorr_10k.root","read");



//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_10k.root","read");



//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_fullstat.root","read");
	
	
	
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_beamTiltCorr_emptyTarget.root","read");

//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_10k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_fullstat.root","read");


//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCut_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_10k.root","read");

//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_10k.root","read");


//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");

//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_50k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector_beamTiltCorr_fullstat.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1_beamTiltCorr_50k.root","read");


//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NeighbouringSectors_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NeighbouringSectors_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NeighbouringSectors_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NeighbouringSectors_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NeighbouringSectors_beamTiltCorr_50k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ6_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ8_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ10_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ12_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_50k.root","read");


//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ3_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ6_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ8_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ10_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_50k.root","read");
	
	
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ2_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_fullstat.root","read");
	

//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksEQ4_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_50k.root","read");
	
	
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_rotatedBackground_noPairCut_beamTiltCorr_10k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_rotatedBackground_DifferentSectors_beamTiltCorr_10k.root","read");

//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT0_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noMetaDoubleUse_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_DifferentSector_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT0_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_MetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_MetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_50k.root","read");

	
	

//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1SameSector_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1SameSector_beamTiltCorr_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_NoEventHashing_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_MetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_TotalEnergy200MeVMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_TotalMomentum200MeVMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_10k.root","read");
	
	
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector0Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector1Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector2Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector3Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector4Pairs_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_OnlySector5Pairs_beamTiltCorr_gen4_50k.root","read");



//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_TransverseSphericity005_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_TransverseSphericity005Mix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_50k.root","read");


//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_NoSector0_beamTiltCorr_gen4_10k.root","read");
//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_NoSector4_beamTiltCorr_gen4_50k.root","read");


//	TFile *f = new TFile("./jobs/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT0_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_NoPairCut_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT0_-140VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_gen4_50k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT2_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT3_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT4_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysis_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_beamTiltCorr_gen4_50k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmRadius05mmMetaHitsMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_fullstat.root","read");
//	TFile *f = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmMetaHitsMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmMetaHitsMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");
//	TFile *f = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmChargedTracksMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");


//	TFile *f = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmChargedTracksMix_WireDistanceGT6NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");
	TFile *f = new TFile("./jobs/wires/analysisPim_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_vertexZ1mmChargedTracksMix_WireDistanceGT6NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","read");







//###################### pi+ ##################################

//	TFile* f = new TFile("./jobs/wires/analysisPip_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","red");
//	TFile* f = new TFile("./jobs/wires/analysisPip_2sigma_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-130VertexZ-110_maxDistTo0XYis5_notMdcEdge_noDoubleHits_VertexZ1mmMetaHitsMix_WireDistanceGT4NoSharedMetaAllLayers_beamTiltCorr_gen4_50k.root","red");


/*************Unlike sign experimental data**************/

//	TFile *f = new TFile("./jobs/wires/analysis_unlikeSign_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_10k.root ","read");
//	TFile *f = new TFile("./jobs/wires/analysis_unlikeSign_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_beamTiltCorr_10k.root ","read");
//	TFile *f = new TFile("./jobs/wires/analysis_unlikeSign_wires_Buffer10_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_nPimEQ1_nPipEQ1_beamTiltCorr_10k.root ","read");
//	TFile *f = new TFile("./jobs/analysis_unlikeSign_wires_Buffer10_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors_beamTiltCorr_10k.root ","read");




/****************SMASH p+p*******************/

	
	
//	TFile *f= new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_NOCUT.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_DPhi4DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DPhi10_DTheta5.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_HITS_TOPOLOGY_DCA2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_VertexZ_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT5_VertexZ_HITS.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1_VertexZ_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT11_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT10_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT9_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT11_VertexZ_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT10_VertexZ_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT9_VertexZ_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT8_VertexZ_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT11_VertexZ_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_NewCuts_2sigma_PE200MeV_nTracksGT1LT11_VertexZ_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_nTracksGT1_HarshVertexCut_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashUnlikeSign_2sigma_noRing_nTracksGT1_DPhi4_DTheta2.root","read");



//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_softVertexCut_nTracksGT1_noCut_noHash.root","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_nTracksGT1_HarshVertexCut_VertexZ3mmMix_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_nTracksGT1_HarshVertexCut_-1VertexZ3mmVertexX5mm_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_nTracksGT1_HarshVertexCut_VertexZ1.5mmVertexX1mmVertexY1mmMix_noCut.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_nTracksGT1_-1VertexZ5mmVertexXY1mm_DPhi4_DTheta2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_nTracksGT1_-1VertexZ5mmVertexXY1mm.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_HarshVertexCut_nTracksGT0_noCut_noHash.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_HarshVertexCut_nTracksGT1_-1VertexZ3mm_DPhi4_DTheta2_sharedHitsRejectionPim.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_HarshVertexCut_nTracksGT1_-1VertexZ3mm_DPhi4_DTheta2_sharedHitsRejectionPimPipP.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_HarshVertexCut_nTracksGT1_-1VertexZ3mm_DPhi4_DTheta2_sharedHitsRejectionAll.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_2sigma_noRing_HarshVertexCut_nTracksGT1_-1VertexZ3mm_DPhi4_DTheta2_sharedHitsRejectionPimOnly.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer200_-1VertexZ3mm_DPhi4_DTheta2_sharedHitsRejectionPimOnly.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer200_-1VertexZ3mm_sharedWiresLT2.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer200_-1VertexZ3mm_sharedWiresLT1NoSharedMetaSignals.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer200_-1VertexZ3mm_sharedWiresLT2NoSharedMetaSignals.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1LT10_Buffer200_-1VertexZ3mm_sharedWiresLT2NoSharedMetaSignals.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1LT10_Buffer50_-1VertexZ3mmEneMom500MeV_sharedWiresLT2NoSharedMetaSignals.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_-1VertexZ3mmEneMom500MeVnTracks_noSharedSectors.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_-1VertexZ3mmEneMom500MeV_sharedWiresLT2NoSharedMetaSignals.root  ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_nokIsUsed_HarshVertexCut_nTracksGT1_Buffer50_-1VertexZ3mmEneMom500MeV_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_Quantiles_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_nokIsUsed_HarshVertexCut_nTracksGT1_Buffer50_VertexXYMetaHitsQuantliesVertexZ3mmMix_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_VertexXYMetaHitsQuantliesVertexZ3mmMix_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_VertexXYMetaHitsQuantiles_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_VertexXYQuantilesVertexZ3mm_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_Vertex5XY15ZQuantiles_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_VertexXYQuantiles_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_Vertex5XQuantiles_sharedWiresLT2NoSharedMetaSignals.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_2sigma_noRing_HarshVertexCut_nTracksGT1_Buffer50_-1VertexZ3mmEneMom500MeVnTracks_noSharedSectors.root ","read");



//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_noIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta.root ","read");



//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_DifferentSectors.root ","read");



//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSector.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SameSectorSharedWiresLT1.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ6_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_rotatedBackground_DifferentSectors.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_NoEventHashing_SharedWiresLT2NoSharedMeta.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT2NoSharedMeta_10k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/smearedFunction_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_NoPairCuts_gen4_10k.root ","read");
//	TFile *f = new TFile("./jobs/smash/smearedFunction_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_DifferentSectors_gen4_10k.root ","read");
//	TFile *f = new TFile("./jobs/smash/smearedFunction_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_gen4_10k.root ","read");
//	TFile *f = new TFile("./jobs/smash/mcFunction_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_gen4_10k.root ","read");
//	TFile *f = new TFile("./jobs/smash/mcFunction_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector0Pairs_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector1Pairs_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector2Pairs_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector3Pairs_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector5Pairs_40k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector0SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector1SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector2SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector3SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector4SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_OnlySector5SharedWiresLT1NoSharedMeta_40k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_SharedWiresLT1NoSharedMeta_fullstat_gen4.root ","read");



//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT1AllLayers_fullstat_gen4.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_AllLayersDifferentSectors_20k_gen4.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_rotatedBackground60deg_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_rotatedBackground60deg_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_rotatedBackground60deg_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_rotatedBackground60deg_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_rotatedBackgroundRandomFrom0To360deg_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_50k_gen4.root ","read");
	
	
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ6_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ8_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ10_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ12_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ6_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ8_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ10_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksEQ12_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitsMix_wireDistanceGT3AllLayersNoSharedMeta_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitsMix_wireDistanceGT4AllLayersNoSharedMeta_50k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT0AllLayers_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT5_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT0AllLayers_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-140VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT0NoSharedMetaAllLayers_50k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmMetaHitssMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT2_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT3_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer50_NoIsGoodEvent_nTracksGT4_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmRadius05mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_fullstat_gen4.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT4NoSharedMetaAllLayers_50k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4NoSharedMetaAllLayers_50k_gen4.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT4AllLayers_50k_gen4.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT5NoSharedMetaAllLayers_50k_gen4.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_wires_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-110_maxDistTo0XYis5_VertexZ1mmChargedTracksMix_wireDistanceGT6NoSharedMetaAllLayers_50k_gen4.root","read");






	//################################ pi+ ###############################//

//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_wires_Buffer50_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_wireDistanceGT10AllLayersNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_wires_Buffer20_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_Buffer20_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMeta_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_Buffer20_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoSharedWiresNoSharedMetaAllLayers_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_wires_Buffer20_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCuts_20k_gen4.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_Buffer20_NoIsGoodEvent_nTracksGT1_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCuts_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_Buffer20_NoIsGoodEvent_nTracksGT2_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCuts_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_Buffer20_NoIsGoodEvent_nTracksGT3_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCuts_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_Buffer20_NoIsGoodEvent_nTracksGT4_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCuts_20k_gen4.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_Buffer20_NoIsGoodEvent_nTracksGT5_-140VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_NoPairCuts_20k_gen4.root ","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPip_Buffer20_NoIsGoodEvent_nTracksGT1_-130VertexZ-100_maxDistTo0XYis5_VertexZ1mmMetaHitsMix_WireDistanceGT4NoSharedMetaAllLayers_50k_gen4.root ","read");




/*************SMASH p+p HGeantKine******************/

//	TFile *f = new TFile("./jobs/smash/analysisPureKinePim_noCut_noMix.root","read");//only one number in Sig/BckgName
//	TFile *f = new TFile("./jobs/smash/analysisPureKinePim_noCut_PairHash.root","read");//only one number in Sig/BckgName
//	TFile *f = new TFile("./jobs/smash/analysisPureKinePim_noCut_PairHash.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisPureKinePim_noCut_EventHash.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisPureKinePim_noCut_BothHash.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisPureKinePim_noCut_noHash.root","read");
//	TFile *f = new TFile("./kinetest.root","read");
//	TFile *f = new TFile("./jobs/smash/idealBackground_hgeantkine_harshVertexCut.root","read");
//	TFile *f = new TFile("./jobs/smash/idealBackground_hgeantkine_noEventSelection_pxpyrotation.root","read");


//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_pureMC_Cosines_nTracksMix.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisSmashPim_pureMC_nTracksMix.root ","read");

//	TFile *f = new TFile("./jobs/smash/analysisPureKinePim_nRealTracksGT1_noCut_nTracksEventHash_kTyPairHash.root ","read");
//	TFile *f = new TFile("./jobs/smash/analysisPureKinePim_nRealTracksGT5_noCut_nTracksEventHash_kTyPairHash.root ","read");
//	TFile *f = new TFile("./jobs/smash/UrQMD_pim_analysis4.5GeV_buffer20_nTracksMix_nTracksGT5.root ","read");
//	TFile *f = new TFile("./jobs/smash/UrQMD_pim_analysis4.5GeV_buffer20_nTracksMix_nTracksGT1.root ","read");





/**************SMASH Ag+Ag HGeantKine******************/


//	TFile *f = new TFile("./jobs/smash/analysisAgAgPureKinePim_noCut_noHash.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisAgAgPureKinePim_noCut_PairHash.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisAgAgPureKinePim_noCut_EventCentralityPlateHash.root","read");
//	TFile *f = new TFile("./jobs/smash/analysisAgAgPureKinePim_noCut_BothHash.root","read");





//	TFile *f = new TFile("./agagtest.root","read");
//	TFile *f = new TFile("./cosinestest.root","read");
//	TFile *f = new TFile("./jobs/wires/agag_analysis.root","read");





/**********************UrQMD*********************/

//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noweights.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_noHash.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_PairHash.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_EventHash.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_noCut_BothHash.root","read");


//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT1_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT2_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT3_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT4_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT5_nTracksMix_NewFemtoMixer.root","read");


//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT1_cosines_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT2_cosines_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT3_cosines_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT4_cosines_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksGT5_cosines_nTracksMix_NewFemtoMixer.root","read");


//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksMix_cosines_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis4.5GeV_nTracksMix_cosines_NewFemtoMixer1.root","read");
	
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis100GeV_nTracksMix_NewFemtoMixer.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_analysis100GeV_nTracksMix_cosines_NewFemtoMixer.root","read");


//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_nTracksMix.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_nTracksMix_kStar.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_nTracksMix_0y2_0.4pT2_kStar.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_nTracksMix_-1y1_400Pt2000.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_kStar.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_rotated.root","read");


//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_-1y1_0.4pT2.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_nTracksMix.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_rotated_boosted.root","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_-1y1_0.4pT2_kTlt2.root ","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_-1y1_0.4pT2_rotated.root ","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_-1y1_0.4pT2_kTlt2_rotated.root ","read");


//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pip_analysis4.5GeV_nTracksMix_NewFemtoMixer.root ","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pip_analysis4.5GeV_nTracksMix_-1y1_400Pt2000.root ","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_nTracksMix_cosine.root ","read");


//	TFile *f = new TFile("./jobs/urqmd/smearedFunction_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_UrQMD.root ","read");
//	TFile *f = new TFile("./jobs/urqmd/mcFunction_NoIsGoodEvent_nTracksGT0_-140VertexZ-100_maxDistTo0XYis5_noPairCuts_FemtoCoulombWeight_UrQMD.root ","read");

//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_nTracksMix_nTracksGT1.root ","read");
//	TFile *f = new TFile("./jobs/urqmd/UrQMD_pim_analysis4.5GeV_nTracksMix_nTracksGT5.root ","read");
	
	
//################# pure SMASH pi- #########################

//	TFile *f = new TFile("./jobs/smash/pureSmash_pim_analysis4.5GeV_buffer20_nChargedTracksMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pim_analysis4.5GeV_buffer20_nChargedTracksMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pim_analysis4.5GeV_buffer20_nTracksMix_nTracksGT1.root","read");

//################# pure SMASH pi+ #########################
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_nTracksMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_chargedTracksMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_chargedTracksMix_nTracksGT5.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_chargedTracksMix_onlyPrimary_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalChargeMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalPositiveChargeMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalPositiveChargeMix_nTracksGT5.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_TotalPositiveAndNegativeChargeMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_nPipMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_positiveAndNegativePionsMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalMomentumMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalMomentumAndChargedTracksMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalKtAndRapidityMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalKtMix_nTracksGT1.root","read");
//	TFile *f = new TFile("./jobs/smash/pureSmash_pip_analysis4.5GeV_buffer20_totalRapidityMix_nTracksGT1.root","read");
	
	
	
//	TFile *f = new TFile("./pimtest.root");
//	TFile *f = new TFile("./simtest.root");
//	TFile *f = new TFile("./unlikeSignTest.root");
//	TFile *f = new TFile("./rotatedpimtest.root");
//	TFile *f = new TFile("./smeartest.root");
//	TFile *f = new TFile("./smashTest.root");
	
	
	
	
	
	
	//TH1D *h = (TH1D*)f->Get("expCF");
	//TH1D *h = (TH1D*)f->Get("doubleRatio");
	
	TH1D *sigExp = new TH1D("signal","signal",1500,0,1500);
	TH1D *bckgExp = new TH1D("background","background",1500,0,1500);
	
	vector<TH1D *>sigExpKtBin;
	vector<TH1D *>sigExpRapidityBin;
	vector<TH1D *>bckgExpKtBin;
	vector<TH1D *>bckgExpRapidityBin;
	
	TPaveText *t = new TPaveText(.5,1.4,0.8,1.6);
	t->SetTextAlign(12); // left horizontally, centered vertically
	t->AddText("p+p at #sqrt{s} = 3.46 GeV");
	t->AddText("HADES work in progress");
//	t->AddText("Raw correlation function");
	t->AddText("No shared wires");
	t->AddText("nTrack#geq 6");
	t->SetBorderSize(0);
	t->SetFillStyle(0);
	
	char SigName[20];
	char BckgName[20];
	
	for(int i=1; i<10; i++)
	{
		sprintf(SigName, "sigExpKtBin%d", i);
		sprintf(BckgName, "BckgExpKtBin%d", i);
		
		sigExpKtBin.push_back(new TH1D(SigName, SigName,1500,0,1500));
		bckgExpKtBin.push_back(new TH1D(BckgName, BckgName,1500,0,1500));
		for(int j=1; j<10; j++)
		{	
			if(std::string(f->GetName()).find("Pim")!=string::npos || std::string(f->GetName()).find("pim")!=string::npos)
			{
				sprintf(SigName, "PimSig_%d%d",i,j);
				sprintf(BckgName, "PimBckg_%d%d",i,j);
			}
			else if(std::string(f->GetName()).find("Pip")!=string::npos || std::string(f->GetName()).find("pip")!=string::npos)
			{
				sprintf(SigName, "PipSig_%d%d",i,j);
				sprintf(BckgName, "PipBckg_%d%d",i,j);
			}
			else
			{
				sprintf(SigName, "PimSig_%d%d",i,j);
				sprintf(BckgName, "PimBckg_%d%d",i,j);	
			}
			TH1D* tempSigExp = (TH1D*)f->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f->Get(BckgName);
			
			if(tempSigExp)
			{
				
				sigExp->Add(tempSigExp);
				bckgExp->Add(tempBckgExp);
				sigExpKtBin.at(i-1)->Add(tempSigExp);
				bckgExpKtBin.at(i-1)->Add(tempBckgExp);
				
				delete tempSigExp;
				delete tempBckgExp;
			}
		}
	}
	
	
	for(int i=1; i<10; i++)
	{
		sprintf(SigName, "sigExpRapidityBin%d", i);
		sprintf(BckgName, "bckgExpRapidityBin%d", i);
		
		sigExpRapidityBin.push_back(new TH1D(SigName, SigName,1500,0,1500));
		bckgExpRapidityBin.push_back(new TH1D(BckgName, BckgName,1500,0,1500));
		for(int j=1; j<10; j++)
		{	
			
			if(std::string(f->GetName()).find("Pim")!=string::npos)
			{
				sprintf(SigName, "PimSig_%d%d",i,j);
				sprintf(BckgName, "PimBckg_%d%d",i,j);
			}
			else if(std::string(f->GetName()).find("Pip")!=string::npos)
			{
				sprintf(SigName, "PipSig_%d%d",i,j);
				sprintf(BckgName, "PipBckg_%d%d",i,j);
			}
			
			TH1D* tempSigExp = (TH1D*)f->Get(SigName);
			TH1D* tempBckgExp = (TH1D*)f->Get(BckgName);
			
			if(tempSigExp)
			{
				
				sigExp->Add(tempSigExp);
				bckgExp->Add(tempBckgExp);
				sigExpRapidityBin.at(i-1)->Add(tempSigExp);
				bckgExpRapidityBin.at(i-1)->Add(tempBckgExp);
				
				delete tempSigExp;
				delete tempBckgExp;
			}
		}
	}
	
	
	cout<<sigExp->GetEntries()<<" "<<bckgExp->GetEntries()<<endl;
	
	sigExp->Rebin(15);
	bckgExp->Rebin(15);
	sigExp->Sumw2(true);
	bckgExp->Sumw2(true);
	
	TH1D *hCF = new TH1D(*sigExp);
	
/*	double numint_div_denint = (double)bckgExp->Integral()/sigExp->Integral();
	
	//TH1D* CF = new TH1D(*sigExp);
	hCF->Scale(numint_div_denint, "");
	*/
	hCF->SetNameTitle("Exp", "Exp");
	hCF->GetXaxis()->SetTitle("q_{inv} (MeV/c)");
	hCF->GetYaxis()->SetTitle("CF");
	
	
	hCF->Divide(bckgExp);
	
	
	//############# Apply momentum resolution correction ################//
	TFile *correctionFile = new TFile("./outputs/momentumResolutionCorrection_nTracksGT0.root", "read");
	TH1D *momResCorr = (TH1D*) correctionFile->Get("momentumResolutionCorrection_nTracksGT0");
	
//	hCF->Multiply(momResCorr);
	
	
	int cnt=0;
	double average=0;	
	//for(int i=hCF->FindBin(350); i<=hCF->FindBin(400); i++)//for UrQMD (Daniel normalized so)
	for(int i=hCF->FindBin(250); i<=hCF->FindBin(350); i++)//for experimental data and SMASH
	{
		cnt++;
		average+=hCF->GetBinContent(i);
	}
	average/=cnt;
	cout<<"srednia "<<average<<endl;
	cout<<"cnt "<<cnt<<endl;
	
	
	hCF->Scale(1/average);
	
	
//	TF1 *hermite4Gaus = new TF1("fitGausHermite4", modifiedGausFitHermiteUpTo4, 0.04, 0.3, 4);
	TF1 *hermite4Gaus = new TF1("fitGausHermite4", hermiteFitFrom3To4, 0.04, 0.3, 5);
	
	
//	TF1 *hermite6Gaus = new TF1("fitGausHermite6", modifiedGausFitHermiteUpTo6, 0.04, 0.3, 5);
	TF1 *hermite6Gaus = new TF1("fitGausHermite6", hermiteFitFrom3To6, 0.04, 0.3, 7);
//	TF1 *fitGaus = new TF1("fitGaus", coulombLinearGausFit, 0.02, 0.8, 5);
	TF1 *fitGaus = new TF1("fitGaus", coulombQuadraticGausFit, 0.02, 0.4, 6);
//	TF1 *fitGaus = new TF1("fitGaus", gausFit, 0.01, 0.15, 3);
	
//	TF1 *fitGaus = new TF1("fitGaus", coulombGausFit, 0.02, 0.35, 3);
//	TF1 *fitExp = new TF1("fitExp", coulombLinearExpFit, 0.05, 0.8, 5);
//	TF1 *fitExp = new TF1("fitExp", coulombQuadraticExpFit, 0.05, 0.8, 6);
//	TF1 *fitExp = new TF1("fitExp", expFit, 0.01, 0.15, 3);
	
	hermite6Gaus->SetParName(0, "lambda");
	hermite6Gaus->SetParName(1, "R");
	hermite6Gaus->SetParName(2, "norm");
	hermite6Gaus->SetParName(3, "kappa 3");
	hermite6Gaus->SetParName(4, "kappa 4");
	hermite6Gaus->SetParName(5, "kappa 5");
	hermite6Gaus->SetParName(6, "kappa 6");
	
	hermite6Gaus->SetParameters(0.7,1,1,1,1);
	
	hermite6Gaus->SetParLimits(0,0,1);
	hermite6Gaus->SetParLimits(1,0.001,15);
	hermite6Gaus->SetParLimits(2,0.01,10);
	
	
	hermite4Gaus->SetParName(0, "lambda");
	hermite4Gaus->SetParName(1, "R");
	hermite4Gaus->SetParName(2, "norm");
	hermite4Gaus->SetParName(3, "kappa 3");
	hermite4Gaus->SetParName(4, "kappa 4");
	
	hermite4Gaus->SetParameters(0.7,1,1,1,1);
	
	hermite4Gaus->SetParLimits(0,0,1);
	hermite4Gaus->SetParLimits(1,0.001,15);
	hermite4Gaus->SetParLimits(2,0.01,10);
	
	
	
	fitGaus->SetParName(0, "lambda");
	fitGaus->SetParName(1, "R");
	fitGaus->SetParName(2, "norm");
	
	fitGaus->SetParameters(0.7,2,1,1,1,1);
	
	fitGaus->SetParLimits(0,0,1);
	fitGaus->SetParLimits(1,0.001,15);
	fitGaus->SetParLimits(2,0.01,10);
	fitGaus->SetParLimits(3,1,2);
	
	
	
	TH1D *hGeV = new TH1D("expCF","expCF",hCF->GetNbinsX(),0,hCF->GetXaxis()->GetXmax()/1000);	
	hGeV->GetXaxis()->SetTitle("q_{inv} (GeV/c)");
	hGeV->GetYaxis()->SetTitle("CF");
	
	for(int i=1;i<=hCF->GetNbinsX();i++)
	{
		hGeV->SetBinContent(i,hCF->GetBinContent(i));
		hGeV->SetBinError(i,hCF->GetBinError(i));
	}
	
	
	
	cout<<endl<<endl<<"************ hermite 4 ************"<<endl;
	hGeV->Fit(hermite4Gaus, "REM0", "");
	double hermite4GausLow=0;
	double hermite4GausTop=0;
	hermite4Gaus->GetRange(hermite4GausLow,hermite4GausTop);
//	TF1 *hermite4GausExtrapolated = new TF1("hermite4GausExtrapolated", modifiedGausFitHermiteUpTo4, hermite4GausTop, hermite4GausTop+0.3, hermite4Gaus->GetNpar());s
	TF1 *hermite4GausExtrapolated = new TF1("hermite4GausExtrapolated", hermiteFitFrom3To4, hermite4GausTop, hermite4GausTop+0.3, hermite4Gaus->GetNpar());
	for(int i=0; i<hermite4Gaus->GetNpar(); i++)
	{
		hermite4GausExtrapolated->SetParameter(i, hermite4Gaus->GetParameter(i));
	}
	cout<<endl<<endl<<"N_gaus hermite4= "<<hermite4Gaus->GetParameter(2)<<" ("<<hermite4Gaus->GetParError(2)<<")"<<endl;
	cout<<"R_gaus hermite4= "<<hermite4Gaus->GetParameter(1)<<" ("<<hermite4Gaus->GetParError(1)<<")"<<endl;
	cout<<"lambda_gaus hermite4= "<<hermite4Gaus->GetParameter(0)<<" ("<<hermite4Gaus->GetParError(0)<<")"<<endl;
	
	
	cout<<endl<<endl<<"************ hermite 6 ************"<<endl;
	hGeV->Fit(hermite6Gaus, "REM0", "");
	double hermite6GausLow=0;
	double hermite6GausTop=0;
	hermite6Gaus->GetRange(hermite6GausLow,hermite6GausTop);
//	TF1 *hermite6GausExtrapolated = new TF1("hermite6GausExtrapolated", modifiedGausFitHermiteUpTo6, hermite6GausTop, hermite6GausTop+0.3, hermite6Gaus->GetNpar());
	TF1 *hermite6GausExtrapolated = new TF1("hermite6GausExtrapolated", hermiteFitFrom3To6, hermite6GausTop, hermite6GausTop+0.3, hermite6Gaus->GetNpar());
	for(int i=0; i<hermite6Gaus->GetNpar(); i++)
	{
		hermite6GausExtrapolated->SetParameter(i, hermite6Gaus->GetParameter(i));
	}
	cout<<endl<<endl<<"N_gaus hermite6= "<<hermite6Gaus->GetParameter(2)<<" ("<<hermite6Gaus->GetParError(2)<<")"<<endl;
	cout<<"R_gaus hermite6= "<<hermite6Gaus->GetParameter(1)<<" ("<<hermite6Gaus->GetParError(1)<<")"<<endl;
	cout<<"lambda_gaus hermite6= "<<hermite6Gaus->GetParameter(0)<<" ("<<hermite6Gaus->GetParError(0)<<")"<<endl;
	
	
	cout<<endl<<endl<<"************ gaus ************"<<endl;
	hGeV->Fit(fitGaus, "REM0", "");
	double gausLow=0;
	double gausTop=0;
	fitGaus->GetRange(gausLow,gausTop);
	TF1 *gausExtrapolated = new TF1("gausExtrapolated", coulombGausFit, gausTop, gausTop+0.3, fitGaus->GetNpar());
	for(int i=0; i<fitGaus->GetNpar(); i++)
	{
		gausExtrapolated->SetParameter(i, fitGaus->GetParameter(i));
	}
	cout<<endl<<endl<<"N_gaus= "<<fitGaus->GetParameter(2)<<" ("<<fitGaus->GetParError(2)<<")"<<endl;
	cout<<"R_gaus= "<<fitGaus->GetParameter(1)<<" ("<<fitGaus->GetParError(1)<<")"<<endl;
	cout<<"lambda_gaus= "<<fitGaus->GetParameter(0)<<" ("<<fitGaus->GetParError(0)<<")"<<endl;
	
	
	
	
	hGeV->GetXaxis()->SetRangeUser(0.0,max({gausTop+0.4,hermite6GausTop+0.4}));
	
	
	TCanvas *cCF = new TCanvas("cCF","cCF",1000,1000);
	
	
	hGeV->SetNameTitle("","");
	hGeV->GetYaxis()->SetRangeUser(0.6,1.6);
	hGeV->GetXaxis()->SetRangeUser(0,0.8);
	hGeV->SetLineWidth(2);
	hGeV->SetMarkerStyle(8);
	hGeV->SetMarkerSize(0.7);
	hGeV->SetMarkerColor(hGeV->GetLineColor());
	hGeV->Draw();
	cout<<endl<<endl;
	
	
	coulombCorrection->SetLineColor(kGreen+1);
//	coulombCorrection->Draw("same");
	
	cCF->cd();
	/*
	cout<<"gaus chi2/ndf "<<fitGaus->GetChisquare()/fitGaus->GetNDF()<<endl;
	fitGaus->SetLineColor(kRed);
	fitGaus->Draw("same");

	gausExtrapolated->SetLineColor(fitGaus->GetLineColor());
	gausExtrapolated->SetLineStyle(kDashed);
//	gausExtrapolated->Draw("same");
	
	
	cout<<"hermite6Gaus chi2/ndf "<<hermite6Gaus->GetChisquare()/hermite6Gaus->GetNDF()<<endl;
	hermite6Gaus->SetLineColor(kOrange+1);
	hermite6Gaus->Draw("same");
	
	hermite6GausExtrapolated->SetLineColor(hermite6Gaus->GetLineColor());
	hermite6GausExtrapolated->SetLineStyle(kDashed);
	hermite6GausExtrapolated->Draw("same");
	
	
	cout<<"hermite4Gaus chi2/ndf "<<hermite4Gaus->GetChisquare()/hermite4Gaus->GetNDF()<<endl;
	hermite4Gaus->SetLineColor(kMagenta+1);
	hermite4Gaus->Draw("same");
	
	hermite4GausExtrapolated->SetLineColor(hermite4Gaus->GetLineColor());
	hermite4GausExtrapolated->SetLineStyle(kDashed);
	hermite4GausExtrapolated->Draw("same");
	

	cout<<endl<<endl<<endl;

	char name[100];
	sprintf(name, "%s fm",coulombCorrection->GetName());
	
	TLegend *leg = new TLegend(0.6,0.2,0.9,0.4);
	leg->AddEntry(hGeV, "CF", "lp");
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
//	leg->AddEntry(coulombCorrection, "Coulomb potential, 1 fm", "lp");
	leg->AddEntry(fitGaus, "Bowler-Sinyukov", "l");
	leg->AddEntry(hermite4Gaus, "Bowler-Sinyukov + H_{3} + H_{4}", "l");
	leg->AddEntry(hermite6Gaus, "Bowler-Sinyukov + H_{3} + ... + H_{6}", "l");
	leg->Draw();
//	t->Draw();
	
	TLine *line = new TLine(0.02,1,0.8,1);
	line->SetLineColor(kAzure-3);
	line->SetLineStyle(9);
	line->Draw();
	
	
	
	TFile *output = new TFile("./outputs/fit_LCMS_HITS.root", "RECREATE");
	hGeV->Write();
	sigExp->Write();
	bckgExp->Write();
	hermite6Gaus->Write();
	fitGaus->Write();
	output->Save();
	output->Close();
	
	

	TCanvas *cKtBin = new TCanvas("cKtBin","cKtBin",800,800);
	cKtBin->Divide(2,3);
	vector<int> colors = {kBlue+1, kRed, kMagenta+1, kGreen+1, kCyan+2};
	for(int i=0;i<5;i++)
	{
		cKtBin->cd(i+1);
		sigExpKtBin.at(i)->Rebin(15);
		bckgExpKtBin.at(i)->Rebin(15);
		sigExpKtBin.at(i)->Sumw2(true);
		bckgExpKtBin.at(i)->Sumw2(true);
		sigExpKtBin.at(i)->Divide(bckgExpKtBin.at(i));
		
		int cnt=0;
		double average=0;			
		for(int j=sigExpKtBin.at(i)->FindBin(250); j<=sigExpKtBin.at(i)->FindBin(350); j++)//for experimental data and SMASH	
		{
			cnt++;
			average+=sigExpKtBin.at(i)->GetBinContent(j);
		}
		average/=cnt;
		cout<<"srednia "<<average<<endl;
		cout<<"cnt "<<cnt<<endl;
	
		sigExpKtBin.at(i)->Scale(1/average);
		

		sigExpKtBin.at(i)->GetXaxis()->SetRangeUser(0,400);
		sigExpKtBin.at(i)->GetYaxis()->SetRangeUser(0,2);
		sigExpKtBin.at(i)->SetLineColor(colors.at(i));
		sigExpKtBin.at(i)->Draw("");
	}
	

	TCanvas *cRapidityBin = new TCanvas("cRapidityBin","cRapidityBin",800,800);
	cRapidityBin->Divide(2,3);
	for(int i=0;i<5;i++)
	{
		cRapidityBin->cd(i+1);
		sigExpRapidityBin.at(i)->Rebin(15);
		bckgExpRapidityBin.at(i)->Rebin(15);
		sigExpRapidityBin.at(i)->Sumw2(true);
		bckgExpRapidityBin.at(i)->Sumw2(true);
		sigExpRapidityBin.at(i)->Divide(bckgExpRapidityBin.at(i));
		
		int cnt=0;
		double average=0;			
		for(int j=sigExpRapidityBin.at(i)->FindBin(250); j<=sigExpRapidityBin.at(i)->FindBin(350); j++)//for experimental data and SMASH	
		{
			cnt++;
			average+=sigExpRapidityBin.at(i)->GetBinContent(j);
		}
		average/=cnt;
		cout<<"srednia "<<average<<endl;
		cout<<"cnt "<<cnt<<endl;
	
		sigExpRapidityBin.at(i)->Scale(1/average);
		

		sigExpRapidityBin.at(i)->GetXaxis()->SetRangeUser(0,400);
		sigExpRapidityBin.at(i)->GetYaxis()->SetRangeUser(0,2);
		sigExpRapidityBin.at(i)->SetLineColor(colors.at(i));
		sigExpRapidityBin.at(i)->Draw("");
	}


	TFitResultPtr r = hGeV->Fit(hermite4Gaus, "SREM0");
	TMatrixDSym corr = r->GetCorrelationMatrix();
	cout<<"hermite 4 correlation matrix"<<endl;
	corr.Print();


	TFitResultPtr r1 = hGeV->Fit(hermite6Gaus, "SREM0");
	TMatrixDSym corr1 = r1->GetCorrelationMatrix();
	cout<<"hermite 6 correlation matrix"<<endl;
	corr1.Print();

	*/
	
	
	cout<<"gauss with quadratic function correlation matrix"<<endl;
	TFitResultPtr rGausQuadratic = hGeV->Fit(fitGaus, "SREM0");
	TMatrixDSym corrGaussQuadratic = rGausQuadratic->GetCorrelationMatrix();
	corrGaussQuadratic.Print();
	fitGaus->Draw("same");
	return 0;
}
	

