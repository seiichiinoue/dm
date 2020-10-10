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
        int *_word_count;
        double *_lambda;         // 混合polya分の混合比
        double **_alpha;         // コンポーネントごとのディリクレパラメータ

        double _alpha0;
        int _num_mixture;        
        int _num_documents;
        int _vocabulary_size;
        int _sum_word_frequency;
        int _ignore_word_count;

        DM() {
            _n_k = NULL;
            _sum_n_k = NULL;
            _word_count = NULL;
            _lambda = NULL;
            _alpha = NULL;
            _alpha0 = ALPHA0;
            _num_mixture = 0;
            _vocabulary_size = 0;
            _num_documents = 0;
            _sum_word_frequency = 0;
            _ignore_word_count = 0;
        }
        ~DM() {}
        void initialize(int vocabulary_size, int num_documents, int num_mixture) {
            _num_mixture = num_mixture;
            _num_documents = num_documents;
            _vocabulary_size = vocabulary_size;
            _n_k = new int*[num_documents];
            _sum_n_k = new int[num_documents];
            // initialization stats
            for (int doc_id=0; doc_id<num_documents; ++doc_id) {
                _n_k[doc_id] = new int[vocabulary_size];
                for (id word_id=0; word_id<vocabulary_size; ++word_id) {
                    _n_k[doc_id][word_id] = 0;
                }
            }
            _word_count = new int[vocabulary_size];
            _lambda = new double[num_mixture];
            _alpha = new double*[num_mixture];
            // initialization alpha
            for (int m=0; m<num_mixture; ++m) {
                _alpha[m] = new double[vocabulary_size];
                for (id word_id=0; word_id<vocabulary_size; ++word_id) {
                    _alpha[m][word_id] = _alpha0;
                }
            }
        }
        void prepare() {
            for (id word_id=0; word_id<_vocabulary_size; ++word_id) {
                double sum_count = 0;
                for (int doc_id=0; doc_id<_num_documents; ++doc_id) {
                    int *count = _n_k[doc_id];
                    sum_count += count[word_id];
                }
                _word_count[word_id] = sum_count;
            }
            int sum_word_frequency_check = 0;
            for (int doc_id=0; doc_id<_num_documents; ++doc_id) {
                int sum = 0;
                int *count = _n_k[doc_id];
                for (id word_id=0; word_id<_vocabulary_size; ++word_id) {
                    sum += count[word_id];
                }
                _sum_n_k[doc_id] = sum;
                sum_word_frequency_check += sum;
            }
            assert(sum_word_frequency_check == _sum_word_frequency);
        }
        void add_word(id word_id, int doc_id) {
            int *count = _n_k[doc_id];
            count[word_id]++;
            _sum_word_frequency++;
        }
        
        double compute_log_likelihood(int doc_id) {
            double log_pw = 0;
            double sum_word_frequency = _sum_n_k[doc_id];
            return log_pw;
        }
    };
};