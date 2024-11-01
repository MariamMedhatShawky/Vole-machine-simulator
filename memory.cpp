# include <iostream>
# include <string>
#include <array>
#include <cctype>


using namespace std;
class memory{
    public:
    static const int size = 256;
    array <string,size> mem;
    bool flag = true;

    memory()
    {
    for (int i = 0; i < size; i++){
        mem[i] = "xy";
    }
    }
    
    

    string getcell(int address)
    {
        if (address >= 0 && address < 256){
            return mem[address];
        }
        else{
            cout << "Out of bounds. ";
        } 
    }

/*    bool hexa(const string &value){

        for (int i = 0; i < value.size(); i++){

            if (value [i] > 0 && value [i] < 9 || value [i] == 'A' || value [i]  =='a' ||value [i] =='b'
            || value [i] == 'B'|| value [i] == 'C' || value [i] == 'D' || value [i] == 'c' || value [i] == 'd'
            || value [i] == 'E'|| value [i] == 'F'|| value [i] == 'e'|| value [i] == 'f');{
            return false;
            }

        }

    }
*/

    void setcell (int address, const string& value)
    {
        
        
           for (int i = 0; i < value.size(); i++){

                if (value [i] < 0 && value [i] > 9 || value [i] != 'A' || value [i]  !='a' ||value [i] != 'b'
                || value [i] != 'B'|| value [i] != 'C' || value [i] != 'D' || value [i] != 'c' || value [i] != 'd'
                || value [i] != 'E'|| value [i] != 'F'|| value [i] != 'e'|| value [i] != 'f');
                flag = false;
                break;

            }

        if (value.size() == 2 && !flag ) {

            mem[address] = value; 
        }
        

        if (value.length() > 2) {
                
        for (size_t i = 0; i < value.length(); i += 2) {
            if (i + 1 < value.length()) {
                string pair = value.substr(i, 2);
            }
        }

        if (value.length() % 2 != 0 && address < size) {
            string remaining(1, value.back());  // Last character
            mem[address++] = remaining;
        }
        }
        if (flag){
            cout << "invalid hexa input. "<<endl;
        }

        

    }

    int main(){
        memory m;
        m.setcell(0,"aa");
        cout << m.getcell(0) << endl;
        m.setcell(200,"abc");
        cout << m.getcell(200)<<endl;
        m.setcell(300,"ll");
        cout << m.getcell(300)<<endl;
        m.setcell(100,"2ab4");
        cout << m.getcell(100);
        return 0;

    }

    



};
