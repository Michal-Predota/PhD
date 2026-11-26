#ifndef HGCONVERSIONPHOTON_H
#define HGCONVERSIONPHOTON_H

#include <TObject.h>
#include <TLorentzVector.h>
#include "hgeomvector.h"

class HGConversionPhoton: public TObject{
protected:
	//only those, rest you can recreate with TLorentzVector & other stuff
	Float_t fPx,fPy,fPz,fEnergy;
    Float_t fConvVertexX, fConvVertexY, fConvVertexZ;

public:
    HGConversionPhoton();
    HGConversionPhoton(Float_t Px, Float_t Py, Float_t Pz, Float_t E);
    virtual ~HGConversionPhoton(){};

    
    void setEnergy(Float_t E) {fEnergy=E;}
    void setPx(Float_t Px) {fPx=Px;}
    void setPy(Float_t Py) {fPy=Py;}
    void setPz(Float_t Pz) {fPz=Pz;}
    void setMomenta(const TLorentzVector &vec);
    Float_t getEnergy(){return fEnergy;}
    Float_t getPx(){return fPx;}
    Float_t getPy(){return fPy;}
    Float_t getPz(){return fPz;}

    void setConversionVertex(Float_t cvX, Float_t cvY, Float_t cvZ);
    void setConversionVertex(HGeomVector &vtx);
    HGeomVector getConversionVertex();

    
    TLorentzVector getTLorentzVector();

    ClassDef(HGConversionPhoton,1);
};

#endif