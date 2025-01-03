#include <iostream>
#include <string>
#include <array>
#include <cctype>

using namespace std;

class Memory {
public:
    static const int size = 256;
    array<string, size> mem;

    Memory() {
        for (int i = 0; i < size; i++) {
            mem[i] = "xy";  // Initialize memory cells to "xy"
        }
    }

    string getcell(int address) {
        if (address < 0 || address >= size) {  // Corrected bounds check
            cout << "Out of bounds. ";
            return "00";  // Return a default value for out of bounds
        } else {
            return mem[address];
        } 
    }

    void setcell(int address, const string& value) {
        bool flag = true;  // Reset flag for each call
        
        // Validate hex input
        for (char c : value) {
            if (!isxdigit(c)) {  // Check if character is not a valid hex digit
                flag = false;
                break;
            }
        }

        // Store valid two-character hex value
        if (value.size() == 2 && flag) {
            if (address >= 0 && address < size) {
                mem[address] = value; 
            } else {
                cout << "Address out of bounds." << endl;
            }
            return;
        }

        // Handle values longer than 2 characters
        if (value.length() > 2) {
            for (size_t i = 0; i < value.length(); i += 2) {
                if (i + 1 < value.length()) {
                    string pair = value.substr(i, 2);
                    if (address >= 0 && address < size) {
                        mem[address++] = pair;  // Store the pair in memory
                    } else {
                        cout << "Out of bounds for address." << endl;
                        return;
                    }
                }
            }
            // Handle any remaining single character
            if (value.length() % 2 != 0 && address < size) {
                string remaining(1, value.back());
                mem[address++] = remaining;  // Store remaining character
            }
        } else if (!flag) {
            cout << "Invalid hex input." << endl;
        }
    }
};

int main() {
    Memory m;
    m.setcell(0, "aa");
    cout << m.getcell(0) << endl;  
    m.setcell(200, "abc");
    cout << m.getcell(200) << endl;  
    cout << m.getcell(201) << endl;  
    m.setcell(150, "bb");
    cout << m.getcell(300) << endl;  
    m.setcell(100, "2ab4");
    cout << m.getcell(100) << endl;  
    cout << m.getcell(101) << endl;  

    return 0;
}
