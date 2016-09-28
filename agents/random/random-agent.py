import random
import sys
import copy
import pickle
from rlglue.agent.Agent import Agent
from rlglue.agent import AgentLoader as AgentLoader
from rlglue.types import Action
from rlglue.types import Observation
from rlglue.utils import TaskSpecVRLGLUE3
from random import Random
import csv
import random
import datetime

class random_agent(Agent):
    randGenerator=Random()
    lastAction=Action()
    lastObservation=Observation()
    obs_specs = []
    actions_specs = []
    policyFrozen=False
    exploringFrozen=False
    task=9
    starttime = datetime.datetime.now()
    episode=0

    u_err = 0   # forward velocity
    v_err = 1   # sideways velocity
    w_err = 2   # downward velocity
    x_err = 3   # forward error
    y_err = 4   # sideways error
    z_err = 5   # downward error
    p_err = 6   # angular rate around forward axis
    q_err = 7   # angular rate around sideways (to the right) axis
    r_err = 8   # angular rate around vertical (downward) axis
    qx_err = 9  # <-- quaternion entries, x,y,z,w   q = [ sin(theta/2) * axis; cos(theta/2)],
    qy_err = 10 # where axis = axis of rotation; theta is amount of rotation around that axis
    qz_err = 11

    def write_data(self,data,dtype):
        with open("logs/task_"+str(self.task)+"/"+dtype+" "+str(self.starttime)+" Episode "+str(self.episode)+".csv",'a') as fp:
            writer = csv.writer(fp,delimiter=',')
            writer.writerow(data)

    def agent_init(self,taskSpecString):
        print "Agent Up"
        # print taskSpecString
        TaskSpec = TaskSpecVRLGLUE3.TaskSpecParser(taskSpecString)
        if TaskSpec.valid:
            print len(TaskSpec.getDoubleActions()),": ",TaskSpec.getDoubleActions(),'\n',len(TaskSpec.getDoubleObservations()),": ",TaskSpec.getDoubleObservations()
            assert len(TaskSpec.getIntObservations())==0, "expecting no discrete observations"
            assert len(TaskSpec.getDoubleObservations())==12, "expecting 12-dimensional continuous observations"

            assert len(TaskSpec.getIntActions())==0, "expecting no discrete actions"
            assert len(TaskSpec.getDoubleActions())==4, "expecting 4-dimensional continuous actions"

            self.obs_specs = TaskSpec.getDoubleObservations()
            self.actions_specs = TaskSpec.getDoubleActions()
            # print "Observations: ",self.obs_specs
            # print "actions_specs:", self.actions_specs

        else:
            print "Task Spec could not be parsed: "+taskSpecString;

        self.lastAction=Action()
        self.lastObservation=Observation()

    def agent_policy(self, observation):

        coll = random.uniform(-1,1)
        elevator = random.uniform(-1,1)
        aileron = random.uniform(-1,1)
        rudder = random.uniform(-1,1)

        action = [aileron, elevator, rudder, coll]

        self.write_data(action,"action")
        return action

    def agent_start(self,observation):
        # print "Observation: ",observation.doubleArray
        returnAction = Action()
        returnAction.doubleArray = self.agent_policy(observation)

        self.lastAction = copy.deepcopy(returnAction)
        self.lastObservation = copy.deepcopy(observation)

        self.write_data(observation.doubleArray,"observation")
        return returnAction

    def agent_step(self,reward, observation):
        # print "Observation: ",observation.doubleArray
        # print "Reward: ",reward
        returnAction = Action()
        returnAction.doubleArray = self.agent_policy(observation)

        self.lastAction = copy.deepcopy(returnAction)
        self.lastObservation = copy.deepcopy(observation)

        self.write_data(observation.doubleArray,"observation")
        self.write_data([reward],"reward")
        return returnAction

    def agent_end(self,reward):
        self.episode +=1

        print "Agent Down!"

    def agent_cleanup(self):
		pass

    def agent_message(self,inMessage):
        print inMessage

        return "Message received"

if __name__=="__main__":
	AgentLoader.loadAgent(random_agent())
