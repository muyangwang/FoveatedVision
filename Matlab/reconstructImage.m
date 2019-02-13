%%% This function recontruct a regular image from a foveatedImage and print
%%% to screen. foveatedImage is defined in createCenteredPyramids.m

%%% layer 5: 1  -256, 257-512
%%% layer 4: 129-256, 257-384
%%% layer 3: 193-256

function reconstructImage(foveatedImage)
[~,~,~, numLayers] = size(foveatedImage);
imageSize = 32*2^(numLayers-1);
reconstructedImage = zeros(imageSize,imageSize,3);
%reconstructedImage = zeros(512,512,3);
for i = 1:numLayers
    layer = numLayers+1-i;
    blockSize = 2^(layer-1);
    %%% for each layer, the valid cover range is from halfImSize-blockSize*16+1 to
    %%% halfImSize+blockSize*16, the mid split line is halfImSize,halfImSize+1 for all layers
    for j = 1:32
        for k = 1:32
            % set color for a block
            blockStartingIndex1 = imageSize/2+(j-16-1)*blockSize; % pos 0
            blockStartingIndex2 = imageSize/2+(k-16-1)*blockSize; % pos 0
            for l = 1:blockSize
                for m = 1:blockSize
                    reconstructedImage(blockStartingIndex1+l, blockStartingIndex2+m,:) ...
                        = foveatedImage(j,k,:,layer);
                end
            end
        end
    end
end
figure;
imshow(reconstructedImage);


end