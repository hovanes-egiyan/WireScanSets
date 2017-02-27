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

#include "ScanResultJSON.hh"
#include "ScanSet.hh"

namespace WireScanSets {

class ScanSetJSON : public ScanSet {
protected:
    // these are attributes needed for ScanSetJSON class
    static std::vector<std::string> neededAttributes;

    static std::map<std::string,double> scannerPositions;

    virtual void buildObjectFromJSON( Json::Value& jsonData ) {
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

       std::vector<ScanResult*> results;
       for( auto& resultObjJSON : jsonData ) {
           try {
               double zPosition = getZ( jsonData["location"].asString() );
               ScanResultJSON* jsonResult = new ScanResultJSON( resultObjJSON,  zPosition );
               results.push_back( jsonResult );
           } catch ( std::runtime_error& e ) {
               throw e;
           }
       }
       *dynamic_cast<ScanSet*>(this) = *(new ScanSet( name, results, jsonData["emittance"].asDouble() ) );
    }

public:
    ScanSetJSON( Json::Value& jsonData ) :  ScanSet () {
    	buildObjectFromJSON( jsonData );
    }

    ScanSetJSON( const std::string& fileName ) : ScanSet() {
        std::cout << "Reading scan from " << fileName << std::endl;
       	std::ifstream ifs( fileName );
        if ( !ifs.is_open() ) {
        	std::string errMsg = "Could not find file " + fileName ;
        	throw std::runtime_error( errMsg) ;
        }
        std::cout << "  Found JSON file " << fileName << std::endl;
        Json::Value scanJSON;
        Json::Reader reader;
        bool parsing_success = reader.parse( ifs, scanJSON );

        if ( !parsing_success ) {
            std::string errMsg = "Parsing failed for file " + fileName ;
        	throw std::runtime_error( errMsg) ;
        }
        std::cout << "  Parsing successful\n";

        buildObjectFromJSON( scanJSON );
    }

    virtual ~ScanSetJSON() {
    }

    virtual double getZ( std::string location ) {
        if( getScannerPositions().count( location ) > 0 ) return scannerPositions[location];
        else throw std::runtime_error( "Bad location error");
    }

    static const std::vector<std::string>& getNeededAttributes()  {
        return neededAttributes;
    }

    void setNeededAttributes(  std::vector<std::string>& neededAttributes ) {
        this->neededAttributes = neededAttributes;
    }

    static std::map<std::string, double>& getScannerPositions() {
        return scannerPositions;
    }

    void setScannerPositions(  std::map<std::string, double>& scannerPositions ) {
        this->scannerPositions = scannerPositions;
    }
};

};

#endif /* SCANSETJSON_HH_ */
