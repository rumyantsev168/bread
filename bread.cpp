#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <climits>
using namespace std;

bool isNumeric(string s) {
    bool res = true;
    for (char c : s) {
        if (!(c >= '0' && c <= '9')) {
            res = false;
            break;
        }
    }
    return res;
}

string charToHexByte(char c) {
    string res = "";
    unsigned char t = static_cast<unsigned char>(c);
    while (t > 0) {
        int rem = t%16;
        char hexDigit = (rem<10 ? '0'+rem : 'A'+rem-10);
        res = hexDigit + res;
        t /= 16;
    }
    res.insert(0, 2-res.length(), '0');
    return res;
}

string getArgValue(int argc, char* argv[], string name) {
    string prefix = "--" + name + "=",
           res = "";
    for (int i = 0; i < argc; i++) {
        string current = argv[i];
        if (current.compare(0, prefix.length(), prefix) == 0) {
            res = current.substr(prefix.length());
            break;
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
    char* filename;
    int bytesPerLine = 32,
        bytesCountMax = INT_MAX;
    if (argc == 1) {
        printf("Usage: %s <filename> [--bytes_per_line=N] [--bytes_count_max=N]\n\n", argv[0]);
        return 0;
    } else {
        filename = argv[1];

        string bytesPerLineValue = getArgValue(argc, argv, "bytes_per_line");
        if (!bytesPerLineValue.empty()) {
            if (isNumeric(bytesPerLineValue)) {
                bytesPerLine = stoi(bytesPerLineValue);
            } else {
                printf("Invalid value for bytes_per_line: '%s'. Using %i as default\n", bytesPerLineValue.c_str(), bytesPerLine);
            }
        }

        string bytesCountMaxValue = getArgValue(argc, argv, "bytes_count_max");
        if (!bytesCountMaxValue.empty()) {
            if (isNumeric(bytesCountMaxValue)) {
                bytesCountMax = stoi(bytesCountMaxValue);
            } else {
                printf("Invalid value for bytes_count_max: '%s'. Using %i as default\n", bytesCountMaxValue.c_str(), bytesCountMax);
            }
        }
    }

    ifstream in(filename, ios::binary);
    if (!in.is_open()) {
        printf("Failed to open %s\n\n", filename);
        return 1;
    }

    printf("Bytes of file: %s\n\n", filename);
    char byte;
    int bytesCount = 0;
    while (in.read(&byte, 1)) {
        if (bytesCount == bytesCountMax) break;
        if (bytesCount > 0 && bytesCount % bytesPerLine == 0) printf("\n");
        printf("%s ", charToHexByte(byte).c_str());
        bytesCount += 1;
    }
    printf("\n\nTotal: %i bytes\n\n", bytesCount);
    return 0;
}
