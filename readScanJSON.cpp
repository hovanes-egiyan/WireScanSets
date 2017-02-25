/*
 * readScanJSON.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: hovanes
 */

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
#include <fstream>
#include <string>
#include <map>

#include <json/json.h>

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

bool readScanFile( string fileName ) {
    cout << "Reading scan from " << fileName << endl;
    std::ifstream ifs( fileName );
    if ( !ifs.is_open() ) {
        cout << "Could not find file " << fileName << endl;
        return false;
    }
    std::cout << "  Found JSON file " << fileName << std::endl;
    Json::Value scanJSON;
    Json::Reader reader;
    bool parsing_success = reader.parse( ifs, scanJSON );

    if ( !parsing_success ) {
        std::cout << "  Parsing failed\n";
        return false;
    } else
        std::cout << "  Parsing successful\n";

    try {
        WireScanSets::ScanSetJSON scanSet( scanJSON );
    } catch  ( const std::runtime_error& e ) {
        cerr << e.what() << endl;
    }
    return true;
}

int main( int argc, char **argv ) {

    TApplication theApp( "App", &argc, argv );

    // February 22, 2017, after focusing improvement
    WireScanSets::ScanResults resultsX_5C11( string( "5C11_X" ), 0, 0.8458, 0.050 );
    WireScanSets::ScanResults resultsX_5C11B( string( "5C11B_X" ), 12163, 0.6540, 0.050 );
    WireScanSets::ScanResults resultsX_Rad( string( "Radiator_X" ), 16420, 0.7113, 0.025 );

    WireScanSets::ScanResults resultsY_5C11( string( "5C11_Y" ), 0, 0.5498, 0.050 );
    WireScanSets::ScanResults resultsY_5C11B( string( "5C11B_Y" ), 12163, 0.4845, 0.050 );
    WireScanSets::ScanResults resultsY_Rad( string( "Radiator_Y" ), 16420, 0.4197, 0.025 );

    WireScanSets::ScanSet setXfeb9( "Feb09X", 5.1855e-6 );
    setXfeb9.addScanResults( resultsX_5C11 );
    setXfeb9.addScanResults( resultsX_5C11B );
    setXfeb9.addScanResults( resultsX_Rad );

    WireScanSets::ScanSet setYfeb9( "Feb09Y", 2.1567e-06 );
    setYfeb9.addScanResults( resultsY_5C11 );
    setYfeb9.addScanResults( resultsY_5C11B );
    setYfeb9.addScanResults( resultsY_Rad );

//    setXfeb9.Print();

    setXfeb9.makeGraphs();
    setXfeb9.fitGraphs( 0, 90000, kGreen );

    setYfeb9.makeGraphs();
    setYfeb9.fitGraphs( 0, 90000, kBlue );

    TCanvas canv( "Canv", "Canv", 1800, 800 );
    canv.Divide( 2, 1, 0.01, 0.01 );

    TH1D zeroX( "zeroX", "zerox", 100, -1000, 90000 );
    zeroX.SetMinimum( 0 );
    zeroX.SetMaximum( 1.2 );
    zeroX.SetXTitle( "Distance from 5C11 harp, mm" );
    zeroX.SetYTitle( "#sigma_{x}^{2} (mm^{2})" );
    zeroX.GetYaxis()->SetTitleOffset( 1.2 );

    TH1D zeroY( "zeroY", "zeroY", 100, -1000, 90000 );
    zeroY.SetMinimum( 0 );
    zeroY.SetMaximum( 1.2 );
    zeroY.SetXTitle( "Distance from 5C11 harp, mm" );
    zeroY.SetYTitle( "#sigma_{y}^{2} (mm^{2})" );
    zeroY.GetYaxis()->SetTitleOffset( 1.2 );

    gStyle->SetOptStat( 0 );
    gStyle->SetOptTitle( 0 );
    gStyle->SetOptFit( 1 );

    canv.cd( 1 );
    gPad->SetGrid( 1, 1 );
    zeroX.Draw();
    setXfeb9.getGraphSigma2()->SetMarkerStyle( 8 );
    setXfeb9.getGraphSigma2()->SetMarkerSize( 1.2 );
    setXfeb9.getGraphSigma2()->Draw( "P" );
    setXfeb9.getUpperEdge( 0, 90000, kGreen )->Draw( "same" );
    setXfeb9.getLowerEdge( 0, 90000, kGreen )->Draw( "same" );

    canv.cd( 2 );
    gPad->SetGrid( 1, 1 );
    zeroY.Draw();
    setYfeb9.getGraphSigma2()->SetMarkerStyle( 21 );
    setYfeb9.getGraphSigma2()->SetMarkerSize( 1.2 );
    setYfeb9.getGraphSigma2()->Draw( "P" );
    setYfeb9.getUpperEdge( 0, 90000, kBlue )->Draw( "same" );
    setYfeb9.getLowerEdge( 0, 90000, kBlue )->Draw( "same" );

    theApp.Run();

    return 0;
}
