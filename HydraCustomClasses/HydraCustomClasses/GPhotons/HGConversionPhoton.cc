#include "HGConversionPhoton.h"

ClassImp(HGConversionPhoton)
HGConversionPhoton::HGConversionPhoton() : TObject(){
	fPx = fPy = fPz = fEnergy = -1;
	fConvVertexX = fConvVertexY = fConvVertexZ = -1000;
}

HGConversionPhoton::HGConversionPhoton(Float_t Px, Float_t Py, Float_t Pz, Float_t E) : TObject(){
	fPx=Px;
	fPy=Py;
	fPz=Pz;
	fEnergy=E;
	fConvVertexX = fConvVertexY = fConvVertexZ = -1000;
}

void HGConversionPhoton::setConversionVertex(Float_t cvX, Float_t cvY, Float_t cvZ){
	fConvVertexX=cvX;
	fConvVertexY=cvY;
	fConvVertexZ=cvZ;
}

void HGConversionPhoton::setConversionVertex(HGeomVector &vtx){
	fConvVertexX=vtx.getX();
	fConvVertexY=vtx.getY();
	fConvVertexZ=vtx.getZ();
}

HGeomVector HGConversionPhoton::getConversionVertex(){
	HGeomVector vtx(fConvVertexX,fConvVertexY,fConvVertexZ);
	return vtx;	
}

void HGConversionPhoton::setMomenta(const TLorentzVector &vec){
	fPx = vec.Px();
	fPy = vec.Py();
	fPz = vec.Pz();
	fEnergy = vec.E();
}

TLorentzVector HGConversionPhoton::getTLorentzVector(){
	TLorentzVector vec;
	vec.SetPxPyPzE(fPx,fPy,fPz,fEnergy);
	return vec;
}