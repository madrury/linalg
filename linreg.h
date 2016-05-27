#include "vector.h"
#include "matrix.h"

struct linreg {
    int n;
    int p;
    struct vector* beta;
    struct vector* y_hat;
    double sigma_resid;
};

struct linreg* new_linreg(void);

struct linreg* fit_linreg(struct matrix* X, struct vector* y);
struct vector* predict_linreg(struct linreg* lnreg, struct matrix* X);
