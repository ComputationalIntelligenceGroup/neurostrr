#' JSON to dataframe.
#'
#' Adds all the measures as dataframe columns.
#' @export
json2dataframe <- function(json) {
  a <- jsonlite::fromJSON(json)
  cols <- setdiff(colnames(a), 'measures')
  a <- cbind(a[, cols], a$measures)
  # colnames(a) <-  gsub('^measures\\.', '', colnames(a))
  a
}
