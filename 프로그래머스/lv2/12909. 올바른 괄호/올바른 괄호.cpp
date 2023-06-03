#include <string>
#include <iostream>
#include <stack>
using namespace std;

bool solution(string s)
{
    bool answer = true;
    stack<char> st;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            st.push('(');
        }
        else if (s[i] == ')') {
            if (st.size() == 0) {
                answer = false;
                break;
            }
            else if (st.top() != '(') {
                answer = false;
                break;
            }
            else if (st.top() == '(') {
                st.pop();
            }
        }
    }
    if (st.size() != 0) answer = false;
    return answer;
}