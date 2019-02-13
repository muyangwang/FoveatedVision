%%% given scene, an initial foveated image and information of our
%%% objective. Generate a sequence of motion of camera to approach the
%%% location of objective.

scene = double(imread('flower1.jpg'))/255;

%% Initialize some objective info for feature matching here.
objectiveInfo = 0;

figure;
imshow(im);
[y, x] = getpts;
initialCameraPos = [x y];
retinaImage = createCenteredPyramids(scene,[int16(x) int16(y)],5);

%% looping through to move camera to approach objective.
while (1)
    [ifMatched, dx, dy] = generateNextCameraMotion(intialRetina, objectiveInfo);
    if ifMatched
        break;
    end
    x = x+dx;
    y = y+dy;
    retinaImage = createCenteredPyramids(scene,[int16(x) int16(y)],5);
end
reconstructImage(retinaImage);