/*
 * ScanResultsJSON.hh
 *
 *  Created on: Feb 24, 2017
 *      Author: hovanes
 */

#ifndef SCANRESULTSJSON_HH_
#define SCANRESULTSJSON_HH_

#include <iostream>
#include <fstream>
#include <string>

#include <json/json.h>

#include "ScanResults.hh"

namespace WireScanSets {

class ScanResultsJSON : public ScanResults {
protected:
    // these are attributes needed for ScanSetJSON class
    static std::vector<std::string> neededAttributes;

public:
    ScanResultsJSON( Json::Value& jsonData, double zLocation ) :
            ScanResults() {
        // Verify that all required attributes exist
        for ( auto& attrib : neededAttributes ) {
            if ( !jsonData.isMember( attrib ) ) {
                std::string errMsge = std::string( "JSON missing attribute <" ) + attrib + ">";
                throw std::runtime_error( errMsge );
            }
        }
        std::cout << "Will call constructor with arguments : " << std::endl;
        ;
        for ( auto& attrib : neededAttributes ) {
            std::cout << attrib << " : " << jsonData[attrib] << std::endl;
        }
        std::cout << std::endl;
        // Create a new object of the base class and assign the value to this
        std::string name = jsonData["direction"].asString();

        *dynamic_cast<ScanResults*>(this) = *( new ScanResults( name, zLocation, jsonData["sigma"].asDouble(), jsonData["delta"].asDouble() ) );
    }
    virtual ~ScanResultsJSON() {
        // TODO Auto-generated destructor stub
    }

    static std::vector<std::string>& getNeededAttributes()  {
        return neededAttributes;
    }

    static void setNeededAttributes( std::vector<std::string>& attrib ) {
        neededAttributes = attrib;
    }
};

} /* namespace WireScanSets */

#endif /* SCANRESULTSJSON_HH_ */
