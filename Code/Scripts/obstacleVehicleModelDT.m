function [Ad,Bd,Cd,Dd,U,Y,X,DX] = obstacleVehicleModelDT(Ts,x,u,param)
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

l_r = param(1);
l_f = param(2);
carLength = l_r+l_f;

theta = x(3);
V = x(4);
delta = u(2);

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
y = C*x + D*u;


% Generate discrete-time model using ZOH.
nx = size(A,1);
nu = size(B,2);
M = expm([[A B]*Ts; zeros(nu,nx+nu)]);
Ad = M(1:nx,1:nx);
Bd = M(1:nx,nx+1:nx+nu);
Cd = C;
Dd = D;
% Nominal conditions for discrete-time plant
X = x;
U = u;
Y = y;
DX = Ad*x+Bd*u-x;

end

