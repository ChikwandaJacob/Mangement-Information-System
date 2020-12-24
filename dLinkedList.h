#ifndef DLINKEDLIST_H_INCLUDED
#define DLINKEDLIST_H_INCLUDED
#endif // DLINKEDLIST_H_INCLUDED
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Node
{
    string fName, lName, dob, grade;
    int id;
    Node *nextNode;
    Node *prevNode;
};

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
    void add(Node *node, int id, string fname, string lname, string dob, string grade)
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
            cout <<"Index"<<"\t\tStudent ID\t\tFirst Name\t\tLast Name\t\tGrade"<<endl;
        else if (showGrade == "no")
            cout <<"Index"<<"\t\tStudent ID\t\tFirst Name\t\tLast Name\t\tDate of Birth"<<endl;
        while (i < total)
            {
                i++;
                if (showGrade == "yes")
                    cout <<i<<".\t\t"<< node->id<<"\t\t\t"<<node->fName<<"\t\t\t"<<node->lName<<"\t\t"<<node->grade<< endl;
                else if (showGrade == "no")
                    cout <<i<<".\t\t"<< node->id<<"\t\t\t"<<node->fName<<"\t\t\t"<<node->lName<<"\t\t"<<node->dob<< endl;
                node = node->nextNode;
            }
    }
   /* void printBackward(Node *node)
    {
        int total = getSize(node), i=0;
        while(i<total)
        {
            i++;
            cout <<i<<". "<< node->data << endl;
            node = node->prevNode;
        }
    }*/
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
