#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream Data(filename);
    string line;

    while(getline(Data,line)){
        int size_name = line.find(":");
        int space_1 = line.find(" ",size_name+2);
        int space_2 = line.find(" ",space_1+1);
        names.push_back(line.substr(0,size_name));
        int score_1 = atoi(line.substr(size_name+2,2).c_str());
        int score_2 = atoi(line.substr(space_1+1,2).c_str());
        int score_3 = atoi(line.substr(space_2+1,2).c_str());
        int all_scores = score_1 + score_2 + score_3;
        scores.push_back(all_scores);
        grades.push_back(score2grade(all_scores));
    }
}

void getCommand(string &command, string &key){
    string all;
    cout << "Please input your command: \n";
    getline(cin, all);
    size_t space = all.find(" ");
    if(space == string::npos){
        command = all;
        key = "";
    }
    else{
    command = all.substr(0,space);
    key = all.substr(space+1);
    }
}
void searchName(vector<string> names, vector<int> scores, vector<char> grade,string key){
    int count = 0;
    for(size_t i=0;i<names.size();i++){
        if(toUpperStr(names[i])==key){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grade[i] << "\n";
            cout << "---------------------------------\n";
            count++;
        }
    }
    if(count == 0){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    int count = 0;
    cout << "---------------------------------\n";
    for(size_t i=0;i<grades.size();i++){
        if(grades[i]==key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            count++;
        }
    }
    if(count == 0){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}