#include "myUI.h"

char input[100][1024];
char output[100][1024];
int num_in, num_out;

char * ui_s10_To_S16(int x) {
    int mod;
    char * str = (char * ) malloc(sizeof(char) * 5);
    if (((x >> 14) & 0x1) == 0) str[0] = '+';
    else if (((x >> 13) & 0x1) == 0) {
        str[0] = ' ';
        x &= ~(1 << 14);
    } else {
        str[0] = '-';
        x &= ~(1 << 14);
        x &= ~(1 << 13);
    }
    for (int i = 4; i > 0; i--) {
        mod = x % 16;
        if (mod < 10) str[i] = '0' + mod;
        else str[i] = 'A' + mod - 10;
        x /= 16;
    }
    return str;
}

int ui_CreateBigChar(long int Big[], int num) {
    Big[0] = BigChars[num][0];
    Big[1] = BigChars[num][1];
    return 0;
}

int ui_input(int operand) {
    mt_gotoXY(1, 26);
    printf("> ");
    long int value;
    scanf("%li", & value);
    if (value > 0x1FFF || value < -0x1FFF) return -1;
    char * str;
    sprintf(str, "%li", value);
    strcpy(input[num_in], str);
    num_in++;
    if (value < 0) {
        value *= -1;
        value += 0x2000;
    }
    value += 0x4000;
    sc_memorySet(operand, (int) value);
    return 0;
}

int ui_output(int operand) {
    int value;
    sc_memoryGet(operand, & value);
    mt_gotoXY(1, 26);
    printf("< ");
    value -= 0x4000;
    if (value >= 0x2000) {
        value -= 0x2000;
        value *= -1;
    }
    char * str;
    sprintf(str, "%li", value);
    strcpy(output[num_out], str);
    printf("< ");
    ui_messageOut(output[num_out]);
    num_out++;
    return 0;
}

int ui_s16_To_S10(char * str, int * value) {
    * value = 0;
    if (!(str[0] == '+' || str[0] == '-')) {
        if (strlen(str) != 5) {
            ui_messageOut((char * )(str + 5));
            return -1;
        }
        for (int i = 5; i > 0; i--) {
            str[i] = str[i - 1];
        }
        str[0] = ' ';
    }
    if (strlen(str) != 6) {
        return -1;
    }
    for (int i = 4; i > 0; i--) {
        if (str[5 - i] >= 'A' && str[5 - i] <= 'F') * value += (str[5 - i] - 'A' + 10) << ((i - 1) * 4);
        else if (str[5 - i] >= '0' && str[5 - i] <= '9') * value += (str[5 - i] - '0') << ((i - 1) * 4);
        else return -1;
    }
    if (str[0] != '+') * value |= 1 << 14;
    if (str[0] == '-') * value |= 1 << 13;
    return 0;
}

int ui_print_number(int address) {
    int value;
    char * str;
    mt_gotoXY(2 + (address % 10) * 6, 2 + (address / 10));
    sc_memoryGet(address, & value);
    str = ui_s10_To_S16(value);
    for (int j = 0; j < 5; j++) {
        printf("%c", str[j]);
    }
    return 0;
}

int ui_print_memory() {
    int value;
    char * str;
    for (int i = 0; i < 100; i++) ui_print_number(i);
    mt_gotoXY(2 + (Memory_Position % 10) * 6, 2 + (Memory_Position / 10));
    sc_memoryGet(Memory_Position, & value);
    str = ui_s10_To_S16(value);
    mt_setbgcolor(YELLOW);
    for (int j = 0; j < 5; j++) {
        printf("%c", str[j]);
    }
    mt_setbgcolor(DEFAULT);
    return 0;
}

int ui_print_accumulator() {
    mt_gotoXY(71, 2);
    char * str;
    str = ui_s10_To_S16(sc_accumulator);
    for (int j = 0; j < 5; j++) {
        printf("%c", str[j]);
    }
    return 0;
}

int ui_print_instructionCounter() {
    mt_gotoXY(71, 5);
    printf("%04X", sc_instructionCounter);
}

int ui_print_operation() {
    int value;
    mt_gotoXY(68, 8);
    int command = -1, operand;
    sc_memoryGet(Memory_Position, & value);
    sc_commandDecode(value, & command, & operand);
    if (command != -1) printf("%04X:%04X", command, operand);
    return 0;
}

