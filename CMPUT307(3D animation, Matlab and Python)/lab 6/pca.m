classdef pca
    methods(Static)
        function centeroid = center(m)
            centeroid = transpose(m);
            centeroid = mean(centeroid);
            centeroid = transpose(centeroid);
        end

        function [eigen, eigen_vec, covar] = eigen_data(m)
            mean_mat = pca.center(m);
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
        end

    end
end




%plot3