/* PostScript.h */
void PostScript_generate( struct GrowthParameters *params, int n_fixed, double *x, double *y);
void PostScript_header();
void PostScript_show_xtal(struct GrowthParameters *params, int n_ball,  double *x, double *y);
