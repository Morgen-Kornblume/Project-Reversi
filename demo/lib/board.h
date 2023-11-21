/*
This code is in the library of the project Reversi (Demo).
This code contains the class board, which is used to store the situation of the board and the history of the game.
The class board has the following functions:
    print: print the board
    print_with_hint: print the board with the hint of the next move
    print_with_predict: print the board with the hint of the next move and the prediction of the result of the game
    move: move the piece
    undo: undo the last move
    check: check if the move is valid
    save: save the game
    load: load the game
This code is a kernal part of the project Reversi (Demo), and can be reused in advanced versions of the project.
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

struct node{
    int x,y,z;
    node(int xx=0,int yy=0,int zz=0){
        x=xx;y=yy;z=zz;
    }
};//x,y: position; z: color

class board{
private:
    int situ[8][8];//situation of the board
    vector<node> history;
    
public:
    board(){
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                situ[i][j]=0;
        situ[3][3]=situ[4][4]=1;
        situ[3][4]=situ[4][3]=-1;
        history.clear();
    }
    bool check(node t){//check if the position can be placed
        if(situ[t.x][t.y]!=0)
            return false;
        int dx[8]={-1,-1,-1,0,0,1,1,1};
        int dy[8]={-1,0,1,-1,1,-1,0,1};
        for(int i=0;i<8;i++){
            int x=t.x+dx[i],y=t.y+dy[i];
            if(x<0||x>7||y<0||y>7||situ[x][y]==0||situ[x][y]==t.z)
                continue;
            while(x>=0&&x<8&&y>=0&&y<8&&situ[x][y]==-t.z){
                x+=dx[i];
                y+=dy[i];
            }
            if(x>=0&&x<8&&y>=0&&y<8&&situ[x][y]==t.z)
                return true;
        }
        return false;
    }
    void print(){
        std::cout << "  1 2 3 4 5 6 7 8" << std::endl;
        for(int i=0;i<8;i++){
            std::cout << i+1 << "|";
            for(int j=0;j<8;j++){
                if(situ[i][j] == 1)//black piece
                    std::cout << "X";
                else if(situ[i][j] == -1)//white piece
                    std::cout << "O";
                else//empty
                    std::cout << " ";
                std::cout << "|";
            }
            std::cout << std::endl;
        }
        std::cout <<"-------------------"<< std::endl;
        std::cout << "X represents black piece." << std::endl;
        std::cout << "O represents white piece." << std::endl;
    }
        
    void print_with_hint(int turn){
        std::cout << "  1 2 3 4 5 6 7 8" << std::endl;
        for(int i=0;i<8;i++){
            std::cout << i+1 << "|";
            for(int j=0;j<8;j++){
                if(situ[i][j] == 1)//black piece
                    std::cout << "X";
                else if(situ[i][j] == -1)//white piece
                    std::cout << "O";
                else//empty
                    if(check(node(i,j,turn)))std::cout << "*";
                    else std::cout << " ";
                std::cout << "|";
            }
            std::cout << std::endl;
        }
        std::cout <<"-------------------"<< std::endl;
        std::cout << "X represents black piece." << std::endl;
        std::cout << "O represents white piece." << std::endl;
        std::cout << "* represents the position that can be placed." << std::endl;
    }
    void move(node t){
        //make a move!
        history.push_back(t);
        situ[t.x][t.y]=t.z;
        int dx[8]={-1,-1,-1,0,0,1,1,1};
        int dy[8]={-1,0,1,-1,1,-1,0,1};
        for(int i=0;i<8;i++){
            int x=t.x+dx[i],y=t.y+dy[i];
            if(x<0||x>7||y<0||y>7||situ[x][y]==0||situ[x][y]==t.z)
                continue;
            while(x>=0&&x<8&&y>=0&&y<8&&situ[x][y]==-t.z){
                x+=dx[i];
                y+=dy[i];
            }
            if(x>=0&&x<8&&y>=0&&y<8&&situ[x][y]==t.z){
                x=t.x+dx[i];
                y=t.y+dy[i];
                while(x>=0&&x<8&&y>=0&&y<8&&situ[x][y]==-t.z){
                    situ[x][y]=t.z;
                    x+=dx[i];
                    y+=dy[i];
                }
            }
        }
        //Warning that move is not checked, so please examine check function before move 
    }
    void print_with_predict(node t){
        if(!check(t)){
            std::cout << "Invalid move!" << std::endl;
            return;
        }
        board temp=*this;
        temp.move(t);
        temp.print();
    }
    void undo(){
        history.pop_back();
        board temp;
        for(node tmp:history)
            temp.move(tmp);
        *this=temp;
    }
    void save(string filename){
        filename = "saves\\" + filename + ".rps";
        std::ofstream outFile(filename);
        for(node tmp : history) {
            outFile << tmp.x << " " << tmp.y << " " << tmp.z << "\n";
        }
        outFile.close();
    }
    void load(string filename){
        filename = "saves\\" + filename + ".rps";
        std::ifstream inFile(filename);
        board temp;
        int x, y, z;
        while (inFile >> x >> y >> z) {
            temp.move(node(x, y, z));
            temp.history.push_back(node(x, y, z));
        }
        *this = temp;
        inFile.close();
    }
};
        