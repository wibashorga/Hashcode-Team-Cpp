
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "utility.h"
using namespace std;

int main()
{
    string path = "a_example";
    auto data = load_data(path);
    for (auto& v : data)
    {
        for (auto& s : v) cout << s << " ";
        cout << endl;
    }

    auto numeric_tab = str_to_int_vector(data[0]);
    print_vector(numeric_tab);
}
