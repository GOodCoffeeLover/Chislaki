echo "Lab №5, Var 23"
echo "Trofimov M.A. M8O-308b-18"
echo ""

echo "y'=  -2 *y + x*x -2"
echo "8 <= x <= 12 ,  y(8) =  -1"
echo ""

echo "Euler; h = 1.0 0.5 0.4"
g++ Euler_first_order.cpp -w && ./a.out
echo ""

echo "Runge-Kutte; h = 1.0 0.5"
g++ Runge-Kutte_first_order.cpp -w && ./a.out
echo ""

echo "y''=    y'  -2 * y  +  3 * x  -6 "
echo "-3 <= x <=  -1  ; y(-3 ) = -2.0 ;  y'(-3 ) = -6.0"
echo ""

echo "Euler; h = 0.50 0.25 0.20"
g++ Euler_second_order.cpp -w && ./a.out
echo ""

echo "Runge-Kutte; h = 0.50 0.25"
g++ Runge-Kutte_second_order.cpp -w && ./a.out
echo ""


echo "Finite Difference; h = 0.20"
echo "2* y'' -y' -4* y = -5* x*x -5* x -1 "
echo "1 <= x <=  2"
echo "5* y( 1)    =   3"
echo "5* y( 2)    =   5"
g++ finite_diff.cpp -w && ./a.out echo ""
echo ""

