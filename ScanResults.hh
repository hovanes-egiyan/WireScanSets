/*
 * ScanResults.hh
 *
 *  Created on: Feb 3, 2017
 *      Author: hovanes
 */

#ifndef SCANRESULTS_HH_
#define SCANRESULTS_HH_

#include <iostream>
#include <string>
#include <vector>

#include <TNamed.h>

namespace WireScanSets {

class ScanResults : public TNamed {
protected:
    double zLocation = 0;

    // Sigmas and errors for different wire directions
    std::pair<double, double> sigma = { 0, 0 };

public:
    ScanResults() : TNamed(){}
    ScanResults( std::string name, double z, double sigma, double deltaSigma ) :
            TNamed( name.c_str(), name.c_str() ), zLocation( z ),
                    sigma( std::pair<double, double>( sigma, deltaSigma ) ) {
        return;
    }
    ScanResults( const ScanResults& scan ) :
            TNamed() {
        *this = scan;
    }
    virtual ~ScanResults() {
    }

    virtual ScanResults& operator=( const ScanResults& scan ) {
        if ( this == &scan ) return *this;
        *dynamic_cast<TNamed*>( this ) = *dynamic_cast<TNamed*>( scan.Clone(
                ( std::string( "clonOf_" ) + std::string( scan.GetName() ) ).c_str() ) );
        zLocation = scan.zLocation;
        sigma = scan.sigma;
        return *this;
    }

    virtual void Print() {
        std::cout << "Width for " << this->GetName() << " at location z= " << zLocation << " is " << sigma.first
                << " +- " << sigma.second << ". " << std::endl;
    }

    virtual const std::pair<double, double> getSigma2() const {
        return std::pair<double, double>( sigma.first * sigma.first, 2. * sigma.first * sigma.second );
    }

    virtual const std::pair<double, double>& getSigma() const {
        return sigma;
    }

    virtual void setSigma( const std::pair<double, double>& sigma = { 0, 0 } ) {
        this->sigma = sigma;
    }

    virtual double getLocation() const {
        return zLocation;
    }

    virtual void setLocation( double location = 0 ) {
        zLocation = location;
    }
};

} /* namespace WireScanSets */

#endif /* SCANRESULTS_HH_ */
