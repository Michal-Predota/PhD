#include "HGEcalPhoton.h"

ClassImp(HGEcalPhoton)
HGEcalPhoton::HGEcalPhoton() : TObject(){
	fPx = fPy = fPz = -1;
	fSize = fSector = fCell = -1;
    fBetaQuality = -1;
    fEcalEnergy = fEcalLowestEnergy = -1;
    fMatchAngle = -1;
	fMatchQuality = -1;
}

HGEcalPhoton::HGEcalPhoton(Float_t Px, Float_t Py, Float_t Pz) : TObject(){
	fPx=Px;
	fPy=Py;
	fPz=Pz;
	fSize = fSector = fCell = -1;
    fBetaQuality = -1;
    fEcalEnergy = fEcalLowestEnergy = -1;
    fMatchAngle = -1;
	fMatchQuality = -1;
}

void HGEcalPhoton::setMomenta(Float_t Px, Float_t Py, Float_t Pz){
	fPx=Px;
	fPy=Py;
	fPz=Pz;
}

void HGEcalPhoton::setMomenta(const TLorentzVector &vec){
	fPx = vec.Px();
	fPy = vec.Py();
	fPz = vec.Pz();
}

TLorentzVector HGEcalPhoton::getTLorentzVector(){
	TLorentzVector vec;
	vec.SetXYZM(fPx,fPy,fPz,0);
	return vec;
}