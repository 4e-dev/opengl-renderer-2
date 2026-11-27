fixing up the file structure
* move the linear algebra header files directly into the test folder



test_linear_algebra file

things i want to refactor
1. the need for explicit instantiation (but it may be necessary)
2. functions that run the tests can be better written imo

testing:
1. vector tests
    1. default constructor
    2. array constructor
    3. component accessor
    4. equality
    5. inequality
    6. addition
    7. subtraction
    8. scalar multiplication
    9. scalar division
    10. component multiply [remove]
    11. component divide [remove]
    12. dot product
    13. distance (length)
    14. linear interp
    15. normalization [add]
    16. cross product [add]

2. matrix tests
    1. default constructor
    2. initializer list constructor
    3. equality
    4. inequality
    5. addition [remove]
    6. subtraction [remove]
    7. scalar multiplication [remove]
    8. scalar division [remove]
    9. matrix-vector multiplication
    10. vector-matrix multiplication
    11. component multiplication [remove]
    12. component division [remove]
    13. dot product [remove]
    14. distance (length) [remove]
    15. linear interpolation [remove]
    16. component accessor [add]

2.5. matrix-matrix multiplication
    1. rectangular multiplication
    2. identity matrix
    3. zero matrix
    4. negative values
    5. 1x1 matrix [remove]
    6. associativity

things to eventually consider
* transpose
* matrix inverse
* perspective projection
* orthographic projection
* lookat
* translation / rotation / scaling
