/*
 * readScanArrayJSON.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: Hovanes Egiyan
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

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

#include "FileNameFinder.hh"

using namespace std;

int main(int argc, char **argv) {

	for (int sig = 0; sig < kMAXSIGNALS; sig++) {
		gSystem->ResetSignal((ESignals) sig);
	}

	WireScanSets::FileNameFinder fileFinder( &argc, argv );
	TApplication theApp("App", &argc, argv);

	string fileName = fileFinder.getFullFileName();

	std::cout << "Reading scans from " << fileName << std::endl;
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		std::string errMsg = "Could not find file " + fileName;
		throw std::runtime_error(errMsg);
	}
	std::cout << "  Found JSON file " << fileName << std::endl;
	Json::Value scanListJSON;
	Json::Reader reader;
	bool parsing_success = reader.parse(ifs, scanListJSON);

	if (!parsing_success) {
		std::string errMsg = "Parsing failed for file " + fileName;
		throw std::runtime_error(errMsg);
	}
	std::cout << "  Parsing successful\n";

	// Create List of Scan objects by looping through the JSON array and picking JSON objects.
	vector<WireScanSets::Scan> scanList;
	if( scanListJSON.isArray() ) {
		for( auto& scanJSON : scanListJSON ) {
			scanList.push_back( WireScanSets::ScanJSON(scanJSON) );
		}
	}

	cout << "Creating sets" << endl;

	WireScanSets::ScanSet setX(scanList, "X");
	WireScanSets::ScanSet setY(scanList, "Y");
	scanList.clear();

	setX.makeGraphs();
	setX.fitGraphs(0, 90000, kGreen);

	setY.makeGraphs();
	setY.fitGraphs(0, 90000, kBlue);

	TCanvas canv("Canv", "Canv", 1800, 800);
	canv.Divide(2, 1, 0.01, 0.01);

	TH1D zeroX("zeroX", "zerox", 100, -1000, 90000);
	zeroX.SetMinimum(0);
	zeroX.SetMaximum(4.0);
	zeroX.SetXTitle("Distance from 5C11 harp, mm");
	zeroX.SetYTitle("#sigma_{x}^{2} (mm^{2})");
	zeroX.GetYaxis()->SetTitleOffset(1.2);

	TH1D zeroY("zeroY", "zeroY", 100, -1000, 90000);
	zeroY.SetMinimum(0);
	zeroY.SetMaximum(4.0);
	zeroY.SetXTitle("Distance from 5C11 harp, mm");
	zeroY.SetYTitle("#sigma_{y}^{2} (mm^{2})");
	zeroY.GetYaxis()->SetTitleOffset(1.2);

	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gStyle->SetOptFit(1);

	canv.cd(1);
	gPad->SetGrid(1, 1);
	zeroX.Draw();
	setX.getGraphSigma2()->SetMarkerStyle(8);
	setX.getGraphSigma2()->SetMarkerSize(1.2);
	setX.getGraphSigma2()->Draw("P");
	setX.getUpperEdge(0, 90000, kGreen)->Draw("same");
	setX.getLowerEdge(0, 90000, kGreen)->Draw("same");

	canv.cd(2);
	gPad->SetGrid(1, 1);
	zeroY.Draw();
	setY.getGraphSigma2()->SetMarkerStyle(21);
	setY.getGraphSigma2()->SetMarkerSize(1.2);
	setY.getGraphSigma2()->Draw("P");
	setY.getUpperEdge(0, 90000, kBlue)->Draw("same");
	setY.getLowerEdge(0, 90000, kBlue)->Draw("same");

	theApp.Run();

	cout << "Exiting" << endl;

	return 0;
}
