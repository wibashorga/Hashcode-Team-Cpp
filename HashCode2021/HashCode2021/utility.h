#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split(string& s);
vector <int> str_to_int_vector(vector<string>& input);
void load_data_in_place(string path, vector<vector<string>>& buffer);
vector <vector<string>> load_data_as_vector(string path);
vector<string> load_data_as_strings(string path);


template <class T>
void print_vector(vector<T>& v)
{
    for (auto& item : v) cout << item << " ";
}

//écrit le contenu d'un vecteur dans un fichier

bool write_vector(vector<string>& v, string path, string sep);
bool write_vector(vector<int>& v, string path, string sep);
bool write_vector(vector<double>& v, string path, string sep);
