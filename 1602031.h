/* @Author
Student Name: Ramazan Yetismis
Student ID : 150190708
Date: 13.11.2019*/

#define NAME_LENGTH 2

struct Task{
	char *name;
	int day;
	int time;
	int priority;

	Task *previous;
	Task *next;
	Task *counterpart;
};
