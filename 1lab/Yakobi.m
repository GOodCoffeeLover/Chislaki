format compact

  
  function [k, m] = maxij(A)
    k = 1;
    m = 2;
    for i = 1:(size(A, 1)-1)
        for j = i+1:size(A, 2)
            if (abs(A(k, m)) < abs(A(i,j)))
                k = i;
                m = j;
            end
        end
    end
  end
   
  function [A, V] = yakobi(A, n)
    V = eye(size(A));
    for i = 1:n
        i
        [k,m] = maxij(A);
        fi = atan(2*A(k,m)/(A(k,k) - A(m,m)))/2
        h=eye(size(A));
        h(k,k)= cos(fi);  h(k,m) = -sin(fi);
        h(m,k)= sin(fi);  h(m,m) = cos(fi);
        h
        inv(h)*A
        V = V*h;
        A= inv(h)*A*h
    end
    for i = 1:size(V)
        V(:,i)/=max(V(:, i));
    end
 end
 
 A = [-4, -6, -10; 
    -6, -11,  4;
    -10, 4, -3];
[L,V] = yakobi(A, 6)