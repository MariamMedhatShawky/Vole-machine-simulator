#include <iostream>
#include <string>
#include <array>
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
        if (address < 0 || address >= size) {  // Corrected range check
            cout << "Out of bounds. " << endl;
            return "00";  // Return a default value for out of bounds
        } else {
            return memory[address];
        }
    }

    void setcell(int address, const string &value) {
        // Validate hex input
        bool flag = true;
        for (char c : value) {
            if (!isxdigit(c)) {  // Check if character is not a valid hex digit
                flag = false;
                break;
            }
        }

        if (!flag) {
            cout << "Invalid hex input." << endl;
            return;
        }

        // Handle valid input
        if (value.length() > 2) {
            // Process longer values in pairs
            for (size_t i = 0; i < value.length(); i += 2) {
                if (i + 1 < value.length()) {
                    string pair = value.substr(i, 2);
                    if (address >= 0 && address < size) {
                        memory[address++] = pair;  // Store the pair as a string
                    } else {
                        cout << "Out of bounds for address." << endl;
                        return;
                    }
                }
            }
            // Handle any remaining single character
            if (value.length() % 2 != 0 && address < size) {
                string remaining(1, value.back());
                memory[address++] = remaining;  // Store remaining character as a string
            }
        } else if (value.size() == 2) {
            // Store valid two-character hex value
            if (address >= 0 && address < size) {
                memory[address] = value;  // Store as string
            } else {
                cout << "Address out of bounds." << endl;
            }
        }
    }
};

int main() {
    Register reg;
    reg.setcell(0, "AA");  
    cout << reg.getcell(0) << endl;  
    reg.setcell(5, "1F");  
    cout << reg.getcell(5) << endl;  

    reg.setcell(10, "2AB4");  
    cout  << reg.getcell(10) << endl;  
    cout  << reg.getcell(11) << endl;  

    reg.setcell(15, "ZZ");  
    cout << reg.getcell(15) << endl;  

    return 0;
}
