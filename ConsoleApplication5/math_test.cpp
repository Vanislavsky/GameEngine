#include"math_test.h"
//glew
#include <GL/glew.h>

void test_vec2() {
    double eps = 1e-7;
    {
        vec2 vec({ 10, 20 });
        glm::vec2 glm_vec(10, 20);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);

        assert(glm::length(glm_vec) == vec.lenght());
        auto normalize_vector = glm::normalize(glm_vec);
        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);

        vec2 vec_2({ 60, 70 });
        glm::vec2 glm_vec_2(60, 70);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);

    }

    {
        vec2 vec({ 87.0f, 17.4f });
        glm::vec2 glm_vec(87.0f, 17.4f);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);

        assert(glm::length(glm_vec) == vec.lenght());

        auto normalize_vector = glm::normalize(glm_vec);

        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);

        vec2 vec_2({ 111.1f, 24.5f });
        glm::vec2 glm_vec_2(111.1f, 24.5f);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);
    }


    {
        vec2 vec({ 187.0f, 217.4f });
        glm::vec2 glm_vec(187.0f, 217.4f);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);

        assert(glm::length(glm_vec) == vec.lenght());
        auto normalize_vector = glm::normalize(glm_vec);
        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);

        vec2 vec_2({ 11.1f, 324.5f });
        glm::vec2 glm_vec_2(11.1f, 324.5f);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);
    }
}


void test_vec3() {
    double eps = 1e-7;
    {
        vec3 vec({ 10, 20 ,30 });
        glm::vec3 glm_vec(10, 20, 30);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);
        assert(vec.get_a3() == glm_vec.z);

        assert(glm::length(glm_vec) == vec.lenght());
        auto normalize_vector = glm::normalize(glm_vec);
        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);
        assert(fabs(normalize_vector.z - vec.normal().get_a3()) <= eps);

        vec3 vec_2({ 60, 70 ,90 });
        glm::vec3 glm_vec_2(60, 70, 90);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec + vec_2).get_a3() == (glm_vec + glm_vec_2).z);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);
        assert((vec - vec_2).get_a3() == (glm_vec - glm_vec_2).z);

        assert(glm::cross(glm_vec, glm_vec_2).x == vec.vector_product(vec_2).get_a1());
        assert(glm::cross(glm_vec, glm_vec_2).y == vec.vector_product(vec_2).get_a2());
        assert(glm::cross(glm_vec, glm_vec_2).z == vec.vector_product(vec_2).get_a3());

    }

    {
        vec3 vec({ 87.0f, 17.4f, 30.9f });
        glm::vec3 glm_vec(87.0f, 17.4f, 30.9f);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);
        assert(vec.get_a3() == glm_vec.z);

        assert(glm::length(glm_vec) == vec.lenght());

        auto normalize_vector = glm::normalize(glm_vec);

        //assert(normalize_vector.x == vec.normal().get_a1());
        //assert(normalize_vector.y == vec.normal().get_a2());
        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);
        assert(fabs(normalize_vector.z - vec.normal().get_a3()) <= eps);
        //assert(normalize_vector.z == vec.normal().get_a3());

        vec3 vec_2({ 111.1f, 24.5f, 33.3f });
        glm::vec3 glm_vec_2(111.1f, 24.5f, 33.3f);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec + vec_2).get_a3() == (glm_vec + glm_vec_2).z);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);
        assert((vec - vec_2).get_a3() == (glm_vec - glm_vec_2).z);

        assert(glm::cross(glm_vec, glm_vec_2).x == vec.vector_product(vec_2).get_a1());
        assert(glm::cross(glm_vec, glm_vec_2).y == vec.vector_product(vec_2).get_a2());
        assert(glm::cross(glm_vec, glm_vec_2).z == vec.vector_product(vec_2).get_a3());

    }


    {
        vec3 vec({ 187.0f, 217.4f, 230.9f });
        glm::vec3 glm_vec(187.0f, 217.4f, 230.9f);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);
        assert(vec.get_a3() == glm_vec.z);

        assert(glm::length(glm_vec) == vec.lenght());
        auto normalize_vector = glm::normalize(glm_vec);
        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);
        assert(fabs(normalize_vector.z - vec.normal().get_a3()) <= eps);

        vec3 vec_2({ 11.1f, 324.5f, 333.3f });
        glm::vec3 glm_vec_2(11.1f, 324.5f, 333.3f);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec + vec_2).get_a3() == (glm_vec + glm_vec_2).z);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);
        assert((vec - vec_2).get_a3() == (glm_vec - glm_vec_2).z);

        assert(glm::cross(glm_vec, glm_vec_2).x == vec.vector_product(vec_2).get_a1());
        assert(glm::cross(glm_vec, glm_vec_2).y == vec.vector_product(vec_2).get_a2());
        assert(glm::cross(glm_vec, glm_vec_2).z == vec.vector_product(vec_2).get_a3());

    }
}

