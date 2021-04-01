echo "Lab №2"
echo "Trofimov M.A. M8O-308b-18"

echo "Dihotomia"
echo "0.5*x*x*x  + 6*x  + 1.25  = 0, (-1; 0)"
g++ dihotomia.cpp -fconcepts && ./a.out
echo ""

echo "Chords"
echo "0.5*x*x*x  + 5*x  + 16  = 0, (-3; -2)"
g++ chord.cpp -fconcepts && ./a.out
echo ""

echo "Newton"
echo "0.5*x*x*x  + 11*x  -24.75  = 0, (1; 2)"
g++ newton.cpp -fconcepts && ./a.out
echo ""

echo "Iterations"
echo "x*x*x  + 6*x  + 20  = 0, (-2; -1)"
g++ iterations.cpp -fconcepts && ./a.out
echo ""

echo "Linerization"
echo "x*x*x  -2* y*y*y  +  19 = 0"
echo "2* x*y -2* y -7  = 0"
echo "(2, 2) and (-2, 0)"
g++ linerization.cpp -fconcepts && ./a.out
echo ""