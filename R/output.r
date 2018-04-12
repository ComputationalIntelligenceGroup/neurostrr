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
is_2D <- function(x) {
  length(dim(x)) == 2
}
#' Filter measures
#' @export
filter_id <- function(branch, keep = FALSE) {
  if (!is_2D(branch)) return (branch)
  keep_columns <- c("neuron", "neurite", "neurite_type", "branch", "node")
  if (!keep) {
    keep_columns <-  setdiff(colnames(branch), keep_columns)
  }
  branch[ , keep_columns, drop = FALSE ]
}

#' Filters either axon or dendritic measures.
#' @export
filter_neurite <- function(neuron, axon = TRUE) {
  if (!is_2D(neuron)) return (neuron)
  if (!all(neuron$neurite_type %in% c('Axon', 'Dendrite', 'Apical'))) stop("Unknown neurite type.")
  ind_axon <- neuron$neurite_type == 'Axon'
  if (!axon) ind_axon <- !ind_axon # XOR?
  neuron[ind_axon, , drop = FALSE]
}
#' Filter trifurcations
#' @export
filter_trifurcations <- function(neuron, keep = FALSE) {
  if (!is_2D(neuron)) return (neuron)
  # stopifnot(is_branch(neuron))
  ind <- neuron$N_descs < 3
  if (keep) ind <- !ind
  neuron[ind, , drop = FALSE]
}
#' Filter branches
#' @export
filter_branches <- function(neuron) {
  if (!is_2D(neuron)) return (neuron)
  neuron[!is.na(neuron[, 'length']), , drop = FALSE]
}

#' Merge branch and node features into a single data frame.
#' introduces dependency on dplyr.
#' @export
merge_branch_node <- function(b, n) {
  columns <- c("neuron", "neurite", "neurite_type", "branch", "node")
  if (!is.data.frame(b) || !is.data.frame(n)) {
    # if they are not data frame but not empty then there is an error in the code
    stopifnot(length(b) == 0 || length(n) == 0)
    # else, just return an empty data frame with following columns
    df <- data.frame(t(rep(NA, length(columns))))
    colnames(df) <- columns
    df <- df[FALSE, ]
    return(df)
  }
  b$x <- NULL
  b$y <- NULL
  b$z <- NULL
  dplyr::left_join(n, b,  by = columns)
}
