// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

// compute_features
std::string compute_features(std::string ifile);
RcppExport SEXP _neurostrcpp_compute_features(SEXP ifileSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type ifile(ifileSEXP);
    rcpp_result_gen = Rcpp::wrap(compute_features(ifile));
    return rcpp_result_gen;
END_RCPP
}
// random_branch
double random_branch();
RcppExport SEXP _neurostrcpp_random_branch() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(random_branch());
    return rcpp_result_gen;
END_RCPP
}
// random_barycenter
double random_barycenter();
RcppExport SEXP _neurostrcpp_random_barycenter() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(random_barycenter());
    return rcpp_result_gen;
END_RCPP
}
// random_node
double random_node();
RcppExport SEXP _neurostrcpp_random_node() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(random_node());
    return rcpp_result_gen;
END_RCPP
}
// timesTwo
NumericVector timesTwo(NumericVector x);
RcppExport SEXP _neurostrcpp_timesTwo(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(timesTwo(x));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_neurostrcpp_compute_features", (DL_FUNC) &_neurostrcpp_compute_features, 1},
    {"_neurostrcpp_random_branch", (DL_FUNC) &_neurostrcpp_random_branch, 0},
    {"_neurostrcpp_random_barycenter", (DL_FUNC) &_neurostrcpp_random_barycenter, 0},
    {"_neurostrcpp_random_node", (DL_FUNC) &_neurostrcpp_random_node, 0},
    {"_neurostrcpp_timesTwo", (DL_FUNC) &_neurostrcpp_timesTwo, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_neurostrcpp(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
