
#include <iostream>
#include <string>
#include <array>
#include <cctype>
#include <sstream>
#include<fstream>
#include<vector>
#include <variant>



using namespace std;


class machihne
{
private:
    CPU processor;
    Memory memory;
public:
    void load_programfile(ifstream& file)
    {
        if (!file.is_open())
        {
            cerr << "Error: File could not be opened." << endl;
            return;
        }

        string line, instruction;
        int address = 0;

        while (getline(file, line))
        {
            istringstream iss(line);  // Initialize with the current line
            while (iss >> instruction)
            {
                memory.setcell(address, instruction);
                address += 2;
            }
        }
    }


    void output_state()
    {

    }



};
