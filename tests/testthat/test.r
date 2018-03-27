context("general")

test_that("Convert nominal", {
    file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
    file2 <- '/tmp/neurostr-test-convert.json'
    convert(file, file2, ext = "json")
    expect_true(file.exists(file2))
    file.remove(file2)
    convert(file, file2, ext = "swc")
    expect_true(file.exists(file2))
})

test_that("Compute branch features nominal", {
  file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
  json_branch <- compute_branch_features(file)
  branch <- json2dataframe(json_branch)
  expect_true('partition_asymmetry' %in% colnames(branch))
})

test_that("Validator nominal", {
  file <- system.file("extdata", "C030397A-P2.swc", package = "neurostr")
  validate <- validate(file)
  expect_true(nchar(validate) > 0)

  validate <- json2dataframe(validate)
  expect_equal(ncol(validate), 4)
})
