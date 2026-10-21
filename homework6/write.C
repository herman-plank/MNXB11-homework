#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
#include <iostream>
#include "MovingObject.h"

void write() {

    const UInt_t seed = 12345;
    gRandom->SetSeed(seed);


    TFile *file = new TFile("tree_file.root", "RECREATE");

    TTree *tree = new TTree("tree", "Tree storing 3D velocity measurements");

    MovingObject *obj = new MovingObject();
    tree->Branch("object", &obj);

    const Int_t nMeasurements = 10000;
    const Double_t mean = 0.0;
    const Double_t sigma = 0.30;

    for (Int_t i = 0; i < nMeasurements; ++i) {
        Double_t vx = gRandom->Gaus(mean, sigma);
        Double_t vy = gRandom->Gaus(mean, sigma);
        Double_t vz = gRandom->Gaus(mean, sigma);

        obj->SetVelocity(vx, vy, vz);
        tree->Fill();
    }

    tree->Write();
    file->Close();

    std::cout << "Generated and wrote " << nMeasurements
              << " entries to tree_file.root" << std::endl;

    delete obj;
    delete file;
}