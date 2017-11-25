#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <map>

//functions that will read in operands after the opCode
std::string get1Operand();
std::string get2Operands();

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
        std::getline(filein, line);
        opcode= line.substr(0, line.find(' '));
        if(!opCode.count(opcode))
        {
            std::cout<<"Error. No such instruction at line "<<counter;
            exit(2);
        }
        fileout<< opCode.at(opcode)<<std::endl;

    }


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