#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

struct student *head = NULL; /* Global Student List */

char* itoa(int i, char b[]) {
	char const digit[] = "0123456789";
	char* p = b;
	int shifter = i;

	do {
		++p;
		shifter /= 10;
	} while(shifter);

	*p = '\0';

	do {
		*--p = digit[i%10];
		i /= 10;
	} while(i);
	return b;
}

/*
 * This function reads the input file in text format and stores it in memory.
 * See sample input file for format.
 * Lines starting with '#' are comments and must be ignored.
 * If there is an error in input text format, the error string must contain the
 * line number where the error occurred.
 * Also, upon error, all allocated memory must be freed.
 */
struct student* read_txt(char *filename, char *error_string) {
	FILE *fp;
	char line[512];
	int count = 1;		/* Keeps track of line number for error_string */

	/* To Check if Inside Student/Course */
	int in_student = 0;	/* 0 = not in student | 1 = in student */
	int in_course = 0;	/* 0 = not in course  | 1 = in course */

	/* To Create Students */
	char name[MAX_NAME_LEN];
	unsigned int age = 0;
	SEX sex = 0;
	float gpa = 0;

	/* To Create Courses */
	char grade = 0;
	unsigned int number = 0;

	/* Open File - Read Only */
	fp = fopen(filename, "r");

	/* Check for NULL File */
	if(fp == NULL) {
	       	error_string = "-1";
		delete_all();
		return NULL;
	}

	/* Process File Line by Line */
	while(fgets(line, sizeof(line), fp)) {
		/* Check for Comment */
		if(strstr(line, "#"));
		/* Check for Student Opening Bracket */
		else if(strstr(line, "student {") != '\0') {
			if(in_student == 1) {
				sprintf(error_string, "%d", count);
				delete_all();
				break;
			}
			in_student = 1;
		}
		/* Check for Course Opening Bracket */
		else if(strstr(line, "course {") != '\0') {
			if(in_course == 1) {
				sprintf(error_string, "%d", count);
				delete_all();
				break;
			}
			in_course = 1;
			if(in_student == 1) {
				enroll_student(&name[0], age, sex, gpa);
				in_student = 0;
			}
		}
		/* Check for Student Name */
		else if(strstr(line, "name") != '\0') {
			strcpy(name, strstr(line, "=")+2);
			name[strlen(name)-1] = '\0';
		}
		/* Check for Student Age */
		else if(strstr(line, "age") != '\0') {
			age = atoi(strstr(line, "=")+2);
			if(age <= 0) {
			       	sprintf(error_string, "%d",  count);
				delete_all();
				break;
			}
		}
		/* Check for Student Sex */
		else if(strstr(line, "sex") != '\0') {
			if(strstr(line, "M") != '\0') sex = MALE;
			else if(strstr(line, "F") != '\0') sex = FEMALE;
			else if(strstr(line, "O") != '\0') sex = OTHER;
			else {
			       	sprintf(error_string, "%d", count);
				delete_all();
				break;
			}
		}
		/* Check for Student GPA */
		else if(strstr(line, "gpa") != '\0') {
			gpa = atof(strstr(line, "=")+2);
			if(gpa < 0 || gpa > 4) {
			       	sprintf(error_string, "%d", count);
				delete_all();
				break;
			}
		}
		/* Check for Course Number */
		else if(strstr(line, "number") != '\0') {
			number = atoi(strstr(line, "=")+2);
			if(number <= 0) {
				sprintf(error_string, "%d", count);
				delete_all();
				break;
			}
		}
		/* Check for Course Grade */
		else if(strstr(line, "grade") != '\0') {
			grade = (strstr(line, "=")+2)[0];
			if(!(grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F')) {
				sprintf(error_string, "%d", count);
				delete_all();
				break;
			}
		}
		/* Check for Closing Bracket */
		else if(strstr(line, "}") != '\0') {
			if(in_student == 1) {
				enroll_student(name, age, sex, gpa);
				in_student = 0;
			} else if(in_course == 1) {
				add_course(name, number, grade);
				in_course = 0;
			}
		}

		/* Increment for Line Numbers */
		count++;
	}

	fclose(fp);
	return head;
}

/*
 * This function writes the student list and the courses to a file in text format.
 * The first line should contain a string:
 * "# Auto generated output file!"
 * The students are written in alphabetical order (dictionary order),
 * and the courses are written in numerically increasing order.
 * That is, high numbered courses follow lower numbered courses.
 */
ERROR_CODE write_txt(char *filename, char *error_string) {
	FILE *fp;
	struct student* list = head;
	struct course* clist;

	fp = fopen(filename, "w+");

	if(fp == NULL) return FAILURE;

	if(list == NULL) {
		fclose(fp);
		return SUCCESS;
	}

	fprintf(fp, "# Auto generated output file!\n\n");

	while(list != NULL && list->courses != NULL) {
		fprintf(fp, "student {\n");
		fprintf(fp, "\tname = %s\n", list->name);
		fprintf(fp, "\tage = %d\n", list->age);
		fprintf(fp, "\tsex = %c\n", list->sex);
		fprintf(fp, "\tgpa = %f\n", list->gpa);

		clist = list->courses;

		while(clist != NULL) {
			fprintf(fp, "\tcourse {\n");
			fprintf(fp, "\t\tnumber = %d\n", clist->number);
			fprintf(fp, "\t\tgrade = %c\n", clist->grade);
			fprintf(fp, "\t}\n");
			clist = clist->next;
		}

		fprintf(fp, "}\n\n");
		list = list->next;
	}

	fclose(fp);
	return SUCCESS;
}

/*
 * Bin format sample (also see sample file included using the hexdump program):
 * 0xF0 0x0D
 * # students
 * student 1.name[32]
 * student 1.age
 * student 1.sex
 * student 1.gpa
 * number of courses for student 1
 * student1.course1.number
 * student1.course1.grade
 * student1.course2.number
 * student1.course2.grade
 * student 2.name[32]
 * ...
 * ...
 */
struct student* read_bin(char *filename, char *error_string) {
	FILE *fp;
	char buffer[32];
	unsigned int students;
	unsigned int courses;
	char error[10];
	int i, j, k;
	int count = 1;

