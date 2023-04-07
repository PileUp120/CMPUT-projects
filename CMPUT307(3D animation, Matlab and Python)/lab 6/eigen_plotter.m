classdef eigen_plotter
    methods(Static)
        function plot2d_pca(m)
            rows = size(m,1);
            assert(rows == 2);
            centroid = pca.center(m);
            [eigen_val,eigenvector,covar_mat] = pca.eigen_data(m);
            fig1=figure(1);
            hold on
            plot([centroid(1) eigenvector(1,1)], [centroid(2) eigenvector(2,1)], 'b');
            plot([centroid(1) eigenvector(1,2)], [centroid(2) eigenvector(2,2)], 'r');
        end

        %plot3d
        function plot3d_pca(m)
            rows = size(m,1);
            assert(rows == 3);
            centroid = pca.center(m);
            [eigen_val,eigenvector,covar_mat] = pca.eigen_data(m);
            fig1=figure(1);
            hold on
            plot3([centroid(1) eigenvector(1,1)], [centroid(2) eigenvector(2,1)], [centroid(3) eigenvector(3,1)], 'b');
            plot3([centroid(1) eigenvector(1,2)], [centroid(2) eigenvector(2,2)], [centroid(3) eigenvector(3,2)],'r');
            plot3([centroid(1) eigenvector(1,3)], [centroid(2) eigenvector(2,3)], [centroid(3) eigenvector(3,3)],'g');
        end

    end
end

%plot2d
