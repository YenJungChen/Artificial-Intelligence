#include <iostream>
#include <time.h>
#include <cstdlib>
#include <math.h>
using namespace std;
void ConverT(int guess, int *A) {
    for(int i=0; i<4; i++)
        A[3-i]=((int)(guess/pow(10.0, i)))%10;
}

void CheckNextGuess(int guess, int answer, int *A, int *B) {
    int G[4],Ans[4];
    ConverT(guess, G);
    ConverT(answer, Ans);
   	*A=0; *B=0;
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            if(G[i]==Ans[j]) {
                if(i==j)
                    *A=*A+1;
                
                else
                    *B=*B+1;
            }
        }
    }
}

bool DigitCheck(int cGuess) {
    int A[4];
    ConverT(cGuess, A);
    if(A[0]==0 || A[1]==0 || A[2]==0 || A[3]==0 ||
       A[0]==A[1] || A[0]==A[2] || A[0]==A[3] ||
       A[1]==A[2] || A[1]==A[3] || A[2]==A[3])
        return 1;
    return 0;
}

bool Win(int A, bool player) {
    if(A==4) {
        if(player) //0=computer, 1=player
            cout<<"You Win!!\n";
        else
            cout<<"Computer Win!!\n";
        return 1;
    }
    return 0;
}

void Answer(int *ans){
    int tmp[4], num=0;
    bool add;
    for(int i=0; i<4; i++) {
        add=true;
        tmp[i]=rand()%10;
        if(tmp[i]==0) {
            i--;
            continue;
        }
        for(int j=0; j<i; j++){
            if(tmp[i]==tmp[j]) {
                add=false;
                i--;
                break;
            }
        }
        if(add)
            num+=tmp[i]*(pow(10.0, 3-i));
    }
    *ans=num;
}

int main(void) {
    srand(time(NULL));
    int ans;
    Answer(&ans);
    //cout<<ans;
    //cin>>ans;
    cout<<"** Bulls & Cows **\n";
    cout<<"Rule: Now you are compete with your computer\n";
    cout<<"      Enter number: 1~9\n";
    cout<<"      Please enter 4-digits each time\n";
    int pGuess, cGuess, A=0, B=0, round=0, rSame=0,
    Record[9]={0}, RecordA[9]={0}, RecordB[9]={0};
    
    for(cGuess=1234;cGuess<=9876;cGuess++) {
        rSame=0;
        if(DigitCheck(cGuess)) {
            continue;
        }
        for(int i=0; i<round; i++) {
            CheckNextGuess(cGuess,Record[i], &A, &B);
            if(RecordA[i]==A && RecordB[i]==B)
                rSame++;
        }
        if(rSame!=round) {
            continue;
        }
        
        cout<<"\nRound: "<<round+1<<endl<<"Player Guess: ";
        cin>>pGuess;
        CheckNextGuess(pGuess, ans, &A, &B);
        cout<<A<<"A"<<B<<"B\n";
        if(Win(A, 1))
            return 0;
        cout<<"Computer Guess: "<<cGuess<<endl;
        CheckNextGuess(cGuess, ans, &A, &B);
        cout<<A<<"A"<<B<<"B\n";
        if(Win(A, 0))
            return 0;
        
        Record[round]=cGuess;
        RecordA[round]=A;
        RecordB[round]=B;
        round++;
    }
    return 0;
}