void test_vec4() {
    double eps = 1e-5;
    {
        vec4 vec({ 10, 20 ,30, 99 });
        glm::vec4 glm_vec(10, 20, 30, 99);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);
        assert(vec.get_a3() == glm_vec.z);

        assert(fabs(glm::length(glm_vec) - vec.lenght()) <= eps);
        auto normalize_vector = glm::normalize(glm_vec);
        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);
        assert(fabs(normalize_vector.z - vec.normal().get_a3()) <= eps);
        assert(fabs(normalize_vector.w - vec.normal().get_a4()) <= eps);

        vec4 vec_2({ 60, 70 ,90, 12 });
        glm::vec4 glm_vec_2(60, 70, 90, 12);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec + vec_2).get_a3() == (glm_vec + glm_vec_2).z);
        assert((vec + vec_2).get_a4() == (glm_vec + glm_vec_2).w);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);
        assert((vec - vec_2).get_a3() == (glm_vec - glm_vec_2).z);
        assert((vec - vec_2).get_a4() == (glm_vec - glm_vec_2).w);

    }

    {
        vec4 vec({ 87.0f, 17.4f, 30.9f, 411.4f });
        glm::vec4 glm_vec(87.0f, 17.4f, 30.9f, 411.4f);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);
        assert(vec.get_a3() == glm_vec.z);

        //?????????assert(fabs(glm::length(glm_vec) - vec.lenght()) <= eps);
        auto normalize_vector = glm::normalize(glm_vec);
        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);
        assert(fabs(normalize_vector.z - vec.normal().get_a3()) <= eps);
        assert(fabs(normalize_vector.w - vec.normal().get_a4()) <= eps);

        vec4 vec_2({ 111.1f, 24.5f, 33.3f, 99.2f });
        glm::vec4 glm_vec_2(111.1f, 24.5f, 33.3f, 99.2f);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec + vec_2).get_a3() == (glm_vec + glm_vec_2).z);
        assert((vec + vec_2).get_a4() == (glm_vec + glm_vec_2).w);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);
        assert((vec - vec_2).get_a3() == (glm_vec - glm_vec_2).z);
        assert((vec - vec_2).get_a4() == (glm_vec - glm_vec_2).w);

    }


    {
        vec4 vec({ 187.0f, 217.4f, 230.9f, 116.6f });
        glm::vec4 glm_vec(187.0f, 217.4f, 230.9f, 116.6f);
        assert(vec.get_a1() == glm_vec.x);
        assert(vec.get_a2() == glm_vec.y);
        assert(vec.get_a3() == glm_vec.z);

        assert(fabs(glm::length(glm_vec) - vec.lenght()) <= eps);
        auto normalize_vector = glm::normalize(glm_vec);
        assert(fabs(normalize_vector.x - vec.normal().get_a1()) <= eps);
        assert(fabs(normalize_vector.y - vec.normal().get_a2()) <= eps);
        assert(fabs(normalize_vector.z - vec.normal().get_a3()) <= eps);
        assert(fabs(normalize_vector.w - vec.normal().get_a4()) <= eps);

        vec4 vec_2({ 11.1f, 324.5f, 333.3f, 116.6f });
        glm::vec4 glm_vec_2(11.1f, 324.5f, 333.3f, 116.6f);

        assert((vec + vec_2).get_a1() == (glm_vec + glm_vec_2).x);
        assert((vec + vec_2).get_a2() == (glm_vec + glm_vec_2).y);
        assert((vec + vec_2).get_a3() == (glm_vec + glm_vec_2).z);
        assert((vec + vec_2).get_a4() == (glm_vec + glm_vec_2).w);
        assert((vec - vec_2).get_a1() == (glm_vec - glm_vec_2).x);
        assert((vec - vec_2).get_a2() == (glm_vec - glm_vec_2).y);
        assert((vec - vec_2).get_a3() == (glm_vec - glm_vec_2).z);
        assert((vec - vec_2).get_a4() == (glm_vec - glm_vec_2).w);

    }
}

