%%% Give an image and a centered point, this function create a corresponding foveated
%%% image. Each foveated image is represented by 5 matrices, each 32*32.
%%% In this project, the centered point is defined as the top right one of
%%% 4 middle pixels.

function foveatedImage = createCenteredPyramids (image, centerPosition, numLayers)
[height, width,~] = size(image);
foveatedImage = zeros(32, 32, 3, numLayers);

for layer = 1:numLayers
    blockSize = 2^(layer-1);
    for i = 1:32
        for j = 1:32
%             disp('layer');
%             disp(layer);
%             disp(centerPosition(1)+(i-16)*blockSize);
%             disp(centerPosition(2)+(j-16)*blockSize);
            foveatedImage(i,j,:,layer) = ...
                colorSelector(image, layer, [centerPosition(1)+(i-16)*blockSize, centerPosition(2)+(j-16)*blockSize]);
        end
    end
end
foveatedImage;
end