//
// Created by Luis on 11/30/2017.
//

//
// Created by Luis on 11/30/2017.
//

#include<iostream>
#include <unordered_map>
#include<fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <limits>

using namespace std;

int bin_to_dec(string bin);
ifstream& GotoLine(ifstream& file, unsigned int num);

int main() {
    ifstream file;
    string inst;
    int op;
    file.open("myFile.chkn");

    unordered_map<string, int> commands;

    commands["0000"] = 0;
    commands["0001"] = 0;
    commands["0010"] = 0;
    commands["0011"] = 0;
    commands["0100"] = 0;
    commands["0101"] = 0;
    commands["0111"] = 0;
    commands["1010"] = 0;

    while (true) {

        file>>inst;
        if(file.eof())
            break;
       // cout<<inst<<endl;

        string opcode = inst.substr(0, 4);
        op = stoi(opcode);

        if(opcode == "0000")//display -- ME
        {
            string reg = inst.substr(4,4);
            cout << commands[reg] << endl;
        }
        else if (opcode =="0001")//input -- ME
        {
            int in =0;
            cin >> in;
            commands[inst.substr(4,4)] = in;
        }
        else if (opcode == "0010")//move
        {
            string num1 = inst.substr(4,4);
            string num2 = inst.substr(8,4);
            commands[num2]=commands[num1];
        }
        else if(opcode == "0011") // add
        {
            string regs = inst.substr(4,4);
            string first = inst.substr(8,4);
            string second = inst.substr(12,4);
            commands[regs] = commands[first] + commands[second];

        }
        else if (opcode =="0100")//subtract -- ME
        {
            string reg = inst.substr(4,4);
            string num1 = inst.substr(8,4);
            string num2 = inst.substr(12,4);

            int sub = commands[num1] - commands [num2];
            commands[reg] = sub;


        }
        else if (opcode =="0101")//multiply
        {
            string regs = inst.substr(4,4);
            string first = inst.substr(8,4);
            string second = inst.substr(12,4);
            commands[regs] = commands[first] * commands[second];

        }
        else if (opcode == "0110")//divide
        {
            string regs = inst.substr(4,4);
            string first = inst.substr(8,4);
            string second = inst.substr(12,4);
            commands[regs] = commands[first] / commands[second];
        }
        else if (opcode == "0111") //module
        {
            string reg = inst.substr(4,4);
            string num1 = inst.substr(8,4);
            string num2 = inst.substr(12,4);
            commands[reg] = commands[num1]%commands[num2];
        }
        else if (opcode == "1000")//jump
        {
            if(commands["bool"]== 1) {
                string num = inst.substr(4);
                file.clear();
                GotoLine(file, commands[num]);
            }
        }
        else if (opcode == "1001")//cond
        {
            string n1 = inst.substr(4,4);
            string n2 = inst.substr(8,4);
            //commands["bool"]= commands[n1] != commands[n2];

            //four entries: opcode condition num1 num2
            //conditions: 1-> if num1 is > num2
            //conditions: 3-> if num1 = num2
            //conditions: 2-> if num1 < num2
            //conditions: 4-> if num1 == 0 (one parameter)

            string condition = inst.substr(4,3);
            int num1= stoi(n1);
            int num2=stoi(n2);
            commands["bool"]= 0;

            if(bin_to_dec(condition) == 1)
            {
                if (num1 > num2)
                {
                    commands["bool"]= 1;
                }

            }
            else if(bin_to_dec(condition) == 2){
                if (num1 < num2)
                {
                    commands["bool"]= 1;
                }

            }
            else if(bin_to_dec(condition) == 3){
                if (num1 == num2)
                {
                    commands["bool"]= 1;
                }

            }
            else if(bin_to_dec(condition) == 4){
                if (num1 == 0)
                {
                    commands["bool"]= 1;
                }
            }
            if(commands["bool"] == 1){

                file>>inst;
                if(file.eof())
                    break;
        }
        }

        else if (opcode == "1010")//put
        {
            string reg = inst.substr (4, 4);
            string num = inst.substr (8);
            int val = bin_to_dec(num);
            commands[reg] = val;
        }
        else if (opcode == "1011")//var
        {
            commands[inst.substr(4,4)]= bin_to_dec( inst.substr(8) );
        }
        //inst="";
       // for ( auto it = commands.begin(); it != commands.end(); ++it )
         //   std::cout << " " << it->first << ":" << it->second <<endl;

        //cout<<endl;
        }
    return EXIT_SUCCESS;
    }


int bin_to_dec(string bin){
    int num = 0;
    for (int i = 0; i < bin.length(); i++)
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);
    return num;
}

ifstream& GotoLine(ifstream& file, unsigned int num){
    file.seekg(0, file.beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}
