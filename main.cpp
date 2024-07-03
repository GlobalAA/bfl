#include <fstream>
#include <iostream>
#include <vector>


#include "interpretator.h"
#include "args.h"

using namespace std;

int main(int argc, char **argv) {
    Args args(argc, argv);
    Interpretator interp;

    interp.manage(&args);
}
