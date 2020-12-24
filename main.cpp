#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include<stdlib.h>
#include <iomanip>

using namespace std;
//Node structure for linked list
struct Node
{
    string fName, lName, dob, grade;
    int id;
    Node *nextNode;
    Node *prevNode;
};
//Doubly Linked List Class
class linkedList{
private:
    Node *head, *tail;
public:
    //Constructor will initialize both head and tail to null
    linkedList()
    {
        head = NULL;
        tail = NULL;
    }
    //Function to get the head
    Node *getHeadNode()
    {
        return head;
    }
    //Function to get the Tail
    Node *getTailNode()
    {
        return tail;
    }
    //Function to get size of Linked List
    int getSize(Node *node)
    {
        int size = 0;
        while (node!=NULL)
        {
            size++;
            node = node->nextNode;
        }
        return size;
    }
    //Function to add data to linked list
    void add(Node *node, int id, string fname, string lname, string dob, string grade, int defaultVar = 0)
    {
        Node *temp = new Node();
        int total = getSize(node);
        temp->id = id;
        temp->fName = fname;
        temp->lName = lname;
        temp->dob = dob;
        temp->grade = grade;
        temp->nextNode = NULL;
        if(total > 0)
        {
            temp->prevNode = getNodeAt(node, total-1);
        }
        if (head == NULL)
        {
            temp->prevNode = NULL;
            head = temp;
            tail = temp;
        }
        else
        {
            tail->nextNode = temp;
            tail = tail->nextNode;
        }
    }
    //Function to print data in linked list
    void printFoward(Node *node, string showGrade)
    {
        int total = getSize(node), i=0;
        if (showGrade == "yes")
            cout <<"#"<<setw(15)<<"Student ID"<<setw(16)<<"First Name"<<setw(16)<<"Last Name"<<setw(15)<<"Grade"<<endl;
        else if (showGrade == "no")
            cout <<"#"<<setw(15)<<"Student ID"<<setw(16)<<"First Name"<<setw(16)<<"Last Name"<<setw(20)<<"Date of Birth"<<endl;
        while (i < total)
            {
                i++;
                if (showGrade == "yes")
                    cout <<i<<setw(12)<< node->id<<setw(14)<<node->fName<<setw(21)<<node->lName<<setw(14)<<node->grade<< endl;
                else if (showGrade == "no")
                    cout <<i<<setw(12)<< node->id<<setw(14)<<node->fName<<setw(21)<<node->lName<<setw(17)<<node->dob<< endl;
                node = node->nextNode;
            }
    }
    //Function to get particular item given index
    int getItemAt(Node *node, int index)
    {
        int total = getSize(node);
        int item;
        for(int i=0; i<total; i++)
        {
            if(index == i)
            {
                item = node->id;
                break;
            }
            node = node->nextNode;
        }
        return item;
    }
    //Function to get a node given an index
    Node *getNodeAt(Node *node, int index)
    {
        int total = getSize(node);
        for(int i=0; i<total; i++)
        {
            if(index == i)
            {
                return node;
                break;
            }
            node = node->nextNode;
        }
    }
    //Function to update list
    void updateID(Node *node, int value)
    {
        node->id = value;
    }
    void updateFName(Node *node, string value)
    {
        node->fName = value;
    }
    void updateLName(Node *node, string value)
    {
        node->lName = value;
    }
    void updateDOB(Node *node, string value)
    {
        node->dob = value;
    }
    void updateGrade(Node *node, string value)
    {
        node->grade = value;
    }
    //Function to Sort items in a list
    void sortList(Node *node)
    {
        int total = getSize(node);
        int LeftID, RightID;
        Node *lRecord, *rRecord;
        string Leftfname, Leftlname, Leftdob, Rightfname, Rightlname, Rightdob;
        for(int i=0; i<total; i++)
        {
            for(int j=i+1; j<total; j++)
            {
                if (getItemAt(node, i) > getItemAt(node, j))
                {
                    lRecord = getNodeAt(node, i);
                    rRecord = getNodeAt(node, j);
                    //Left Side Data
                    LeftID = lRecord->id;
                    Leftfname = lRecord->fName;
                    Leftlname = lRecord->lName;
                    Leftdob = lRecord->dob;
                    //Right Side Data
                    RightID = rRecord->id;
                    Rightfname = rRecord->fName;
                    Rightlname = rRecord->lName;
                    Rightdob = rRecord->dob;
                    //Updating Data
                    updateID(getNodeAt(node, i), RightID);
                    updateID(getNodeAt(node, j), LeftID);
                    updateFName(getNodeAt(node, i), Rightfname);
                    updateFName(getNodeAt(node, j), Leftfname);
                    updateLName(getNodeAt(node, i), Rightlname);
                    updateLName(getNodeAt(node, j), Leftlname);
                    updateDOB(getNodeAt(node, i), Rightdob);
                    updateDOB(getNodeAt(node, j), Leftdob);
                }
            }
        }
    }
    //Function to search for an item
    int searchItem(Node *node, int value)
    {
        int total = getSize(node), first=0, middle, last = total-1, position = -1;
        bool found = false;
        while (found != true && first <= last)
        {
            middle = (first+last)/2;
            if(getItemAt(node, middle) == value)
            {
                found = true;
                position = middle;
            }else if (getItemAt(node, middle) > value)
            {
                last = middle - 1;
            }else
            {
                first = middle + 1;
            }
        }
        return position;
    }
    //Function to delete node
    void deleteItem(Node *node, int index)
    {
        int total = getSize(node);
        Node *temp = getNodeAt(node, index);
        if (total > 0)
        {
            if (index!=0)
                {
                  if(temp->nextNode != NULL)
                    {
                        getNodeAt(node, index-1)->nextNode = temp->nextNode;
                        getNodeAt(node, index)->prevNode = getNodeAt(node, index-1);
                    }
                  else if (temp->nextNode == NULL)
                    {
                        getNodeAt(node, index-1)->nextNode = temp->nextNode;
                    }
                }
            else if (index == 0 && total >=2)
            {
                temp = getNodeAt(node, index+1);
                getNodeAt(node, index)->id = temp->id;
                getNodeAt(node, index)->fName = temp->fName;
                getNodeAt(node, index)->lName = temp->lName;
                getNodeAt(node, index)->dob = temp->dob;
                getNodeAt(node, index)->grade = temp->grade;
                getNodeAt(node, index)->nextNode = temp->nextNode;
                getNodeAt(node, index)->prevNode = NULL;
            }
            else
            {
                head = NULL;
                tail = NULL;
            }
            delete temp;
        }
        else
        {
            cout <<"No items to delete\n";
        }
    }
};
//Global Variable
linkedList list1;
//All Function Prototypes
void menu();
void saveToFile();
void addRecord();
void showRecord();
void searchRecord();
void fillList();
void update();
void showGrade();
bool testName(string name);
bool testDate(string date);
bool testID(string id);
void updateDOB(Node *record);
void updateFName(Node *record);
void updateLName(Node *record);
void updateID(Node *record);
void deleteRecord();
int strToInt(string value);
void updateGrade();
int main()
{
    system("color f4");
    fillList();
    menu();
}
//All Function Definitions
//Function to test id
bool testID(string id)
{
    int initialNumber=0, finalNumber = id.length(), nonDigitNumber=0;
    for (int i=0; i<7; i++)
    {
        if(!isdigit(id[i]))
            nonDigitNumber++;
        if(isdigit(id[i]))
            initialNumber++;
    }
    if(nonDigitNumber == 0 &&  finalNumber==7 )
        return true;
    else
        return false;
}
//Function to test date
bool testDate(string date)
{
    int count = 0;
    //This string will concatenate 10 0ne's. If ones are 10 the date is valid
    string initialSpecial = "", finalSpecial ="1111111111";
    for(count=0; count <2; count++)
    {
        if (isdigit(date[count]))
            initialSpecial+="1";
    }
    for(count = 2; count <3; count++)
        if(date[count]=='-')
            initialSpecial+="1";
    for(count = 3; count < 5; count++)
        if(isdigit(date[count]))
            initialSpecial+="1";
    for(count = 5; count <6; count++)
        if(date[count]=='-')
            initialSpecial+="1";
    for(count = 6; count < 10; count++)
        if(isdigit(date[count]))
            initialSpecial+="1";
    if (initialSpecial == finalSpecial)
        return true;
    else
        return false;
}
//Function to test name
bool testName(string name)
{
    int countNumber = 0;
    // If countNumber is greater than 0 it means that the string contains both numbers and letters after converting string. Making name invalid
    for (int i=0; i<name.length(); i++)
    {
        if (isdigit(name[i]))
            countNumber++;
    }
    if(countNumber>0)
        return false;
    else
        return true;
}
//Function to add / insert record
void addRecord()
{
    system("cls");
    int errIndex = 0;
    string fName, lName, DOB, listData;
    int studentID;
    bool proceed = false;
    //Title
    cout << "***Add Records Menu***\n\n";
    //Adding First Name
    do
    {
        if(errIndex > 0)
        {
            errIndex--;
            system("color F5");
            cout <<"!!!YOUR INPUT DID NOT NAME STANDARDS!!!"<<endl;
            cout <<"Your first name seems to contain characters not found in a name."<<endl;
            system("pause");
            system("cls");
            cout << "***Add Records Menu***\n\n";
        }
        system("color F4");
        cout << "Entry of First Name\n";
        cout << "---------------------\n";
        cout << "Instruction: FIRST NAME SHOULD ONLY CONTAIN LETTERS\n\n";
        cout << "Enter First Name: ";
        cin>> fName;
        errIndex++;
        proceed = testName(fName);
    }while(!proceed);
    errIndex =0; proceed = false;
    //Adding Last Name
    do
    {
        cout << "***Add Records Menu***\n\n";
        if(errIndex > 0)
        {
            errIndex--;
            system("color F5");
            cout <<"!!!YOUR INPUT DID NOT NAME STANDARDS!!!"<<endl;
            cout <<"Your last name seems to contain characters not found in a name."<<endl;
            system("pause");
            cout << "***Add Records Menu***\n\n";
        }
        system("color F4");
        cout << "Entry of Last Name\n";
        cout << "---------------------\n";
        cout << "Instruction: LAST NAME SHOULD ONLY CONTAIN LETTERS\n\n";
        cout << "Enter Last Name: ";
        cin>> lName;
        errIndex++;
        proceed = testName(lName);
    }while(!proceed);
    errIndex =0; proceed = false;
    //Adding ID
    do
    {
        cout << "***Add Records Menu***\n\n";
        string tempID = "";
        if(errIndex > 0)
        {
            errIndex--;
            system("color F5");
            cout <<"!!!YOUR INPUT DID NOT MATCH THE REQUIRED STANDARDS!!!"<<endl;
            cout <<"Your id is either beyond 7 digits or has characters that should not be in an id."<<endl;
            system("pause");
            system("cls");
            cout << "***Add Records Menu***\n\n";
        }
        system("color F4");
        cout << "Entry of Student ID\n";
        cout << "--------------------\n";
        cout << "Instruction: ID SHOULD HAVE 7 DIGITS ONLY\n\n";
        cout << "Enter Student ID: ";
        cin>> tempID;
        errIndex++;
        proceed = testID(tempID);
        studentID = strToInt(tempID);
    }while(!proceed);
    errIndex =0; proceed = false;
    //Adding Date of Birth
    do
    {
        cout << "***Add Records Menu***\n\n";
        if(errIndex > 0)
        {
            errIndex--;
            system("color F5");
            cout <<"!!!YOUR INPUT DID NOT MATCH THE REQUIRED FORMAT!!!"<<endl;
            cout <<"The format should be \'day-month-year\' Example 01-01-1999"<<endl;
            system("pause");
            system("cls");
            cout << "***Add Records Menu***\n\n";
        }
        system("color F4");
        cout << "Entry of  Date of Birth\n";
        cout << "-----------------------\n";
        cout << "Instruction: DATE OF BIRTH SHOULD BE IN 01-01-1999 FORMAT\n\n";
        cout << "Enter Date of Birth: ";
        cin>> DOB;
        errIndex++;
        system("cls");
        proceed = testDate(DOB);
    }while(!proceed);
    errIndex =0; proceed = false;
    //Adding to list.
    string tempGrade = "NULL";
    list1.add(list1.getHeadNode(), studentID, fName, lName, DOB, tempGrade);
    saveToFile();
    cout << "***Add Records Menu***\n\n";
    cout << "STUDENT RECORD ADDED SUCCESSFULLY\n" << endl;
    int option; string tempOption;
    cout << "Enter 1 to add another record\n";
    cout << "Enter 2 to go back to Menu\n";
    cout << "Enter 3 to exit\n";
    cin >> tempOption;
    option = strToInt(tempOption);
    system("cls");
    if(option == 1)
        addRecord();
    else if (option == 2)
        menu();
    else if(option == 3)
        exit(0);
    else
    {
        system("color F5");
        cout << "***Add Records Menu***\n\n";
        cout << "You Pressed An Invalid Option\n";
        system("pause");
        system("cls");
        menu();
    }
}
//Function to show student record
void showRecord()
{
    system("cls");
    int total = 0;
    total = list1.getSize(list1.getHeadNode());
    if (total>0)
    {
        cout<<"\t\t\t\t\t***All Students***\n\n";
        list1.printFoward(list1.getHeadNode(), "no");
        cout<<endl;
        system("pause");
    }
    else
    {
        cout<<"\t\t\t***All Students***\n\n";
        cout << "NO RECORDS TO SHOW\n";
        cout<<endl;
        system("pause");
    }
    menu();
}
//Function to search for record
void searchRecord()
{
    system("cls");
    Node *record;
    int id, position, option, total = list1.getSize(list1.getHeadNode());
    cout << "\t\tSearch Record\n\n";
if(total > 0)
{
    bool proceed = false;
    int errIndex = 0;
    do
    {
        if(errIndex > 0)
        {
            errIndex--;
            system("color F5");
            cout <<"!!!YOUR INPUT DID NOT NAME STANDARDS!!!"<<endl;
            cout <<"Your last name seems to contain characters not found in a name."<<endl;
            system("pause");
            system("cls");
        }
        system("color F4");
        cout << "Enter ID of Student: ";
        string tempID;
        cin >> tempID;
        errIndex++;
        proceed = testID(tempID);
        id = strToInt(tempID);
    }while(!proceed);
    system("cls");
    position = list1.searchItem(list1.getHeadNode(), id);
    record = list1.getNodeAt(list1.getHeadNode(), position);
    if (position != -1)
    {
        cout << "\t\tSearch Record\n\n";
        cout << "RECORD HAS BEING FOUND" << endl;
        cout << "Student ID: " << record->id << endl;
        cout << "Student First Name: " << record->fName << endl;
        cout << "Student Last Name: " << record->lName << endl;
        cout << "Student Date of Birth: " << record->dob << endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout <<"Enter 1 to update record\n";
        cout <<"Enter 2 to delete record\n";
        cout << "Your option: ";
        cin >> option;
        system("cls");
        if (option == 1)
        {
            cout << "\t\tSearch Record\n\n";
            cout << "Student ID: " << record->id << endl;
            cout << "Student First Name: " << record->fName << endl;
            cout << "Student Last Name: " << record->lName << endl;
            cout << "Student Date of Birth: " << record->dob << endl;
            cout <<"***Update Record***\n";
            cout << "1. Update ID\n";
            cout << "2. Update First Name\n";
            cout << "3. Update Last Name\n";
            cout << "4. Update Date of Birth\n";
            cout << "Choose an option: ";
            cin >> option;
            system("cls");
            if (option == 1)
            {
                int sID;
                cout << "\t\tSearch Record\n\n";
                cout << "Enter new ID: ";
                cin >> sID;
                list1.updateID(record, sID);
            }else if (option == 2)
            {
                string fName;
                cout << "\t\tSearch Record\n\n";
                cout << "Enter New First Name: ";
                cin >> fName;
                list1.updateFName(record, fName);
            }else if (option == 3)
            {
                string lName;
                cout << "\t\tSearch Record\n\n";
                cout << "Enter New Last Name: ";
                cin >> lName;
                list1.updateLName(record, lName);
            }else if (option == 4)
            {
                string DOB;
                cout << "\t\tSearch Record\n\n";
                cout << "Enter New Date of Birth: ";
                cin >> DOB;
                list1.updateDOB(record, DOB);
            }else if (option == 5)
            {
                cout << "\t\tSearch Record\n\n";
                cout << "Invalid option was pressed\n";
                menu();
            }
            cout << "Updated Successfully\n";
            saveToFile();
            menu();
        }else if (option ==2)
        {
            cout << "\t\t***Delete Record***\n\n";
            list1.deleteItem(list1.getHeadNode(), position);
            cout << "Deleted Successfully\n";
            saveToFile();
            menu();
        }else
        {
            cout << "\t\tSearch Record\n\n";
            cout << "You pressed an invalid option\n";
            menu();
        }
    }else
    {
        cout << "\t\tSearch Record\n\n";
        cout << "RECORD NOT FOUND\n" << endl;
        menu();
    }
}
else
{
        cout << "NO RECORDS! SEARCH CAN'T BE DONE\n\n" << endl;
        system("pause");
        system("cls");
        menu();
}

}
//Function to load file data
void fillList()
{
    fstream file("Records.txt", ios::in);
    int id=0;
    string fname, lname, dob, grade;
    if(file)
    {
        while(file>>id>>fname>>lname>>dob>>grade)
        {
            list1.add(list1.getHeadNode(), id, fname, lname, dob, grade);
        }
        file.close();
    }else
    {
        cout << "File Failed to Open\n";
    }
}
//Function to Save Data to file
void saveToFile()
{
    fstream file("Records.txt", ios::out);
    int total = list1.getSize(list1.getHeadNode());
    list1.sortList(list1.getHeadNode());
    Node *record;
    for (int i=0; i<total; i++)
    {
        record = list1.getNodeAt(list1.getHeadNode(), i);
        file << record->id <<"\t\t"<< record->fName <<"\t\t"<< record->lName <<"\t\t"<< record->dob <<"\t\t"<<record->grade<< endl;
    }
    file.close();
}
//Function to display menu
void menu()
{
        system("color F4");
        int option;
        string choice;
        system("cls");
        cout <<"\t\t***Student Management System***\n\n";
        cout <<"1. Show All Records\n";
        cout <<"2. Search For A Record\n";
        cout <<"3. Add A Record(s)\n";
        cout <<"4. Update A Record(s)\n";
        cout <<"5. Delete A Record(s)\n";
        cout <<"6. Grades Menu\n";
        cout <<"7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        system("cls");
        option = strToInt(choice);
        switch(option)
        {
        case 1:
            showRecord();
            break;
        case 2:
            searchRecord();
            break;
        case 3:
            addRecord();
            break;
        case 4:
            update();
            break;
        case 5:
            deleteRecord();
            break;
        case 6:
            showGrade();
            break;
        case 7:
            exit(0);
            break;
        default:
            {
            system("color F5");
            cout << "!!!YOUR ENTRY WAS WRONG!!!" <<endl;
            system("pause");
            menu();
            }
        }
}
//Function to update records
void update()
{
    system("color F4");
    system("cls");
    int option, total = list1.getSize(list1.getHeadNode());
    string choice;
    cout << "\t\t***Record Update***\n\n";
    //This part of the code displays records in list. If condition tests if the list is empty or not
    if(total > 0)
    {
        do
        {
            list1.printFoward(list1.getHeadNode(), "no");
            cout << "Update Record Number: ";
            cin >> choice;
            system("cls");
            option = strToInt(choice);
        }while(option < 0 && option > total);
        //The line below gets the node that needs editing.
        Node *record = list1.getNodeAt(list1.getHeadNode(), option-1);
        cout << "\t\t***Record Update***\n";
        //Code below uses node created above to show data contained by the node.
        cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Student ID: "<<"\t\t" << record->id << endl;
        cout << "Student First Name: "<<"\t" << record->fName << endl;
        cout << "Student Last Name: "<<"\t" << record->lName << endl;
        cout << "Student Date of Birth: "<<"\t" << record->dob << endl;
        cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "1. Update ID\n";
        cout << "2. Update First Name\n";
        cout << "3. Update Last Name\n";
        cout << "4. Update Date of Birth\n";
        cout << "5. Update Everything\n";
        cout << "Choose an option: ";
        cin >> choice;
        option = strToInt(choice);
        system("cls");
        switch(option)
        {
            case 1:
                updateID(record);
                system("cls");
                cout << "!!!UPDATE SUCCESSFUL\n";
                saveToFile();
                system("pause");
                menu();
                break;
            case 2:
                updateFName(record);
                system("cls");
                cout << "!!!UPDATE SUCCESSFUL\n";
                saveToFile();
                system("pause");
                menu();
                break;
            case 3:
                updateLName(record);
                system("cls");
                cout << "!!!UPDATE SUCCESSFUL\n";
                saveToFile();
                system("pause");
                menu();
                break;
            case 4:
                updateDOB(record);
                system("cls");
                cout << "!!!UPDATE SUCCESSFUL\n";
                saveToFile();
                system("pause");
                menu();
                break;
            case 5:
                updateID(record);
                updateFName(record);
                updateLName(record);
                updateDOB(record);
                system("cls");
                cout << "!!!UPDATE SUCCESSFUL\n";
                saveToFile();
                system("pause");
                menu();
                break;
            default:
                system("color F5");
                cout << "!!!YOUR INPUT IS NOT VALID!!!" << endl;
                cout << "Enter numbers between 1 and 4\n";
                system("pause");
                system("cls");
                update();
                break;
        }
    }
    else
    {
        cout << "NO RECORDS! UPDATE CANT BE DONE\n\n";
        system("pause");
        system("cls");
        menu();
    }
}
//Function to delete record
void deleteRecord()
{
    int total = list1.getSize(list1.getHeadNode()), option;
    cout << "\t\t***Delete Record***\n\n";
    if(total > 0)
    {
            total = list1.getSize(list1.getHeadNode());
            cout << "\t\t***Delete Record***\n\n";
            list1.printFoward(list1.getHeadNode(), "no");
            cout << "Delete Record Number: ";
            string tempOption ="";
            cin >> tempOption;
            system("cls");
            option = strToInt(tempOption);
            if (option == 0)
            {
                cout << "\t\t***Delete Record***\n\n";
                cout << "!!!INVALID OPTION!!!" << endl;
                cout << "Enter record that is within range\n";
                system("pause");
                system("cls");
                deleteRecord();
            }
            else
            {
                cout << "\t\t***Delete Record***\n\n";
                cout << "!!!YOU ARE ABOUT TO DELETE A RECORD!!!\n";
                cout << "Enter 1 to confirm deletion otherwise 0 to cancel: ";
                cin >> tempOption;
                system("cls");
                option = strToInt(tempOption);
                switch(option)
                {
                case 0:
                    cout << "\t\t***Delete Record***\n\n";
                    cout << "!!!YOU HAVE CANCLED THE DELETION!!!\n";
                    cout << "Enter continue to go to menu otherwise close the program\n";
                    system("pause");
                    menu();
                    break;
                default:
                    Node *record = list1.getNodeAt(list1.getHeadNode(), option-1);
                    list1.deleteItem(record, option-1);
                    saveToFile();
                    cout << "\t\t***Delete Record***\n\n";
                    cout << "!!!RECORD DELETED SUCCESSFULLY!!!\n";
                    system("pause");
                    system("cls");
                    cout << "\t\t***Delete Record***\n\n";
                    cout << "Enter 1 to delete another item\n";
                    cout << "Enter 2 to go to menu\n";
                    cout << "Enter 3 to exit\n";
                    cout << "Enter choice: ";
                    cin >> tempOption;
                    option = strToInt(tempOption);
                    switch(option)
                    {
                    case 1:
                        deleteRecord();
                        break;
                    case 2:
                        menu();
                        break;
                    case 3:
                        exit(0);
                        break;
                    default:
                        cout << "Invalid Choice...\n";
                        system("pause");
                        break;
                    }
                }
            }
    }
    else
    {
        cout << "\t\t***Delete Record***\n\n";
        cout << "NO RECORDS DELETION CANT TAKE PLACE\n\n";
        system("pause");
        system("cls");
        menu();
    }
}
//Function to update last name
void updateLName(Node *record)
{
                int errIndex=0;
                bool proceed = false;
                string lName;
                do
                {
                    if(errIndex > 0)
                    {
                        errIndex--;
                        system("color F5");
                        cout <<"!!!YOUR INPUT DID NOT NAME STANDARDS!!!"<<endl;
                        cout <<"Your last name seems to contain characters not found in a name."<<endl;
                        system("pause");
                        system("cls");
                    }
                    cout << "OLD LAST NAME: "<<"\t" << record->lName << endl;
                    cout << "Enter New Last Name: ";
                    cin >> lName;
                    errIndex++;
                    system("cls");
                    proceed = testName(lName); //proceed has being set to false by default
                }while(!proceed);
                list1.updateLName(record, lName);
}
//Function to update first name
void updateFName(Node *record)
{
                int errIndex=0;
                bool proceed = false;
                string fName;
                do
                {
                    if(errIndex > 0)
                    {
                        errIndex--;
                        system("color F5");
                        cout <<"!!!YOUR INPUT DID NOT NAME STANDARDS!!!"<<endl;
                        cout <<"Your first name seems to contain characters not found in a name."<<endl;
                        system("pause");
                        system("cls");
                    }
                    cout << "OLD FIRST NAME: "<< record->fName << endl;
                    cout << "Enter New First Name: ";
                    cin >> fName;
                    errIndex++;
                    proceed = testName(fName); //proceed has being set to false by default
                }while(!proceed);
                list1.updateFName(record, fName);
}
//Function to update date of birth
void updateDOB(Node *record)
{
                string DOB;
                bool proceed = false;
                int errIndex = 0;
                do
                {
                    if(errIndex > 0)
                    {
                        errIndex--;
                        system("color F5");
                        cout <<"!!!YOUR INPUT DID NOT MATCH THE REQUIRED FORMAT!!!"<<endl;
                        cout <<"The format should be \'day-month-year\' Example 01-01-1999"<<endl;
                        system("pause");
                        system("cls");
                    }
                    system("color F4");
                    cout << "OLD DATE OF BIRTH: "<<"\t" << record->dob << endl;
                    cout << "Enter New Date of Birth: ";
                    cin >> DOB;
                    proceed = testDate(DOB);
                    errIndex++;
                    system("cls");
                }while (!proceed);
                list1.updateDOB(record, DOB);
}
//Function to update id
void updateID(Node *record)
{
                bool proceed = false;
                int sID, errIndex=0;
                string tempID;
                do
                {
                    if(errIndex > 0)
                    {
                        errIndex--;
                        system("color F4");
                        cout <<"!!!YOUR INPUT DID NOT MATCH THE REQUIRED STANDARDS!!!"<<endl;
                        cout <<"Your id is either beyond 7 digits or has characters that should not be in an id."<<endl;
                        system("pause");
                        system("cls");
                    }
                    system("color 0F");
                    cout << "OLD ID : "<< record->id << endl;
                    cout << "Enter new ID: ";
                    cin >> tempID;
                    errIndex++;
                    proceed = testID(tempID);
                    if(proceed)
                    {
                        stringstream toInt(tempID);
                        toInt >> sID;
                    }
                }while(!proceed);
                list1.updateID(record, sID);
}
//Function to show grades
void showGrade()
{
    system("cls");
    string tempChoice;
    int choice, total  = list1.getSize(list1.getHeadNode());;
    cout <<"\t\t\t***Grades Menu***\n\n";
    cout <<"1. View All Grades\n";
    cout <<"2. Update Student Grade\n";
    cout <<"3. Go Back to Menu\n\n";
    cout <<"Enter your choice: ";
    cin >> tempChoice;
    system("cls");
    choice = strToInt(tempChoice);
    switch(choice)
    {
    case 1:
        if (total > 0)
        {
            cout<<"\t\t\t***All Student Grades***\n\n";
            list1.printFoward(list1.getHeadNode(), "yes");
            system("pause");
            system("cls");
            showGrade();
        }
        else
        {
            cout<<"\t\t\t***All Student Grades***\n\n";
            cout << "NO RECORDS TO SHOW\n\n";
            system("pause");
            system("cls");
            menu();
        }
        break;
    case 2:
        if (total > 0)
            updateGrade();
        else
        {
            cout<<"\t\t\t***All Student Grades***\n\n";
            cout << "NO RECORDS TO SHOW\n\n";
            system("pause");
            system("cls");
            menu();
        }
        break;
    case 3:
        menu();
        break;
    default:
        cout<<"\t\t\t***Grades Menu***\n\n";
        cout << "YOU PRESSED AN INVALID OPTION RETRY\n\n";
        system("pause");
        showGrade();
        break;
    }
}
//Function to update grade
void updateGrade()
{
    cout<<"\t\t\t***Update Student Grade(s)***\n\n";
        int total = 0, choice;
        string tempChoice;
        total = list1.getSize(list1.getHeadNode());
      if (total > 0)
      {
            do
            {
                list1.printFoward(list1.getHeadNode(), "yes");
                cout << "Enter record to update: ";
                cin >> tempChoice;
                system("cls");
                choice = strToInt(tempChoice);
            }while(choice < 0 && choice > total);
            //Create node
            Node *record = list1.getNodeAt(list1.getHeadNode(), choice-1);
            //Code below uses node created above to show data contained by the node.
            cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "Student Grade: "<<"\t\t" << record->grade << endl;
            cout << "Student First Name: "<<"\t" << record->fName << endl;
            cout << "Student Last Name: "<<"\t" << record->lName << endl;
            cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
            cout <<"86% - 100%  --->A+\n";
            cout <<"80% - 85%   --->A\n";
            cout <<"75% - 79%   --->B+\n";
            cout <<"70% - 75%   --->B\n";
            cout <<"56% - 69%   --->C\n";
            cout <<"50% - 55%   --->D\n";
            cout <<"00% - 49%   --->F\n\n";
            cout << "Enter new Student Grade: ";
            string newGrade = "";
            cin >>newGrade;
            system("cls");
            list1.updateGrade(record, newGrade);
            cout << "\t\t\t***Grades Menu***\n\n";
            cout << record->fName <<" "<<record->lName <<"'s Grades Updated Successfully\n";
            saveToFile();
            system("pause");
            system("cls");
            showGrade();
      }
      else
      {
          system("color F5");
            cout << "\t\t\t***Grades Menu***\n\n";
            cout << "!!!NO RECORDS!!!" << endl;
            cout << "Seems like the list is empty\n";
            system("pause");
            system("cls");
            menu();
      }
}
//Function to convert a string to an interger
int strToInt(string value)
{
    int result=0;
    stringstream change(value);
    change >> result;
    return result;
}
