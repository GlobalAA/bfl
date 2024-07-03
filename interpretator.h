#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>
#include <cstring>
#include <sstream>
#include <algorithm>

#include "args.h"


using namespace std;

class Interpretator
{
public:
    Interpretator();
    void manage(Args *args);

    void target_dir(string dir, bool save);
    void target_file(string file, bool save);
private:
    string interpretate();
    vector<char> acc;
    static char cpu[30000];
};

#endif // INTERPRETATOR_H
