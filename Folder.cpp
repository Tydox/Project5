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
			//if (tmp->innerfolders > 0 || tmp->innerdfiles > 0)//more sub folders
				killRoot(f);
			
			delete tmp;//TODO CHECK IF NEED TO ADD *TMP ^^^ if need to change the if condition
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
			//this->files[i]->operator=(*(f.files[i]));
			this->files[i] = new DataFile(*tmp2);
			++innerdfiles;
		}
		const Folder* tmp = dynamic_cast<const Folder*>(f.files[i]);
		if (tmp) {
			//this->files[i]->operator=(*(f.files[i]));
			this->files[i] = new Folder(*tmp);

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
			//files = nullptr;
			
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

std::string Folder::getData() const
{
	return std::string();
}

void Folder::addFileToArray(AD_FILE& adf, char mode) //TODO CHECK IF THIS IS VALID
{
	try {
		AD_FILE** newArray = new AD_FILE * [innerfolders + innerdfiles + 1];

		//if((innerfolders + innerdfiles) == 0)
		//{
		//	newArray[0] = new AD_FILE(adf);
		//}
		//else 
		//{
			int i = 0;
			for (; i < innerfolders + innerdfiles; ++i)
				newArray[i] = files[i];
			
			if (mode == '0')
				newArray[i] = &(createItem(&adf)); //TODO CHECK THIS WARNING
			else
				newArray[i] = &adf;
				//}
		delete[] files;
		files = newArray;		
		addNums(&adf);//count what file type i added
	}
	catch(std::bad_alloc& error)
	{
		std::cout << "Error Allocation @ addFileToArray! " << error.what();
	}
}

void Folder::addNums(AD_FILE* adf)
{
	const Folder* tmp = dynamic_cast<const Folder*>(adf);
	if (tmp) {
		//++folderNum;
		++innerfolders;
	}
	else {
		const DataFile* tmp2 = dynamic_cast<const DataFile*>(adf);
		if (tmp2) {
			//++dataFileNum;
			++innerdfiles;
		}
	}
}

void Folder::operator=(AD_FILE& adf)
{
	addFileToArray(adf);
}

void Folder::mkfile(const std::string fn, const std::string fd)
{
	try {
		isExist(fn, 'd');
		addFileToArray(createItem(fn, fd), 'n');
	}
	catch(std::exception error)
	{
		std::cout << error.what();
	}
}

void Folder::mkDir(const std::string fn)
{
	try {
		isExist(fn, 'f');
		addFileToArray(createItem(fn), 'n');
	}
		catch (std::exception error)
	{
		std::cout << error.what();
	}
}

void Folder::isExist(const std::string fn, char type)
{
	for(int i =0;i<innerdfiles+innerfolders;++i)
	{
		const DataFile* tmp2 = dynamic_cast<const DataFile*>(this->files[i]);
		if (tmp2) {
			if (tmp2->getFileName() == fn)
				throw std::exception("File already exists! mkfile stopping!");
		}
		const Folder* tmp = dynamic_cast<const Folder*>(this->files[i]);
		if (tmp) {
			if(tmp->getFileName()==fn)
				throw std::exception("File already exists! mkDir stopping!");
		}
	}

	
}

AD_FILE& Folder::createItem(AD_FILE* adf)
{
	const DataFile* tmp2 = dynamic_cast<const DataFile*>(adf);
	if (tmp2) {
		DataFile* newData = new DataFile(*tmp2);
		//++innerdfiles;
		return (AD_FILE&)*newData;
	}
	else
	{
		const Folder* tmp = dynamic_cast<const Folder*>(adf);
		if (tmp) {
			Folder* newFolder = new Folder(*tmp);
			//++innerfolders;
			return (AD_FILE&)*newFolder;

		}
	}
	throw std::exception("Something went wrong with creating a new item in folder!");
}

AD_FILE& Folder::createItem(const std::string fn, const std::string fd)
{
	std::string fp = this->folderPath;
	if(fd.empty())//folder
	{
		Folder* newFolder = new Folder(fn,fp);
		return (AD_FILE&)*newFolder;
	}
	else
	{
		DataFile* newData = new DataFile(fn,fd);
		return (AD_FILE&)*newData;	
	}
}

void Folder::dir() const
{
	//TODO - CHECK IF DIR PRINT INCLUDES SUB FOLDERS OR JUST ROOT 
	std::cout << std::left << std::setw(21) << std::setfill(' ') << "Files in Directory <" << folderPath << ">" << std::endl;

	for (int i = 0; i < innerfolders + innerdfiles; ++i)
	{
		DataFile* tmp2 = dynamic_cast<DataFile*>(files[i]);//++dataFileNum;//++innerdfiles;
		if (tmp2) {
			std::cout << std::left << std::setw(7) << std::setfill(' ');
			std::cout << std::left << std::setw(8) << std::setfill(' ') << (tmp2->getSize()) / 1000 << "kb ";
			std::cout << std::left << std::setw(30) << std::setfill(' ') << tmp2->getFileName();
			continue;
		}

		Folder* tmp = dynamic_cast<Folder*>(files[i]);
		if (tmp) {
			std::cout << std::left << std::setw(7) << std::setfill(' ') << "<DIR>";
			std::cout << std::left << std::setw(8) << std::setfill(' ');
			std::cout << std::left << std::setw(30) << std::setfill(' ') << tmp->getFileName();
			
			continue;
		}
	}
	
}

Folder* Folder::cd(std::string& path)
{
	search(path, nullptr);
	return nullptr;
}

Folder* Folder::search(std::string& path, const Folder* f)
{
	for (int i = 0; i < f->innerfolders + f->innerdfiles; ++i)
	{
		Folder* tmp = dynamic_cast<Folder*>(f->files[i]);
		if (tmp) {
			if (tmp->getFileName() == path)
			{
				return tmp;
			}
			else
			{
				search(path, tmp);
			}
		}
	}

	std::cout << "Folder was not found!!!";
	return nullptr;
}

//std::string Folder::getFullPath()
//{
//	return folderPath;
//}
