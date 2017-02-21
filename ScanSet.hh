/*
 * ScanSet.hh
 *
 *  Created on: Feb 6, 2017
 *      Author: hovanes
 */

#ifndef SCANSET_HH_
#define SCANSET_HH_

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "TGraphErrors.h"

#include "ScanResults.hh"
#include "FunctionOfEmittance.hh"
#include "DerivativeFunctionOfEpsilon.hh"
#include "BoundaryFuncionOfEmmitance.hh"

namespace WireScanSets {

class ScanSet : public TNamed, public FunctionOfEmittance {
public:
    std::vector<ScanResults*> scanList;

    TGraphErrors* graphSigma = 0;
    TGraphErrors* graphSigma2 = 0;

    class fitFuncSigma2 : public FunctionOfEmittance {
    public:
        fitFuncSigma2( double epsilon ) :
                FunctionOfEmittance( epsilon ) {
        }
        fitFuncSigma2( const fitFuncSigma2& obj ) :
                FunctionOfEmittance( obj ) {
        }
        double operator()( double* x, double* p ) {
            double alpha0 = p[0];
            double beta0 = p[1];
            double xVal = x[0];
            double value = 0;
            if ( beta0 > 1.0e-25 ) {
                value = emmitance
                        * ( ( ( 1 + alpha0 * alpha0 ) / ( beta0 ) ) * xVal * xVal - 2.0 * alpha0 * xVal + beta0 );
            }
            return value;
        }
    };

    class dSigma2_dAlpha0 : public DerivativeFunctionOfEpsilon {
    public:
        dSigma2_dAlpha0( double epsilon ) :
                DerivativeFunctionOfEpsilon( epsilon ) {
        }
        dSigma2_dAlpha0( const dSigma2_dAlpha0& obj ) :
                DerivativeFunctionOfEpsilon( obj ) {
        }
        double operator()( double* x, double* p ) {
            double alpha0 = p[0];
            double beta0 = p[1];
            double xVal = x[0];
            double value = 0;
            if ( beta0 > 1.0e-25 ) {
                value = emmitance * ( ( ( 2.0 * alpha0 ) / ( beta0 ) ) * xVal * xVal - 2.0 * xVal );
            }
            return value;
        }
    };

    class dSigma2_dBeta0 : public DerivativeFunctionOfEpsilon {
    public:
        dSigma2_dBeta0( double epsilon ) :
                DerivativeFunctionOfEpsilon( epsilon ) {
        }
        dSigma2_dBeta0( const dSigma2_dBeta0& obj ) :
                DerivativeFunctionOfEpsilon( obj ) {
        }
        double operator()( double* x, double* p ) {
            double alpha0 = p[0];
            double beta0 = p[1];
            double xVal = x[0];
            double value = 0;
            if ( beta0 > 1.0e-25 ) {
                value = emmitance * ( ( ( 1 + alpha0 * alpha0 ) / ( beta0 * beta0 ) ) * ( -1.0 ) * xVal * xVal + 1.0 );
            }
            return value;
        }
    };

