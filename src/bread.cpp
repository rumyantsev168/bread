#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

bool isNumeric(const string &s) {
    bool res = true;
    for (char c : s) {
        if (!(c >= '0' && c <= '9')) {
            res = false;
            break;
        }
    }
    return res;
}

string toLower(const string &s) {
    string res = "";
    for (char c : s) {
        res += tolower(c);
    }
    return res;
}

string charToByte(const char &c, const short int &base) {
    string res = "";
    unsigned char t = static_cast<unsigned char>(c);
    short int pad;
    switch (base) {
        case 2:
            pad = 8;
            break;
        case 8:
            pad = 4;
            break;
        case 10: 
            pad = 4;
            res = to_string(t);
            res.insert(0, pad-res.length(), '0');
        case 16:
            pad = 2;
            break;
    }
    while (t > 0) {
        int rem = t%base;
        char digit = (rem<10 ? '0'+rem : 'A'+rem-10);
        res = digit + res;
        t /= base;
    }
    res.insert(0, pad-res.length(), '0');
    return res;
}

bool getArgExists(const int &argc, const char* argv[], const string &name) {
    string prefix = "--" + name;
    bool res = false;
    for (int i = 0; i < argc; i++) {
        string current = argv[i];
        if (current.compare(0, prefix.length(), prefix) == 0) {
            res = true;
            break;
        }
    }
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
    string filename;
    int base = 16,
        bytesPerLine = 32,
        bytesCountMax = 0;
    bool verbose = true;
    if (argc == 1 || getArgExists(argc, argv, "help")) {
        cout << "Usage: " << argv[0] << " <filename> [--base=N] [--bytes_per_line=N] [--bytes_count_max=N] [--verbose=T/F]\n"
             << "Options:\n"
             << "  --base               How to represent the bytes. Default is 16. Possible values are:\n"
             << "                         2 - binary    8 - octal   10 - decimal    16 - hexadecimal\n"
             << "  --bytes_per_line     How many bytes should each output line display. Default is 32.\n"
             << "  --bytes_count_max    If specified, outputs first N bytes of a given file. Default is none.\n"
             << "  --verbose            Whether to print file name and total printed bytes count. Default is true.\n";
        return 0;
    } else {
        filename = argv[1];

        string baseValue = getArgValue(argc, argv, "base"),
               baseValues[4] = {"2", "8", "10", "16"};
        if (!baseValue.empty()) {
            if (find(baseValues, baseValues+4, baseValue) != baseValues+4) {
                base = stoi(baseValue);
            } else {
                cerr << "Invalid value for base: " << baseValue << ". Using " << base << " as default.\n";
            }
        }

        string bytesPerLineValue = getArgValue(argc, argv, "bytes_per_line");
        if (!bytesPerLineValue.empty()) {
            if (bytesPerLineValue != "0" && isNumeric(bytesPerLineValue)) {
                bytesPerLine = stoi(bytesPerLineValue);
            } else {
                cerr << "Invalid value for bytes_per_line: \'" << bytesPerLineValue << "\'. Using " << bytesPerLine << " as default.\n";
            }
        }

        string bytesCountMaxValue = getArgValue(argc, argv, "bytes_count_max");
        if (!bytesCountMaxValue.empty()) {
            if (isNumeric(bytesCountMaxValue)) {
                bytesCountMax = stoi(bytesCountMaxValue);
            } else {
                cerr << "Invalid value for bytes_count_max: \'" << bytesCountMaxValue << "\'. Printing all bytes.\n";
            }
        }

        string verboseValue = toLower(getArgValue(argc, argv, "verbose")),
               trueValues[] = {"true", "t", "yes", "y"};
        if (!verboseValue.empty() && find(trueValues, trueValues+4, verboseValue) == trueValues+4) {
            verbose = false;
        }
    }

    ifstream in(filename, ios::binary);
    if (!in.is_open()) {
        cerr << "Failed to open \'" << filename << "\'! Check if it exists.\n";
        return 1;
    }

    if (verbose) cout << (bytesCountMax ? "First "+to_string(bytesCountMax)+" bytes" : "Bytes") << " of \'" << filename << "\'\n\n";
    
    // Buffered read into an array and process from there
    const size_t BUF_SIZE = 4096;
    vector<char> buffer(BUF_SIZE);
    int bytesCount = 0;

    while (true) {
        size_t toRead = BUF_SIZE;
        if (bytesCountMax) {
            int remaining = bytesCountMax - bytesCount;
            if (remaining <= 0) break;
            toRead = static_cast<size_t>(min<int>(static_cast<int>(BUF_SIZE), remaining));
        }

        in.read(buffer.data(), static_cast<streamsize>(toRead));
        streamsize got = in.gcount();
        if (got <= 0) break;

        for (streamsize i = 0; i < got; ++i) {
            if (bytesCount && bytesCount % bytesPerLine == 0) cout << "\n";
            cout << charToByte(buffer[static_cast<size_t>(i)], base) << " ";
            ++bytesCount;
        }
    }

    cout << "\n";
    if (verbose) cout << "\nPrinted " << bytesCount << (bytesCountMax ? " of "+to_string(bytesCountMax) : "") << " bytes.\n";
    return 0;
}
