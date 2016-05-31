#ifndef BASICDATAFILE_H
#define BASICDATAFILE_H

#include<string>
#include<map>

using namespace std;

class BasicDataFile
{
    string filename;
    map<string, string> values;
public:
    BasicDataFile(string filename);
    int getInteger(string);
    float getFloat(string);
    double getDouble(string);
    char getChar(string);
    long getLong(string);
    bool getBoolean(string);
    string get(string);

    void putInteger(string, int);
    void putFloat(string, float);
    void putDouble(string, double);
    void putChar(string, char);
    void putLong(string, long);
    void putBoolean(string, bool);
    void put(string, string);

    bool has(string);

    bool save();
    bool load();

    string getFilename();
};

#endif // BASICDATAFILE_H
