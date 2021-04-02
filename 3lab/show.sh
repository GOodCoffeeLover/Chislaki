echo "Lab №3"
echo "Trofimov M.A. M8O-308b-18"
echo ""

echo "x=   1.00   2.00   3.00   4.00"
echo "y=   4.00   7.00   4.00   7.00"
echo "x*=   2.50"


echo "Lagrange"
echo "x=   1.00   2.00   3.00"
g++ lagrang.cpp && ./a.out
echo ""

echo "Newton"
echo "x=   2.00   3.00   4.00"
g++ newton.cpp && ./a.out
echo ""

echo "Kanon"
echo "x=   1.00   2.00   3.00   4.00"
g++ kanon.cpp && ./a.out
echo ""

echo "Mnk"
echo "x=     -2.00   -1.00    1.00    3.00"
echo "y=     -4.00    0.00   -2.00  -16.00"
g++ mnk.cpp && ./a.out
echo ""

echo "C-spline"
echo "x=      2.0     3.0     4.0     5.0"
echo "y=       -3      -7     -10     -13"
g++ c-spline.cpp && ./a.out
echo ""