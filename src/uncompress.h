#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <zlib.h>

using namespace std;

bool uncompressFile(const string& archiveName);
