function Curvature = curvatureEstimator(Reference)
% curvatureEstimator try to estimate the curvature of the road in the next
% small portion, by making the average of the values in the reference angle
% of the road for the prediction horizon
    Theta_ref = Reference(:,3);
    Curvature = mean(Theta_ref-Theta_ref(1));