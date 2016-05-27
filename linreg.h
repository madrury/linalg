#include "vector.h"
#include "matrix.h"

struct linreg {
    int n;
    int p;
    struct vector* beta;
    struct vector* y_hat;
    double sigma_resid;
};

struct linreg* linreg_new(void);
void           linreg_free(struct linreg* lr);

struct linreg* linreg_fit(struct matrix* X, struct vector* y);
struct vector* linreg_predict(struct linreg* lr, struct matrix* X);
