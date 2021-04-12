function [xdot,X, Y, yaw, v] = obstacleVehicleModelCT(x,u,param)
% The model has four states:
%
% * |xPos| - Global horizontal position of the car center
% * |yPos| - Global vertical position of the car center
% * |theta| - Heading angle of the car (0 when facing east, counterclockwise positive)
% * |V| - Speed of the car (positve)
%
% There are two manipulated variables:
%
% * |throttle| - Throttle (positive when accelerating, negative when braking)
% * |delta| - Steering angle change (counterclockwise positive)
%
% There are two parameters:
%
% * |l_r| - Distance from CoG to rear axle
% * |l_f| - Distance from CoG to front axle
%

%% Parameters
l_r = param(1);                     % Distance between CoG and rear wheels
l_f = param(2);                     % Distance between CoG and front wheels
carLength = l_r+l_f;                % Wheelbase


%% State space equations
theta = x(3);                       % Vehicle Orientation
V = x(4);                           % Vehicle speed
delta = u(2);                       % Steering angle

A = [ 0, 0, -V*sin(theta), cos(theta);
      0, 0,  V*cos(theta), sin(theta);
      0, 0, 0,             tan(delta)/carLength;
      0, 0, 0,             0];
  
B = [0  , 0;
     0  , 0;
     0  , (V*(tan(delta)^2 + 1))/carLength;
     1, 0];
 
C = eye(4);

D = zeros(4,2);

xdot = A*x + B*u;

%% Outputs
y = C*x + D*u;

X = y(1);
Y = y(2);
yaw = y(3);
v = y(4);

end

