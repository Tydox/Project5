#include "Folder.h"
Folder* Folder::root= new Folder("root","\\root");
bool Folder::rootCreated = false;

//constructor
Folder::Folder(const std::string& fn, const std::string& fp):AD_FILE(fn),files(nullptr),innerfolders(0), innerdfiles(0)
{
	if (fn == DEF_FOLDER)
	{
		try {
			if (rootCreated == true)
				throw std::logic_error("CANNOT INIT ROOT, ALREADY DEFINED! Folder not created!");
			rootCreated = true;
			root = this;			
		}
		catch(std::logic_error& error)
		{
			std::cout << error.what()<<std::endl;
			delete this;
			return;
		}
	}
	
	initFolder(fp);
}

//destructor
Folder::~Folder()
{
	for (int i = 0; i < innerfolders + innerdfiles; ++i)
	{
		DataFile* tmp2 = dynamic_cast<DataFile*>(files[i]);
		if (tmp2) {
			delete tmp2;
			tmp2 = nullptr;
			continue;
		}

		Folder* tmp = dynamic_cast<Folder*>(files[i]);
		if (tmp) {
			delete tmp;
			tmp = nullptr;
		}
	}
	
	delete[] files;
	files = nullptr;
}

//copy constructor
Folder::Folder(Folder& f,std::string& path):AD_FILE(path),files(nullptr)
{
	initFolder("\\" + path);
	buildRoot(f);
	delete &f; //root sub items
	root = this; //move root to new place under new name
}


Folder::Folder(const Folder& f) :AD_FILE(f.getFileName())
{
	initFolder(f.getFullPath());
	buildRoot(f);
}

void Folder::buildRoot(const Folder& f)
{
	int size = f.innerdfiles + f.innerfolders;
	for (int i = 0; i < size; ++i)
	{
		const DataFile* tmp2 = dynamic_cast<const DataFile*>(f.files[i]);
		if (tmp2){
			AD_FILE* adfT = new DataFile(*tmp2);
			addFileToArray(*adfT);
	}
		const Folder* tmp = dynamic_cast<const Folder*>(f.files[i]);
		if (tmp) {
			AD_FILE* adfT = new Folder(*tmp);
			addFileToArray(*adfT);
		}
	}
}


void Folder::initFolder(const std::string& fp)
{
	setFolderPath(fp);
	innerdfiles = 0;
	innerfolders = 0;
}

void Folder::setFolderPath(const std::string& fp)
{
	if (fp.empty())
		throw std::logic_error("Given String to setFolderPath is null");

	folderPath = fp;
}