    class sigma2_plus_dSigma2 : public BoundaryFuncionOfEmmitance {
    public:
        sigma2_plus_dSigma2( double epsilon ) :
                BoundaryFuncionOfEmmitance( epsilon, +1 ) {
            dFdX1 =  new dSigma2_dAlpha0( epsilon ) ;
            dFdX2 =  new dSigma2_dBeta0( epsilon ) ;
            meanValue = new fitFuncSigma2( epsilon ) ;
        }
        sigma2_plus_dSigma2( const sigma2_plus_dSigma2& obj ) :
                BoundaryFuncionOfEmmitance( obj ) {
        }
        virtual ~sigma2_plus_dSigma2() {
//            if ( dFdX1 != nullptr ) delete dFdX1;
//            if ( dFdX2 != nullptr ) delete dFdX2;
//            if ( meanValue != nullptr ) delete meanValue;
        }
    };
    class sigma2_minus_dSigma2 : public BoundaryFuncionOfEmmitance {
    public:
        sigma2_minus_dSigma2( double epsilon ) :
                BoundaryFuncionOfEmmitance( epsilon, -1 ) {
            dFdX1 =  new dSigma2_dAlpha0( epsilon ) ;
            dFdX2 =  new dSigma2_dBeta0( epsilon ) ;
            meanValue = new fitFuncSigma2( epsilon ) ;
        }
        sigma2_minus_dSigma2( const sigma2_minus_dSigma2& obj ) :
                BoundaryFuncionOfEmmitance( obj ) {
        }
        virtual ~sigma2_minus_dSigma2() {
//            if ( dFdX1 != nullptr ) delete dFdX1;
//            if ( dFdX2 != nullptr ) delete dFdX2;
//            if ( meanValue != nullptr ) delete meanValue;
        }
    };

//    class fitFuncSigma {
//    protected:
//        fitFuncSigma2 fun2;
//    public:
//        fitFuncSigma( double epsilon ) :
//                fun2( epsilon ) {
//        }
//        fitFuncSigma( const fitFuncSigma& obj ) :
//                fun2( obj.fun2 ) {
//        }
//        double operator()( double* x, double* p ) {
//            double value2 = fun2( x, p );
//            if ( value2 > 0 )
//                return sqrt( value2 );
//            else
//                return 0;
//        }
//        fitFuncSigma& operator=( const fitFuncSigma& obj ) {
//            fun2 = obj.fun2;
//            return *this;
//        }
//        virtual double getEmmitance() const {
//            return fun2.getEmmitance();
//        }
//    };

//    fitFuncSigma  fitFuncSigmaObj;

public:
    ScanSet( std::string name, double emmitance = 0 ) :
            TNamed( name.c_str(), name.c_str() ), FunctionOfEmittance( emmitance ), scanList() {
    }
    ScanSet( std::string name, std::vector<ScanResults*>& scans, double emmitance ) :
            TNamed( name.c_str(), name.c_str() ), FunctionOfEmittance( emmitance ), scanList( scans ) {
    }
    ScanSet( const ScanSet& set ) :
            FunctionOfEmittance( set ) {
        *dynamic_cast<TNamed*>( this ) = *dynamic_cast<TNamed*>( set.Clone(
                ( std::string( "clonOf_" ) + std::string( set.GetName() ) ).c_str() ) );
        for ( auto& oldScan : set.scanList ) {
            this->scanList.push_back( new ScanResults( *oldScan ) );
        }
    }

    virtual ~ScanSet();

    virtual ScanSet& operator=( const ScanSet& set ) {
        if ( this == &set ) return *this;
//        fitFuncSigma2Obj = set.fitFuncSigma2Obj;
//        fitFuncSigmaObj = set.fitFuncSigmaObj;
        *dynamic_cast<TNamed*>( this ) = *dynamic_cast<TNamed*>( set.Clone(
                ( std::string( "clonOf_" ) + std::string( set.GetName() ) ).c_str() ) );
        *dynamic_cast<FunctionOfEmittance*>( this ) =
                *dynamic_cast<FunctionOfEmittance*>( const_cast<ScanSet*>( &set ) );

        for ( auto& scan : scanList ) {
            if ( scan != nullptr ) delete scan;
        }
        scanList.erase( scanList.begin(), scanList.end() );

        for ( auto& oldScan : set.scanList ) {
            this->scanList.push_back( new ScanResults( *oldScan ) );
        }
        return *this;
    }

    virtual void Print();

    virtual void addScanResults( ScanResults& scan ) {
        scanList.push_back( new ScanResults( scan ) );
    }

    virtual TGraphErrors* makeGraphs();
    virtual TF1* fitGraphs( double xMin, double xMax, Color_t col );

    virtual TF1* getUpperEdge(double xMin, double xMax, Color_t col) ;
    virtual TF1* getLowerEdge(double xMin, double xMax, Color_t col) ;

    virtual const std::vector<ScanResults*>& getScanList() const {
        return scanList;
    }

    virtual void setScanList( const std::vector<ScanResults*>& scanMap ) {
        this->scanList = scanMap;
    }

    virtual TGraphErrors* getGraphSigma() const {
        return graphSigma;
    }

    virtual TGraphErrors* getGraphSigma2() const {
        return graphSigma2;
    }

};

} /* namespace WireScanSets */

#endif /* SCANSET_HH_ */
