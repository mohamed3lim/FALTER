function print3dCamPic( u )
%Plots a heatmap of the 3d CAMs distance values...

% Subplot on positions 4,2 and 5,2
width = 2;
hight = 5;
subplot(hight, width, [8 10]);

% Plot image
%imagesc(fliplr(flipud(u)));
imagesc(u);
title('PMD Cam');

return;

end

