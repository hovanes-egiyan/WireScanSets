/*
 * FileNameFinder.hh
 *
 *  Created on: Mar 2, 2017
 *      Author: Hovanes Egiyan
 */

#ifndef FILENAMEFINDER_HH_
#define FILENAMEFINDER_HH_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <exception>
#include <stdexcept>


namespace WireScanSets {

class FileNameFinder {
protected:
	std::string dirName; // Default directory name
	std::string fileName; // File name

public:
	FileNameFinder( int* ac, char* av[] );
	virtual ~FileNameFinder();

	virtual void parseFullFileName( const std::string& dName, const std::string& fName );

	inline virtual std::string getFileName() const { return fileName ;}
	inline virtual std::string getDirName() const {return dirName ; }
	inline virtual std::string getFullFileName() const {return dirName + "/" + fileName;}

	inline virtual std::string setFileName( const std::string fName ) {return (fileName = fName);}
	inline virtual std::string setDirName( const std::string dName) {return (dirName= dName);}
};

} /* namespace WireScanSets */

#endif /* FILENAMEFINDER_HH_ */
