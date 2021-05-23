function [SafeX,SafeY,EndX,EndY,EntryPoint,detection,Zone,indexObs_old,DetectionPoint,ObstacleCnt_old,EndIdx_old,EntryIdx_old,leftLaneFLAG_old] = detectionFun(number_obstacles,Actual,Obstacle,dyn_obstacle1,map,Lw,Ts,indexObs,ObstacleCnt,ActualIdx,EndIdx,EntryIdx,leftLaneFLAG)
% detectFun takes as input the position of one or more obstacle, the actual
% position of the vehicle, the reference map and the Lanewidth to give as
% output a detection flag and a set of points to define a safety zone
% around the obstacle.
% Inputs are:
%   - Actual -      actual state (x,y,theta,v) of the vehicle
%   - Obstacle -    Matrix with NumObstacle rows, each one containing
%                   position (x,y) of the obstacle
%   - map -         reference map NSteps*4
%   - Lw -          [m] Lane width
%   - Ts -          [s] Time step 
%   - indexObs -    Variable used to avoid to search obstacle on map at
%                   every cycle
%   - ObstacleCnt - Obstacle counter, an integer containing the index of
%                   the last obtacle detected
%   - ActualIdx -   Index of the actual position in the reference map
%   - EndIdx -      Index of the end of the actual Safe Zone
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
% - ObstacleCnt_old -   Obstacle counter, an integer containing the index
%                       of the last obtacle detected
% - EndIdx_old -    Index of the end of the actual Safe Zone
%
% This version of detectFun doesn't accept single row obstacle matrix
%

% Define all the outputs to 0 when no obstacle are detected
    SafeX = 0;
    SafeY = 0;
    EndX = 0;
    EndY = 0;
    EntryPoint = [0 0 0 0];
    DetectionPoint = [0 0 0 0];
    Zone = 0;
    EndIdx_old = 0;
    EntryIdx_old = 0;
    FLAG = 0;
    X_obs_old = 0;
    Y_obs_old = 0;
    
    
    % Actual position of ego-vehicle
    X_act = Actual(1);
    Y_act = Actual(2);
    
    % Actual position of dynamic obstacle
    X_dyn_obs_act = dyn_obstacle1(1);
    Y_dyn_obs_act = dyn_obstacle1(2);
    
    % Reference speed
    V_ref = map(1,4);
    
    
    % Control how many obstacles and find the closer
    NumObstacle = length(number_obstacles);
    if NumObstacle == 1   % Single obstacle
        
        %%%% Position and speed of the obstacle
        % Static Obstacle
        X_obs = Obstacle(1);   
        Y_obs = Obstacle(2);
        V_obs = Obstacle(3); 
              
        if V_obs == 0
            % Distance from the static obstacle
            distance = sqrt((X_act-X_obs)^2+(Y_act-Y_obs)^2);
        else  
            % Distance from the dynamic obstacle  
            distance = sqrt((X_act-X_dyn_obs_act)^2+(Y_act-Y_dyn_obs_act)^2);
            if distance < 200 % Stop the research when an obstacle is in the sensor range
                return;
            end
        end
    else     
        for i = 1:NumObstacle   % Multiple obstacles 
            %%%%% Position and speed of the obstacles
            % Static Obstacles
            X_obs = Obstacle(i,1);
            Y_obs = Obstacle(i,2);
            V_obs = Obstacle(i,3);
               
            if V_obs == 0
                % Distance from the static obstacle
                distance = sqrt((X_act-X_obs)^2+(Y_act-Y_obs)^2);
            else
                % Distance from the dynamic obstacle
                distance = sqrt((X_act-X_dyn_obs_act)^2+(Y_act-Y_dyn_obs_act)^2);
                if distance < 200 % Stop the research when an obstacle is in the sensor range
                    break;
                end
            end
        end
    end

    % Backup of the indexes
    indexObs_old = indexObs;
    ObstacleCnt_old = ObstacleCnt;
    
    if ObstacleCnt_old > 0 && indexObs > 0% If it is not the first obstacle
        if ObstacleCnt_old < NumObstacle % If it is not the last obstacle
            if ActualIdx >= EndIdx  % If the vehicle is after the safezone of the previous obstacle
                X_obs_old = Obstacle(ObstacleCnt_old,1);
                Y_obs_old = Obstacle(ObstacleCnt_old,2);
                X_obs = Obstacle(ObstacleCnt_old + 1,1);
                Y_obs = Obstacle(ObstacleCnt_old + 1,2);
                FLAG = 1;
            end
        else % If it is the last obstacle in the map
%             indexObs = 0;
        end
    end
    
    %% Static Obstacle Detection
    
