#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <map>

//functions that will read in operands after the opCode
void get1Operand( std::ifstream& in, std::ofstream& out);
void get2Operands( std::ifstream& in, std::ofstream& out);
std::string dec_to_binary(int dec);


int main()
{
    //All our operations in a handy reference map, just call the op name to receive the code
    const std::map<std::string, std::string> opCode = {{"disp","0000"},{"input","0001"},
    {"move", "0010"}, {"add","0011"}, {"subt", "0100"}, {"mult", "0101"}, {"div", "0110"},
    {"mod", "0111"},{"jump","1000"},{"cond","1001"}};

    //File in our ISA to be read from - ".chicken" sounds like a nice file name
    std::ifstream filein("myFile.chicken");

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

        if(!opCode.count(opcode))
        {
            std::cout<<"Error. No such instruction at line "<<counter;
            exit(2);
        }

        fileout<< opCode.at(opcode);
        if( opcode =="disp" || opcode == "input" )
            get1Operand(filein, fileout);
        else
            get1Operand( filein, fileout);
    }
}

void get1Operand(std:: ifstream& in, std:: ofstream& out)
{
    std::string line;
    in>>line;
    std::cout<<line<<std::endl;
    if(isdigit(line[0]))
    {
        out<<" " <<dec_to_binary(stoi(line))<<std::endl;
    }
}

void get2Operands( std::string, std::ofstream& out)
{
    std::cout<<"shouldn't be here";
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

    while(bin.size() < 6)
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