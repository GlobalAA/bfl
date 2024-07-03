#include "interpretator.h"

char Interpretator::cpu[30000];

Interpretator::Interpretator() {}

void Interpretator::manage(Args *args) {
    filesystem::path cwd = filesystem::current_path();

    if (args->args.count("target_file") >= 2 && args->args.count("target_dir") >= 2) {
        cout << "target_file and target_dir arguments cannot be used simultaneously" << endl;
        exit(0);
    }

    bool save_mode = false;

    if (args->args.count("s") == 1) {
        save_mode = (string)args->args.at("s") == "true";
    }
    if (args->args.count("target_file") == 1) {
        this->target_file(args->args.at("target_file"), save_mode);
    }
    if (args->args.count("target_dir") == 1) {
        this->target_dir(cwd, save_mode);
    }
}

string Interpretator::interpretate() {
    string output;
    unsigned int j = 0;
    int brc = 0;
    unsigned int e_count = 0;
    char operators[8] = {'>', '<', '+', '-', '.', ',', '[', ']'};
    for (int i = 0; i < this->acc.size(); ++i) {
        auto it = find(begin(operators), end(operators), this->acc[i]);
        if (it == end(operators)) {
            if (e_count > 3) {
                cout << "Brainfuck code not found" << endl;
                exit(0);
            }
            e_count++;
            continue;
        }

        if (this->acc[i] == '>') j++;
        if (this->acc[i] == '<') j--;
        if (this->acc[i] == '+') this->cpu[j]++;
        if (this->acc[i] == '-') this->cpu[j]--;
        if (this->acc[i] == '.') output+=this->cpu[j];
        if (this->acc[i] == ',') cin >> this->cpu[j];
        if (this->acc[i] == '[') {
            if (!this->cpu[j]) {
                ++brc;
                while (brc) {
                    ++i;
                    if (this->acc[i] == '[')
                        ++brc;
                    if (this->acc[i] == ']')
                        --brc;
                }
            } else continue;
        } else if (this->acc[i] == ']') {
            if (!this->cpu[j]) continue;
            else {
                if (this->acc[i] == ']') brc++;
                while (brc) {
                    --i;
                    if (this->acc[i] == '[') brc--;
                    if (this->acc[i] == ']') brc++;
                }
                --i;
            }
        }
    }
    return output;
}
void Interpretator::target_dir(string dir, bool save) {
    map<string, string> files;
    map<string, string>::iterator file_iter;

    map<string, string> outputs;
    map<string, string>::iterator output_iter;

    for (const auto &entity : filesystem::directory_iterator(dir)) {
        filesystem::path path = entity.path();
        if (path.extension() == ".bf") {
            files[path] = path;
        }
    }

    cout << "Found " << files.size() << " brainfucks files" << endl << endl;

    for (file_iter = files.begin(); file_iter != files.end(); file_iter++) {
        this->acc.clear();
        memset(this->cpu, 0, sizeof(this->cpu));

        string filename = file_iter->first;
        string path = file_iter->second;

        char ch;
        ifstream infile(path);
        if (infile) {
            while (infile) {
                infile.get(ch);
                this->acc.push_back(ch);
            }
            infile.close();
        }

        string data = this->interpretate();
        outputs[filename] = data;
    }

    for (output_iter = outputs.begin(); output_iter != outputs.end(); output_iter++) {
        string file = output_iter->first;
        string data = output_iter->second;

        if (!save) {
            stringstream ss(file);
            string token;
            vector<string> tokens;

            while (getline(ss, token, '/')) {
                tokens.push_back(token);
            }


            cout << "Filename: " << tokens.back() << endl;
            cout << data << endl << endl;
        }
        else {
            ofstream ofile(file);
            ofile << data;
            ofile.close();

            cout << "File updated" << endl;
        }
    }
}

void Interpretator::target_file(string file, bool save) {
    char ch;
    ifstream infile(file);
    if (infile) {
        while (infile) {
            infile.get(ch);
            this->acc.push_back(ch);
        }
        infile.close();
    }
    else {
        cout << "File not found" << endl;
        exit(0);
    }

    string data = this->interpretate();

    if (save){
        ofstream ofile(file);
        ofile << data;
        ofile.close();

        cout << "File updated" << endl;
    }
    else {
        cout << data << endl;
    }
}
