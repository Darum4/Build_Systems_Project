#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <zlib.h>

using namespace std;

bool compressFiles(const string& archiveName, const vector<string>& files);
