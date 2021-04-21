function map = ScenarioLoading(scenarioName)
% This function takes as input the string containing a Matlab workspace
% generated with Driving Scenario Tool and gives as output the map of road
% centers with 2 columns (X and Y coordinates) and N rows, which represents
% all waypoints present in the map

    % Open scenario file
    Scenario = open(scenarioName);
    
    % Check if it is an empty file
    if isempty(Scenario)
        disp('Error: Scenario not Loaded')
    else
        disp([scenarioName(1:end-4) ' correctly loaded'])
        
        % Create a cell array to store the road centers coordinates
        pieces = cell(1,length(Scenario.data.RoadSpecifications));
        pieces{1,length(Scenario.data.RoadSpecifications)} = [];
        for i = 1:length(Scenario.data.RoadSpecifications)
            if i>1
                pieces{i} = Scenario.data.RoadSpecifications(1,i).Centers(1:end-1,:);
            else
                pieces{i} = Scenario.data.RoadSpecifications(1,i).Centers;
            end
        end  
        j = length(Scenario.data.RoadSpecifications):-1:1;
        
        % Merge various pieces of the map in one matrix
        Map = vertcat(pieces{1,j});
        
        % Normalize map coordinates and store
        Map_x = Map(:,1);
        Map_y = Map(:,2);
        Map_x = Map_x - Map_x(1,1);
        Map_y = Map_y - Map_y(1,1);
        map = [Map_x Map_y];
    end
end