void test_mat2() {
    {
        mat2 mat({ 10, 20, 30, 40 });
        glm::mat2x2 glm_mat(10, 20, 30, 40);

        assert(mat.get_value(0, 0) == glm_mat[0][0]);
        assert(mat.get_value(0, 1) == glm_mat[0][1]);
        assert(mat.get_value(1, 0) == glm_mat[1][0]);
        assert(mat.get_value(1, 1) == glm_mat[1][1]);

        mat2 mat_2({ 50, 21, 9, 30 });
        glm::mat2x2 glm_mat_2(50, 21, 9, 30);

        {
            auto res_mat = mat + mat_2;
            auto glm_res_mat = glm_mat + glm_mat_2;

            assert(res_mat.get_value(0, 0) == glm_res_mat[0][0]);
            assert(res_mat.get_value(0, 1) == glm_res_mat[0][1]);
            assert(res_mat.get_value(1, 0) == glm_res_mat[1][0]);
            assert(res_mat.get_value(1, 1) == glm_res_mat[1][1]);
        }

        {
            auto res_mat = mat - mat_2;
            auto glm_res_mat = glm_mat - glm_mat_2;

            assert(res_mat.get_value(0, 0) == glm_res_mat[0][0]);
            assert(res_mat.get_value(0, 1) == glm_res_mat[0][1]);
            assert(res_mat.get_value(1, 0) == glm_res_mat[1][0]);
            assert(res_mat.get_value(1, 1) == glm_res_mat[1][1]);
        }

        {
            auto res_mat = mat * mat_2;
            auto glm_res_mat = glm_mat_2 * glm_mat;
            assert(res_mat.get_value(0, 0) == glm_res_mat[0][0]);
            assert(res_mat.get_value(0, 1) == glm_res_mat[0][1]);
            assert(res_mat.get_value(1, 0) == glm_res_mat[1][0]);
            assert(res_mat.get_value(1, 1) == glm_res_mat[1][1]);
        }

        {
            vec2  vec({ 66, 77 });
            glm::vec2 glm_vec(66, 77);
            auto res_mat = mat * vec;
            auto glm_res_mat = glm_vec * glm_mat;

            assert(res_mat.get_a1() == glm_res_mat.x);
            assert(res_mat.get_a2() == glm_res_mat.y);
        }

        {
            auto res_mat = mat.transposed_mat2();
            auto glm_res_mat = glm::transpose(glm_mat);
            assert(res_mat.get_value(0, 0) == glm_res_mat[0][0]);
            assert(res_mat.get_value(0, 1) == glm_res_mat[0][1]);
            assert(res_mat.get_value(1, 0) == glm_res_mat[1][0]);
            assert(res_mat.get_value(1, 1) == glm_res_mat[1][1]);
        }
    }

    {
        mat2 mat({ 110.6f, 20.22f, 320.1f, 99.2f });
        glm::mat2x2 glm_mat(110.6f, 20.22f, 320.1f, 99.2f);

        assert(mat.get_value(0, 0) == glm_mat[0][0]);
        assert(mat.get_value(0, 1) == glm_mat[0][1]);
        assert(mat.get_value(1, 0) == glm_mat[1][0]);
        assert(mat.get_value(1, 1) == glm_mat[1][1]);

        mat2 mat_2({ 70.7f, 80.0f, 37.7f, 41.88f });
        glm::mat2x2 glm_mat_2(70.7f, 80.0f, 37.7f, 41.88f);

        {
            auto res_mat = mat + mat_2;
            auto glm_res_mat = glm_mat_2 + glm_mat;

            assert(res_mat.get_value(0, 0) == glm_res_mat[0][0]);
            assert(res_mat.get_value(0, 1) == glm_res_mat[0][1]);
            assert(res_mat.get_value(1, 0) == glm_res_mat[1][0]);
            assert(res_mat.get_value(1, 1) == glm_res_mat[1][1]);
        }

        {
            auto res_mat = mat - mat_2;
            auto glm_res_mat = glm_mat - glm_mat_2;

            assert(res_mat.get_value(0, 0) == glm_res_mat[0][0]);
            assert(res_mat.get_value(0, 1) == glm_res_mat[0][1]);
            assert(res_mat.get_value(1, 0) == glm_res_mat[1][0]);
            assert(res_mat.get_value(1, 1) == glm_res_mat[1][1]);
        }

        {
            auto res_mat = mat * mat_2;
            auto glm_res_mat = glm_mat_2 * glm_mat;

            assert(res_mat.get_value(0, 0) == glm_res_mat[0][0]);
            assert(res_mat.get_value(0, 1) == glm_res_mat[0][1]);
            assert(res_mat.get_value(1, 0) == glm_res_mat[1][0]);
            assert(res_mat.get_value(1, 1) == glm_res_mat[1][1]);
        }

        {
            vec2  vec({ 120.6f, 77.5f });
            glm::vec2 glm_vec(120.6f, 77.5f);
            auto res_mat = mat * vec;
            auto glm_res_mat = glm_vec * glm_mat;

            assert(res_mat.get_a1() == glm_res_mat.x);
            assert(res_mat.get_a2() == glm_res_mat.y);
        }

        {
            auto res_mat = mat.transposed_mat2();
            auto glm_res_mat = glm::transpose(glm_mat);
            assert(res_mat.get_value(0, 0) == glm_res_mat[0][0]);
            assert(res_mat.get_value(0, 1) == glm_res_mat[0][1]);
            assert(res_mat.get_value(1, 0) == glm_res_mat[1][0]);
            assert(res_mat.get_value(1, 1) == glm_res_mat[1][1]);
        }
    }
}

