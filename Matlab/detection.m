%%% give a foveatedImage and info about our objective, this function
%%% matches from the mosted detailed layer to least detailed layer, and
%%% stop once we hit a match.

%%% return:
%%%    - the id of layer the objective is found.
%%%    - location of objective in current layer.

function [layer, x, y] = detection(foveatedImage, objectiveInfo)
[~,~,~,numLayers] = size(foveatedImage);
for i = 1:numLayers
    % match each layer with our objective. if found, break and return result.
end
[layer, x, y];
end