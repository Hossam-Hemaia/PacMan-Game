#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <chrono>
#include <windows.h>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <map>
#include <set>
#include <string>
#include <iomanip>
// template function to check the coordinates while looping to draw food in spaces
template <typename M1, typename M2>
bool getcoord(std::multimap<M1, M2> &mmap, size_t k, size_t j){
    for (const auto &elem:mmap)
        if (elem.first == k && elem.second == j)
            return true;
    return false;
}
// function to delete the food if the coordinates of the palyer is the same as the food coordinates
// and deleting the food coordiantes from the map container and returning a true value
bool map_eraser(std::map<int, std::set<int>> &del_elem, int x, int y){
    for (auto &elem:del_elem){
        for (auto set_elem:elem.second){
            if (elem.first == x && set_elem == y){
                elem.second.erase(set_elem);
                return true;
            }
        }
    }return false;
}
bool busted;                 // boolean variable if the player got cought by the enemies
bool gamerunning;     // boolean variable to check if the game still running or not
int score{0};                   // the score variable
int lives{4};                     // the life variable which decremented if the player got cought by the enemy
enum eDirection{STOP = 0, UP, DOWN, LEFT, RIGHT};       // using enumeration for directions 
eDirection direction;
int x = 1;          //this is the player starting coordinates
int y = 3;                      
int enemy1x = 10;    // this is the enemies starting coordiantes
int enemy1y = 19;
int enemy2x = 10;
int enemy2y = 18;
int enemy3x = 10;
int enemy3y = 20;
int stray_enemyx = 10;
int stray_enemyy = 21;
std::multimap<size_t, size_t>coordmap;           //multimap container to store the coordinates of the space coordinates
std::map<int, std::set<int>>position;                 // map container to store the food coordinates 
std::set<int>h_position;                                       // set container to store the horizental coordinates only
char map[21][40]{                 // declaring dimensional array of charachter i made it global declaration so it can be passed to all functions        
         "  ###################################  ",
         "  #                                 #  ",
         "  # ### ### ## ####### ## ####### # #  ",
         "  # ### ### ## ####### ## ####### # #  ",
         "  # ### ### ## ####### ## ##      # #  ",
         "  # #######    ###|### ## ####### # #  ",
         "  # ####### ## ###|###    ####### # #  ",
         "  # ### ### ## ####### ##      ## # #  ",
         "  # ### ### ## ####### ## ####### # #  ",
         "### ### ### ## ####### ## ####### # ###",
         "#<                                   >#",
         "### ####### ## ####### ## ## ### ## ###",
         "  # ####### ## ####### ## ###|#|### #  ",
         "  # ##      ## ###|### ## ####|#### #  ",
         "  # ####### ## ###|###    ######### #  ",
         "  # #######    ####### ## ####|#### #  ",
         "  #      ## ## ### ### ## ### # ### #  ",
         "  # ####### ## ### ### ## ###   ### #  ",
         "  # ####### ## ### ### ## ###   ### #  ",
         "  #                                 #  ",
         "  ###################################  "};
