#include "compress.h"

bool compressFiles(const string& archiveName, const vector<string>& files)
{
    ofstream out(archiveName, ios::binary);
    if (!out) {
        cout << "Error: cannot create archive " << archiveName << endl;
        return false;
    }

    size_t fileCount = files.size();
    out.write((char*)&fileCount, sizeof(size_t));

    for (const string& filename : files) {
        ifstream in(filename, ios::binary);
        if (!in) {
            cout << "Warning: cannot open file " << filename << endl;
	    continue;
        }

        vector<char> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

        uLongf compressedSize = compressBound(data.size());
        vector<Bytef> compressed(compressedSize);

        if (compress(compressed.data(), &compressedSize,
                     (Bytef*)data.data(), data.size()) != Z_OK) {
            cout << "Warning: cannot compress file " << filename << endl;
	    continue;
        }

        size_t nameLen = filename.length();
        out.write((char*)&nameLen, sizeof(size_t));
        out.write(filename.c_str(), nameLen);

        size_t originalSize = data.size();
        out.write((char*)&originalSize, sizeof(size_t));
        out.write((char*)&compressedSize, sizeof(uLongf));
        out.write((char*)compressed.data(), compressedSize);

        cout << "File successfully archived: " << filename 
             << " (" << originalSize << " -> " << compressedSize << " byte)" << endl;
    }

    cout << "Archive created: " << archiveName << endl;
    return true;
}


int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Usage: compress <archive_name> <file1> [file2] ..." << endl;
        cout << "Example: compress backup.z photo.jpg document.txt" << endl;
        return 1;
    }

    string archiveName = argv[1];
    vector<string> files;

    for (int i = 2; i < argc; ++i) {
        files.push_back(argv[i]);
    }

    compressFiles(archiveName, files);
    return 0;
}

