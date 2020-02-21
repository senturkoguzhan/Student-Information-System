/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                       			                     */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/

#ifndef LECTURER_H
#define LECTURER_H

#include <iostream>
#include <string>
#include <vector>
#include "classroom.h"

using namespace std;

namespace LecturerNS
{
	class Lecturer
	{
	public:
		void proposeCourse(string course_data);
		void assignCourse(Course course1, Course lecture[], int& number_of_lectures);
		int assignCourse_automatic(Course course1, Course lecture[], int& number_of_lectures);
		string getter_lecturer_name();
		string getter_lecturer_surname();
		int getter_lecturer_personal_id();
		string getter_lecturer_title();
		void setter_lecturer_name(string name1);
		void setter_lecturer_surname(string surname1);
		void setter_lecturer_personal_id(int personal_id1);
		void setter_lecturer_title(string title1);
		void setter_lecturer_professions(string proffesions1);
		vector <string> professions; 
		vector<Course> courses;
		vector<Course> propose_courses;
		vector<Course> must_take_course;
		Lecturer& operator = (const Lecturer& rightside);
		~Lecturer();
		Lecturer(const Lecturer& lecturer_object);
		Lecturer();
	private:
		string name; 
		string surname; 
		int personal_id; 
		string title; 
	};
}
#endif