int enemy1direction(){        // these functions is to randomly generate the enemies directions
    return rand() %4 + 1;
}
int enemy2direction(){
    return rand() %4 + 1;
}
int enemy3direction(){
    return rand() %4 + 1;
}
int enemy4direction(){
    return rand() %4 + 1;
}
void setup(){    //this function is to setup the variables before starting the game
    lives = 4;
    score = 0;
    direction = STOP;
    for (int i = 1; i < 20; ++i){            // this loop is to insert values of the space coordinates into the map container
        for (int t = 3; t < 37; ++t){
            if (map[i][t] == ' '){
                h_position.insert(t);
            }
        }position.insert(std::make_pair(i, h_position));
    }
}
void draw(){         // this function to draw the game on the console screen
    std::this_thread::sleep_for(std::chrono::milliseconds(35));    //determining how fast the motion will be for every action in this function
    LockWindowUpdate(GetConsoleWindow());    // this code stops the console window from updating                      
    system("cls");           // clearing the consol
    char map[21][40]{     // declaring the diminsional array of character again so it will appear after we cleard the console screen
         "  ###################################  ",
         "  #                                 #  ",
         "  # ### ### ## ####### ## ####### # #  ",
         "  # ### ### ## ####### ## ####### # #  ",
         "  # ### ### ## ####### ## ##      # #  ",
         "  # #######    ###|### ## ####### # #  ",
         "  # ####### ## ###|###    ####### # #  ",
         "  # ### ### ## ####### ##      ## # #  ",
         "  # ### ### ## ####### ## ####### # #  ",
         "### ### ### ## ####### ## ####### # ###",
         "#<                                   >#",
         "### ####### ## ####### ## ## ### ## ###",
         "  # ####### ## ####### ## ###|#|### #  ",
         "  # ##      ## ###|### ## ####|#### #  ",
         "  # ####### ## ###|###    ######### #  ",
         "  # #######    ####### ## ####|#### #  ",
         "  #      ## ## ### ### ## ### # ### #  ",
         "  # ####### ## ### ### ## ###   ### #  ",
         "  # ####### ## ### ### ## ###   ### #  ",
         "  #                                 #  ",
         "  ###################################  "};
        for (size_t k = 0; k < 21; ++k){                      // main loop to draw every thing in the array you can understand the rest
            for (size_t j = 0; j < 40; ++j){
                if (map[x] == map[k] && map[y] == map[j]){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);     // palyer color
                    std::cout << '@';
                }else if (map[enemy1x] == map[k] && map[enemy1y] == map[j]){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);     // enemy color and so on
                    std::cout << (map[enemy1x][enemy1y] = 'X');
                }else if (map[enemy2x] == map[k] && map[enemy2y] == map[j]){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                    std::cout << (map[enemy2x][enemy2y] = 'R');
                }else if (map[enemy3x] == map[k] && map[enemy3y] == map[j]){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    std::cout << (map[enemy3x][enemy3y] = 'K');
                }else if (map[stray_enemyx] == map[k] && map[stray_enemyy] == map[j]){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    std::cout << (map[stray_enemyx][stray_enemyy] = 'Z');
                }else if (map[k][j] == ' ' && k >=1 && k < 20 && j >=3 && j < 37 && getcoord(coordmap, k, j) == false){ // this if statement to draw food take a deep look
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    std::cout << (map[k][j] = '-');
                }else if (map[k][j] == ' '){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                    std::cout << (map[k][j] = ' ');
                }else{
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    std::cout << map[k][j];
                }
            }std::cout << std::endl;
        }
    LockWindowUpdate(NULL);  // unlocking the console window after drawing the game
}
void input(){    // this function is for the keyboard input 
    if (_kbhit())                              
         (getch());
        if (GetAsyncKeyState(VK_UP) && map[x-1][y] != '#' ){     // the if statement is to get true value if the UP arrow key is hitand so on
            direction = UP;                                                                    // other condition is to prevent the player to stop while moving and the direction is toward a wall
            std::this_thread::sleep_for(std::chrono::milliseconds(15));   
        }
        if (GetAsyncKeyState(VK_DOWN) && map[x+1][y]  != '#'){
            direction = DOWN;
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
            
       if (GetAsyncKeyState(VK_LEFT) && map[x][y-1] != '#'){
            direction = LEFT;
        } 
        if (GetAsyncKeyState(VK_RIGHT) && map[x][y+1] != '#'){
            direction = RIGHT;
        }
        if (GetAsyncKeyState(VK_ESCAPE)){
            gamerunning = true;
        }
}
void logic(){                   // this function for the logic of the game
    switch (direction){    // switch the player direction
        case UP:
            if(map[x-1][y] != '#' ){
                coordmap.insert(std::pair<size_t, size_t>(static_cast<size_t>(x-1), static_cast<size_t>(y)));   // inserting the player coordinates while moving so it gives true value
                if (map_eraser(position, (x-1), y)){                                                                                                   // so the draw food condition fails
                    ++score;       // this code is to increment the socre by 1 and using if statement if the true value returned so the score is incremented
                }
                --x;
            }else{
                break;
            }
            break;
        case DOWN:
            if(map[x+1][y]  != '#'){
                coordmap.insert(std::pair<size_t, size_t>(static_cast<size_t>(x+1), static_cast<size_t>(y)));
                if (map_eraser(position, (x+1), y)){
                    ++score;
                }
                ++x;
            }else{
                break;
            }
            break;
        case LEFT:
            if (map[x][y-1] == ' '){
                coordmap.insert(std::pair<size_t, size_t>(static_cast<size_t>(x), static_cast<size_t>(y-1)));
                if (map_eraser(position, x, (y-1))){
                    ++score;
                }
                --y;
            }else if (map[x][y-1] == '<'){       // this if statement used to enable the player to go throu the backdoor in the maze
                map[x][y] = ' ';
                y = 37;
            }else{
                break;
            }
            break;
        case RIGHT:
            if (map[x][y+1] == ' '){
                coordmap.insert(std::pair<size_t, size_t>(static_cast<size_t>(x), static_cast<size_t>(y+1)));
                if (map_eraser(position, x, (y+1))){
                    ++score;
                }
                ++y;
            }else if ( map[x][y+1] == '>'){
                map[x][y] = ' ';
                y = 3;
            }else{
                break;
            }
            break;
        default:
            break;
    }
    switch (enemy1direction()){     // first enemy directions
        case 1:
            if (map[enemy1x-1][enemy1y] != '#' && enemy1x >= x){         // the first condition is to check for spaces the other condition is to chase the player coordinates
                --enemy1x;
            }else if (map[enemy1x-1][enemy1y] == '#' && map[enemy1x+1][enemy1y] != '#'){
                ++enemy1x;
            }
            break;
        case 2:
            if (map[enemy1x+1][enemy1y] != '#' && enemy1x <= x){
                ++enemy1x;
            }else if (map[enemy1x+1][enemy1y] == '#' && map[enemy1x-1][enemy1y] != '#'){
                --enemy1x;
            }
            break;
        case 3:
            if (map[enemy1x][enemy1y-1] != '#' && enemy1y >= y){
                --enemy1y;
            }else if (map[enemy1x][enemy1y-1] == '#' && map[enemy1x][enemy1y+1] != '#'){
                ++enemy1y;
            }
            break;
        case 4:
            if (map[enemy1x][enemy1y+1] != '#'&& enemy1y <= y){
                ++enemy1y;
            }else if (map[enemy1x][enemy1y+1] == '#' && map[enemy1x][enemy1y-1] != '#'){
                --enemy1y;
            }
            break;
        default:
            break;
    }
    switch (enemy2direction()){     // second enemy directions
        case 1:
            if (map[enemy2x-1][enemy2y] != '#' && enemy2x >= x){
                --enemy2x;
            }else if (map[enemy2x-1][enemy2y] == '#' && map[enemy2x+1][enemy2y] != '#'){
                ++enemy2x;
            }
            break;
        case 2:
            if (map[enemy2x+1][enemy2y] != '#' && enemy2x <= x){
                ++enemy2x;
            }else if (map[enemy2x+1][enemy2y] == '#' && map[enemy2x-1][enemy2y] != '#'){
                --enemy2x;
            }
            break;
        case 3:
            if (map[enemy2x][enemy2y-1] != '#' && enemy2y >= y){
                --enemy2y;
            }else if (map[enemy2x][enemy2y-1] == '#' && map[enemy2x][enemy2y+1] != '#'){
                ++enemy2y;
            }
            break;
        case 4:
            if (map[enemy2x][enemy2y+1] != '#' && enemy2y <= y){
                ++enemy2y;
            }else if (map[enemy2x][enemy2y+1] == '#' && map[enemy2x][enemy2y-1] != '#'){
                --enemy2y;
            }
            break;
        default:
            break;
    }
    switch (enemy3direction()){     // third enemy directions
        case 1:
            if (map[enemy3x-1][enemy3y] != '#' && enemy3x >= x){
                --enemy3x;
            }else if (map[enemy3x-1][enemy3y] == '#' && map[enemy3x+1][enemy3y] != '#'){
                ++enemy3x;
            }
            break;
        case 2:
            if (map[enemy3x+1][enemy3y] != '#' && enemy3x <= x){
                ++enemy3x;
            }else if (map[enemy3x+1][enemy3y] == '#' && map[enemy3x-1][enemy3y] != '#'){
                --enemy3x;
            }
            break;
        case 3:
            if (map[enemy3x][enemy3y-1] != '#' && enemy3y >= y){
                --enemy3y;
            }else if (map[enemy3x][enemy3y-1] == '#' && map[enemy3x][enemy3y+1] != '#'){
                ++enemy3y;
            }
            break;
        case 4:
            if (map[enemy3x][enemy3y+1] != '#' && enemy3y <= y){
                ++enemy3y;
            }else if (map[enemy3x][enemy3y+1] == '#' && map[enemy3x][enemy3y-1] != '#'){
                --enemy3y;
            }
            break;
        default:
            break;
    }
    switch (enemy4direction()){     // stray enemy directions this enemy doesn't chase the player
        case 1:
            if (map[stray_enemyx - 1][stray_enemyy] != '#'){
                --stray_enemyx;
            }else if (map[stray_enemyx-1][stray_enemyy] == '#' && map[stray_enemyx+1][stray_enemyy] != '#'){
                ++stray_enemyx;
            }
            break;
        case 2:
            if (map[stray_enemyx+1][stray_enemyy] != '#'){
                ++stray_enemyx;
            }else if (map[stray_enemyx+1][stray_enemyy] == '#' && map[stray_enemyx-1][stray_enemyy] != '#'){
                --stray_enemyx;
            }
            break;
        case 3:
            if (map[stray_enemyx][stray_enemyy-1] != '#'){
                --stray_enemyy;
            }else if (map[stray_enemyx][stray_enemyy-1] == '#' && map[stray_enemyx][stray_enemyy+1] != '#'){
                ++stray_enemyy;
            }
            break;
        case 4:
            if (map[stray_enemyx][stray_enemyy+1] != '#'){
                ++stray_enemyy;
            }else if (map[stray_enemyx][stray_enemyy+1] == '#' && map[stray_enemyx][stray_enemyy-1] != '#'){
                --stray_enemyy;
            }
            break;
        default:
            break;
    }
    if ((map[x] == map[enemy1x] && map[y] == map[enemy1y]) || (map[x] == map[enemy2x] && map[y] == map[enemy2y]) 
        || (map[x] == map[enemy3x] && map[y] == map[enemy3y]) || (map[x] == map[stray_enemyx] && map[y] == map[stray_enemyy])){
        busted = true;       // if statement to set the player death conditions so if any of the enemies coordinates are equal to the player 
        --lives;                    // coordinates the player is busted and lives are decremented by 1 and all go back to thier starting coordinates
        x = 1;
        y = 3;
        enemy1x = 10;
        enemy1y = 19;
        enemy2x = 10;
        enemy2y = 18;
        enemy3x = 10;
        enemy3y = 20;
        stray_enemyx = 10;
        stray_enemyy = 21;
        direction = STOP;
    }
    if (score == 251){     // the condition if the player ate all the food
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        std::cout << std::setw(23) << std::right << "You won!!!" << std::endl;
        direction = STOP;
        x = 1;
        y = 3;
        enemy1x = 10;
        enemy1y = 19;
        enemy2x = 10;
        enemy2y = 18;
        enemy3x = 10;
        enemy3y = 20;
        stray_enemyx = 10;
        stray_enemyy = 21;
        gamerunning = false;
        position.clear();
    }
}
int main(){     
    std::string run_game;
    srand(time(NULL));       // this cood is to seed the random functions so it will not generate the same sequence of results
    char answer{'y'};
    do{      // the outer game loop
        if (answer == 'Y' || answer == 'y'){
            setup();
            lives = 4;
            coordmap.clear();
            gamerunning = true;
            std::cout << "Start game (Y/N): ";
            std::cin>> run_game;
            if (run_game == "y" && run_game == "y"){
                while(lives > 0 && gamerunning == true){       // the main game loop 
                    draw();
                    input();
                    logic();
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    std::cout << "Score: " << score << std::endl;
                    std::cout << "Lives: " << lives << std::endl;
                }
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "Play again (Y/N): ";
        std::cin >> answer;
        if (answer != 'y' && answer != 'n')
            std::cout << "Please Enter a valid answer(y/n)"<<std::endl;
        position.clear();
    }while(answer != 'N' && answer != 'n');
    std::cout << "Goodbye!!!" << std::endl;
    return 0;
}
