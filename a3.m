h = 0.3; % main step
x_beg = 0; % left boundary of the working zone
x_end = 3; % right boundary of the working zone

% make grid denser at the boundaries
% boundaries' derivatives
x = [x_beg:h./10:x_beg+h, x_beg+2.*h:h:x_end-2.*h , x_end-h:h./10:x_end]'; 
% working zone's grid

% different functions
%y = sin(x);
%y(x==0) = 1;
y = exp(-x.^2); % function
dy_exact  = -2.*x.*exp(-x.^2); % exact derivative
d2y_exact = -2.*exp(-x.^2) + 4.*x.^2.*exp(-x.^2); % exact 2nd derivative 
%y2 = 2.*exp(-x) - 4.*x.*exp(-x) + x.^2.*exp(-x);
%y2 = -0.2.*exp(-(x.^2)./10) + ((0.2.*x).^2).*exp(-(x.^2)./10);

n = length(x); % number of grid nodes
                                                                                   
% make empty matrices n x n
Dx  = sparse(n,n); 
D2x = sparse(n,n);

d = difs_nkl_row(x,0,1,4); % make rows of derivatives, 0 left 4 right
Dx(1,1:5) = d(1,:);   % fill the first row of derivative's matrix
D2x(1,1:5) = d(2,:);  % fill the 2nd row of 2nd derivative's matrix

d = difs_nkl_row(x,1,2,3); % make rows of derivatives, 0 left 4 right
Dx(2,1:5) = d(1,:);   % fill the first row of derivative's matrix
D2x(2,1:5) = d(2,:);  % fill the 2nd row of 2nd derivative's matrix

for ii = 3: n-2 % inner nodes' cicle
    d = difs_nkl_row(x,2,ii,2);  % make rows of derivatives, 2 left 2 right
    Dx(ii,ii-2:ii+2) = d(1,:);   % fill the current row of derivative's matrix
    D2x(ii,ii-2:ii+2) = d(2,:);  % fill the current row of 2nd derivative's matrix
end

d = difs_nkl_row(x,3,n-1,1);  % make rows of derivatives, 3 left 1 right
Dx(n-1,n-4:n) = d(1,:);  % fill the penult row of derivative's matrix
D2x(n-1,n-4:n) = d(2,:); % fill the penult row of 2nd derivative's matrix

d = difs_nkl_row(x,4,n,0);   % make rows of derivatives, 4 left 0 right
Dx(n,n-4:n) = d(1,:);   % fill the last row of derivative's matrix
D2x(n,n-4:n) = d(2,:);  % fill the last row of 2nd derivative's matrix

%U = exp(-(x.^2)./1);
%H = D2x + speye(n,n).*U.*400;

d2y = D2x*y; % numerically - 1st derivative
dy = Dx*y; % numerically - 2nd derivative

figure;
hold on;
grid on;
plot(x,y,'.-b');  
plot(x,dy,'.-m'); 
plot(x,dy_exact,'-','color',[0.5 0 0.5]); % color - dark purple
plot(x,d2y,'.-r');
plot(x,d2y_exact,'-','color',[0.5 0 0]);
legend('function','numerical derivative','exact derivative', ...
    'exact 2nd derivative','numerical 2nd derivative');


function d = difs_nkl_row(x,l,n,r)
% БШВХЯКЕМХЕ ЯРПНЙХ ЛЮРПХЖ ДХТТ НОЕПЮРНПНБ Я МНЛЕПНЛ n 
% n - ПЮАНВХИ МНЛЕП СГКЮ ЯЕРЙХ (n>0,k>0,r>0)
% l - ЙНКХВЕЯРБН ЬЮЦНБ БКЕБН (n-l)
% r - ЙНКХВЕЯРБН ЬЮЦНБ БОПБН (n+r)

    hl = zeros(l,1); % ЯЛЕЫЕМХЪ ОН ЯЕРЙЕ БКЕБН
    for ii = l : -1 : 1
        hl(l-ii+1) = x(n-ii) - x(n);
    end
    hr = zeros(r,1); % ЯЛЕЫЕМХЪ ОН ЯЕРЙЙЕ БОПЮБН
    for ii = 1 : r
        hr(ii) = x(n+ii) - x(n);
    end
    hh = [hl;hr]; % НАЗЕДХМЪЕЛ Б НАЫХИ БЕЙРНП ЯЛЕЫЕМХИ 
    
    % ЙНЩТТХЖХЕМРШ НАПЮРМШУ ТЮЙРНПХЮКНБ
    cg = [1:r+l]; 
    cg = 1./gamma(cg+1);
        
    A = hh.*ones(r+l,r+l);  % ЯРПНХЛ НАЫСЧ ЛЮРПХЖС ЙНЩТТХЖХЕМРНБ 
    for ii = 1:r+l
        A(:,ii) = A(:,ii).^ii; % СВ╦Р ЯРЕОЕМЕИ
    end
    A = A.*cg; % СВ╦Р ТЮЙРНПХЮК-ЛМНФХРЕКЕИ
    % ЙЮФДЮЪ ЯРНЙЮ ЛЮРПХЖШ A  - МЮАНП ЙНЩТТХЖХЕМРНБ Б якюс/ МЕХГБЕЯРМШЕ Б
    % ЩРНЛ якюс - ГМЮВЕМХЪ ОПНХГБНДМШУ. йЮФДЮЪ ЯРПНЙЮ якюс ДКЪ НРДЕКЭМНИ
    % БЕПЬХМШ ЯЕРЙХ
    
    % ПЕЬЮЕЛ якюс ВЕПЕГ QR-ПЮГКНФЕМХЕ. 
    [Q,R] = qr(A); % QR - ПЮГКНФЕМХЕ ЛЮРПХЖШ A
    
    % ЯРПНХЛ ЛЮРПХЖС ЯРНКАЖНБ ХГ ОПЮБНИ ВЮЯРХ  СПЮБМЕМХЪ Ax=b
    B = eye(l+r,r); % ЛЮРПХЖЮ Я ЕДХМХЖЮЛХ МЮ ЦКЮБМНИ ДХЮЦНМЮКХ
    B = [eye(l+r,l),-ones(l+r,1), B(end:-1:1,end:-1:1)]; % ХРНЦНБЮЪ ЛЮРПХЖЮ  ; B(end:-1:1,end:-1:1) - ОЕПЕБНПЮВХБЮЕЛ ЛЮРПХЖС
    B = Q'*B; % ОПЕНАПЮГСЕЛ ОПЮБСЧ ВЮЯРЭ якюс 
    d = R\B; % ХРНЦНБШИ ПЕГСКЭРЮР
