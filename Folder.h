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
//	static int sumfiles;//total folders + files in root only
//	static int totalfiles;// total folders + data files in root folder
	//static int folderNum;//total folders in the root folder
	//static int dataFileNum;//total data files in the root folder
	int innerfolders;//total folders in this folder
	int innerdfiles;//total data files in this folder
	
	std::string folderPath;
	
	static bool rootCreated;
	static int rootlength;
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
	
	//static Folder root;

	//default constructor
	//Folder();

	


	
	

	
	
	//set
	void setFolderPath(const std::string& fp);

	//get
	//BUG CHECK WHAT IT MEANS TO RETURN FULL PATH TO A FILE
	std::string getFullPath() const;

	std::string getPath() const;
	//std::string getData()const;
	
	


	//virtual void operator=(AD_FILE& adf);

	void mkfile(const std::string& fn, const std::string& fd);
	void mkDir(const std::string& fn);
	//void isExist(const std::string fn, char type);
	void isExist(const std::string fn, const char& type);
	//AD_FILE& createItem(AD_FILE * adf);
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

