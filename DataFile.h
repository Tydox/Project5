#include "AD_FILE.h"
#include <typeinfo>

class DataFile : public AD_FILE
{
private:
	std::string data;
protected:
	//support method for operators
	bool dfcmp(const DataFile& df) const;
public:

	//constructor
	DataFile(std::string fn);
	//copy constructor
	DataFile(const DataFile& df);
	
	//get size in bytes of object
	int getSize()const;
	std::string getData()const;

	//set
	void setData(std::string dt);
	
	//operator overloading
	bool operator==(const DataFile& df) const;
	//overwriting virtual operator polymorphic
	virtual bool operator==(const AD_FILE& fn);
	
};
