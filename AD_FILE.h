#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>

class AD_FILE
{
private:

protected:
	std::string fileName;
	tm* lastModified;
	void setTime();

	tm* getPTime()const;

	//generic virtual
	virtual bool operator==(const AD_FILE& fn) const;

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

		//###DEBUG###
		//virtual ~AD_FILE() { std::cout << "\nAD_FILE DESTRUCTOR - \n" << this->getFileName()<< std::endl; fileName.clear(); }
		//no need for destructor string self, pointer isn't allocated
};

