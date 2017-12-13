#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>

//functions that will read in operands after the opCode
void get1Operand( std::ifstream& in, std::ofstream& out);
void get1OperandAddress(std:: ifstream& in, std:: ofstream& out);
void get2Operands( std::ifstream& in, std::ofstream& out);
void setVar( std::string label, std::ifstream& in, std::ofstream& out);
void get3Operands( std::ifstream& in, std::ofstream& out);
void get3OperandsCond( std::ifstream& in, std::ofstream& out);

std::string dec_to_binary(int dec);

//All our operations in a handy reference map, just call the op name to receive the code
std::map<std::string, std::string> opCode = {{"disp","0000"},{"input","0001"},
                                             {"move", "0010"}, {"add","0011"}, {"subt", "0100"}, {"mult", "0101"}, {"div", "0110"},
                                             {"mod", "0111"},{"jump","1000"},{"cond","1001"}, {"put", "1010"}, {"var","1011"},{"arr", "1100"},
                                             {"at", "1101"}};

std::map <std:: string, std:: string> regCode = {{"i","0000"},{"c1","0001"},{"c2","0010"},
                                                 {"c3","0011"},{"c4","0100"},{"c5","0101"},{"c6","0111"},{"c7","1010"}};



int varCount=0;

int m()
{

    //File in our ISA to be read from - ".chicken" sounds like a nice file name
    std::ifstream filein("arr.chicken");

    //File to hold our binary data - this can be changed to follow the .o convention
    std::ofstream fileout("myFile.chkn");

    if(filein.fail())
    {
        std::cout<<"Error. Could not open file. Exiting...";
        exit(1);
    }


    //Variables needed to process thing
    std::string line, opcode, operand;

    //Line counter
    int counter=0;

    while(!filein.eof())
    {
        counter++;

        filein>>opcode;
        std::cout<< opcode;

        if(!opCode.count(opcode))
        {
            std::cout<<"Error. No such instruction at line "<<counter;
            exit(2);
        }

        fileout<< opCode.at(opcode);
        if( opcode == "var")
        {
            filein>>opcode;
            setVar(opcode, filein, fileout);
        }
        else if( opcode=="arr")
        {
            filein>>opcode;
            setVar(opcode,filein, fileout);
        }
        else if( opcode == "put")
        {
            filein>>opcode;
            if(regCode.count(opcode))
            {
                fileout<<regCode[opcode];
            }
            else {
                std::cout<<"ERROR!";
                exit(1);
            }
            filein>>opcode;
            fileout<<dec_to_binary(stoi(opcode))<<std::endl;

        }
        else if( opcode == "cond")
            get3OperandsCond(filein,fileout);
        else if( opcode =="disp" || opcode == "input" || opcode == "jump")
            get1OperandAddress(filein, fileout);
        else if(opcode == "move" || opcode=="at")
            get2Operands( filein, fileout);
        else
            get3Operands(filein, fileout);

    }
}


void get1Operand(std:: ifstream& in, std:: ofstream& out)
{
    std::string line;
    in>>line;
    //std::cout<<line<<std::endl;
    if(isdigit(line[0]))
    {
        out<<" " <<dec_to_binary(stoi(line))<<std::endl;
    }
    //out<<std::endl;
}

void setVar( std::string label, std::ifstream& in, std::ofstream& out)
{
    regCode[label]=dec_to_binary(8+varCount);
    varCount++;
    out<< regCode[label];
    std::string line;
    in>>line;
    out<< dec_to_binary(std::stoi( line ));

    out<<std::endl;


}

void get1OperandAddress(std:: ifstream& in, std:: ofstream& out)
{
    std::string line;
    in>>line;
    //std::cout<<line;
    if(regCode.count(line))
    {
        out<<regCode[line];
    }
    else {
        std::cout<<"ERROR!";
        exit(1);
    }
    out<<std::endl;

}

void get2Operands( std::ifstream& in, std::ofstream& out)
{
    std::string line;
    in>>line;
    if(regCode.count(line))
    {
        out<<regCode[line];
    }
    else {
        std::cout<<"ERROR!";
        exit(1);
    }
    in>>line;
    if(regCode.count(line))
    {
        out<<regCode[line];
    }
    else {
        std::cout<<"ERROR!";
        exit(1);
    }
    out<<std::endl;


}

void get3Operands( std::ifstream& in, std::ofstream& out)
{
    std::string line;
    in>>line;
    if(regCode.count(line))
    {
        out<<regCode[line];
    }
    else {
        std::cout<<"ERROR!";
        exit(1);
    }
    in>>line;
    if(regCode.count(line))
    {
        out<<regCode[line];
    }
    else {
        std::cout<<"ERROR!";
        exit(1);
    }
    in>>line;
    if(regCode.count(line))
    {
        out<<regCode[line];
    }
    else {
        std::cout<<"ERROR!";
        exit(1);
    }
    out<<std::endl;
}


void get3OperandsCond( std::ifstream& in, std::ofstream& out)
{
    std::string line;

    in>>line;
    int cas= std::stoi(line);
    out<<dec_to_binary(cas);
    in>>line;
    if(regCode.count(line))
    {
        out<<regCode[line];
    }
    else {
        std::cout<<"ERROR!";
        exit(1);
    }
    in>>line;
    if(cas!=4) {
        if (regCode.count(line)) {
            out << regCode[line];
        }
        else {
            std::cout << "ERROR!";
            exit(1);
        }
    }
    out<<std::endl;
}

std::string dec_to_binary(int dec)
{
    std::string bin = "";

    if(dec == 0)
        return "0000000";

    while(dec / 2 != 0)
    {
        bin = std::to_string(dec % 2) + bin;
        dec /= 2;
    }
    bin = "1" + bin;

    while(bin.size() < 4)
        bin = "0" + bin;

    return bin;
}



























/*#include <iostream>
using namespace std;
void display( int value)
{
    cout<< value<<endl;
}

template <class Process, class Item, class SizeType>
void apply( Process f, Item data[], SizeType n)
{
    for(SizeType i=0; i< n; i++)
    {
        f(data[i]);
    }
};

int main() {
    int a1[10] = {3,5,7,9,1,2,3,4,6,12};
    apply(display, a1,10);
    return 0;
}
*/