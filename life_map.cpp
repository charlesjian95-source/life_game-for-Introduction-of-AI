#include "life_map.h"
#include <fstream>
#include <iostream>

using namespace std;


/*======================初始化地圖======================*/
void initMode(int mapp[][map_width],int mapp2[][map_width] , int mode_ID){ //兩族群所使用之init
    const vector<string>mode_file = {
        "double_patterns/dual_block.txt",
        "double_patterns/dual_glider.txt",
        "double_patterns/mixed_blinker.txt",
        "double_patterns/random.txt",
        "double_patterns/void.txt"
    };

    for(int i=0; i<map_height; i++){
        for(int j=0; j<map_width; j++){mapp[i][j]=0;mapp2[i][j]=0;}
    }
    if(mode_ID >0 && mode_ID <= mode_file.size()){
        ifstream file(mode_file[mode_ID-1]);
        if(!file.is_open()){return;}
        string line;
        vector<string> template_map;
        while(getline(file,line)){template_map.push_back(line);}
        loadMap(template_map,mapp,mapp2);
    }
    else{return;}
}
/*======================初始化地圖======================*/
void initMode(int mapp[][map_width] , int mode_ID){
    const vector<string>mode_file = {
        "block.txt",
        "beehive.txt",
        "blinker.txt",
        "toad.txt",
        "beacon.txt",
        "pulsar.txt",
        "glider.txt",
        "lwss.txt",
        "r_pentomino.txt",
        "acorn.txt",
        "gosper_glider_gun.txt",
        "void.txt"
    };
    //int mode_ID;
    /*
    cout << "input put mode you want";
    cout <<"=====Still Life靜態模式=====\n";
    cout << "1.Block\n" << "2.Beehive\n";
    cout <<"=====Oscillator週期震盪模式=====\n";
    cout<< "3.Blinker\n" << "4.Toad\n" << "5.Beacon\n"<< "6.Pulse\n"; 
    cout<<"=====Spaceship滑翔機=====\n";
    cout<< "7.Glider\n" << "8.LWSS\n"; 
    cout <<"=====Methuselah長壽模式=====\n";;
    cout<< "9.R-pentomino\n" << "10.Acorn\n";
    cout <<"=====Gun產生器=====\n";
    cout << "11.Gosper Glider Gun\n";
    cout << ":";
    cin >> mode_ID;*/
    for(int i=0; i<map_height; i++){
        for(int j=0; j<map_width; j++){mapp[i][j]=0;}
    }
    if(mode_ID >0 && mode_ID <= mode_file.size()){
        ifstream file(mode_file[mode_ID-1]);
        if(!file.is_open()){return;}
        string line;
        vector<string> template_map;
        while(getline(file,line)){template_map.push_back(line);}
        loadMap(template_map,mapp);
    }
    else{return;}
}

