#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>

class AD_FILE
{
private:

	
protected:
	//data
	std::string fileName;
	tm* lastModified;

	//methods
	void setFileName(const std::string& fn);
	std::string getFileName()const { return fileName; }

	void setTime();
	std::string getTime() const;
	tm* getPTime()const;
	
	
public:
	//constructor
	AD_FILE(const std::string& fn);
	//copy constructor
	AD_FILE(const AD_FILE& adf);

	//operator==
	//virtual bool operator==(const std::string& fn) const;

	//generic virtual
	virtual bool operator==(const AD_FILE& fn) const;
	virtual ~AD_FILE() { std::cout << "\nAD_FILE DESTRUCTOR - \n" << this->getFileName(); }

	//no need for destructor string self, pointer isn't allocated

	//BUG CHECK IF NEED TO MAKE A OPERATOR =
	
};

