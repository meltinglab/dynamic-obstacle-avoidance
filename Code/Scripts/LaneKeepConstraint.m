function [E, F, G] = LaneKeepConstraint(Reference,Lw,detection,SafeX,SafeY,EndX,EndY,EntryPoint,Zone,DetectionPoint)
% LaneKeepConstraint function generates the matrices E F G to give to the
% controller in order to define linear constraint.
%
% Controller needs to satisfy the following equation:
%           E*u(k+j)+F*y(k+j)<=G
%
% LaneKeepConstraint take as input:
% - Reference -         Actual reference point for the controller
% - Lw -                [m] Lane Width
% - detection -     flag that is 1 when obstacle is detected, 0 otherwise
% - SafeX,SafeY -   Point where starts the Safe Zone, as lower bound of the
%                   overtaking (left) lane
% - EndX,EndY -     Point where ends the Safe Zone, as lower bound of the
%                   overtaking (left) lane
% - EntryPoint -    Point in the reference map, after the obstacle, where
%                   the vehicle should return after the overtaking maneuver
% - Zone -          flag that tell where the vehicle is with respect to the
%                   obstacle. Outcomes are:
%                       - 0 - No obstacle
%                       - 1 - Well before the obstacle
%                       - 2 - Before the obstacle, leave the lane
%                       - 3 - In the Safe Zone, stay in the left lane
%                       - 4 - After the Safe Zone, come back in your lane
%                       - 5 - Obstacle passed 
% - DetectionPoint -    Point where to start leave the lane to go in the
%                       Safe Zone
%



    % Acquire the Reference point
    X_ref = Reference(1);
    Y_ref = Reference(2);
    Theta_ref = Reference(3);
    
    % Normalize Theta_ref to -pi:pi
    Theta_ref = Theta_ref + pi;
    Theta_ref = mod(Theta_ref,2*pi);
    Theta_ref = Theta_ref - pi;
    
    % Set 0 constraints on input
    E = [0 0
        0 0];
    
    % Point where to reenter in the lane when obstacle is passed
    X_entry = EntryPoint(1);
    Y_entry = EntryPoint(2);
    
    % Point where to leave tha lane when obstacle is detected
    X_det = DetectionPoint(1);
    Y_det = DetectionPoint(2);

    % Road orientation
    m = tan(Theta_ref);
    
    if abs(m) > 1 % Close to vertical
        
        m = cot(Theta_ref); % Inverse angular coefficient
        
        % Lane boundaries
        q1 = X_ref + 1/2*Lw/sin(Theta_ref) - m*Y_ref;        
        q2 = X_ref - 1/2*Lw/sin(Theta_ref) - m*Y_ref;


        if detection
            q2 = q2 - Lw/sin(Theta_ref); % Bound of the overtaking lane
            
            if Zone == 2 % Before the Safe, change line
                slope = ( (SafeX - X_det)/(SafeY - Y_det) );
                constraintSlope = slope;
                constraintIntercept = SafeX - constraintSlope*SafeY;

            elseif Zone == 3 % In the Safe Zone
                slope = m;
                constraintSlope = slope;
                constraintIntercept = X_ref - Lw/sin(Theta_ref) - m*Y_ref;
            elseif Zone == 4 % After the Safe
                entrySlope = ((X_entry - EndX)/(Y_entry-EndY));
                constraintSlope = entrySlope;
                constraintIntercept = X_entry - constraintSlope*(Y_entry);
            else %Far from the obstacle
                constraintSlope = m;
                constraintIntercept = q1;                
            end

            if Theta_ref > 0 && constraintSlope <= 0
                % x < constraintIntercept + constraintSlope*Y
                % x > q2 + m*Y
                F = [1 -constraintSlope 0 0
                    -1 m 0 0];

                G = [constraintIntercept; -q2];
            elseif Theta_ref < 0 && constraintSlope > 0
                % x > constraintIntercept + constraintSlope*Y
                % x < q2 + m*Y
                F = [-1 constraintSlope 0 0
                    1 -m 0 0];

                G = [-constraintIntercept; q2];
                
            elseif Theta_ref > 0 && constraintSlope > 0
                 % x < constraintIntercept + constraintSlope*Y
                 % x > q2 + m*Y
                F = [1 -constraintSlope 0 0
                    -1 m 0 0];
                G = [constraintIntercept; -q2];
            else
                 % x > constraintIntercept + constraintSlope*Y
                 % x < q2 + m*Y
                F = [-1 constraintSlope 0 0
                     1 -m 0 0];
                G = [-constraintIntercept; q2];

            end

        else % No obstacle
%             if Theta_ref < 0
%                 F = [-1 m 0 0
%                     1 -m 0 0];
%                 G = [-q1; q2];
%             else
%                 F = [1 -m 0 0
%                     -1 m 0 0];
%                 G = [q1; -q2];
%             end
            F = [0 0 0 0
                0 0 0 0];
            G = [0;0];
        end
        
        
        
        
        
        
        
        
        
        
    else % close to horizontal
    
        q1 = Y_ref - 1/2*Lw/cos(Theta_ref) - m*X_ref;        
        q2 = Y_ref + 1/2*Lw/cos(Theta_ref) - m*X_ref;


        if detection
            q2 = q2 + Lw/cos(Theta_ref);
            if Zone == 2 % Before the Safe
                slope = ( (SafeY - Y_det)/(SafeX - X_det) );
                constraintSlope = slope;
                constraintIntercept = SafeY - constraintSlope*SafeX;

            elseif Zone == 3 % In the Safe Zone
%                 slope = ( (EndY - SafeY)/(EndX - SafeX) );
%                 constraintSlope = slope;
%                 constraintIntercept = EndY - constraintSlope*EndX;
                slope = m;
                constraintSlope = slope;
                constraintIntercept = Y_ref + Lw/cos(Theta_ref) - m*X_ref;
            elseif Zone == 4 % After the Safe
                entrySlope = ((Y_entry - EndY)/(X_entry-EndX));
                constraintSlope = entrySlope;
                constraintIntercept = Y_entry - constraintSlope*(X_entry);
            else
                constraintSlope = m;
                constraintIntercept = q1;
            end

            if abs(Theta_ref) <= pi/2 && constraintSlope >= 0
                % y > constraintIntercept + constraintSlope*X
                % y < q2 + m*X
                F = [constraintSlope -1 0 0
                    -m 1 0 0];

                G = [-constraintIntercept; q2];
            elseif abs(Theta_ref) > pi/2 && constraintSlope < 0
                % y < constraintIntercept + constraintSlope*X
                % y > q2 + m*X
                F = [-constraintSlope 1 0 0
                    m -1 0 0];

                G = [constraintIntercept; -q2];
            elseif abs(Theta_ref) <= pi/2 && constraintSlope < 0
                 % y > constraintIntercept + constraintSlope*X
                 % y < q2 + m*X
                F = [constraintSlope -1 0 0
                    -m 1 0 0];
                G = [-constraintIntercept; q2];
            else
                F = [-constraintSlope 1 0 0
                     m -1 0 0];
                 G = [constraintIntercept; -q2];

            end

        else
%             if abs(Theta_ref) < pi/2
%                 F = [-m 1 0 0
%                     m -1 0 0];
%                 G = [-q1; q2];
%             else
%                 F = [m -1 0 0
%                     -m 1 0 0];
%                 G = [q1; -q2];
%             end
            F = [0 0 0 0
                0 0 0 0];
            G = [0;0];
        end
    end
    
    
end
