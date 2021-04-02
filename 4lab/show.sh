echo "Lab №4"
echo "Trofimov M.A. M8O-308b-18"
echo ""

echo "f(x)= (  -2*x +  1 )/( x*x +  9); [-4, 0]"

echo "Trapeze; h = 1.0 0.5 0.25"
g++ trapeze.cpp -fconcepts && ./a.out
echo ""

echo "Simpson; h = 1.0 0.5"
g++ simpson.cpp -fconcepts && ./a.out
echo ""