int ui_print_flags() {
    int value;
    for (int i = 1; i <= 5; i++) {
        if (sc_regGet(i, & value)) return -1;
        mt_gotoXY(68 + (i * 2), 11);
        if (value) printf("%c", fl[i - 1]);
        else printf(" ");
    }
}

int ui_set_accumulator() {
    int value;
    sc_memoryGet(Memory_Position, & value);
    sc_accumulator = value & (~(1 << 14));
    return 0;
}

int ui_terminal_init() {
    Flags = 0;
    Memory_Position = 0;
    sc_instructionCounter = 0;
    if (rk_mytermsave()) return -1;
    sc_memoryInit();
    sc_regInit();
    return 0;
}

int ui_print_bigNumber() {
    long int Big[10];
    int temp, mod;
    sc_memoryGet(Memory_Position, & temp);
    if (temp >= 0) ui_CreateBigChar(Big, 16);
    else ui_CreateBigChar(Big, 17);
    for (int i = 4; i > 0; i--) {
        mod = temp % 16;
        ui_CreateBigChar((Big + i * 2), mod);
        temp /= 16;
    }
    for (int i = 0; i < 5; i++) bc_printbigchar((Big + 2 * i), 2 + i * 9, 14, DEFAULT, YELLOW);
    return 0;
}

void ui_SetMemoryPosition(int ind) {
    Memory_Position = ind;
    sc_instructionCounter = Memory_Position;
}

int ui_terminal_update() {
    mt_clrscr();
    bc_box(1, 1, 61, 12);
    ui_print_memory();
    mt_gotoXY(29, 1);
    printf(" Memory ");
    bc_box(62, 1, 83, 3);
    bc_box(62, 4, 83, 6);
    bc_box(62, 7, 83, 9);
    bc_box(62, 10, 83, 12);
    mt_gotoXY(66, 1);
    printf(" accumulator ");
    ui_print_accumulator();
    mt_gotoXY(63, 4);
    printf(" instructionCounter ");
    ui_print_instructionCounter();
    mt_gotoXY(68, 7);
    printf(" Operation ");
    ui_print_operation();
    mt_gotoXY(68, 10);
    printf(" Flags ");
    ui_print_flags();
    bc_box(1, 13, 46, 22);
    bc_box(47, 13, 83, 22);
    mt_gotoXY(48, 13);
    printf(" Keys: ");
    mt_gotoXY(48, 14);
    printf("l  - load");
    mt_gotoXY(48, 15);
    printf("s  - save");
    mt_gotoXY(48, 16);
    printf("r  - run");
    mt_gotoXY(48, 17);
    printf("t  - step");
    mt_gotoXY(48, 18);
    printf("i  - reset");
    mt_gotoXY(48, 19);
    printf("F5 - accumulator");
    mt_gotoXY(48, 20);
    printf("F6 - instructionCounter");
    ui_print_bigNumber();
    mt_gotoXY(1, 23);
    printf("Input/Output\n>");
    for (int i = 0; i < num_in; i++) printf("%s ", input[i]);
    printf("\n<");
    for (int i = 0; i < num_out; i++) printf("%s ", output[i]);
    mt_gotoXY(1, 26);
    return 0;
}

int ui_Change_Memory_Position(enum keys key, int flag) {
    if (flag == 1) {
        if (key == key_up) {
            if (Memory_Position < 10) Memory_Position += 90;
            else Memory_Position -= 10;
            return 0;
        }
        if (key == key_down) {
            if (Memory_Position >= 90) Memory_Position -= 90;
            else Memory_Position += 10;
            return 0;
        }
        if (key == key_left) {
            if ((Memory_Position % 10) == 0) Memory_Position += 9;
            else Memory_Position--;
            return 0;
        }
        if (key == key_right) {
            if ((Memory_Position % 10) == 9) Memory_Position -= 9;
            else Memory_Position++;
            return 0;
        }
    }
    return -1;
}