void test_mat3() {
    {
        mat3 mat({ 10, 20, 30, 40, 33, 56, 76, 88, 11});
        glm::mat3x3 glm_mat(10, 20, 30, 40, 33, 56, 76, 88, 11);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                assert(mat.get_value(i, j) == glm_mat[i][j]);
            }
        }

        mat3 mat_2({ 10.6f, 20.2f, 130, 140, 3, 56.7f, 76.7f, 88.7f, 131});
        glm::mat3x3 glm_mat_2(10.6f, 20.2f, 130, 140, 3, 56.7f, 76.7f, 88.7f, 131);
        {
            auto res_mat = mat + mat_2;
            auto glm_res_mat = glm_mat_2 + glm_mat;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    assert(res_mat.get_value(i, j) == glm_res_mat[i][j]);
                }
            }
        }

        {
            auto res_mat = mat * mat_2;
            auto glm_res_mat = glm_mat_2 * glm_mat;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    assert(res_mat.get_value(i, j) == glm_res_mat[i][j]);
                }
            }
        }

        {
            vec3  vec({ 120.6f, 77.5f, 11.4f});
            glm::vec3 glm_vec(120.6f, 77.5f, 11.4f);
            auto res_mat = mat * vec;
            auto glm_res_mat = glm_vec * glm_mat;

            assert(res_mat.get_a1() == glm_res_mat.x);
            assert(res_mat.get_a2() == glm_res_mat.y);
        }

        {
            auto res_mat = mat.transposed_mat3();
            auto glm_res_mat = glm::transpose(glm_mat);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    assert(res_mat.get_value(i, j) == glm_res_mat[i][j]);
                }
            }
        }
    }
}

