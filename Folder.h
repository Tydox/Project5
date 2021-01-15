#pragma once

//#include <iostream>
#include "DataFile.h"
#include "AD_FILE.h"
#include <iomanip>

#define DEF_FOLDER "root"
//constexpr auto DEF_NAME = "root";

class Folder : public AD_FILE
{
private:
	AD_FILE** files; //files array folders + data files
	int innerfolders;//total folders in this folder
	int innerdfiles;//total data files in this folder
	std::string folderPath;
	static bool rootCreated;
	
protected:


public:
	static Folder* root;

	//constructor
	Folder(const std::string& fn, const std::string& fp);

	//destructor
	~Folder();
	
	void addFileToArray(AD_FILE& adf);
	void addNums(AD_FILE* adf); //count what type was added to array

	//copy constructor
	Folder(const Folder& f);
	Folder(Folder& f, std::string& path);
	void buildRoot(const Folder& f);
	void initFolder(const std::string& fp);

	static void searchF(Folder& cdr,Folder*& fp, std::string& fn, char& flag1);
	
	std::string pathURL(std::string fp);
	
	//set
	void setFolderPath(const std::string& fp);

	//get
	std::string getFullPath() const;
	std::string getPath() const;
	
	void mkfile(const std::string& fn, const std::string& fd);
	void mkDir(const std::string& fn);
	void isExist(const std::string fn, const char& type);
	AD_FILE& createItem(const std::string fn, const std::string fd = "0");
	void dir()const;
	static Folder* cd(std::string& path);
	static Folder* search(std::string& path, const Folder* f = nullptr);
	virtual bool operator==(const AD_FILE& fn) const;
	bool operator==(const Folder& fn) const;
	bool fcmp(const Folder& fn, const Folder& ft) const;
	friend bool FC(Folder& cdr, std::string& src, std::string dst);
	static std::string splitFileName(const std::string& fn, std::string& nfn);
	DataFile* dfs(std::string& df) const;
	
};

