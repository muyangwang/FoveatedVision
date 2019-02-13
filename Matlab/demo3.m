%% given a sequnce of saccade foveated images, detect and match features in
% them. And generate a motion map of each feature.

% foveats is a sequence of saccade foveated images, cameraMotion is a
% sequence of movement of camera, including [dx, dy], may further [theta,
% phi] for next step implementation.

%% Initialization
load(timeticks.mat);
load(foveats.mat);

% camera motion can be unknown in further implementations.
load(cameraMotion.mat);

state = stateInitialier();

%% loop through using time ticks to simulate a real-time matching process.
for t = 1:maxTimeTicks
    
    % detect any feature in the most detailed layer of current frame and if
    % a new feature is detected, add it to the objective list. If an old
    % one, update its position vs time tick matrix.
    objectives = featureGenrator(foveats[:,:,:,:,t], objectives);
    
    %remove objectives that dont occur for a long time.
    objectives = simplify(objectives);
    
    %calculate each objective's motion along time. 
    %(may determined the motion of camera if we have some known objectives that dont move over time)
    
end