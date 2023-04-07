X = pcread('dragondata/dragon.ply');
%figure(1)

%scatter3(X.Location(:,1),X.Location(:,2),X.Location(:,3),"b.");

%  ---------------- Write your code here  ---------------------------

%center the input matrrix
c = center_matrix(X.Location);
%create a n+1 by 4 homogenous version of the matrix
h_c = [c;zeros(1,3)];
h_c = [h_c zeros(size(h_c,1),1)];
h_c(size(h_c,1),4) = 1;
%get the eigen data
[~,eigen_vectors,~] = eigen_data(c);
first_eigen = eigen_vectors(:,1);
first_eigen_t = transpose(first_eigen);
x_axis = [1 0 0];
theta = angle_bw_two(first_eigen_t, x_axis);
rot_matrix = make_xt(theta);
transformed_points = h_c * rot_matrix;
transformed_points(size(transformed_points,1),:) = [];
transformed_points(:,4) = [];
transformed_points = sortrows(transformed_points);
min_x = transformed_points(1,1);
max_x = transformed_points(size(transformed_points,1),1);

figure(1)
hold on;
scatter3(transformed_points(:,1),transformed_points(:,2),transformed_points(:,3),"b.");

num_points = ceil(size(c,1)/100);
%
sp_intervals = {};
%intervals = zeros(100,2);
%i = 1;
st_idx = 1;
end_idx = size(transformed_points,1);
curr_idx = num_points-1;

while curr_idx < end_idx
    %{
    int_min = transformed_points(st_idx,1);
    int_max = transformed_points(curr_idx,1);
    intervals(i,:) = [int_min int_max];
    %}
    section = transformed_points(st_idx:curr_idx,:);
    sp_intervals{end+1} = section;
    %i = i+1;
    st_idx = curr_idx+1;
    curr_idx = curr_idx + num_points;
end

final_section = transformed_points(st_idx:end_idx,:);
sp_intervals{end+1} = final_section;

num_clusters = ceil(size(c,1)/1000);



clusters = {};
for cel = sp_intervals
    arr = cell2mat(cel);
    [assignments,centers,~,distances] = kmeans(arr,num_clusters);
    radii = max(distances);
    for i = 1:length(centers)
        rad_mat = [radii(i) 0 0];
        combo = [rad_mat; centers(i,:)];
        combo = transpose(combo);
        clusters{end+1} = combo;
    end
end

fileID = fopen('custers.txt','w');

for cus = clusters
    writecell(cus,'custers.txt','WriteMode','append');
end

fclose(fileID);
%this function calculates the average of a matrix column wise
function centeroid = center(m)
    centeroid = mean(m);
end

%this function centers a matrix of points using the average of the matrix
function centered = center_matrix(inp_matrix)
    mean_mat = center(inp_matrix);
    centered = inp_matrix - mean_mat;
end

%this function assumes that a matrix of centered data points is being
%passed to it, and returns an array with the written parameters
function [eigen, eigen_vec, covar] = eigen_data(m)
    s = transpose(m); %we need a 3x3 covariance matrix for a 3d data set
    covar = s*transpose(s);
    eigen = eig(covar);
    [eigen_vec,~] = eig(covar);
end

function angle = angle_bw_two(vector1,vector2)
    scalar = dot(vector1, vector2);
    mag1 = sqrt(sum(vector1.*vector1));
    mag2 = sqrt(sum(vector2.*vector2));
    cos_t = scalar/(mag1*mag2);
    angle = acos(cos_t);
end

function x_rotation = make_xt(theta)
    x_rotation = eye(4);
    x_rotation(2,2) = cos(theta); x_rotation(3,3) = cos(theta);
    x_rotation(3,2) = sin(theta); x_rotation(2,3) = -1*sin(theta);
end

%rotation matrix is inverse of eigen vector
%https://www.mathworks.com/help/matlab/ref/cell.html