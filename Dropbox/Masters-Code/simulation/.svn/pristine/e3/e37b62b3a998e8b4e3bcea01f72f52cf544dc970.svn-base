function particle(box,index)
%Create a New Sphere
%Opens the world to be changed
box = box';
s = ['particle_', num2str(index)];
position = box(1:3);
size = box(4:6);
if position == 0
    return;
end
world = vrworld('walls');
open(world);
%individual name for every new sphere
try
    box = vrnode(world, s);
    delete(box);
catch
end

box = vrnode(world, s, 'box');
%places the sphere
box.positionb = position;
box.sizeb = size/2;


close(world);
end

