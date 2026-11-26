#ifndef HGCONVERSIONPHOTONSIM_H
#define HGCONVERSIONPHOTONSIM_H


#include "HGConversionPhoton.h"

class HGConversionPhotonSim: public HGConversionPhoton{
private:
	//only sim-related stuff (rest in inherited)
    Float_t fConvVertexXgeant, fConvVertexYgeant, fConvVertexZgeant;
    Int_t fIDe, fIDp, fTracke, fTrackp, fParentIDe, fParentIDp, fParentTracke, fParentTrackp, fGParentIDe, fGParentIDp, fGParentTracke, fGParentTrackp;
    Bool_t fInAcceptance, fAdded; //acceptance flag & extra added flag

public:
    HGConversionPhotonSim();
    HGConversionPhotonSim(Float_t Px, Float_t Py, Float_t Pz, Float_t E);
    ~HGConversionPhotonSim(){};

    void setElectronID(Int_t id) {fIDe=id;}
    void setPositronID(Int_t id) {fIDp=id;}
    void setElectronTrack(Int_t track) {fTracke=track;}
    void setPositronTrack(Int_t track) {fTrackp=track;}
    void setElectronParentID(Int_t parId) {fParentIDe=parId;}
    void setPositronParentID(Int_t parId) {fParentIDp=parId;}
    void setElectronParentTrack(Int_t parTrack) {fParentTracke=parTrack;}
    void setPositronParentTrack(Int_t parTrack) {fParentTrackp=parTrack;}
    void setElectronGrandParentID(Int_t parId) {fGParentIDe=parId;}
    void setPositronGrandParentID(Int_t parId) {fGParentIDp=parId;}
    void setElectronGrandParentTrack(Int_t parTrack) {fGParentTracke=parTrack;}
    void setPositronGrandParentTrack(Int_t parTrack) {fGParentTrackp=parTrack;}
    void setAcceptanceFlag(Bool_t inAcc) {fInAcceptance=inAcc;}
    void setAddedFlag(Bool_t isAdded) {fAdded=isAdded;}

    Int_t getElectronID(){return fIDe;}
    Int_t getPositronID(){return fIDp;}
    Int_t getElectronTrack(){return fTracke;}
    Int_t getPositronTrack(){return fTrackp;}
    Int_t getElectronParentID(){return fParentIDe;}
    Int_t getPositronParentID(){return fParentIDp;}
    Int_t getElectronParentTrack(){return fParentTracke;}
    Int_t getPositronParentTrack(){return fParentTrackp;}
    Int_t getElectronGrandParentID(){return fGParentIDe;}
    Int_t getPositronGrandParentID(){return fGParentIDp;}
    Int_t getElectronGrandParentTrack(){return fGParentTracke;}
    Int_t getPositronGrandParentTrack(){return fGParentTrackp;}
    Bool_t getAcceptanceFlag(){return fInAcceptance;}
    Bool_t getAddedFlag(){return fAdded;}

    void setConversionGeantVertex(Float_t cvX, Float_t cvY, Float_t cvZ);
    void setConversionGeantVertex(HGeomVector &vtx);
    HGeomVector getConversionGeantVertex();

    ClassDef(HGConversionPhotonSim,1);
};

#endif