void Folder::addFileToArray(AD_FILE& adf) //TODO CHECK IF THIS IS VALID
{
	try {
		AD_FILE** newArray = new AD_FILE * [innerfolders + innerdfiles + 1];

			int i = 0;
			for (; i < innerfolders + innerdfiles; ++i)
				newArray[i] = files[i];
			newArray[i] = &adf;
		
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
	if (tmp) 
	{
		++innerfolders;
	}
	else {
		const DataFile* tmp2 = dynamic_cast<const DataFile*>(adf);
		if (tmp2) 
		{
			++innerdfiles;
		}
	}
}

void Folder::mkfile(const std::string& fn, const std::string& fd)
{
	try {
		if (fn.empty() || fd.empty())
			throw std::exception("Invalid Echo!");
		
		isExist(fn,'d');
		addFileToArray(createItem(fn, fd));
	}
	catch(std::exception& error)
	{
		std::cout << error.what()<<std::endl;
	}
}

void Folder::mkDir(const std::string& fn)
{
	try {
		isExist(fn,'f');
		addFileToArray(createItem(fn));	
	}
		catch (std::exception& error)
	{
		std::cout << error.what()<<std::endl;
	}
}

void Folder::isExist(const std::string fn, const char& type)
{
	for (int i = 0; i < innerdfiles + innerfolders; ++i)
	{
		if (type == 'd') {
			const DataFile* tmp2 = dynamic_cast<const DataFile*>(this->files[i]);
			if (tmp2) {
				if (tmp2->getFileName() == fn)
					throw std::exception("File already exists!");
			}
		}
		if (type == 'f') {
			const Folder* tmp = dynamic_cast<const Folder*>(this->files[i]);
			if (tmp) {
				if (tmp->getFileName() == fn)
					throw std::exception("File already exists!");
			}
		}
	}

	
}

AD_FILE& Folder::createItem(const std::string fn, const std::string fd)
{
	if (fd == "0")//folder
	{
		std::string fp = getFullPath()+ "\\" + fn;
		Folder* newFolder = new Folder(fn, fp);
		return (AD_FILE&)*newFolder;
	}
	else {
		DataFile* newData = new DataFile(fn, fd);
		return (AD_FILE&)*newData;
	}
}

void Folder::dir() const
{
	if(innerdfiles + innerfolders == 0)
	{
		std::cout << std::left << std::setw(17) << std::setfill(' ') << "Empty Directory!" << std::endl;
		return;
	}
	std::cout << std::left << std::setw(21) << std::setfill(' ') << "Files in Directory <"+ getPath() + ">" << std::endl;


	for (int i = 0; i < innerfolders + innerdfiles; ++i)
	{
		DataFile* tmp2 = dynamic_cast<DataFile*>(files[i]);
		if (tmp2) {
			std::cout << std::left << std::setw(20) << std::setfill(' ') << tmp2->getTime();
			std::cout << std::left << std::setw(7) << std::setfill(' ') << " ";
			std::cout << std::left << std::setw(5) << std::setfill(' ') << ((tmp2->getSize()) / 1000);
			std::cout << std::left << std::setw(33) << std::setfill(' ') << "KB " + tmp2->getFileName() << std::endl;
			continue;
		}

		Folder* tmp = dynamic_cast<Folder*>(files[i]);
		if (tmp) {
			std::cout << std::left << std::setw(20) << std::setfill(' ') << tmp->getTime();
			std::cout << std::left << std::setw(7) << std::setfill(' ') << "<DIR>";
			std::cout << std::left << std::setw(8) << std::setfill(' ') << " ";
			std::cout << std::left << std::setw(30) << std::setfill(' ') << tmp->getPath() << std::endl;
		}
	}
	
}

Folder* Folder::cd(std::string& path)
{
	Folder* tmp = search(path, root);
	if (tmp)
		return tmp;
	else
		throw std::exception("Path Not found!");
}

std::string Folder::pathURL(std::string fp)
{
	std::string stmp = fp;
	for (int i = 0; i < 2; ++i)
		stmp = stmp.substr(stmp.find("\\") + 1);

	return stmp;
}
Folder* Folder::search(std::string& path, const Folder* f)
{
	Folder* tmpP=nullptr;
	for (int i = 0; i < f->innerfolders + f->innerdfiles; ++i)
	{
		if (path == root->getFullPath())
			return root;
		
		Folder* tmp = dynamic_cast<Folder*>(f->files[i]);
		if (tmp) {
			
			if (tmp->pathURL(tmp->getFullPath()) == path)
			//if (tmp->getFullPath().substr(5) == path)
			{
				return tmp;
			}
			else
			{
				tmpP = search(path, tmp);
				if (tmpP)//check if returned pointer end of recursion
					if (tmpP->pathURL(tmpP->getFullPath()) == path) //check if its the right name
						return tmpP;
			}
		}
	}
//debug
//	std::cout << "Path <" << path <<"> was not found!!!\n";
	return tmpP;
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
				//flag = (*f2ftmp == *f1ftmp);
				if (flag == false)
					break;
			}
		}
		
		if (!loopflag)
			break;	
	}
	return flag;
}


void Folder::searchF(Folder& cdr,Folder*& fp, std::string& fn,char& flag1)
{
	Folder* ftot = nullptr;
	char bslash = '\\';
	if (flag1 == bslash)
		ftot =  &cdr;
	else
		ftot = root;

	fp = ftot->cd(fn);
}



bool FC(Folder& cdr, std::string& src, std::string dst)
{
	//create strings
	std::string fileName1;
	std::string folderName1 = Folder::splitFileName(src, fileName1);

	std::string fileName2;
	std::string folderName2 = Folder::splitFileName(dst, fileName2);

	//create flags for back slash
	char flag1 = folderName1.at(0);
	char flag2 = folderName2.at(0);

	//end condition, one is a file name and one is not
	if((fileName1.empty() && !fileName2.empty()) || (!fileName1.empty() && fileName2.empty()))
	{
		std::cout << "Not equal comparision!\n ";
		return false;
	}
	
	Folder* f1 = nullptr;
	Folder* f2 = nullptr;
	
	Folder::searchF(cdr,f1,folderName1, flag1);
	Folder::searchF(cdr, f2, folderName2, flag2);

	
	if (!fileName1.empty() && !fileName2.empty())
		{
			const DataFile* pf1 = f1->dfs(fileName1);
			const DataFile* pf2 = f2->dfs(fileName2);
			return *pf1 == *pf2;
		}
	
	return *f1 == *f2;
	
}


std::string Folder::splitFileName(const std::string& fn, std::string& nfn)
{
	const size_t failed = -1;
	std::size_t founddot = fn.find_last_of('.');
	if (founddot == failed)//its folder path
	{
		std::string tmp = fn;
		return tmp;
	}
	else
	{
		std::size_t found = fn.find_last_of('\\');
		nfn = fn.substr(found + 1);
		std::string tmp = fn.substr(0,found);
		return tmp;
		
	}
}


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

	}
	std::cout << "File not found in folder!\n";
	return nullptr;
}

std::string Folder::getFullPath() const
{
	return folderPath;
}

std::string Folder::getPath() const
{
	std::size_t found = folderPath.find_last_of("/\\");
	return folderPath.substr(found + 1);
}
