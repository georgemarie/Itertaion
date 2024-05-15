/*
    20210219 : abdallah mohamed abdelfattah
    20210264 : omar khaled mohamed
    20210106 : George Marie Demyan
*/

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>

typedef long long ll;
using namespace std;

struct Call
{
    ll n;
    ll a, b, c, d;
    ll cur_loc;
};

ll F(ll n)
{
    Call initial_call;
    initial_call.n = n;
    initial_call.cur_loc = 0;
    stack<Call> st;
    st.push(initial_call);
    ll last_ret_val = 0; 
    // Return value of last finished call
    while (!st.empty())
    {
        Call &call = st.top();
        if (call.cur_loc == 0)
        {
            if (call.n <= 1)
            {
                // Call finished, save return value and pop stack
                last_ret_val = 1;
                st.pop();
            }
            else
            {
                // Make new child call F(n−1) and push to stack
                Call new_call;
                new_call.cur_loc = 0;
                new_call.n = call.n - 1;
                st.push(new_call);
                // Update current location inside parent call
                call.cur_loc = 1;
            }
        }
        else if (call.cur_loc == 1)
        {
            // Do required computations
            call.a = call.n * last_ret_val;
            // Make new child call F(n/2) and push to stack
            Call new_call;
            new_call.cur_loc = 0;
            new_call.n = (call.n / 2);
            st.push(new_call);
            // Update current location inside parent call
            call.cur_loc = 2;
        }
        else if (call.cur_loc == 2)
        {
            // Do required computations
            call.b = 7 * last_ret_val;
            call.c = call.n - 3 - (call.a + call.b) % 2;
            // Make new child call F(c) and push to stack
            Call new_call;
            new_call.cur_loc = 0;
            new_call.n = call.c;
            st.push(new_call);
            // Update current location inside parent call
            call.cur_loc = 3;
        }
        else if (call.cur_loc == 3)
        {
            // Do required computations
            call.d = last_ret_val;
            // Call finished, save return value and pop stack
            last_ret_val = call.a + call.b + call.d;
            st.pop();
        }
    }
    return last_ret_val;
}
// the recursive call to test our stack 
ll G(ll n)
{
    if (n <= 1)
        return 1;
    ll a = n * F(n - 1);
    ll b = 7 * F(n / 2);
    ll c = (n - 3 - (a + b) % 2);
    ll d = F(c);
    return a + b + d;
}

int main()
{
    ll TESTS = 20;
    int passes = 0;
    int failed = 0;
    for (ll test = 1; test <= TESTS; test++)
    {
        cout << "F(" << test << ") : " << F(test) << " ";
        if (F(test) == G(test))
        {
            cout << "passed...\n";
            passes++;
        }
        else
        {
            cout << "test failed!\n";
            failed++;
        }
    }
}