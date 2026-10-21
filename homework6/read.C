#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>
#include "MovingObject.h"

void read() {
    
    TFile *file = TFile::Open("tree_file.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open tree_file.root." << std::endl;
        return;
    }

    TTree *tree = nullptr;
    file->GetObject("tree", tree);
    if (!tree) {
        std::cerr << "Error: Could not find tree 'tree' in file." << std::endl;
        file->Close();
        delete file;
        return;
    }

    MovingObject *obj = nullptr;
    tree->SetBranchAddress("object", &obj);

    Long64_t nEntries = tree->GetEntries();
    std::cout << "Successfully opened tree_file.root. Total entries: " << nEntries << std::endl;

    TH2D *h2 = new TH2D("h2_vxy", "Velocity Distribution;v_{x} [m/s];v_{y} [m/s];Counts",
                        100, -1.5, 1.5, 100, -1.5, 1.5);
    h2->SetDirectory(nullptr); 

    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        h2->Fill(obj->Vx(), obj->Vy());
    }

    gStyle->SetOptStat(1111);
    TCanvas *c1 = new TCanvas("c1_vxy", "2D Velocity Components", 800, 700);
    c1->SetRightMargin(0.14);
    h2->Draw("COLZ");
    c1->SaveAs("velocity_components.pdf");
    c1->SaveAs("velocity_components.png");

    
    TCanvas *c2 = new TCanvas("c2_scatter", "Scatter Plot with Cut", 800, 600);
    c2->SetRightMargin(0.08);


    const char *drawExpr = "object.HorizontalSpeed() : object.fVz";
    const char *cutExpr  = "object.Speed() > 0.50";

    tree->Draw(drawExpr, cutExpr, "SCAT");
    


    TH2F *htemp = (TH2F*)gPad->GetPrimitive("htemp");
    if (htemp) {
        htemp->SetTitle("Selected Measurements (v > 0.50 m/s);v_{z} [m/s];v_{xy} [m/s]");
        htemp->SetStats(kFALSE);
    }
    c2->Modified();
    c2->Update();
    c2->SaveAs("speed_selection_scatter.pdf");
    c2->SaveAs("speed_selection_scatter.png");

    file->Close();
    delete file;
    delete obj;
}
