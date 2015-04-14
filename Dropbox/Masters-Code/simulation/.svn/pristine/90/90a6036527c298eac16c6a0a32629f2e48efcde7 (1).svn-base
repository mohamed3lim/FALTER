function ret = columnMinNotNull( A )

% replace zeroes entries by NaN, such tham min won't find them...
A(A==0) = inf;

mins = min(A);

mins(isinf(mins)) = 0;

ret = mins;

end

