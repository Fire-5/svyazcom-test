// Git ne podderjivaet kirillicu, commentarii dubliruyi

#include "stdc++.h"
using namespace std;
class MathString {
public:
    string Stroka_vvoda;
    double resultat;

    double Podschet(string s) {
        Stroka_vvoda = s;
        Stroka_vvoda = DelProbel();
        Stroka_stack = StackCreate();
        resultat = Schetaem();

        return resultat;
    }
private:
    double a = 0, b = 0;
    stack<double> st;
    string Stroka_stack;

    string DelProbel() {
        int pos = Stroka_vvoda.find(' ', 0);
        while (pos != -1) {
            //cout << " - pos - " << pos << endl;
            Stroka_vvoda.erase(pos, 1);
            pos = Stroka_vvoda.find(' ', 0);
            //cout << " - pos new - " << pos << endl;
        }
        cout << " - ������ ����� �������� ���������: " << Stroka_vvoda << endl;
        return Stroka_vvoda;
    }

    int Prioritet(char ch) {
        if (ch == '*' || ch == '/') return 2;
        else if (ch == '+' || ch == '-') return 1;
        else return -1;
    }

    string StackCreate() {
        stack<char> StackCh;
        string res;
        Stroka_vvoda += " ";
        int len = Stroka_vvoda.size();
        for (int i = 0; i < len; i++) {
            if (isdigit(Stroka_vvoda[i]) || Stroka_vvoda[i] == '.') {   // isdigit(char ch) - �������� ch �������� �� ������ �� 0 �� 9
                res += Stroka_vvoda[i];
                // cout << " -- " << res << endl;
            }
            else if (Stroka_vvoda[i] == '(') {
                StackCh.push('(');
                // cout << " -- " << res << endl;
            }
            else if (Stroka_vvoda[i] == ')') {
                res += " ";
                while (!StackCh.empty() && StackCh.top() != '(') {
                    char ch = StackCh.top();
                    StackCh.pop();
                    res += ch;
                    if (ch == '*' || ch == '/') res += " ";
                    // cout << " -- " << res << endl;
                }
                if (StackCh.top() == '(') {
                    char ch = StackCh.top();
                    StackCh.pop();
                    // cout << " -- " << res << endl;
                }
            }
            else {
                res += " ";
                while (!StackCh.empty() && Prioritet(Stroka_vvoda[i]) <= Prioritet(StackCh.top())) {
                    char ch = StackCh.top();
                    StackCh.pop();
                    res += ch;
                    res += " ";
                    //cout << " -- " << res << endl;
                }
                StackCh.push(Stroka_vvoda[i]);
                // cout << " -- " << res << endl;
            }
        }
        while (!StackCh.empty()) {
            char ch = StackCh.top();
            StackCh.pop();
            res += ch;
        }
        cout << " - ���������� �����: " << res << endl;
        return res;
    }

    double Schetaem() {
        stringstream str(Stroka_vvoda);
        string sign;
        while (str >> sign) {
            if (!(sign == "-" || sign == "+" || sign == "*" || sign == "/"))
                st.push(atof(sign.c_str())); // �� �� ����� ������� ��� �����...
            else {
                if (!st.empty()) {
                    b = st.top();
                    st.pop();
                }
                if (!st.empty()) {
                    a = st.top();
                    st.pop();
                }
                switch (sign[0]) {
                case '+':
                    st.push(a + b);
                    cout << " --> " << a << "+" << b;
                    break;
                case '-':
                    st.push(a - b);
                    cout << " --> " << a << "-" << b;
                    break;
                case '*':
                    st.push(a * b);
                    cout << " --> " << a << "*" << b;
                    break;
                case '/':
                    st.push(a / b);
                    cout << " --> " << a << "/" << b;
                    break;
                }
                cout << " = " << st.top() << endl;
            }
        }
        if (!st.empty()) {
            double ch = st.top();
            st.pop();
            if (st.empty()) {
                //cout << " ���������: " << ch << "\n";
                return ch;
            }
        }

    }


};