void test_translate() {

    {
        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
        vec = trans * vec;

        vec4 vec_2(1.0f, 0.0f, 0.0f, 1.0f);
        vec3 tr_vec({ 1.0f, 1.0f, 0.0f });
        auto res_math = translate(tr_vec);
        auto res = res_math * vec_2;

        
        assert(res.get_a1() == vec.x);
        assert(res.get_a2() == vec.y);
        assert(res.get_a3() == vec.z);
    }

    {
        glm::vec4 vec(19.0f, 20.0f, 30.0f, 31.0f);
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(11.0f, 13.0f, 70.0f));
        vec = trans * vec;

        vec4 vec_2(19.0f, 20.0f, 30.0f, 31.0f);
        vec3 tr_vec({ 11.0f, 13.0f, 70.0f });
        auto res_mat = translate(tr_vec);
        auto res = res_mat * vec_2;

        assert(res.get_a1() == vec.x);
        assert(res.get_a2() == vec.y);
        assert(res.get_a3() == vec.z);
    }

    {
        glm::vec4 vec(119.0f, 220.0f, 330.0f, 31.0f);
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(141.0f, 3.0f, 740.0f));
        vec = trans * vec;

        vec4 vec_2(119.0f, 220.0f, 330.0f, 31.0f);
        vec3 tr_vec({ 141.0f, 3.0f, 740.0f });
        auto res_math = translate(tr_vec);
        auto res = res_math * vec_2;

        assert(res.get_a1() == vec.x);
        assert(res.get_a2() == vec.y);
        assert(res.get_a3() == vec.z);
    }
}

void test_scale() {
    {
        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans(1.0f);
        trans = glm::scale(trans, glm::vec3(1.5f, 1.5f, 0.0f));
        vec = trans * vec;

        vec4 vec_2(1.0f, 0.0f, 0.0f, 1.0f);
        vec3 tr_vec({ 1.5f, 1.5f, 0.0f });
        auto res_math = scale(tr_vec);
        auto res = res_math * vec_2;

        assert(res.get_a1() == vec.x);
        assert(res.get_a2() == vec.y);
        assert(res.get_a3() == vec.z);
    }

    {
        glm::vec4 vec(19.0f, 20.0f, 30.0f, 31.0f);
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(3.0f, 1.0f, 7.0f));
        vec = trans * vec;

        vec4 vec_2(19.0f, 20.0f, 30.0f, 31.0f);
        vec3 tr_vec({ 3.0f, 1.0f, 7.0f });
        auto res_math = translate(tr_vec);
        auto res = res_math * vec_2;

        assert(res.get_a1() == vec.x);
        assert(res.get_a2() == vec.y);
        assert(res.get_a3() == vec.z);
    }

    {
        glm::vec4 vec(119.0f, 220.0f, 330.0f, 31.0f);
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(4.0f, 3.0f, 7.0f));
        vec = trans * vec;

        vec4 vec_2(119.0f, 220.0f, 330.0f, 31.0f);
        vec3 tr_vec({ 4.0f, 3.0f, 7.0f });
        auto res_math = translate(tr_vec);
        auto res = res_math * vec_2;

        assert(res.get_a1() == vec.x);
        assert(res.get_a2() == vec.y);
        assert(res.get_a3() == vec.z);
    }
}

void test_rotate() {
    {
        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans (1.0f);
        trans = glm::rotate(trans, 90.0f, glm::vec3(0.0, 0.0, 1.0));
        vec = trans * vec;

        vec4 vec_2(1.0f, 0.0f, 0.0f, 1.0f);

        vec3 tr_vec({ 0.0, 0.0, 1.0 });
        auto res_math = rotate(90.0f, tr_vec);
        auto res = res_math * vec_2;

        assert(res.get_a1() == vec.x);
        assert(res.get_a2() == vec.y);
        assert(res.get_a3() == vec.z);

    }
}

