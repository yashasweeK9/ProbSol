#include <bits/stdc++.h>
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <fstream>
#include <string>

using namespace std;

// Definations

#define l << "\n" << 
#define cl cout << flush; system("CLS");
#define spt session_paperTag 
#define sy session_year
#define res response = "";

const int headMenuLine =    13;
const int tailMenuLine =    7;
const int dpLines =         100;
const int dlLines =         38;
const int cfLines =         4;
const int ansLines =        13;
const int editLines =       83;
const int rbooks =          3;

int session_year;
string session_paperTag = ""; 

//Each Information on the Application is mapped to their Respective ZIO CODE
map<int,string>pC; 
map<string,string>dl;   //Question Paper & Solution Keys Links
map<string,string>cf;   //Cutoffs
map<string,string>dp;   //All Strings That Are Either Prompted OR Labled
map<string,string>ans;
map<string,string>ed;
map<string,string>book;

//Function Definitions

void initializer(); //Calls all the Respective Databases to Load in the Local Memory
void dLoad();
void cfLoad();
void dpLoad();
void ansLoad();
void editLoad();
void bookLoad();

bool download(string qTag, string response);
bool redirect(string yTag, string qTag);

string fetchCutoff(string yTag, string std);
string fetchAnswer(string yTag, string qTag, string tcTag);
string toggleU(string input);
string drawLine(string x);

void transfer(string destination);
void downloadQPaper();
void downloadSPaper();
void getRBooks();
void getCutoff();
void getEditorial();
void help(int state);
void settings();

bool download(string Tag, string response) { // response = B for Books // response = Q for Question Paper // response = S for Solutions 
    string dwnld_URL = "";
    if(response=="B") {
        Tag = "ZIOrbook"  + Tag;
        dwnld_URL = book[Tag];
    } else {
        if(Tag.length()>7)
            Tag = Tag.substr(0,Tag.length()-2)+response;
        else if(Tag.length()==7)
            Tag = Tag + response;
        else
            return false;
        dwnld_URL = dl[Tag];
    }
    ShellExecuteA(NULL, "open", dwnld_URL.c_str(), NULL, NULL, SW_SHOWNORMAL);
    return true; 
}

bool redirect(string yTag, string qTag) {
    string url = "ZIO"+yTag+"Q"+qTag;
    url = ed[url];
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
    return true;    
}

string fetchCutoff(string yTag, string std) { 
    if(yTag.length()>7)
        yTag = yTag.substr(0,yTag.length()-2);
    std = toggleU(std);
    if(std=="TWELVE"||std=="12"||std=="XII") //Normalizing The Class
        std = "12";
    else if(std=="ELEVEN"||std=="11"||std=="XI") 
        std = "11";
    else if(std=="TEN"||std=="10"||std=="X")
        std = "10";
    else if(std=="NINE"||std=="09"||std=="IX"||std=="9")
        std = "09";
    else
        return "";
    return cf[yTag+std];
}

string fetchAnswer(string yTag, string qTag, string tcTag) {
    return ans["ZIO"+yTag+"Q"+qTag+"T"+tcTag];
}

string toggleU(string input) {
    transform(input.begin(),input.end(),input.begin(),::toupper);
    return input;
}

string drawLine(string x) {
    string ld = "+";
    for(int i=0; i<x.length()-2;i++)
        ld+="-";
    return ld+"+";
}

void dLoad() {
    string line = "";
    ifstream file ("dl.txt");
    if (file.is_open()) {
        for (int lineno = 0; getline (file,line) && lineno < dlLines; lineno++) {
            int n = line.find(" ");
            string code = line.substr(0, n);
            dl[code]=line.substr(n+1,line.length());
        }
        file.close();
    }
}

void cfLoad() {
    string line = "";
    ifstream file ("cutoff.txt");
    if (file.is_open()) {
        for (int lineno = 0; getline (file,line) && lineno < cfLines; lineno++) {
            int n = line.find(" ");
            string code = line.substr(0, n);
            cf[code]=line.substr(n+1,line.length());
        }
        file.close();
    }
}

void dpLoad() {
    string line = "";
    ifstream file ("display.txt");
    if (file.is_open()) {
        for (int lineno = 0; getline (file,line) && lineno < dpLines; lineno++) {
            int n = line.find(" ");
            string code = line.substr(0, n);
            dp[code]=line.substr(n+1,line.length());
        }
        file.close();
    }
}

void ansLoad() {
    string line = "";
    ifstream file ("answer.txt");
    if (file.is_open()) {
        for (int lineno = 0; getline (file,line) && lineno < ansLines; lineno++) {
            int n = line.find(" ");
            string code = line.substr(0, n);
            ans[code]=line.substr(n+1,line.length());
        }
        file.close();
    }
}

void editLoad() {
    string line = "";
    ifstream file ("editorial.txt");
    if (file.is_open()) {
        for (int lineno = 0; getline (file,line) && lineno < editLines; lineno++) {
            int n = line.find(" ");
            string code = line.substr(0, n);
            ed[code]=line.substr(n+1,line.length());
        }
        file.close();
    }
}

