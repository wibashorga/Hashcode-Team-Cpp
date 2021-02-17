
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

//fonction qui calcule le score
/*int score(vector<Pizza>& p)
{
    
    int sum = 0;
    for (auto& pizza : p)
    {
        set<string> s(pizza.begin()+1, pizza.end());
        sum += s.size() * s.size();
    }
    return sum;
}*/

/* on crée une fonction qui évalue la distance entre deux pizzas
plus la distance est grande, plus leurs ingrédients sont différents*/
int distance(Pizza& p1, Pizza& p2)
{
    int distance = p1.size() + p2.size();
    for (auto& ingredient : p1) if (find(p2.begin(), p2.end(), ingredient) != p2.end()) distance-=2;
    return distance;
}
int distanceToList(Pizza& p, initializer_list<int> list, vector<Pizza>& pizzas)
{
    int sum = 0;
    for (auto& p2 : list)
    {
        sum += distance(p, pizzas[p2]);
    }
    return sum;
}
set<int> available_pizzas(map<PairInt, int>& distances)
{
    set <int> dispo;
    for (auto& p : distances)
    {
        dispo.insert(p.first.first);
        dispo.insert(p.first.second);
    }
    return dispo;
}

void erase_item_from_distances(int item, map<PairInt, int>& distances)
{
    for (auto iterator = distances.begin(); iterator != distances.end();)
    {
        if (iterator->first.first == item || iterator->first.second == item)
        {
            iterator = distances.erase(iterator);
        }
        else iterator++;
    }
}

pair<int, int> choiceMax(map<PairInt, int>& distances)
{
    return (*max_element(distances.begin(), distances.end(), [](pair<const pair<int, int>, int>& p1,
        pair<const pair<int, int>, int>& p2) {
            return p1.second < p2.second;
        })).first;
}

void choice2(map<PairInt, int>& distances, vector<vector<int>>& outputs)
{
    if (distances.size())
    {
        auto max_elt = choiceMax(distances);
        outputs.push_back({ 2, max_elt.first, max_elt.second });
        erase_item_from_distances(max_elt.first, distances);
        erase_item_from_distances(max_elt.second, distances);
    }
}
void choice3(map<PairInt, int>& distances, vector<vector<int>>& outputs, vector<Pizza>& pizzas)
{
    if (distances.size())
    {
        auto max_elt = choiceMax(distances);
        vector<int> d;
        for (int i = 0; i < pizzas.size(); i++) d.push_back(i);
        auto available = available_pizzas(distances);//numéros des pizzas disponibles
        
        for_each(d.begin(), d.end(), [&max_elt, &pizzas, &available](auto& item) {
            if (available.find(item) != available.end())
            {
                item = distanceToList(pizzas[item], { max_elt.first, max_elt.second }, pizzas);
            }else item = -1;
            });
        
        cout << endl;
        int  third_pizza = std::distance(d.begin(), max_element(d.begin(), d.end()));
        outputs.push_back({ 3, max_elt.first, max_elt.second, third_pizza });
        erase_item_from_distances(max_elt.first, distances);
        erase_item_from_distances(max_elt.second, distances);
        erase_item_from_distances(third_pizza, distances);
        

    }
}

int main()
{
    string path = "a_example";
    auto file_data = load_data_as_vector(path);//on récupère les inputs et on les stocke dans un vector<vector<string>>
    auto first_line = str_to_int_vector(file_data[0]);
    int nb_pizzas = first_line[0], nb_2team = first_line[1], nb_3team = first_line[2], nb_4team = first_line[3];
    
    vector <vector<int>> outputs;// les différents outputs qu'il faudra afficher avec write_vector
    
    vector<Pizza> pizzas;//les différentes pizzas
    set<int> available_pizzas;
    for (int i = 1; i < file_data.size(); i++)
    {
        pizzas.push_back(Pizza(file_data[i].begin() + 1, file_data[i].end()));// on initialise pizzas
        available_pizzas.insert(i);
       
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
    
    /* La startégie consiste à fournir d'abord les équipes de deux puisqu'elles ont le moins de risque 
    * de se retrouver avec des doublons.
    * Pour décider quelles pizzas on leur fournit, on utilise la fonction de distance entre deux pizzas
    * qui permet de maximiser le nombre d'ingrédients différents
    */
    int score = 0;
   for (int i = 0; i < nb_2team; i++)         
   {
       choice2(distances, outputs);
       if (!distances.size()) break;
   }
   for (int i = 0; i < nb_3team; i++)
   {
       choice3(distances, outputs, pizzas);
       if (!distances.size()) break;
   }
   for (auto& v : outputs) {
       print_vector(v); cout << endl;
   }
   for (auto& p : distances) cout << "(" << p.first.first << ", " << p.first.second << ") :" << p.second << endl;
   
            
        
        
    


    cin.ignore();
}
