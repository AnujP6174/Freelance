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
    file.open("grades_Section1.txt");
    string s;

    while (getline(file, s))
    {
        //Splitting whole fetched line by a " " (space)

        string buf;         // Have a buffer string
        stringstream ss(s); // Insert the string into a stream

        vector<string> tokens; // Create vector to hold our words

        while (ss >> buf)
        {
            tokens.push_back(buf);
        }

        //Creating objects of structures and assigning data to them;
        string full_name = tokens[0] + " " + tokens[1];
        int total_scores;
        vector<int> marks;

        if (!isNumber(tokens[2]))
        {
            full_name = full_name + " " + tokens[2];

            //Typecasting the tokens[3] to int total_scores;
            stringstream number(tokens[3]);
            number >> total_scores;

            for (int j = 4; j < 4 + total_scores; j++)
            {
                int mark_temp;
                stringstream marks_typecasting(tokens[j]);
                marks_typecasting >> mark_temp;
                marks.push_back(mark_temp);
            }
        }
        else
        {
            //Typecasting the tokens[2] to an integer first;
            stringstream number(tokens[2]);
            number >> total_scores;

            for (int j = 3; j < 3 + total_scores; j++)
            {
                int mark_temp;
                stringstream marks_typecasting(tokens[j]);
                marks_typecasting >> mark_temp;
                marks.push_back(mark_temp);
            }
        }

        float average = 0;

        for (auto i : marks)
        {
            average += i;
        }
        average = average / total_scores;

        //Setting the grade
        string Grade;
        if (average >= 95 && average <= 100)
        {
            Grade = "A";
        }
        else if (average >= 91.67 && average <= 95)
        {
            Grade = "A-";
        }
        else if (average >= 88.33 && average <= 91.67)
        {
            Grade = "B+";
        }
        else if (average >= 85 && average <= 88.3)
        {
            Grade = "B";
        }
        else if (average >= 81.67 && average <= 85)
        {
            Grade = "B-";
        }
        else if (average >= 78.33 && average <= 81.67)
        {
            Grade = "C+";
        }
        else if (average >= 75 && average <= 78.33)
        {
            Grade = "C";
        }
        else if (average >= 71.67 && average <= 75)
        {
            Grade = "C-";
        }
        else if (average >= 68.33 && average <= 71.67)
        {
            Grade = "D+";
        }
        else if (average >= 65 && average <= 68.33)
        {
            Grade = "D";
        }
        else if (average >= 61.67 && average <= 65)
        {
            Grade = "D-";
        }
        else if (average >= 0 && average <= 61.67)
        {
            Grade = "F";
        }
        cout << full_name << endl;
        cout << "Average : " << average << endl;
        cout << "Grade : " << Grade << endl;
        cout << "\n\n\n";

        ofstream file;
        file.open("Student_info.txt", ios_base::app);

        file << full_name;
        file << "\nTotal exam scores : " << total_scores;
        file << "\nExam Scores : ";
        for (auto i : marks)
        {
            file << i << " ";
        }
        file << "\nAverage Score : " << average;
        file << "\nGrade obtained :" << Grade;
        file << "\n\n";
    }

    return 0;
}
