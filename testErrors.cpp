/*
 * testErrors.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: hovanes
 */




#include <iostream>
#include <string>
//#include <pair>
#include <map>

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TStyleManager.h>
#include <TF1.h>

#include "ScanResults.hh"
#include "ScanSet.hh"

using namespace std;

int main( int argc, char **argv ) {

    cout << "Starting" << endl;

    TApplication theApp("App", &argc, argv);

    TF1* fitFun2 = new TF1( "sigma2", WireScanSets::ScanSet::fitFuncSigma2( 5.1855e-6 ), -100, 90000, 2 );
    fitFun2->SetParName( 0, "alpha0" );
    fitFun2->SetParName( 1, "beta0" );
    fitFun2->SetParameter( 0, 3.644 );
    fitFun2->SetParameter( 1, 2.178e+05 );
    fitFun2->SetParError( 0, 0.855 );
    fitFun2->SetParError( 1, 2.012e+04 );
    fitFun2->SetParError( 0, 0 );
    fitFun2->SetParError( 1, 0 );

    fitFun2->SetLineColor( 1 );
    fitFun2->SetLineWidth( 4 );

    cout << "Drawing" << endl;

    fitFun2->Draw("l");

    TF1* upperEdge = new TF1( "ul_sigma2", WireScanSets::ScanSet::sigma2_plus_dSigma2( 5.1855e-6 ), -100, 90000, 4 );
    upperEdge->SetParameter( 0, 3.644 );
    upperEdge->SetParameter( 1, 2.178e+05 );
    upperEdge->SetParameter( 2, 0.855);
    upperEdge->SetParameter( 3, 2.012e+04 );
    upperEdge->SetLineColor( 1 );
    upperEdge->SetLineStyle( kDashed );
    upperEdge->Draw("same");


    theApp.Run();

    return 0;
}
