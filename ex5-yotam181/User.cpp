

// don't change those includes
#include "User.h"
#include "RecommendationSystem.h"


// implement your cpp code here
User::User (std::string &user_name, rank_map &ranks, rs_ptr &rs):
        _user_name(user_name), _rank_map(ranks), _rs(rs) // maybe change unique pointer to shared with "move"
{}

std::string User::get_name() const
{
    return _user_name;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
    std::map<sp_movie,double> order_map;
    for (const auto& pair : user._rank_map)
    {
        order_map[pair.first] = pair.second;
    }
    os << "name: " << user._user_name << std::endl;
    for(const auto& pair : order_map)
    {
        os << *(pair.first);
    }
    os << std::endl;
    return os;
}

rank_map User::get_ranks() const {
    return _rank_map;
}

void User::add_movie_to_rs(const std::string &name, int year, const std::vector<double> &features, double rate) {
    sp_movie movie = _rs->add_movie(name, year, features);
    _rank_map.insert({movie,rate});
}

sp_movie User::get_recommendation_by_content() const {
    return _rs->recommend_by_content(*this);
}

sp_movie User::get_recommendation_by_cf(int k) const {
    return  _rs->recommend_by_cf(*this, k);
}

double User::get_prediction_score_for_movie(const std::string &name, int year, int k) const {
    sp_movie movie = _rs->get_movie(name, year);
    return _rs->predict_movie_score(*this, movie, k);
}

