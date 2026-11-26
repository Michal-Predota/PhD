#include "HGEcalPhotonSim.h"

ClassImp(HGEcalPhotonSim)
HGEcalPhotonSim::HGEcalPhotonSim() : HGEcalPhoton(){
	fID = fTrack = fParentID = fParentTrack = -1;
	fInAcceptance=kTRUE;
	fAdded=kFALSE;
}

HGEcalPhotonSim::HGEcalPhotonSim(Float_t Px, Float_t Py, Float_t Pz) : HGEcalPhoton(Px, Py, Pz){
	fID = fTrack = fParentID = fParentTrack = -1;
	fInAcceptance=kTRUE;
	fAdded=kFALSE;
}