/*
// ��������� ������ ����� ����������� ��������
// Prioritet znacov cherez vozvraschenie znacheniy
int Prioritet(char ch) {
    if (ch == '*' || ch == '/') return 2;
    else if (ch == '+' || ch == '-') return 1;
    else return -1;
}

// �������� ����� ������������������ ����������
// Sozdanie stack-posledovatelnosti vyichislenia
// - push � �������� ������� � ����;
// - pop   � ������� ������� �� �����;
// - peek � ����������� �������� �����;
string StackCreate(string& s) {
    stack<char> StackCh;
    string res;
    s += " ";
    int len = s.size();
    for (int i = 0; i < len; i++) {
        if (isdigit(s[i]) || s[i] == '.') {   // isdigit(char ch) - �������� ch �������� �� ������ �� 0 �� 9
            res += s[i];
            // cout << " -- " << res << endl;
        }
        else if (s[i] == '(') {
            StackCh.push('(');
            // cout << " -- " << res << endl;
        }
        else if (s[i] == ')') {
            res += " ";
            while (!StackCh.empty() && StackCh.top() != '(') {
                char ch = StackCh.top();
                StackCh.pop();
                res += ch;
                if (ch == '*' || ch == '/') res += " ";
                // cout << " -- " << res << endl;
            }
            if (StackCh.top() == '(') {
                char ch = StackCh.top();
                StackCh.pop();
                // cout << " -- " << res << endl;
            }
        }
        else {
            res += " ";
            while (!StackCh.empty() && Prioritet(s[i]) <= Prioritet(StackCh.top())) {
                char ch = StackCh.top();
                StackCh.pop();
                res += ch;
                res += " ";
                //cout << " -- " << res << endl;
            }
            StackCh.push(s[i]);
            // cout << " -- " << res << endl;
        }
    }
    while (!StackCh.empty()) {
        char ch = StackCh.top();
        StackCh.pop();
        res += ch;
    }
    cout << " - ���������� �����: " << res << endl;
    return res;
}

double Schet(string s, stack<double> st, double a,  double b) {
    stringstream str(s);
    string sign;
    while (str >> sign) {
        if (!(sign == "-" || sign == "+" || sign == "*" || sign == "/"))
            st.push(atof(sign.c_str())); // �� �� ����� ������� ��� �����...
        else {
            if (!st.empty()) {
                b = st.top();
                st.pop();
            }
            if (!st.empty()) {
                a = st.top();
                st.pop();
            }
            switch (sign[0]) {
            case '+':
                st.push(a + b);
                cout << " --> " << a << "+" << b;
                break;
            case '-':
                st.push(a - b);
                cout << " --> " << a << "-" << b;
                break;
            case '*':
                st.push(a * b);
                cout << " --> " << a << "*" << b;
                break;
            case '/':
                st.push(a / b);
                cout << " --> " << a << "/" << b;
                break;
            }
            cout << " = " << st.top() << endl;
        }
    }
    if (!st.empty()) {
        double ch = st.top();
        st.pop();
        if (st.empty()) {
            //cout << " ���������: " << ch << "\n";
            return ch;
        }
    }

}

// ������� ������� � ������. � ���� ������ � ���������, � �� ���� ������ ����� ������ ������ ��� ���
// Udalenie probelow v stroke. Ya pishu primer s probelami, a na vhod stack nujno davat stroku bez nih
string DelProbel (string s) {
    int pos = s.find(' ', 0);
    while (pos != -1) {
        //cout << " - pos - " << pos << endl;
        s.erase(pos, 1);
        pos = s.find(' ', 0);
        //cout << " - pos new - " << pos << endl;
    }
    cout << " - ������ ����� �������� ���������: " << s << endl;
    return s;
}
*/


int main() {
    /*
    // ����� ������� (������)...
        setlocale(LC_ALL, "Russian");
    double a = 0, b = 0;
    stack<double> st;
    string s;

    cout << " ������� ��� ������: ";
    getline(cin, s);

    s = DelProbel(s);
    s = StackCreate(s);
   
    double res = Schet(s, st, a, b);
    cout << " ���������: " << res << "\n";

    system("pause");
    */

    // ---------------------------------------
    // ����� �����.

    setlocale(LC_ALL, "Russian");
    string s;

    MathString Stroka;
    cout << " ������� ��� ������: ";
    getline(cin, s);
    Stroka.Podschet(s);
    cout << " ���������: " << Stroka.resultat << "\n";

    return 0;
}