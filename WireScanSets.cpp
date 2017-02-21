//============================================================================
// Name        : WireScanSets.cpp
// Author      : Hovanes Egiyan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

//#include <stdio.h>
//#include <stdlib.h>

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

//	puts("!!!Hello World!!!");

    TApplication theApp("App", &argc, argv);


//    // Feb 09, 2017
//    WireScanSets::ScanResults resultsX_5C11( string( "5C11_X" ),         0, 0.9780, 0.050 );
//    WireScanSets::ScanResults resultsX_5C11B( string( "5C11B_X" ),   12163, 0.9495, 0.050 );
//    WireScanSets::ScanResults resultsX_Rad( string( "Radiator_X" ),  16420, 0.8507, 0.025 );
//
//
//    WireScanSets::ScanResults resultsY_5C11( string( "5C11_Y" ),         0, 0.4404, 0.050 );
//    WireScanSets::ScanResults resultsY_5C11B( string( "5C11B_Y" ),   12163, 0.4255, 0.050 );
//    WireScanSets::ScanResults resultsY_Rad( string( "Radiator_Y" ),  16420, 0.3458, 0.025 );

//    // Feb 15, 2017, after tuning by Todd
//    WireScanSets::ScanResults resultsX_5C11( string( "5C11_X" ),         0, 1.1530, 0.050 );
//    WireScanSets::ScanResults resultsX_5C11B( string( "5C11B_X" ),   12163, 0.9290, 0.050 );
//    WireScanSets::ScanResults resultsX_Rad( string( "Radiator_X" ),  16420, 0.7822, 0.025 );
//
//
//    WireScanSets::ScanResults resultsY_5C11( string( "5C11_Y" ),         0, 0.5229, 0.050 );
//    WireScanSets::ScanResults resultsY_5C11B( string( "5C11B_Y" ),   12163, 0.504, 0.050 );
//    WireScanSets::ScanResults resultsY_Rad( string( "Radiator_Y" ),  16420, 0.3213, 0.05 );


//    // Feb 15, 2017, after tuning by Todd, verifying
//    WireScanSets::ScanResults resultsX_5C11( string( "5C11_X" ),         0, 1.0730, 0.040 );
//    WireScanSets::ScanResults resultsX_5C11B( string( "5C11B_X" ),   12163, 0.8118, 0.040 );
//    WireScanSets::ScanResults resultsX_Rad( string( "Radiator_X" ),  16420, 0.7822, 0.015 );
//
//
//    WireScanSets::ScanResults resultsY_5C11( string( "5C11_Y" ),         0, 0.5150, 0.050 );
//    WireScanSets::ScanResults resultsY_5C11B( string( "5C11B_Y" ),   12163, 0.4979, 0.050 );
//    WireScanSets::ScanResults resultsY_Rad( string( "Radiator_Y" ),  16420, 0.3213, 0.035 );
//


//    // April 9, 2016, after tuning by Todd
//    WireScanSets::ScanResults resultsX_5C11( string( "5C11_X" ),         0, 1.2134, 0.060 );
//    WireScanSets::ScanResults resultsX_5C11B( string( "5C11B_X" ),   12163, 0.9496, 0.060 );
//    WireScanSets::ScanResults resultsX_Rad( string( "Radiator_X" ),  16420, 0.8414, 0.025 );
//
//
//    WireScanSets::ScanResults resultsY_5C11( string( "5C11_Y" ),         0, 0.6850, 0.060 );
//    WireScanSets::ScanResults resultsY_5C11B( string( "5C11B_Y" ),   12163, 0.6447, 0.060 );
//    WireScanSets::ScanResults resultsY_Rad( string( "Radiator_Y" ),  16420, 0.4683, 0.025 );


    // December 17, 2017, after quick tuning by Todd
    WireScanSets::ScanResults resultsX_5C11( string( "5C11_X" ),         0, 2.1840, 0.150 );
    WireScanSets::ScanResults resultsX_5C11B( string( "5C11B_X" ),   12163, 2.0360, 0.150 );
    WireScanSets::ScanResults resultsX_Rad( string( "Radiator_X" ),  16420, 0.4800, 0.060 );


    WireScanSets::ScanResults resultsY_5C11( string( "5C11_Y" ),         0, 0.9192, 0.080 );
    WireScanSets::ScanResults resultsY_5C11B( string( "5C11B_Y" ),   12163, 0.9260, 0.080 );
    WireScanSets::ScanResults resultsY_Rad( string( "Radiator_Y" ),  16420, 0.3100, 0.050 );



