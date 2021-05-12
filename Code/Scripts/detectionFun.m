function [SafeX,SafeY,EndX,EndY,EntryPoint,detection,Zone,indexObs_old,DetectionPoint] = detectionFun(Actual,Obstacle,map,Lw,Ts,indexObs)
% This funtion takes as input the position of the obstacle, the actual
% position of the vehicle, the reference map and the Lanewidth to give as
% output a detection flag and a set of points to define a safety zone
% around the obstacle.
% Inputs are:
%   - Actual -      actual state (x,y,theta,v) of the vehicle
%   - Obstacle -    position (x,y) of the obstacle
%   - map -         reference map NSteps*4
%   - Lw -          [m] Lane width
%   - Ts -          [s] Time step 
%   - indexObs -    Variable used to avoid to search obstacle on map at
%                   every cycle
%
% Outputs are:
% - SafeX,SafeY -   Point where starts the Safe Zone, as lower bound of the
%                   overtaking (left) lane
% - EndX,EndY -     Point where ends the Safe Zone, as lower bound of the
%                   overtaking (left) lane
% - EntryPoint -    Point in the reference map, after the obstacle, where
%                   the vehicle should return after the overtaking maneuver
% - detection -     flag that is 1 when obstacle is detected, 0 otherwise
% - Zone -          flag that tell where the vehicle is with respect to the
%                   obstacle. Outcomes are:
%                       - 0 - No obstacle
%                       - 1 - Well before the obstacle
%                       - 2 - Before the obstacle, leave the lane
%                       - 3 - In the Safe Zone, stay in the left lane
%                       - 4 - After the Safe Zone, come back in your lane
%                       - 5 - Obstacle passed
% - IndexObs_old -  Variable used to avoid to search obstacle on map at
%                   every cycle
% - DetectionPoint -    Point where to start leave the lane to go in the
%                       Safe Zone
%

% Define all the outputs to 0 when no obstacle are detected
    SafeX = 0;
    SafeY = 0;
    EndX = 0;
    EndY = 0;
    EntryPoint = [0 0 0 0];
    DetectionPoint = [0 0 0 0];
    Zone = 0;
    
    % Actual position
    X_act = Actual(1);
    Y_act = Actual(2);
    
    % Reference speed
    V_ref = map(1,4);
    
    
    % Control how many obstacles and find the closer
    NumObstacle = length(Obstacle(:,1));
    if NumObstacle == 1
        % Position of the obstacle
        X_obs = Obstacle(1);
        Y_obs = Obstacle(2);

        % Distance from the obstacle
        distance = sqrt((X_act-X_obs)^2+(Y_act-Y_obs)^2);
    else
        for i = 1:NumObstacle
            % Position of the obstacle
            X_obs = Obstacle(i,1);
            Y_obs = Obstacle(i,2);

            % Distance from the obstacle
            distance = sqrt((X_act-X_obs)^2+(Y_act-Y_obs)^2);
            if distance < 200
                break;
            end
        end
    end

    indexObs_old = indexObs;
    % Detect if less than 200 meters
    if distance < 200
        detection = 1;
 
        % Analyze the map and find the closest point in the map to the
        % obstacle
        lengthMap = length(map(:,1));
        
       if indexObs == 0
            distObsMap = zeros(lengthMap,1);
            for ii = 1:lengthMap
               distObsMap(ii) =  sqrt((map(ii,1)-X_obs)^2+(map(ii,2)-Y_obs)^2);
            end
            [minObs,indexObs] = min(distObsMap);
            indexObs_old = indexObs;
       end
       
        % Set the Safe Distance related with the speed
        % Safety distance = (V[km/h]/10)^2
        %
        % Safe ends 10 meters after the obstacle
        % Reentrance point is 50 meters after the obstacle
        % Lane change point is 40 meters before the Safe
        
        SafeSteps = V_ref*(3.6/10)^2/Ts;
        SafeIdx = max(1,round(indexObs-SafeSteps));
        SafePoint = map(SafeIdx,:);
        
        EndIdx = min(lengthMap,round(indexObs+10/(V_ref*Ts)));
        EndPoint = map(EndIdx,:);
        
        EntryIdx = min(lengthMap,round(indexObs+50/(V_ref*Ts)));
        EntryPoint = map(EntryIdx,:);
        
        DetIdx = max(1,round(indexObs-SafeSteps-40/(V_ref*Ts)));
        DetectionPoint = map(DetIdx,:);

        % Project Safe zone in the left lane
        SafeX = SafePoint(1) - Lw*sin(SafePoint(3));
        EndX = EndPoint(1) - Lw*sin(EndPoint(3));

        SafeY = SafePoint(2) + Lw*cos(SafePoint(3));
        EndY = EndPoint(2) + Lw*cos(EndPoint(3));



        % Find the Zone in the nearby of the obstacle
        distActMap = zeros(lengthMap,1);
        for jj = DetIdx:EntryIdx
           distActMap(jj) =  sqrt((map(jj,1)-X_act)^2+(map(jj,2)-Y_act)^2);
        end
        
        [minDist,IdxDist] = min(distActMap(DetIdx:EntryIdx));
        IdxDist = IdxDist + DetIdx-1;
        if IdxDist==DetIdx
            % Well Before the Safe, stay in your lane
            Zone = 1;
            detection = 0;
        elseif IdxDist > DetIdx && IdxDist <= SafeIdx
            % Before the Safe Zone, change lane
            Zone = 2;
        elseif IdxDist > SafeIdx && IdxDist <= EndIdx
            % In the Safe Zone, stay on left lane
            Zone = 3;
        elseif IdxDist > EndIdx && IdxDist < EntryIdx
            % After the Safe, reenter in you lane
            Zone = 4;
        else
            % Obstacle passed, stay in your lane
            Zone = 5;
            detection = 0;
        end
            
    else
        detection = 0;
        indexObs_old = 0;
    end



end