void bookLoad() {
    string line = "";
    ifstream file ("books.txt");
    if (file.is_open()) {
        for (int lineno = 0; getline (file,line) && lineno < rbooks; lineno++) {
            int n = line.find(" ");
            string code = line.substr(0, n);
            book[code]=line.substr(n+1,line.length());
        }
        file.close();
    }
}

void initializer() {
    dLoad();
    cfLoad();
    dpLoad();
    ansLoad();
    editLoad();
    bookLoad();
}

void transfer(string destination) {
    if(destination=="1")
        downloadQPaper();
    else if(destination=="3")
        getCutoff();
    else if(destination=="6")
        getEditorial();
    else if(destination=="11")
        getRBooks();
}

void help(int state) { 

    if(state==-1) {
        //Tell The User There is no Problem
    }
    else if(state==0) {
        //Show the User the Power of Your Program
    }
        
    else if(state==1) {
        cout << dp["help10"] l drawLine(dp["help10"]) l dp["help11"] l dp["help12"] l dp["help13"] l dp["help14"] l dp["help15"] l dp["help16"] << "\n";
    }

    else if(state==2) {
        //Tell the User why his download could not be done.
    }

    else if(state==3) {
        // Class Code does not match
    }

    else if (state==5) {
        cout << dp["help50"] l drawLine(dp["help50"]) l dp["help51"] l dp["help52"];
    }

    else if(state==6) {
        //Typeing error maybe in VERIFY & ANSWER
    }

    else if(state==7) {
         cout << dp["help70"] l drawLine(dp["help70"]) l dp["help71"] l dp["help72"] l dp["help73"] << "\n";
    }

    else if(state==8) {
        // Such content does not exists in the Menu
    }
     else if (state==9) {
         cout << dp["help90"] l drawLine(dp["help90"]) l dp["help91"] l dp["help92"] l dp["help93"];
     }
}

void settings() {

}

void downloadQPaper() {
    cl
    if(download(spt,"Q"))
        cout << dp["rbooksuccess"] l drawLine(dp["rbooksuccess"]) l dp["dwnFileTrue1"] l dp["dwnFileTrue2"] l "\n";
    else
        help(2);
}

void downloadSPaper() {
    cl
    if(download(spt,"S")) 
        cout << dp["rbooksuccess"] l drawLine(dp["rbooksuccess"]) l dp["dwnFileTrue1"] l dp["dwnFileTrue2"] l "\n";
    else
        help(2);
}

void getVerifyAnswer() {
    cl;
    string res
    cout << dp["confirmQPrompt"] << sy <<"\n" << dp["confirmQLabel"];
    cin >> response;
    if(response=="1"||response=="2"||response=="3"||response=="4"||response=="5"||response=="6") {
        string qTag = response;
        res
        cl
        cout << dp["confirmTcPrompt"] << qTag <<"\n" << dp["confirmTcLabel"];
        cin >> response;
        if(response=="1"||response=="2"||response=="3") {
            string tcTag = response;
            res cl
            cout << dp["confirmAPrompt1"] << sy << " Q." << qTag << " T." << tcTag l dp["confirmAPrompt2"] l dp["confirmALabel"];
            cin >> response;
            response = toggleU(response);
            string prev_guess = "N/A";
            if(response=="VERIFY"||response=="1"||response=="VER") {
                bool cont = false;
                int corAns = stoi(fetchAnswer(to_string(sy),qTag,tcTag));
                int guessAns;
                do {
                    cont = false;
                    cl
                    cout << dp["prevGuessLabel"] << prev_guess << " *\n";
                    cout << dp["guessPrompt"] l dp["guessLabel"];
                    cin >> guessAns;
                    if(guessAns!=corAns) {
                        cout << dp["wrongAnsLabel"] << "\n";
                        cout << dp["wrongAnsContinuePrompt"] l dp["wrongAnsContinueLabel"];
                        res
                        cin >> response;
                        response = toggleU(response);
                        if(response=="YES"||response=="1"||response=="A") {
                            prev_guess = to_string(guessAns);
                            cont = true;
                            continue;
                        }
                        else if(response=="NO"||response=="2"||response=="B") {
                            cont = false;
                            continue;
                        }

                        else {
                            break;
                        }           
                    }
                    else {
                        cout << dp["corAnsLabel"] << "\n";
                        break; 
                    }
                } while(cont);

                cout << dp["neuAnsQPrompt"]+"\n"+dp["neuAnsQLabel"];
            }
            else if(response=="ANSWER"||response=="2"||response=="ANS") {
                cout << fetchAnswer(to_string(sy),qTag,tcTag);
            }
            else {
                help(6);
            }
        }
    }
}

