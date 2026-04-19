/**
 * @file   sim_core.h
 * @brief  Core functions. This file will be included only in Xsim.c.
 * @author Takeshi NISHIMATSU
*/

/**
 * @brief  swap two doubles
 */
void swap_double(double *a, double *b);

/**
 * @brief  search and return the number of spheres in {x,y}_ary[]s touching with spheres at (x,y)
 * @param [in] dxd : d square
 * @param [in] x,y : coordinates
 * @param [in] n_ary : the number of spheres in {x,y}_ary[]s.
 * @param [in] x_ary[], y_ary[] : spheres
 * @param [out] x_touch[], y_touch[] : spheres touching with
 * @return the number of spheres in {x,y}_ary[]s touching with spheres at (x,y)
*/
int n_touch(double dxd, double x, double y, int n_ary,
            double x_ary[],   double y_ary[], /* input */
            double x_touch[], double y_touch[]); /* output */

/**
 * @brief go around to avoid a under ball ((-dx, -dy) direction)
 */
void go_around(double *x, double *y, double velocity, double dx, double dy, double diameter);

/**
 * @brief add a sphere at (x,y) to x_result[] and y_result[] under the periodic boundary condition
 */
void add_to_result(double x, double y, double diameter3, int *n_fixed,
                   double x_result[], double y_result[]);
