%interactive user input to selct file
files_ = ["eclipse1.mat" "eclipse2.mat" "eclipse3.mat";"3d_sphere.mat" "bun_zipper.mat" "teapot.mat"];

user_dimensions = input("Enter the dimensions 2 or 3 to generate pca data for: ");
while ~or(user_dimensions == 2, user_dimensions == 3)
    disp("Invalid dimensions");
    user_dimensions = input("Enter the dimensions 2 or 3 to generate pca data for: ");
end

if (user_dimensions == 2)
    disp("Available 2d files:");
    disp(files_(1,:));
elseif (user_dimensions == 3)
    disp("Available 3d files:");
    disp(files_(2,:));
end

user_data = input("Enter a file number 1,2 or 3 to generate pca for: ");
while ~and(user_data >= 1, user_data <= 3)
    disp("Invalid file");
    user_data = input("Enter a file number 1,2 or 3 to generate pca for: ");
end

disp("Selected file: ");
disp(files_((user_dimensions-1), user_data));

data = load(files_((user_dimensions-1), user_data));
nd_array = transpose(data.X); %the data dimensions are reversed to d*n instead of n*d
if (user_dimensions == 2)
    plot2d_pca(nd_array);
elseif (user_dimensions == 3)
    plot3d_pca(nd_array);
end

%This function finds the center of the pca projection by calculating the
%mean matrix
function centeroid = center(m)
    centeroid = transpose(m);
    centeroid = mean(centeroid); %the mean function calculates column wise mean, so we transpose it back and forth
    centeroid = transpose(centeroid);
end

%this function returns the eigen values, a dXd array with the eigen vectors
%and the covariance matrix
function [eigen, eigen_vec, covar] = eigen_data(m)
    mean_mat = center(m);
    rows = size(m,1);
    columns = size(m,2);
    centered = zeros(rows, columns);
    for i = drange(1:rows)
        for j = drange(1:columns)
            centered(i,j) = m(i,j)-mean_mat(i);
        end
    end
    covar = centered*transpose(centered);
    eigen = eig(covar);
    [eigen_vec,~] = eig(covar);
%     disp("mean of all points: ");
%     disp(mean_mat);
%     disp("dxd covariance matrix: ");
%     disp(covar);
%     disp("eigen values: ");
%     disp(eigen);
%     disp("dxd eigen vectors matrix: ");
%     disp(eigen_vec);
end

%this function plots the eigen vectors and their associated data points
function plot2d_pca(m)
    rows = size(m,1);
    assert(rows == 2);
    centroid = pca.center(m);
    [~,eigenvector,~] = eigen_data(m);
%     fig1=figure(1);
    plot(m(1,:),m(2,:),'.');
    hold on
    plot([centroid(1) eigenvector(1,1)], [centroid(2) eigenvector(2,1)],'b');
    plot([centroid(1) eigenvector(1,2)], [centroid(2) eigenvector(2,2)],'r');
    
end

%plot3d
function plot3d_pca(m)
    rows = size(m,1);
    assert(rows == 3);
    centroid = pca.center(m);
    [~,eigenvector,~] = eigen_data(m);
%     fig1=figure(1);
    %plot points and then hold on
    plot3(m(1,:),m(2,:),m(3,:),'.');
    hold on
    plot3([centroid(1) eigenvector(1,1)], [centroid(2) eigenvector(2,1)], [centroid(3) eigenvector(3,1)],'b');
    plot3([centroid(1) eigenvector(1,2)], [centroid(2) eigenvector(2,2)], [centroid(3) eigenvector(3,2)],'r');
    plot3([centroid(1) eigenvector(1,3)], [centroid(2) eigenvector(2,3)], [centroid(3) eigenvector(3,3)],'g');
    
end