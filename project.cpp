#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
////////////////////////////////////////////
void add_student();
void score();
void save_to_file(string stu_id, string stu_name, float average);
void show_student_by_id();
void show_student_by_name();
void delete_student_by_id();
void delete_student_by_name();
/////////////////////////////////////////////

int main() {
    int n = 0;
    while (true) {
        cout << "\n1. Add Student" << endl;
        cout << "2. Show student information (by ID)" << endl;
        cout << "3. Show student information (by Name)" << endl;
        cout << "4. Delete student (by ID)" << endl;
        cout << "5. Delete student (by Name)" << endl;
        cout << "6. Exit" << endl;
        cout << "================================================" << endl;
        cout << "Please select an operation from the menu below: ";
        cin >> n;

        switch (n) {
            case 1:
                add_student();
                break;
            case 2:
                show_student_by_id();
                break;
            case 3:
                show_student_by_name();
                break;
            case 4:
                delete_student_by_id();
                break;
            case 5:
                delete_student_by_name();
                break;
            case 6:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid selection! Please try again." << endl;
        }
    }
}
//////////////////////////////////////////////////////////////////
void add_student() {
    int number_of_students;
    cout << "Enter number of students: ";
    cin >> number_of_students;
    for (int i = 0; i < number_of_students; i++) {
        score();
    }
}
/////////////////////////////////////////////////////////////////////
void score() {
    string stu_id, stu_name, coursename;
    int course, unit;
    int units = 0;
    float score, sumcourse = 0;

    cout << "Enter student ID: ";
    cin >> stu_id;
    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, stu_name);
    cout << "Number of courses: ";
    cin >> course;

    for (int i = 0; i < course; i++) {
        cout << "Enter course name " << (i + 1) << ": ";
        cin >> coursename;
        cout << "Enter the number of units: ";
        cin >> unit;
        do {
            cout << "Enter score (0 to 20): ";
            cin >> score;
            if (score < 0 || score > 20) {
                cout << "Invalid score!Please enter a value between 0 and 20." << endl;
            }
        } while (score < 0 || score > 20);

        units += unit;
        sumcourse += unit * score;
    }

    float average = sumcourse / units;
    save_to_file(stu_id, stu_name, average);
}
////////////////////////////////////////////////////////////////////////
void save_to_file(string stu_id, string stu_name, float average) {
    ofstream inputFile("students.txt", ios::app);
    if (inputFile.is_open()) {
        inputFile << stu_id << "," << stu_name << ":" << average << endl;
        inputFile.close();
        cout << "Student information saved successfully." << endl;
    } else {
        cerr << "Error opening the file!" << endl;
    }
}
//////////////////////////////////////////////////////////////////////
void show_student_by_id() {
    string id, line, result = "";
    cout << "Enter student ID to search: ";
    cin >> id;

    ifstream file("students.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(id + ",") == 0) {
                result = line;
                break;
            }
        }
        file.close();

        cout << "Student details: " << result << endl;
        if(result=="")
            cout << "Student with ID " << id << " not found!" << endl;
        }
}
//////////////////////////////////////////////////////////////////////
void show_student_by_name(){
    string name;
    cout << "Enter the student's name: ";
    cin >> name;

    ifstream file("students.txt"); 
    if (!file) {
        cerr << "Error opening the file!" << endl;
        return;
    }
    string line;
    string result = "";

    while (getline(file, line)) {
        if (line.find(name) != string::npos) { 
            cout << "Student found: " << line << endl;
            result = name;
            break;
        }
    }
    if (result=="") {
        cout << "Student with name " << name << " not found!" << endl;
    }

    file.close(); 
}
////////////////////////////////////////
void delete_student_by_id() {
    string id, stu_id, stu_name;
    float average;
    bool found = false;

    cout << "Enter student ID to delete: ";
    cin >> id;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (file && temp) {
        while (file >> stu_id >> stu_name >> average) {
            if (stu_id == id) {
                found = true; // خط مرتبط حذف می‌شود
            } else {
                temp << stu_id << " " << stu_name << " " << average << endl;
            }
        }
        file.close();
        temp.close();

        if (found) {
            remove("students.txt");
            rename("temp.txt", "students.txt");
            cout << "Student with ID " << id << " deleted successfully!" << endl;
        } else {
            cout << "Student with ID " << id << " not found!" << endl;
            remove("temp.txt");
        }
    } else {
        cout << "Could not open file!" << endl;
    }
}

