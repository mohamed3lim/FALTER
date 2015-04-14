function raum(t)
%buidls a room out of a (n x 9)-matrix
%determines size of matrix t
s = size(t);
%it is easier to work with an (9 x m) Matrix
a = t';
k=s(2);
%opens the world to be changed
world = vrworld('walls');
node = nodes(world);
%if there are allready walls in the world, the automatical creation is
%likely to fail
if(size(node)<=5)
    %now every wall is build with the the function 'newWall.m'
    for i = 0 : s(1)-1    
        x = [a(i*k+1), a(i*k+2), a(i*k+3)];
        w = [a(i*k+4), a(i*k+5), a(i*k+6)];
        v = [a(i*k+7), a(i*k+8), a(i*k+9)];
        
        newWall(x, v, w, i);
    end
end

end

