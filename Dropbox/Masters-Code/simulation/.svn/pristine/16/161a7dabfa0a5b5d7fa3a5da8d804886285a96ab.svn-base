function deleteWalls( world )
%deletes all walls of a given world
%array containing all walls
walls = getObjects(world);
%number of walls
s = size(walls);
%deleting all walls with consecutive names
for i = 0 :s(1)-1
    str = ['wall_', num2str(i)];
    wall = vrnode(world, str);
    delete(wall)
    
end

