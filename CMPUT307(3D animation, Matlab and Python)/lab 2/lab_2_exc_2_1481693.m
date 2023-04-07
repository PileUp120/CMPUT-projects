d_x = 2; % howmuchever you want to translate in horizontal direction
d_y = 3; % howmuchever you want to translate in vertical direction
% create the original box
% first row has horizontal coordinates, second row has vertical coordinates
my_points = [1 1 2 2 1;1 2 2 1 1];
% write code to plot the original box
fig1=figure(1);
plot(my_points(1,:), my_points(2,:));
% write code to create your Homogeneous 2D Translation matrix my_trans using d_x and d_y
my_trans = eye(3); %method referenced from https://www.mathworks.com/help/matlab/ref/eye.html
%method referenced from example found 
%in https://www.mathworks.com/matlabcentral/answers/120180-how-i-select-a-part-or-section-of-a-matrix#answer_127079
%by user Image Analyst in thread https://www.mathworks.com/matlabcentral/answers/120180-how-i-select-a-part-or-section-of-a-matrix
my_trans(1:2,3) = [d_x;d_y];
% Next, we perform the translation
% write code to convert my_points to the homogeneous system and store the result in hom_my_points
ones_row = ones(1, length(my_points)); %referenced from offical matlab documentation https://www.mathworks.com/help/matlab/ref/ones.html
hom_my_points = [my_points; ones_row];
% write code to perform translation in the homogeneous system using my_trans and hom_my_points and store the result in trans_my_points
trans_my_points = my_trans*hom_my_points;
hold on
% write code to plot the Translated box (output) which has to be done in Cartesian, so...
% cut out the X, Y points and ignore the 3rd dimension
plot(trans_my_points(1,:), trans_my_points(2,:));
axis([0.5 4.5 0.5 5.5]); % modified axes to allow for viewing larger translations