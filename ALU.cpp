#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <stdexcept>
#include <sstream>

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

    string getCell(int address) {
        if (address < 0 || address >= size) {
            cout << "Out of bounds." << endl;
            return "00";
        }
        return memory[address];
    }

    void setCell(int address, const string& value) {
        if (value.size() == 2 && address >= 0 && address < size) {
            memory[address] = value;
        } else {
            cout << "Invalid input or address out of bounds." << endl;
        }
    }
};

class ALU {
    Register& registerFile;

public:
    ALU(Register& reg) : registerFile(reg) {}

    static int hexToDec(const string& hexStr) {
        int decimal;
        stringstream ss;
        ss << hex << hexStr;
        ss >> decimal;
        return decimal;
    }

    static string decToHex(int decimal) {
        stringstream ss;
        ss << hex << uppercase << ((decimal < 16) ? "0" : "") << decimal;
        return ss.str();
    }

    static bool isValidString(const string& str) {
        for (char c : str) {
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
                return false;
            }
        }
        return true;
    }

    void addRegistersFloat(string r, string s, string t) {
        if (!isValidString(r) || !isValidString(s) || !isValidString(t)) {
            cout << "Invalid hexadecimal input." << endl;
            return;
        }

        int R = hexToDec(t);
        int S = hexToDec(s);
        int T = hexToDec(r);
// Hexa to float 
        auto hexToFloat = [](int hexValue) -> float {
            int sign = (hexValue & 0x80) ? -1 : 1;          // Sign bit (1 for negative)
            int exponent = ((hexValue >> 4) & 0x07) - 4;    // Exponent bits (SSS) adjusted by -4
            float mantissa = (hexValue & 0x0F) / 16.0f;     // Mantissa bits (MMMM) scaled
            return sign * pow(2, exponent) * mantissa;
        };

        float num1 = hexToFloat(S);
        float num2 = hexToFloat(T);
        float sum = num1 + num2;

       
        int result = 0;
        if (sum < 0) {
            result |= 0x80;  
            sum = -sum;      
        }

        int exponent = static_cast<int>(log2(sum));
        exponent += 4;  

        if (exponent < 0 || exponent > 7) {
            throw overflow_error("Exponent out of range for encoding.");
        }

        result |= (exponent << 4) & 0x70;  
        float mantissa = sum / pow(2, exponent - 4);
        mantissa -= 1.0f;
        result |= static_cast<int>(mantissa * 16) & 0x0F; 

        registerFile.setCell(R, decToHex(result));
    }
};
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

int main() {
    Register reg;
    ALU alu(reg);

    reg.setCell(0, "4E");
    reg.setCell(1, "A3");

    alu.addRegistersFloat("0", "1", "2"); 
    cout << "Result in register 2: " << reg.getCell(2) << endl;

    return 0;
}
