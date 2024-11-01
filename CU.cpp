#include <iostream>
#include <string>
#include <array>
#include <cctype>
#include <sstream>

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


class CU{
    public:
    

    void load(int Regp, int Memp, Register& reg, Memory& mem){

        reg.setcell(Regp,mem.getcell(Memp));
        
    }


    void store (int Regp, int Memp, Register & r, Memory &m){
        
        m.setcell(Memp,r.getcell(Regp));
    }

    void move (int Regp1, int Regp2, Register & reg){
        reg.setcell(Regp2, reg.getcell(Regp1));
    }

    
    bool isHalted = false; // Flag to indicate if execution is halted

    void halt() {
        cout << "Execution halted." << endl;
        isHalted = true ;
        return;

    }

    
    void jump(int regIndex, int memAddress, Register& reg, int& PC){
        if (reg.getcell(regIndex) == reg.getcell(0)) {
            PC = memAddress;
        }

        else if (reg.getcell(regIndex) != reg.getcell(0)){
            cout << "No jumb. ";
        }
    }

    void load(int regIndex, int value, Register& reg) {
        // Convert the integer value to a two-character hex string
        stringstream s;
        s << hex << value;
        string hexValue;
        hexValue = s.str();


        // Store this hex string in the specified register
        reg.setcell(regIndex, hexValue);

        
    }


    };


int main() {
    Memory memory;
    Register reg;
    CU cu;

    int PC = 0; 

    
    memory.setcell(10, "1A"); 
    cu.load(2, 10, reg, memory); 
    cout << "Register[2] after load from memory: " << reg.getcell(2) << endl;

    
    cu.load(3, 27, reg);  
    cout << "Register[3] after immediate load: " << reg.getcell(3) << endl;

    
    reg.setcell(5, "4C"); 
    cu.store(5, 15, reg, memory); 
    cout << "Memory[15] after store from register: " << memory.getcell(15) << endl;

    
    reg.setcell(7, "5D"); 
    cu.move(7, 8, reg); 
    cout << "Register[8] after move from Register[7]: " << reg.getcell(8) << endl;

    
    reg.setcell(0, "00"); 
    reg.setcell(4, "00");  
    cu.jump(4, 20, reg, PC); 
    cout << "Program Counter after jump: " << PC << endl;

    
    cu.halt();
    cout << "Execution status (isHalted): " << (cu.isHalted ? "Yes" : "No") << endl;

    return 0;
}


