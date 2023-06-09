#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <utility>
#include <cmath>
#include <sstream>
#include <array>
#include <vector>
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include <iterator>
#include <ios>
#include <iomanip>
#include <fstream>
using namespace std ;
//********************************************
// todo : declaring the structure
struct Student
{
    string First_name ;
    string Last_name ;
    Student* next{nullptr} ;
};

struct Year
{
    int yeare {} ;
    Year* next {nullptr} ;
    Student* stud {nullptr} ;
};

struct Speciality
{
    string name ;
    Speciality* next{nullptr} ;
    Year* yeare{nullptr} ;
};

struct Department
{
    string name ;
    Department* next{nullptr} ;
    Speciality* spec{nullptr} ;
};

struct Faculty
{
    string name ;
    Faculty* next{nullptr} ;
    Department* dep{nullptr} ;
};
struct University
{
    string name ;
    University* next{nullptr} ;
    Faculty* fac{nullptr} ;
};
typedef University* university_r ;
typedef Faculty* faculty_r ;
typedef Department* Department_r ;
typedef Speciality* Speciality_r ;
typedef Student* Student_r ;
//********************************************
// ! All Searching functions :
// todo : University Search :
University* Search_University (University* univer , string name){
    University* univer_x{univer} ;
    while (univer_x)
    {
        if (univer_x->name == name) return univer_x ;
        univer_x = univer_x->next ;
    };
    if ( !univer_x) return nullptr ;
};
// todo : Faculty Search :
Faculty* Search_Faculty (University* univer , string name){
    Faculty* fac_x{univer->fac};
    while ( fac_x ){
        if ( fac_x->name == name ) return fac_x ;
        fac_x = fac_x->next ;
    };
    if ( !fac_x ) return nullptr ;
};
// todo : Department Search :
Department* Search_Department (Faculty* fac , string name){
    Department* dep_x {fac->dep} ;
    while ( dep_x ) {
        if ( dep_x->name == name ) return dep_x ;
        dep_x = dep_x->next ;
    };
    if ( !dep_x ) return nullptr ;
};
// todo : Speciality Search :
Speciality* Search_speciality (Department* dep , string name){
    Speciality* spec_x {dep->spec} ;
    while ( spec_x ) {
        if (spec_x->name == name) return spec_x ;
        spec_x = spec_x->next ;
    };
    if ( !spec_x ) return nullptr ;
};
// todo : Student Search :
Student* Search_student (Speciality* spec , string first_name , string last_name){
        Year* year_x{spec->yeare} ;
        while ( year_x ){
            Student* stud{year_x->stud} ;
            while (stud){
                if ( (stud->First_name == first_name) && (stud->Last_name == last_name) ) return stud ;
                stud = stud->next ;
            };
            year_x = year_x->next ;
        };
    if ( !year_x ) return nullptr ;
};
//********************************************

// ! all Functions of creeting
// todo : University Creation :
void Creet_university (university_r& univer , string name){
        University* univer_x{new (University)} ;
        univer_x->name = name ;
        univer_x->next = univer ;
        univer = univer_x ;
};
// todo : Faculty Creation :
void Creet_faculty (University* univer , string name){
    Faculty* fac_x {new ( Faculty )} ;
    fac_x->name = name ;
    fac_x->next = univer->fac ;
    univer->fac = fac_x ;
};
// todo : Department Creation :
void Creet_department (Faculty* fac , string name){
    Department* dep_x {new( Department )} ;
    dep_x->name = name ;
    dep_x->next = fac->dep ;
    fac->dep = dep_x ;
};
// todo : Speciality creation :
// todo : and creating 5 years inside it :
void Creet_speciality (Department* dep , string name){
    Speciality* spec_x {new ( Speciality )} ;
    spec_x->name = name ;
    spec_x->next = dep->spec ;
    dep->spec = spec_x ;
    for (int i = 5 ; i > 0 ; i--){
        Year* year_x {new (Year)} ;
        year_x->yeare = i ;
        year_x->next = spec_x->yeare ;
        spec_x->yeare = year_x ;
    };
};
// todo : Student creation :
void Creet_student (Speciality* spec , int year , string first_name , string last_name){
    Year* year_x {spec->yeare} ;
    int i{year} ;
    while (i-1 != 0){
        year_x = year_x->next ;
        i-- ;
    };
    Student* stud_x {new ( Student )} ;
    stud_x->First_name = first_name ;
    stud_x->Last_name = last_name ;
    stud_x->next = year_x->stud ;
    year_x->stud = stud_x ;
};
//********************************************

