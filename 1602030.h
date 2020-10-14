/* @Author
Student Name: Ramazan Yetismis
Student ID : 150190708
Date: 13.11.2019*/

#ifndef TASK_MANAGEMENT_TOOL
#define TASK_MANAGEMENT_TOOL

#include <stdio.h>

#define strnicmp strncasecmp

#include "task.h"

struct WorkPlan{
	void create();
	void close();
	void add(Task *input);
	void checkAvailableNextTimesFor(Task *delayed);
	int  getUsableDay();
	int getUsableTime();
	void remove(Task *target);
	void display(bool verbose, bool testing);
	void delayAllTasksOfDay(int day);
	Task * getTask(int day, int time);
	bool checkCycledList();//ok
	void delayingProcces(Task *start,Task *addNode);//it delays a task due to priorities
	
	void addbefore(Task *start,Task *addNode);//adds the tas before the first task

	
	Task *head;
	int usable_day;
	int usable_time;
};
#endif 

