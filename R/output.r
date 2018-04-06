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

#' #' Filter measures
#' #' @export
#' filter_measures <- function(branch) {
#'   keep <-  setdiff(colnames(branch), c("neuron", "neurite", "neurite_type", "branch", "node"))
#'   branch[ , keep, drop = FALSE ]
#' }

#' Filters either axon or dendritic measures.
#' @export
filter_neurite <- function(neuron, axon = TRUE) {
  if (!all(neuron$neurite_type %in% c('Axon', 'Dendrite', 'Apical'))) stop("Unknown neurite type.")
  ind_axon <- neuron$neurite_type == 'Axon'
  if (!axon) ind_axon <- !ind_axon # XOR?
  neuron[ind_axon, , drop = FALSE]
}
#' Filter trifurcations
#' @export
filter_trifurcations <- function(neuron, keep = FALSE) {
  # stopifnot(is_branch(neuron))
  ind <- neuron$N_descs < 3
  if (keep) ind <- !ind
  neuron[ind, , drop = FALSE]
}
#' Filter branches
#' @export
filter_branches <- function(neuron) {
  neuron[!is.na(neuron[, 'length']), , drop = FALSE]
}

#' Merge branch and node features into a single data frame.
#' introduces dependency on dplyr.
#' @export
merge_branch_node <- function(b, n) {
  b$x <- NULL
  b$y <- NULL
  b$z <- NULL
  b <- dplyr::left_join(n, b,  by = c("neuron", "neurite", "neurite_type", "branch", "node"))
}