	/* To Create Students */
	char name[MAX_NAME_LEN];
	unsigned int age = 0;
	SEX sex = 0;
	float gpa = 0;

	/* To Create Courses */
	char grade = 0;
	unsigned int number = 0;

	/* Open File - Read Only Binary */
	fp = fopen(filename, "rb");

	/* Check for NULL File */
	if(fp == NULL) {
		error_string = "-1";
		delete_all();
	}

	/* 0xF0 0x0D */
	fread(buffer, sizeof(char), 2, fp);

	/* Reset Buffer */
	for(j = 0; j < 2; j++) buffer[j] = '\0';

	/* # of Students */
	fread(buffer, sizeof(unsigned int), 1, fp);
	students = buffer[0] + buffer[1] + buffer[2] + buffer[3];

	/* Reset Buffer */
	for(j = 0; j < 4; j++) buffer[j] = '\0';

	/* Enter Student Creation */
	for(i = 0; i < students; i++) {
		/* Process Student Data */
		fread(&name, sizeof(buffer), 1, fp);
		fread(&age, sizeof(age), 1, fp);
		fread(&sex, sizeof(sex), 1, fp);
		fread(&gpa, sizeof(gpa), 1, fp);

		/* Create Student */
		enroll_student(name, age, sex, gpa);

		/* # of Courses */
		fread(buffer, sizeof(unsigned int), 1, fp);
		courses = buffer[0] + buffer[1] + buffer[2] + buffer[3];

		/* Reset Buffer */
		for(j = 0; j < 4; j++) buffer[j] = '\0';

		/* Enter Course Creation */
		for(k = 0; k < courses; k++) {
			/* Process Course Data */
			fread(&number, sizeof(unsigned int), 1, fp);
			fread(&grade, sizeof(char), 1, fp);

			/* Create Course */
			add_course(name, number, grade);
		}
	}

