%% MPC for Dynamic Obstacle Avoidance - Setup

clc; clear all; close all

% include useful folders
addpath('./Scripts');
addpath('./Files');
addpath('./SimulinkModels');
addpath('./Scenarios');

%% Model Parameters

param = loadParameters(1);              % Parameter array for Dynamic Model

%% Initial Conditions

Lw = 4;                                 % [m] Lane width
V = 20/3.6;                             % [m/s] initial speed
x0_kin = [0; 0; 0; V];                  % Initial condition for kinematic model states
x0_dyn = [0; 0; 0; V; 0; 0];            % Initial condition for dynamic model states
u0 = [0; 0];                            % Initial condition for inputs
Ts = 0.02;                              % [s] Sample time
%% Scenario Loading
map = ScenarioLoading('switzerland 2.mat');

% Evaluate total distance covered by the route on the map
distance = odometer(map);
%% Reference signal
% Upsample map based on speed and timestep
[X_rec, Y_rec, Theta_rec] = reference_generator(map,V,Ts);
% Define initial condition based on map
x0_kin = [X_rec(1) Y_rec(1) Theta_rec(1) V]';
x0_dyn = [X_rec(1) Y_rec(1) Theta_rec(1) V 0 0]';

%% Discretization
% Create a discrete time state space model for the plant
[Ad,Bd,Cd,Dd,U,Y,X,DX] = obstacleVehicleModelDT(Ts,x0_kin,u0,param(1:2));
dsys = ss(Ad,Bd,Cd,Dd,'Ts',Ts);
dsys.InputName = {'Throttle','Delta'};
dsys.StateName = {'X','Y','Theta','V'};
dsys.OutputName = dsys.StateName;

%% MPC Design 
% Define controller properties
status = mpcverbosity('off');
mpcobj = mpc(dsys);

p = 40;                     % [Steps] Prediction Horizon
c = 2;                      % [Steps] Control Horizon
mpcobj.PredictionHorizon = p;          
mpcobj.ControlHorizon = c;              

%% Constraints on inputs
ThrottleMax = 4;            % [m/s^2] Maximum Torque deliverable
ThrottleMin = -7.85;        % [m/s^2] Minimum Torque deliverable (braking)
SteeringMax = pi/5;         % [rad] Maximum steering angle (left)
SteeringMin = -pi/5;        % [rad] Minimum steerinf angle (right)

mpcobj.ManipulatedVariables(1).Max = ThrottleMax;
mpcobj.ManipulatedVariables(1).Min = ThrottleMin;
mpcobj.ManipulatedVariables(2).Max = SteeringMax;
mpcobj.ManipulatedVariables(2).Min = SteeringMin;

ThrottleRateMax = 8*Ts;            % [m/s^2] Maximum Torque rate deliverable
ThrottleRateMin = -20*Ts;          % [m/s^2] Minimum Torque rate deliverable (braking)
SteeringRateMax = pi/3*Ts;         % [rad/s] Maximum steering rate (left)
SteeringRateMin = -pi/3*Ts;        % [rad/s] Minimum steerinf rate (right)

mpcobj.ManipulatedVariables(1).RateMin = ThrottleRateMin;         
mpcobj.ManipulatedVariables(1).RateMax = ThrottleRateMax;
mpcobj.ManipulatedVariables(2).RateMin = SteeringRateMin;
mpcobj.ManipulatedVariables(2).RateMax = SteeringRateMax;

%% Weights
% Tune weights for cost function
WOV = [30 30 1 5];      % [X Y yaw V]                         % Optimization weights of the states
WMV = [10 0];           % [Throttle Steering]                 % Optimization weights on manipulated variable
WMVR = [10 1];           % [Throttle_rate Steering_rate]       % Optimization weights on manipulated variable rate
mpcobj.Weights.OutputVariables = WOV;           
mpcobj.Weights.ManipulatedVariables = WMV;         
mpcobj.Weights.ManipulatedVariablesRate = WMVR;      


mpcobj.Model.Nominal = struct('U',U,'Y',Y,'X',X,'DX',DX);

%% Constraints for obstacle avoidance
% At least one Custom Constraint MUST be not 0 to run on simulink
% E*u(k+j)+F*y(k+j)<=G
E1 = [0 0];
F1 = [0 0 0 1]; 
G1 = 100;

E2 = [0 0];
F2 = [0 0 0 -1]; 
G2 = 100;


E=[E1;E2];
F=[F1;F2];
G=[G1;G2];

setconstraint(mpcobj,E,F,G,[0;0]);



%% Simulation
% Initialization
% High covariance means that the MPC state estimator should trust on
% measurements rather than model
egoStates = mpcstate(mpcobj);
egoStates.Covariance = eye(6)*1000;

% Save the initial condition of the controller to run multiple simulation
egoStates_init = egoStates;
T = 0:Ts:distance/V;  

% Log files for plotting
ympc = zeros(length(T),size(Cd,1));
umpc = zeros(length(T),size(Bd,2));

% Extend the reference signal to avoid index over limits
X_rec(end+1:end+p+20) = X_rec(end);
Y_rec(end+1:end+p+20) = Y_rec(end);
Theta_rec(end+1:end+p+20) = Theta_rec(end);
extended_map = [X_rec Y_rec Theta_rec repmat(V,length(X_rec),1)];
%% Run the simulation.
x_new = x0_kin;
u = u0;