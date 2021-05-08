function [E, F, G] = LaneKeepConstraint(Reference,Lw,detection,x,SafeX,SafeY,EndX,EndY,EntryPoint,Zone,DetectionPoint)

    X_ref = Reference(1);
    Y_ref = Reference(2);
    Theta_ref = Reference(3);
       
    E = [0 0
        0 0];
    
    X_act = x(1);
    Y_act = x(2);
    
    X_entry = EntryPoint(1);
    Y_entry = EntryPoint(2);
    
    X_det = DetectionPoint(1);
    Y_det = DetectionPoint(2);


    m = tan(Theta_ref);
    if abs(m) > 1
        
        m = cot(Theta_ref);
        
        q1 = X_ref + 1/2*Lw/sin(Theta_ref) - m*Y_ref;        
        q2 = X_ref - 1/2*Lw/sin(Theta_ref) - m*Y_ref;


        if detection
            q2 = q2 - Lw/sin(Theta_ref);
            if Zone == 1 % Before the Safe
                slope = ( (SafeX - X_det)/(SafeY - Y_det) );
                constraintSlope = slope;
                constraintIntercept = SafeX - constraintSlope*SafeY;

            elseif Zone == 2 % In the Safe Zone
%                 slope = ( (EndX - SafeX)/(EndY - SafeY) );
%                 constraintSlope = slope;
%                 constraintIntercept = EndX - constraintSlope*EndY;
                slope = m;
                constraintSlope = slope;
                constraintIntercept = X_ref - Lw/sin(Theta_ref) - m*Y_ref;
            else % After the Safe
                entrySlope = ((X_entry - EndX)/(Y_entry-EndY));
                constraintSlope = entrySlope;
                constraintIntercept = X_entry - constraintSlope*(Y_entry);
            end

            if Theta_ref > 0 && constraintSlope <= 0
                % x < constraintIntercept + constraintSlope*Y
                % x > q2 + m*Y
                F = [1 -constraintSlope 0 0
                    -1 m 0 0];

                G = [constraintIntercept; -q2];
            elseif Theta_ref < 0 && constraintSlope > 0
                % x < constraintIntercept + constraintSlope*Y
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

                F = [-1 constraintSlope 0 0
                     1 -m 0 0];
                G = [-constraintIntercept; q2];

            end

        else
%             if Theta_ref < 0
%                 F = [1 -m 0 0
%                     -1 m 0 0];
%                 G = [-q1; q2];
%             else
%                 F = [-1 m 0 0
%                     1 -m 0 0];
%                 G = [q1; -q2];
%             end
            F = [0 0 0 0
                0 0 0 0];
            G = [0;0];
        end
        
        
        
        
        
        
        
        
        
        
    else
    
        q1 = Y_ref - 1/2*Lw/cos(Theta_ref) - m*X_ref;        
        q2 = Y_ref + 1/2*Lw/cos(Theta_ref) - m*X_ref;


        if detection
            q2 = q2 + Lw/cos(Theta_ref);
            if Zone == 1 % Before the Safe
                slope = ( (SafeY - Y_det)/(SafeX - X_det) );
                constraintSlope = slope;
                constraintIntercept = SafeY - constraintSlope*SafeX;

            elseif Zone == 2 % In the Safe Zone
%                 slope = ( (EndY - SafeY)/(EndX - SafeX) );
%                 constraintSlope = slope;
%                 constraintIntercept = EndY - constraintSlope*EndX;
                slope = m;
                constraintSlope = slope;
                constraintIntercept = Y_ref + Lw/cos(Theta_ref) - m*X_ref;
            else % After the Safe
                entrySlope = ((Y_entry - EndY)/(X_entry-EndX));
                constraintSlope = entrySlope;
                constraintIntercept = Y_entry - constraintSlope*(X_entry);
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
