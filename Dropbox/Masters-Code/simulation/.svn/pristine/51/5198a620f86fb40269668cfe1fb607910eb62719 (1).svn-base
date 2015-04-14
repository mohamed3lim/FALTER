function mygrid(i)

%baut eine 3d-Heatmap ins Bild aus einer Matrix
%Load HeatMap
temp = load('fortiss.mat');
heatMap = temp.map;
clear temp;
%Load size of map
s = size(heatMap);
%save names

filename='finalgrid.wrl';
%open file for writing
fid = fopen(filename, 'w+', 'n', 'UTF-8');
%header of VRML-file
fprintf(fid, '#VRML V2.0 utf8');
%wrinting VRML file
fprintf(fid,' \n DEF mesh Transform{');
%start point of the grid in the left buttom corner
fprintf(fid,' \n translation -27 -1.04 -15');
%fprintf(fid,num2str(point));
%scaling of the grid, at the moment it needs the double size to fit the
%walls
fprintf(fid,' \n scale 2 0.01 2' );
fprintf(fid,' \n children[');
fprintf(fid,' \n Shape' );
fprintf(fid,' \n { appearance Appearance { ');
%for texture-use you need these lines:
%fprintf(fid,' \n texture ImageTexture { url ["');
%fprintf(fid, image);
%fprintf(fid,'"]}');
fprintf(fid,' \n material Material{');
%it is red
fprintf(fid,' \n diffuseColor 0.8 0.3 0');
fprintf(fid,' \n ambientIntensity 1.1666667');
fprintf(fid,' \n specularColor 0.8 0.3 0.0');
fprintf(fid,' \n emissiveColor  0 0 0');
fprintf(fid,' \n shininess 0.0976563');
fprintf(fid,' \n transparency 0.5 } }');	
fprintf(fid,' \n geometry ElevationGrid {');
%the grid
%dimensions are taken from the matrix
fprintf(fid,' \n xDimension ');
fprintf(fid, num2str(s(1)));
fprintf(fid,' \n xSpacing 0.1');
fprintf(fid,' \n zDimension ');
fprintf(fid, num2str(s(2)));
fprintf(fid,' \n zSpacing 0.1');
fprintf(fid,' \n height[ ');
%one row vector of the grid
f = heatMap(:);
%one line vector of the grid
f = f';
fprintf(fid, num2str(f));
fprintf(fid,' ]');
fprintf(fid,' \n color NULL');
%Using colors leads to horrible rendering of transparency and even worse
%performance
%Farbe :-)
%color = zeros(s(1)*s(2), 3);
%for i = 1:s(1)*s(2)
%    if k(i) <= 100
%        h = [0 0.5 0];
%    elseif k(i)>100 && k(i)<250
%        h = [0.5 0.5 0];
%    else
%        h = [1 0 0];
%    end
%    color(i,:) = h;
%    str = [num2str(color(i,:)), ', '];
%    fprintf(fid, str);    
%end

fprintf(fid,' \n colorPerVertex FALSE');

fprintf(fid,' \n normal NULL');
fprintf(fid,' \n normalPerVertex FALSE');
%fprintf(fid,' \n texCoord NULL');
%fprintf(fid,' \n ccw FALSE');
fprintf(fid,' \n solid FALSE');
fprintf(fid,' \n creaseAngle 0 } } ] }');

fclose(fid);


end