#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <cctype>

using namespace std;

class Register {
public:
    static const int size = 16;  // Size of the register
    array<string, size> memory;   // Array to hold register values as strings

    Register() {
        for (int i = 0; i < size; i++) {
            memory[i] = "00";  // Initialize memory to "00"
        }
    }

    string getcell(int address) {
        if (address < 0 || address >= size) {
            cout << "Out of bounds." << endl;
            return "00";
        } else {
            return memory[address];
        }
    }

    void setcell(int address, const string &value) {
        bool isValidHex = true;
        for (char c : value) {
            if (!isxdigit(c)) {
                isValidHex = false;
                break;
            }
        }

        if (!isValidHex) {
            cout << "Invalid hex input." << endl;
            return;
        }

        if (value.size() == 2 && address >= 0 && address < size) {
            memory[address] = value;
        } else {
            cout << "Address out of bounds." << endl;
        }
    }
};

class ALU {
private:
    Register reg;  // Link Register directly in ALU

public:
    static int hexToDec(const string& hexStr) {
        return stoi(hexStr, nullptr, 16);
    }

    static string decToHex(int decimalValue) {
        stringstream ss;
        ss << hex << uppercase << decimalValue;
        return ss.str();
    }

    void add(int index1, int index2, int resultIndex) {
        string hex1 = reg.getcell(index1);
        string hex2 = reg.getcell(index2);

        int value1 = hexToDec(hex1);
        int value2 = hexToDec(hex2);

        int result = value1 + value2;
        reg.setcell(resultIndex, decToHex(result));
    }

    void displayRegister(int index) {
        cout << "Value at register " << index << ": " << reg.getcell(index) << endl;
    }
};

// Main function to test ALU and Register interaction
int main() {
    ALU alu;

    // Initialize some register cells
    alu.add(0, 0, 0);  // Initial set to show it works with ALU as single unit

    alu.displayRegister(0);  // Displaying content after addition

    return 0;
}
