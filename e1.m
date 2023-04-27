[X, Y] = meshgrid(-20:.5:20);
Z = besselj(1, 0.5 * sqrt(X.*X + Y.*Y));
surf(X, Y, (Z.*Z)./(X.*X + Y.*Y))