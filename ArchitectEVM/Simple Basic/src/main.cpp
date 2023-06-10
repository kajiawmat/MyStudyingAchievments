#include<cstdio>
#include<cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cstring>
#include <iomanip>

using namespace std;

struct SimpleAssembler {
    string command = "";
    int operand;
};

struct SimpleBasic {
    string lb = "";
    int pos;
};
SimpleAssembler Memory[100];
int counterStart = 0, counterEnd = 99, tagCounter = 0, constCounter = 0, last = 0;
SimpleBasic Labels[100];
SimpleBasic ConstVars[100];
int Name_Address[26] = {
    0
};

int Prioritet(char c) {
    if (c < 0) return 4;
    switch (c) {
    case '(':
        return 1;
    case '-':
        return 2;
    case '+':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    }
    return -1;
}

int VarAddress(char c) {
    if ((c >= 'A') && (c <= 'Z')) {
        if (Name_Address[c - 'A'] < 0) {
            Name_Address[c - 'A'] = counterEnd;
            Memory[counterEnd].operand = 0;
            Memory[counterEnd].command = "=";
            counterEnd--;
        }
        return Name_Address[c - 'A'];
    } else
        return -1;
}

void SetMemory(string command, int operand) {
    Memory[counterStart].command = command;
    Memory[counterStart].operand = operand;
    counterStart++;
}

int ConstAddress(string s) {
    int a;
    try {
        a = stoi(s);
    } catch (const exception & e) {
        e.what();
        cout << "WRONG CONST 1" << s;
        exit(1);
    }
    for (int i = 0; i < constCounter; i++) {
        if (ConstVars[i].lb == s) {
            return ConstVars[i].pos;
        }
    }
    if (abs(a) > 0x1FFF) {
        cout << "WRONG CONST 2" << s;
        exit(1);
    }
    ConstVars[constCounter].lb = s;
    ConstVars[constCounter].pos = counterEnd;
    if (a < 0) a = abs(a) + (1 << 13);
    Memory[counterEnd].operand = a;
    Memory[counterEnd].command = "=";
    counterEnd--;
    constCounter++;
    return counterEnd + 1;
}

void RPN_to_SA(string in , char c) {
    int depth = 0;
    string tmp = "";
    string out = "";
    for (unsigned int i = 0; i < in .size(); i++) {
        if (last > counterEnd - depth + 1) {
            cout << "ERROR OVERFLOW MEMORY";
            exit(1);
        } //Check memory for temp operations
        if (( in [i] >= 'A' && in [i] <= 'Z')) {
            SetMemory("LOAD", VarAddress( in [i]));
            SetMemory("STORE", counterEnd - depth);
            depth++;
        } else if ( in [i] == ' ') {
            tmp = "";
            i++;
            while ( in [i] != ' ') {
                tmp += in [i];
                i++;
            }
            SetMemory("LOAD", ConstAddress(tmp));
            SetMemory("STORE", counterEnd - depth);
            depth++;
        } else {
            if ( in [i] < 0) {
                if (depth < 1) {
                    cout << "ERROR NOT ENOUGH OPERAND TO OPERSTION IN LET";
                    exit(1);
                }
                if (- in [i] == '-') {
                    SetMemory("LOAD", ConstAddress("0"));
                    SetMemory("SUB", counterEnd - depth + 1);
                    SetMemory("STORE", counterEnd - depth + 1);
                }
            } else {
                if (depth < 2) {
                    cout << "ERROR NOT ENOUGH OPERAND TO OPERATION IN LET";
                    exit(1);
                }
                int st1 = counterEnd - depth + 1;
                int st2 = st1 + 1;
                SetMemory("LOAD", st2);
                switch ( in [i]) {
                case '+':
                    SetMemory("ADD", st1);
                    break;

                case '-':
                    SetMemory("SUB", st1);
                    break;

                case '/':
                    SetMemory("DIVIDE", st1);
                    break;

                case '*':
                    SetMemory("MUL", st1);
                    break;
                }
                SetMemory("STORE", st2);
                depth--;
            }
        }
    }
    if (depth != 1) {
        cout << "ERROR TOO MANY OPERAND";
        exit(1);
    }
    SetMemory("LOAD", counterEnd);
    SetMemory("STORE", VarAddress(c));
}

