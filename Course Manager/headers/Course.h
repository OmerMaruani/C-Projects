#ifndef _COURSE_H_
#define _COURSE_H_




class Lesson
{

private:
	int team_number;
	int day;
	int starting_time;
	int during_time;
	string teacher_name;
	string class_name;




public:



	Lesson(const int t, const int d, const int s, const int during_time, const string& name, const string& class_name);
	Lesson();
	Lesson(const Lesson& lesson);
	~Lesson();


	int get_team_number() const;
	int get_day() const;
	int get_starting_time() const;
	int get_during_time() const;
	string get_teacher_name() const;
	string get_class_name() const;


	void set_team_number(const int n);
	void set_day(const int n);
	void set_starting_time(const int n);
	void set_during_time(const int n);
	void set_teacher_name(const string& name);
	void set_class_name(const string& name);


	friend ostream& operator<<(ostream& os, const Lesson& lesson);
	bool operator==(int id) const;

	string serialization() const;

	Lesson& operator=(const Lesson& lesson);



};


ostream& operator<<(ostream& os, const Lesson& lesson);





class Course {



private:

	int id;
	string course_name;
	string teacher_name;
	double credit_points;

	//map <int,Lesson> lectures;
	//map <int,Lesson> tutorials;
	//map <int,Lesson> labs;

	//not using Array because this one can be changed.
	vector<Lesson> lectures;
	vector<Lesson> tutorials;
	vector<Lesson> labs;




public:

	//Course(const int id,const string&name, const string& teacher,const int c_points,const Lesson& l1,const Lesson& l2,const Lesson& l3);
	Course(const int id, const string& name, const string& teacher, const int c_points);
	Course(const Course& course);
	Course();
	~Course();


	friend ostream& operator<<(ostream& os, const Course& course);


	int get_id() const;
	string get_course_name() const;
	string get_teacher_name() const;
	double get_credit_points() const;
	vector<Lesson> get_lectures() const;
	vector<Lesson> get_tutorials() const;
	vector<Lesson> get_labs() const;


	bool get_lecture(int group_id, Lesson& lesson) const;//sometimes return 0 when not found
	bool get_tutorial(int group_id, Lesson& lesson) const;
	bool get_lab(int group_id, Lesson& lesson) const;



	static int get_number_courses();

	void set_id(const int id);
	void set_course_name(const string& name);
	void set_teacher_name(const string& name);
	void set_credit_points(const double c_points);
	void set_lecture(const Lesson& l);
	void set_tutorial(const Lesson& l);
	void set_lab(const Lesson& l);
	//int check_team_exist(int n) const;

	void pop_lecture_lesson(int i);
	void pop_tutorial_lesson(int i);
	void pop_lab_lesson(int i);




	static unordered_map<int, Course >  readFromCSV(const string& filename);
	static int writeForCSV(const string& filename, const unordered_map<int, Course >& courses);

	string serialization() const;

	Course& operator=(const Course& course);
	//void print_lesson(int group_id);





};

ostream& operator<<(ostream& os, const Course& course);





typedef  void(Course::* set_method)(const Lesson& l);//defined a pointer to method : set_lesson(const Lesson& l) ; 
void fileSetLesson(const string& lesson_name, set_method set_lesson, Course& course);

bool const get_lesson(int group_id, Lesson& lesson, const vector<Lesson>& lesson_vector);
ofstream open_lesson_file(const string& file_name, const Course& course);
ofstream open_course_file(const string& file_name);

typedef vector<Lesson>(Course::* get_method)() const; // a pointer to Course method that has empty parameters : Course.func()
void write_lesson_to_csv(ofstream& file, const Course& course, get_method get_lessons);

void remove_lessons(const string& string_id, const string& lesson);

/*
void set_lecture_wrapper(Course& course, const Lesson& lesson);
void set_tutorial_wrapper(Course& course, const Lesson& lesson);
void set_lab_wrapper(Course& course, const Lesson& lesson);
*/


#endif