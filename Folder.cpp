#include "Folder.h"

//int Folder::totalfiles = 0;
//int Folder::folderNum = 0;
//int Folder::dataFileNum = 0;
Folder* Folder::root=NULL;
bool Folder::rootCreated = false;


Folder::~Folder()
{
	//innerfolders = 0;
	//innerdfiles = 0;
	delete[] files;
}

void Folder::killRoot(Folder& f)
{
	//reccursion delete
	//if (innerfolders == 0 && innerdfiles == 0)
	//	return;
	
	for (int i = 0; i < innerfolders + innerdfiles; ++i)
	{
		DataFile* tmp2 = dynamic_cast<DataFile*>(files[i]);//++dataFileNum;//++innerdfiles;
		if (tmp2) {
			delete tmp2;
			tmp2 = nullptr;
			continue;
		}

		Folder* tmp = dynamic_cast<Folder*>(files[i]);
		if (tmp) {
			if (tmp->innerfolders > 0 || tmp->innerdfiles > 0)//more sub folders
				killRoot(f);
			
			//delete[] tmp->files;//TODO CHECK IF NEED TO ADD *TMP ^^^ if need to change the if condition
		}
	}
	
	
}

Folder::Folder(const Folder& f,std::string& path):AD_FILE(f.getFileName())
{
	killRoot(*this); //reset this root
	//totalfiles = 0;
	//folderNum = 0;
	//dataFileNum = 0;
	this->setFolderPath(path);
	buildRoot(f);

	this->setFolderPath(path);
	

	
}

void Folder::buildRoot(const Folder& f)
{
	int size = f.innerdfiles + f.innerfolders;
	for (int i = 0; i < size; ++i)
	{
		const DataFile* tmp2 = dynamic_cast<const DataFile*>(f.files[i]);
		if (tmp2) {
			this->files[i]->operator=(*(f.files[i]));
				++innerdfiles;
		}
		const Folder* tmp = dynamic_cast<const Folder*>(f.files[i]);
		if (tmp) {
			this->files[i]->operator=(*(f.files[i]));
			buildRoot(*tmp);
			++innerfolders;
		}
	}

}

Folder::Folder(const std::string& fn, const std::string& fp, const std::string& rt):AD_FILE(fn),files(nullptr),innerfolders(0), innerdfiles(0)
{
	if (rt == DEF_FOLDER)
	{
		try {
			if (rootCreated == true)
				throw std::logic_error("CANNOT INIT ROOT, ALREADY DEFINED! Folder not created!");

			rootCreated = true;
			root = this; //
			files = nullptr;
			
		}
		catch(std::logic_error& error)
		{
			std::cout << error.what();
			return;
		}
		
	}
	
	initFolder(fp);
}

void Folder::initFolder(const std::string& fp)
{
	setFolderPath(fp);
	//++folderNum;
	innerdfiles = 0;
	innerfolders = 0;
}


void Folder::setFolderPath(const std::string& fp)
{
	if (fp.empty())
		throw std::logic_error("Given String to setFolderPath is null");

	folderPath = fp;
}

void Folder::addFileToArray(const AD_FILE& adf) //TODO CHECK IF THIS IS VALID
{
	try {
		AD_FILE** newArray = new AD_FILE * [innerfolders + innerdfiles + 1];

		if((innerfolders + innerdfiles) == 0)
		{
			*newArray[0] = adf;
		}
		else 
		{
			for (int i = 0; i < innerfolders + innerdfiles; ++i)
				newArray[i] = files[i];

			*(newArray[(innerfolders + innerdfiles +1)]) = adf; //TODO CHECK THIS WARNING
		}
		delete[] files;
		files = newArray;		
		addNums(&adf);//count what file type i added
	}
	catch(std::bad_alloc& error)
	{
		std::cout << "Error Allocation @ addFileToArray! " << error.what();
	}
}

void Folder::addNums(const AD_FILE* adf)
{
	const Folder* tmp = dynamic_cast<const Folder*>(adf);
	if (tmp) {
		//++folderNum;
		++innerfolders;
	}
	const DataFile* tmp2 = dynamic_cast<const DataFile*>(adf);
	if (tmp2) {
		//++dataFileNum;
		++innerdfiles;
	}
}

void Folder::operator=(const AD_FILE& adf)
{
	addFileToArray(adf);
}

//std::string Folder::getFullPath()
//{
//	return folderPath;
//}
