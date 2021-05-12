function boundaries = laneBoundaries(X,Y,Theta,laneWidth)
% This function returns a structure with the coordinates of the lane
% boundaries, given a map structure with X Y and Theta and the laneWidth
    
    % Check input dimension
    if (length(X)==length(Y)&&length(X)==length(Theta))
        X_top = zeros(length(X),1);
        X_bottom = zeros(length(X),1);
        Y_top = zeros(length(X),1);
        Y_bottom = zeros(length(X),1);
        for jj = 1:length(X)
            X_top(jj) = X(jj)+laneWidth/2*(-sin(Theta(jj)));
            X_bottom(jj) = X(jj)+laneWidth/2*(sin(Theta(jj)));
            Y_top(jj) = Y(jj)+laneWidth/2*(cos(Theta(jj)));
            Y_bottom(jj) = Y(jj)+laneWidth/2*(-cos(Theta(jj)));
        end
    end
    
    boundaries = [X_top, Y_top, X_bottom, Y_bottom];

end