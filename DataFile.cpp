#include "DataFile.h"

DataFile::DataFile(std::string fn):AD_FILE(fn)
{
	
}

DataFile::DataFile(const DataFile& df):AD_FILE(df.getFileName())
{
	setData(df.getData());
}

int DataFile::getSize() const
{
	//return size of object in bytes
	return sizeof(*this);
}

std::string DataFile::getData() const
{
	return this->data;
}

void DataFile::setData(std::string dt)
{
	if (dt.empty())
		throw std::logic_error("Given Param to setData is null");

	data = dt;
}

bool DataFile::operator==(const DataFile& df) const
{
	return dfcmp(df);
}

bool DataFile::operator==(const AD_FILE& fn)
{
	try {
		const DataFile fnp = dynamic_cast<const DataFile&>(fn);
		return dfcmp(fnp);
	}
	catch(std::bad_cast& bc)
	{
		std::cout << "Failed to convert given based on virtual method, passed AD_FILE is not of type of Data File!\n";
		std::cout << bc.what();
		return false;
	}	
}

bool DataFile::dfcmp(const DataFile& df) const
{
	//BUG DO I NEED TO VERIFY IF THE TIMES ARE THE SAME AS WELL??????

	//use operator in base to check names
	bool fileName = AD_FILE::operator==(df.getFileName());
	//get data from both datafiles and compare their strings
	bool fileData = (this->getData() == df.getData());
	//use logical compare to return if files are the same

	return (fileName && fileData);
}
