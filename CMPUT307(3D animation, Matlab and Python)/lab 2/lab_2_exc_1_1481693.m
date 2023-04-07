% create box
% first row is horizontal coordinates; second row is vertical coordinates
my_pts = [2 2 3 3 2;2 3 3 2 2];
% write code here to display the original box
fig1=figure(1);
%referring to specific row of a matrix method from https://www.mathworks.com/matlabcentral/answers/175231-extract-first-row-from-matrix#answer_349252
%by userMathworks SUpport Team in thread https://www.mathworks.com/matlabcentral/answers/175231-extract-first-row-from-matrix
plot(my_pts(1,:), my_pts(2,:)); 
% write code here to create your 2D rotation matrix my_rot
my_rot = [];
%method referenced from https://www.mathworks.com/help/matlab/ref/deg2rad.html
theta = -deg2rad(23); %rotate clockwise by 23 degrees, but convert to radians to work with matlab default functions
my_rot(1,1) = cos(theta); my_rot(2,2) = my_rot(1,1); %referenced from lecture notes
my_rot(2,1) = sin(theta); my_rot(1,2) = -my_rot(2,1); 
% write code to perform rotation using my_rot and my_pts and store the result in my_rot_pts
my_rot_pts = my_rot * my_pts;
hold on
%write code to plot output
plot(my_rot_pts(1,:), my_rot_pts(2,:));
axis([1.5 4.5 0 3.5]);