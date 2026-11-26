#ifndef HGECALPHOTONSIM_H
#define HGECALPHOTONSIM_H

#include "HGEcalPhoton.h"

class HGEcalPhotonSim: public HGEcalPhoton{
private:
	//extra sim stuff
    Int_t fID, fTrack, fParentID, fParentTrack;
    Bool_t fInAcceptance, fAdded, fGoodCluster; //acceptance flag & extra added flag
public:
    HGEcalPhotonSim(); //default - 0's all the way
    HGEcalPhotonSim(Float_t Px, Float_t Py, Float_t Pz);
    ~HGEcalPhotonSim(){};

    void setID(Int_t id) {fID=id;}
    void setTrack(Int_t track) {fTrack=track;}
    void setParentID(Int_t parId) {fParentID=parId;}
    void setParentTrack(Int_t parTrack) {fParentTrack=parTrack;}
    void setAcceptanceFlag(Bool_t inAcc) {fInAcceptance=inAcc;}
    void setAddedFlag(Bool_t isAdded) {fAdded=isAdded;}
    void setClusterFlag(Bool_t isGood) {fGoodCluster=isGood;}

    Int_t getID(){return fID;}
    Int_t getTrack(){return fTrack;}
    Int_t getParentID(){return fParentID;}
    Int_t getParentTrack(){return fParentTrack;}
    Bool_t getAcceptanceFlag(){return fInAcceptance;}
    Bool_t getAddedFlag(){return fAdded;}
    Bool_t getClusterFlag() {return fGoodCluster;}

    ClassDef(HGEcalPhotonSim,1);
};

#endif
