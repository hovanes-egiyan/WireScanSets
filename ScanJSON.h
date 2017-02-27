/*
 * ScanJSON.h
 *
 *  Created on: Feb 27, 2017
 *      Author: hovanes
 */

#ifndef SCANJSON_H_
#define SCANJSON_H_

#include <iostream>
#include <fstream>
#include <string>

#include <json/json.h>

#include "ScanResultJSON.hh"
#include "ScanSet.hh"
#include "Scan.hh"

namespace WireScanSets {

class ScanJSON: public Scan {
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

       std::map<std::string,ScanResult*> results;
       for( auto& resultObjJSON : jsonData ) {
           try {
               double zPosition = getZ( jsonData["location"].asString() );
               ScanResultJSON jsonResult = new ScanResultJSON( resultObjJSON,  zPosition );
               results[jsonResult.GetName()] = jsonResult ;
           } catch ( std::runtime_error& e ) {
               throw e;
           }
       }
       *dynamic_cast<Scan*>(this) = *(new Scan( name, results ) );
       results.clear();
    }


public:
	ScanJSON() {
		// TODO Auto-generated constructor stub

	}
	virtual ~ScanJSON() {
		// TODO Auto-generated destructor stub
	}

    virtual double getZ( std::string location ) {
        if( scannerPositions.count( location ) > 0 ) return scannerPositions[location];
        else throw std::runtime_error( "Bad location error");
    }

};

} /* namespace WireScanSets */

#endif /* SCANJSON_H_ */
