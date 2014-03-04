/* GrowthParameters.h */
#define DEFAULT_DIAMETER 0.0499999999999
#define DEFAULT_HEIGHT   1.2
#define DEFAULT_VELOCITY 0.0008
struct GrowthParameters
{
  double  diameter;
  double  height;
  int     criterion;
  int     n_ball;
  double  velocity;
  char   *guest;
};