// ! All function of deleting
// todo : Delete a student :
void Delete_student (Speciality* spec , int year , string first_name , string last_name){
    Year* year_x {spec->yeare} ;
    int i {year} ;
    while (i-1 != 0){
        year_x = year_x->next ;
        i-- ;
    };
    Student* stud_x{year_x->stud} ;
    Student* stud_z{nullptr} ;
    if (stud_x->First_name == first_name && stud_x->Last_name == last_name){
        year_x->stud = year_x->stud->next ;
        delete stud_x ;
        stud_x = nullptr ;
    }else{
        while ( stud_x->next){
            if (stud_x->next->First_name == first_name && stud_x->next->Last_name == last_name){
                stud_z = stud_x->next ;
                stud_x->next = stud_x->next->next ;
                delete stud_z ;
                stud_z = nullptr ;
                stud_x = nullptr ;
            }else stud_x = stud_x->next ;
        };
    };
};
// todo : Delete a speciality :
void Delete_speciality (Department* dep ,string name){
    Speciality* spec_x{dep->spec} ;
    Speciality* spec_z{nullptr} ;
    if (dep->spec->name == name){
        spec_z = dep->spec ;
        dep->spec = dep->spec->next ;
    }else{
        while (spec_x->next){
            if (spec_x->next->name == name){
                spec_z = spec_x->next ;
                spec_x->next = spec_x->next->next ;
                spec_x = nullptr ;
            }else spec_x = spec_x->next ;
        };
    };
    Year* year_x {spec_z->yeare} ;
    Student* stud_x{nullptr} ;
    Student* stud_y{nullptr} ;
    while (year_x){
        stud_x = year_x->stud ;
        while (stud_x){
            stud_y = stud_x ;
            stud_x = stud_x->next ;
            delete stud_y ;
            stud_y = nullptr ;
        };
        year_x->stud = nullptr ;
        spec_z->yeare = spec_z->yeare->next ;
        delete year_x ;
        year_x = spec_z->yeare ;
    };
    delete spec_z ;
    spec_z = nullptr ;
};
// todo : Delete a department :
void Delete_department (Faculty* fac , string name){
    Department* dep_x{fac->dep} ;
    Department* dep_z{nullptr} ;
    if (fac->dep->name == name){
        dep_z = fac->dep ;
        fac->dep = fac->dep->next ;
    }else{
        while (dep_x->next){
            if (dep_x->next->name == name){
                dep_z = dep_x->next ;
                dep_x->next = dep_x->next->next ;
                dep_x = nullptr ;
            }else dep_x = dep_x->next ;
        };
    };
    while (dep_z->spec){
        Delete_speciality( dep_z , dep_z->spec->name ) ;
    };
    delete dep_z ;
    dep_z = nullptr ;
};
// todo : Delete a faculty :
void Delete_faculty (University* univer , string name){
    Faculty* fac_x{univer->fac} ;
    Faculty* fac_z{nullptr} ;
    if (univer->fac->name == name){
        fac_z = univer->fac ;
        univer->fac = univer->fac->next ;
    }else{
        while (fac_x->next){
            if (fac_x->next->name == name){
                fac_z = fac_x->next ;
                fac_x->next = fac_x->next->next ;
                fac_x = nullptr ;
            }else fac_x = fac_x->next ;
        };
    };
    while (fac_z->dep){
        Delete_department( fac_z , fac_z->dep->name ) ;
    };
    delete fac_z ;
    fac_z = nullptr ;
};
// todo : Delete a university :
void Delete_university (university_r& univer , string name){
    University* univer_x{univer} ;
    University* univer_z{nullptr} ;
    if (univer->name == name){
        univer_z = univer ;
        univer = univer->next ;
    }else{
        while (univer_x->next){
            if (univer_x->next->name == name){
                univer_z = univer_x->next ;
                univer_x->next = univer_x->next->next ;
                univer_x = nullptr ;
            }else univer_x = univer_x->next ;
        };
    };
    while (univer_z->fac){
        Delete_faculty( univer_z , univer_z->fac->name) ;
    };
    delete univer_z ;
    univer_z = nullptr ;
};
void Delete_all (university_r& univer){
    while (univer) Delete_university(univer,univer->name) ;
};
//***********************************************************************************************************
// todo : Procedure that writes down the whole structrure :
void Display (University* univer){
    University* univer_x{univer} ;
    while (univer_x){
        cout << "University : " << univer_x->name << '\n' ;
        Faculty* fac_x {univer_x->fac} ;
        while (fac_x){
            cout << setw(15) << setfill(' ') ;
            cout << "Faculty : " << fac_x->name << '\n' ;
            Department* dep_x {fac_x->dep} ;
            while (dep_x){
                cout << setw(20) << setfill(' ') ;
                cout << "Department : " << dep_x->name << '\n' ;
                Speciality* spec_x {dep_x->spec} ;
                while (spec_x){
                    cout << setw(30) << setfill(' ') ;
                    cout << "Speciality : " << spec_x->name << '\n' ;
                    Year* year_x{spec_x->yeare} ;
                    while (year_x){
                        cout << setw(40) << setfill(' ') ;
                        cout << "Year "<< year_x->yeare << " :\n" ;
                        Student* stud_x{year_x->stud} ;
                        while (stud_x){
                            cout << setw(50) << setfill(' ') ;
                            cout << stud_x->Last_name << '_'
                                 << stud_x->First_name << '\n' ;
                            stud_x = stud_x->next ;
                        };
                        year_x = year_x->next ;
                    };
                    spec_x = spec_x->next ;
                };
                dep_x = dep_x->next ;
            };
            fac_x = fac_x->next ;
        };
        univer_x = univer_x->next ;
    };
};
//***********************************************************************************************************
// todo : Save the structure to a file :
void Save_structure (University* univer , string file_name) {
    University* univer_x {univer} ;
    ofstream file_delete(file_name, ofstream::out | ofstream::trunc);
    if (file_delete.is_open()) {
        file_delete.close();
    };
    fstream file ;
    file.open(file_name) ;
    if (file.is_open()){
        while (univer_x){
            file << " | " << univer_x->name ;
            Faculty* fac_x {univer_x->fac} ;
            while (fac_x){
                file << " : " << fac_x->name ;
                Department* dep_x { fac_x->dep } ;
                while (dep_x){
                    file << " , " << dep_x->name ;
                    Speciality* spec_x { dep_x->spec } ;
                    while (spec_x){
                        file << " ; " << spec_x->name ;
                        Year* year_x { spec_x->yeare } ;
                        while (year_x){
                            file << " . " << to_string(year_x->yeare) ;
                            Student* stud_x { year_x->stud } ;
                            while (stud_x){
                                file << " / " << stud_x->Last_name
                                     << " " << stud_x->First_name ;
                                stud_x = stud_x->next ;
                            };
                            year_x = year_x->next ;
                        };
                        spec_x = spec_x->next ;
                    };
                    dep_x = dep_x->next ;
                };
                fac_x = fac_x->next ;
            };
            univer_x = univer_x->next ;
        };
        file << " *Exit*" ;
    };
    file.close() ;
};
// todo : Get the previous structure :
void Get_structure (university_r& univer , string file_name){
    string s = "*Exit*" ;
    University* univer_x { nullptr } ;
    Faculty* fac_x {nullptr} ;
    Department* dep_x {nullptr} ;
    Speciality* spec_x {nullptr} ;
    Year* year_x {nullptr} ;
    Student* stud_x {nullptr} ;
    fstream file ;
    file.open(file_name) ;
    if ( file.is_open() ){
        file >> s ;
        while ( s != "*Exit*" ){
            if ( s == "|"){
                file >> s ;
                univer_x = new University ;
                univer_x->name = s ;
                univer_x->next = univer ;
                univer = univer_x ;
            }else if ( s == ":"){
                file >> s ;
                fac_x = new Faculty ;
                fac_x->name = s ;
                fac_x->next = univer->fac ;
                univer->fac = fac_x ;
            }else if ( s == ","){
                file >> s ;
                dep_x = new Department ;
                dep_x->name = s ;
                dep_x->next = fac_x->dep ;
                fac_x->dep = dep_x ;
            }else if ( s == ";"){
                file >> s ;
                spec_x = new Speciality ;
                spec_x->name = s ;
                spec_x->next = dep_x->spec ;
                dep_x->spec = spec_x ;
            }else if (s == "."){
                file >> s ;
                year_x = new Year ;
                year_x->yeare = stoi(s) ;
                year_x->next = spec_x->yeare ;
                spec_x->yeare = year_x ;
            }else if (s == "/"){
                file >> s ;
                stud_x = new Student ;
                stud_x->Last_name = s ;
                file >> s ;
                stud_x->First_name = s ;
                stud_x->next = year_x->stud ;
                year_x->stud = stud_x ;
            };
            file >> s ;
        };
    };
};
//***********************************************************************************************************
int main () {
    int choose {} ;
    string name , name1 ;
    University* univer{nullptr} ;
    University* univer_y{nullptr} ;
    Faculty* fac_y{nullptr} ;
    Department* dep_y{nullptr} ;
    Speciality* spec_y{nullptr} ;
    Year* year_y{nullptr} ;
    Student* stud_y{nullptr} ;
    Get_structure(univer,"Structure.txt") ;
    if (!univer) cout << "it did not work \n" ;
    do
    {
        cout << setw(50) << setfill('-') << '\n' ;
        cout << "1  : Creet a University\n"
             << "2  : Creet a Faculty\n"
             << "3  : Creet a Department\n"
             << "4  : Creet a Speciality\n"
             << "5  : Creet a Student\n"
             << "6  : Search for a University\n"
             << "7  : Search for a Faculty\n"
             << "8  : Search for a Department\n"
             << "9  : Search for a Speciality\n"
             << "10 : Search for a Student\n"
             << "11 : Delete a given University \n"
             << "12 : Delete a given Faculty \n"
             << "13 : Delete a given Department \n"
             << "14 : Delete a given Speciality \n"
             << "15 : Delete a given Student\n"
             << "16 : Sort the Students of a certain year by last name\n"
             << "17 : write down the whole structrue\n" 
             << "18 : Delete everything\n"
             << "00 : Exit the program\n" ;
        cout << setw(75) << setfill('-') << '\n' ;
        cout << "Choose one of the operations above :\n" ;
        cin >> choose ;
        switch (choose)
        {
        case 1:{
            cout << "Enter the name of the university that you want to creet :\n" ;
            cin >> name ;
            Creet_university(univer,name) ;
        }
            break;
        case 2:{
            another_name2:
            cout << "Enter the name of the University that you want to creet the Faculty in :\n" ;
            cin >> name ;
            univer_y = Search_University(univer,name) ;
            if ( !univer_y) {
                cout << "The university the you entered does not exist\n"
                     << "Do you want to enter another university ?\n"
                     << "1 : Yes\n"
                     << "2 : No,return\n";
                cin >> choose ;
                if (choose == 1) goto another_name2 ;
            }else{
                cout << "Enter the name of the faculty :\n" ;
                cin >> name ;
                Creet_faculty( univer_y , name) ;
            };
        }
            break;
        case 3:{
            another_name3:
            cout << "Enter the name of the University that you want to creet the Department in :\n" ;
            cin >> name ;
            univer_y = Search_University(univer,name) ;
            if ( !univer_y) {
                cout << "The university that you entered does not exist\n"
                     << "Do you want to enter another university ?\n"
                     << "1 : Yes\n"
                     << "2 : No,return\n";
                cin >> choose ;
                if (choose == 1) goto another_name3 ;
            }else{
                another_name4:
                cout << "Enter the name of the faculty that you want to creat the Department in :\n" ;
                cin >> name ;
                fac_y = Search_Faculty(univer_y,name) ;
                if ( !fac_y) {
                    cout << "The faculty you enterer does not exist in "
                         << univer_y->name << " University\n" 
                         << "Do you want to enter another faculty ?\n"
                         << "1 : Yes\n"
                         << "2 : No,return\n" ;
                    cin >> choose ;
                    if ( choose == 1 ) goto another_name4 ;
                }else{
                    cout << "Enter the name of the Depatment :\n" ;
                    cin >> name ;
                    Creet_department (fac_y , name) ;
                };
            };
        }
            break;
        case 4:{
            another_name5:
            cout << "Enter the name of the University that you want to creet the Speciality in :\n" ;
            cin >> name ;
            univer_y = Search_University(univer,name) ;
            if ( !univer_y) {
                cout << "The university that you entered does not exist\n"
                     << "Do you want to enter another university ?\n"
                     << "1 : Yes\n"
                     << "2 : No,return\n";
                cin >> choose ;
                if (choose == 1) goto another_name5 ;
            }else{
                another_name6:
                cout << "Enter the name of the faculty that you want to creat the Speciality in :\n" ;
                cin >> name ;
                fac_y = Search_Faculty(univer_y,name) ;
                if ( !fac_y) {
                    cout << "The faculty you entered does not exist in "
                         << univer_y->name << " University\n" 
                         << "Do you want to enter another faculty ?\n"
                         << "1 : Yes\n"
                         << "2 : No,return\n" ;
                    cin >> choose ;
                    if ( choose == 1 ) goto another_name6 ;
                }else{
                    another_name7:
                    cout << "Enter the name of the Depatment that you want to creat the Speciality in :\n" ;
                    cin >> name ;
                    dep_y = Search_Department(fac_y,name) ;
                    if ( !dep_y) {
                        cout << "The Department you entered does not exist in the faculty of "
                             << fac_y->name << '\n'
                             << "Do you want to enter another department ?\n"
                             << "1 : Yes\n"
                             << "2 : No,return\n" ;
                        cin >> choose ;
                        if ( choose == 1 ) goto another_name7 ;
                    }else{
                        cout << "Enter the Speciality name : \n" ;
                        cin >> name ;
                        Creet_speciality ( dep_y , name ) ;
                    };
                };
            };
        };
            break;
        case 5:{
            another_name8:
            cout << "Enter the name of the University that you want to creet the Student in :\n" ;
            cin >> name ;
            univer_y = Search_University(univer,name) ;
            if ( !univer_y) {
                cout << "The university that you entered does not exist\n"
                     << "Do you want to enter another university ?\n"
                     << "1 : Yes\n"
                     << "2 : No,return\n";
                cin >> choose ;
                if (choose == 1) goto another_name8 ;
            }else{
                another_name9:
                cout << "Enter the name of the faculty that you want to creat the Student in :\n" ;
                cin >> name ;
                fac_y = Search_Faculty(univer_y,name) ;
                if ( !fac_y) {
                    cout << "The faculty you entered does not exist in "
                         << univer_y->name << " University\n" 
                         << "Do you want to enter another faculty ?\n"
                         << "1 : Yes\n"
                         << "2 : No,return\n" ;
                    cin >> choose ;
                    if ( choose == 1 ) goto another_name9 ;
                }else{
                    another_name10:
                    cout << "Enter the name of the Depatment that you want to creat the Student in :\n" ;
                    cin >> name ;
                    dep_y = Search_Department(fac_y,name) ;
                    if ( !dep_y) {
                        cout << "The Department you entered does not exist in the faculty of "
                             << fac_y->name << '\n'
                             << "Do you want to enter another department ?\n"
                             << "1 : Yes\n"
                             << "2 : No,return\n" ;
                        cin >> choose ;
                        if ( choose == 1 ) goto another_name10 ;
                    }else{
                        another_name11:
                        cout << "Enter the name of Speciality that you want to creat the Student in : \n" ;
                        cin >> name ;
                        spec_y = Search_speciality(dep_y,name) ;
                        if ( !spec_y) {
                            cout << "The speciality you entered does not exist in "
                                 << dep_y->name << " department\n"
                                 << "Do you want to enter another Speciality ?\n"
                                 << "1 : Yes\n"
                                 << "2 : No,return\n" ;
                            cin >> choose ;
                            if ( choose == 1 ) goto another_name11 ;
                        }else{
                            another_name12:
                            cout << "Enter the Year that you want to creat the student in : \n" ;
                            cin >> choose ;
                            if ( choose < 1 || choose > 5 ) {
                                cout << "You did not enter a valid year (valid years are : [1..5])\n"
                                     << "Do you want to re-enter the year ?\n"
                                     << "1 : Yes\n"
                                     << "2 : No,return\n" ;
                                cin >> choose ;
                                if ( choose == 1 ) goto another_name12 ;
                            }else{
                                cout << "Enter the First Name of the Student : \n" ;
                                cin >> name ;
                                cout << "Enter his/her Last name : \n" ;
                                cin >> name1 ;
                                Creet_student(spec_y,choose,name,name1) ;
                            };
                        };
                    };
                };
            };
        };
            break;
        case 6:{
            cout << "Enter the name of the university :\n" ;
            cin >> name ;
            if ( ! Search_University(univer,name)) {
                cout << "The University is not found\n" ;
            }else cout << "The university is found successfully!" ;
        };
            break;
        case 7:{
            choose = 1 ;
            cout << "Enter the name of the faculty :\n" ;
            cin >> name ;
            univer_y = univer ;
            while ( univer_y ){
                if ( Search_Faculty(univer_y,name)){
                    cout << "The Faculty is fount successfully!\n"
                         << "And its path is :\n"
                         << univer_y->name << " / "
                         << name << '\n' ;
                    choose++ ;
                };
                univer_y = univer_y->next ;
            };
            if ( !univer_y && choose == 1 ) cout << "The faculty is not found\n" ;
        };
            break;
        case 8:{
            choose = 1 ;
            cout << "Enter the name of Department :\n" ;
            cin >> name ;
            univer_y = univer ;
            while ( univer_y ){
                fac_y = univer_y->fac ;
                while (fac_y){
                    if ( Search_Department(fac_y,name)){
                        cout << "The department is found successfully!\n"
                             << "And its path is :\n"
                             << univer_y->name << " / "
                             << fac_y->name << " / "
                             << name << '\n' ;
                        choose++ ;
                    };
                    fac_y = fac_y->next ;
                };
                univer_y = univer_y->next ;
            };
            if ( ! univer_y && choose == 1 ) cout << "The department is not found\n" ;
        };
            break;
        case 9:{
            choose = 1 ;
            cout << "Enter the name of the Speciality :\n" ;
            cin >> name ;
            univer_y = univer ;
            while ( univer_y ){
                fac_y = univer_y->fac ;
                while (fac_y){
                    dep_y = fac_y->dep ;
                    while (dep_y){
                        if ( Search_speciality(dep_y,name)){
                            cout << "The speciality is found successfully!\n"
                                 << "And its path is :\n"
                                 << univer_y->name << " / "
                                 << fac_y->name << " / "
                                 << dep_y->name << " / "
                                 << name << '\n' ;
                            choose++ ;
                        };
                        dep_y = dep_y->next ;
                    };
                    fac_y = fac_y->next ;
                };
                univer_y = univer_y->next ;
            };
            if ( ! univer_y && choose == 1 ) cout << "The speciality is not found\n" ;
        };
            break;
        case 10:{
            choose = 1 ;
            cout << "Enter the Student's first name :\n" ;
            cin >> name ;
            cout << "Enter his/her second name :\n" ;
            cin >> name1 ;
            univer_y = univer ;
            while (univer_y){
                fac_y = univer_y->fac ;
                while (fac_y){
                    dep_y = fac_y->dep ;
                    while (dep_y){
                        spec_y = dep_y->spec ;
                        while (spec_y){
                            if ( Search_student(spec_y,name,name1)){
                                cout << "The student is found successfully!\n"
                                     << "And his/her path is :\n"
                                     << univer_y->name << " / "
                                     << fac_y->name << " / "
                                     << dep_y->name << " / "
                                     << spec_y->name << " / "
                                     << name1 << "_"
                                     << name << '\n' ;
                                choose++ ;
                            };
                            spec_y = spec_y->next ;
                        };
                        dep_y = dep_y->next ;
                    };
                    fac_y = fac_y->next ;
                };
                univer_y = univer_y->next ;
            };
            if ( ! univer_y && choose == 1 ) cout << "The student is not found\n" ;
        };
            break;
        case 11:{
            cout << "Enter the name of the university to be deleted :\n" ;
            cin >> name ;
            if (!Search_University(univer,name)){
                cout << "The university you entered does not exist\n" ;
            }else{
                Delete_university(univer,name) ;
            };
        };
            break;
        case 12:{
            cout << "Enter the name of the faculty's university :\n" ;
            cin >> name ;
            univer_y = Search_University(univer,name) ;
            if (!univer_y){
                cout << "The university does not exist\n" ;
            }else{
                cout << "Enter the name of the faculty to be deleted :\n" ;
                cin >> name ;
                if (!Search_Faculty(univer_y,name)){
                    cout << "The faculty does not exist :\n" ;
                }else{
                    Delete_faculty(univer_y,name) ;
                };
            };
        };
            break;
        case 13:{
            cout << "Enter the university :\n" ;
            cin >> name ;
            univer_y = Search_University(univer,name) ;
            if ( !univer_y) {
                cout << "The university does not exist\n" ;
            }else{
                cout << "Enter the name of the faculty :\n" ;
                cin >> name ;
                fac_y = Search_Faculty(univer_y,name) ;
                if (!fac_y){
                    cout << "The faculty does not exist\n" ;
                }else{
                    cout << "Enter the name of the department to be deleted :\n" ;
                    cin >> name ;
                    if (!Search_Department(fac_y,name)){
                        cout << "The department does not exist\n" ;
                    }else{
                        Delete_department(fac_y,name) ;
                    };
                };
            };
        }
            break;
        case 14:{
            cout << "Enter the university :\n" ;
            cin >> name ;
            univer_y = Search_University(univer,name) ;
            if ( !univer_y) {
                cout << "The university does not exist\n" ;
            }else{
                cout << "Enter the name of the faculty :\n" ;
                cin >> name ;
                fac_y = Search_Faculty(univer_y,name) ;
                if (!fac_y){
                    cout << "The faculty does not exist\n" ;
                }else{
                    cout << "Enter the name of the department :\n" ;
                    cin >> name ;
                    dep_y = Search_Department(fac_y,name) ;
                    if (!dep_y){
                        cout << "The department does not exist\n" ;
                    }else{
                        cout << "Enter the name of the Speciality to be deleted :\n" ;
                        cin >> name ;
                        if (!Search_speciality(dep_y,name)){
                            cout << "The speciality does not exist\n" ;
                        }else{
                            Delete_speciality(dep_y,name) ;
                        };
                    };
                };
            };
        };
            break;
        case 15:{
            cout << "Enter the university that the student study in :\n" ;
            cin >> name ;
            univer_y = Search_University(univer,name) ;
            if ( ! univer_y){
                cout << "The university does not exist\n" ;
            }else {
                cout << "Enter the Faculty :\n" ;
                cin >> name ;
                fac_y = Search_Faculty(univer_y,name) ;
                if ( !fac_y){
                    cout << "The faculty does not exist\n" ;
                }else{
                    cout << "Enter the Department :\n" ;
                    cin >> name ;
                    dep_y = Search_Department(fac_y,name) ;
                    if (!dep_y){
                        cout << "The department does not exist\n" ;
                    }else{
                        cout << "Enter the Speciality :\n" ;
                        cin >> name ;
                        spec_y = Search_speciality(dep_y,name) ;
                        if (!spec_y){
                            cout << "The Speciality does not exist\n" ;
                        }else{
                            cout << "Enter the year :\n" ;
                            cin >> choose ;
                            if ( choose < 1 || choose > 5) {
                                cout << "That's not a valid year\n" ;
                            }else{
                                cout << "Enter the student's first name :\n" ;
                                cin >> name ;
                                cout << "Enter his/her las name :\n" ;
                                cin >> name1 ;
                                stud_y = Search_student(spec_y,name,name1) ;
                                if (!stud_y){
                                    cout << "The Student does not exist\n" ;
                                }else Delete_student(spec_y,choose,name,name1) ;
                            };
                        };
                    };
                };
            };
        };
            break;
        case 16:{

        }
            break;
        case 17:{
            Display (univer) ;
        };
            break;
        case 18:{
            Delete_all(univer) ;
            cout << "Everything was deleted successfully!\n" ;
        };
            break;
        default:
            break;
        } 
    } while ( choose != 0);
    cout << "Do you want to save the changes ?\n"
         << "1: Save\n"
         << "2: Discard\n" ;
    cin >> choose ;
    if (choose == 1) {
        Save_structure(univer ,"Structure.txt") ;
        cout << "The structure has been saved successfully!\n" ;
    };
    return 0 ;
}