/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                       			                     */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/

#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

	struct Course
	{
		int id;
		string name;
		int code;
		int credit;
		int total_hours;
		string lecture_dates;
		string field;
		int isMandotary;
		vector<string> class_name;
		int student_count = 0;
		int **attendance_rec = nullptr;
		~Course()
		{
			if(attendance_rec) // if attendance_rec point any memory location instead of nullptr
			{
				for (int i = 0; i < student_count; ++i)
				{
					delete[] attendance_rec[i];
				}
				delete[] attendance_rec;
			}
			attendance_rec = nullptr; // prevent dangling pointer
		}
	};

namespace ClasroomNS
{
	class Classroom
	{
	public:
		int id;
		string c_no;
		int capacity;
		int student_inroom;
		vector<int> int_date;
		vector<Course*> course_name;
		void attendance(int course_id,int student_id);
		Classroom& operator = (const Classroom& rightside);
		~Classroom();
		Classroom(const Classroom& classroom_object);
		Classroom();

	};

}
#endif
