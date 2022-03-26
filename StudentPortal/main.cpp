#include <conio.h>
#include <iostream>

#include "console.h"
#include "studentlist.h"

using namespace std;

int main()
{
    // https://docs.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
    SetConsoleOutputCP(65001);

    // https://docs.microsoft.com/en-us/windows/console/setconsolemode
    SetConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    auto students = StudentList("student.json");

    Start:
    ResetColor();
    system("cls");

    WriteLine(Center("Group HelloWorld", 120));
    PrintBorders({ 20, 3 }, "STUDENT INFORMATION SYSTEM", 80, 20);

    XY(49, 6);
    WriteLine("What do you want to do?");

    XY(48, 7);
    Color yellow{ 232, 182, 30 };
    WriteLine(ChangeColor("1", yellow) + ". Add New Record");
    WriteLine(ChangeColor("2", yellow) + ". Search Record");
    WriteLine(ChangeColor("3", yellow) + ". Display All Records");
    WriteLine(ChangeColor("4", yellow) + ". Display Specific Record");
    WriteLine(ChangeColor("5", yellow) + ". Delete Record");
    WriteLine(ChangeColor("6", yellow) + ". Exit");

    const int choice = Prompt<int>("Enter selection", {27, 16});
    switch (choice)
    {
        case 1: students.AddStudent();
            break;
        case 2: students.SearchStudent();
            break;
        case 3: students.DisplayStudents();
            break;
        case 4: students.DisplayStudent();
            break;
        case 5: students.DeleteStudent();
            break;
        case 6: return 0;
    }
    students.Save();
    MoveCursor(CursorDirection::Down, 2);
    system("pause");
    goto Start;
}
