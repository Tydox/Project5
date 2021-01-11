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

	

	void setTime();
	//std::string getTime() const;
	tm* getPTime()const;

	//generic virtual
	virtual bool operator==(const AD_FILE& fn) const;
	//operator==
	//virtual bool operator==(const std::string& fn) const;

	//default constructor - dont make because you must give a folder name
	//AD_FILE() { std::cout << "\nDefault AD_FILE Constructor\n"; }

	//virtual std::string getData() const = 0;
	
	public:
		//methods
		void setFileName(const std::string& fn);
		std::string getFileName()const { return fileName; }
		std::string getTime() const;
	//constructor
	AD_FILE(const std::string& fn);
	//copy constructor
	AD_FILE(const AD_FILE& adf);
	//operator=
	virtual void operator=(const AD_FILE& adf);
	

	virtual ~AD_FILE() { std::cout << "\nAD_FILE DESTRUCTOR - \n" << this->getFileName()<< std::endl; fileName.clear(); }

	
	//no need for destructor string self, pointer isn't allocated

	//BUG CHECK IF NEED TO MAKE A OPERATOR =
	
};

