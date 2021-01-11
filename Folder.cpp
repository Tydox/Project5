#include "Folder.h"

//int Folder::totalfiles = 0;
//int Folder::folderNum = 0;
//int Folder::dataFileNum = 0;
Folder* Folder::root= new Folder();
//Folder Folder::root;
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

Folder::Folder():AD_FILE("Main Root")
{
	files = nullptr;
	rootCreated = false;
	innerdfiles = 0;
	innerfolders = 0;
	folderPath = "";
	
	
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
			
			if (mode == 'n')
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
		//isExist(fn, 'd');
		isExist(fn);
		addFileToArray(createItem(fn, fd), 'n');
	}
	catch(std::exception& error)
	{
		std::cout << error.what();
	}
}

void Folder::mkDir(const std::string fn)
{
	try {
		//isExist(fn, 'f');
		if (rootCreated == false)
		{
			rootCreated = true;
			root = this;
			folderPath = fn;
		}
		isExist(fn);
		addFileToArray(createItem(fn), 'n');
		
	}
		catch (std::exception& error)
	{
		std::cout << error.what();
	}
}

//void Folder::isExist(const std::string fn, char type) // char type can be removed i think~!!!!!!!!
void Folder::isExist(const std::string fn) // char type can be removed i think~!!!!!!!!
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
				if (tmp->getFileName() == fn)
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
	if(fd == "0")//folder
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
			std::cout << std::left << std::setw(20) << std::setfill(' ') << tmp2->getTime();
			std::cout << std::left << std::setw(7) << std::setfill(' ') << " ";
			std::cout << std::left << std::setw(8) << std::setfill(' ') << (tmp2->getSize()) / 1000 << "kb ";
			std::cout << std::left << std::setw(30) << std::setfill(' ') << tmp2->getFileName() << std::endl;
			continue;
		}

		Folder* tmp = dynamic_cast<Folder*>(files[i]);
		if (tmp) {
			std::cout << std::left << std::setw(20) << std::setfill(' ') << tmp->getTime();
			std::cout << std::left << std::setw(7) << std::setfill(' ') << "<DIR>";
			std::cout << std::left << std::setw(8) << std::setfill(' ') << " ";
			std::cout << std::left << std::setw(30) << std::setfill(' ') << tmp->getFileName() << std::endl;
			
			continue;
		}
	}
	
}

Folder* Folder::cd(std::string& path)
{
	return search(path, root);
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

	std::cout << "Path <" << path <<"> was not found!!!";
	throw std::exception("File/Folder Was not found!");
	//return nullptr;
}

bool Folder::operator==(const AD_FILE& fn) const
{
	try {
		const Folder fnp = dynamic_cast<const Folder&>(fn);
		return fcmp(fnp, *this);
	}
	catch (std::bad_cast& bc)
	{
		std::cout << "Failed to convert given based on virtual method, passed AD_FILE is not of type of Data File!\n";
		std::cout << bc.what();
		return false;
	}
}

bool Folder::operator==(const Folder& fn) const
{
	return fcmp(fn,*this);
}

bool Folder::fcmp(const Folder& fn, const Folder& ft) const
{
	bool flag = true;
	bool loopflag = false;
	int f1 = ft.innerdfiles + ft.innerfolders;
	int f2 = fn.innerdfiles + fn.innerfolders;

	if (f1 != f2) // sum of files & folders is different
		return false;

	/*if (f1 == 0 && f2 == 0)
	{
		std::cout << "Both Folders are empty, nothing to compare! Aborting!\n";
		return false;
	}*/

	for (int i = 0; ((i < f1) && (i < f2)); ++i,loopflag=false)
	{
		DataFile* f1dtmp = dynamic_cast<DataFile*>(ft.files[i]);
		DataFile* f2dtmp = dynamic_cast<DataFile*>(fn.files[i]);
		if (f1dtmp && f2dtmp)
		{
			if ((f1dtmp->getFileName() == f2dtmp->getFileName()) && (f1dtmp->getData() == f2dtmp->getData()))
			{
				loopflag = true;
				continue;
			}
			else
				return false;
		}

		Folder* f1ftmp = dynamic_cast<Folder*>(ft.files[i]);
		Folder* f2ftmp = dynamic_cast<Folder*>(fn.files[i]);
		if (f1ftmp && f2ftmp)
		{
			if (f1ftmp->getFileName() != f2ftmp->getFileName()) {
				return false;
			}
			else
			{
				loopflag = true;
				flag = fcmp(*f2ftmp, *f1ftmp);
				if (flag == false)
					break;
			}
		}
		
		if (!loopflag)
			break;	
	}
	return flag;
}

bool FC(Folder& cdr, std::string& src, std::string dst)
{
	
	std::string fileName1;
	std::string folderName1 = Folder::splitFileName(src, fileName1);

	std::string fileName2;
	std::string folderName2 = Folder::splitFileName(dst, fileName2);

	char flag1 = folderName1.at(0);
	char flag2 = folderName2.at(0);
	char bslash = '\\';
	
	if((fileName1.empty() && !fileName2.empty()) || (!fileName1.empty() && fileName2.empty()))
	{
		std::cout << "Not equal comparision!\n ";
		return false;
	}
	Folder* ftot = nullptr;
	Folder* f1 = nullptr;
	Folder* f2 = nullptr;
	
	if (flag1 == bslash)
		ftot = &cdr;
	else
		ftot = Folder::root;

	f1 = ftot->cd(folderName1);
	
	if (flag2 == bslash)
		ftot = &cdr;
	else
		ftot = Folder::root;

	f2 = ftot->cd(folderName2);

	if (!fileName1.empty() && !fileName2.empty())
		if (fileName1 == fileName2)
		{
			DataFile* pf1 = f1->dfs(fileName1);
			DataFile* pf2 = f2->dfs(fileName2);

			return pf1 == pf2;
		}
	
	return f1 == f2;
	
}


std::string& Folder::splitFileName(const std::string& fn, std::string& nfn)
{
	std::size_t found = fn.find_last_of("/\\");
	//std::cout << " path: " << fn.substr(0, found) << '\n';
	//std::cout << " file: " << fn.substr(found + 1) << '\n';
	nfn = fn.substr(found + 1);
	std::string tmp = fn.substr(0, found);
	return tmp;
}

// TODO CHECKKKKKKKKKKK HOOOOOOWWWWWWWWWWW TOOOOOOOOOO DOOOOOOOOO THHHHHHHHHHIIIIIIIIISSSSSSSSSSSSS
DataFile* Folder::dfs(std::string& df) const
{
	for (int i = 0; i < this->innerfolders + this->innerdfiles; ++i)
	{
		DataFile* tmp = dynamic_cast<DataFile*>(this->files[i]);
		if (tmp) {
			if (tmp->getFileName() == df)
			{
				return tmp;
			}
		}
		//Folder* tmp2 = dynamic_cast<Folder*>(this->files[i]);
		//if (tmp2) {
		//	if (tmp2->getFileName() == df)
		//	{
		//		return tmp2;
		//	}
		//}
		//
	}
	std::cout << "File not found in folder!\n";
	return nullptr;
}

std::string Folder::getFullPath() const
{
	return folderPath;
}
