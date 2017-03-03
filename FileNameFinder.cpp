/*
 * FileNameFinder.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: Hovanes Egiyan
 */

#include "FileNameFinder.hh"

#include "boost/program_options.hpp"

#include "FileNameFinder.hh"

using namespace std;

namespace po = boost::program_options;


namespace WireScanSets {



FileNameFinder::FileNameFinder( int* ac, char* av[] ) :
	dirName(""), fileName( "" ) {
	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "help message")
	    ("input-file", po::value< string>(), "input file")
	    ("input-directory", po::value< string>(), "input file directory")
	    ;

	po::positional_options_description p;
	p.add("input-file", -1);

	po::variables_map vm;
	po::store(po::command_line_parser(*ac, av).
	          options(desc).positional(p).run(), vm);
	po::notify(vm);

	if( vm.count("help" )) {
		cerr<< desc << endl;
	}
	if (vm.count("input-file")) {
		cout << "Input file is: "
		         << vm["input-file"].as< string >() << "\n";
		fileName = vm["input-file"].as< string >();
	}
	if( vm.count("input-directory") ) {
		cout << "Input file directory is: "
		         << vm["input-directory"].as< string >() << "\n";
		dirName = vm["input-directory"].as< string >();
	}


	parseFullFileName( dirName, fileName );

	return;
}

FileNameFinder::~FileNameFinder() {
	return;
}


void FileNameFinder::parseFullFileName( const string& dName, const string& fName ) {
	string fileName = fName;
//	string dirName = string( dName + string("/") );
	string dirName = dName;

	if( fName.find("/") != string::npos ) {
		size_t lastSlashPos = fName.find_last_of("/");
		fileName = fName.substr( lastSlashPos, fName.size() - lastSlashPos );
//		dirName = fName.substr( 0, lastSlashPos + 1 );
		dirName = fName.substr( 0, lastSlashPos  );
	}
	if( fName == "" && dName == "" ) {
		dirName = ".";
	}
	cout << "FullFileName is " << fName <<
			" file name is " << fileName <<
			" dir name is " << dirName << endl;
	this->setFileName( fileName );
	this->setDirName( dirName );
	return ;
}


} /* namespace WireScanSets */
