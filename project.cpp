#include <iostream>
#include <fstream>

using namespace std;

////////////////////////////////////////////
void add_student();
void score();
void save_to_file(string stu_id, string stu_name, float average, string courses_details);
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
    string stu_id, stu_name, coursename, courses_details;
    int course, unit;
    int units = 0;
    float score, sumcourse = 0;

    cout << "Enter student ID: ";
    cin >> stu_id;
    cout << "Enter your full name: ";
    getline(cin >> ws, stu_name);
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

        courses_details += "Course: " + coursename + ", Credits: " + to_string(unit) + ", Grade: " + to_string(score) + "\n";
    }

    float average = sumcourse / units;
    save_to_file(stu_id, stu_name, average, courses_details);
}

////////////////////////////////////////////////////////////////////////
void save_to_file(string stu_id, string stu_name, float average, string courses_details) {
    ofstream inputFile("students.txt", ios::app);
    if (inputFile.is_open()) {
        inputFile << "Student ID: " << stu_id << endl;
        inputFile << "Student Name: " << stu_name << endl;
        inputFile << courses_details;
        inputFile << "GPA: " << average << endl;
        inputFile << "------" << endl;
        inputFile.close();
        cout << "Student information saved successfully." << endl;
    } else {
        cerr << "Error opening the file!" << endl;
    }
}

//////////////////////////////////////////////////////////////////////
void show_student_by_id() {
    string id, line;
    cout << "Enter student ID to search: ";
    cin >> id;

    ifstream file("students.txt");
    bool found = false;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find("Student ID: " + id) != string::npos) {
                found = true;
                cout << line << endl;
                for (int i = 0; i < 4; ++i) {
                    getline(file, line);
                    cout << line << endl;
                }
                break;
            }
        }
        file.close();

        if (!found) {
            cout << "Student with ID " << id << " not found!" << endl;
        }
    } else {
        cerr << "Error opening the file!" << endl;
    }
}

//////////////////////////////////////////////////////////////////////
void show_student_by_name() {
    string name, line;
    cout << "Enter the student's name: ";
    cin.ignore();
    getline(cin, name);

    ifstream file("students.txt");
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find("Student Name: " + name) != string::npos) {
                found = true;
                cout << "Student details:" << endl;
                cout << line << endl;

                while (getline(file, line) && line != "------") {
                    cout << line << endl;
                }
                cout << "------" << endl;
                break;
            }
        }
        file.close();

        if (!found) {
            cout << "Student with name \"" << name << "\" not found!" << endl;
        }
    } else {
        cerr << "Error opening the file!" << endl;
    }
}

////////////////////////////////////////
void delete_student_by_id() {
    string stu_id, line;
    cout << "Enter student ID to delete: ";
    cin >> stu_id;

    string students[100];
    int count = 0;

    ifstream file("students.txt");
    if (!file.is_open()) {
        cerr << "Error opening the file!" << endl;
        return;
    }

    bool found = false;
    while (getline(file, line)) {
        if (line.find("Student ID: " + stu_id) != string::npos) {
            found = true;
            while (getline(file, line) && line != "------");
        } else {
            students[count++] = line;
        }
    }
    file.close();

    if (!found) {
        cout << "Student with ID " << stu_id << " not found!" << endl;
        return;
    }

    ofstream outfile("students.txt");
    for (int i = 0; i < count; i++) {
        outfile << students[i] << endl;
    }
    outfile.close();
    cout << "Student with ID " << stu_id << " deleted successfully!" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////
void delete_student_by_name() {
    string stu_name, line;
    cout << "Enter student name to delete: ";
    cin.ignore();
    getline(cin, stu_name);

    if (stu_name.empty()) {
        cout << "No name entered!" << endl;
        return;
    }

    string students[100];
    int count = 0;

    ifstream file("students.txt");
    if (!file.is_open()) {
        cerr << "Error opening the file!" << endl;
        return;
    }

    bool found = false;
    bool delete_student = false;

    while (getline(file, line)) {
        if (line.find("Student Name: " + stu_name) != string::npos) {
            found = true;
            delete_student = true;

            while (getline(file, line) && line != "------");
        } else {
            if (!delete_student) {
                students[count++] = line;
            } else {
                if (line == "------") {
                    delete_student = false;
                }
            }
        }
    }
    file.close();

    if (!found) {
        cout << "Student with name \"" << stu_name << "\" not found!" << endl;
        return;
    }

    ofstream outfile("students.txt");
    for (int i = 0; i < count; i++) {
        outfile << students[i] << endl;
    }
    outfile.close();
    cout << "Student with name \"" << stu_name << "\" deleted successfully!" << endl;
}
