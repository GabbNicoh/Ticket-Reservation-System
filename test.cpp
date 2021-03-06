#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<fstream>
#include<stdlib.h>
using namespace std;

void welcome(void), menu(void), options(void), search(void), removeFromFile(void), quit(void);
void reserve(int row, char column, int type);
void addToFile(string name, string reservedSeat);
fstream file;
// try to put this inside a function
struct mainSeat{
    const char *upuan[6][6] = {{"   ", "A", "B", "C", "D", "E"},
                               {"1 |", "O", "O", "O", "O", "O"},
                               {"2 |", "O", "O", "O", "O", "O"},
                               {"3 |", "O", "O", "O", "O", "O"},
                               {"4 |", "O", "O", "O", "O", "O"},
                               {"5 |", "O", "O", "O", "O", "O"}};

    const char *names[6][6] ={{"|  ", "     ", "     ", "     ", "     ", "     "},
                              {"|  ", "     ", "     ", "     ", "     ", "     "},
                              {"|  ", "     ", "     ", "     ", "     ", "     "},
                              {"|  ", "     ", "     ", "     ", "     ", "     "},
                              {"|  ", "     ", "     ", "     ", "     ", "     "},
                              {"|  ", "     ", "     ", "     ", "     ", "     "}};
};

mainSeat *ms, s;

int main(){
    do{
        options();
    }
    while(true);

    return 0;
}

void welcome(void){
    system("cls");
    char dash[] = "       -------------------------------------------------\n";
    cout << "\n\n"<< dash << "                 BARRIOS Reservation Services!\n" << dash;
}

void menu(void){
    ms = &s;
    cout << "\n\n| Below are the available seats for today: \n" << endl;
    cout << "       ----------------------------------------------\n";
    cout << "       |                   SCREEN                   |\n";
    cout << "       ----------------------------------------------\n";
    for (int x = 0; x < 6; x++){
        cout << "\n            ";
        for(int y = 0; y < 6; y++){
            cout << (*ms).names[x][y] << " ";
        }
            cout << "  |";
        cout << "\n          ";
        for(int y = 0; y < 6; y++){
            cout << (*ms).upuan[x][y] << "     ";
            if (x==0 && y==5)cout<<"\n            -------------------------------------";
        }
            if(x==0) continue;
            cout << "| " << x;
        
    }
    cout<<"\n            -------------------------------------";
    cout << "\n\n            Legend: O = Available        X = Taken";
}

void options(void){
    system("cls");
    welcome();
    int option;
    cout << "\n              | 1. Search a seat\n              | 2. Reserve a seat"
    <<      "\n              | 3. Cancel the reservation\n              | 4. Quit\n" << endl;
    
    cin >> option;

    if(option == 1) search();
    else if(option == 2) search();
    else if(option == 3) removeFromFile();
    else if(option == 4) quit();
    else cout << "Please enter a valid value";
    option = 0;
}

void search(){
    system("cls");
    menu();
    int r;
    char c;
        cout << "\n\n| Please search for a seat number\n Enter your desired row: ";
        cin >> r;
        cout << " Enter your desired column: ";
        cin >> c;

    cout << "\n| You entered seat: " << r << c;
    reserve(r,c,1);
}

