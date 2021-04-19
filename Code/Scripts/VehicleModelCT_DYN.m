function [xdot,X, Y, yaw, v] = VehicleModelCT_DYN(x,u,param)
% The model has 6 states:
%
% * |X| - Global X coordinate
% * |Y| - Global Y coordinate
% * |gamma| - Heading angle of the car (0 when facing east, counterclockwise positive)
% * |x_dot| - Longitudinal component of the car center speed
% * |y_dot| - Orthogonal component of the car center speed
% * |gamma_dot| - Angular velocity of the car center
%
% There are two manipulated variables:
%
% * |throttle| - Throttle (positive when accelerating, negative when braking)
% * |delta| - Steering angle change (counterclockwise positive)
%
% There are 6 parameters:
% 
% * |l_r| - Distance from CoG to rear axle
% * |l_f| - Distance from CoG to front axle
% * |m| - Vehicle mass
% * |I| - Inertia of the vahicle with respect to vertical axe
% * |C_f| - Front lateral friction coefficient
% * |C_r| - Rear lateral friction coefficient
%

%% Parameters

l_r = param(1);                 % Distance between CoG and rear wheels
l_f = param(2);                 % Distance between CoG and front wheels
m = param(3);                   % Mass of the vehicle
I = param(4);                   % Inertia of the vehicle
C_f = param(5);                 % Front lateral slip friction coefficient
C_r = param(6);                 % Rear lateral slip friction coefficient



%% States
X = x(1);                       % X coordinate in global reference frame 
Y = x(2);                       % Y coordinate in global reference frame
yaw = x(3);                     % yaw angle
dx = x(4);                      % X component of speed
v = dx;                         % Longitudinal speed
dy = x(5);                      % Y component of speed
dyaw = x(6);                    % yaw rate


%% Inputs
throttle = u(1);                % Throttle
delta = u(2);                   % Steering angle


%% Dynamic Model
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%% Estimation of tire slip %%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

theta_f = atan((dy + l_f*dyaw)/dx);               % Front wheel slip angle
theta_r = atan((dy - l_r*dyaw)/dx);               % Rear wheel slip angle

F_f = 2*C_f*(delta-theta_f);                      % Front side slip force
F_r = 2*C_r*(-theta_r);                           % Rear side slip force

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%  Dynamics of the model  %%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

ddx = dyaw*dy+throttle;
ddy = -dyaw*dx + 2/m*(F_f*cos(delta) + F_r);
ddyaw = 2/I*(l_f*F_f - l_r*F_r);
dX = dx*cos(yaw) - dy*sin(yaw);
dY = dx*sin(yaw) + dy*cos(yaw);

xdot = [dX; dY; dyaw; ddx; ddy; ddyaw];




