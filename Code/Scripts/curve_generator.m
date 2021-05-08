function [X_ref, Y_ref, Theta_ref] = curve_generator(R,V,Ts)
%
% This function generates a matrix [X_ref Y_ref Theta_ref] of dimension NSteps x 3,
% where NSteps is evaluated to fill 3/4 of a circle with steps equal to V*Ts.
% Takes as input
% - R - Curvature radius
% - V - actual speed of the vehicle
% - Ts - Sampling time
%

X_ref = 0;
Y_ref = 0;

Theta_ref = 0;
ii = 2;
AngleStep=1/R*V*Ts;
while(Theta_ref(ii-1)<=3/2*pi&&Theta_ref(ii-1)>=-3/2*pi)
    Theta_ref(ii) = Theta_ref(ii-1)+AngleStep;
    X_ref(ii) = X_ref(ii-1) + cos(Theta_ref(ii))*V*Ts;
    Y_ref(ii) = Y_ref(ii-1) + sin(Theta_ref(ii))*V*Ts;
    ii = ii+1;
end

X_ref = X_ref';
Y_ref = Y_ref';
Theta_ref = Theta_ref';

end