void reserve(int row, char column, int type){
    ms = &s;
    int newColumn;
    char toReserve;
    
    column = toupper(column);

    if(column == 'A') newColumn = 1;
    if(column == 'B') newColumn = 2;
    if(column == 'C') newColumn = 3;
    if(column == 'D') newColumn = 4;
    if(column == 'E') newColumn = 5;

    // dito i seset kung i rereserve ba or hindi
    string reservedSeat = to_string(row) + column;
    if(type==1){
         if((*ms).upuan[row][newColumn] == "O"){
        cout << "\n This seat is available!\n Would you like to reserve it? (y/n)\n";
        // enter y/n to continue then run addToFile
            cin >> toReserve;
            if(toReserve == 'y'){
                (*ms).upuan[row][newColumn] = "X";
                
                string name;
                cout << " Enter your name: ";
                cin >> name;
                transform(name.begin(), name.end(), name.begin(), ::toupper);
                (*ms).names[row][newColumn] = name.c_str();
                
                addToFile(name, reservedSeat);
            }else options();
        }
        else if ((*ms).upuan[row][newColumn] == "X"){
            cout << "\n I'm sorry but this seat is already taken.\n Would you like to reserve somewhere else? (y/n)";
            cin >> toReserve;
            if(toReserve == 'y'){
                search();
            }else options();
        }
    }
    else if(type==2){
        // change from x to o
        for (int x = 1; x < 6; x++){
            for(int y = 1; y < 6; y++){
                if((*ms).upuan[x][y] == "X"){
                    (*ms).upuan[x][y] = "O";
                    (*ms).names[x][y] = "     ";
                }
            }
        }
    }
    else if(type == 3){
        // recommend some seats
        int seatLoop;
        char reservation, reverseColumn;
        cout << "\nHow many seats do you wish to reserve?" << endl;
            cin >> seatLoop;
        for(int x = 0; x < seatLoop; x++){
            char next;
            cout << "Recommended seats are: " << endl;
            if((*ms).upuan[row][newColumn] == "O"){
                if(newColumn == 1) reverseColumn = 'A';
                if(newColumn == 2) reverseColumn = 'B';
                if(newColumn == 3) reverseColumn = 'C';
                if(newColumn == 4) reverseColumn = 'D';
                if(newColumn == 5) reverseColumn = 'E';

                cout << row << reverseColumn << endl;
                newColumn++;
            }
        }
        cout << "\nContinue to reservation? (y/n)" << endl;
        cin >> reservation;
        reservation == 'y' ? options() : options();
    }
}

void addToFile(string name, string reservedSeat){
    system("cls");
    int question;
    // add to txt file
    file.open("Reservation Database", ios::out | ios::app);
        file << "Customer Name: " << name << "\nSeat: "<< reservedSeat << endl;
    file.close();

    cout << "\n| 1. Go back to options" << endl;
    cin >> question;
    question == 1 ? options() : options();
}

void removeFromFile(){
    system("cls");
    int r;
    char c;
    string name;
    cout << "| Please enter the name of the reservation holder" << endl;
    cin >> name;
        file.open("Reservation Database", ios::in);
            string laman;
            if(file.good()){
                cout << "\n "<< name << "'s Reservation is: " << endl;
                while(file.good()){
                    getline(file, laman);
                    cout << "  "<< laman << endl;
                }
            }else if(!file.good()){
                char blank;
                cout << "This user has no reservation.\nPlease enter a different name: " << endl;
                cin >> blank;
                removeFromFile();
            }
        file.close();
    char toDelete;
    cout << "| Would you like to cancel your reservation? (y/n)" << endl;
    char cancel;
        cin >> cancel;
    if(cancel=='y'){
        remove("Reservation Database");
        reserve(1, 'A', 2);
        cout << "\n...Processing\n\n...Processing Complete\n\nReservation has been deleted" << endl; 
    }
    char another;
    cout << "\n Go back to main menu? (y/n)" << endl;
        cin >> another;
    another == 'y' ? options() : removeFromFile();
}
void quit(void){
    system("cls");
    cout << "Thank you for using BARRIOS Reservation Services!\n\n" << endl;
    exit(0);
}

/* 
    PROBLEMS: 
    struct


    # add color
        \033[0m
        \033[31m
        
            black - 30
            red - 31
            green - 32
            brown - 33
            blue - 34
            magenta - 35
            cyan - 36
            lightgray - 37

    # A WAY TO ADD X AMOUNT OF SPACES OR REMOVE X AMOUNT OF SPACES DPENDING ON THE NEEDED SPACE
    # when exit print the receipt
    # change spacing of array strings
    # separate function for search? search function suggests seats
    # 
    # please enter how many seats you wish to delete then loop in for loop   

    # loop so that the number of arrays are looping inside the for loop so all the content are in the loop
    # improve the row and column part
    # improve the yes/no
    1.	Menu: 
        Search - seat if available to reserve, 
        Reserve - input your name and the selected seat number, Reserve seat individual and by group (enter names based on the number of seats).
        Cancel/Delete Reservation Record – remove the name and the seat should be available again.
        View Record - names, seat number
        Exit.
    2.	Input Data: Name and seat number
    3.	Calculated data change status if reserve or not
    4.	Calculated behavior is checking for continuous seats  e.g. 2 seats, 3 seats, 4 seats, etc.
    5.	Data for system should be saved on a flat file e.g. text file or txt files.
    6.	System can accept multiple reservation.
    7.	Design your own Menu.
*/