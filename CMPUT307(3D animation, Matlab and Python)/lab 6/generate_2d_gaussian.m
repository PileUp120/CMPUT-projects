% Gaussian distr, Box-Mueller method
n = 1000;
U = rand(2,n);
v = 2*pi*U(2,:);
X = ones(2,1)*sqrt(-2.*log(U(1,:))).*[cos(v);sin(v)];

plot(X(1,:),X(2,:),'.')
axis equal

% Transform
A = [32 -10
     22 12];
t = [-20; 30];
Y = A*X+t*ones(1,n);
plot(Y(1,:),Y(2,:),'.')
axis equal
hold on