#pragma once

#include <iostream>
#include "DataFile.h"
#include "AD_FILE.h"
#include <iomanip>

#define DEF_FOLDER "root"

class Folder : public AD_FILE
{
private:
	AD_FILE** files; //files array folders + data files
	int innerfolders;//total folders in this folder
	int innerdfiles;//total data files in this folder
	std::string folderPath;
	static bool rootCreated;

protected:
	//support methods
	static std::string splitFileName(const std::string& fn, std::string& nfn);
	DataFile* dfs(std::string& df) const;
	bool fcmp(const Folder& fn, const Folder& ft) const;
	static Folder* search(std::string& path, const Folder* f = nullptr);
	void isExist(const std::string fn, const char& type);
	AD_FILE& createItem(const std::string fn, const std::string fd = "0");
	
	void buildRoot(const Folder& f);
	void initFolder(const std::string& fp);
	void addNums(AD_FILE* adf); //count what type was added to array
	void addFileToArray(AD_FILE& adf);
	static void searchF(Folder& cdr, Folder*& fp, std::string& fn, char& flag1);

	//set
	void setFolderPath(const std::string& fp);

	
public:
	static Folder* root;
	
	//constructor
	Folder(const std::string& fn, const std::string& fp);

	//destructor
	~Folder();
	
	//copy constructor
	Folder(const Folder& f);
	Folder(Folder& f, std::string& path);

	//get
	std::string getFullPath() const;
	std::string getPath() const;
	std::string pathURL(std::string fp);

	//methods
	void mkfile(const std::string& fn, const std::string& fd);
	void mkDir(const std::string& fn);
	void dir()const;
	static Folder* cd(std::string& path);
	friend bool FC(Folder& cdr, std::string& src, std::string dst);
	virtual bool operator==(const AD_FILE& fn) const;
	bool operator==(const Folder& fn) const;

};

