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
#include <TSystem.h>

#include "ScanResult.hh"
#include "ScanSet.hh"
#include "Scan.hh"

#include "ScanJSON.hh"
#include "ScanResultJSON.hh"

using namespace std;

bool readScanFile( string fileName ) {
//    cout << "Reading scan from " << fileName << endl;
//    std::ifstream ifs( fileName );
//    if ( !ifs.is_open() ) {
//        cout << "Could not find file " << fileName << endl;
//        return false;
//    }
//    std::cout << "  Found JSON file " << fileName << std::endl;
//    Json::Value scanJSON;
//    Json::Reader reader;
//    bool parsing_success = reader.parse( ifs, scanJSON );
//
//    if ( !parsing_success ) {
//        std::cout << "  Parsing failed\n";
//        return false;
//    } else
//        std::cout << "  Parsing successful\n";
//
//    try {
//        WireScanSets::ScanSetJSON scanSet( scanJSON );
//    } catch  ( const std::runtime_error& e ) {
//        cerr << e.what() << endl;
//    }
    return true;
}


int main( int argc, char **argv ) {

		for (int sig = 0; sig < kMAXSIGNALS; sig++) {
			gSystem->ResetSignal((ESignals) sig);
		}


    TApplication theApp( "App", &argc, argv );

	map<string, WireScanSets::Scan*> scanMap = {
			{ "scan5C11.json", new WireScanSets::ScanJSON("scan5C11.json") },
			{ "scan5C11B.json", new WireScanSets::ScanJSON("scan5C11B.json") },
			{ "scanRadiator.json", new WireScanSets::ScanJSON("scanRadiator.json") }
	};

	for( auto& scanIt : scanMap ) {
		cout << "Scan key is " << scanIt.first << " Scan pointer is " << scanIt.second << endl;
		cout << "X result is " << scanIt.second->getResult("X") << endl;
	}

	usleep( 2000000 );

	cout << "Creating sets" << endl;
	WireScanSets::ScanSet setX( scanMap, string("X") );
	WireScanSets::ScanSet setY( scanMap, string("Y") );

	scanMap.clear();

    setX.makeGraphs();
    setX.fitGraphs( 0, 90000, kGreen );

    setY.makeGraphs();
    setY.fitGraphs( 0, 90000, kBlue );

    TCanvas canv( "Canv", "Canv", 1800, 800 );
    canv.Divide( 2, 1, 0.01, 0.01 );

    TH1D zeroX( "zeroX", "zerox", 100, -1000, 90000 );
    zeroX.SetMinimum( 0 );
    zeroX.SetMaximum( 4.0 );
    zeroX.SetXTitle( "Distance from 5C11 harp, mm" );
    zeroX.SetYTitle( "#sigma_{x}^{2} (mm^{2})" );
    zeroX.GetYaxis()->SetTitleOffset( 1.2 );

    TH1D zeroY( "zeroY", "zeroY", 100, -1000, 90000 );
    zeroY.SetMinimum( 0 );
    zeroY.SetMaximum( 4.0 );
    zeroY.SetXTitle( "Distance from 5C11 harp, mm" );
    zeroY.SetYTitle( "#sigma_{y}^{2} (mm^{2})" );
    zeroY.GetYaxis()->SetTitleOffset( 1.2 );

    gStyle->SetOptStat( 0 );
    gStyle->SetOptTitle( 0 );
    gStyle->SetOptFit( 1 );

    canv.cd( 1 );
    gPad->SetGrid( 1, 1 );
    zeroX.Draw();
    setX.getGraphSigma2()->SetMarkerStyle( 8 );
    setX.getGraphSigma2()->SetMarkerSize( 1.2 );
    setX.getGraphSigma2()->Draw( "P" );
    setX.getUpperEdge( 0, 90000, kGreen )->Draw( "same" );
    setX.getLowerEdge( 0, 90000, kGreen )->Draw( "same" );

    canv.cd( 2 );
    gPad->SetGrid( 1, 1 );
    zeroY.Draw();
    setY.getGraphSigma2()->SetMarkerStyle( 21 );
    setY.getGraphSigma2()->SetMarkerSize( 1.2 );
    setY.getGraphSigma2()->Draw( "P" );
    setY.getUpperEdge( 0, 90000, kBlue )->Draw( "same" );
    setY.getLowerEdge( 0, 90000, kBlue )->Draw( "same" );

    theApp.Run();

    cout << "Exiting" << endl;

    return 0;
}