end



% МХФЕ - 'ВЕПМНБХЙ'

function d = bound_row(x)
    
    h1 = x(2) - x(1);
    h2 = x(3) - x(1);
    h3 = x(4) - x(1);
    h4 = x(5) - x(1);
    
    A = [h1 0.5.*h1.^2 (h1.^3)./6 (h1.^4)./24
         h2 0.5.*h2.^2 (h2.^3)./6 (h2.^4)./24
         h3 0.5.*h3.^2 (h3.^3)./6 (h3.^4)./24
         h4 0.5.*h4.^2 (h4.^3)./6 (h4.^4)./24];
     
     [Q,R] = qr(A);
     
     b = [-1 1 0 0 0
          -1 0 1 0 0
          -1 0 0 1 0
          -1 0 0 0 1];
     b = Q'*b;
     d = R\b; 
end


function d = difs_n_row(x,n)
    
    h1 = x(n-2) - x(n);
    h2 = x(n-1) - x(n);
    h3 = x(n+1) - x(n);
    h4 = x(n+2) - x(n);
    
    A = [h1 0.5.*h1.^2 (h1.^3)./6 (h1.^4)./24
         h2 0.5.*h2.^2 (h2.^3)./6 (h2.^4)./24
         h3 0.5.*h3.^2 (h3.^3)./6 (h3.^4)./24
         h4 0.5.*h4.^2 (h4.^3)./6 (h4.^4)./24];
     
     [Q,R] = qr(A);
     
     b = [ 1 0 -1 0 0 
           0 1 -1 0 0
           0 0 -1 1 0
           0 0 -1 0 1 ];
     b = Q'*b;
     d = R\b;
    % d = [d(:,2:3),d(:,1),d(:,4:5)];
end

function d = difs_bn_row(x,n)
    
    h1 = x(n-1) - x(n);
    h2 = x(n+1) - x(n);
    h3 = x(n+2) - x(n);
    h4 = x(n+3) - x(n);
    
    A = [h1 0.5.*h1.^2 (h1.^3)./6 (h1.^4)./24
         h2 0.5.*h2.^2 (h2.^3)./6 (h2.^4)./24
         h3 0.5.*h3.^2 (h3.^3)./6 (h3.^4)./24
         h4 0.5.*h4.^2 (h4.^3)./6 (h4.^4)./24];
     
     [Q,R] = qr(A);
     
     b = [-1 1 0 0 0
          -1 0 1 0 0
          -1 0 0 1 0
          -1 0 0 0 1];
     b = Q'*b;
     d = R\b; 
     d = [d(:,2),d(:,1),d(:,3:5)];
end

function [D] = laplacian_1D(xx)
%LAPLACIAN_1D ЦЕМЕПЮРНП НОЕПЮРНПЮ КЮОКЮЯХЮМЮ ДКЪ 1D ЯЕРЙХ
%   
N = length(xx);

dx = xx(2) - xx(1);

ii = [1:N];
iix = [1:N-1];
jjx = [2:N];

t = ones(1,N).*(2./dx^2);
a = ones(size(iix)).*(-1./dx^2);

jj = [ii,jjx,iix];
ii = [ii,iix,jjx];
t  = -[t,a,a];

D = sparse(ii,jj,t,N,N);

end