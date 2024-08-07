/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/
#include "dirent.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR -1
#define DIRECTORY "C:/Users/Cyber_User/Documents"
#define VIDEOS "C:/Users/Cyber_User/Videos"
#define IMAGES "C:/Users/Cyber_User/Pictures"
#define MISC "C:/Users/Cyber_User/Documents/Misc"
#define DOCUMENTS "C:/Users/Cyber_User/Documents/Documents"
#define FOLDERS "C:/Users/Cyber_User/Documents/Folders"

void directoryScan(DIR* directory);
char* checkFileType(char* filePath);
void sortToDir(char* filePath, char* fileExtension, char* fileName);
void renameNewPath(char* filePath, char* folderToWrite, char* fileName);

int main(void)
{
	FILE* tempLog = NULL;
	DIR* directory = opendir(DIRECTORY);
	directoryScan(directory);
	getchar();
	return 0;
}

void directoryScan(DIR* directory)
{
	struct dirent* file = 0;
	char* filePath = NULL;
	//reading the directory and adding the count by if its not another directory or . or ..
	while ((file = readdir(directory)) != NULL)
	{
		filePath = (char*)malloc(sizeof(char) * (strlen(file->d_name) + strlen(DIRECTORY) + 2));
		sprintf(filePath, "%s/%s", DIRECTORY, file->d_name);
		if (strcmp(file->d_name, ".") && strcmp(file->d_name, "..") && file->d_type != DT_DIR)
		{
			printf("File - %s\n", filePath);
			sortToDir(filePath, checkFileType(filePath) , file->d_name);
		}
		else
		{
			printf("Directory - %s\n", filePath);
			sortToDir(filePath, NULL, file->d_name);
		}
		free(filePath);
	}
	closedir(directory); //closing the directory and reutrning the count
}

char* checkFileType(char* filePath)
{
	char* fileExtension = NULL;
	if (strstr(filePath, "."))
	{
		fileExtension = (char*)malloc(sizeof(char) * (strlen(strstr(filePath, "."))) + 1);
		strcpy(fileExtension, strstr(filePath, ".") + 1);
		printf("FileExtension - %s\n", fileExtension);
		return fileExtension;
	}
	else
	{
		printf("FileExtension - None\n");
		return NULL;
	}
}

void sortToDir(char* filePath, char* fileExtension, char* fileName)
{
	if (fileExtension == NULL)
	{
		renameNewPath(filePath, FOLDERS, fileName);
	}
	else if (!strcmp("txt", fileExtension) || !strcmp("doc", fileExtension) || !strcmp("DOC", fileExtension) || !strcmp("TXT", fileExtension) || !strcmp("pdf", fileExtension) || !strcmp("PDF", fileExtension) || !strcmp("PPT", fileExtension) || !strcmp("ppt", fileExtension) || !strcmp("docx", fileExtension) || !strcmp("html", fileExtension) || !strcmp("DOCX", fileExtension) || !strcmp("c", fileExtension) || !strcmp("py", fileExtension) || !strcmp("bin", fileExtension) || !strcmp("DOCX", fileExtension) || !strcmp("DOCX", fileExtension) || !strcmp("pyc", fileExtension) || !strcmp("PYC", fileExtension) || !strcmp("xlsx", fileExtension) || !strcmp("XLSX", fileExtension))
	{
		renameNewPath(filePath, DOCUMENTS, fileName);
	}
	else if (!strcmp("jpg", fileExtension) || !strcmp("webp", fileExtension) || !strcmp("WEBP", fileExtension) || !strcmp("jpeg", fileExtension) || !strcmp("png", fileExtension) || !strcmp("ico", fileExtension) || !strcmp("jfif", fileExtension) || !strcmp("JPG", fileExtension) || !strcmp("JPEG", fileExtension) || !strcmp("PNG", fileExtension) || !strcmp("ICO", fileExtension) || !strcmp("JFIF", fileExtension))
	{
		renameNewPath(filePath, IMAGES, fileName);
	}
	else if (!strcmp("zip", fileExtension) || !strcmp("bak", fileExtension) || !strcmp("ZIP", fileExtension) || !strcmp("BAK", fileExtension) || !strcmp("pcap", fileExtension) || !strcmp("PCAP", fileExtension) || !strcmp("rar", fileExtension) || !strcmp("RAR", fileExtension))
	{
		renameNewPath(filePath, FOLDERS, fileName);
	}
	else if (!strcmp("mp4", fileExtension) || !strcmp("MP4", fileExtension) || !strcmp("webm", fileExtension) || !strcmp("WEBM", fileExtension) || !strcmp("wav", fileExtension) || !strcmp("WAV", fileExtension))
	{
		renameNewPath(filePath, VIDEOS, fileName);
	}
	else
	{
		renameNewPath(filePath, MISC, fileName);
	}
}

void renameNewPath(char* filePath, char* folderToWrite, char* fileName)
{
	char* newFilePath = NULL;
	newFilePath = (char*)malloc(sizeof(char) * (strlen(fileName) + strlen(folderToWrite) + 2));
	sprintf(newFilePath, "%s/%s", folderToWrite, fileName);
	rename(filePath, newFilePath);
	free(newFilePath);
}