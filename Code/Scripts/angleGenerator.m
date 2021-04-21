function Theta_ref = angleGenerator(X_ref,Y_ref)

lengthMap = length(X_ref);
if lengthMap == length(Y_ref)
    Theta_ref = zeros(lengthMap,1);
    for ii = 2:lengthMap
        Theta_ref(ii) = atan2(Y_ref(ii)-Y_ref(ii-1),X_ref(ii)-X_ref(ii-1));
    end
    Theta_ref(1) = Theta_ref(2);
else
    disp('Error: Wrong input size')
end


end

