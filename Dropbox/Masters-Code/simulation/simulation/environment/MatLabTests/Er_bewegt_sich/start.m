
world = vrworld('room.wrl');
set(world, 'Description', 'Falter in a Room')
open(world);
%view(world);
bewegung([0 0 0]);
falter = vrnode(world, 'Falter');
falter.rotation = [0 0 0 0];