int ui_set_memory_value() {
    int value;
    char buffer[10];
    printf("Set the value of the cell under the number \n");
    printf("Enter value in HEX format > ");
    fgets(buffer, 10, stdin);
    printf("%s", buffer);
    if (buffer[strlen(buffer) - 1] != '\n') ui_clearBuffIn(); // очистка потока ввода
    if (ui_s16_To_S10(buffer, & value) == -1) {
        ui_messageOut((char * )
            "Invalid input");
        return -1;
    }
    if (value > 0x7FFF) {
        ui_messageOut((char * )
            "Number should be lesser than 0x7FFF");
        return -1;
    }
    if (value < -0x3FFF) {
        ui_messageOut((char * )
            "Number should be bigger than 0x3FFF");
        return -1;
    }
    sc_memorySet(Memory_Position, value);
    return 0;
}

int ui_set_instructionCounter(int * value) {
    int value2;
    char buffer[10];
    printf("Set a value InstructionCounter between 0x0000 and 0x0063 inclusive\n");
    printf("Enter value in HEX format > ");
    fgets(buffer, 10, stdin);
    if (ui_s16_To_S10(buffer, & value2) == -1) {
        ui_messageOut((char * )
            "Invalid input");
        return -1;
    }
    if (value2 >= 100 || value2 < 0) {
        ui_messageOut((char * )
            "Number should be lesser than 0x0063 and more then 0x0000");
        return -1;
    }
    sc_instructionCounter = value2;
    Memory_Position = sc_instructionCounter;
    * value = sc_instructionCounter;
    return 0;
}

int ui_set_MemoryPosition() {
    int value;
    char buffer[10];
    printf("Set a value InstructionCounter between 0x0000 and 0x0063 inclusive\n");
    printf("Enter value in HEX format > ");
    fgets(buffer, 10, stdin);
    if (ui_s16_To_S10(buffer, & value) == -1) {
        ui_messageOut((char * )
            "Invalid input");
        return -1;
    }
    if (value >= 100 || value < 0) {
        ui_messageOut((char * )
            "Number should be lesser than 0x0063 and more then 0x0000");
        return -1;
    }
    Memory_Position = value;
    return 0;
}

/*int ui_run(int step)
{
    enum keys key_ex;
    struct itimerval nval, oval;
    nval.it_interval.tv_sec = 2;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = 0;
    nval.it_value.tv_usec = 0;

    if(!rk_readkey(&key_ex))
    {    
        ui_terminal_update() ;
        Memory_Position += step ;
        if (Memory_Position >= 100)
        {
            Memory_Position = 0 ;
        }
        sc_instructionCounter=Memory_Position;
        //alarm(1);
        setitimer(ITIMER_REAL, &nval, &oval);
    }
    return 0;
}*/

int ui_pause(int time) {
    fflush(stdout); // очистка потока вывода
    char buffer[5] = "\0";
    rk_mytermregime(0, time, 0, 0, 0);
    read(fileno(stdin), buffer, 5);
    rk_mytermrestore();
    return 0;
}

int ui_messageOut(char * str) {
    printf("%s", str);
    ui_pause(25);
    return 0;
}

int ui_clearBuffIn() {
    int ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != '\0');
    return 0;
}

int ui_saveMemory() {
    char filename[102];
    printf("Saving file...\n");
    printf("Enter the file name to save > ");
    mt_setfgcolor(GREEN);
    fgets(filename, 102, stdin);
    mt_setfgcolor(DEFAULT);
    if (filename[strlen(filename) - 1] != '\n') {
        printf("The file name is too long. The length is trimmed to the first 100 characters.\n");
        ui_clearBuffIn();
    } else filename[strlen(filename) - 1] = '\0';

    if (sc_memorySave(filename)) {
        ui_messageOut((char * )
            "Failed to save memory");
        return -1;
    } else
        ui_messageOut((char * )
            "Successful save");
    return 0;
}

int ui_loadMemory() {
    char filename[102];
    printf("Loading file...\n");
    printf("Enter the file name to load > ");
    mt_setfgcolor(GREEN);
    fgets(filename, 102, stdin);
    mt_setfgcolor(DEFAULT);
    if (filename[strlen(filename) - 1] != '\n') {
        ui_messageOut((char * )
            "The name of the file to open is too long (up to 100 characters are allowed)");
        ui_clearBuffIn(); // очистка потока ввода
        return -1;
    }
    filename[strlen(filename) - 1] = '\0';
    if (sc_memoryLoad(filename)) {
        ui_messageOut((char * )
            "Failed to load memory");
        return -1;
    } else {
        ui_messageOut((char * )
            "Successful load");
        ui_restart();
    }

    return 0;
}

