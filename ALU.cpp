#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <cctype>
#include <cmath> 


using namespace std;

class Register {
public:
    static const int size = 16;  
    array<string, size> memory;   

    Register() {
        for (int i = 0; i < size; i++) {
            memory[i] = "00"; 
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
    Register& registerFile;

    float hexToFloat(const string& hexValue) {
        int binary = stoi(hexValue, nullptr, 16);

        int sign = (binary >> 7) & 0x1;       
        int exponent = (binary >> 4) & 0x7;   
        int mantissa = binary & 0xF;         

        // Convert to floating-point using the custom format
        float value = (mantissa / 16.0f) * pow(2, exponent - 4);
        if (sign == 1) value = -value;       

        return value;
    }

    void addFloating(int index1, int index2, int dest) {
        float num1 = hexToFloat(registerFile.getCell(index1));
        float num2 = hexToFloat(registerFile.getCell(index2));
        float sum = num1 + num2;

        string resultHex = floatToHex(sum);
        registerFile.setCell(dest, resultHex);
    }

    string floatToHex(float value) {
        int sign = value < 0 ? 1 : 0;
        value = fabs(value); 

        int exponent = 4;
        while (value >= 1.0f && exponent < 7) {
            value /= 2;
            exponent++;
        }
        while (value < 0.5f && exponent > 0) {
            value *= 2;
            exponent--;
        }

        int mantissa = static_cast<int>(value * 16) & 0xF;

        int binary = (sign << 7) | (exponent << 4) | mantissa;

        char hexStr[3];
        snprintf(hexStr, 3, "%02X", binary);
        return string(hexStr);
    }

public:
    ALU(Register& reg) : registerFile(reg) {}
};

int main() {
    Register reg;
    ALU alu(reg);

    reg.setCell(0, "A3");
    reg.setCell(1, "4E");
    alu.addFloating(0, 1, 2);
    cout << "Result in register 2: " << reg.getCell(2) << endl;

    return 0;
}

