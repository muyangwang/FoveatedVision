%%% given a foveatedImage and information about our objective, generate a
%%% step motion of the centerPoint. Set ifMatched to 1 if the objective
%%% falls in the area with most activation.

%%% TODO: determine step size.

function [ifMatched, dx, dy] = generateNextCameraMotion(retinaImage, objectiveInfo)
ifMatched = 0;
[layer, x, y] = detection(foveatedImage, objectiveInfo);
if (layer == 1)
    ifMatched = 1;
end
% we use 1/3 distance of current center to matched block center as moving step.
blockSize = 2^(layer-1);
dx = (x-16)* blockSize/3;
dy = (y-16)* blockSize/3;

if dx > 0
    dx = floor(dx);
else
    dx = -floor(-dx);
end

if dy > 0
    dy = floor(dy);
else
    dy = -floor(-dy);
end

[ifMatched, dx, dy];
end