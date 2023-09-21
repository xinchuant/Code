if (code[line][0] == '0')
{
    if (code[line][1] == '0')
    {
        if (code[line][2] == '0')
        {
            if (code[line][3] == '0')
                BR(code[line], &line);
            else
                ADD(code[line]);
        }
        else
        {
            if (code[line][3] == '0')
            {
                LD(code[line], code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)], line);
            }
            else // ST OK
            {
                int SR = recon_Register(code[line], 4, 6);
                unsigned short r = R[SR];
                short offset9 = signed_binary_to_decimal(code[line], 7, 15);
                for (int i = 15; i > -1; i--)
                {
                    if (r % 2 == 1)
                        code[line + 1 + offset9][i] = '1';
                    else
                        code[line + 1 + offset9][i] = '0';
                    r = r / 2;
                }
                condition_code = set_condition_code_string(code[line + 1 + signed_binary_to_decimal(code[line], 7, 15)]);
            }
        }
    }
    else
    {
        if (code[line][2] == '0')
        {
            if (code[line][3] == '0')
                JSR(code[line], &line, start_address);
            else
                AND(code[line]);
        }
        else
        {
            if (code[line][3] == '0') // LDR OK
            {
                int DR = recon_Register(code[line], 4, 6);
                int BaseR = recon_Register(code[line], 7, 9);
                short offset6 = signed_binary_to_decimal(code[line], 10, 15);
                R[DR] = unsigned_binary_to_decimal(code[R[BaseR] + offset6 - start_address], 0, 15);
                condition_code = set_condition_code_num(DR);
            }
            else // STR 注意地址与start address以及line的关系
            {
                int SR = recon_Register(code[line], 4, 6);
                int BaseR = recon_Register(code[line], 7, 9);
                short offset6 = signed_binary_to_decimal(code[line], 10, 15);
                unsigned short address = offset6 + R[BaseR];
                unsigned short r = R[SR];
                for (int i = 15; i > -1; i--)
                {
                    if (r % 2 == 1)
                        code[address - start_address][i] = '1';
                    else
                        code[address - start_address][i] = '0';
                    r = r / 2;
                }
                condition_code = set_condition_code_string(code[address - start_address]);
            }
        }
    }
}
else
{
    if (code[line][1] == '0')
    {
        if (code[line][2] == '0')
            NOT(code[line]);
        else
        {
            if (code[line][3] == '0') // LDI OK
            {
                int DR = recon_Register(code[line], 4, 6);
                short offset9 = signed_binary_to_decimal(code[line], 7, 15);
                unsigned short address = line + 1 + offset9;
                R[DR] = unsigned_binary_to_decimal(code[unsigned_binary_to_decimal(code[address], 0, 15) - start_address], 0, 15);
                condition_code = set_condition_code_num(DR);
            }
            else // STI
            {
                int SR = recon_Register(code[line], 4, 6);
                short offset9 = signed_binary_to_decimal(code[line], 7, 15);
                unsigned short address = line + 1 + offset9;
                unsigned short r = R[SR];
                for (int i = 15; i > -1; i--)
                {
                    if (r % 2 == 1)
                        code[unsigned_binary_to_decimal(code[address], 0, 15) - start_address][i] = '1';
                    else
                        code[unsigned_binary_to_decimal(code[address], 0, 15) - start_address][i] = '0';
                    r = r / 2;
                }
                condition_code = set_condition_code_string(code[unsigned_binary_to_decimal(code[address], 0, 15) - start_address]);
            }
        }
    }
    else
    {
        if (code[line][2] == '0')
            JMP(code[line], &line, start_address);
        else
        {
            if (code[line][3] == '0')
                LEA(code[line], line, start_address);
            else
                TRAP_HALT_ONLY();
        }
    }
}
}