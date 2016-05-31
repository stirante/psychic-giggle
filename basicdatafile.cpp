#include "basicdatafile.h"
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

//TODO: probably should be moved to binary saving instead text saving
BasicDataFile::BasicDataFile(std::string name)
{
    filename = name;
}

int BasicDataFile::getInteger(string key)
{
    return atoi(values[key].c_str());
}

float BasicDataFile::getFloat(string key)
{
    return atof(values[key].c_str());
}

double BasicDataFile::getDouble(string key)
{
    return atof(values[key].c_str());
}

long BasicDataFile::getLong(string key)
{
    return atol(values[key].c_str());
}

char BasicDataFile::getChar(string key)
{
    return values[key].c_str()[0];
}

bool BasicDataFile::getBoolean(string key)
{
    return atoi(values[key].c_str()) == 1;
}

string BasicDataFile::get(string key)
{
    return values[key];
}

void BasicDataFile::putBoolean(string key, bool val)
{
    ostringstream os;
    os << val;
    put(key, os.str());
}

void BasicDataFile::put(string key, string val)
{
    /*if (key.find("=") != key.end()) {
        cerr << "Key cannot containt '=' character!" << endl;
        return;
    }
    if (val.find("=") != val.end()) {
        cerr << "Value cannot containt '=' character!" << endl;
        return;
    }*/
    values[key] = val;
}

bool BasicDataFile::has(string key)
{
    return values.find(key) != values.end();
}

void BasicDataFile::putInteger(string key, int val)
{
    ostringstream os;
    os << val;
    put(key, os.str());
}
void BasicDataFile::putFloat(string key, float val)
{
    ostringstream os;
    os << val;
    put(key, os.str());
}
void BasicDataFile::putDouble(string key, double val)
{
    ostringstream os;
    os << val;
    put(key, os.str());
}
void BasicDataFile::putLong(string key, long val)
{
    ostringstream os;
    os << val;
    put(key, os.str());
}

void BasicDataFile::putChar(string key, char val)
{
    ostringstream os;
    os << val;
    put(key, os.str());
}

bool BasicDataFile::save()
{
    ofstream fs(filename.c_str());
    if (!fs) return false;
    for (map<string, string>::iterator i = values.begin();i != values.end();i++) {
        fs << i->first << "=" << i->second << endl;
    }
    fs.flush();
    fs.close();
    return true;
}

bool BasicDataFile::load()
{
    ifstream ifs(filename.c_str());
    if (!ifs) return false;
    string line;
    while (getline(ifs, line))
    {
        istringstream is_line(line);
        string key;
        if (getline(is_line, key, '='))
        {
            string value;
            if (key[0] == '#')//support for commenting
                continue;
            if (getline(is_line, value))
            {
                values[key] = value;
            }
        }
    }
    return true;
}

string BasicDataFile::getFilename()
{
    return filename;
}

