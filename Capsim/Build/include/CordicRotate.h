


#if      !defined(_CordicRotate_H)
#define  _CordicRotate_H

#ifndef _CordicArctan_H

typedef signed short INT16S;
typedef signed int   INT32S;

#endif



#define  NUMBER_ITER      14   /* Number of iterations */
#define  PI_2          65536   /* PI/2                 */
#define  PI_1         131072   /* PI                   */
#define  ROUND_MASK        8   /* Rounding mask        */


void CordicRotate(INT32S *x_P,
                  INT32S *y_P,
                  INT32S thetha); 		

#endif
