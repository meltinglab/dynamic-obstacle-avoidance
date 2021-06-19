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
V = 40/3.6;                             % [m/s] initial speed
x0_kin = [0; 0; 0; V];                  % Initial condition for kinematic model states
x0_dyn = [0; 0; 0; V; 0; 0];            % Initial condition for dynamic model states
u0 = [0; 0];                            % Initial condition for inputs
Ts = 0.01;                              % [s] Sample time
% Scenario Loading
map = ScenarioLoading('puglia.mat');
% length_road = 5000;
% map = [0 0; length_road 0];
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


%% Generate Obstacles
% STATIC

% Define points where the static obstacles are
obst_1 = round(length(extended_map)*0.1);
obst_2 = round(length(extended_map)*0.2);
obst_3 = round(length(extended_map)*0.21);


idx = [obst_1
       obst_2
       obst_3];             
% Set to 0 the static obstacles speed     
V_obst = [0       
          0
          0];    
   
obstacle = zeros(length(idx),3);

for k = 1:length(idx)
    obstacle(k,:) = [extended_map(idx(k),1) extended_map(idx(k),2) V_obst(k)];
end

lastidx = round(length(extended_map)*0.91);
fakeObs = [extended_map(lastidx,1) extended_map(lastidx,2) 0
    10000 0 0];


% DYNAMIC

VObs = 10/3.6;                  % [m/s] Set the speed for the dynamic obstacle
% Define trajectory of the dynamic obstacle
[X_ostacolo, Y_ostacolo, theta_ostacolo] = reference_generator(map,VObs,Ts);
% Define where the dynamico obstacle is at the start of the simulation
spawn = 0.3*length(X_rec);
spawn_idx = round(spawn*V/VObs);
% Define dynamic obstacle object for simulation
extended_obs = [T' X_ostacolo(spawn_idx+1:spawn_idx+length(T)) Y_ostacolo(spawn_idx+1:spawn_idx+length(T)) repmat(VObs,length(T),1)];
% Define dynamic obstacle  trajectory for plotting
dyn_obstacle1 = [X_ostacolo(spawn_idx+1:spawn_idx+length(T)) Y_ostacolo(spawn_idx+1:spawn_idx+length(T)) theta_ostacolo(spawn_idx+1:spawn_idx+length(T))...
                 repmat(VObs,length(T),1)];

             
VObs2 = 20/3.6;                  % [m/s] Set the speed for the dynamic obstacle
% Define trajectory of the dynamic obstacle
[X_ostacolo2, Y_ostacolo2, theta_ostacolo2] = reference_generator(map,VObs2,Ts);
% Define where the dynamico obstacle is at the start of the simulation
spawn = 0.18*length(X_rec);
spawn_idx = round(spawn*V/VObs);
% Define dynamic obstacle object for simulation
extended_obs2 = [T' X_ostacolo2(spawn_idx+1:spawn_idx+length(T)) Y_ostacolo2(spawn_idx+1:spawn_idx+length(T)) repmat(VObs2,length(T),1)];
% Define dynamic obstacle  trajectory for plotting
dyn_obstacle2 = [X_ostacolo2(spawn_idx+1:spawn_idx+length(T)) Y_ostacolo2(spawn_idx+1:spawn_idx+length(T)) theta_ostacolo2(spawn_idx+1:spawn_idx+length(T))...
                 repmat(VObs2,length(T),1)];
             
%% Simulation
sim('Dynamic_obstacle_avoidance.slx');
%% PLOT
boundaries = laneBoundaries(X_rec,Y_rec,Theta_rec,Lw);
h = figure;
plot(X_rec,Y_rec);grid
hold on
plot(boundaries(:,1),boundaries(:,2),'--k')
plot(boundaries(:,3),boundaries(:,4),'k')
plot(boundaries(:,5),boundaries(:,6),'k')
for j = 1:size(obstacle,1)
    plotRectangle(obstacle(j,1:2),4,2,extended_map(idx(j),3),[.85 .325 .098]);
end
plotRectangle(fakeObs(1,1:2),4,2,extended_map(3000,3),[.85 .325 .098]);
for i = 1:200:length(X_out)
plot(X_out(1:i),Y_out(1:i),'--r','LineWidth',2);
plot(dyn_obstacle1(1:i,1),dyn_obstacle1(1:i,2),'--g','LineWidth',1);
plot(dyn_obstacle2(1:i,1),dyn_obstacle2(1:i,2),'--y','LineWidth',1);
r = plotRectangle([X_out(i) Y_out(i)],4,2,Theta_out(i),'r');
q = plotRectangle([dyn_obstacle1(i,1) dyn_obstacle1(i,2)],4,2,dyn_obstacle1(i,3),'g');
q2 = plotRectangle([dyn_obstacle2(i,1) dyn_obstacle2(i,2)],4,2,dyn_obstacle2(i,3),'y');
xlim([0 5000])
ylim([-15 15])
pause(.2)
drawnow 
% % Capture the plot as an image 
%       frame = getframe(h); 
%       im = frame2im(frame); 
%       [imind,cm] = rgb2ind(im,256); 
%       % Write to the GIF File 
%       if i == 1 
%           imwrite(imind,cm,'gif.gif','gif', 'Loopcount',inf); 
%       else 
%           imwrite(imind,cm,'gif.gif','gif','WriteMode','append'); 
%       end
delete(r)
delete(q)
delete(q2)
end


figure
hold on
grid on
plot(X_out,Y_out,'Linewidth',1)
% plot(X_rec,Y_rec,'Linewidth',1)
plot(boundaries(:,1),boundaries(:,2),'--k')
plot(boundaries(:,3),boundaries(:,4),'k')
plot(boundaries(:,5),boundaries(:,6),'k')


% Plot STATIC
for j = 1:size(obstacle,1)
    plotRectangle(obstacle(j,1:2),4,2,extended_map(idx(j),3),[.85 .325 .098]);
    plot(DetPoint(1,1,idx(j)),DetPoint(1,2,idx(j)),'go','LineWidth',2.5)
    plot(EntryPoint(1,1,idx(j)),EntryPoint(1,2,idx(j)),'rd','LineWidth',2.5)
    plot(SafeX(idx(j)),SafeY(idx(j)),'m*','LineWidth',2.5)
    plot(EndX(idx(j)),EndY(idx(j)),'b+','LineWidth',2.5)
end
axis equal

figure
plot(lateral_dev,'Linewidth',1)
yline(4,'--g','Linewidth',1);
yline(2,'--k','Linewidth',1);
yline(6,'k','Linewidth',1);
