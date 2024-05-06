//
// Created by yotam on 22/06/2023.
//
#include "RecommendationSystem.h"

sp_movie RecommendationSystem::add_movie(const std::string &name, int year, const std::vector<double> &features) {
    sp_movie movie_to_add = get_movie(name, year);
    movie_to_add = std::move(std::make_shared<Movie>(name, year));
    _m_m.insert(std::make_pair(movie_to_add,features));
    return movie_to_add;
}



sp_movie RecommendationSystem::get_movie(const std::string &name, int year) const {
    sp_movie movie_to_get = nullptr;
    for (const auto &movie_feat_pair : _m_m)
    {
        if (movie_feat_pair.first->get_name() == name && movie_feat_pair.first->get_year() == year)
        {
            movie_to_get = movie_feat_pair.first;
            break;
        }
    }
    return movie_to_get;
}

double RecommendationSystem::content_helper_avg_calc (rank_map& rank_map)
{
    double avg = 0;
    double num_of_movies = 0;
    for (auto &movie : rank_map)
    {
        if(movie.second != 0)
        {
            avg += movie.second;
            num_of_movies++;
        }
    }
    return avg / num_of_movies;
}

feature_vec RecommendationSystem::content_helper_pref_calc (rank_map& rank_map, double average)
{
    feature_vec pref_vec(_m_m.begin()->second.size(), 0);
    for (auto &movie_rating_pair : rank_map)
    {
        if(movie_rating_pair.second != 0)
        {
            for (int i = 0; i < _m_m.begin()->second.size() ; ++i) // maybe wrong size
            {
                pref_vec[i] += (movie_rating_pair.second-average) * _m_m[movie_rating_pair.first][i];
            }
        }
    }
    return pref_vec;
}

sp_movie RecommendationSystem::recommend_by_content(const User &user) {
    rank_map rank_map = user.get_ranks();
    double average = content_helper_avg_calc(rank_map);
    feature_vec pref_vec = content_helper_pref_calc(rank_map, average);
    double max_rec_val = -1.0;
    sp_movie rec_movie = nullptr;
    for (const auto &movie_feat_pair : _m_m)
    {
        sp_movie movie = movie_feat_pair.first;
        auto it = rank_map.find(movie);
        if(it == rank_map.end())
        {
          double score = 0;
          for (int i = 0; i < pref_vec.size (); ++i) // maybe wrong size
          {
            score += pref_vec[i] * movie_feat_pair.second[i];
          }
          double val_to_div =  norm_calc (pref_vec) * norm_calc (movie_feat_pair.second);
          if (val_to_div != 0)
          {
            score /= val_to_div;
          }
          if (score > max_rec_val)
          {
            max_rec_val = score;
            rec_movie = movie_feat_pair.first;
          }
        }
    }
    return rec_movie;


}

std::ostream &operator<<(std::ostream &os, const RecommendationSystem &rs) {

    for (const auto &movie_feat_pair : rs._m_m) {
        os << *(movie_feat_pair.first);
    }
    return os;
}

double RecommendationSystem::norm_calc(const feature_vec &vec) {
    double norm = 0;
    for (double i : vec)
    {
        norm += i * i;
    }
    return sqrt(norm);
}

double RecommendationSystem::predict_movie_score(const User &user, const sp_movie &movie, int k) {
    std::vector<std::pair<sp_movie ,double>> sim_vec;
    for(const auto& movie_rating_pair : user.get_ranks()) {
        if(movie_rating_pair.second != 0)
        {
            sim_vec.emplace_back(movie_rating_pair.first, cf_helper_get_sim(_m_m[movie_rating_pair.first], _m_m[movie]));
        }
    }
    std::sort(sim_vec.begin(), sim_vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    double sum = 0;
    double div = 0;
    for(int i = 0; i < k; i++)
    {
        sum += sim_vec[i].second * user.get_ranks().at(sim_vec[i].first);
        div += sim_vec[i].second;
    }
    return sum / div;
}


double RecommendationSystem::cf_helper_get_sim(const feature_vec &vec1, const feature_vec &vec2) {
    if((int)vec1.size() != (int)vec2.size())
    {
        throw std::length_error("vector size is incompatible");
    }
    double deg = 0;
    for (int i = 0; i < vec1.size() ; ++i) // maybe wrong size
    {
        deg += vec1[i] * vec2[i];
    }
    double val_to_div = norm_calc(vec1) * norm_calc(vec2);
    return deg / val_to_div;
}

sp_movie RecommendationSystem::recommend_by_cf(const User &user, int k) {
  rank_map rank_map = user.get_ranks();
  std::vector<std::pair<sp_movie ,double>> pred_vec;

  double best_sim = -1.0;
  sp_movie best_movie = nullptr;

  for(auto &movie_feat_pair : _m_m)
  {
    sp_movie movie = movie_feat_pair.first;
    auto it = rank_map.find(movie);
    if(it == rank_map.end())
    {
        double cur_sim = predict_movie_score(user, movie_feat_pair.first, k);
        if(cur_sim > best_sim)
        {
            best_sim = cur_sim;
            best_movie = movie_feat_pair.first;
        }
    }
  }
    return best_movie;
}


bool equal_f(const sp_movie &lhs, const sp_movie &rhs) {
    return (*lhs < *rhs);
}


RecommendationSystem::RecommendationSystem() {
    movie_map init(equal_f);
    _m_m = init;
}


