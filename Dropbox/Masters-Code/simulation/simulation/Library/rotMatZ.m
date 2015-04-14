function ret = rotMatZ( angle )
%ROTMATZ Summary of this function goes here
%   Detailed explanation goes here

result = eye(3);

result(1,1) = cos(angle);
result(2,1) = sin(angle);
result(1,2) = -sin(angle);
result(2,2) = cos(angle);

ret = result;
end

