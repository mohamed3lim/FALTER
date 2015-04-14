function [walls, boxes, spheres, sensors] = getObjects( vrworld )
%get [walls boxes spheres]
world = vrworld;
open(world);

node = nodes(world);
s = size(node);
j = 1;  %WallArray
k = 1;  %boxArray
l = 1;  %SphereArray
m = 1;  %SensorArray
wall = 0;
box = 0;
sphere = 0;

try
for i = 1: s
    %creating a Array of walls
   if strncmp('wall', get(node(i), 'Name'), 4)
       %Cannot prallocate, do not know number of walls before
       %First part is the x-Vector of a Wall
       wall(j,1:3) = getfield(node(i), 'x');      
       %next part is the w-Vector of a Wall
       wall(j,4:6) = getfield(node(i), 'w');
       %last part is the v-Vector of a Wall       
       wall(j,7:9) = getfield(node(i), 'v');       
       j = j+1;
   %Creating an Array of boxes    
   elseif strncmp('box', get(node(i), 'Name'), 3)
       %first part is the position of the box
       box(k,1:3) = getfield(node(i), 'positionb');
       %second part is the size of the box
       box(k,4:6) = getfield(node(i), 'sizeb');
       k = k+1;
   %Creating an Array of Spheres    
   elseif strncmp('sphere', get(node(i), 'Name'), 3)
       %first part is the psotion of the box
       sphere(l, 1:3) = getfield(node(i), 'positions');
       %second part is the radius of the box
       sphere(l, 4) = getfield(node(i), 'radius');
       l= l+1;
   elseif strncmp('sensor', get(node(i), 'Name'), 6)
       sensor(m, 1:3) = getfield(node(i), 'position');
       m = m+1;
   end
   
   
end
catch exception
end
walls = wall;
boxes = box;
spheres = sphere;
sensors = sensor;
close(world);
end

