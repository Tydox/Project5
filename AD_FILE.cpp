#include "AD_FILE.h"

void AD_FILE::setFileName(const std::string& fn)
{
	if (fn.empty())
		throw std::logic_error("Given Param to setFileName is null");
	fileName = fn;
}

void AD_FILE::setTime()
{
	// current date/time based on current system
	time_t now = time(0);
	lastModified = localtime(&now);
}

std::string AD_FILE::getTime() const
{
	char buf[80];
	strftime(buf, sizeof(buf), "%d/%m/%Y %X", lastModified);
	return buf;
}

tm* AD_FILE::getPTime() const
{
	return lastModified;
}

AD_FILE::AD_FILE(const std::string& fn)
{
	setFileName(fn);
	setTime();
}

AD_FILE::AD_FILE(const AD_FILE& adf)
{
	*this = adf;
}

void AD_FILE::operator=(const AD_FILE& adf)
{
	if (this != &adf)
	{
		setFileName(adf.getFileName());
		lastModified = adf.getPTime();
		return;
	}
	std::cout << "Same File, nothing to copy!";

	//return *this;
}

bool AD_FILE::operator==(const AD_FILE& fn) const
{
	return (fileName == fn.getFileName());
}

//bool AD_FILE::operator==(const std::string& fn) const
//{
//	return (fileName == fn);
//}

