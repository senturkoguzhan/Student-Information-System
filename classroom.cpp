/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                 					             */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "classroom.h"

namespace ClasroomNS
{
	void Classroom::attendance(int course_id,int student_id) // function to calculate attendance of course
	{
		int course_index; 
		int new_student = 1;	// if new student enter classroom
		for (course_index = 0; course_index < course_name.size(); ++course_index) // which course given by class at that moment
		{
			if(course_name[course_index]->id == course_id)
			{
				break;
			}
		}

		if (course_name[course_index]->attendance_rec == nullptr) // first student
		{
			course_name[course_index]->student_count  = 1;
		 	course_name[course_index]->attendance_rec = new int*[course_name[course_index]->student_count ]; // dynamic allocation
		 	course_name[course_index]->attendance_rec[0] = new int[2];	// dynamic allocation
		 	course_name[course_index]->attendance_rec[0][0] =student_id;
		 	course_name[course_index]->attendance_rec[0][1] = 1;
		}
		else
		{
			for (int i = 0; i < course_name[course_index]->student_count ; ++i) // same student
			{
				if(student_id == course_name[course_index]->attendance_rec[i][0])
				{
					course_name[course_index]->attendance_rec[i][1]++;
					new_student = 0;
					break;
				}
			}
			if(new_student == 1)	// new student
			{
				course_name[course_index]->student_count  ++;
				int** temp = new int*[course_name[course_index]->student_count ];
				for (int i = 0; i < course_name[course_index]->student_count ; ++i) // dynamic allocation
				{
					temp[i]= new int[2];
				}
				for (int i = 0; i < course_name[course_index]->student_count -1; ++i) // copy old array to new array
				{
					temp[i][0] = course_name[course_index]->attendance_rec[i][0];
					temp[i][1] = course_name[course_index]->attendance_rec[i][1];
				}
				for (int i = 0; i < course_name[course_index]->student_count -1; ++i) // delete old array
				{
					delete[] course_name[course_index]->attendance_rec[i];
				}
				delete[] course_name[course_index]->attendance_rec;	
				course_name[course_index]->attendance_rec = temp; // old array is new array
				course_name[course_index]->attendance_rec[course_name[course_index]->student_count -1][0] = student_id;
		 		course_name[course_index]->attendance_rec[course_name[course_index]->student_count -1][1] = 1;
			}
		} 
	}
	Classroom& Classroom::operator = (const Classroom& rightside)
	{
		if(this == &rightside)
		{
			return *this;
		}
		else
		{
			id = rightside.id;
			c_no = rightside.c_no;
			capacity = rightside.capacity;
			student_inroom = rightside.student_inroom;
			int_date = rightside.int_date;
			course_name = rightside.course_name;
		}
	}
	Classroom::~Classroom()
	{
		
	}
	Classroom::Classroom(const Classroom& classroom_object)
	{
		id = classroom_object.id;
		c_no = classroom_object.c_no;
		capacity = classroom_object.capacity;
		student_inroom = classroom_object.student_inroom;
		int_date = classroom_object.int_date;
		course_name = classroom_object.course_name;
	}
	Classroom::Classroom()
	{
		
	}
}
