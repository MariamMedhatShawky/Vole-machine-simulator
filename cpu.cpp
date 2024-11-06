class CPU
{
private:
    int PC = 0;
    string IR;
    ALU alu;
    CU cu;
    Register regest;
  


public:

    void fetch(Memory& memo)
    {
        string instructionPart1 = memo.getcell(PC);    // Fetch from memory at PC
        string instructionPart2 = memo.getcell(PC + 1); // Fetch from memory at PC + 1

        IR = instructionPart1 + instructionPart2; // Combine the two parts into a single instruction

        // Increment PC by 2 to point to the next instruction pair
        PC += 2;
    }

    void decode(vector <char>& inst)
    {
        inst[0] = IR[0];
        inst[1] = IR[1];
        inst[2] = IR[2];
        inst[3] = IR[3];


    }

    void execute(Register& regest, Memory& memo, vector<char>instruction)
    {
        char opcode = instruction[0];
        int reg = instruction[1] - '0';
      
        char operand1 = instruction[2];
        char operand2 = instruction[3];
        string operand = string(1, operand1) + operand2;

        if (opcode == '1')
        {
            alu.hexToDec(operand);
            cu.load1(reg, alu.hexToDec(operand),regest,memo);
        }

        else if (opcode == '2')
        {
            cu.load2(reg, alu.hexToDec(operand), regest);
        }
        else if (opcode == '3')
        {
            cu.store(reg, alu.hexToDec(operand), regest, memo);
        
        }
        else if (opcode == '4')
        {
            /*char hexChar = 'A';
    int decimalValue = std::stoi(std::string(1, hexChar), nullptr, 16);*/
            int reg_r = stoi(string(1, operand1), nullptr, 16);
            int reg_s = stoi(string(1, operand2), nullptr, 16);
          
            cu.move(reg_r, reg_s, regest);
            
        }
        else if (opcode == '5')
        {
            int s = operand1 - '0';
            int t = operand2 - '0';
            // add content in register s , t and put the result in reg r
            alu.add(s, t, reg);
        }
        else if (opcode == '6')
        {

            string r = to_string(reg);
            string s = string(1, operand1);
            string t = string(1, operand2);
            alu.addRegistersFloat(r, s, t);
        }
        else if (opcode == 'B')
        {
            cu.jump(reg, alu.hexToDec(operand),regest,PC);
        }
        else if (opcode == 'C')
        {
            cu.halt();
        }
    }

    void run_nextStep(Memory& memo , Register& regist)
    {
        fetch(memo); // Load the next instruction into ir

        vector<char>instructionData(2);  // Vector to store opcode and operand
        decode(instructionData);  // Decode the instruction in ir

        execute(regist, memo, instructionData);
    }
};