int SearchLabel(string str) {
    for (int i = 0; i < tagCounter; i++) {
        if (Labels[i].lb == str) return Labels[i].pos;
    }
    return -1;
}

void SetLabel(string str1) {
    if (SearchLabel(str1) != -1) {
        cout << "ERROR CAN NOT FIND TAG " << str1;
        exit(1);
    }
    if (tagCounter > 0 && (Labels[tagCounter - 1].lb.length() > str1.length() || (Labels[tagCounter - 1].lb.length() == str1.length() && Labels[tagCounter - 1].lb >= str1))) {
        cout << "ERROR WRONG TAG" << Labels[tagCounter - 1].lb << "|" << str1 << "|";
        exit(1);
    }
    Labels[tagCounter].lb = str1;
    Labels[tagCounter].pos = counterStart;
    tagCounter++;
    counterStart++;
}

int RPN(string & out, string in ) {
    int num_open = 0, num_close = 0;
    string opers = "";
    char prev = ' ';
    for (unsigned int i = 0; i < in .length(); i++) {
        if ( in [i] == ' ') continue;
        if ( in [i] == ')') {
            num_close++;
            if (num_open > num_close) {
                cout << "ERROR wrong operation";
                exit(1);
            }
            while (opers.back() != '(') {
                out += opers.back();
                opers.pop_back();
                if (opers.empty()) {
                    cout << "ERROR missing bracket \'(\'";
                    exit(1);
                }
            }
            opers.pop_back();
        }
        if ( in [i] >= 'A' && in [i] <= 'Z') {
            out += in [i];
        }
        if ( in [i] >= '0' && in [i] <= '9') {
            string tmp = "";
            while ( in [i] >= '0' && in [i] <= '9') {
                tmp += in [i];
                i++;
            }
            i--;
            int num;
            try {
                num = stoi(tmp);
            } catch (const exception & e) {
                e.what();
                cout << "Wrong: big number in LET";
                exit(1);
            }
            out += " " + to_string(num) + " ";
        }
        if ( in [i] == '(') {
            opers += "(";
            num_open++;
        }
        if (( in [i] == '+' || in [i] == '-') && (prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '(')) {
            opers.push_back(- in [i]);
        } else if ( in [i] == '/' || in [i] == '*' || in [i] == '+' || in [i] == '-') {
            if (opers.empty()) {
                opers += in [i];
            } else {
                if (Prioritet(opers.back()) < Prioritet( in [i])) {
                    opers += in [i];
                } else {
                    while (!opers.empty() && (Prioritet(opers.back()) >= Prioritet( in [i]))) {
                        out += opers.back();
                        opers.pop_back();
                    }
                    opers += in [i];
                }
            }
        }
        prev = in [i];
    }
    if (num_open != num_close) {
        cout << "ERROR missing bracket";
        exit(1);
    }
    while (!opers.empty()) {
        out += opers.back();
        opers.pop_back();
    }
    return 0;
}

