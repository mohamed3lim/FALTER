function newWall(x, v, w, index)
%painting walls
world = vrworld('walls');
s = ['wall_', num2str(index)];
open(world)

sizeV =  sqrt(dot(v,v));
sizeW =  sqrt(dot(w,w));

%There are only standing and lying walls, none askew ones
%For standing walls
if (w(1) == 0 && w(3) == 0)
    wall = vrnode(world, s, 'wall');
    %Size    
    wall.size = [sizeV/2 sizeW/2 0];
    %rotation
    roty = acos(v(1)/sizeV);
    if v(1)<0, roty = -roty; end
    wall.rotation = [0 1 0 roty];
    

%For lying ones
elseif (w(2) == 0)   
    wall = vrnode(world, s, 'ground');   
    %Size
    wall.size = [sizeV/2 0 sizeW/2];
    %rotation
    roty = acos(abs(v(1))/sizeV);
    wall.rotation = [0 1 0 -roty];

else
    wall = vrnode(world, s, 'wall');
    wall.size = [sizeV/2 sizeW/2 0];
    rotxz = acos(abs(w(1))/sizeW);
    wall.rotation = [v, -rotxz];
end


%Postition
m = (v+w)/2 + x;
wall.position  = m;


%Saves the given map in three vector representation

wall.x = x;
wall.v = v;
wall.w = w;

end



    


