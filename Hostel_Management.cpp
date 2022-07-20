#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;
char numbers[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

vector<string>V1, V2, V5, V6, V7, V8;
vector<int>V3, V4, V9;

//admin

class admin{
public:
    string uN, p_W;
    int Login();
    int adminView();
    int checkListOfRoom();
    void deleteRoom();
};

int admin::Login(){
    tag:
    system("clear");
    cout<<"\n -------------------- Admin Login -----------------\n\n";
    cout<<"Enter username: "; cin>>uN;
    cout<<"Enter password: "; cin>>p_W;
    int n[2], i, x;
    for (i = 0; i < 2; i++)
    {
        x=rand()%10;
        n[i]=x;
    }
    int sm, smtmp;
    sm=n[0]+n[1];
    cout<<"Check if you are not a robot:\n";
    cout<<n[0]<<" + "<<n[1]<<" = ";
    cin>>smtmp;
    if(smtmp==sm){
        if(uN=="inha" && p_W=="inha"){
            adminView();
            getchar();
        }
        else{
            cout<<"\nError, Invalid 'username' or 'password'.\n";
            getchar(); getchar();
        }
    }
    else{
        cout<<"Error, Press any key to continue...";
        getchar(); getchar();
        goto tag;
    }
    return 0;
}

int admin::adminView(){
    int goBack=0;
    while(1){
        system("clear");
        cout<<"\n[1] Check List of Booked Rooms.";
        cout<<"\n[2] Delete Booked Rooms.";
        cout<<"\n[0] Go Back.\n";
        int choice;
        cout<<"Your choice...\n> "; cin>>choice;

        switch(choice){
            case 1:
                checkListOfRoom();
                break;
            case 2:
                deleteRoom();
                break;
            case 0:
                goBack=1;
                break;
            default:
                cout<<"\nInvalid choice, Enter again...\n> ";
                getchar();
        }
        if(goBack==1){
            break;
        }
    }
    return 0;
}

void admin::deleteRoom(){
    int flag=0;
    int ctr=0;
    string line, b_name;
    cout<<"Enter the first name of a person whose\nbooked room"<<
    " will be deleted: "; cin>>b_name;
    ifstream fin;
    ofstream fout;
    fin.open("save.csv", ios::in);
    if(!fin){
        cout<<"\nFile not found!";
        cout<<"\nPress any key to continue... \n";
        getchar(); getchar();
    }
    else{
        fout.open("tempfile.csv", ios::out);
        fin.seekg(0);
        while(!fin.eof()){
            int i=0;
            getline(fin,line,'\n');
            string s="";
            while(line[i] != ','){
                s+=line[i];
                i++;
            }
            if(s!=b_name){
                if(flag==0){
                    fout<<line<<endl;;
                    flag=1;
                }
                else{
                    fout<<endl<<line;
                }
            }
            else if(s==b_name){
                ctr++;
            }
        }
        fin.close();
        fout.close();
        remove("save.csv");

        rename("tempfile.csv", "save.csv");
        if(ctr==0){
            cout<<"\nCannot delete record.\n";
            cout<<"Record not found!\n";
            cout<<"Press any key ro continue...\n";
            getchar(); getchar();
        }
        else{
            cout<<"Deletion seccessful !\n";
            cout<<"Press any key to continue...\n";
            getchar(); getchar();
        }
    }
}

int admin::checkListOfRoom(){
    cout<<"\n ---------- List of Booked Rooms ----------- \n";
    ifstream read;
    read.open("save.csv");
    string line;
    while(read.good()){
        getline(read,line,',');
        if(line=="")break;
        cout<<"First name : "<<line<<endl;
        getline(read,line,',');
        cout<<"Last name : "<<line<<endl;
        getline(read,line,',');
        cout<<"Password : "<<line<<endl;
        getline(read,line,',');
        cout<<"Age : "<<line<<endl;
        getline(read,line,',');
        cout<<"Date : "<<line<<endl;
        getline(read,line,',');
        cout<<"Days : "<<line<<endl;
        getline(read,line,',');
        cout<<"City : "<<line<<endl;
        getline(read,line,',');
        cout<<"Room Type : "<<line<<endl;
        getline(read,line,'\n');
        cout<<"Price : "<<line;
        cout<<"\n--------------------------------------------------------------------------------------------------------\n";
    }
    read.close();
    cout<<"\nPlease enter any key to continue...\n> ";
    getchar(); getchar();
    return 0;
}

//customer

class customer{
public:
    int age, day, payment, price;
    string fname, lname, r_place, pword, date, c_num, pass;
    string name;
    int ch;
    int Login();
    void main_menu();
    void booking();
    void information();
    void save_booking_data(const string &f_n, const string &l_n, const int &a,
    const int &d, const string &r_p, const string &p_w, const string &t,
    const int &p);
};

int customer::Login(){
    system("clear");
    cout<<"\n-- 'Grimuar' Hostel --";
    cout<<"\n---- User System -----\n";
    main_menu();
    return 0;
}

void customer::main_menu(){
    customer c1;
    int choice;
    cout<<"\n";
    cout<<"Hello, Would you like to..." "\n\n";
    cout<<"[1] Book a Room." "\n";
    cout<<"[2] See your booked room's info." "\n";
    cout<<"[3] Exit.\n";
    cout<<"> "; cin>>choice;
    
    switch (choice){
        case 1:
            c1.booking();
            break;
        case 2:
            c1.information();
            break;
        case 3:
            break;
        default:
            getchar();
    }
}

void customer::booking(){
    system("clear");
    cout<<"\n\t[1] 'SINGLE' for $35 a day\n";
    cout<<"\t[2] 'DOUBLE' for $50 a day\n";
    cout<<"\t[4] 'FAMILY' for $65 a day\n";
    cout<<"\t[5] 'VIP' for $100 a day\n";
    cout<<"Your choice...\n> "; cin>>ch;
    if(ch>0&&ch<6){    
        cout<<"First Name: "; cin>>fname;
        cout<<"Last Name: "; cin>>lname;
        cout<<"Enter password: "; cin>>pword;
        cout<<"Your age: "; cin>>age;
        cout<<"Your residental place: "; cin>>r_place;
        cout<<"Enter the date as (dd/mm/yyyy): "; cin>>date;
        cout<<"How many days: "; cin>>day;
        cout<<"[1]Card / [2] Cash...\n> "; cin>>payment;
        if(payment==1){
            switch (ch)
            {
            case 1:
                price=day*35;
                break;
            case 2:
                price=day*50;
                break;
            case 3:
                price=day*65;
                break;
            case 4:
                price=day*100;
                break;
            }
            cout<<"Payment = $"<<price<<"\n";
            cout<<"Enter card number: "; cin>>c_num;
            cout<<"Enter card password: "; cin>>pass;
            cout<<"THANKS FOR YOUR ATTENTION!!!\n";
            cout<<"Enter any key, to go to menu...\n> ";
            getchar(); getchar();
        }
        else if(payment==2){
            switch (ch)
            {
            case 1:
                price=day*35;
                break;
            case 2:
                price=day*50;
                break;
            case 3:
                price=day*65;
                break;
            case 4:
                price=day*100;
                break;
            }
            cout<<"Payment = $"<<price<<"\n";
            cout<<"Here is our bank number, 12345678, You should pay for this...\n";
            cout<<"THANKS FOR YOUR ATTENTION!!!\n";
            cout<<"Enter any key, to go to menu...\n> ";
            getchar(); getchar();
        }
        else{
            getchar(); getchar();
        }
    }
    save_booking_data(fname, lname, age, day, r_place, pword, date, price);
}

void customer::save_booking_data(const string &f_n, const string &l_n, const int &a,
const int &d, const string &r_p, const string &p_w, const string &t,
const int &p){
    int i=0;
    ofstream book;
    book.open("save.csv", ios::app);
    V1.push_back(f_n); V2.push_back(l_n); V3.push_back(a);
    V4.push_back(d); V5.push_back(r_p);
    switch (ch)
    {
    case 1:
        V6.push_back("SINGLE");
        break;
    case 2:
        V6.push_back("DOUBLE");
        break;
    case 3:
        V6.push_back("FAMILY");
        break;
    case 4:
        V6.push_back("VIP");
        break;
    }
    V7.push_back(p_w);
    V8.push_back(t);
    V9.push_back(p);
    cout<<V1[i]<<","<<V2[i]<<","<<V3[i]<<","<<V4[i]<<","<<V5[i]<<","<<V6[i]<<","<<V7[i]<<","<<V8[i]
    <<","<<V9[i]<<"\n";
    book<<"DATA:\n";
    book<<V1[i]<<","<<V2[i]<<","<<V7[i]<<","<<V3[i]<<","<<V8[i]<<",";
    book<<V4[i]<<","<<V5[i]<<","<<V6[i]<<","<<V9[i]<<"\n\n";
    i++;
    book.close();
}

void customer::information(){
    customer c2;
    string f="";
    string p="";
    string f_name, password;
    cout<<"Enter your first name: "; cin>>f_name;
    cout<<"Enter the password: "; cin>>password;
    ifstream read;
    read.open("save.csv");
    string line;
    while(read.good()){
        getline(read,line,',');
        if(line=="")break;
        cout<<"First name : "<<line<<endl;
        getline(read,line,',');
        cout<<"Last name : "<<line<<endl;
        getline(read,line,',');
        cout<<"Password : "<<line<<endl;
        getline(read,line,',');
        cout<<"Age : "<<line<<endl;
        getline(read,line,',');
        cout<<"Date : "<<line<<endl;
        getline(read,line,',');
        cout<<"Days : "<<line<<endl;
        getline(read,line,',');
        cout<<"City : "<<line<<endl;
        getline(read,line,',');
        cout<<"Room Type : "<<line<<endl;
        getline(read,line,'\n');
        cout<<"Price : "<<line;
        cout<<"\n--------------------------------------------------------------------------------------------------------\n";
        read.close();
        cout<<"\nPlease enter any key to continue...\n> ";
        getchar(); getchar();
    }
}

void G_Info(){
	system("clear");
	char a;
	cout<<"_____________________________________________________________________________________________________________________________________________________________\n"<<endl;
	cout<<"\t\t\t\t\t'Grimuar' HOSTEL ROOMS...\n\n\n";
	cout<<"Single room";
	cout<<"\t\tPrice Per Day|";
	cout<<"\tDouble room";
	cout<<"\t\tPrice Per Day|";
	cout<<"\tFamily room";
	cout<<"\t\tPrice Per Day|";
    cout<<"\tVip room";
    cout<<"\t\tPrice Per Day|"<<endl;
    cout<<"Number 101 (non booked)       $35    |";
    cout<<"\tNumber 201  (non booked)      $50    |";
    cout<<"\tNumber 301 (non booked)       $65    |";
    cout<<"\tNumber 401 (booked)           $100   |"<<endl;
    cout<<"Number 102 (non booked)       $35    |";
    cout<<"\tNumber 202  (non booked)      $50    |";
    cout<<"\tNumber 301 (booked)           $65    |";
    cout<<"\tNumber 402 (non booked)       $100   |"<<endl;
    cout<<"Number 103 (non booked)       $35    |";
    cout<<"\tNumber 203  (non booked)      $50    |";
    cout<<"\tNumber 303 (non booked)       $65    |";
    cout<<"\tNumber 403 (non booked)       $100   |"<<endl;
    cout<<"Number 104 (booked)           $35    |";
    cout<<"\tNumber 204  (booked)          $50    |";
    cout<<"\tNumber 304 (non booked)       $65    |"<<endl;
    cout<<"Number 105 (non booked)       $35    |";
    cout<<"\tNumber 205 (booked)           $50    |";
    cout<<"\tNumber 305 (non booked)       $65    |"<<endl;
    cout<<"_____________________________________________________________________________________________________________________________________________________________\n"<<endl;
    cout<<"Enter any key to go back: ";
    getchar(); getchar();
}

int main(){
    customer c;
    admin a;
    int choice;
    system("clear");
    while(1){
        system("clear");
        cout<<"\n\t\t\t***************************************\n";
        cout<<"\t\t\t****WELCOME TO THE 'Grimuar' HOSTEL****\n";
        cout<<"\t\t\t***************************************\n\n\n";
        cout<<"1.Administrative System.\n";
        cout<<"2.User System.\n";
        cout<<"3.General Information.\n";
        cout<<"0.Exit.\n\n";
        cout<<"Enter your choice: "; cin>>choice;
        switch(choice){
            case 1:
                a.Login();
                break;
            case 2:
                c.Login();
                break;
            case 3:
                G_Info();
                break;
            case 0:
                while(1){
                    system("clear");
                    cout<<"\n\tAre you sure, you want to exit? y | n\n";
                    char ex;
                    cin>>ex;
                    if(ex=='y' || ex=='Y'){
                        exit(0);
                    }
                    else if(ex=='n' || ex == 'N'){
                        getchar(); getchar();
                        break;
                    }
                    else{
                        cout<<"\n\tInvalid choice;\n";
                        getchar();
                    }
                }   break;
            default:
                getchar();
        }
    }
    return 0;
}
