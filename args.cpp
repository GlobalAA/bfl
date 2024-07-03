#include "args.h"

Args::Args(int p_argc, char **p_argv): argv(p_argv), argc(p_argc) {
    regex pattern(R"((.+)=(.+))");
    smatch matches;

    for (int idx = 1; idx < this->argc; ++idx) {
        string arg = this->argv[idx];

        if (regex_match(arg, matches, pattern)) {
            auto it = find(this->with_params.begin(), this->with_params.end(), matches[1]);
            if (it != this->with_params.end()) {
                string key = matches[1].str();
                string val = matches[2].str();

                key.replace(key.find("-"), 1, "");
                this->args[key] = val;
            }
            else {
                printf("Argument not found\n");
                exit(0);
            }
        }
        else if (find(this->without_params.begin(), this->without_params.end(), arg) != this->without_params.end()) {
            arg.replace(arg.find("-"), 1, "");
            this->args[arg] = "true";
        }
        else {
            printf("Argument not valid\n");
            exit(0);
        }
    }
}
