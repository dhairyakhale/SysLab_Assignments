#include <bits/stdc++.h>
#include <random>
#include <fstream>

#define BLK_SIZE 4

using namespace std;

struct file{
    string filename;
    vector<int> disk_blocks;
};

vector<file> files;

void create_file(string cmd){
    int cmd_length = cmd.length();
    int space = 0;
    string instruction = "", filename = "", content = "";

 
    for(int i=0; i<cmd_length; ++i){
        if(cmd[i] == ' ') space ++;
        else if(space == 0 && cmd[i] != ' ')
            instruction += cmd[i];
        else if(space == 1 && cmd[i] != ' ')
            filename += cmd[i];
        else if(space == 2){
            content = cmd.substr(i);
            break;
        }
    }

    //Removing the "" from the content
    content = content.substr(1, content.length()-2);
    int content_length = content.length();

    //Random number generation
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(1, (int)1e6);

    //Generating the blocks
    ofstream out;
    vector<int> disk_blocks;
    file f;

    for(int i=0; i<content_length; ++i){
        int cnt = 0;
        int block_number = dist(rng);
        string block = to_string(block_number) + ".txt";
        disk_blocks.push_back(block_number);
        out.open(block); 
        while(cnt < BLK_SIZE && i < content_length){
            out << content[i];
            i ++;
            cnt ++;
        }
        out.close();
        i --;
    }

    f.filename = filename;
    f.disk_blocks = disk_blocks;

    files.push_back(f);
}

int main(){
    string cmd; getline(cin, cmd);

    string instruction = "";
    for(int i=0; i<cmd.length(); ++i){
        if(cmd[i] != ' '){
            instruction += cmd[i];
        }
        else{
            break;
        }
    }


    if(instruction == "mf") create_file(cmd);
    return 0;
}