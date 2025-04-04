#ifndef _MANAGE_H_
#define _MANAGE_H_


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#define STUDENT 1
#define ADMIN 2

#define FIRST_HOUR 8
#define LAST_HOUR 18


#define TOTAL_CLASSES_SIZE 9
#define TOTAL_CLASSES {"M-300","M-305","M-310","M-400","M-405","M-410","M-500","M-505","M-510"}

#define COURSE_ID_SIZE 5
#define CREDIT_PAY 100

#include <iostream>
#include <string>
#include <exception>
#include <fstream> 
#include <sstream> 
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <unordered_map>

using namespace std;


#include "Course.h"
#include "Person.h"



class Manage
{

private:

	//vector< unique_ptr<Person> > persons;
	//vector< Course > courses;

	unordered_map<int, unique_ptr<Person> > persons;
	unordered_map<int, Course > courses;

	//to know how to print next ten courses
	int number_course;



public:

	Manage();
	~Manage();


	void read_persons();
	void write_persons() const;
	void read_courses();
	void write_courses() const;

	void start();

	void print_by_courseid(int course_id) const;
	void print_ten_courses();
	void print_more_ten();
	void print_persons() const;



	//student





	void print_schedule(Student& student, int schedule_id);
	void print_all(Student& student);
	void add_schedule(Student& student);
	void rm_schedule(Student& student, stringstream& ss);
	void add_course_schedule(Student& student, stringstream& ss);
	void rm_course_schedule(Student& student, stringstream& ss);
	void search_course_id(const string& str);




	void add_course(); //check if course valid
	void add_specific_lesson(int course_id, const string& lesson);
	void add_lesson(int course_id, const string& lesson);
	int check_class_available(int course_id, int start_time, int end_time, int day, const string& class_name) const;
	int check_class_exist(const string& s) const;
	void check_class_lesson(const vector<Lesson>& l, int& avilable, int start_time, int end_time, int day, const string& class_name) const;
	void print_all_classes() const;
	int check_teacher_exist(const string& name) const;
	void print_all_teachers() const;



	void rm_course(stringstream& ss);
	void add_lecturer();
	void rm_lecturer(stringstream& ss);
	void add_student();
	bool rm_student(stringstream& ss);
	void search_text(stringstream& ss); //add const

	void search_course(const string& text) const;
	void search_lesson(const string& text) const;
	void search_person(const string& text) const;



	int join();
	int id_exist() const;
	bool id_type_match(const int& id, const string& type);
	int id_valid() const;
	int course_id_valid() const;

	string name_valid(const string& person) const;
	bool password_valid(int id);
	bool password_admin(int id);

	void promote(stringstream& ss_id);
	void add_lesson_course(stringstream& ss);
	void rm_lesson_course(stringstream& ss);

	const unordered_map<int, Course >& get_courses() const;
	const unordered_map<int, unique_ptr<Person> >& get_persons() const;

	bool check_valid_id(int course_id, int schedule_id, Student& student) const;
	int get_payment(int student_id, int schedule_id);


};


//bool check_valid_id(int course_id, int schedule_id, Student& student, Manage& manager);
bool time_valid(int i, int day, const Lesson& lesson);
void check_course_print(int& another_check, int i, int n, Lesson& lesson,
	unordered_map< int, array<int, 3> >& scheudle, const vector<Course>& s_courses);
void print_lines();
void print_days();
void search_by_parameter(const Manage& manage, int parameter);

template <typename T>
bool search_course(const unordered_map<int, Course>& courses, T text)
{

	auto it = find_if(courses.begin(), courses.end(),
		[text](const pair<const int, Course>& course)
		{


			if constexpr (is_same_v<T, int>)
			{

				return course.second.get_id() == (text);

			}

			else if constexpr (is_same_v<T, string>)
			{
				return course.second.get_course_name() == text || course.second.get_teacher_name() == text;

			}
			else if constexpr (is_same_v<T, double>)
			{
				return course.second.get_credit_points() == (text);

			}
		});




	if (it != courses.end())
	{
		cout << "Found course" << endl;
		cout << it->second;
		return 1;

	}
	else
		return 0;
}


void search_lessons(const string& text, const vector<Lesson>& lessons, int id, const string& lesson);



#endif