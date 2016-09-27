#BIN_PATH = ./system
#RL_GLUE_PATH = ./system/rl-glue
#BUILD_PATH = ./system/build

#AGENT_NETWORKED=1
#ENV_NETWORKED=1
#EXP_NETWORKED=1

#CFLAGS = -I$(RL_GLUE_PATH) -O2
#LDFLAGS = -lm 

all: 	
	cd ./agents/randomAgentJava/ && make
	cd ./agents/randomAgentCPP/ && make
	cd ./agents/helicopterAgentCPP/ && make
	cd ./trainers/consoleTrainerJavaHelicopter/ && make

agents:


trainers:
	cd ./trainers/consoleTrainerJavaHelicopter/ && make
	
clean:
	-rm -f $(BIN_PATH)/RL_glue
	-rm -f $(BIN_PATH)/RL_glue.exe
	-rm -f ./system/includes/*.pyc
	-rm -f $(RL_GLUE_PATH)/Python/rlglue/*.pyc
	-rm -f $(RL_GLUE_PATH)/Python/rlglue/network/*.pyc
	-rm -f $(RL_GLUE_PATH)/Python/rlglue/agent/*.pyc
	-rm -f $(RL_GLUE_PATH)/Python/rlglue/environment/*.pyc
	-rm -f agents/randomAgentPython/src/*.pyc
	cd ./agents/randomAgentJava/ && make clean
	cd ./agents/randomAgentCPP/ && make clean
	cd ./agents/helicopterAgentCPP/ && make clean
	cd ./trainers/consoleTrainerJavaHelicopter/ && make clean

#include $(RL_GLUE_PATH)/RL_glue.makefile
