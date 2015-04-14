function output = newSensor(k)
%places the sensor
dir = k(1:3);

falter = k(4:6);


position = falter + dir;
rotationaxis = cross(dir, [0 1 0]);


winkel = [rotationaxis, 1.5708];
y = position;
y(2) = y(2)+0.1;
position =[y(1) y(2) y(3)];

output(1:4) = winkel;
output(5:7) = position;

end