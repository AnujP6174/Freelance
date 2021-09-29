#include <iostream>
#include <fstream>
#include <ctype.h>
#include <vector>
#include <sstream>
#include "isnum.h"
using namespace std;


int main()
{
    ifstream file;
    string name_array[25];
    int name_array_index = 0;
    file.open("grades_Section2.txt");
    string s;

    int total_students = 0;
    int total_marks = 0;
    //First we will only read the first line of the file
    if (getline(file, s))
    {
        vector<int> array_indices;
        string buf;
        stringstream ss(s);
        while (ss >> buf)
        {
            int temp;
            //Typecasting to int
            stringstream buf_to_int(buf);
            buf_to_int >> temp;
            array_indices.push_back(temp);
        }
        file.close();
        total_students = array_indices[0];
        total_marks = array_indices[1];
    }

    file.open("grades_Section2.txt");
    int flag_for_first_line = 0; //First line scanned if 1

    int student_record[total_students][total_marks];
    int student_counter_row = 0;
    float average[total_marks];
    char grades[total_students][total_marks];
    vector<string> full_names;

    while (getline(file, s))
    {
        //Splitting whole fetched line by a " " (space)

        string buf;         // Have a buffer string
        stringstream ss(s); // Insert the string into a stream

        vector<string> tokens; // Create vector to hold our words

        //Typecasting all line chars into string and adding them to a vector
        while (ss >> buf)
        {
            tokens.push_back(buf);
        }

        //Checking logic for 1st line only
        if (isNumber(tokens[0]) && isNumber(tokens[1]) && flag_for_first_line == 0)
        {
            stringstream index0(tokens[0]);
            stringstream index1(tokens[1]);

            index0 >> total_students;
            index1 >> total_marks;

            cout << total_students << " ";
            cout << total_marks << endl;
            flag_for_first_line = 1;
        }
        else
        {
            //int student_record[total_students][total_marks];
            string full_name;

            full_name = tokens[0] + " " + tokens[1];
            if (!isNumber(tokens[2]))
            {
                full_name = full_name + " " + tokens[2];
                full_names.push_back(full_name);

                //We will execute a loop from token[3] to total_marks+3 and scan the marks in array
                for (int j = 0; j < total_marks; j++)
                {
                    stringstream mark_typecasting(tokens[j + 3]);
                    int temp_mark;
                    mark_typecasting >> temp_mark;
                    //cout<<temp_mark<< " ";
                    student_record[student_counter_row][j] = temp_mark;
                }
                student_counter_row = student_counter_row + 1;
            }
            else
            {
                full_names.push_back(full_name);
                //We will execute a loop from token[2] to total_marks+2 and scan the marks in array
                for (int j = 0; j < total_marks; j++)
                {
                    stringstream mark_typecasting(tokens[2 + j]);
                    int temp_mark;
                    mark_typecasting >> temp_mark;
                    //cout<<temp_mark<< " ";
                    student_record[student_counter_row][j] = temp_mark;
                }
                student_counter_row = student_counter_row + 1;
            }
            cout << full_name + " " << endl;
        }
    }

    for (int i = 0; i < total_marks; i++)
    {
        float exam_average = 0;
        for (int j = 0; j < total_students; j++)
        {
            exam_average += student_record[j][i];
        }
        exam_average = exam_average / total_students;
        average[i] = exam_average;
    }
    cout << "================================================" << endl;
    for (int i = 0; i < total_marks; i++)
    {
        cout << average[i] << " ";
    }

    for (int i = 0; i < total_students; i++)
    {
        for (int j = 0; j < total_marks; j++)
        {
            char Grade;
            if (student_record[i][j] <= average[j] + 5 && student_record[i][j] >= average[j] - 5)
            { //94<=99 or 84>=99  is 99 <= 94 and 99>=84
                Grade = 'C';
            }
            if (student_record[i][j] > average[j] + 5)
            {
                Grade = 'B';
            }
            if (student_record[i][j] < average[j] - 5)
            {
                Grade = 'D';
            }
            if (student_record[i][j] > average[j] + 15)
            {
                Grade = 'A';
            }
            if (student_record[i][j] < average[j] - 15)
            {
                Grade = 'F';
            }
            grades[i][j] = Grade;
        }
    }
    cout << "\n===============================================" << endl;
    for (int i = 0; i < total_students; i++)
    {
        for (int j = 0; j < total_marks; j++)
        {
            cout << student_record[i][j] << " ";
            cout << grades[i][j] << " ";
        }
        cout << endl;
    }

    ofstream outfile;
    outfile.open("Student_records.txt");

    for (int i = 0; i < total_students; i++)
    {
        outfile << "Full name : " << full_names[i];
        outfile << "\n";
        outfile << "Scores : ";
        for (int j = 0; j < total_marks; j++)
        {
            outfile << student_record[i][j];
            outfile << " ";
        }
        outfile << "\nGrades: ";
        for (int l = 0; l < total_marks; l++)
        {
            outfile << grades[i][l] << " ";
        }
        outfile << "\n\n";
    }
    outfile.close();
    return 0;
}
