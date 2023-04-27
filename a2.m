P = rand(10, 2);
T = delaunayTriangulation(P);
triplot(T, '-.')
hold on
plot(P(:, 1), P(:, 2), '*')