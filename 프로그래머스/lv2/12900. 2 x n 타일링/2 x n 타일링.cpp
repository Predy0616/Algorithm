#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int ar[60001]={0, };
    ar[1]=1;
    ar[2]=2;
    for(int i=3; i<=n; i++){
        ar[i] = (ar[i-1]+ar[i-2])%1000000007;
    }
    int answer = ar[n];
    return answer;
}