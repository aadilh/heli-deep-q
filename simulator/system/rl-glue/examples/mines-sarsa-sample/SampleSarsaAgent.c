/* 
	Copyright (C) 2008, Brian Tanner

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

	
	*  $Revision: 1007 $
	*  $Date: 2009-02-09 16:30:05 -0600 (Mon, 09 Feb 2009) $
	*  $Author: brian@tannerpages.com $
	*  $HeadURL: http://rl-library.googlecode.com/svn/trunk/projects/packages/examples/mines-sarsa-c-directcompile/SampleSarsaAgent.c $
	
*/

/* 	
	This is a very simple Sarsa agent for discrete-action, discrete-state
	environments.  It uses epsilon-greedy exploration.
	
	We've made a decision to store the previous action and observation in 
	their raw form, as structures.  This code could be simplified and you
	could store them just as ints.
*/


#include <stdio.h>  /* for printf */
#include <string.h> /* for strcmp */
#include <assert.h>
#include <rlglue/Agent_common.h> /* agent_ functions and RL-Glue types */
#include <rlglue/utils/C/RLStruct_util.h> /* helpful functions for structs */
#include <rlglue/utils/C/TaskSpec_Parser.h> /* task spec parser */


action_t this_action;
action_t last_action;

observation_t *last_observation=0;

double* value_function=0;
double sarsa_stepsize = 0.1;
double sarsa_epsilon = 0.1;
double sarsa_gamma = 1.0;
int numActions=0;
int numStates=0;

int policy_frozen=0;
int exploring_frozen=0;

/* Returns a random integer in [0,max] */
int randInRange(int max);
/* 
 *	Selects a random action with probability 1-sarsa_epsilon, 
 *	and the action with the highest value otherwise.  This is a 
 *	quick'n'dirty implementation, it does not do tie-breaking or
 *	even use a good method of random generation.
*/
int egreedy(int theState);
int calculateArrayIndex(int theState, int theAction);
void save_value_function(const char *fileName);
void load_value_function(const char *fileName);

void agent_init(const char* task_spec)
{
	/*Struct to hold the parsed task spec*/
	taskspec_t *ts=(taskspec_t*)malloc(sizeof(taskspec_t));
	int decode_result = decode_taskspec( ts, task_spec );
	if(decode_result!=0){
		printf("Could not decode task spec, code: %d for task spec: %s\n",decode_result,task_spec);
		exit(1);
	}
	
	/* Lots of assertions to make sure that we can handle this problem.  */
	assert(getNumIntObs(ts)==1);
	assert(getNumDoubleObs(ts)==0);
	assert(isIntObsMax_special(ts,0)==0);
	assert(isIntObsMin_special(ts,0)==0);

	
	numStates=getIntObsMax(ts,0)+1;

	assert(getNumIntAct(ts)==1);
	assert(getNumDoubleAct(ts)==0);
	assert(isIntActMax_special(ts,0)==0);
	assert(isIntActMin_special(ts,0)==0);

	numActions=getIntActMax(ts,0)+1;

	free_taskspec_struct(ts); /* Make the taskspec struct a "blank slate" */
	free(ts); /* Free the structure itself */
	/*Here is where you might allocate storage for parameters (value function or policy, last action, last observation, etc)*/
	
	/*Here you would parse the task spec if you felt like it*/
	
	/*Allocate memory for a one-dimensional integer action using utility functions from RLStruct_util*/
	allocateRLStruct(&this_action,1,0,0);
	allocateRLStruct(&last_action,1,0,0);
	/* That is equivalent to:
			 this_action.numInts     =  1;
			 this_action.intArray    = (int*)calloc(1,sizeof(int));
			 this_action.numDoubles  = 0;
			 this_action.doubleArray = 0;
			 this_action.numChars    = 0;
			 this_action.charArray   = 0;
	*/

	/*Allocate memory for a one-dimensional integer observation using utility functions from RLStruct_util*/
	last_observation=allocateRLStructPointer(1,0,0);
	
	/*Later we will parse this from the task spec, but for now*/
	value_function=(double *)calloc(numActions*numStates,sizeof(double));
	
}

const action_t *agent_start(const observation_t *this_observation) {
	int theIntAction=egreedy(this_observation->intArray[0]);
	this_action.intArray[0]=theIntAction;

	replaceRLStruct(&this_action, &last_action);
	replaceRLStruct(this_observation, last_observation);
	
	return &this_action;
}