void openDocument() {
    char buff[PATH_MAX];
    _getcwd( buff, PATH_MAX );
    string current_working_dir(buff);
    string url = "";
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void getCutoff() {
    cl;
    string response = "";
    cout << dp["stdPrompt"] l dp["stdInputLabel"];
    cin >> response;
    string cutf = fetchCutoff(spt,response);
    if(cutf!="") {
        cout << dp["cfAnsLabel1"] << sy l dp["cfAnsLabel2"] << response << dp["cfAnsLabel3"] << cutf l dp["cfAnsLabel4"];
        float cutfPercent = (stoi(cutf)/80)*100;
        printf("%2f",cutfPercent); cout << dp["cfAnsLabel5"] << "\n";
    }
    else
        help(3);
}

void getEditorial() {
    string response = "";
    cl;
    cout << dp["confirmQPrompt"] << sy <<"\n" << dp["confirmQLabel"];
    cin >> response;
    if(response=="1"||response=="2"||response=="3"||response=="4"||response=="5"||response=="6") {
        cl;
        if(redirect(to_string(sy),response))
            cout l dp["loadFileTrue1"] l dp["loadFileTrue2"] << "\n";
        else
            help(4);
    }
}

void getRBooks() {
    cout << dp["rbookmenu0"] l drawLine(dp["rbookmenu0"]);
    for(int i=1;i<=rbooks;i++) {
        string index = to_string(i);
        if(i>9)
            cout << "\n *  (" << index << ") > " << dp["rbookmenu"+index];  
        else
            cout << "\n *  (" << "0"+index << ") > " << dp["rbookmenu"+index];    
    }
    cout l drawLine(dp["rbookmenu0"]) l dp["rbooklabel"]; 
    string response = "";
    cin >> response; cout << drawLine(dp["rbooklabel"]);
    if(book["ZIOrbook"+response]!="") {
        download(response,"B");
        cl;
        cout << dp["rbooksuccess"] l drawLine(dp["rbooksuccess"]) l dp["dwnFileTrue1"] l dp["dwnFileTrue2"] l "\n";
    } else {
        cl;
        help(9);
    }
}

int main() {
start:
    initializer();
    system("CLS");
    string menu = "";
    string tailMenu = "";
    string session_state = "0";
    
    for(int i=0;i<=tailMenuLine;i++) {
            tailMenu = tailMenu + dp["tailmenuPrompt"+to_string(i)] + "\n";
        }
    tailMenu = tailMenu + dp["tailLabel"];
    cout << flush; cout << dp["startLabel"];
    string input; cin >> input; input = toggleU(input);

    if(input=="H" || input=="HELP") {
        help(0);
    }

    else if(input=="S" || input=="SETTINGS" || input=="SET") {
        settings();
    }

    else {
        
        sy = -1;
        
        for(int i=2002;i<=2020;i++) {
            size_t found = input.find(to_string(i)); 
            if (found != string::npos) 
            sy = i;
        }
        
        if(sy!=-1) {
            
            string response = "";

            for(int i=0;i<=headMenuLine;i++) {
                menu = menu + dp["menuPrompt"+to_string(i)] + "\n";
            }
            menu = menu +  dp["headLabel"];
            spt = "ZIO"+to_string(sy);
            cout << menu;
            cin >> response; response = toggleU(response);
            cl
            if(response=="1" || response=="A" || response=="QUESTION PAPER") {
                    response = "1";
                    session_state = response;
                    downloadQPaper();
                }

            else if(response=="2" || response=="B" || response=="SOLUTION KEY") {
                response = "2";
                session_state = response;
                downloadSPaper();
            }
            
            else if(response=="3" || response=="C" || response=="CUTOFF") {
                response = "3";
                getCutoff();
                session_state = response;
            }

            else if(response=="5" || response=="E" || response=="ANSWER") {
                response = "5";
                session_state = response;
                getVerifyAnswer();                
            }

            else if(response=="6" || response=="F" || response=="EDITORIAL") {
                response = "6";
                session_state = response;
                getEditorial();
            }
            
            else if(response=="11"|| response=="K" || response=="BOOKS") {
                response = "11";
                session_state = response;
                getRBooks();
                
            }
            
            else if(response=="4"||response=="7"||response=="8"||response=="9"||response=="10") {
                help(7);
            }
            
            else if(response=="12" || response=="L" || response=="EXIT" || response=="QUIT") {
                system("exit");
            }

            else {
                help(9);
            }
        }
        else {
            help(1);
        }       
    }

tail:

    string resp = "";
    cout << tailMenu;
    cin >> resp;

    if(resp=="1")
        goto start;
    else if (resp=="3") {
        cl;
        cout << dp["devLabel1"] + "\n" + dp["devLabel2"] + "\n" + dp["devLabel3"] + "\n" + dp["devLabel4"] + "\n" + dp["devLabel5"] + "\n" + dp["devLabel6"] + "\n" + dp["devLabel7"] + "\n"; 
        goto tail;
    } else if(resp=="2"||resp=="SUB") { 
        transfer(session_state);
        goto tail;
    } else {
        system("exit");
    }
}