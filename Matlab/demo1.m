%%% demo of generation of foveatedImages

im = double(imread('flower1.jpg'))/255;
figure;
imshow(im);
[y, x] = getpts;
foveatedImage = createCenteredPyramids(im,[int16(x) int16(y)],5);
reconstructImage(foveatedImage);