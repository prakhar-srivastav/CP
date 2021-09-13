 /*
 For example :
 mask = 101101
 
 sub-masks are: 
 001101
 101001
 000001
 001100
 101000
 ... and so on 
 
 */
 
 
 for(int i = mask; i > 0; i = (i-1) & mask)
