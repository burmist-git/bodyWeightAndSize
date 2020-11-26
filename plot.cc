/***********************************************************************
* Copyright(C) 2020 - LBS - (Single person developer.)                 *
* Tue Mar 24 17:56:37 CET 2020                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libpushVectorInRoot.h"

//root
#include "TROOT.h"
#include "TStyle.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TGaxis.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
  if(argc == 4 && atoi(argv[1])==0){
    TString rootFileIn = argv[2];
    TString vecNamesFile = argv[3];
    Int_t saveKey = 1;
    Double_t timeAxisLabelOffset = 0.02;
    std::vector<TGraph*> gr_v = getGraphsVector (rootFileIn, vecNamesFile, saveKey);
    TGraph *gr_size_vs_time_norm = new TGraph();
    gr_size_vs_time_norm->SetTitle("size vs time norm");
    gr_size_vs_time_norm->SetName("gr_size_vs_time_norm");
    //
    Double_t weight_min = 75;
    Double_t weight_max = 100;
    Double_t size_min   = 75;
    Double_t size_max   = 100;
    Double_t ktr = (weight_max - weight_min)/(size_max - size_min); 
    ////
    TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,800);
    gStyle->SetPalette(1);
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetStatColor(kWhite);
    c1->SetRightMargin(0.12);
    c1->SetLeftMargin(0.12);
    c1->SetTopMargin(0.1);
    c1->SetBottomMargin(0.15);
    c1->SetGrid();
    //
    gr_v.at(0)->SetLineColor(kRed);
    gr_v.at(0)->SetMarkerColor(kRed);
    gr_v.at(0)->SetMarkerStyle(20);
    gr_v.at(0)->SetLineStyle(kSolid);
    gr_v.at(0)->SetMinimum(weight_min);
    gr_v.at(0)->SetMaximum(weight_max);
    //gr_v.at(0)->Draw("APL");
    //gr_v.at(0)->GetYaxis()->SetTitle("Weight, kg");  
    //gr_v.at(0)->GetXaxis()->SetTimeDisplay(1);
    //gr_v.at(0)->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M}%F1970-01-01 00:00:00");
    //gr_v.at(0)->GetXaxis()->SetLabelOffset(timeAxisLabelOffset);
    //
    gr_v.at(1)->SetLineColor(kBlue);
    gr_v.at(1)->SetMarkerColor(kBlue);
    gr_v.at(1)->SetMarkerStyle(20);
    gr_v.at(1)->SetLineStyle(kSolid);
    gr_v.at(1)->SetMinimum(size_min);
    gr_v.at(1)->SetMaximum(size_max);
    //gr_v.at(1)->Draw("APL");
    //gr_v.at(1)->GetYaxis()->SetTitle("Size, cm");  
    //gr_v.at(1)->GetXaxis()->SetTimeDisplay(1);
    //gr_v.at(1)->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M}%F1970-01-01 00:00:00");
    //gr_v.at(1)->GetXaxis()->SetLabelOffset(timeAxisLabelOffset);
    //
    for(Int_t i = 0;i<gr_v.at(1)->GetN();i++){
      Double_t x,y;
      gr_v.at(1)->GetPoint(i,x,y);
      gr_size_vs_time_norm->SetPoint(i,x,y/ktr);
    }
    gr_size_vs_time_norm->SetLineColor(kBlue);
    gr_size_vs_time_norm->SetMarkerColor(kBlue);
    gr_size_vs_time_norm->SetMarkerStyle(20);
    gr_size_vs_time_norm->SetLineStyle(kSolid);
    gr_size_vs_time_norm->SetMinimum(size_min);
    gr_size_vs_time_norm->SetMaximum(size_max);
    // 
    TMultiGraph *mg = new TMultiGraph();
    TString mgTitle = "Body weight and size";
    TString mgName = "mg";
    mg->Add(gr_v.at(0));
    mg->Add(gr_size_vs_time_norm);
    mg->SetTitle(mgTitle.Data());
    mg->SetName(mgName.Data());
    mg->SetMaximum(weight_max);
    mg->SetMinimum(weight_min);
    mg->Draw("APL");
    mg->GetXaxis()->SetTimeDisplay(1);
    mg->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M}%F1970-01-01 00:00:00");
    mg->GetXaxis()->SetLabelOffset(timeAxisLabelOffset);
    mg->GetXaxis()->SetLabelSize(0.025);
    mg->GetYaxis()->SetTitle("Weight, kg");
    TGaxis *axis = new TGaxis( gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(), size_min, size_max, 510, "+L");
    axis->SetLineColor(kBlack);
    axis->SetLabelColor(kBlack);
    axis->SetTitle("Size, cm");
    axis->Draw();
    //
    TString pdfOutFile = rootFileIn;
    pdfOutFile += ".pdf";
    c1->SaveAs(pdfOutFile.Data());
  }
  else{
    cout<<" --> ERROR in input arguments "<<endl
	<<" runID [1] = 0 (execution ID number)"<<endl
      	<<"       [2] - rootFileIn"<<endl
	<<"       [3] - vecNamesFile"<<endl;
  }
  return 0;
}
