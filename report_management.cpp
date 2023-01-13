#include <iostream> // console input output
#include <fstream>  // file input output
using namespace std;

// class start
class student
{
    int rollno;
    char name[50];
    int cs_marks, math_marks, sci_marks, eng_marks, lang2_marks;
    double average;
    char grade;

public:
    // these functions are defined outside the class

    // setter function
    void setData();
    // getter function
    void getData() const;
    // return rollno
    int retrn_rollno() const;
    // calculate average marks and grade
    void calculate();
}; // class ends here

// these function are declared inside the class and define with the help of :: (scope resolution) operator, its a functionality in c++
void student::calculate()
{
    average = (cs_marks + math_marks + sci_marks + eng_marks + lang2_marks) / 5.0;

    if (average >= 90)
        grade = 'A';
    else if (average >= 75)
        grade = 'B';
    else if (average >= 60)
        grade = 'C';
    else if (average >= 50)
        grade = 'D';
    else
        grade = 'F';
}

void student::getData() const
{
    cout << "Roll number of student : " << rollno;
    cout << "\nName of student : " << name;
    cout << "\n\nMarks(out of 100)" << endl;
    cout << "\nComputer Science :" << cs_marks;
    cout << "\nMaths : " << math_marks;
    cout << "\nScience : " << sci_marks;
    cout << "\nEnglish : " << eng_marks;
    cout << "\nLanguage2 : " << lang2_marks;
    cout << "\nAverage Marks :" << average;
    cout << "\nGrade of student is :" << grade;
    cout << "\n\n====================================\n";
}

void student::setData()
{
    cout << "Enter student's roll number: ";
    cin >> rollno;

    cout << "\nEnter student name: ";
    cin.ignore(); // to clear input buffer
    cin.getline(name, 50);
    
        cout << "\n\nEnter Marks(out of 100)\n"
             << endl;
        cout << "\nComputer science:  ";
        cin >> cs_marks;

        cout << "Math:  ";
        cin >> math_marks;

        cout << "Science:  ";
        cin >> sci_marks;

        cout << "English: ";
        cin >> eng_marks;

        cout << "2nd language:  ";
        cin >> lang2_marks;
        calculate();

        if (cs_marks > 100 || math_marks > 100 || sci_marks > 100 || eng_marks > 100 || lang2_marks > 100)
        {
            cout << "Error: You have entered more than 100 marks in subject(s)" << endl;
            cout << "Suggestion: Delete this record manually and Enter again"<<endl;
        }

}

int student::retrn_rollno() const
{
    return rollno;
}

// function declaration, these are defined after the main function
void create_student();      // create record of a student
void display_stud(int);     // display particular record
void display_all();         // display all records
void delete_student(int);   // delete particular record
void delete_all_students(); // delete the record file

// MAIN
int main()
{
    char ch;
    do
    {
        int num;
        system("cls");
        cout << "****************MENU****************";
        cout << "\n1. Create student record";
        cout << "\n2. Search student record";
        cout << "\n3. Display all students records";
        cout << "\n4. Delete particular student record";
        cout << "\n5. Delete all students record";
        cout << "\n6. Exit";
        cout << "\nWhat is your Choice (1/2/3/4/5/6): ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            create_student();
            break;
        case '2':
            cout << "Enter The roll number ";
            cin >> num;
            display_stud(num);
            break;
        case '3':
            display_all();
            break;
        case '4':
            cout << "Enter The roll number: ";
            cin >> num;
            delete_student(num);
            break;
        case '5':
            delete_all_students();
            break;
        case '6':
            cout << "Exiting, Thank you!";
            exit(0);
        }

    } while (ch != '6');
    return 0;
}

void error_msg()
{
    cout << "File could not be opened" << endl;
}

void menu_msg()
{
    cout << "Press any key to return to main menu" << endl;
}

// write student details to file
void create_student()
{
    student stud;
    ofstream oFile;

    oFile.open("student.dat", ios::binary | ios::app);
    stud.setData();
    oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));
    oFile.close();
    cout << "Student record Has Been Created. !!" << endl;
    menu_msg();
    cin.ignore();
    cin.get();
}

// read file records
void display_all()
{
    student stud;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);

    if (!inFile)
    {
        error_msg();
        menu_msg();
        cin.ignore();
        cin.get();
        return;
    }

    cout << "****************DISPLAYING ALL RECORDS****************\n\n";

    while (inFile.read(reinterpret_cast<char *>(&stud), sizeof(student)))
    {
        stud.getData();
    }
    inFile.close();
    cout << "[End of File]" << endl;
    menu_msg();
    cin.ignore();
    cin.get();
}

// read specific record based on roll number
void display_stud(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile)
    {
        error_msg();
        menu_msg();
        cin.ignore();
        cin.get();
        return;
    }

    bool flag = false;
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student)))
    {
        if (stud.retrn_rollno() == n)
        {
            stud.getData();
            flag = true;
        }
    }

    iFile.close();

    if (flag == false)
        cout << "record does not exist !!\n";

    menu_msg();
    cin.ignore();
    cin.get();
}

// delete record with particular roll number
void delete_student(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile)
    {
        error_msg();
        menu_msg();
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat", ios::out);
    iFile.seekg(0, ios::beg);
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student)))
    {
        if (stud.retrn_rollno() != n)
        {
            oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();

    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "Record Deleted ..\n";
    menu_msg();
    cin.ignore();
    cin.get();
}

// delete the file that contains the record of students
void delete_all_students()
{
    cout << "Warning: File containing all the students record will be deleted !!" << endl;
    char res;
    cout << "Enter y to delete or any other key to return to main menu" << endl;
    cin >> res;
    if (res == 'y')
    {
        remove("student.dat");
        cout << "All Students record are deleted !!" << endl;
        menu_msg();
        cin.ignore();
        cin.get();
    }
}