/*======================迭代函數======================*/
void nextGen(int mapp[][map_width])
{
    int x[8] = {-1,0,1,1,1,0,-1,-1};
    int y[8] = {1,1,1,0,-1,-1,-1,0};

    int newMapp[map_height][map_width];

    for(int i =0; i<map_height; i++){
        for(int j=0; j<map_width; j++){
            newMapp[i][j] = mapp[i][j];
        }
    }

    for(int i = 1; i< map_height - 1; i++)
    {
        for(int j=1; j<map_width - 1;j++)
        {
            int exist_num = 0;
            for(int k=0; k<8; k++ )
            {
                if(mapp[i+x[k]][j+y[k]] == 1){
                    exist_num ++ ;
                }
                
                

            }
            if(mapp[i][j] == 0 &&  exist_num == 3)
                newMapp[i][j] = 1;
            else if(mapp[i][j] == 0)
                continue;
            if(exist_num < 2)
                newMapp[i][j] = 0;
            else if(exist_num == 2 || exist_num == 3)
                newMapp[i][j] = 1;
            else if(exist_num > 3)
                newMapp[i][j] = 0;
        }
    }

    for(int i =0; i<map_height; i++){
        for(int j=0; j<map_width; j++){
            mapp[i][j] = newMapp[i][j];
        }
    }
}
/*======================迭代函數(多族群)======================*/
void nextGen(int mapp[][map_width],int mapp2[][map_width])
{
    int x[8] = {-1,0,1,1,1,0,-1,-1};
    int y[8] = {1,1,1,0,-1,-1,-1,0};

    int newMapp[map_height][map_width];
    int newMapp2[map_height][map_width];

    for(int i =0; i<map_height; i++){
        for(int j=0; j<map_width; j++){
            newMapp[i][j] = mapp[i][j];
            newMapp2[i][j] = mapp2[i][j];
        }
    }

    for(int i = 1; i< map_height - 1; i++)
    {
        for(int j=1; j<map_width - 1;j++)
        {
            int exist_num_1 = 0;
            int exist_num_2 = 0;
            int exist_sum = 0;
            for(int k=0; k<8; k++ )
            {
                if(mapp[i+x[k]][j+y[k]] == 1){
                    exist_num_1 ++ ;
                }
                if(mapp2[i+x[k]][j+y[k]] == 1){
                    exist_num_2 ++ ;
                }
            }

            exist_sum = exist_num_2 + exist_num_1; //計算鄰居數量

            if(mapp[i][j] == 0&& mapp2[i][j]==0 &&  exist_sum == 3){//判斷原來是空格的情況
                if(exist_num_1 > exist_num_2){newMapp[i][j]=1;}
                if(exist_num_1 < exist_num_2){newMapp2[i][j]=1;}
            }
            
            if(exist_sum < 2 || exist_sum >=4){
                newMapp[i][j] = 0;
                newMapp2[i][j] = 0;
            }
        }
    }


    for(int i =0; i<map_height; i++){
        for(int j=0; j<map_width; j++){
            mapp[i][j] = newMapp[i][j];
            mapp2[i][j] = newMapp2[i][j];
        }
    }
}
/*======================輸出地圖======================*/
void showMap(int mapp[][map_width])
{
    cout << "┌";
    for(int i=1; i< map_width-1; i++){cout <<"--";}
    cout << "┐" << '\n';
    for(int i = 1; i< map_height-1; i++)
    {   
        cout << "|";
        for(int j=1; j<map_width-1;j++)
        {
            if(mapp[i][j] == 1){
                cout << "██";
            }
            else{
                cout << "  ";
            }
        }
        cout << "|";
        cout << '\n';
    }
    cout << "└";
    for(int i=1; i< map_width-1; i++){cout << "--";}
    cout << "┘\n";
}
/*======================設置邊界======================*/
void buildBound(int mapp[][map_width]){
    for(int i=1; i<map_width-1; i++){ mapp[0][i] = -1; mapp[map_height-1][i] = -1;}
    for(int i=1; i<map_height-1; i++){ mapp[i][0] = -1; mapp[i][map_height-1] = -1;}
    mapp[0][0] = -1; 
    mapp[map_height-1][map_width-1] = -1;
    mapp[0][map_width-1] = -1;
    mapp[map_height-1][0] = -1;
}

/*======================初始化地圖(載入模板)======================*/
void loadMap(vector<string>template_map,int mapp[][map_width]){
    int height = template_map.size();
    int width = template_map[0].size();
    int h_begin = (map_height - height)/2;
    int w_begin = (map_width - width)/2;
    for(int i =0; i<height; i++){
        for(int j=0; j<width; j++){
            if(template_map[i][j] == 'O'){
                mapp[h_begin + i][w_begin + j] = 1;
            }
            
        }
    }
}

/*======================初始化地圖(載入模板)多族群使用======================*/
void loadMap(vector<string>template_map,int mapp[][map_width] , int mapp2[][map_width]){
    int height = template_map.size();
    int width = template_map[0].size();
    int h_begin = (map_height - height)/2;
    int w_begin = (map_width - width)/2;
    for(int i =0; i<height; i++){
        for(int j=0; j<width; j++){
            if(template_map[i][j] == '1'){
                mapp[h_begin + i][w_begin + j] = 1;
            }
            if(template_map[i][j] == '2'){
                mapp2[h_begin + i][w_begin + j] = 1;
            }
        }
    }
}
