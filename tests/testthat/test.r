context("general")

test_that("Convert nominal", {
    file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
    json <- convert(file, ext = "json")
    # Currently not working because I have not adapted json2dataframe to handle the output of convert
    branch <- json2dataframe(json)
    swc <- convert(file, ext = "swc")
})

test_that("Compute branch features nominal", {
  file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
  json_branch <- compute_branch_features(file)
  branch <- json2dataframe(json_branch)
  expect_true('partition_asymmetry' %in% colnames(branch))
})

test_that("Compute node features nominal", {
  file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
  json_node <- compute_node_features(file)
  node <- json2dataframe(json_node)
  expect_true('node_order' %in% colnames(node))
})

test_that("Validator nominal", {
  file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
  validate <- validate(file)
  expect_true(nchar(validate) > 0)

  validate <- json2dataframe(validate)
  expect_equal(ncol(validate), 4)
})