	fclose(fp);
	return head;
}

/*
 * This function writes the student list and the courses to a file in binary format.
 * The first two bytes must be 0xF0 and 0x0D.
 * The students are written in alphabetical order (dictionary order),
 * and the courses are written in numerically increasing order.
 * That is, higher numbered courses follow lower numbered courses.
 * SUCCESS of FAILURE is appropriately returned.
 * The error string must contain an informative error message.
 */
ERROR_CODE write_bin(char *filename, char *error_string) {
	FILE *fp;
	struct student* list = head;
	struct course* clist;
	unsigned char buffer[2];
	int count_students = 0;
	int count_courses = 0;

	fp = fopen(filename, "wb");

	if(fp == NULL) return FAILURE;

	if(list == NULL) {
		fclose(fp);
		return SUCCESS;
	}

	buffer[0] = 0xF0;
	buffer[1] = 0x0D;

	fwrite(buffer, sizeof(buffer), 1, fp);

	while(list != NULL) {
		if(list->courses != NULL) {
			count_students++;
		}
		list = list->next;
	}

	fwrite(&count_students, 2*sizeof(buffer), 1, fp);

	list = head;

	while(list != NULL && list->courses != NULL) {
		clist = list->courses;
		fwrite(list->name, sizeof(list->name), 1, fp);
		fwrite(&list->age, sizeof(list->age), 1, fp);
		fwrite(&list->sex, sizeof(list->sex), 1, fp);
		fwrite(&list->gpa, sizeof(list->gpa), 1, fp);

		count_courses = 0;
		if(clist != NULL) {
			while(clist != NULL) {
				count_courses++;
				clist = clist->next;
			}
		}

		fwrite(&count_courses, 2*sizeof(buffer), 1, fp);

		clist = list->courses;

		while(clist != NULL) {
			fwrite(&clist->number, sizeof(clist->number), 1, fp);
			fwrite(&clist->grade, sizeof(clist->grade), 1, fp);
			clist = clist->next;
		}
		list = list->next;
	}

	fclose(fp);
	return SUCCESS;
}

/*
 * This function creates a new student and stores it in its appropriate position (following dictionary order)
 * in the list. A pointer to the newly added student structure is returned.
 */
struct student* enroll_student(char *name, unsigned int age, SEX sex, float gpa) {
	struct student* list = head; /* Temporary Student List */
	struct student* new_student = (struct student *) calloc (1, sizeof(struct student)); /* New Student to Return */
	struct student* previous = NULL; /* Previous Student */
	int count = 0;

	/* Fill student data in structure */
	strcpy(new_student->name, name);
	new_student->age = age;
	new_student->sex = sex;
	new_student->gpa = gpa;

	/* Check to see if this is the furst student */
	if(list == NULL) {
		head = new_student;
		head->next = NULL;
		return new_student;
	}

	/* Two students will not have the same name, don't need to worry about this case. */

	/* If not the first student, put into correct place in list */
	while(list != NULL) {
		if(strcmp(list->name, new_student->name) > 0) {
			if(previous == NULL) {
				head = new_student;
				head->next = list;
			} else {
				previous->next = new_student;
				new_student->next = list;
			}
			return new_student;
		}
		else if(list->next == NULL) {
			list->next = new_student;
			break;
		} else {
			previous = list;
			list = list->next;
		}
	}

	return new_student;
}

/*
 * This function removes a student given the name (case sensitive).
 * A pointer to the removed student structure is returned.
 */
struct student* remove_student(char *name) {
	struct student* list = head; /* Temporary Student List */
	struct student* previous; /* Previous Student */

	/* Check if name matches the first student */
	if(list != NULL && strcmp(list->name, name) == 0) {
		head = list->next;
		return list;
	}

	/* Loop through list until NULL or name is found */
	while(list != NULL && strcmp(list->name, name) != 0) {
		previous = list;
		list = list->next;
	}

	/* If list is NULL, name was not found so return NULL */
	if(list == NULL) return NULL;

	/* Otherwise, update list and return removed student */
	previous->next = list->next;
	return list;
}

/*
 * This function adds course information for a student.
 * A course structure is created and added at appropriate position in the courses list within student structure.
 * A pointer to the newly added course is returned.
 */
struct course* add_course(char *name, unsigned int number, char grade) {
	struct student* slist = head; /* Temporary Student List */
	struct course* list; /* Temporary List Containing Student's Courses */
	struct course* new_course = (struct course *) calloc (1, sizeof(struct course)); /* New Course to Add */
	struct course* previous = NULL; /* Previous Course */

	/* Fill course data in structure */
	new_course->number = number;
	new_course->grade = grade;
	//new_course->next = NULL;

	/* Check if student list is NULL */
	if(slist == NULL) return NULL;

