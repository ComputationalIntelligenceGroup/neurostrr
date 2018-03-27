// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

// compute_branch_features
std::string compute_branch_features(std::string ifile, bool omitapical, bool omitaxon, bool omitdend, bool correct, std::string selection);
RcppExport SEXP _neurostrcpp_compute_branch_features(SEXP ifileSEXP, SEXP omitapicalSEXP, SEXP omitaxonSEXP, SEXP omitdendSEXP, SEXP correctSEXP, SEXP selectionSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type ifile(ifileSEXP);
    Rcpp::traits::input_parameter< bool >::type omitapical(omitapicalSEXP);
    Rcpp::traits::input_parameter< bool >::type omitaxon(omitaxonSEXP);
    Rcpp::traits::input_parameter< bool >::type omitdend(omitdendSEXP);
    Rcpp::traits::input_parameter< bool >::type correct(correctSEXP);
    Rcpp::traits::input_parameter< std::string >::type selection(selectionSEXP);
    rcpp_result_gen = Rcpp::wrap(compute_branch_features(ifile, omitapical, omitaxon, omitdend, correct, selection));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_neurostrcpp_compute_branch_features", (DL_FUNC) &_neurostrcpp_compute_branch_features, 6},
    {NULL, NULL, 0}
};

RcppExport void R_init_neurostrcpp(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