const action_t *agent_step(double reward, const observation_t *this_observation) {
	int newState=this_observation->intArray[0];
	int lastState=last_observation->intArray[0];
	int lastAction=last_action.intArray[0];
	
	int newAction=egreedy(newState);
	
	double Q_sa=value_function[calculateArrayIndex(lastState,lastAction)];
	double Q_sprime_aprime=value_function[calculateArrayIndex(newState,newAction)];
	
	double new_Q_sa=Q_sa + sarsa_stepsize * (reward + sarsa_gamma * Q_sprime_aprime - Q_sa);
	/*	Only update the value function if the policy is not frozen */
	if(!policy_frozen){
		value_function[calculateArrayIndex(lastState,lastAction)]=new_Q_sa;
	}
	this_action.intArray[0]=newAction;
	
	replaceRLStruct(&this_action, &last_action);
	replaceRLStruct(this_observation, last_observation);
	
	return &this_action;
}

void agent_end(double reward) {
	int lastState=last_observation->intArray[0];
	int lastAction=last_action.intArray[0];
	
	double Q_sa=value_function[calculateArrayIndex(lastState,lastAction)];
	double new_Q_sa=Q_sa + sarsa_stepsize * (reward - Q_sa);

	/*	Only update the value function if the policy is not frozen */
	if(!policy_frozen){
		value_function[calculateArrayIndex(lastState,lastAction)]=new_Q_sa;
	}
	clearRLStruct(&last_action);
	clearRLStruct(last_observation);
}

void agent_cleanup() {
	clearRLStruct(&this_action);
	clearRLStruct(&last_action);
	freeRLStructPointer(last_observation);
	
	if(value_function!=0){
		free(value_function);
		value_function=0;
	}
}

const char* agent_message(const char* inMessage) {
	static char buffer[128];
	
	/*	Message Description
 	 * 'freeze learning'
	 * Action: Set flag to stop updating policy
	 */
	if(strcmp(inMessage,"freeze learning")==0){
		policy_frozen=1;
		return "message understood, policy frozen";
	}
	/*	Message Description
 	* unfreeze learning
 	* Action: Set flag to resume updating policy
	*/
	if(strcmp(inMessage,"unfreeze learning")==0){
		policy_frozen=0;
		return "message understood, policy unfrozen";
	}
	/*Message Description
 	* freeze exploring
 	* Action: Set flag to stop exploring (greedy actions only)
	*/
	if(strcmp(inMessage,"freeze exploring")==0){
		exploring_frozen=1;
		return "message understood, exploring frozen";
	}
	/*Message Description
 	* unfreeze exploring
 	* Action: Set flag to resume exploring (e-greedy actions)
	*/
	if(strcmp(inMessage,"unfreeze exploring")==0){
		exploring_frozen=0;
		return "message understood, exploring unfrozen";
	}
	/*Message Description
 	* save_policy FILENAME
 	* Action: Save current value function in binary format to 
	* file called FILENAME
	*/
	if(strncmp(inMessage,"save_policy",11)==0){
		strncpy(buffer,inMessage+12,sizeof(buffer));
		printf("Saving value function...");
		save_value_function(buffer);
		printf("Saved.\n");
		return "message understood, saving policy";
	}
	/*Message Description
 	* load_policy FILENAME
 	* Action: Load value function in binary format from 
	* file called FILENAME
	*/
	if(strncmp(inMessage,"load_policy",11)==0){
		strncpy(buffer,inMessage+12,sizeof(buffer));
		printf("Loading value function...");
		load_value_function(buffer);
		printf("Loaded.\n");
		return "message understood, loading policy";
	}

	
	return "SampleSarsaAgent(C/C++) does not understand your message.";
			
}

void save_value_function(const char *fileName){
	FILE *fp;
	fp=fopen(fileName, "wb");
	
	fwrite(value_function,sizeof(double),numStates*numActions,fp);
	fclose(fp);
}
void load_value_function(const char *fileName){
	FILE *fp;
	fp=fopen(fileName, "rb");
	
	fread(value_function,sizeof(double),numStates*numActions,fp);
	fclose(fp);
}

int egreedy(int state){
	int maxIndex = 0;
	int a = 1;
	int randFrequency=(int)(1.0f/sarsa_epsilon);

	if(!exploring_frozen){
  		if((rand() % randFrequency == 1)) {
    		return randInRange(numActions-1);
  		}
	}

/*otherwise choose the greedy action*/
  maxIndex = 0;
  for(a = 1; a < numActions; a++){
    if(value_function[calculateArrayIndex(state,a)] > value_function[calculateArrayIndex(state,maxIndex)]) {
      maxIndex = a;
    }
  }
  return maxIndex;
}

int randInRange(int max){
	double r, x;
	r = ((double)rand() / ((double)(RAND_MAX)+(double)(1)));
   	x = (r * (max+1));

	return (int)x;
}

int calculateArrayIndex(int theState, int theAction){
	assert(theState<numStates);
	assert(theAction<numActions);
	
	

	return theState*numActions+theAction;
}
