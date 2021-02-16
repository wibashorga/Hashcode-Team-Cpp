#include "utility.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

vector<string> split(string& s)
{
    vector <string> v = { "" };
    for (auto& c : s)
    {
        if (c == ' ')
        {
            if (v.back().size() && (&c != &s.back())) v.push_back("");
        }
        else
        {
            v.back() += c;
        }
    }
    return v;
}

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

vector <vector<string>> load_data(string path)
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

