function ret = genBeamPrototype(horizontalResolution, verticalResolution)
% Range of the camera in m
detectionRange = 3;
% horizontalResolution = 64;
% verticalResolution = 48;
% horizontalResolution = 128;
% verticalResolution = 96;

angularResolution = (pi/6) / verticalResolution;

% angularResolution = (pi/6) /48;

result = ones(horizontalResolution*verticalResolution, 3);

%for h = (-(floor(horizontalResolution/2)-0.5) * angularResolution) : angularResolution : ((floor(horizontalResolution/2)-0.5) * angularResolution),
%    for v = (-(floor(verticalResolution/2)-0.5) * angularResolution) : angularResolution : ((floor(verticalResolution/2)-0.5) * angularResolution),
%        result(h + horizontalResolution*(v-1), 1:3) = (rotMatZ(h) * rotMatY(v) * [1 0 0]')'
%    end;
%end;


    for v = 1 : 1 : verticalResolution,
        for h = 1 : 1 : horizontalResolution,
            %angleH = (h-1-floor(horizontalResolution/2))*(angularResolution) + angularResolution/2;
            %angleV = (v-1-floor(verticalResolution/2))*(angularResolution) + angularResolution/2;

            angleH = ((floor(horizontalResolution/2) - 1) - (h-1))*(angularResolution) + angularResolution/2;
            angleV = ((floor(verticalResolution/2) - 1) - (v-1))*(angularResolution) + angularResolution/2;

            %result(h + horizontalResolution*(v-1), 1:3) = (rotMatZ(angleV) * rotMatY(angleH) * [detectionRange 0 0]')';
            result(v + verticalResolution*(h-1), 1:3) = (rotMatZ(angleV) * rotMatY(angleH) * [detectionRange 0 0]')';
            %result(h + horizontalResolution*(v-1), 4) = h + horizontalResolution*(v-1);
            %result(h + horizontalResolution*(v-1), 5) = norm(result(h + horizontalResolution*(v-1), 1:3));
        end;
    end;

ret = result;
    
end

