function filename_final = grid(heatMap, point)
%baut eine 3d-Heatmap ins Bild aus einer Matrix
%laenge und breite erfassen
s = size(heatMap);
filename='shape.wrl';
filename_final='finalgrid.wrl';
fid = fopen(filename, 'w+', 'n', 'UTF-8');
fprintf(fid, '#VRML V2.0 utf8');
fprintf(fid,' \n DEF mesh Transform{');
fprintf(fid,' \n translation ');
fprintf(fid,num2str(point));
fprintf(fid,' \n scale 2 0.01 2' );
fprintf(fid,' \n children[');
fprintf(fid,' \n Shape' );
fprintf(fid,' \n { appearance Appearance { ');
%fprintf(fid,' \n texture ImageTexture { url ["');
%fprintf(fid, image);
%fprintf(fid,'"]}');
fprintf(fid,' \n material Material{');
fprintf(fid,' \n diffuseColor 1.0 1.0 1.0');
fprintf(fid,' \n ambientIntensity 1.1666667');
fprintf(fid,' \n specularColor 0.4012008 0.4012008 0.4012008');
fprintf(fid,' \n emissiveColor  0 0 0');
fprintf(fid,' \n shininess 0.0976563');
fprintf(fid,' \n transparency 0.0 } }');	
fprintf(fid,' \n geometry ElevationGrid {');
fprintf(fid,' \n xDimension ');
fprintf(fid, num2str(s(1)));
fprintf(fid,' \n xSpacing 0.1');
fprintf(fid,' \n zDimension ');
fprintf(fid, num2str(s(2)));
fprintf(fid,' \n zSpacing 0.1');
fprintf(fid,' \n height[ ');
f = heatMap(:);
f = f';
k=f;
%s2 = size(f);
%for i = 1: s2(2)
%    if (mod(i,2) == 0 || mod(floor(i/s(2)), 2) == 0)
%        f(i) = f(i);
%    end
%end

fprintf(fid, num2str(f));
fprintf(fid,' ]');
fprintf(fid,' \n color Color { color [');
%Farbe :-)
color = zeros(s(1)*s(2), 3);
for i = 1:s(1)*s(2)
    if k(i) <= 100
        h = [0 0.5 0];
    elseif k(i)>100 && k(i)<250
        h = [0.5 0.5 0];
    else
        h = [1 0 0];
    end
    color(i,:) = h;
    str = [num2str(color(i,:)), ', '];
    fprintf(fid, str);
    
end

fprintf(fid, '] }');

fprintf(fid,' \n colorPerVertex TRUE');

fprintf(fid,' \n normal NULL');
fprintf(fid,' \n normalPerVertex FALSE');
fprintf(fid,' \n texCoord NULL');
fprintf(fid,' \n ccw FALSE');
fprintf(fid,' \n solid FALSE');
fprintf(fid,' \n creaseAngle 0 } } ] }');

fclose(fid);
copyfile(filename, filename_final, 'f');
delete(filename);
end

