/*
 * ScanSet.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: hovanes
 */

#include "ScanSet.hh"
#include "TF1.h"

using namespace std;

namespace WireScanSets {

ScanSet::~ScanSet() {
	for (auto& scanPtr : scanList) {
		if (scanPtr != nullptr)
			delete scanPtr;
	}
}

void ScanSet::Print() {
	cout << "Scan Set " << GetName() << " with emittance " << getEmittance()
			<< " : ";
	for (auto& scanPtr : scanList) {
		scanPtr->Print();
	}
}

TGraphErrors* ScanSet::makeGraphs() {
	vector<double> x;
	vector<double> sigma;
	vector<double> deltaSigma;

	vector<double> sigma2;
	vector<double> deltaSigma2;

	for (auto& scan : scanList) {
		x.push_back(scan->getLocation());
		sigma.push_back(scan->getSigma().first);
		deltaSigma.push_back(scan->getSigma().second);

		sigma2.push_back(scan->getSigma2().first);
		deltaSigma2.push_back(scan->getSigma2().second);
	}

	graphSigma = new TGraphErrors(x.size(), &(x[0]), &(sigma[0]), 0,
			&(deltaSigma[0]));
	graphSigma2 = new TGraphErrors(x.size(), &(x[0]), &(sigma2[0]), 0,
			&(deltaSigma2[0]));

	return graphSigma2;
}

TF1* ScanSet::fitGraphs(double xMin, double xMax, Color_t col) {
//    TF1* fitFun2 = new TF1( "sigma2", "pol2", xMin, xMax );
//    graphSigma2->Fit( fitFun2, "", "", xMin, xMax );
//
	TF1* fitFun2 = new TF1("sigma2", fitFuncSigma2(emittance), xMin, xMax, 2);
	fitFun2->SetParName(0, "alpha0");
	fitFun2->SetParName(1, "beta0");
	fitFun2->SetParameter(0, scanList[0]->getSigma2().second / emittance);
	fitFun2->SetParameter(1, 2.0e-35);
	fitFun2->SetParLimits(1, 1.0e-35, 10000000);

	graphSigma2->SetMarkerColor(col);
	graphSigma2->SetLineColor(col);

	fitFun2->SetLineColor(col);
	fitFun2->SetLineWidth(4);
	graphSigma2->Fit(fitFun2, "B", "", xMin, xMax);

	graphSigma->SetMarkerColor(col);
	graphSigma->SetLineColor(col);

//    TF1* fitFun = new TF1( "sigma", fitFuncSigma(emittance), xMin, xMax, 2 );
//    fitFun->SetParName( 0, "alpha0" );
//    fitFun->SetParName( 1, "beta0" );
//    fitFun->SetParameter( 0, scanList[0]->getSigma2().second / emittance );
//    fitFun->SetParameter( 1, 0.0 );
//    fitFun->SetParLimits( 1, 1.0e-25, 10000000);

	graphSigma->SetMarkerColor(col);
	graphSigma->SetLineColor(col);

//    fitFun->SetLineColor( col );
//    graphSigma->Fit( fitFun, "B", "", xMin, xMax );

//    TF1* fitFun1 = new TF1( "sigma", "pol1", xMin, xMax );
//    graphSigma->Fit( fitFun1, "", "", xMin, xMax );

	return fitFun2;
}

TF1* ScanSet::getUpperEdge(double xMin, double xMax, Color_t col) {
	TF1* upperEdge = new TF1("ul_sigma2", sigma2_plus_dSigma2(emittance), xMin,
			xMax, 4);
	upperEdge->SetParameter(0,
			graphSigma2->GetFunction("sigma2")->GetParameter(0));
	upperEdge->SetParameter(1,
			graphSigma2->GetFunction("sigma2")->GetParameter(1));
	upperEdge->SetParameter(2,
			graphSigma2->GetFunction("sigma2")->GetParError(0));
	upperEdge->SetParameter(3,
			graphSigma2->GetFunction("sigma2")->GetParError(1));
	upperEdge->SetLineColor(col);
	upperEdge->SetLineStyle(kDashed);
	return upperEdge;
}

TF1* ScanSet::getLowerEdge(double xMin, double xMax, Color_t col) {
	TF1* upperEdge = new TF1("ll_sigma2", sigma2_minus_dSigma2(emittance), xMin,
			xMax, 4);
	upperEdge->SetParameter(0,
			graphSigma2->GetFunction("sigma2")->GetParameter(0));
	upperEdge->SetParameter(1,
			graphSigma2->GetFunction("sigma2")->GetParameter(1));
	upperEdge->SetParameter(2,
			graphSigma2->GetFunction("sigma2")->GetParError(0));
	upperEdge->SetParameter(3,
			graphSigma2->GetFunction("sigma2")->GetParError(1));
	upperEdge->SetLineColor(col);
	upperEdge->SetLineStyle(kDashed);
	return upperEdge;
}

} /* namespace WireScanSets */
