#include<iostream>
#include <unordered_map>
#include<fstream>
#include <cstdlib>
#include <string>
using namespace std;

int bin_to_dec(string bin);
int main() {
    ifstream file;
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

    while (!file.eof()) {
        string opcode = stoi(file.substr(0, 3));

        if(opcode == "0000")//display -- ME
        {
            string reg = stoi(file.substr(4,7));
            cout << commands[reg] << endl;
        }
        else if (opcode =="0001")//input -- ME
        {
            int in =0;
            cin >> in;
            commands[file.substr(4,7)] = in;
        }
        else if (opcode == "0010")//move
        {
            string num1 = file.substr(4,7);
            string num2 = file.substr(8,11);
            commands[num2]=commands[num1];
        }
        else if(opcode == "0011") // add
        {
            string regs = file.substr(4,7);
            string first = file.substr(8,11);
            string second = file.substr(12,15);
            commands[regs] = commands[first] + commands[second];

        }
        else if (opcode =="0100")//subtract -- ME
        {
            string reg = file.substr(4,7);
            string num1 = file.substr(8,11);
            string num2 = fie.substr(12,15);

            int sub = commands[num1] - commands [num2];
            commands[reg] = sub;


        }
        else if (opcode =="0101")//multiply
        {
            string regs = inst.substr(4,7);
            string first = inst.substr(8,11);
            string second = inst.substr(12,15);
            commands[regs] = commands[first] * commands[second];

        }
        else if (opcode == "0110")//divide
        {
            string regs = inst.substr(4,7);
            string first = inst.substr(8,11);
            string second = inst.substr(12,15);
            commands[regs] = commands[first] / commands[second];
        }
        else if (opcode == "0111") //module
        {
            string reg = file.substr(4,7);
            string num1 = file.substr(8,11);
            string num2 = file.substr(12,15);
            commands[reg] = commands[num1]%commands[num2];
        }
        else if (opcode == "1000")//jump
        {
        }
        else if (opcode == "1001")//cond
        {
        }
        else if (opcode == "1010")//put
        {
            string reg = file.substr(4, 7);
            string num = file.substr(8, 13);

            int val = bin_to_dec(num);
            commands[reg] = val;
        }
    }
}
int bin_to_dec(string bin)
{
    int num = 0;
    for (int i = 0; i < bin.length(); i++)
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);
    return num;
}