function distance = odometer(map)
% This function compute the distance traveled by the car along the path
mapx = map(:,1);
mapy = map(:,2); 
dist = zeros(length(map),1);

for j = 2:length(map)
dist(j,1) = sqrt((mapx(j,1)-mapx(j-1,1))^2+(mapy(j,1)-mapy(j-1,1))^2);
end

distance = sum(dist);
end
