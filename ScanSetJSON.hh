/*
 * ScanSetJSON.hh
 *
 *  Created on: Feb 24, 2017
 *      Author: hovanes
 */

#ifndef SCANSETJSON_HH_
#define SCANSETJSON_HH_

#include <iostream>
#include <fstream>
#include <string>

#include <json/json.h>

#include "ScanSet.hh"

namespace WireScanSets {

class ScanSetJSON : public ScanSet {
protected:
    // these are attributes needed for ScanSetJSON class
    static std::vector<std::string> neededAttributes;

    static std::map<std::string,double> scannerPositions;

public:
    ScanSetJSON( Json::Value& jsonData ) :  ScanSet () {
        // Verify that all required attributes exist
        for ( auto& attrib : neededAttributes ) {
            if ( !jsonData.isMember( attrib ) ) {
                std::string errMsge =    std::string("JSON missing attribute <") + attrib + ">";
                throw std::runtime_error( errMsge );
            }
        }
        std::cout << "Will call constructor with arguments : " << std::endl; ;
        for ( auto& attrib : neededAttributes ) {
            std::cout << attrib << " : " << jsonData[attrib] << std::endl;
        }
       std::cout << std::endl;
       // Create a new object of the base class and assign the value to this
       std::string name = jsonData["location"].asString() + "-" + jsonData["date"].asString();

       std::vector<ScanResults*> results;
       for( auto& resultObjJSON : jsonData ) {
           try {
               double zPosition = getZ( jsonData["location"].asString() );
               ScanResultsJSON* jsonResult( resultObjJSON,  zPosition );
               results.push_back( jsonResult );
           } catch ( std::runtime_error& e ) {
               throw e;
           }
       }

       *this = *(new ScanSet( name, results, jsonData["emittance"].asDouble() ) );
    }

    virtual ~ScanSetJSON() {
    }

    virtual double getZ( std::string location ) {
        if( getScannerPositions().count( location ) > 0 ) return getScannerPositions()[location];
        else throw std::runtime_error( "Bad locarion error");
    }

    static const std::vector<std::string>& getNeededAttributes()  {
        return neededAttributes;
    }

    void setNeededAttributes( static const std::vector<std::string>& neededAttributes ) {
        this->neededAttributes = neededAttributes;
    }

    static const std::map<std::string, double>& getScannerPositions() const {
        return scannerPositions;
    }

    void setScannerPositions( static const std::map<std::string, double>& scannerPositions ) {
        this->scannerPositions = scannerPositions;
    }
};

#endif /* SCANSETJSON_HH_ */
