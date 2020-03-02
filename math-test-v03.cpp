
#include "stdc++.h"
using namespace std;

int prec(char ch) {
    if (ch == '*' || ch == '/') return 2;
    else if (ch == '+' || ch == '-') return 1;
    else return -1;
}

// �������� ����� ������������������ ����������
string infixToPostfix(string& s) {
    stack<char> st;
    string res;
    s += " ";
    int len = s.size();
    for (int i = 0; i < len; i++) {
        if (isdigit(s[i]) || s[i] == '.') {
            res += s[i];
            // cout << " -- " << res << endl;
        }            
        else if (s[i] == '(') {
            st.push('(');
            // cout << " -- " << res << endl;
        }
        else if (s[i] == ')') {
            res += " ";
            while (!st.empty() && st.top() != '(') {
                char ch = st.top();
                st.pop();
                res += ch;
                if (ch == '*' || ch == '/') res += " ";
                // cout << " -- " << res << endl;
            }
            if (st.top() == '(') {
                char ch = st.top();
                st.pop();
                // cout << " -- " << res << endl;
            }
        }
        else {
            res += " ";
            while (!st.empty() && prec(s[i]) <= prec(st.top())) {
                char ch = st.top();
                st.pop();
                res += ch;
                res += " ";
                //cout << " -- " << res << endl;
            }
            st.push(s[i]);
            // cout << " -- " << res << endl;
        }
    }
    while (!st.empty()) {
        char ch = st.top();
        st.pop();
        res += ch;
    }
    cout << " - ���������� �����: " << res << endl;
    return res;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a, b;
    stack<double> st;
    string s, sign;

    cout << " ������� ��� ������: ";
    getline(cin, s);

    // ������� ������� � ������. � ���� ������ � ���������, � �� ���� ������ ����� ������ ������ ��� ���
    int pos = s.find(' ', 0);
    while (pos != -1) {
        //cout << " - pos - " << pos << endl;
        s.erase(pos, 1);
        pos = s.find(' ', 0);
        //cout << " - pos new - " << pos << endl;
    }
    cout << " - ������ ����� �������� ���������: " << s << endl;

    s = infixToPostfix(s);
    stringstream str(s);
    while (str >> sign) {
        if (!(sign == "-" || sign == "+" || sign == "*" || sign == "/")) 
            st.push(atof(sign.c_str()));
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
                    cout << " -- " << a << "+" << b;
                    break;
                case '-':
                    st.push(a - b);
                    cout << " -- " << a << "-" << b;
                    break;
                case '*':
                    st.push(a * b);
                    cout << " -- " << a << "*" << b;
                    break;
                case '/':
                    st.push(a / b);
                    cout << " -- " << a << "/" << b;
                    break;
            }
            cout << " = " << st.top() << endl;
        }
    }
    if (!st.empty()) {
        double ch = st.top();
        st.pop();
        if (st.empty()) {
            cout << " ���������: " << ch << "\n";
        }
    }
    system("pause");
    return 0;
}