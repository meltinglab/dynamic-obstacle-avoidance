function [X_ref, Y_ref, Theta_ref] = reference_generator(map,V,Ts)
%
% This function generates a matrix [X_ref Y_ref Theta_ref] of dimension NSteps x 3,
% where NSteps is evaluated to fill all the map with steps equal to V*Ts.
% Takes as input
% - map - a set of coordinated in the shape Nmap*2, where first column is X
%           and second column is Y
% - V - actual speed of the vehicle
% - Ts - Sampling time
%

% Start from second point in the map
X = map(1,1);
Y = map(1,2);


idx = 2;
X_next = map(idx,1);
Y_next = map(idx,2);

% Starting slope
theta = atan2((Y_next-Y),(X_next-X));

X_ref = 0;
Y_ref = 0;


ii = 2;
lengthMap = length(map);
% Duplicate last point in map to avoid overflow index error
map(end+1,:) = map(end,:);
oldDistance = 1000;
% Trigonometrical calculation to up-sample the map
while(idx<=lengthMap)
    X_ref(ii) = X_ref(ii-1) + cos(theta)*V*Ts;
    Y_ref(ii) = Y_ref(ii-1) + sin(theta)*V*Ts;
    distance = sqrt((X_ref(ii)-X_next)^2+(Y_ref(ii)-Y_next)^2);
    ii = ii+1;
    if distance < V*Ts || (distance > oldDistance)  
        idx = idx + 1;
        X_old = map(idx-1,1);
        Y_old = map(idx-1,2);
        X_next = map(idx,1);
        Y_next = map(idx,2);
        theta = atan2((Y_next-Y_old),(X_next-X_old));
        distance = 1000;
    end
    oldDistance = distance;
end
% Smoothing the reference according to step, taking windows of 20 meters
SmoothFactor = 20/(V*Ts);
X_ref = smooth(X_ref,SmoothFactor);
Y_ref = smooth(Y_ref,SmoothFactor);
Theta_ref = angleGenerator(X_ref,Y_ref);

end