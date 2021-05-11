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
V = 30/3.6;                             % [m/s] initial speed
x0_kin = [0; 0; 0; V];                  % Initial condition for kinematic model states
x0_dyn = [0; 0; 0; V; 0; 0];            % Initial condition for dynamic model states
u0 = [0; 0];                            % Initial condition for inputs
Ts = 0.01;                              % [s] Sample time
%% Scenario Loading
map = ScenarioLoading('puglia.mat');

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

p = 15;                     % [Steps] Prediction Horizon
c = 5;                      % [Steps] Control Horizon
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

% Add a constraint to the minimum speed, avoiding to go to 0
mpcobj.OutputVariables(4).Min = 1;      % [m/s] Minimum speed


%% Weights
% Tune weights for cost function
WOV = [30 30 8 30];      % [X Y yaw V]                         % Optimization weights of the states
WMV = [0 0];           % [Throttle Steering]                 % Optimization weights on manipulated variable
WMVR = [0 0];           % [Throttle_rate Steering_rate]       % Optimization weights on manipulated variable rate
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

setconstraint(mpcobj,E,F,G,[0.3;1]);



%% Simulation
% Initialization
% High covariance means that the MPC state estimator should trust on
% measurements rather than model
egoStates = mpcstate(mpcobj);
egoStates.Covariance = eye(6)*1000;

% Save the initial condition of the controller to run multiple simulation
egoStates_init = egoStates;
T = 0:Ts:distance/V;  


% Extend the reference signal to avoid index over limits
X_rec(end+1:end+p+20) = X_rec(end);
Y_rec(end+1:end+p+20) = Y_rec(end);
Theta_rec(end+1:end+p+20) = Theta_rec(end);
extended_map = [X_rec Y_rec Theta_rec repmat(V,length(X_rec),1)];


%% Generate Obstacle
obstacle = [extended_map(10000,1) extended_map(10000,2)];
idx = 10000;

%%
figure
% patch([SafeX(idx) EndX(idx) EndX(idx) SafeX(idx)],[SafeY(idx) EndY(idx) EndY(idx)-6/cos(Theta_rec(1)) SafeY(idx)-6/cos(Theta_rec(1))],[0.4 0.4 0.4])
hold on
grid on
plot(X_out,Y_out,'Linewidth',1)
plot(X_rec,Y_rec,'Linewidth',1)
plotRectangle(obstacle,4,2,extended_map(idx,3))
plot(DetPoint(1,1,idx),DetPoint(1,2,idx),'o')
plot(EntryPoint(1,1,idx),EntryPoint(1,2,idx),'o','LineWidth',2)
plot(SafeX(idx),SafeY(idx),'*','LineWidth',2)
plot(EndX(idx),EndY(idx),'*')
axis equal


figure
plot(lateral_dev,'Linewidth',1)
yline(4,'--g','Linewidth',1);
yline(2,'--k','Linewidth',1);
yline(6,'--k','Linewidth',1);
