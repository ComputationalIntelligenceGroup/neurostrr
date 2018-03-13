#' @useDynLib neurostrcpp
#' @importFrom Rcpp sourceCpp
NULL

.onUnload <- function (libpath) {
  library.dynam.unload("neurostrcpp", libpath)
}
