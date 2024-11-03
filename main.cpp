#include <iostream>
#include <sstream>
#include <stdexcept> // For std::invalid_argument
using namespace std;

// ALU struct
struct ALU {
    // Converts a hex string to a decimal string
    static string hexToDec(const string& hexStr) {
        int decimalValue = stoi(hexStr, nullptr, 16);
        return to_string(decimalValue);
    }

    // Converts a decimal string to a hex string
    static string decToHex(const string& decStr) {
        int decimalValue = stoi(decStr);
        string hexStr;

        while (decimalValue > 0) {
            int remainder = decimalValue % 16;
            hexStr = decToHexChar(remainder) + hexStr;
            decimalValue /= 16;
        }

        return hexStr.empty() ? "0" : hexStr;
    }

    // Helper function to convert a decimal value to a hex character
    static char decToHexChar(int decValue) {
        if (decValue >= 0 && decValue <= 9)
            return '0' + decValue;
        else if (decValue >= 10 && decValue <= 15)
            return 'A' + (decValue - 10);
        return '0';
    }

    // Checks if a string is a valid hexadecimal string
    static bool isValidString(const string& str) {
        for (char c : str) {
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
                return false;
            }
        }
        return true;
    }

    // Adds the contents of two registers and stores the result in a third register
    static void add(int index1, int index2, int index3, int* registers) {
        registers[index3] = registers[index1] + registers[index2];
    }
};

// Main function to test ALU methods
int main() {
    int registers[16] = {0};

    string hexStr = "1A3";
    cout << "Hex to Dec of " << hexStr << " is: " << ALU::hexToDec(hexStr) << endl;

    string decStr = "420"; // Change this to test both even and odd
    cout << "Dec to Hex of " << decStr << " is: " << ALU::decToHex(decStr) << endl;

    string testStr = "1A3";
    cout << "Is \"" << testStr << "\" a valid hex string? " << boolalpha << ALU::isValidString(testStr) << endl;

    registers[1] = 10;
    registers[2] = 15;
    ALU::add(1, 2, 3, registers);
    cout << "Result of adding registers[1] and registers[2] in registers[3]: " << registers[3] << endl;

    return 0;
}
