===========================================
RL-Competition 2013 Training Distribution
===========================================

http://2013.rl-competition.org/

Thank you for downloading the training distribution!

==========
Contents:

1: Installation Instructions
2: Information about what is in this package
3: Agents
4: Trainers
5: Running your first experiment
6: Where to go for more info
7: Credits
==========


--------------------------
1 :: INSTALLATION INSTRUCTIONS
--------------------------

To install the core RL-Glue code, as well as all of the sample agents,
Helicopter environment, and trainers, type:

$> bash install.bash
$> make

The competition domain (Helicopter) is implemented in Java and is already packaged and ready to use.

--------------------------
2 :: THIS PACKAGE
--------------------------

The purpose of this package is to provide the software foundation for
the reinforcement learning competition.  This package contains all of
the resources required to create agents and experiments and to test
them on the testing versions of the competition helicopter problem.

Every experiment that is run using this software consists of four components:
	- An experiment program (a trainer)
	- An agent program
	- An environment program
	- The RL_glue communication software

We have taken care of RL_glue and the environments, so the important
components for you are the agents and the trainers.

--------------------------
3 :: AGENTS
--------------------------

Agents are located in the /agents directory.

We have provided several sample agents, implemented in C/C++
and Java. 

There is also one general purpose agent that can work on any problem
(in each of the 3 languages):

/agents/randomAgentJava
/agents/randomAgentCPP

To run any agent, go into its directory and type:
$>make
$>bash run.bash 

*****
* Note 1: running an agent is only half of what is necessary to run
* an experiment -- you also need a trainer!  See the next section.
*****

The source of each agent is in the /agents/<someAgent>/src directory

To rebuild an agent, in that agent's directory type:
$>make clean;make

----------------------------------------------------
4 :: TRAINERS
----------------------------------------------------

Trainers are programs that put an agent into an environment and
control the experiment.  Sample trainers are located in the /trainers
directory.

Console trainers are well suited to running a proper experiment,
trying parameters, etc.

We have provide sample trainers implemented in Java and is located in:

/trainers/consoleTrainerJavaHelicopter

This console trainer will run any of the Helicopter domain. 

To run the trainer, go into its directory and type:

$>bash run.bash

*****
* Note 2: running the trainer is only half of what is necessary to run
* an experiment -- you also need an agent!  See the previous section!
*****

To rebuild the trainer, in that trainer's directory type:
$>make clean;make

----------------------------------------------------
5 :: RUNNING YOUR FIRST EXPERIMENT
----------------------------------------------------

Running an experiment is very easy, you need to choose a trainer and an agent.  By default, the trainer are set to run 10 episodes of Helicopter.  In order to change that go into the src/ directory and select the
appropriate number of episodes in consoleTrainer.cpp, and then type "make" back in the trainer's home directory.

To run the default Helicopter experiment, open two terminal windows:

Terminal 1:
$>cd trainers/consoleTrainerJavaHelicopter
$>bash run.bash

Terminal 2:
$>cd agents/randomAgentJava
$>bash run.bash

You should see an experiment unfold!

----------------------------------------------------
6 :: Where to go for more info
----------------------------------------------------

To get more information about how to use this package, how to create
custom experiments, new agents, and trouble shooting, please visit:

http://2013.rl-competition.org /

----------------------------------------------------
7 :: CREDITS (2013 Tech Committee)
----------------------------------------------------
Christos Dimitrakakis
Arnaud Barré 
Nikolaos Tziortziotis
Guangliang Li
Diederik Roijers
