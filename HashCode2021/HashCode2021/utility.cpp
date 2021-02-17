#include "utility.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
using std::ios;

vector<string> split(string& s)
{
    vector <string> v = { "" };
    for (int i =0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            if (v.back().size() && i!=s.size()-1 && s[i+1]!=' ') v.push_back("");
        }
        else
        {
            v.back() += s[i];
        }
    }
    return v;
}

//transforme un vecteur de string en vecteur d'entiers
vector <int> str_to_int_vector(vector<string>& input)
{
    vector <int> output;
    for (auto& s : input)
    {
        if (s != " ") output.push_back(stoi(s));
    }
    return output;
}

void load_data_in_place(string path, vector<vector<string>>& buffer)
{
    ifstream input_file(path.c_str());
    if (input_file)
    {
        string line;
        while (getline(input_file, line))
        {
            buffer.push_back(split(line));
        }
    }
}


/** Retourne un vector<vector<string>> des entrées*/
vector <vector<string>> load_data_as_vector(string path)
{
    ifstream input_file(path.c_str());
    vector<vector<string>> buffer;
    if (input_file)
    {
        string line;
        while (getline(input_file, line))
        {
            buffer.push_back(split(line));
        }
    }
    return buffer;
}

vector<string> load_data_as_strings(string path)
{

    ifstream input_file(path.c_str());
    vector<string> buffer;
    if (input_file)
    {
        string line;
        while (getline(input_file, line))
        {
            buffer.push_back(line);
        }
    }
    return buffer;
}

bool write_vector(vector<string>& v, string path, string sep)
{
    ofstream output_file(path.c_str(), ios::app);
    if (output_file)
    {
        for (auto& item : v) output_file << item << sep;
        output_file << endl;
    }
    bool open = output_file.is_open();
    output_file.close();
    return open;
}

bool write_vector(vector<int>& v, string path, string sep)
{
    ofstream output_file(path.c_str(), ios::app);
    if (output_file)
    {
        for (auto& item : v) output_file << item << sep;
        output_file << endl;
    }
    bool open = output_file.is_open();
    output_file.close();
    return open;
}
bool write_vector(vector<double>& v, string path, string sep)
{
    ofstream output_file(path.c_str(), ios::app);
    if (output_file)
    {
        for (auto& item : v) output_file << item << sep;
        output_file << endl;
    }
    bool open = output_file.is_open();
    output_file.close();
    return open;
}

string join(vector<string>& v)
{
    string s;
    for (auto& str : v) s += str;
    return s;
}