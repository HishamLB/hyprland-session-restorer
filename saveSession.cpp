#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <array>
#include <vector>
#include <unistd.h>

using namespace std;

// TODO:
// Write your own restore
// Handle applications not visible to hyprland using lookup tables and if's
// check if the hyprctl clients is longer after u dispatch, if it isnt moveo  n
vector<string> lines;
void save();
void restore();
int checkIfAppOpen();
string find_in_path(const std::string& app);
int main(){

    restore();
    return 0;
}

void dispatch(int workspace, string application){
    int before = checkIfAppOpen();
    sleep(2);

    
    string command = "hyprctl dispatch exec \"[workspace " + std::to_string(workspace) + " silent] " + application + "\"";

    cout << command << endl;
    system(command.c_str());
    
    sleep(2);
    int after = checkIfAppOpen();
    

    if(before == after){
        // make a list of special cases??:
        if(application == "libreoffice-impress")
            system("hyprctl dispatch exec \"libreoffice --impress\" ");
        cout << "Trying..";
        string path = find_in_path(application);
        string pathCommand = "hyprctl dispatch exec \"[workspace " +to_string(workspace) + " silent] " + path + "\"";
        cout << "hyprctl dispatch exec \"" + path + "\"";
        
        system(pathCommand.c_str());
    }

}
std::string shell_escape_spaces(const std::string& path) {
    std::string escaped;
    for (char c : path) {
        if (c == ' ') {
            escaped += "\\ ";
        } else {
            escaped += c;
        }
    }
    return escaped;
}

std::string find_in_path(const std::string& app) {
    std::string cmd = "which " + app + " 2>/dev/null";
    std::array<char, 4096> buffer;
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    if (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result = buffer.data();
        if (!result.empty() && result.back() == '\n')
            result.pop_back();
    }
    pclose(pipe);

    return shell_escape_spaces(result);
}
int checkIfAppOpen(){

    std::vector<std::string> clients;
    char buffer[4096];
    FILE* pipe = popen("hyprctl clients", "r");


    while (fgets(buffer, sizeof(buffer), pipe)) {
        std::string line(buffer);
        if (!line.empty() && line.back() == '\n')
            line.erase(line.size() - 1);
        clients.push_back(line);
    }
    pclose(pipe);
    for( int x = 0; x< clients.size(); x++)
        cout << clients[x] << endl;
    return clients.size();

}

void restore() {
    ifstream readFile("HyprSaveSession.txt");
    string line;
    while(getline(readFile, line)){
        lines.push_back(line);
    }

    int workspace;
    string application;
    int x;
    for(x = 0; x < lines.size() - 1; x=x+26){

        workspace =  stoi(lines[x+5].substr(12,1));

        application = lines[x+9].substr(8);
        cout << "dispatching: " << application << endl;
        dispatch(workspace,application);
    }

}
void save(){
    array<char, 5000> buffer;
    string clients;
    ofstream writeFile("HyprSaveSession.txt");    
    system("hyprctl clients");
    FILE* pipe = popen("hyprctl clients","r");
    if(!pipe){

    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        clients += buffer.data();
    }
    writeFile << clients;
    writeFile.close();




}
