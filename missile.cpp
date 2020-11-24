#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int initial_tanks = 8;
const int initial_sm = 1;
const int boardRow = 4;
const int boardCol = 8;

bool verifyCoordinate(string coor){
    if(coor.size() == 2 && isalpha(coor[0]) && isdigit(coor[1]) &&
       coor[0] >= 'A' && coor[0] <= 'H' && coor[1] >= '1' && coor[1] <= '4')
        return true;
    return false;
}

void split_command(string command, vector<string> &split_list){
    int found = command.find_first_of(" ");
    int start = 0;
    while(found != string::npos){
        split_list.push_back(command.substr(start, found-start));
        start = found+1;
        found = command.find_first_of(" ", start);
    }
    split_list.push_back(command.substr(start));
}

string generateNewCoordinate(string old, string direction){
    string newC = old;
    if(direction == "T")
        newC[1]++;
    else if(direction == "B")
        newC[1]--;
    else if(direction == "L")
        newC[0]--;
    else if(direction == "R")
        newC[0]++;

    return newC;
}


struct Player{
    Player(string name_ = "default_player", int tanks_= initial_tanks, int sm_ = initial_sm): name(name_),
            tanks(tanks_), sm(sm_) {
        for(int i=0;i<boardRow;i++){
            board.push_back(vector<int>());
        }
        for(int i=0;i<boardRow;i++){
            for(int j=0; j<boardCol;j++){
                board[i].push_back(0);
            }
        }
    }
    string name;
    int tanks;
    int sm;
    vector<vector<int>> board;
    vector<string> destroyed;
    vector<string> targeted;
};


