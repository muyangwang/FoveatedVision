%%% this function takes one of the saccade image as input. 
%%% return: a set of possible foveated Images for the raw image.

function foveatedSets = initProcess(rawImage, numLayers)
featurePoints = detection(rawImage);
[numF, ~] = size(featurePoints);
for i = 1:numF
    foveatedSets(:,:,:,i) = createCenteredPyramids(rawImage, featurePoints(i,:), numLayers);
end
foveatedSets;
end