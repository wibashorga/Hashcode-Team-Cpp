
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include <cmath>
#include <initializer_list>
#include "utility.h"
using namespace std;
using Pizza = vector<string>;
using PairInt = pair<int, int>;


void attributePizzasToTeam(vector<vector<int>>& outputs, vector<PairInt>& pizzas_scores, vector<int> pizzas)
{
    outputs.push_back(pizzas);
    
}
void erase_item_from_pizzas(int item, vector<PairInt>& pizzas_scores)
{
    remove_if(pizzas_scores.begin(), pizzas_scores.end(), [&item](const PairInt& p) {
        return p.first == item;
        });
}

bool choice4(vector<PairInt>& pizzas_scores, vector<vector<int>>& outputs, int& nb4, int nb4_max)
{
    if (pizzas_scores.size() >= 4 && nb4<nb4_max)
    {
        int first, second, third, last;
        int t = pizzas_scores.size();
        first = pizzas_scores[0].first;
        second = pizzas_scores[1].first;
        third = pizzas_scores[t - 1].first;
        last = pizzas_scores[t - 2].first;
        outputs.push_back({ 4, first, second, third, last });
        pizzas_scores.erase(pizzas_scores.begin());
        pizzas_scores.erase(pizzas_scores.begin()+1);
        pizzas_scores.erase(pizzas_scores.end()-1);
        pizzas_scores.erase(pizzas_scores.end()-1);
        nb4++;

        
        return true;

    }
    return false;

}
bool choice3(vector<PairInt>& pizzas_scores, vector<vector<int>>& outputs, int& nb3, int nb3_max)
{
    if (pizzas_scores.size() >= 3 && nb3 < nb3_max)
    {
        int first, second, third, last;
        int t = pizzas_scores.size();
        first = pizzas_scores[0].first;
        second = pizzas_scores[1].first;
        third = pizzas_scores[t - 1].first;
        //last = pizzas_scores[t - 3].first;
        outputs.push_back({ 3, first, second, third});
        pizzas_scores.erase(pizzas_scores.begin());
        pizzas_scores.erase(pizzas_scores.begin() + 1);
        pizzas_scores.erase(pizzas_scores.end() - 1);
        //pizzas_scores.erase(pizzas_scores.end() - 1);

    }
    return false;

}
bool choice2(vector<PairInt>& pizzas_scores, vector<vector<int>>& outputs, int& nb2, int nb2_max)
{
    if (pizzas_scores.size() >= 2 && nb2 < nb2_max)
    {
        int first, second, third, last;
        int t = pizzas_scores.size();
        first = pizzas_scores[0].first;
        second = pizzas_scores[t-1].first;
        outputs.push_back({ 2, first, second});
        pizzas_scores.erase(pizzas_scores.begin());
        pizzas_scores.erase(pizzas_scores.end() - 1);
        //pizzas_scores.erase(pizzas_scores.end() - 1);
        //pizzas_scores.erase(pizzas_scores.end() - 1);

    }
    return false;

}
int main()
{
    for (auto ch : { "a","b","c","d","e" })
    {
        string input_path = string(ch)+"_input_set";
        string output_path = string(ch)+"_resu.txt";
        auto file_data = load_data_as_vector(input_path);//on récupère les inputs et on les stocke dans un vector<vector<string>>
        auto first_line = str_to_int_vector(file_data[0]);
        int nb_pizzas = first_line[0], nb_2team = first_line[1], nb_3team = first_line[2], nb_4team = first_line[3];

        vector <vector<int>> outputs;// les différents outputs qu'il faudra afficher avec write_vector

        vector<Pizza> pizzas;//les différentes pizzas

        set<int> available_pizzas;
        vector<pair<int, int>> pizzas_points;


        for (int i = 1; i < file_data.size(); i++)
        {
            pizzas.push_back(Pizza(file_data[i].begin() + 1, file_data[i].end()));// on initialise pizzas
            available_pizzas.insert(i);
            pizzas_points.push_back(PairInt(i - 1, pizzas.back().size()));
        }
        /*
        sort(pizzas_points.begin(), pizzas_points.end(), [](const auto a, const auto b) {
            return a.second > b.second;
            });*/
        int nb4 = 0, nb3 = 0, nb2 = 0;
        while (choice4(pizzas_points, outputs, nb4, nb_4team));
        while (choice3(pizzas_points, outputs, nb3, nb_3team));
        while (choice2(pizzas_points, outputs, nb2, nb_2team));

        ofstream outfile(output_path);
        outfile << outputs.size() << endl;
        for (auto& v : outputs)
        {
            write_vector(v, output_path);
        }
        cout << ch << " ended" << endl;
    }
    cout << "end";

    cin.ignore();
}
