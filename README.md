# Flying Helicopter using Reinforcement Learning

This repository contains code for learning Helicopter maneuvers using Deep Q-Learning using the simulator of 2014 Reinforcement Learning challenge for Helicopter domain.

## Challenge

Creators: Pieter Abbeel, Adam Coates, Andrew Y. Ng, Stanford University.

Detailed specifications of challenge can be found [here](https://sites.google.com/site/rlcompetition2014/domains/helicopter).

### Introduction

Autonomous helicopter flight represents a challenging control problem with high dimensional, asymmetric, noisy, nonlinear, non-minimum phase dynamics. Though helicopters are significantly harder to control than fixed-wing
aircraft, they are uniquely suited to many applications requiring either low-speed flight or stable hovering. The control of autonomous helicopters thus provides an important and challenging testbed for learning and control algorithms.

Based on a simulator created by Andrew Ng's group at Stanford, the competition environment simulates an XCell Tempest helicopter in the flight regime close to hover. The agent's objective is to hover the helicopter by manipulating four continuous control inputs based on a 12-dimensional state space. A few pictures of the helicopter have been included with the simulator.

In the last few years, considerable progress has been made in finding good controllers for helicopters [Abbeel et al., 2006]. Other recent accounts of successful autonomous helicopter flight are given in: [Bagnell and Schneider, 2001] [Gavrilets et al., 2004], [La Civita et al., 2006], [Ng et al., 2004a], [Ng et al., 2004b], [Roberts et al., 2003], [Saripalli et al., 2003], and [Abbeel et al., 2008].

### Technical Details

The helicopter's full state is given by its velocity, position, angular rate and orientation.

Observation Space: 12 dimensional, continuous valued:
- forward velocity
- sideways velocity (to the right)
- downward velocity
- helicopter x-coord position - desired x-coord position -- helicopter's x-axis - points forward
- helicopter y-coord position - desired y-coord position -- helicopter's y-axis - points to the right
- helicopter z-coord position - desired z-coord position -- helicopter's z-axis - points down
- angular rate around helicopter's x axis
- angular rate around helicopter's y axis
- angular rate around helicopter's z axis
- quaternion x entry
- quaternion y entry
- quaternion z entry

Action Space: 4 dimensional, continuous valued:-
- longitudinal (front-back) cyclic pitch
- latitudinal (left-right) cyclic pitch
- main rotor collective pitch
- tail rotor collective pitch

Rewards: function of the 12 dimensional observation

### End Conditions

The simulator is set up to run for 6000 timesteps, and each simulation step is 0.1 seconds, thus giving runs of 10 minutes (although the simulator runs faster than real-time). If the simulator enters a terminal state before 6000 timesteps, a large negative reward is given, corresponding to getting the most negative reward achievable for the remaining time.

Note: the competition software will provide your agent with a task specification string that describes the basic inputs and outputs of the particular problem instance your agent is facing. For the competition, the ranges provided in task specification may not be tight; they provide a rough approximation of the actual observation and action ranges. 
