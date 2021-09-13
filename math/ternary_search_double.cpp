/*
This is for minimum convex function.
Take care of using setprecision(x) in the output
Take care of range of epsilon 
*/

double ternary_search(double l, double r)
{
    double e = 0.000000000001;
    while (r - l > e)
    {

        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;
        double f1 = f(m1);
        double f2 = f(m2);
        if (f1 < f2)
        {
            r = m2;
        }
        else if (f1 > f2)
        {
            l = m1;
        }
        else
        {
            l = m1, r = m2;
        }
    }
    
    return f(l);
}
