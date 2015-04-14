function bewegung(translation)
%wir bewegen den falter
world = vrworld('room.wrl');
open(world);
%fig = view(world);
falter = vrnode(world, 'Falter');


falter.translation = translation;

vrdrawnow;
close(world);
end