%     % Detect if less than 200 meters
%     if distance < 200 && V_obs == 0
%         detection = 1;
%  
%         % Analyze the map and find the closest point in the map to the
%         % obstacle
%         lengthMap = length(map(:,1));
%         
%        if indexObs == 0 && FLAG == 0
%             distObsMap = zeros(lengthMap,1);
%             for ii = 1:lengthMap
%                distObsMap(ii) =  sqrt((map(ii,1)-X_obs)^2+(map(ii,2)-Y_obs)^2);
%             end
%             [minObs,indexObs] = min(distObsMap);
%             indexObs_old = indexObs;
%             ObstacleCnt_old = ObstacleCnt_old + 1;
%        end
%        
%        if FLAG == 1 % When consequent obstacle are detected
%            distObs_oldMap = zeros(lengthMap,1);
%             for ii = 1:lengthMap
%                distObs_oldMap(ii) =  sqrt((map(ii,1)-X_obs_old)^2+(map(ii,2)-Y_obs_old)^2);
%             end
%             [minObs,indexObsOld] = min(distObs_oldMap); % Find the position of the previous
%             
%             distObs_newMap = zeros(lengthMap,1);
%             for ii = 1:lengthMap
%                distObs_newMap(ii) =  sqrt((map(ii,1)-X_obs)^2+(map(ii,2)-Y_obs)^2);
%             end
%             [minObs,indexObsNew] = min(distObs_newMap); % Find the position of the next
%             
%             % Compute detection point and safe zone for the new obstacle
%             SafeSteps = V_ref*(3.6/10)^2/Ts;
%             SafeIdxNew = max(1,round(indexObsNew-SafeSteps));
%             DetIdxNew = max(1,round(indexObsNew-SafeSteps-40/(V_ref*Ts)));
%             % If the new obsatcle SafeZone starts before the EndZone of the
%             % last obstacle OR the vehicle is after the detection point of
%             % the new obstacle, set the new obstacle as the current
%             % ELSE
%             % set the previous obstacle as the current
%             if DetIdxNew < EntryIdx || DetIdxNew < ActualIdx
%                 indexObs = indexObsNew;
%                 ObstacleCnt_old = ObstacleCnt_old + 1;
%                 indexObs_old = indexObs;
%                 if DetIdxNew < EntryIdx
%                     leftLaneFLAG = 1;
%                 end
%             else 
%                 indexObs = indexObsOld;
%                 indexObs_old = indexObs;
%             end
%        end
%        
%         % Set the Safe Distance related with the speed
%         % Safety distance = (V[km/h]/10)^2
%         %
%         % Safe ends 10 meters after the obstacle
%         % Reentrance point is 50 meters after the obstacle
%         % Lane change point is 40 meters before the Safe
%         
%         SafeSteps = max(V_ref*(3.6/10)^2/Ts,5/(V_ref*Ts));
%         SafeIdx = max(1,round(indexObs-SafeSteps));
%         SafePoint = map(SafeIdx,:);
%         
%         EndIdx = min(lengthMap,round(indexObs+10/(V_ref*Ts)));
%         EndIdx_old = EndIdx;
%         EndPoint = map(EndIdx,:);
%         
% 
%         EntryIdx = min(lengthMap,round(indexObs+50/(V_ref*Ts)));
%         EntryIdx_old = EntryIdx;
%         EntryPoint = map(EntryIdx,:);
%         DetIdx = max(1,round(indexObs-SafeSteps-40/(V_ref*Ts)));
%         DetectionPoint = map(DetIdx,:);
% 
%         
%         % Project Safe zone in the left lane
%         SafeX = SafePoint(1) - Lw*sin(SafePoint(3));
%         EndX = EndPoint(1) - Lw*sin(EndPoint(3));
% 
%         SafeY = SafePoint(2) + Lw*cos(SafePoint(3));
%         EndY = EndPoint(2) + Lw*cos(EndPoint(3));
% 
% 
% 
%         % Find the Zone in the nearby of the obstacle
%         distActMap = zeros(lengthMap,1);
%         for jj = DetIdx:EntryIdx
%            distActMap(jj) =  sqrt((map(jj,1)-X_act)^2+(map(jj,2)-Y_act)^2);
%         end
%         
%         [minDist,IdxDist] = min(distActMap(DetIdx:EntryIdx));
%         IdxDist = IdxDist + DetIdx-1;
%         if IdxDist==DetIdx
%             % Well Before the Safe, stay in your lane
%             Zone = 1;
%             detection = 0;
%             if leftLaneFLAG == 1
%                 Zone = 3;
%                 detection = 1;
%             end
%         elseif IdxDist > DetIdx && IdxDist <= SafeIdx
%             % Before the Safe Zone, change lane
%             Zone = 2;
%             
%             % You are already in the left lane and don't need to come back
%             % to Zone 2
%             if leftLaneFLAG == 1
%                 Zone = 3;
%             end
%             
%         elseif IdxDist > SafeIdx && IdxDist <= EndIdx
%             % In the Safe Zone, stay on left lane
%             Zone = 3;
%             leftLaneFLAG = 0;
%         elseif IdxDist > EndIdx && IdxDist < EntryIdx
%             % After the Safe, reenter in you lane
%             Zone = 4;
%             
%             % You are already next to another obstacle, stay on the left
%             if leftLaneFLAG == 1
%                 Zone = 3;
%             end
%             
%         else
%             % Obstacle passed, stay in your lane
%             Zone = 5;
%             detection = 0;
%         end
%             
%     else
%         detection = 0;
%         indexObs_old = 0;
%     end
%     
     %% Dynamic Obstacle Detection
    
    % Detect if less than 200 meters
    if distance < 200 && V_obs > 0
        detection = 1;
 
        % Analyze the map and find the closest point in the map to the
        % obstacle
        lengthMap = length(map(:,1));
        
       if indexObs == 0 && FLAG == 0
            distObsMap = zeros(lengthMap,1);
            for ii = 1:lengthMap
               distObsMap(ii) =  sqrt((map(ii,1)-X_dyn_obs_act)^2+(map(ii,2)-Y_dyn_obs_act)^2);
            end
            [minObs,indexObs] = min(distObsMap);
            indexObs_old = indexObs;
            ObstacleCnt_old = ObstacleCnt_old + 1;
       end
       
       if FLAG == 1 % When consequent obstacle are detected
           distObs_oldMap = zeros(lengthMap,1);
            for ii = 1:lengthMap
               distObs_oldMap(ii) =  sqrt((map(ii,1)-X_obs_old)^2+(map(ii,2)-Y_obs_old)^2);
            end
            [minObs,indexObsOld] = min(distObs_oldMap); % Find the position of the previous
            
            distObs_newMap = zeros(lengthMap,1);
            for ii = 1:lengthMap
               distObs_newMap(ii) =  sqrt((map(ii,1)-X_dyn_obs_act)^2+(map(ii,2)-Y_dyn_obs_act)^2);
            end
            [minObs,indexObsNew] = min(distObs_newMap); % Find the position of the next
            
            % Compute detection point and safe zone for the new obstacle
            V_rel = V_ref-V_obs;
            SafeSteps = V_ref*(3.6/10)^2/Ts;
            SafeIdxNew = max(1,round(indexObsNew-SafeSteps));
            DetIdxNew = max(1,round(indexObsNew-SafeSteps-40/(V_ref*Ts)));
            % If the new obstacle SafeZone starts before the EndZone of the
            % last obstacle OR the vehicle is after the detection point of
            % the new obstacle, set the new obstacle as the current
            % ELSE
            % set the previous obstacle as the current
            if DetIdxNew < EntryIdx || DetIdxNew < ActualIdx
                indexObs = indexObsNew;
                ObstacleCnt_old = ObstacleCnt_old + 1;
                indexObs_old = indexObs;
                if DetIdxNew < EntryIdx
                    leftLaneFLAG = 1;
                end
            else 
                indexObs = indexObsOld;
                indexObs_old = indexObs;
            end
       end
       
        % Set the Safe Distance related with the speed
        % Safety distance = (V[km/h]/10)^2
        %
        % Safe ends 10 meters after the obstacle
        % Reentrance point is 50 meters after the obstacle
        % Lane change point is 40 meters before the Safe
        
        V_relative = V_ref - V_obs;
        
        SafeSteps = max(V_relative*(3.6/10)^2/Ts,5/(V_relative*Ts));
        SafeIdx = max(1,round(indexObs-SafeSteps));
        SafePoint = map(SafeIdx,:);
        
        EndIdx = min(lengthMap,round(indexObs+10/(V_ref*Ts)));
        EndIdx_old = EndIdx;
        EndPoint = map(EndIdx,:);
        
        EntryIdx = min(lengthMap,round(indexObs+50/(V_ref*Ts)));
        EntryIdx_old = EntryIdx;
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
            if leftLaneFLAG == 1
                Zone = 3;
                detection = 1;
            end
        elseif IdxDist > DetIdx && IdxDist <= SafeIdx
            % Before the Safe Zone, change lane
            Zone = 2;
            
            % You are already in the left lane and don't need to come back
            % to Zone 2
            if leftLaneFLAG == 1
                Zone = 3;
            end
            
        elseif IdxDist > SafeIdx && IdxDist <= EndIdx
            % In the Safe Zone, stay on left lane
            Zone = 3;
            leftLaneFLAG = 0;
        elseif IdxDist > EndIdx && IdxDist < EntryIdx
            % After the Safe, reenter in you lane
            Zone = 4;
            
            % You are already next to another obstacle, stay on the left
            if leftLaneFLAG == 1
                Zone = 3;
            end
            
        else
            % Obstacle passed, stay in your lane
            Zone = 5;
            detection = 0;
        end
            
    else
        detection = 0;
        indexObs_old = 0;
    end
    
    %%
    leftLaneFLAG_old = leftLaneFLAG;


end