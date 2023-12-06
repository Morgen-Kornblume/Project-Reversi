#include<iostream>
#include<vector>
#include<iomanip>
#include<random>
#include<utility>
#include<windows.h>
#include<conio.h>
#include"board.h"
#include"AI.h"
using namespace std;

class game{
private:
    board br; // The board of the game, which contains the information of the pieces on the board.
    int gametype; // The type of the game, 0 for human vs. human, 1 for human vs. AI.
    int difficulty; // The difficulty of the AI, 1 for random AI, 2 for greedy AI, 3 for minimax AI, 4 for alpha-beta AI, 5 for MCTS AI.
    //Random_AI RAI;
    //Greedy_AI GAI;
public:
    game(){
        br=board();
        gametype=0;
        difficulty=0;
    } // The constructor of the game, which initializes the game.
    void start(){
        //command list of the game
        system("cls");
        cout<<"Welcome to the world of Reversi!"<<endl;
        cout<<"Author: Morgen Kornblume"<<endl;
        cout<<"Version: Demo 1.0"<<endl;
        cout<<"Command list: "<<endl;
        cout<<"In following examples, '[(xx)yy]' contains a term, which has a name 'yy' and a type 'xx'. You don't need to really enter '[]'"<<endl;
        cout<<"command1: start-human [(int)color] -Start a human vs. human game with given one moves first (1:black / -1:white)"<<endl;
        cout<<"command2: start-AI [(int)Difficulty] [(int)color] -Start a human vs. AI game with given color moves first (1:black / -1:whit) (Difficulty:1~5 The higher,The harder) (AI always uses white pieces)"<<endl;
        cout<<"command3: load [(string)filename] -Load an existing game from file"<<endl;
        cout<<"command4: replay [(string)filename] -Replay an existing game from file"<<endl;
        gototag1:
        cout<<"Enter your command>> ";
        string command;
        cin>>command;
        if(command=="start-human"){
            int color;
            cin>>color;
            if(color==1||color==-1){
                this->br=board();
                round(color);
            }
            else{
                cout<<"Invalid color!"<<endl;
                goto gototag1;
            }
        }
        else if(command=="start-AI"){
            int color;
            cin>>difficulty>>color;
            if(difficulty<1||difficulty>5){
                cout<<"Invalid difficulty!"<<endl;
                goto gototag1;
            }
            if(color==1||color==-1){
                this->gametype=1;
                switch (difficulty){
                    case 1:
                        this->br=board();
                        //random AI
                        round(color);
                        break;
                    case 2:
                        this->br=board();
                        //greedy AI
                        round(color);
                        break;
                    case 3:
                        this->br=board();
                        //minimax AI
                        break;
                    case 4:
                        this->br=board();
                        //alpha-beta AI
                        break;
                    case 5:
                        this->br=board();
                        //MCTS AI
                        break;
                    //more : AI deep learning ...?
                }
            }
            else{
                cout<<"Invalid color!"<<endl;
                goto gototag1;
            }
        }
        else if(command=="load"){
            string filename;
            cin>>filename;
            filename = "saves\\" + filename + ".rps";
            ifstream fin(filename);
            if(!fin){
                cout<<"File not found!"<<endl;
                goto gototag1;
            }
            else{
                fin.close();
                load(filename);
            }
        }
        else if(command=="replay"){
            string filename;
            cin>>filename;
            filename = "saves\\" + filename + ".rps";
            ifstream fin(filename);
            if(!fin){
                cout<<"File not found!"<<endl;
                goto gototag1;
            }
            else{
                fin.close();
                replay(filename);
            }
        }
        else{
            cout<<"Invalid command!"<<endl;
            goto gototag1;
        }
    } // Start the game.
    void round(int color){
        if(gametype==1&&color==-1){
            //AI move
            node t;
            cout<<"AI is thinking... Please wait a moment..."<<endl;
            switch (difficulty){
                case 1:
                    t=Random_AI(color).move(br);
                    break;
                case 2:
                    t=Greedy_AI(color).move(br);
                    break;
                case 3:
                    //t=Minimax_AI(color).move(br);
                    break;
                case 4:
                    //t=AlphaBeta_AI(color).move(br);
                    break;
                case 5:
                    //t=MCTS_AI(color).move(br);
                    break;
                //more : AI deep learning ...?
            }
            br.move(t);
            int nxt=br.round_determin(color);
            if(nxt==0)end(br.get_score());
            else round(nxt);
        }
        system("cls");
        br.print();
        cout<<"Player "<<(color==1?"black":"white")<<"'s turn."<<endl;
        cout<<"Command list:"<<endl;
        cout<<"In following examples, '[(xx)yy]' contains a term, which has a name 'yy' and a type 'xx'. You don't need to really enter '[]'"<<endl;
        cout<<"command1: move [(int)x] [(int)y] -Place a piece on (x,y) if valid"<<endl;
        cout<<"command2: undo -Undo the last move"<<endl;
        cout<<"command3: save [(string)filename] -Save the game to file"<<endl;
        cout<<"command4: quit -Quit the game without saving"<<endl;
        cout<<"command5: quit-save [(string)filename] -Quit the game and save the game to file"<<endl;
        cout<<"command6: hint -Show where can be placed"<<endl;
        cout<<"command7: predict [(int)x] [(int)y] -Show what will happen if you place a piece on (x,y) (if valid)"<<endl;
        gototag2:
        cout<<"Enter your command>> ";
        Beep(720,1500);
        string command;
        cin>>command;
        if(command=="move"){
            int x,y;
            cin>>x>>y;
            x--;y--;
            if(x<0||x>7||y<0||y>7){
                cout<<"Invalid position!"<<endl;
                goto gototag2;
            }
            if(br.check(node(x,y,color))){
                br.move(node(x,y,color));
                int nxt=br.round_determin(color);
                if(nxt==0)end(br.get_score());
                else round(nxt);
            }
            else{
                cout<<"Invalid move!"<<endl;
                goto gototag2;
            }
        }
        else if(command=="undo"){
            br.undo();
            br.undo();
            round(color);
        }
        else if(command=="save"){
            string filename;
            cin>>filename;
            br.save(filename, gametype, difficulty);
            cout<<"Game saved!"<<endl;
            Beep(600,2000);
            round(color);
        }
        else if(command=="quit"){
            cout<<"Confirm to quit without saving? (y/n)"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y');
            else goto gototag2;
            cout<<"Game end!"<<endl;
            Beep(650,2000);
            system("pause");
            return;
        }
        else if(command=="quit-save"){
            string filename;
            cin>>filename;
            br.save(filename, gametype, difficulty);
            cout<<"Game saved!"<<endl;
            Beep(650,2000);
            system("pause");
            return;
        }
        else if(command=="hint"){
            br.print_with_hint(color);
            system("pause");
            round(color);
        }
        else if(command=="predict"){
            int x,y;
            cin>>x>>y;
            x--;y--;
            if(x<0||x>7||y<0||y>7){
                cout<<"Invalid position!"<<endl;
                goto gototag2;
            }
            br.print_with_predict(node(x,y,color));
            system("pause");
            round(color);
        }
        else if(command=="7355608"){//cheat code
            //music
            gototag3:
            system("cls");
            cout<<"Big brother, you have found the cheat code!"<<endl;
            mt19937 rnd(time(0));
            for(int i=0;i<10;i++){
                int x=rnd()%8,y=rnd()%8;
                br.move(node(x,y,color));
            }
            br.print();
            Sleep(40);
            goto gototag3;
        }
        else{
            cout<<"Invalid command!"<<endl;
            goto gototag2;
        }
    } // Start a round of the game , `color` is the color of the player to move.
    void replay(string filename){
        ifstream inFile(filename);
        vector<node> operations;
        int x, y, z;
        inFile>>(this->gametype)>>(this->difficulty);
        while (inFile >> x >> y >> z) {
            operations.push_back(node(x, y, z));
            //debug//
            //cout<<x<<" "<<y<<" "<<z<<endl;
            ////////
        }
        if(operations.empty()){
            cout<<"File is empty!"<<endl;
            Beep(650,2000);
            system("pause");
            return;
        }
        inFile.close();
        br = board();
        int pos = 0;
        gototag4:
        system("cls");
        cout<<"Replay: "<<pos<<"/"<<operations.size()<<endl;
        Beep(1000,200);
        br.print();
        cout<<"Input D(d) to show next step, A(a) to show previous step, q to quit."<<endl;//WASD
        char op = _getch();
        if(op=='a'||op=='A'){
            if(pos!=0){
                pos--;
                br.undo();
            }
        }
        else if(op=='d'||op=='D'){
            if(pos!=operations.size()){
                if(!br.check(operations[pos])){
                    cout<<"Bad Save!"<<endl;
                    Beep(650,2000);
                    system("pause");
                    return;
                }
                br.move(operations[pos]);
                pos++;
            }
        }
        else if(op=='q'||op=='Q'){
            cout<<"Confirm to quit? (y/n)"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y');
            else goto gototag4;
            cout<<"Replay end!"<<endl;
            Beep(650,2000);
            system("pause");
            return;
        }
        else{
            cout<<"Invalid command!"<<endl;
            goto gototag4;
        }
        goto gototag4;
    }// Replay the given game.
    void load(string filename){
        ifstream inFile(filename);
        vector<node> operations;
        //////debug////////
        //cout<<filename<<endl;
        //cout<<(inFile.is_open()?1:0)<<endl;
        ///////////////////
        inFile>>(this->gametype)>>(this->difficulty);
        int x, y, z;
        while (inFile >> x >> y >> z) {
            operations.push_back(node(x, y, z));
        }
        if(operations.empty()){
            cout<<"File is empty!"<<endl;
            Beep(650,2000);
            system("pause");
            return;
        }
        inFile.close();
        br = board();
        for(node tmp:operations){
            if(!br.check(tmp)){
                cout<<"Bad Save!"<<endl;
                Beep(650,2000);
                system("pause");
                return;
            }
            br.move(tmp);
        }
        int nxt=br.round_determin(operations.back().z);
        if(nxt==0)end(br.get_score());
        else round(nxt);
    } // Load the given game.
    void end(pair<int,int> result){
        system("cls");
        br.print();
        if(result.first>result.second)
            cout<<"Black wins!"<<endl;
        else if(result.first<result.second)
            cout<<"White wins!"<<endl;
        else
            cout<<"Draw!"<<endl;
        Beep(800,1500);
        system("pause");
    } // End the game.
};