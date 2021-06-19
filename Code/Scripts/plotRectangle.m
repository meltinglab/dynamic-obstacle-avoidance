function p = plotRectangle(center,width,height,rotation,Color)
% Plot a rectangle of width X height in the position center tilted with rotation
    angles = [-width/2 -width/2 width/2 width/2;
              -height/2 height/2 height/2 -height/2];
    R = [cos(rotation) -sin(rotation);
         sin(rotation) cos(rotation)];
    Rectangle = R*angles+[center' center' center' center'];
    p = patch(Rectangle(1,:),Rectangle(2,:),Color,'EdgeColor',Color,'DisplayName','Obstacle','LineWidth',2);
end