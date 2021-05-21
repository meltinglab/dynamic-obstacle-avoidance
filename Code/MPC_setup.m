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
V = 100/3.6;                             % [m/s] initial speed
x0_kin = [0; 0; 0; V];                  % Initial condition for kinematic model states
x0_dyn = [0; 0; 0; V; 0; 0];            % Initial condition for dynamic model states
u0 = [0; 0];                            % Initial condition for inputs
Ts = 0.01;                              % [s] Sample time
%% Scenario Loading
% map = ScenarioLoading('A_14.mat');
map = [0 0; 1000 0];
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

point_A = round(length(extended_map)*0.3);
% point_B = round(length(extended_map)*0.4);
point_C = round(length(extended_map)*0.8);
% point_D = round(length(extended_map)*0.80);
% point_E = round(length(extended_map)*0.85);
% point_F = round(length(extended_map)*0.9);

obst_1 = point_A;
obst_2 = point_C;
% obst_3 = (point_D:10:point_E)';
% obst_4 = point_F;

idx = [obst_1
       obst_2];              
           
V_obst = [30/3.6       
          50/3.6];    
   
obstacle = zeros(length(idx),3);

for k = 1:length(idx)
    obstacle(k,:) = [extended_map(idx(k),1) extended_map(idx(k),2) V_obst(k)];
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[X_ostacolo, Y_ostacolo theta_ostacolo] = reference_generator(map,V_obst(1),Ts);

point_A = round(length(X_ostacolo)*0.3);

dyn_obstacle1 = [X_ostacolo(point_A:end) Y_ostacolo(point_A:end)];

X_obstacle_dyn = dyn_obstacle1(:,1);
Y_obstacle_dyn = dyn_obstacle1(:,2);

%% Crucial Points for avoidance Calculations 

V_relative = V-V_obst(1);  % to work > 40 km/h
SafeZONE = ((V_relative*3.6)/10)^2; 
var = 1;
index = 1;
dist = zeros(length(X_rec),1);

% %%%%%%%%%%%%%%%%%%%%%%%% Point B DetectionPoint %%%%%%%%%%%%%%%%%%%%%%%%%%
while var
    dist(index) = sqrt((X_rec(index)-X_obstacle_dyn(index))^2+(Y_rec(index)-Y_obstacle_dyn(index))^2);
    if dist(index) <= SafeZONE+40
       var = 0;
    end
    index = index + 1;
end
index_B = index-1;    

% %%%%%%%%%%%%%%%%%%%%%%%% Point C SafePoint %%%%%%%%%%%%%%%%%%%%%%%%%%
var = 1;
index = 1;
dist = zeros(length(X_rec),1);
while var
    dist(index) = sqrt((X_rec(index)-X_obstacle_dyn(index))^2+(Y_rec(index)-Y_obstacle_dyn(index))^2);
    if dist(index) <= SafeZONE
       var = 0;
    end
    index = index + 1;
end
index_C = index-1;    

%%%%%%%%%%%%%%%%%%%%%%%% Point D EndPoint %%%%%%%%%%%%%%%%%%%%%%%%%%
var = 1;
index = 1;
dist = zeros(length(X_rec),1);
while var 
    dist(index) = sqrt((X_rec(index)-X_obstacle_dyn(index))^2+(Y_rec(index)-Y_obstacle_dyn(index))^2);
    if dist(index) > 9.8 && dist(index) < 10.2 
       if dist(index-1) < dist(index)
          var = 0;
       end
    end
    index = index + 1;
end
index_D = index-1;

%%%%%%%%%%%%%%%%%%%%%%%% Point E EntryPoint %%%%%%%%%%%%%%%%%%%%%%%%%%
var = 1;
index = 1;
dist = zeros(length(X_rec),1);
while var 
    dist(index) = sqrt((X_rec(index)-X_obstacle_dyn(index))^2+(Y_rec(index)-Y_obstacle_dyn(index))^2);
    if dist(index) > 49.8 && dist(index) < 50.2 
       if dist(index-1) < dist(index)
          var = 0;
       end
    end
    index = index + 1;
end
index_E = index-1;

 %% Multiple static obstacle
%  
% point_A = round(length(extended_map)*0.2);
% point_B = round(length(extended_map)*0.4);
% point_C = round(length(extended_map)*0.65);
% point_D = round(length(extended_map)*0.68);
% point_E = round(length(extended_map)*0.8);
% 
% obst_1 = point_A;
% obst_2 = point_B;
% obst_3 = point_C;
% obst_4 = point_D;
% obst_5 = point_E;
% 
% idx_dyn = [obst_1;              
%            obst_2;    
%            obst_3;    
%            obst_4;
%            obst_5];      
% 
% obstacle = zeros(length(idx_dyn),2);
% 
% for k = 1:length(idx_dyn)
%     obstacle(k,:) = [extended_map(idx_dyn(k),1) extended_map(idx_dyn(k),2)];
% end

%%
boundaries = laneBoundaries(X_rec,Y_rec,Theta_rec,Lw);

sim('Dynamic_obstacle_avoidance.slx');
%%
figure
hold on
grid on
% plot(X_out,Y_out,'Linewidth',1)
plot(X_rec,Y_rec,'Linewidth',1)
plot(boundaries(:,1),boundaries(:,2),'--k')
plot(boundaries(:,3),boundaries(:,4),'--k')
for j = 1:100:length(X_obstacle_dyn)
      plotRectangle([X_obstacle_dyn(j,1) Y_obstacle_dyn(j,1)],4,2,theta_ostacolo(j));
%     plot(DetPoint(1,1,idx(j)),DetPoint(1,2,idx(j)),'go','LineWidth',2.5)
%     plot(EntryPoint(1,1,idx(j)),EntryPoint(1,2,idx(j)),'rd','LineWidth',2.5)
%     plot(SafeX(idx(j)),SafeY(idx(j)),'m*','LineWidth',2.5)
%     plot(EndX(idx(j)),EndY(idx(j)),'b+','LineWidth',2.5)
end

plot(X_rec(index_B),Y_rec(index_B),'go','LineWidth',7.5)
plot(X_rec(index_E),Y_rec(index_E),'rd','LineWidth',7.5)
plot(X_rec(index_C),Y_rec(index_C),'m*','LineWidth',7.5)
plot(X_rec(index_D),Y_rec(index_D),'b+','LineWidth',7.5)
axis equal


figure
plot(lateral_dev,'Linewidth',1)
yline(4,'--g','Linewidth',1);
yline(2,'--k','Linewidth',1);
yline(6,'--k','Linewidth',1);
