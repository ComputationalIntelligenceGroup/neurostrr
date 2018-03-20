context("general")

test_that("Convert nominal", {
    file <- '/home/bmihaljevic/code/bbp-data/data/BBP_SWC/C030502A.swc'
    file2 <- '/home/bmihaljevic/test-convert.json'
    file.remove(file2)
    neurostrcpp::convert(file, file2)
    expect_true(file.exists(file2))
})

test_that("Compute branch features nominal", {
  file <- '/home/bmihaljevic/code/bbp-data/data/BBP_SWC/C030502A.swc'
  json_branch <- neurostrcpp::compute_branch_features(file)
  branch <- json2dataframe(json_branch)
  expect_true('partition_asymmetry' %in% colnames(branch))
})
