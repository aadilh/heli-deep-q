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

class weak_baseline(Agent):
    randGenerator=Random()
    lastAction=Action()
    lastObservation=Observation()
    obs_specs = []
    actions_specs = []
    policyFrozen=False
    exploringFrozen=False

    def agent_init(self,taskSpecString):
        # print taskSpecString
        TaskSpec = TaskSpecVRLGLUE3.TaskSpecParser(taskSpecString)
        if TaskSpec.valid:
            # print len(TaskSpec.getDoubleActions()),": ",TaskSpec.getDoubleActions(),'\n',len(TaskSpec.getDoubleObservations()),": ",TaskSpec.getDoubleObservations()
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

    def policy(self, observation):

        return [0.0, 0.0, 0.0, 0.0]

    def agent_start(self,observation):
		returnAction = Action()
		returnAction.doubleArray = self.policy(observation)

		self.lastAction = copy.deepcopy(returnAction)
		self.lastObservation = copy.deepcopy(observation)

		return returnAction

    def agent_step(self,reward, observation):
		returnAction = Action()
		returnAction.doubleArray = self.policy(observation)

		self.lastAction = copy.deepcopy(returnAction)
		self.lastObservation = copy.deepcopy(observation)

		return returnAction

    def agent_end(self,reward):
        print "Agent Down!"

    def agent_cleanup(self):
		pass

    def agent_message(self,inMessage):
        print inMessage

        return "Message received"

if __name__=="__main__":
	AgentLoader.loadAgent(weak_baseline())
