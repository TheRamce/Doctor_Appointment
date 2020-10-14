/* @Author
Student Name: Ramazan Yetismis
Student ID : 150190708
Date: 13.11.2019*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{	
	//cout<<"sadasdasd"<<endl;
	head=NULL;
	usable_time=0;
	usable_day=0;	
	return;

}

void WorkPlan::close()
{
	Task *last,*rTask,*cTask;
	
	

	while (head)
		{
		
		last=head->previous;
		rTask=head;
		
		//cout<<"deleting "<<rTask->name<<endl;
		
		head=head->next;
		last->next=head;
		head->previous=last;
		
		
			while (rTask->counterpart)
			{
			cTask=rTask->counterpart;
			//cout<<"counterpart is "<<cTask->name<<endl;
			rTask->counterpart=rTask->counterpart->counterpart;
			delete cTask;
			cTask=rTask->counterpart;

			}
			//cout<<"head is "<<head->name<<endl;
			//cout<<"head neaxt is "<<head->next->name<<endl;
		
			if(rTask==head){
				//cout<<"asdkljas"<<endl;
				head=NULL;
				delete rTask;
				return;

			}
			
			delete rTask;

		}
		usable_time=0;
		usable_day=0;
		return;
	

}

void WorkPlan::add(Task *input)
{
	//THIS FUNCTION WILL BE CODED BY YOU
	Task *task=new Task();
	task->next=NULL;
	task->previous=NULL;
	task->counterpart=NULL;
	task->name=new char [strlen(input->name)];
	strcpy(task->name,input->name);
	task->day=input->day;
	task->time=input->time;
	task->priority=input->priority;


	if(head==NULL){
		task->next=task;
		task->previous=task;
		head=task;
		//cout<<"head is "<<task->name<<endl;
		return;
	}
	if(task->day<head->day){//if task smaller than head
		Task *last=head->previous;
		task->next=head;
		task->previous=last;
		last->next=head->previous=task;
		head=task;
		return;
	}//if task smaller than head
	else if(task->day==head->day){//the days are equal
		if(task->time<head->time){//times is smaller
			addbefore(head,task);
			return;
		}//times is smaller
		if(task->time==head->time){//time is equal
				if(task->priority<=head->priority){//head has bigger prio
					delayingProcces(head,task);
					return;
				}//head has bigger prio
				else{//head prio<
				//cout<<"hereeee"<<endl;
						Task *temp=head;
						task->previous=head->previous;;
						task->next=head->next;
						head->previous->next=task;
						head->previous=NULL;
						head->next->previous=task;
						head->next=NULL;
						task->counterpart=head->counterpart;
						head=task;
						temp->counterpart=NULL;
						
						delayingProcces(task,temp);
						return;
					}//head prio<
		
		}//time is equal
		else
		{//time is not equal
			Task *trav=head;
			Task *prev=head;
			Task *trav2=head->counterpart;
			while(trav2&&trav2->time<task->time){
				prev=trav2;
				trav2=trav2->counterpart;
				}
			if(trav2){//not end
				if(trav2->time==task->time){//times are eequal
					if(task->priority<=trav2->priority){//prioirty s smaller
					delayingProcces(trav,task);
					return;
					}//prioirty s smaller
					else{//bigger prio
				    prev->counterpart=task;
					task->counterpart=trav2->counterpart;
					trav2->counterpart=NULL;
					delayingProcces(trav,trav2);
					return;
					}//bigger prio

				
				}//times are eequal
				else{//if no allocated time
							//cout<<"task  is added  tas->day"<<task->day<<"->time"<<task->time<<"trav -> time"<<trav2->time<<endl;
							prev->counterpart=task;
							task->counterpart=trav2;
							return;

					}//if no allocated time
				}//not end
			else{//add last end of the counterpart
					
							//cout<<"entered heree prev "<< prev->time<<endl;
							//cout<<"task  is added  tas->day"<<task->day<<"->time"<<task->time<<endl;
							prev->counterpart=task;
							task->counterpart=trav2;
							return;
				}


		}//time is bigger

	}//the days are equal
	else{//data is beetween or end

		Task *trav=head;
		
			while (trav->next!=head && trav->day<task->day ){
					//cout<<"trav->day"<<trav->day<<endl;
					trav=trav->next;
						
				}
				//cout<<"aaatrav->day"<<trav->day<<endl;
			if(trav!=head){//means not end of the list
			//cout<<"aaatrav->day"<<trav->day<<endl;
				if(task->day!=trav->day){//add beetween
				
				//cout<<"trav->day"<<trav->day<<endl;
				
					if(trav->next==head&&task->day>trav->day){
						//cout<<"day name is"<<task->name<<endl;
									task->next = head; 
									head->previous = task; 
									task->previous = trav; 
									trav->next = task; 
									return;
								} 
					task->next=trav;
					task->previous=trav->previous;
					trav->previous->next=task;
					trav->previous=task;
					return;
				}//add beetween
				else{//days are equal
					if(task->time<trav->time){//smaller time 
						addbefore(trav,task);
						return;
					}//smaller time
					else if(task->time==trav->time){//if times are equal
							if(task->priority<=trav->priority){//smaller prio
								delayingProcces(trav,task);
								return;
					
						}//smaller prio
						else{//bigger prio
							//cout<<"tasks priority is bigger"<<endl;
							task->previous=trav->previous;;
							task->next=trav->next;
							trav->previous->next=task;
							trav->previous=NULL;
							trav->next->previous=task;
							trav->next=NULL;
							task->counterpart=trav->counterpart;
							trav->counterpart=NULL;
							delayingProcces(task,trav);
							return;
						}//bigger prio
						
					}//if times are equal
					else{//if task time is bigger
						Task *prev=trav;
						Task *trav2=trav->counterpart;
						while(trav2&&trav2->time<task->time){
							prev=trav2;
							trav2=trav2->counterpart;
						}
						if(trav2){//not end of the counter part
							if(trav2->time==task->time){//times are eequal
								if(task->priority<=trav2->priority){//prioirty s smaller
									//cout<<"asdjasjkldasjkdaskdaskdasş"<<endl;
									delayingProcces(trav,task);
									return;
								}//prioirty s smaller
								else
								{//bigger prio
									prev->counterpart=task;
									task->counterpart=trav2->counterpart;
									trav2->counterpart=NULL;
									delayingProcces(trav,trav2);
									return;
								}//bigger prio
							}//times are eequal
							else{//if no allocated time
								prev->counterpart=task;
								task->counterpart=trav2;
								return;
							}//if no allocated time
						
						}//not end of the counter part
							else{//add last end of the counterpart
							prev->counterpart=task;
							task->counterpart=trav2;
							return;
						}//add last end of the counterpart
				

						
						
						}//if task time is bigger

				
				
				}//days are equal
				
			}//means not end of the list	
			else
			{
				//cout<<"aaatrav->day"<<endl;
					task->next = head; 
					head->previous = task; 
					task->previous = trav; 
					trav->next = task; 
				return;
			}
			



		}	//data is beetween or end









} 
//this function helps me to delay a proccces
void WorkPlan::delayingProcces(Task *start,Task *addNode){

	checkAvailableNextTimesFor(addNode);//sets the usable time and date
	int day=getUsableDay();
	int time=getUsableTime();

	//cout<<"usable day is "<<day<<" usable time is "<<time<<endl;
	addNode->time=time;
	addNode->day=day;
	Task *iter,*iter2,*last;
	if(start->next==head){//if empty return 
		//cout<<"you fşnfddd"<<endl;
		return;
	}

	iter=start;//horizontal iteration

	while (iter->day<day)//go to the the
	{
		iter=iter->next;
	}
	//cout<<"iter is"<<iter->name<<endl;
	iter2=iter;//vertical iteration
	last=iter2;
	while (iter2->counterpart&&iter2->time<time)
	{
		last=iter2;
		iter2=iter2->counterpart;
	}

	if(iter->day==start->day){//if they are in same day add
		
		//cout<<"las is "<<last->name<<endl;
		last->counterpart=addNode;
		addNode->counterpart=iter2;
		return;
		
	}
	else
	{
		if(time==8){//adds before the first node
			addbefore(iter,addNode);
			return;
		}
		else
		{//adds after
			//cout<<"las is "<<last->name<<endl;
			last->counterpart=addNode;
			addNode->counterpart=iter2;
		return;
		}
		

	}
	
	
	
	
	
	return;

	

}
	
	
//iteratrs over the list and returns the task
Task * WorkPlan::getTask(int day, int time)
{
	Task * temp=head;

	while (temp->next!=head&&temp->day<day)
	{	
		//cout<<"tempp is"<<temp->day <<endl;
		temp=temp->next;
	}
	//	cout<<"tempp is"<<temp->day <<endl;
	if(!temp){
		return NULL;


	}else
	{
		if(temp->time==time){
			return temp;
		}else
		{
			Task *temp2=temp->counterpart;
			while (temp2 && temp2->time<time)
			{
				temp2=temp2->counterpart;
				
			}
			if(!temp2){
					return NULL;

			}else
			{
				return temp2;
			}
			
			
		}
		
	}
	
	
	return NULL;
}


void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{	
	usable_time=-1;
	usable_day=-1;
	Task *trav=head,*trav2,*lookat;
	bool flag1=false;
	

	while (trav->day<delayed->day)
	{
		trav=trav->next;
		//cout<<"found day "<<trav->day<<endl;
	
	}
	lookat=trav;
	
	
	
	
	trav2=trav;
	//cout<<"trav2 time"<<trav2->counterpart->time<<endl;
	//cout<<"found day "<<trav2->day<<endl;
			while (trav2->time<delayed->time)
			{
				
				trav2=trav2->counterpart;
			}//we find the time
			//cout<<"found time "<<trav2->time<<endl;
			bool flag=false;
	int count=0;

	if(trav->next!=head){
		//cout<<"next is head"<<endl;
		
	


		while (count<2)
			{
				if(trav==head){
				count++;

			}
			//cout<<"asşldö"<<endl;
			if(trav->day!=delayed->day&& trav->time>8){

				usable_day=trav->day;
				usable_time=8;
				//cout<<"usable d "<<trav->day<<"time is 8"<<endl;
				return;
				}
			if(flag){
					trav2=trav;
			}
				
		
				
			while (trav2->counterpart)
			{

				if(trav2->counterpart->time-trav2->time>1){
					//cout<<"couterpart is "<<trav2->counterpart->name<<"trav is"<<trav2->name<<endl;
					usable_time=trav2->time+1;
					usable_day=trav2->day;
					//cout<<"usable day from check "<<trav2->day<<"time is "<<trav2->time+1<<endl;
					return;
				}
				//cout<<"trav"<<trav2->name<<endl;
				trav2=trav2->counterpart;
				
			}
			flag=true;
			trav=trav->next;
			
		}
	}
	else{
			//cout<<"entered hereeeeeee"<<endl;
			
			
			
				trav2=lookat;
				while (trav2->counterpart)
				{
					trav2=trav2->counterpart;
				}
				if(trav2->time<16){
					usable_time=trav2->time+1;
					usable_day=trav2->day;
					return;
				}
			

		else
		{
			return;
		}
	}
		
	


}
//addds element before the first element
void WorkPlan::addbefore(Task *start,Task *addNode)
{

				addNode->previous=start->previous;
				addNode->next=start->next;
				start->previous->next=addNode;
				start->previous=NULL; 
				start->next->previous=addNode;
				start->next=NULL;
				addNode->counterpart=start;
				//cout<<"head  is "<<head->name<<endl;
				if(start==head){
					head=addNode;
					return;
				}
				start=addNode;
				return;



}




bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}

void WorkPlan::remove(Task *target){
	 // If list is empty 
    if (head == NULL) {
        return; 
	}
  
    // Find the required node 
    // Declare two pointers and initialize them 
    Task *curr = head, *prev_1 = NULL; 
    while (curr->day!=target->day) { //go to the data
        // If node is not present in the list 
        if (curr->next == head) { 
            printf("\nList doesn't have node with value "); 
            return; 
        } 
		   prev_1 = curr; 
       	   curr = curr->next; 
    } //go to the data
	cout<<"curr is "<<curr->name<<endl;

	if(curr->day==target->day &&curr->time==target->time){//if target is at the begining node
		cout<<"target is equal"<<curr->name<<endl;
	
    	if (curr->next == head && prev_1 == NULL) {	// Check if node is the only node in list  
			if(curr->counterpart!=NULL){//if counter part is exist
				Task *task=curr->counterpart;
				task->next=task;
				task->previous=task;
				head=task;
				delete(curr);
				return;
			}//if counter part is exist
       		 head = NULL; 
			delete curr;
			return; 
   		 } 	// Check if node is the only node in list 

		// If list has more than one node, 
   		 // check if it is the first node 
   		if (curr == head) {
				if (curr->counterpart!=NULL)
				{
					cout<<"asdkmsşidmiasş"<<endl;
					Task *task=curr->counterpart;
					task->previous=head->previous;;
					task->next=head->next;
					head->previous->next=task;
					head->previous=NULL;
					head->next->previous=task;
					head->next=NULL;
					head=task;
					curr->counterpart=NULL;
					delete curr;
					return;
					
				}
				 
       
	   			prev_1 = head->previous; 
  
       			 // Move start ahead 
      			 head = head->next; 
  
        		// Adjust the pointers of prev_1 and start node 
       			 prev_1->next = head; 
       			 head->previous = prev_1; 
       			 delete curr; 
				return;
    	}//it is the head
		 // check if it is the last node 
    	else if (curr->next == head) {//if it is last node 
        // Adjust the pointers of prev_1 and start node 
			if (curr->counterpart)
			{
				cout<<"entered here"<<endl;
				Task *task=curr->counterpart;
				task->previous=curr->previous;;
				task->next=curr->next;
				curr->previous->next=task;
				curr->previous=NULL;
				curr->next->previous=task;
				curr->next=NULL;
				curr->counterpart=NULL;
				delete curr;
				return;
				
			}
			

       		 prev_1->next = head; 
        	head->previous = prev_1; 
        	delete curr; 
			return;
    	} //if it is lats node
		else { //if it is beetwe
        // create new pointer, points to next of curr node 

			if (curr->counterpart)
			{
				Task *task=curr->counterpart;
				task->previous=curr->previous;;
				task->next=curr->next;
				curr->previous->next=task;
				curr->previous=NULL;
				curr->next->previous=task;
				curr->next=NULL;
				curr->counterpart=NULL;
				delete curr;
				return;
				
			
			}
		
        	Task* temp = curr->next; 
  			// Adjust the pointers of prev_1 and temp node 
        	prev_1->next =temp; 
        	temp->previous = prev_1; 
        	delete curr; 
   	 	} //if it is beetwe

	}//if target is at the begining node
	else
	{//it is in the counter part
		Task *travcounter=curr;
		Task *prev=curr;

		while (travcounter && travcounter->time!=target->time)
		{
			prev=travcounter;
			travcounter=travcounter->counterpart;
		}
		if (travcounter)
		{	
			prev->counterpart=travcounter->counterpart;
			delete travcounter;
			return;
		
		}
		else
		{
			cout<<"no element found"<<endl;
			return;
			
		}
		
		
		
		
	}//it is in the counter part
	



}

void WorkPlan::delayAllTasksOfDay(int day){

	Task *oldone=new Task();
	Task *newone=new Task();
	Task * trav=head,*temp,*trav2;
	while (trav->next!=head&&trav->day!=day)
	{
		trav=trav->next;
	}
	trav2=trav;
	//go to the speciffic day
	while (trav2->counterpart)
	{
		trav2=trav2->counterpart;
	}
	cout<<"trav 2 is sssss"<<trav2->time<<endl;

	int time;

	if (trav->next!=head)
	{
			temp=trav->next;
		
	
	
	


	//loop terminates when there is no task left
	while (trav)
	
	{
		time=trav->time;
		cout<<" first time is"<<time<<endl;
		oldone=getTask(day, time);
		
		trav=oldone->counterpart;
		if (oldone!=NULL)
		{
			oldone->day=day;
			oldone->time=trav2->time;

			
			newone->name=new char [strlen(oldone->name)];
			newone->name=oldone->name;
			newone->priority=oldone->priority;
			checkAvailableNextTimesFor(oldone);
			cout<<getUsableDay()<<".day and "<<std::setw(2)<<getUsableTime()<<":00 is the first available day and hour for delaying the task "<<oldone->name<<" that is on "<<oldone->day<<".day at "<<std::setw(2)<< oldone->time <<":00"<<endl;
			newone->day=getUsableDay();
			newone->time=getUsableTime();
			oldone->day=day;
			oldone->time=time;
			remove(oldone);	
			add(newone);
			
		}
		else
		{
			return;
		}
		
		
			
	}
	}


}