int main(int argc, char *argv[]) {
    if(argc < 3){
        cout << "Usage: missile <player_1_coordinate_file> <player_2_coordinate_file>" << endl;
        return 0;
    }

    int max_arg=4;
    Player players[2];

    //for the board, 0 means an empty slot, 1 means occupied by a tank

    for(int i=1;i<argc && i<=max_arg;i++){
        if(i == 1 || i == 2){
            int player = i-1;
            ifstream infile(argv[i]);
            if(!infile){
                cout << "Error: invalid file name for player_coordinate_file" << endl;
                return 0;
            }
            else{
                vector<string> coordinate_list;
                while(!infile.eof()){
                    string coor;
                    infile >> coor;
                    if(!coor.empty())
                        coordinate_list.push_back(coor);
                }
                if(coordinate_list.size() != initial_tanks){
                    cout << "Error: invalid content for player_coordinate_file" << endl;
                    return 0;
                }
                else{
                    for(int j=0;j<initial_tanks;j++){
                        if(verifyCoordinate(coordinate_list[j])){
                            players[player].board[coordinate_list[j][1]-'1'][coordinate_list[j][0]-'A'] = 1;
                        }
                        else{
                            cout << "Error: invalid content for player_coordinate_file" << endl;
                            return 0;
                        }
                    }
                }
            }
        }
        else if(i == 3){
            players[0].name = string(argv[i]);
        }
        else if(i == 4){
            players[1].name = string(argv[i]);
        }
    }

    string testcase;
    if(argc >= 2)
        testcase = string(argv[2]);
    int symbol = testcase.find("/");
    testcase = testcase.substr(0, symbol+1);


    Player initial_players[2];
    initial_players[0] = players[0]; initial_players[1] = players[1];

    ifstream infile(testcase + "commands.txt");
    if(!infile){
        cout << "Test case file does not exits." << endl;
        return 0;
    }
    int turn_count = 0;
    int player = 1 ;
    int counter = 0;
    while(!infile.eof() && players[0].tanks && players[1].tanks){
         string command;
         getline(infile, command);
         if(command.empty())
             continue;
         else{
             turn_count++;
             player = (turn_count+1) % 2;
             counter = (player == 1)? 0 : 1;
             cout << players[player].name << ", now is your turn." << endl;
             cout << command << endl;
             if(command == "stats" || command == "help" || command == "reset"){
                 if(command == "stats"){
                     cout << "======================================Stats Board=======================" << endl;
                     cout << "This is turn number " << turn_count << endl;
                     cout << players[0].name << " has targeted the following positions: " << endl;
                     for(int i=0;i<players[0].targeted.size();i++){
                         cout << players[0].targeted[i] << " ";
                     }
                     cout << endl;
                     cout << players[0].name << " has destroyed " << players[0].destroyed.size() << " tanks in the following positions: " << endl;
                     for(int i=0;i<players[0].destroyed.size();i++){
                         cout << players[0].destroyed[i] << " ";
                     }
                     cout << endl;
                     cout << players[0].name << " has " << players[0].sm << " special missiles" << endl;
                      cout << "------------------------------------------------------------------------" << endl;
                      cout << players[1].name << " has targeted the following positions: " << endl;
                     for(int i=0;i<players[1].targeted.size();i++){
                         cout << players[1].targeted[i] << " ";
                     }
                     cout << endl;
                     cout << players[1].name << " has destroyed " << players[1].destroyed.size() << " tanks in the following positions: " << endl;
                     for(int i=0;i<players[1].destroyed.size();i++){
                         cout << players[1].destroyed[i] << " ";
                     }
                     cout << endl;
                     cout << players[1].name << " has " << players[1].sm << " special missiles" << endl;
                     cout << "========================================================================" << endl;
                      turn_count--;
                     continue;
                 }
                 else if(command == "help"){
                     cout << "Missile is a game where 2 players each have a 4x8 board which is hidden from the other player. "
                             "Initially, each player has 8 tanks placed on the board, 1 special missile and infinite regular missiles."
                             "A regular missile can target one coordinate. A special missile can target one coordinate and one that is adjacent to it."
                             "Whoever destroyed the first tank can get an additional special missile."
                             "The player who first destroys all 8 tanks of the opponent wins." << endl;
                     turn_count--;
                     continue;
                 }
                 else{
                     cout << "Are you sure to reset the game to the initial state? Input Y to confirm." << endl;
                     string choice;
                     getline(infile, choice);
                     if(choice == "Y"){
                         players[0] = initial_players[0];
                         players[1] = initial_players[1];
                         turn_count = 0;
                         continue;
                     }
                     else{
                         cout << "Error: you have entered something invalid, the reset is not going to happen" << endl;
                         turn_count--;
                         continue;
                     }
                 }
             }
             else{
                 vector<string> split_list;
                 split_command(command, split_list);
                 if(split_list.size() && split_list[0] == "RM" || split_list[0] == "SM"){
                     if(split_list[0] == "RM"){
                         if(split_list.size() == 2 && verifyCoordinate(split_list[1])){
                             players[player].targeted.push_back(split_list[1]);
                             if(players[counter].board[split_list[1][1]-'1'][split_list[1][0]-'A'] == 1){
                                 if(players[0].destroyed.size() == 0 && players[1].destroyed.size() == 0){
                                     players[player].sm++;
                                 }
                                 players[counter].board[split_list[1][1]-'1'][split_list[1][0]-'A'] = 0;
                                 players[player].destroyed.push_back(split_list[1]);
                                 players[counter].tanks--;
                                 cout << "You have destroyed a tank!" << endl;
                              }
                             else{
                                 cout << "Nothing happened!" << endl;
                             }
                         }
                         else{
                             cout << "The input is invalid, please try again" << endl;
                             turn_count--;
                             continue;
                         }
                     }
                     else if(split_list[0] == "SM"){
                         if(split_list.size() == 3 && verifyCoordinate(split_list[1]) &&
                            (split_list[2] == "T" || split_list[2] == "L" || split_list[2] == "B"
                             || split_list[2] == "R")){
                             if(players[player].sm){
                                 players[player].targeted.push_back(split_list[1]);
                                 int destroyed_tank = 0;
                                 if(players[counter].board[split_list[1][1]-'1'][split_list[1][0]-'A'] == 1){
                                     if(players[0].destroyed.size() == 0 && players[1].destroyed.size() == 0){
                                         players[player].sm++;
                                     }
                                     players[counter].board[split_list[1][1]-'1'][split_list[1][0]-'A'] = 0;
                                     players[counter].tanks--;
                                     players[player].destroyed.push_back(split_list[1]);
                                     destroyed_tank++;
                                  }
                                 string newC = generateNewCoordinate(split_list[1], split_list[2]);
                                 if(verifyCoordinate(newC)){
                                     players[player].targeted.push_back(newC);
                                     if(players[counter].board[newC[1]-'1'][newC[0]-'A'] == 1){
                                         if(players[0].destroyed.size() == 0 && players[1].destroyed.size() == 0){
                                             players[player].sm++;
                                         }
                                         players[counter].board[newC[1]-'1'][newC[0]-'A'] = 0;
                                         players[player].destroyed.push_back(newC);
                                         players[counter].tanks--;
                                         destroyed_tank++;
                                     }
                                 }
                                  cout << "You have destroyed " << destroyed_tank << " tanks!" << endl;
                                 players[player].sm--;
                             }
                             else{
                                 cout << "You don't have any special missile!" << endl;
                                 turn_count--;
                                 continue;
                             }
                         }
                         else{
                             cout << "The input is invalid, please try again" << endl;
                             turn_count--;
                             continue;
                         }
                     }
                 }
                 else{
                     cout << "The command is invalid, please try again" << endl;
                     turn_count--;
                     continue;
                 }
             }
         }
    }

	if(players[0].tanks == 0 && players[1].tanks){
		cout << players[1].name << ", you have won!" << endl;	
	}
	else if(players[0].tanks && players[1].tanks == 0){
		cout << players[0].name << ", you have won!" << endl;
	}
	

    return 0;


}
