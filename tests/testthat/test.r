context("general")

test_that("Convert nominal", {
    file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
    json <- convert(file, ext = "json")
    # json2dataframe does not handle the output of convert
    # branch <- json2dataframe(json)
    expect_true(is.character(json))
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

test_that("filter axon", {
 file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
 json_branch <- compute_branch_features(file)
 branch <- json2dataframe(json_branch)
 expect_equal(dim(branch), c(304, 33))
 branch <- filter_neurite(branch)
 expect_equal(dim(branch), c(35, 33))
})


test_that("parse radius correctly", {
 file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
 json_branch <- compute_node_features(file)
 branch <- json2dataframe(json_branch)
 expect_equal(branch$diameter[1], .899999 * 2, tolerance = 1e-5)
})