int main_setICounter() {
    sc_regSet(TactIgnore, 1);
    sc_instructionCounter = 0;
    return 0;
}

int ui_restart() {
    sc_regInit();
    sc_instructionCounter = 0;
    Memory_Position = 0;
    for (int i = 0; i < 100; i++) {
        strcpy(input[i], "");
        strcpy(output[i], "");
    }
    num_in = 0;
    num_out = 0;
    return 0;
}

int signalRun(int * value) {
    Memory_Position = sc_instructionCounter;
    ui_terminal_update();
    int command = 0, operand = 0;
    int val;
    sc_memoryGet(sc_instructionCounter, & val);
    int res = sc_commandDecode(val, & command, & operand);
    if (res == -1) {
        sc_regSet(ErrorCommand, 1);
        sc_regSet(TactIgnore, 1);
        return -1;
    } else if (res == 0) {
        if (operand >= 100) {
            printf("Wrond address of memory");
            sc_regSet(MemoryOut, 1);
            return -1;
        }
        if (command == ADD || command == SUB || command == DIVIDE || command == MUL || command == LOGRC) {
            if (ALU(command, operand) == -1) {
                printf("ERROR\n");
                return -1;
            }
            sc_instructionCounter++;
            * value = sc_instructionCounter;
            return 0;
        }
        int value;
        switch (command) {
        case READ:
            if (ui_input(operand) != 0) {
                printf("Wrong value for memory\n");
                sc_regSet(OverFlow, 1);
                return -1;
            }
            sc_instructionCounter++;
            break;
        case WRITE:
            ui_output(operand);
            sc_instructionCounter++;
            break;
        case LOAD:
            sc_memoryGet(operand, & sc_accumulator);
            sc_instructionCounter++;
            break;
        case STORE:
            sc_memorySet(operand, sc_accumulator);
            sc_instructionCounter++;
            break;
        case JUMP:
            ui_SetMemoryPosition(operand);
            break;
        case JNEG:
            if (((sc_accumulator >> 13) & 0x1) == 1) ui_SetMemoryPosition(operand);
            else sc_instructionCounter++;
            break;
        case JZ:
            if (sc_accumulator == 0) ui_SetMemoryPosition(operand);
            else sc_instructionCounter++;
            break;
        case HALT:
            sc_regSet(TactIgnore, 1);
            return -1;
        default:
            sc_instructionCounter++;
            break;
        }
    } else sc_instructionCounter++;
    * value = sc_instructionCounter;
    return 0;
}

int ALU(int command, int operand) {
    int value;
    sc_memoryGet(operand, & value);
    if (((value >> 14) & 0x1) && ((sc_accumulator >> 14) & 0x1)) {
        value &= ~(1 << 14);
        if (((value >> 13) & 0x1) == 1) {
            value &= ~(1 << 13);
            value *= -1;
        }
        sc_accumulator &= ~(1 << 14);
        if (((sc_accumulator >> 13) & 0x1) == 1) {
            sc_accumulator &= ~(1 << 13);
            sc_accumulator *= -1;
        }
        switch (command) {
        case ADD:
            sc_accumulator += value;
            if (sc_accumulator > 0x1FFF || sc_accumulator < -0x1FFF) {
                printf("Modul of Sum of two numbers is too big\n");
                sc_regSet(OverFlow, 1);
                return -1;
            }
            break;
        case SUB:
            sc_accumulator -= value;
            break;
        case DIVIDE:
            if (value == 0) {
                printf("Divide by zero!!!\n");
                sc_regSet(ZeroDivision, 1);
                return -1;
            }
            sc_accumulator /= value;
            break;
        case MUL:
            sc_accumulator *= value;
            if (sc_accumulator > 0x1FFF || sc_accumulator < -0x1FFF) {
                printf("Modul of Mul of two numbers is too big\n");
                sc_regSet(OverFlow, 1);
                return -1;
            }
            break;
        case LOGRC:
            if (value < 0) {
                value *= -1;
                sc_accumulator--;
            }
            for (int i = 0; i < sc_accumulator; i++) {
                value /= 2;
            }
            sc_accumulator = value;
            break;
        }
        if (sc_accumulator < 0) {
            sc_accumulator *= -1;
            sc_accumulator += 0x2000;
        }
        sc_accumulator += 0x4000;
    } else {
        ui_messageOut("Incorrect numbers\n");
        return -1;
    }
    return 0;
}