	/* If student list is not NULL process */
	while(slist != NULL) {
		int compare = strcmp(slist->name, name);

		if(compare == 0) {
			list = slist->courses;

			if(list == NULL) {
				slist->courses = new_course;
				slist->courses->next = NULL;
				return slist->courses;
			}

			while(list != NULL) {
				if(number < list->number) {
					new_course->next = list;
					if(previous != NULL) previous->next = new_course;
					if(list == slist->courses) slist->courses = new_course;
					list = new_course;
					return list;
				}

				if(list->next == NULL) {
					new_course->next = NULL;
					list->next = new_course;
					return new_course;
				}
				previous = list;
				list = list->next;
			}
		}
		slist = slist->next;
	}

	/* Student with provided name not found, return NULL */
	return NULL;
}

/*
 * This function removes a course structure from a student's course list given the student's name.
 * A pointer to the removed structure is returned.
 */
struct course* remove_course(char *name, unsigned int number) {
	struct student* list = head;
	struct student* previous;
	struct course* cprevious;

	/* Update list until student is found or list is NULL */
	while(list != NULL && strcmp(list->name, name) != 0) {
		previous = list;
		list = list->next;
	}

	/* If list is NULL, student doesn't exist */
	if(list == NULL) return NULL;

	/* If the number is the first course of list, update the list accordingly */
	if(list != NULL && strcmp(list->name, name) == 0 && list->courses->number == number) {
		cprevious = list->courses;
		list->courses = list->courses->next;
		return cprevious;
	}

	/* If the number is not the first course, cycle through list until course is found or courses is NULL */
	while(list->courses != NULL && list->courses->number != number) {
		cprevious = list->courses;
		list->courses = list->courses->next;
	}

	/* If courses is NULL, course doesn't exist */
	if(list->courses == NULL) return NULL;

	/* Otherwise, course found, update the courses accordingly */
	cprevious->next = list->courses->next;
	list->courses = cprevious;
	return list->courses;
}

/*
 * This function systematically frees all the memory.
 * NOTE: All the memory must be freed (i.e., all students and all courses). There must be no memory leak.
 */
void delete_all() {
	struct student* list = head;
	struct student* stemp;
	struct course* clist;
	struct course* ctemp;

	if(list != NULL) {
		while(list->next != NULL) {
			if(list->courses != NULL) {
				clist = list->courses;
				while(clist != NULL) {
					ctemp = clist;
					clist = clist->next;
					remove_course(&list->name[0], ctemp->number);
					free(ctemp);
				}
				free(clist);
			}
			stemp = list;
			list = list->next;
			remove_student(&stemp->name[0]);
			free(stemp);
		}
		
		if(list->courses != NULL) {
			clist = list->courses;
			while(clist->next != NULL) {
				ctemp = clist;
				clist = clist->next;
				remove_course(&list->name[0], ctemp->number);
				free(ctemp);
			}
			remove_course(&list->name[0], ctemp->number);
			free(clist);
		}

		head = NULL;
		free(list);
	}
}

/*
 * This function lists the names of all students in the list (in alphabetical order).
 */
void list_students() {
	struct student* list = head; /* Temporary Student List */

	/* Loop through linked list and print student names */
	while(list != NULL) {
		printf("%s ", list->name);
		list = list->next;
	}
	printf("\n");
}

/*
 * This function lists all the course numbers enrolled by all the students.
 * For example, if student 1 is registered for 120, 220, 240 and 440, and 
 * student 2 is registered for 120, 340 and 580. This function prints out:
 * 120, 220, 240, 340, 440 and 580.
 */
void list_courses() {
	struct student* slist = head;
	struct course* clist = NULL;
	unsigned int arr[500];
	int count = 0;
	int i, j, k, temp;

	while(slist != NULL) {
		clist = slist->courses;
		while(clist != NULL) {
			arr[count] = clist->number;
			clist = clist->next;
			count++;
		}
		slist = slist->next;
	}

	for(i = 0; i < count; i++) {
		for(j = i+1; j < count; j++) {
			if(arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			} else if(arr[i] == arr[j]) {
				for(k = j; k < count; k++) arr[k] = arr[k+1];
				count--;
			}
		}
	}

	for(i = 0; i < count; i++) printf("%d ", arr[i]);
	printf("\n");
}
