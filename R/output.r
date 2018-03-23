#' JSON to dataframe.
#'
#' For feature extraction, adds all the measures as dataframe columns.
#' For validation, it omits any detailed results.
#' @export
json2dataframe <- function(json) {
  a <- jsonlite::fromJSON(json)
  if ('measures' %in% colnames(a)) {
    cols <- setdiff(colnames(a), 'measures')
    a <- cbind(a[, cols], a$measures)
  }
  else {
    a$results <- NULL
  }
  stopifnot(!any(sapply(a, is.list)))
  a
}
