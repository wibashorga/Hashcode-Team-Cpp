#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> split(string& s);
vector <int> str_to_int_vector(vector<string>& input);
void load_data_in_place(string path, vector<vector<string>>& buffer);
vector <vector<string>> load_data(string path);


template <class T>
void print_vector(vector<T>& v)
{
    for (auto& item : v) cout << item << " ";
}
