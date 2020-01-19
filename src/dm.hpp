#pragma once
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <unordered_set>
#include <cassert>
#include <cmath>
#include <random>
#include <fstream>
#include "common.hpp"
using namespace std;

namespace dm {
    class DM {
    public:
        // model parameters
        int **_n_k;             // 文書ごとの単語の出現頻度
        int *_sum_n_k;          // 文書ごとの単語の出現頻度の総和
        double *_lambda;         // 混合polya分の混合比
        double **_alpha;         // コンポーネントごとのディリクレパラメータ
        
        int _num_documents;
        int _vocabulary_size;
        int _sum_word_frequency;
        int _ignore_word_count;

        DM() {
            _n_k = NULL;
            _sum_n_k = NULL;
            _lambda = NULL;
            _alpha = NULL;
        }
        ~DM() {}
        void initialize() {
        }
        void add_word(id word_id, int doc_id) {
        }
    };
};