function p = plotRectangle(center,width,height,rotation)
% Plot a rectangle of width X height in the position center tilted with rotation
    angles = [-width/2 -width/2 width/2 width/2;
        -height/2 height/2 height/2 -height/2];
    R = [cos(rotation) -sin(rotation);
        sin(rotation) cos(rotation)];
%     Rectangle = R*(angles-repmat(center,[2 2]))+repmat(center,[2 2]);
    Rectangle = R*angles+[center' center' center' center'];
    p = patch(Rectangle(1,:),Rectangle(2,:),'w','DisplayName','Obstacle','LineStyle',':','LineWidth',2);
end