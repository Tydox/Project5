#pragma once

#include "AD_FILE.h"
#include <typeinfo>

class DataFile : public AD_FILE
{
private:
	std::string data;
protected:
	//support method for operators
	bool dfcmp(const DataFile& df) const;

	//default constructor
	//DataFile():AD_FILE() { std::cout << "\nDefault DataFile Constructor\n"; }
	
public:

	//constructor
	DataFile(std::string fn, std::string df);
	//copy constructor
	DataFile(const DataFile& df);
	//destructor
	~DataFile() { std::cout << "\nDataFile DESTRUCTOR - \n" << this->getFileName(); data.clear(); }
	
	//get size in bytes of object
	float getSize()const;
	std::string getData()const;

	//set
	void setData(const std::string& dt);
	
	virtual void operator=(const AD_FILE& adf);

	//operator overloading
	bool operator==(const DataFile& df) const;
	//overwriting virtual operator polymorphic
	virtual bool operator==(const AD_FILE& fn);
	
};
