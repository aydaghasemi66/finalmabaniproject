#include <iostream>
#include <fstream>
using namespace std;
void add_student();
void score();
void save_to_file(string stu_id, string stu_name, float average);

void add_student(){
    int number_of_students;
    cout<<"Enter number of students:";
    cin>>number_of_students;
    for(int i=0;i < number_of_students;i++){
        score();
    }


}
void score(){
    string stu_id , stu_name, coursename;
    int course;
    int units=0;
    int unit;
    float score, sumcourse = 0;
    cout << "Enter student ID: ";
    cin >> stu_id;
    cout << "Enter your full name: ";
    cin >> stu_name;
    cout << "Number of courses: ";
    cin >> course;
    for (int i = 0; i < course; i++) {
        cout << "Enter course name " << (i + 1) << ": ";
        cin >> coursename;
        cout << "Enter the number of units: ";
        cin >> unit;
        cout << "Enter score (0 to 20): ";
        cin >> score;
        units += unit;
        sumcourse += unit * score;
    }

    float average = sumcourse / units;
    save_to_file(stu_id, stu_name, average);
}

void save_to_file(string stu_id, string stu_name, float average) {
    ofstream file("students.txt", ios::app);
    if (file.is_open()) {
        file << stu_id << "," << stu_name << "," << average << endl;
        file.close();
        cout << "\nStudent information saved successfully." << endl;
    } else {
        cout << "Error opening the file!" << endl;
    }

  
}



int main(){
    int n = 0;
    while (n==0){
        cout << "1.  Add Student" << endl;
        cout << "2.  Show student information (by ID)" << endl;
        cout << "3.  Show student information (by Name)" << endl;
        cout << "4.  Delete student (by ID)" << endl;
        cout << "5.  Delete student (by Name)" << endl;
        cout << "6.  Exit" << endl;
        cout <<"//////////////////////////////////////////////////"<<endl;
        cout <<" Please select an operation from the menu below:"<<endl;
        cin >> n;

    }
    switch (n)
    {
        case 1:
            add_student();
            break;
    
                // نمایش بر اساس نام (در آینده پیاده‌سازی می‌شود)
                break;
        case 4:
                // حذف بر اساس کد (در آینده پیاده‌سازی می‌شود)
                break;
        case 5:
                // حذف بر اساس نام (در آینده پیاده‌سازی می‌شود)
                break;
        case 6:
                cout << "برنامه بسته شد." << endl;
                return 0;
        default:
                cout << "انتخاب نامعتبر است!" << endl;

    
}
}
