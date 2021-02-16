
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "utility.h"
using namespace std;
using Pizza = vector<string>;

int main()
{
    string path = "a_example";
    auto file_data = load_data_as_vector(path);//on récupère les inputs et on les stocke dans un vector<vector<string>>
    auto first_line = str_to_int_vector(file_data[0]);
    int nb_pizzas = first_line[0], nb_2team = first_line[1], nb_3team = first_line[2], nb_4team = first_line[3];
    Pizza pizzas;


    cin.ignore();
}
