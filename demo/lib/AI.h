#include<iostream>
#include<windows.h>
#include<iomanip>
#include<cstdlib>
#include<random>

using namespace std;

class Random_AI {
private:
    int color;

public:
    Random_AI(int color) {
        this->color = color;
    }

    node move(board br) {
        // Make a move randomly
        vector<node>valid=br.get_hint(color);
        for(int i=0;i<valid.size();i++)valid[i].x-=1,valid[i].y-=1;
        int len=valid.size();
        mt19937 rnd(time(0));
        int x=rnd()%len;
        return valid[x];
    }
};

class Greedy_AI {
private:
    int color;
    board brd;

public:
    Greedy_AI(int color) {
        this->color = color;
    }

    node move(board br) {
        brd=br;
        // Make a move using the greedy algorithm
        // Calculate the score of each move and choose the move with the highest score
        vector<node>valid=br.get_hint(color);
        for(int i=0;i<valid.size();i++)valid[i].x-=1,valid[i].y-=1;
        int len=valid.size();
        vector<int>score(len);
        for(int i=0;i<len;i++){
            board tmp=brd;
            tmp.move(valid[i]);
            if(color==1)
                score[i]=tmp.get_score().first;
            else
                score[i]=tmp.get_score().second;
        }
        int max=0,ans=0;
        for(int i=0;i<len;i++)
            if(score[i]>max){
                max=score[i];
                ans=i;
            }
            else if(score[i]==max){
                mt19937 rnd(time(0));
                if(rnd()%2)
                    ans=i;
            }
        return valid[ans];
    }
};

