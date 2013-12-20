//
//  HuskyLoader.cpp
//  dummy
//
//  Created by Brendan Ragan on 20/12/13.
//  Copyright (c) 2013 Stirfire Studios. All rights reserved.
//

#include "HuskyLoader.h"

#include <dirent.h>
#include <iterator>

HuskyLoader* HuskyLoader::instance;

HuskyLoaderHandle::HuskyLoaderHandle() {
	this->dllhandle = NULL;
}

HuskyLoaderHandle::HuskyLoaderHandle(void *dllhandle) {
	this->dllhandle = dllhandle;
}

bool endsWith(const char *string, const char *ending) {
	unsigned long length1, length2;
	length1 = strlen(string);
	length2 = strlen(ending);
	const char *endofstring = string + (length1 - length2);
	return strcmp(ending, endofstring) == 0;
}


HuskyLoader::HuskyLoader() {
	_map = new LoaderHandleMap();
}

unsigned long HuskyLoader::scanForHuskies() {
	return scanForHuskies(NULL);
}

unsigned long HuskyLoader::scanForHuskies(char *directory) {
	const char* extension = ".dylib";

	DIR *dir;
	if (directory == NULL) {
		dir = opendir(".");
	} else {
		dir = opendir(directory);
	}
	
	if (dir == NULL) {
		printf("Could not open specified directory!");
		return 0;
	}
	
	struct dirent *ent;
	while((ent = readdir(dir)) != NULL) {
		if (ent->d_type == DT_REG) {
			if (endsWith(ent->d_name, extension)) {
				void* dll_handle = dlopen(ent->d_name, RTLD_LOCAL|RTLD_LAZY);
				if (dll_handle) {
					HuskyGetStaticInstance* fHuskyInstance = (HuskyGetStaticInstance*)dlsym(dll_handle, "getHuskyInstance");
					HuskyGetName* fHuskyName = (HuskyGetName*)dlsym(dll_handle, "getHuskyName");
					if (fHuskyName && fHuskyInstance) {
						HuskyLoaderHandle *handleObj = new HuskyLoaderHandle(dll_handle);
						std::string *name = new std::string(fHuskyName());
						_map->insert(LoaderHandleMap::value_type(*name, *handleObj));
					}
				}
			}
		}
	}
	return _map->size();
}

const char* HuskyLoader::getHuskyName(int index) {
	if (index > _map->size())
		return NULL;

	LoaderHandleMap::iterator i = _map->begin();
	std::advance(i, index);
	return i->first.c_str();
}

Husky* HuskyLoader::getHuskyInstance(char *name) {
	std::string *strname = new std::string(name);
	HuskyLoaderHandle handleObj;
	try {
		handleObj = _map->at(*strname);
	} catch (std::exception &e) {
		return NULL;
	}

	HuskyGetStaticInstance* fHuskyInstance = (HuskyGetStaticInstance*)dlsym(handleObj.dllhandle, "getHuskyInstance");
	return fHuskyInstance();
}

HuskyLoader::~HuskyLoader() {
	free(_map);
}

HuskyLoader* HuskyLoader::getInstance() {
	if(!instance) {
		instance = new HuskyLoader();
	}
	return instance;
}