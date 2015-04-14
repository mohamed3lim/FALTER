function matrix = BoxMatrix(box)
%computes walls from a position to build a box

A = zeros(1, 3);
B = zeros(1, 3);
box = box';
position = box(1:3);
size = box(4:6);
for i = 1: 3
    A(i) = position(i) - size(i)/2;
    B(i) = position(i) + size(i)/2;
end
%six walls for our box:
if(all(size == 0))
    matrix = zeros(6,9);
else 
    matrix =  [A, 0 size(2) 0, size(1) 0 0;
            A, 0 size(2) 0, 0 0 size(3);
            A, 0 0 size(3), size(1) 0 0;
            B, 0 -size(2) 0, -size(1) 0 0;
            B, 0 -size(2) 0, 0 0 -size(3);
            B, 0 0 -size(3), -size(1) 0 0];
end
end

