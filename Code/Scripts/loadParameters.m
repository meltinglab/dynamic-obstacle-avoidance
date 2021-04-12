function params = loadParameters(VehicleID)
%
% This function takes as input an ID (numerical value) and returns a vector
% params with the vehicle parameters.
% ID allowed are the following:
%           1 - Hyundai Azera
%           2 - BMW 325i
%           3 - Ford E150
%           4 - Suzuki Samurai
%           5 - Volkswagen Beetle
%
% params = l_r
%          l_f
%          mass
%          inertia
%          C_f
%          C_r
%
% If ID is invalid, an Error message is displayed and default parameters
% are loaded:
% Default params = [1; 1; 1000; 1000; 10^5; 10^5]
%
    file = open('VehicleDatabase.mat');
    if isempty(file)
        disp('Error: Database not found')
    else
        condition = 0;
        for i = 1:5
            if i == VehicleID
                condition = 1;
            end
        end

        if condition
            vehicle = file.database(VehicleID);
            l_r = vehicle.l_r;              % [m] Distance between CoG and rear wheels                 
            l_f = vehicle.l_f;              % [m] Distance between CoG and front wheels
            mass = vehicle.mass;            % [kg] Mass of the vehicle
            inertia = vehicle.inertia;      % [kg/m^2] Inertia of the vehicle
            C_f = 1.0745E5;                 % [N] Lateral slip friction coefficient front
            C_r = 1.9032E5;                 % [N] Lateral slip friction coefficient rear
            params = [l_r; l_f; mass; inertia; C_f; C_r];
            disp([vehicle.Vehicle_Name ' correctly loaded'])
        else
            disp('Error: Invalid Vehicle ID, default parameters loaded')
            l_r = 1;            % [m] Distance between CoG and rear wheels                 
            l_f = 1;            % [m] Distance between CoG and front wheels
            mass = 1000;        % [kg] Mass of the vehicle
            inertia = 1000;     % [kg/m^2] Inertia of the vehicle
            C_f = 1E5;          % [N] Lateral slip friction coefficient front
            C_r = 1E5;          % [N] Lateral slip friction coefficient rear
            params = [l_r; l_f; mass; inertia; C_f; C_r];
        end
    end
   
end