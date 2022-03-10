#include <bits/stdc++.h>
#include <random>
#include <fstream>

#define BLK_SIZE 4

using namespace std;

static string root = "root/";

struct file{
    string filename;
    int inode;
    vector<string> disk_blocks;
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

    //TODO: Check if the file exists or not previously with same name
    for(file f:files){
        if(f.filename == filename){
            cout << "File with same name exists!\n";
            return;
        }
    }

    //Generating the blocks
    ofstream out;
    vector<string> disk_blocks;
    file f;

    for(int i=0; i<content_length; ++i){
        int cnt = 0;
        string block = root + to_string(dist(rng)) + ".txt";
        disk_blocks.push_back(block);
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
    f.inode = dist(rng);
    f.disk_blocks = disk_blocks;

    files.push_back(f);
    cout << "Files created successfully\n";
}

void print_file(string cmd){
    int cmd_length = cmd.length();
    int space = 0;
    string instruction = "", filename = "";

    //Parsing the command
    for(int i=0; i<cmd_length; ++i){
        if(cmd[i] == ' ') space ++;
        else if(space == 0 && cmd[i] != ' ')
            instruction += cmd[i];
        else if(space == 1){
            filename = cmd.substr(i);
            break;
        }
    }

    //Fetching the disk blocks
    vector<string> disk_blocks;
    for(file f: files){
        if(f.filename == filename){
            disk_blocks = f.disk_blocks;
            break;
        }
    }

    //Combining the disk block to form the string
    string content = "";
    ifstream in;
    for(string s: disk_blocks){
        in.open(s);
        string str;
        getline(in, str);
        content += str;
        in.close();
    }

    cout << content << "\n";
}

void delete_file(string cmd){
    int cmd_length = cmd.length();
    int space = 0;
    string instruction = "", filename = "";

    //Parsing the command
    for(int i=0; i<cmd_length; ++i){
        if(cmd[i] == ' ') space ++;
        else if(space == 0 && cmd[i] != ' ')
            instruction += cmd[i];
        else if(space == 1){
            filename = cmd.substr(i);
            break;
        }
    }

    //Deleting the files from file system
    vector<string> disk_blocks;
    for(file f : files){
        if(f.filename == filename)
            disk_blocks = f.disk_blocks;
    }

    for(string block : disk_blocks){
        remove(block.c_str());
    }

    //TODO: Deleting the entry from datastructure
    for(int i=0; i<files.size(); ++i){
        if(files[i].filename == filename){
            files.erase(files.begin()+i);
        }
    }
    cout << "Deleted the blocks!\n";
}

void rename_file(string cmd){
    int cmd_length = cmd.length();
    int space = 0;
    string instruction = "", filename1 = "", filename2 = "";

    //Parsing the command
    for(int i=0; i<cmd_length; ++i){
        if(cmd[i] == ' ') space ++;
        else if(space == 0 && cmd[i] != ' ')
            instruction += cmd[i];
        else if(space == 1 && cmd[i] != ' ')
            filename1 += cmd[i];
        else if(space == 2){
            filename2 = cmd.substr(i);
            break;
        }
    }

    //Rename the file
    bool flag = false;
    for(int i=0; i<files.size(); ++i){
        if(files[i].filename == filename1){
            files[i].filename = filename2;
            flag = true;
            break;
        }
    }
    if(!flag) cout << "File does not exist!\n";
}

void list_file(string cmd){
    //List all the existing files
    for(file f : files){
        cout << f.filename << " " << f.inode << "\n";
    }
}

int main(){
    string ch;
    while(true){
        string cmd;
        getline(cin, cmd);
        string instruction = "";
        for(int i=0; i<cmd.length(); ++i){
            if(cmd[i] != ' '){
                instruction += cmd[i];
            }
            else{
                break;
            }
        }

        if(instruction == "mf") {
            create_file(cmd);
            cin.clear();
        }
        else if(instruction == "pf") {
            print_file(cmd);
            cin.clear();
        }
        else if(instruction == "df") {
            delete_file(cmd);
            cin.clear();
        }
        else if(instruction == "rf") {
            rename_file(cmd);
            cin.clear();
        }
        else if(instruction == "ls") {
            list_file(cmd);
            cin.clear();
        }
        cout << "\nDo you want to enter another command?";
        cin.clear();
        getline(cin, ch);
        if(ch == "n" || ch == "N")
            break;
    }
    return 0;
}