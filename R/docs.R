#' @useDynLib neurostr
#' @importFrom Rcpp sourceCpp
NULL

.onUnload <- function (libpath) {
  library.dynam.unload("neurostr", libpath)
}
