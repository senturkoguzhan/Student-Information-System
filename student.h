/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                      			                     */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include "classroom.h"
using namespace std;

namespace StudentNS
{
	using namespace ClasroomNS;
	class Student
	{
	public:
		int enroll_course(Course lecture);
		int disenroll_course(Course lecture);
		string extract_schedule();
		void enter_classroom(Classroom& class_room,int student_id,int date_of_week);
		void quit_classroom(Classroom& class_room);
		void setter(string name1,string surname1,int student_no1,int level1);
		bool overlap(Course lec);
		int find_course_id(Classroom class_room,int date_of_week); 
		int getter_student_no();
		int getter_student_credit();
		int getter_student_level();
		int getter_student_busy();
		int getter_student_class_id();
		string getter_student_name();
		string getter_student_surname();
		Student& operator = (const Student& rightside);
		~Student();
		Student(const Student& student_object);
		Student();


	private:
		int class_id;
		string name;
		string surname;
		int student_no;
		int level;
		int stu_credit;
		int busy;
		vector<Course> schedule;
	};
}
#endif