int SB_to_SA(string buf) {
    smatch sm;

    if (regex_search(buf, sm, regex("([0-9]+)\\s+REM"))) {
        return 1;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+LET\\s+([A-Z])\\s+=([A-Z0-9\\-+/*\\(\\) ]*)\\s*\n"))) {
        string rpnstr;
        if (RPN(rpnstr, sm[3].str()) == -1) cout << "ERROR";
        RPN_to_SA(rpnstr, sm[2].str()[0]);
        return 2;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+INPUT\\s+([A-Z])\\s*\n"))) {
        SetMemory("READ", VarAddress(sm[2].str()[0]));
        return 3;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+OUTPUT\\s+([A-Z]\\s*)\n"))) {
        SetMemory("WRITE", VarAddress(sm[2].str()[0]));
        return 4;
    } else if (regex_search(buf, sm, regex("^(([0-9]+)\\s+IF\\s+([-A-Z0-9]+)\\s*([<>=]{1,2})\\s*([-A-Z0-9]+)\\s+GOTO\\s+([0-9]+)\\s*\n)$"))) {
        string s1, s2, s3;
        s1 = sm[3].str();
        s2 = sm[4].str();
        s3 = sm[5].str();
        int st1 = 0, st2 = 0;
        if (s1[0] >= 'A' && s1[0] <= 'Z') {
            if (s1.size() != 1) {
                cout << "ERROR WRONG FIRST ARGUMENT IN IF";
                exit(1);
            }
            st1 = VarAddress(s1[0]);
        } else {
            st1 = ConstAddress(s1);
        }
        if (s3[0] >= 'A' && s3[0] <= 'Z') {
            if (s3.size() != 1) {
                cout << "ERROR WRONG SECOND ARGUMENT IN IF";
                exit(1);
            }
            st2 = VarAddress(s3[0]);
        } else {
            st2 = ConstAddress(s3);
        }
        int d = -1;
        d = SearchLabel(sm[6].str());
        if (d == -1) {
            cout << "ERROR CAN NOT FIND TAG";
            exit(1);
        }
        if (s2 == ">") {
            SetMemory("LOAD", st2);
            SetMemory("SUB", st1);
            SetMemory("JNEG", d);
        } else if (s2 == "<") {
            SetMemory("LOAD", st1);
            SetMemory("SUB", st2);
            SetMemory("JNEG", d);
        } else if (s2 == "=") {
            SetMemory("LOAD", st2);
            SetMemory("SUB", st1);
            SetMemory("JZ", d);
        } else if (s2 == ">=") {
            SetMemory("LOAD", st2);
            SetMemory("SUB", st1);
            SetMemory("JNEG", d);
            SetMemory("JZ", d);
        } else if (s2 == "<=") {
            SetMemory("LOAD", st1);
            SetMemory("SUB", st2);
            SetMemory("JNEG", d);
            SetMemory("JZ", d);
        } else {
            cout << "ERROR";
            exit(1);
        }
        return 5;
    } else if (regex_search(buf, sm, regex("^(([0-9]+)\\s+GOTO\\s+([0-9]+)\n)$"))) {
        int d = -1;
        d = SearchLabel(sm[3].str());
        if (d != -1) {
            SetMemory("JUMP", d);
            return 6;
        }
        return -1;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+END\\s*\n"))) {
        SetMemory("HALT", 0);
        return 7;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+PRINT\\s+([A-Z]\\s*)\n"))) {
        SetMemory("WRITE", VarAddress(sm[2].str()[0]));
        return 4;
    } else return -1;
    return 0;
}

int Check_SB(string buf) {
    smatch sm;
    if (regex_search(buf, sm, regex("([0-9]+)\\s+REM\\s+(.*)\n"))) {
        Labels[tagCounter].lb = sm[1].str();
        Labels[tagCounter].pos = counterStart;
        tagCounter++;
        return 1;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+LET\\s+([A-Z])\\s+=([A-Z0-9\\-+/*\\(\\) ]*)\\s*\n"))) {
        SetLabel(sm[1].str());
        string rpnstr;
        if (RPN(rpnstr, sm[3].str()) == -1) {
            cout << "ERROR WRONG LET  in line " << sm[1].str();
            exit(1);
        }
        //cout << rpnstr << endl;
        for (unsigned int i = 0; i < rpnstr.size(); i++) {
            if (VarAddress(rpnstr[i]) != -1) counterStart += 2;
            if (rpnstr[i] == ' ') {
                string tmp = "";
                i++;
                while (rpnstr[i] != ' ') {
                    tmp += rpnstr[i];
                    i++;
                }
                ConstAddress(tmp);
                counterStart += 2;
            }
            if (rpnstr[i] == '+' || rpnstr[i] == '-' || rpnstr[i] == '/' || rpnstr[i] == '*') counterStart += 3;
            if (rpnstr[i] == -'-') {
                ConstAddress("0");
                counterStart += 3;
            }
        }
        counterStart++;
        return 2;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+INPUT\\s+([A-Z])\\s*\n"))) {
        if (sm[2].str().size() != 1) {
            cout << "ERROR WRONG INPUT_COMMAND in line " << sm[1].str();
            exit(1);
        }
        VarAddress(sm[2].str()[0]);
        SetLabel(sm[1].str());
        return 3;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+OUTPUT\\s+([A-Z]\\s*)\n"))) {
        if (sm[2].str().size() != 1) {
            cout << "ERROR WRONG OUTPUT_COMMAND  in line " << sm[1].str();
            exit(1);
        }
        VarAddress(sm[2].str()[0]);
        SetLabel(sm[1].str());
        return 4;
    } else if (regex_search(buf, sm, regex("^(([0-9]+)\\s+IF\\s+([-A-Z0-9]+)\\s*([<>=]{1,2})\\s*([-A-Z0-9]+)\\s+GOTO\\s+([0-9]+)\\s*\n)$"))) {
        SetLabel(sm[2].str());
        string s1, s2;
        s1 = sm[3].str();
        s2 = sm[5].str();
        if (s1[0] >= 'A' && s1[0] <= 'Z') {
            if (s1.size() != 1) {
                cout << "ERROR WRONG VALUE IN IF in line " << sm[2].str();
                exit(1);
            }
            VarAddress(s1[0]);
        } else {
            ConstAddress(s1);
        }
        if (s2[0] >= 'A' && s2[0] <= 'Z') {
            if (s2.size() != 1) {
                cout << "ERROR WRONG VALUE IN IF in line " << sm[2].str();
                exit(1);
            }
            VarAddress(s2[0]);
        } else {
            ConstAddress(s2);
        }
        if (sm[4].str().size() == 2) counterStart++;
        counterStart += 2;
        return 5;
    } else if (regex_search(buf, sm, regex("^(([0-9]+)\\s+GOTO\\s+([0-9]+)\n)$"))) {
        SetLabel(sm[2].str());
        return 6;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+END\\s*\n"))) {
        SetLabel(sm[1].str());
        return 7;
    } else if (regex_search(buf, sm, regex("([0-9]+)\\s+PRINT\\s+([A-Z]\\s*)\n"))) {
        if (sm[2].str().size() != 1) {
            cout << "ERROR WRONG PRINT_COMMAND";
            exit(1);
        }
        VarAddress(sm[2].str()[0]);
        SetLabel(sm[1].str());
        return 4;
    }
    if (regex_search(buf, sm, regex("\0"))) return 0;
    else return -1;
}

int main(int argc, char * argv[]) {
    bool endflag = 0;
    if (argc != 2) {
        cout << "Start command should looks like ./bin/main <filename>\n";
        return -1;
    }
    string filename = argv[1];
    ifstream in (filename + ".sb");
    ofstream out(filename + ".sa");
    if (! in ) {
        cout << "CANNOT OPEN";
        exit(1);
    } else {
        for (int i = 0; i < 26; i++) {
            Name_Address[i] = -1;
        }
        while (! in .eof()) {
            string buf;
            getline( in , buf);
            buf += "\n";
            int tmp1 = Check_SB(buf);
            if (tmp1 == 7 && endflag) {
                cout << "ERROR MORE ONE END";
                exit(1);
            }
            if (tmp1 == 7) endflag = 1;
            if (tmp1 == 0) break;
            if (tmp1 == -1) {
                cout << "WRONG COMMAND IN LINE" << Labels[tagCounter].lb;
                exit(1);
            }
            if (counterStart > counterEnd + 1) {
                cout << "ERROR OVERFLOW MEMORY";
                exit(1);
            }
        }
        if (!endflag) {
            cout << "ERROR NO END";
            exit(1);
        }
        last = counterStart;
        counterStart = 0; in .clear(); in .seekg(0);
        while (! in .eof()) {
            string buf;
            getline( in , buf);
            buf += "\n";
            SB_to_SA(buf);
        }
    }
    for (int i = 0; i < 100; i++) {
        if (Memory[i].command == "") continue;
        if (Memory[i].command == "=")
            out << setfill('0') << setw(2) << i << " " << Memory[i].command << " " << (((Memory[i].operand & (1 << 13)) > 0) ? '-' : '+') << hex << uppercase << setfill('0') << setw(4) << (Memory[i].operand & 8191) << dec << '\n';
        else
            out << setfill('0') << setw(2) << i << " " << Memory[i].command << " " << setfill('0') << setw(2) << (Memory[i].operand & 8191) << '\n';
    }
    out << '\0';
    out.close(); in .close();
    return 0;
}