# Student-Information-System

### Description
For this project, I implemented Student Information System in C++.

### Usage

* Write terminal _"make"_ to run.
* courses_classrooms.txt include courses and classrooms in university.
  * Courses's format in txt:
    
    ID, NAME, CODE, CREDIT, TOTAL HOURS, FIELD
  * Classroom's format in txt:
    
    ID, CLASSROOM_NO, CAPACITY
* lecturers.txt include lecturers in university.
  * Lecturer's format in txt:
    
    NAME, SURNAME, PERSONAL_ID, TITLE, PROFESSIONS
* Write terminal _"make clean"_ to delete object code that created if you need.
    
### USER GUIDE
* You can add student to system by this command

  **-ns STUDENT_NAME STUDENT_SURNAME STUDENT_NUMBER STUDENT_LEVEL**
* You can enroll student to course by this command
  
  **-e STUDENT_NUMBER COURSE_ID**
* You can disenroll student to course by this command
  
  **-de STUDENT_NUMBER COURSE_ID**
* You can extract one student's schedule by this command
  
  **-o STUDENT_NUMBER**
* You can extract all student's schedule by this command
  
  **-o**
* You can extract all student's schedule to txt file by this command
  
  **-o -f FILENAME.TXT**
* Lecturer can propose elective courses by this command
  
  **-propose LECTURER_ID COURSE_NAME COURSE_CODE COURSE_CREDIT_ COURSE_TOTAL_HOURS COURSE_FIELD**
* You can assign course to lecturer by this command
  
  **-assign LECTURER_ID COURSE_ID**
* You can assign all course to lecturers automatically by this command
  
  **-assign**
* You can arrange one course's timetable randomly by this command

  **-timetable COURSE_ID**
* You can arrange all course's timetable randomly by this command

  **-timetable**
* You can arrange one course's classroom by this command
  * **-arrangeC COURSE_ID CLASSROOM_ID**
  * **-arrangeC COURSE_ID,CLASSROOM_ID CLASSROOM_ID**
  
  _Course can not be more than two days in a week_
* You can arrange all course's classroom automatically by this command

  **-arrangeC**
* Lecturer can get attendace record of courses s/he gives by this command 
  * **-enter STUDENT_ID CLASSROOM_ID HOUR_OF_WEEK**
  * **-quit STUDENT_ID**
* You can extract attendance record for course by this command

  **-attendance**


### Contact
osenturk@gtu.edu.tr

### License
[Apache License 2.0](https://choosealicense.com/licenses/apache-2.0/)


