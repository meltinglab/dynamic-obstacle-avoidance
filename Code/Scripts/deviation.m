function [dev, lateral_dev] = deviation(reference,actual)
%
% This function evaluate which is the distance between the actual position
% of the vehicle and the "desired" position, that is to say the next point
% in the reference map. It also evaluate what is the distance with the
% center line of the lane assuming that it is a straigth line (assumption
% often verified considering a dense set of points in the reference map)
% 
% Take as input
% - reference - Actual point in the reference map in the form:
%                   X_ref
%                   Y_ref
%                   Theta_ref
%                   speed_ref
%
% - actual - Actual states of the vehicle model, at least X and Y actual
% 
    X_ref = reference(1);
    Y_ref = reference(2);
    Theta_ref = reference(3);
    
    X_act = actual(1);
    Y_act = actual(2);

    % Compute the difference between the actual position and the reference
    % point as Euclidean distance
    dev = sqrt((X_ref-X_act)^2+(Y_ref-Y_act)^2);
    
    
    % Compute the distance between the actual position and the projection
    % of the roal lane center line
    m = tan(Theta_ref);
    if m > 100 % almost vertical line
        lateral_dev = abs(X_ref-X_act);
    else
        q = Y_ref-m*X_ref;
        lateral_dev = abs(Y_act - (m*X_act + q))/sqrt(1+m^2);
    end

end