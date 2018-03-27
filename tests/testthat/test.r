context("general")

test_that("Convert nominal", {
    file <- '/home/bmihaljevic/code/bbp-data/data/BBP_SWC/C030502A.swc'
    file2 <- '/tmp/neurostr-test-convert.json'
    neurostrcpp::convert(file, file2, ext = "json")
    expect_true(file.exists(file2))
    file.remove(file2)
    neurostrcpp::convert(file, file2, ext = "swc")
    expect_true(file.exists(file2))
})

test_that("Compute branch features nominal", {
  file <- '/home/bmihaljevic/code/bbp-data/data/BBP_SWC/C030502A.swc'
  json_branch <- neurostrcpp::compute_branch_features(file)
  branch <- json2dataframe(json_branch)
  expect_true('partition_asymmetry' %in% colnames(branch))
})

test_that("Validator nominal", {
  file <- '/home/bmihaljevic/code/bbp-data/data/BBP_SWC/C030502A.swc'
  validate <- neurostrcpp::validate(file)
  expect_true(nchar(validate) > 0)

  validate <- json2dataframe(validate)
  expect_equal(ncol(validate), 4)
})