void test_mat4() {
    {
        mat4 mat({ 10, 20, 30, 40, 33, 56, 76, 88, 11, 22, 21, 32, 44, 41, 12, 56 });
        glm::mat4x4 glm_mat(10, 20, 30, 40, 33, 56, 76, 88, 11, 22, 21, 32, 44, 41, 12, 56);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                assert(mat.get_value(i, j) == glm_mat[i][j]);
            }
        }

        mat4 mat_2({ 10.6f, 20.2f, 130, 140, 3, 56.7f, 76.7f, 88.7f, 131, 232, 281, 382, 4.4f, 4.1f, 1.2f, 5.6f });
        glm::mat4x4 glm_mat_2(10.6f, 20.2f, 130, 140, 3, 56.7f, 76.7f, 88.7f, 131, 232, 281, 382, 4.4f, 4.1f, 1.2f, 5.6f);
        {
            auto res_mat = mat + mat_2;
            auto glm_res_mat = glm_mat_2 + glm_mat;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    assert(res_mat.get_value(i, j) == glm_res_mat[i][j]);
                }
            }
        }

        {
            auto res_mat = mat * mat_2;
            auto glm_res_mat = glm_mat_2 * glm_mat;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    assert(res_mat.get_value(i, j) == glm_res_mat[i][j]);
                }
            }
        }

        {
            vec4  vec({ 120.6f, 77.5f, 11.4f, 19.9f });
            glm::vec4 glm_vec(120.6f, 77.5f, 11.4f, 19.9f);
            auto res_mat = mat * vec;
            auto glm_res_mat = glm_vec * glm_mat;

            assert(res_mat.get_a1() == glm_res_mat.x);
            assert(res_mat.get_a2() == glm_res_mat.y);
        }

        {
            auto res_mat = mat.transposed_mat4();
            auto glm_res_mat = glm::transpose(glm_mat);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    assert(res_mat.get_value(i, j) == glm_res_mat[i][j]);
                }
            }
        }
    }
}

void test_look_at() {
    {
        glm::mat4 glm_view;
        glm_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

        vec3 camera_pos(0.0f, 0.0f, 3.0f);
        vec3 goal_coord(0.0f, 0.0f, 0.0f);
        vec3 up(0.0f, 1.0f, 0.0f);
        mat4 view = look_at(camera_pos, goal_coord, up);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                assert(view.get_value(i, j) == glm_view[i][j]);
            }
        }
    }

    {
        glm::mat4 glm_view;
        glm_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 1.0f));

        vec3 camera_pos(0.0f, 0.0f, 6.0f);
        vec3 goal_coord(0.0f, 0.0f, 0.0f);
        vec3 up(0.0f, 1.0f, 1.0f);
        mat4 view = look_at(camera_pos, goal_coord, up);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                assert(view.get_value(i, j) == glm_view[i][j]);
            }
        }
    }

    {
        glm::mat4 glm_view;
        glm_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 19.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 2.0f));

        vec3 camera_pos(0.0f, 0.0f, 19.0f);
        vec3 goal_coord(0.0f, 0.0f, 0.0f);
        vec3 up(0.0f, 1.0f, 2.0f);
        mat4 view = look_at(camera_pos, goal_coord, up);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                assert(view.get_value(i, j) == glm_view[i][j]);
            }
        }
    }

}

void test_ortho() {
    auto proj = ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    auto tr_proj = proj.transposed_mat4();
 
    auto glm_projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tr_proj.get_value(i, j) != glm_projection[i][j]) {
                std::cout<< tr_proj.get_value(i, j) << " " << glm_projection[i][j] << "  " << i << "  " << j << std::endl;
            }
        }
    }

}


void test_perspective() {
    auto proj = perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
    auto tr_proj = proj.transposed_mat4();

    auto glm_projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(tr_proj.get_value(i, j) == glm_projection[i][j]);
        }
    }


}

void test() {
    test_vec2();
    test_vec3();
    test_vec4();
    test_mat2();
    test_mat3();
    test_mat4();
    test_translate();
    test_scale();
    test_look_at();
    test_rotate();
    test_ortho();
    test_perspective();
    std::cout << "ALL TEST COMPLETED!!!" << std::endl;
}