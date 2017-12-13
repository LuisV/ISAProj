//
// Created by Luis on 11/30/2017.
//
#include<iostream>
#include <unordered_map>
#include<fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int bin_to_dec(string bin);
ifstream& GotoLine(ifstream& file, unsigned int num);

int main() {


    ifstream file;
    string inst;
    int op;
    file.open("myFile.chkn");


    std::unordered_map <std:: string, std::vector<int>> arrMap;

    unordered_map<string, int> commands;

    int* c0= nullptr;
    //commands["0000"] = 0;
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
        //cout<<inst<<endl;
        string reg;

        string opcode = inst.substr(0, 4);
        op = stoi(opcode);

        if(opcode == "0000")//display -- ME
        {
            reg = inst.substr(4,4);
            if(reg=="0000")
                cout<<*c0<<endl;
            else
                cout << commands[reg] << endl;
        }
        else if (opcode =="0001")//input -- ME
        {
            int in =0;
            reg=inst.substr(4,4);
            cin >> in;
            if(reg=="0000")
                *c0=in;
            else
                commands[reg] = in;
        }
        else if (opcode == "0010")//move
        {

            string num1 = inst.substr(4,4);

            string num2 = inst.substr(8,4);

            if(num1=="0000"&& num2!="0000")
                *c0=commands[num2];
            else if (num1!="0000" && num2=="0000")
                commands[num1]= *c0;
            else
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

                string num = inst.substr(4);
                file.clear();
                GotoLine(file, commands[num]);

        }
        else if (opcode == "1001")//cond
        {
            double num1, num2;
            string n1 = inst.substr(8,4);
            string n2 = inst.substr(12,4);

            if(n1=="0000")
                num1=*c0;
            else
                num1 = commands[n1];

            if(n2=="0000")
                num2=*c0;
            else
                num2 = commands[n2];
            //commands["bool"]= commands[n1] != commands[n2];

            //four entries: opcode condition num1 num2
            //conditions: 1-> if num1 is > num2
            //conditions: 3-> if num1 = num2
            //conditions: 2-> if num1 < num2
            //conditions: 4-> if num1 == 0 (one parameter)

            string condition = inst.substr(4,4);
           // cout<<"C:"<<condition<<" "<<bin_to_dec(condition)<<" ";

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
            if(commands["bool"]== 1){

                file>>inst;
                //cout<<"taken"<<inst;
                if(file.eof())
                    break;

            }
        }

        else if (opcode == "1010")//put
        {
            reg = inst.substr (4, 4);
            string num = inst.substr (8);
            int val = bin_to_dec(num);

            if(reg=="0000")
                *c0=val;
            else
                commands[reg] = val;
        }
        else if (opcode == "1011")//var
        {
            commands[inst.substr(4,4)]= bin_to_dec( inst.substr(8) );
        }

        else if( opcode == "1100")//arr
        {
            std::vector<int> temp;
            temp.resize(bin_to_dec(inst.substr(8)));
          //  fill(temp.begin(),temp.end(),0);
            arrMap[inst.substr(4,4)]= temp;
          //  for ( auto it = arrMap[inst.substr(4,4)].begin(); it != arrMap[inst.substr(4,4)].end(); ++it )
            //    std::cout << "!" << *it;
            cout<<endl;
        }
        else if( opcode == "1101")//at
        {


            c0= &arrMap[inst.substr(4,4)].at(commands[inst.substr(8,4)]);

            cout<<endl;
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