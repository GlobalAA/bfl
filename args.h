#ifndef ARGS_H
#define ARGS_H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <regex>

using namespace std;

class Args
{
public:
    Args(int argc, char **argv);
    map<string, string> args;
private:
    int argc;
    const vector<string> with_params = {"-target_file"};
    const vector<string> without_params = {"-target_dir", "-s"};
    char **argv;
};

#endif // ARGS_H
