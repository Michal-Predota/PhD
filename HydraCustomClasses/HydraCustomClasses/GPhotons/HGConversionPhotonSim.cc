#include "HGConversionPhotonSim.h"

ClassImp(HGConversionPhotonSim)
HGConversionPhotonSim::HGConversionPhotonSim() : HGConversionPhoton(){
	fConvVertexXgeant = fConvVertexYgeant = fConvVertexZgeant = -1000;
	fIDe = fIDp = fParentIDe = fParentIDp = fGParentIDe = fGParentIDp = -1;
	fTracke = fTrackp = fParentTracke = fParentTrackp = fGParentTracke = fGParentTrackp = -1;
	fInAcceptance=kTRUE;
	fAdded=kFALSE;
}

HGConversionPhotonSim::HGConversionPhotonSim(Float_t Px, Float_t Py, Float_t Pz, Float_t E) : HGConversionPhoton(Px, Py, Pz, E){
	fConvVertexXgeant = fConvVertexYgeant = fConvVertexZgeant = -1000;
	fIDe = fIDp = fParentIDe = fParentIDp = fGParentIDe = fGParentIDp = -1;
	fTracke = fTrackp = fParentTracke = fParentTrackp = fGParentTracke = fGParentTrackp = -1;
	fInAcceptance=kTRUE;
	fAdded=kFALSE;
}

void HGConversionPhotonSim::setConversionGeantVertex(Float_t cvX, Float_t cvY, Float_t cvZ){
	fConvVertexXgeant=cvX;
	fConvVertexYgeant=cvY;
	fConvVertexZgeant=cvZ;
}

void HGConversionPhotonSim::setConversionGeantVertex(HGeomVector &vtx){
	fConvVertexXgeant=vtx.getX();
	fConvVertexYgeant=vtx.getY();
	fConvVertexZgeant=vtx.getZ();
}

HGeomVector HGConversionPhotonSim::getConversionGeantVertex(){
	HGeomVector vtx(fConvVertexXgeant,fConvVertexYgeant,fConvVertexZgeant);
	return vtx;	
}


