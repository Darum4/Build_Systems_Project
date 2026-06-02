#include "uncompress.h"

bool uncompressFile(const string& archiveName)
{
    ifstream in(archiveName, ios::binary);
    if (!in) {
        cout << "Error: cannot open archive " << archiveName << endl;
        return false;
    }

    size_t fileCount;
    in.read((char*)&fileCount, sizeof(size_t));

    cout << "Found " << fileCount << " files in archive " << archiveName << endl;

    for (size_t i = 0; i < fileCount; ++i) {
        size_t nameLen;
        in.read((char*)&nameLen, sizeof(size_t));

        string filename(nameLen, '\0');
        in.read(&filename[0], nameLen);

        size_t originalSize;
        in.read((char*)&originalSize, sizeof(size_t));

        uLongf compressedSize;
        in.read((char*)&compressedSize, sizeof(uLongf));

        vector<Bytef> compressed(compressedSize);
        in.read((char*)compressed.data(), compressedSize);

        vector<Bytef> decompressed(originalSize);
        uLongf decompressedSize = originalSize;

        if (uncompress(decompressed.data(), &decompressedSize,
                       compressed.data(), compressedSize) != Z_OK) {
            cout << "Error while extracting file: " << filename << endl;
            continue;
        }

        ofstream out(filename, ios::binary);
        if (!out) {
            cout << "Cannot create file: " << filename << endl;
            continue;
        }

        out.write((char*)decompressed.data(), decompressedSize);
        cout << "Extracted file: " << filename << " (" << decompressedSize << " bytes)" << endl;
    }

    cout << "Unarchivation complete: " << archiveName << endl;
    return true;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: uncompress <archive1> [archive2] ..." << endl;
        cout << "Example: uncompress backup.z" << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        cout << "Extracting file: " << argv[i] << " ..." << endl;
        uncompressFile(argv[i]);
        cout << endl;
    }

    return 0;
}

