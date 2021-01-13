#include<iostream>
#include<string.h>
using namespace std;

void welcome(void), menu(void), options(void), enter(void), addToFile(void), reviewTheFile(void), removeFromFile(void), quit(void);
void choosing(int row, char column);

// try to put this inside a function
char upuan[6][6] = {{' ', 'A', 'B', 'C', 'D', 'E'},
                       {'1', 'O', 'X', 'O', 'O', 'O'},
                       {'2', 'O', 'O', 'O', 'O', 'O'},
                       {'3', 'O', 'O', 'O', 'O', 'O'},
                       {'4', 'O', 'O', 'O', 'O', 'O'},
                       {'5', 'O', 'O', 'O', 'O', 'O'}};

int main(){
    // intro
    welcome();

    // print menu
    menu();

    // choose between the following
        // reserve
            // reserve seat by individual or by group (multiple reservations)

            // search seat to reserve and how many (loop for how many you want)
            // check if it is avaiable if yes then continue if not then say
            enter();

        // remove
        // view
        // quit
    
    // Do you want to view record and exit or continue reservation

    // delete reservation
    
    // view record and exit. (View record is txt file)
    
    return 0;
}

void welcome(void){
    char dash[] = "-------------------------------------------------\n";
    cout << "\n\n"<< dash << "          BARRIOS Reservation Services!\n" << dash;
}

void menu(void){

    char (*menuPointer)[6];
    menuPointer = upuan;

    cout << "\nBelow are the available seats for today: " << endl;

    for (int x = 0; x < 6; x++){
        cout << "\n                 ";
        for(int y = 0; y < 6; y++){
            cout << menuPointer[x][y] << " ";
        }
    }
    cout << "\n\n                           Legend: O = Available";
    cout << "\n                                   X = Taken";
}

void options(void){
    int option;
    cout << "1. Reserve a seat\n2. Delete a reservation\n3. Review the reservation\n4. Quit";
    cin >> option;

    if(option == 1) enter();
    else if(option == 2) removeFromFile();
    else if(option == 3) reviewTheFile();
    else if(option == 4) quit();
    else cout << "Please enter a valid value";
}

void reviewTheFile(){

}

void enter(){
    int r;
    char c;
        cout << "\n\nPlease search for a seat number\n Enter your desired row: ";
        cin >> r;
        cout << " Enter your desired column: ";
        cin >> c;

    cout << "\nYou entered seat: " << r << c;
    choosing(r,c);
}

void choosing(int row, char column){
    int newColumn;

    if(column == 'A') newColumn = 1;
    else if(column == 'B') newColumn = 2;
    if(column == 'C') newColumn = 3;
    if(column == 'D') newColumn = 4;
    if(column == 'E') newColumn = 5;

    // dito i seset kung i rereserve ba or hindi
    if(upuan[row][newColumn] == 'O'){
        cout << "\n This seat is available!\n Would you like to reserve it?";
        // enter y/n to continue then run addToFile
        addToFile();
    }
    else if (upuan[row][newColumn] == 'X'){
        cout << "\n I'm sorry but this seat is already taken.\n Would you like to reserve something else?";
        enter();
    }
}

void addToFile(void){

}

void removeFromFile(){

}

void quit(void){
    exit(0);
}

/* PROBLEMS: 
    char array
    pointers
*/