//    WireScanSets::ScanSet setXfeb9( "Feb09X", 5.14e-6 );
    WireScanSets::ScanSet setXfeb9( "Dec17_2016X", 6.3574e-6 );
//    WireScanSets::ScanSet setXfeb9( "Feb09X", 5.1855e-6 );
    setXfeb9.addScanResults( resultsX_5C11 );
    setXfeb9.addScanResults( resultsX_5C11B );
    setXfeb9.addScanResults( resultsX_Rad);

    //    WireScanSets::ScanSet setYfeb9( "Feb09Y", 3.44e-06 );
    WireScanSets::ScanSet setYfeb9( "Dec17_2016Y", 3.8591e-06 );
//    WireScanSets::ScanSet setYfeb9( "Feb09Y", 2.1567e-06 );
    setYfeb9.addScanResults( resultsY_5C11 );
    setYfeb9.addScanResults( resultsY_5C11B );
    setYfeb9.addScanResults( resultsY_Rad);

//    setXfeb9.Print();

    setXfeb9.makeGraphs();
    setXfeb9.fitGraphs( 0, 90000, kGreen );

    setYfeb9.makeGraphs();
    setYfeb9.fitGraphs( 0, 90000, kBlue );

    TCanvas canv( "Canv", "Canv", 1800, 800 );
    canv.Divide(2,1, 0.01, 0.01 );


    TH1D zeroX( "zeroX", "zerox", 100, -1000, 90000 );
    zeroX.SetMinimum( 0 );
    zeroX.SetMaximum( 5.0 );
    zeroX.SetXTitle( "Distance from 5C11 harp, mm");
    zeroX.SetYTitle( "#sigma_{x}^{2} (mm^{2})");
    zeroX.GetYaxis()->SetTitleOffset(1.2);

    TH1D zeroY( "zeroY", "zeroY", 100, -1000, 90000 );
    zeroY.SetMinimum( 0 );
    zeroY.SetMaximum( 1.6 );
    zeroY.SetXTitle( "Distance from 5C11 harp, mm");
    zeroY.SetYTitle( "#sigma_{y}^{2} (mm^{2})");
    zeroY.GetYaxis()->SetTitleOffset(1.2);

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit(1);

    canv.cd(1);
    gPad->SetGrid(1, 1);
    zeroX.Draw();
    setXfeb9.getGraphSigma2()->SetMarkerStyle( 8 );
    setXfeb9.getGraphSigma2()->SetMarkerSize(1.2);
    setXfeb9.getGraphSigma2()->Draw("P");
    setXfeb9.getUpperEdge(0, 90000, kGreen )->Draw("same");
    setXfeb9.getLowerEdge(0, 90000, kGreen )->Draw("same");

    canv.cd(2);
    gPad->SetGrid(1, 1);
    zeroY.Draw();
    setYfeb9.getGraphSigma2()->SetMarkerStyle( 21 );
    setYfeb9.getGraphSigma2()->SetMarkerSize(1.2);
    setYfeb9.getGraphSigma2()->Draw("P");
    setYfeb9.getUpperEdge(0, 90000, kBlue )->Draw("same");
    setYfeb9.getLowerEdge(0, 90000, kBlue )->Draw("same");

//    setXfeb9.getGraphSigma()->SetMarkerStyle( 8 );
//    setXfeb9.getGraphSigma()->SetMarkerSize(1.2);
//    setXfeb9.getGraphSigma()->Draw("P");
//    setYfeb9.getGraphSigma()->SetMarkerStyle( 21 );
//    setYfeb9.getGraphSigma()->SetMarkerSize(1.2);
//    setYfeb9.getGraphSigma()->Draw("P");

//    usleep( 3000000 );

//    resultsX_5C11.Print();
//    resultsX_5C11B.Print();
//    resultsX_Rad.Print();


    theApp.Run();

//	cout << results.getSigma2X() << " : " << results.getSigma2Y() << endl;

    return 0;
}
