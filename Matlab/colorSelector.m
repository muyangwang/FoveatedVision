%%% Given a block, choose what color should be used.
%%% Method:
%%% select random block color for now.If the block is out of range, set it
%%% to 0. If the block is half out of range, set the block color based on
%%% valid points.
%%% ToDO:If the block contains a corner or edge, choose a random point in the
%%% section as block color, otherwise use average color for the block. 
%%% TODO: Possible improvement: use a tuple to represent a block's possible
%%% color, so that edges' imformation might be saved.
function color = colorSelector(image, layer, position)
[height, width, ~] = size(image);
color = [0 0 0];
if (layer == 1)

    if (position(1) > 1 && ...
            position(1) <= height && ...
            position(2) > 1 && ...
            position(2) <= width)
        disp(position(1));
        disp(position(2));
        color = image(position(1), position(2),:);
    end
else
    blockSize = 2^(layer-1);
    % find in range block
    if (position(1) > height || position(1)+ blockSize-1 < 1 || ...
            position(2) > width || position(2) + blockSize-1 <1)
        % block fully outof range
        %disp('fully out of range');
        color;
        return
    end
        
    if (position(1) > 1 && ...
            position(1)+blockSize-1 < height && ...
            position(2) > 1 && ...
            position(2)+blockSize-1< width)
        %block fully in range
        %disp('fully in range');
        pos = randi([0 blockSize-1],1,2);
        color = image(position(1)+pos(1), position(2)+pos(2),:);
        return
    end
    
    % the block is half out of range
    % the valid block is the closure of [top, bot],[left, right]
    %disp('half out of range');
    if (position(1) < 1)
        topBorder = 1;
    else
        topBorder = position(1);
    end
    if (position(1)+blockSize-1>height)
        botBorder = height;
    else
        botBorder = position(1)+blockSize-1;
    end
    if (position(2) < 1)
        leftBorder = 1;
    else
        leftBorder = position(2);
    end
    if (position(2)+blockSize-1>width)
        rightBorder = width;
    else
        rightBorder = position(2)+blockSize-1;
    end
    asize = botBorder-topBorder+1;
    bsize = rightBorder-leftBorder+1;
    a = randi([0 asize-1],1,1);
    b = randi([0 bsize-1],1,1);
    color = image(topBorder+a, leftBorder+b,:);
    return;
end
color;
end