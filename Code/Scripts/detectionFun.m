function [SafeX,SafeY,EndX,EndY,EntryPoint,detection,Zone,indexObs_old,DetectionPoint] = detectionFun(Actual,Obstacle,map,Lw,Ts,indexObs)
    
    % Position of the obstacle
    X_obs = Obstacle(1);
    Y_obs = Obstacle(2);
    
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
    
    % Distance from the obstacle
    distance = sqrt((X_act-X_obs)^2+(Y_act-Y_obs)^2);

    indexObs_old = indexObs;
    % Detect if less than 100 meters
    if distance < 100
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
        % Set the Safe Distance as 1 second before the Obstacle, its end
        % at 1 second after the obstacle and the reentrance again after 1
        % second
        SafeIdx = max(1,round(indexObs-5/Ts));
        SafePoint = map(SafeIdx,:);
        EndIdx = min(lengthMap,round(indexObs+5/Ts));
        EndPoint = map(EndIdx,:);
        EntryPoint = map(min(lengthMap,round(indexObs+10/Ts)),:);
        DetectionPoint = map(max(1,round(indexObs-10/Ts)),:);

        SafeX = SafePoint(1) - Lw*sin(SafePoint(3));
        EndX = EndPoint(1) - Lw*sin(EndPoint(3));

        SafeY = SafePoint(2) + Lw*cos(SafePoint(3));
        EndY = EndPoint(2) + Lw*cos(EndPoint(3));



        % Find the Zone in the nearby of the obstacle
        distActMap = zeros(lengthMap,1);
        for jj = SafeIdx:EndIdx
           distActMap(jj) =  sqrt((map(jj,1)-X_act)^2+(map(jj,2)-Y_act)^2);
        end
        
        [minDist,IdxDist] = min(distActMap(SafeIdx:EndIdx));
        IdxDist = IdxDist + SafeIdx-1;
        if IdxDist==SafeIdx
            % Before the Safe
            Zone = 1;
        elseif IdxDist > SafeIdx && IdxDist < EndIdx
            % In the Safe Zone
            Zone = 2;
        else
            % After the Safe
            Zone = 3;
        end
            
    else
        detection = 0;
    end



end