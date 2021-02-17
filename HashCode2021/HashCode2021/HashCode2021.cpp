
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include "utility.h"
using namespace std;
using Pizza = vector<string>;
using PairInt = pair<int, int>;

//fonction qui calcule le score
int score(vector<Pizza>& p)
{
    
    int sum = 0;
    for (auto& pizza : p)
    {
        set<string> s(pizza.begin()+1, pizza.end());
        sum += s.size() * s.size();
    }
    return sum;
}

/* on crée une fonction qui évalue la distance entre deux pizzas
plus la distance est grande, plus leurs ingrédients sont différents*/
int distance(Pizza& p1, Pizza& p2)
{
    int distance = min(p1.size(), p2.size());
    for (auto& ingredient : p1) if (find(p2.begin(), p2.end(), ingredient) != p2.end()) distance--;
    return distance;
}

//


int main()
{
    string path = "a_example";
    auto file_data = load_data_as_vector(path);//on récupère les inputs et on les stocke dans un vector<vector<string>>
    auto first_line = str_to_int_vector(file_data[0]);
    int nb_pizzas = first_line[0], nb_2team = first_line[1], nb_3team = first_line[2], nb_4team = first_line[3];
    
    vector <vector<int>> outputs;// les différents outputs qu'il faudra afficher avec write_vector
    
    vector<Pizza> pizzas;//les différentes pizzas
    for (int i = 1; i < file_data.size(); i++)
    {
        pizzas.push_back(Pizza(file_data[i].begin() + 1, file_data[i].end()));// on initialise pizzas
       
    }
    //for (auto& pizza : pizzas) print_vector(pizza);
    
    map<pair<int, int>, int> distances;// on stocke la distance entre chaque pizza qui correspon au nombre d'ingrédients différents
    for (int i = 0; i < pizzas.size(); i++)
    {
        for (int j = i; j < pizzas.size(); j++)
        {
            if (i < j) distances[PairInt(i, j)] = distance(pizzas[i], pizzas[j]);
        }
    }
    for (auto& p : distances) cout << "(" << p.first.first << ", " << p.first.second << ") :" << p.second << endl;
    
    /* La startégie consiste à fournir d'abord les équipes de deux puisqu'elles ont le moins de risque 
    * de se retrouver avec des doublons.
    * Pour décider quelles pizzas on leur fournit, on utilise la fonction de distance entre deux pizzas
    * qui permet de maximiser le nombre d'ingrédients différents
    */

    for (int team = 1; team <= nb_2team; team++)
    {
        auto it_max = max_element(distances.begin(), distances.end(), [](pair<const pair<int,int>, int>& p1, 
            pair<const pair<int,int>, int>& p2) {
            return p1.second < p2.second;
            });
        cout << "max :" << it_max->first.first << ", " << it_max->first.second << endl;
    }


    cin.ignore();
}
