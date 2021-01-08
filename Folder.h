#pragma once
#include <iostream>
#include "DataFile.h"
#include "AD_FILE.h"

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
	static Folder* root;
	static bool rootCreated;

protected:


public:
	//default constructor
	Folder();

	//copy constructor
	Folder(const Folder& f,std::string& path);
	void buildRoot(const Folder& f);
	//constructor
	Folder(const std::string& fn, const std::string& fp,const std::string& rt="0");
	void initFolder(const std::string& fp);

	//destructor
	~Folder();
	void killRoot(Folder& f);
	//set
	void setFolderPath(const std::string& fp);

	//get
	//BUG CHECK WHAT IT MEANS TO RETURN FULL PATH TO A FILE
	//std::string getFullPath();

	std::string getData()const;
	
	void addFileToArray(AD_FILE& adf,char mode='0');
	void addNums(AD_FILE* adf);


	virtual void operator=(AD_FILE& adf);


	void mkfile(const std::string fn, const std::string fd);
	void mkDir(const std::string fn);
	void isExist(const std::string fn, char type);

	AD_FILE& createItem(AD_FILE * adf);
	AD_FILE& createItem(const std::string fn, const std::string fd = 0);
};

