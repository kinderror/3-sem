A = rand(110, 110);
B = A;
% i, ii, iii
s1 = 0;
s2 = 0;
for k = 1:110
    s1 = s1 + A(k, k);
    s2 = s2 + A(k, 111-k);
    B(k, k) = A(k, 111-k);
end
% iv
C = eye(11);
for ii = 1:11
    for jj = 1:11
        C(ii, jj) = det(B((10 * ii - 9):(10 * ii), (10 * jj - 9):(10 * jj)));
    end
end
C
det(C);
det(A);