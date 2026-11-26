#ifndef HGECALPHOTON_H
#define HGECALPHOTON_H

#include <TObject.h>
#include <TLorentzVector.h>
#include <iostream>

class HGEcalPhoton: public TObject{
protected:
	//only those, rest you can recreate with TLorentzVector & other stuff
	Float_t fPx,fPy,fPz;
    Int_t fSize; //cluster size
    Float_t fBetaQuality; //beta sigma from beta=1
    Float_t fEcalEnergy, fEcalLowestEnergy;
    Float_t fMatchQuality; //EMC mq for "charged tracks" correlated with clustres
    Float_t fMatchAngle; //Matching angle with inner & outer segments (calculated by hand)
    Int_t fSector, fCell;
public:
    HGEcalPhoton();
    HGEcalPhoton(Float_t Px, Float_t Py, Float_t Pz);
    virtual ~HGEcalPhoton(){};

    void setPx(Float_t Px) {fPx=Px;}
    void setPy(Float_t Py) {fPy=Py;}
    void setPz(Float_t Pz) {fPz=Pz;}
    void setMomenta(Float_t Px, Float_t Py, Float_t Pz);
    void setMomenta(const TLorentzVector &vec);
    void setClusterSize(Int_t S) {fSize=S;}
    void setBetaQuality(Float_t BQ) {fBetaQuality=BQ;}
    void setEcalEnergy(Float_t Energy) {fEcalEnergy=Energy;}
    void setEcalLowestEnergy(Float_t Energy) {fEcalLowestEnergy=Energy;}
    void setMatchAngle(Float_t Angle) {fMatchAngle=Angle;}
    void setMatchQuality(Float_t MQ) {fMatchQuality=MQ;}
    void setSector(Int_t sec) {fSector=sec;}
    void setCell(Int_t cell) {fCell=cell;}

    Float_t getPx(){return fPx;}
    Float_t getPy(){return fPy;}
    Float_t getPz(){return fPz;}
    Int_t getClusterSize(){return fSize;}
    Float_t getEcalEnergy(){return fEcalEnergy;}
    Float_t getEcalLowestEnergy(){return fEcalLowestEnergy;}
    Float_t getBetaQuality(){return fBetaQuality;}
    Float_t getMatchAngle(){return fMatchAngle;}
    Float_t getMatchQuality(){return fMatchQuality;}
    Int_t getSector() {return fSector;}
    Int_t getCell() {return fCell;}

    TLorentzVector getTLorentzVector();
    ClassDef(HGEcalPhoton,1);
};

#endif