function [dev, lateral_dev] = deviation(reference,actual)
    X_ref = reference(1);
    Y_ref = reference(2);
    Theta_ref = reference(3);
    
    X_act = actual(1);
    Y_act = actual(2);
    
    dev = sqrt((X_ref-X_act)^2+(Y_ref-Y_act)^2);
    
    m = tan(Theta_ref);
    if m > 100 % almost vertical line
        lateral_dev = abs(X_ref-X_act);
    else
        q = Y_ref-m*X_ref;
        lateral_dev = abs(Y_act - (m*X_ref + q))/sqrt(1+m^2);
    end

end