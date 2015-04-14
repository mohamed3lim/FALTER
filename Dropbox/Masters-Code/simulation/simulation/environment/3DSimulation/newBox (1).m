function newBox(box)
%Create a New Sphere
%Opens the world to be changed
box = box';
position = box(1:3);
size = box(4:6);
if position == 0
    return;
end
world = vrworld('walls');
open(world);
%individual name for every new sphere

try
    box = vrnode(world, 'box1');
    delete(box);
catch
end

% global id;
% id = id + 1;
% s = sprintf('box%f', id);

box = vrnode(world, 'box1', 'box');
%places the sphere
box.positionb = position;
box.sizeb = size/2;


close(world);
end

