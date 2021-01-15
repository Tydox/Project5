#include "DataFile.h"

DataFile::DataFile(std::string fn,std::string df):AD_FILE(fn)
{
	setData(df);
}

DataFile::DataFile(const DataFile& df):AD_FILE(df.getFileName())
{
	setData(df.getData());
}

float DataFile::getSize() const
{
	//return size of data in bytes
	return data.size()+1;
}

std::string DataFile::getData() const
{
	return this->data;
}

void DataFile::setData(const std::string& dt)
{
	if (dt.empty())
		throw std::logic_error("Given string to setData is empty!");

	data = dt;
}

void DataFile::operator=(const AD_FILE& adf)
{
	try {
		const AD_FILE* tmpP = &adf;
		const DataFile* temp = dynamic_cast<const DataFile*>(tmpP);
		*this = *temp;
	}
	catch (std::exception&  error)
	{
		std::cout << error.what();
	}
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
	return (this->getData() == df.getData());
}
