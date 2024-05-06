//
// Created on 2/20/2022.
//

#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H
#include "User.h"
#include <cmath>
#include <map>
#include <algorithm>



typedef std::vector<double> feature_vec;
typedef std::vector<std::pair<sp_movie ,double>> movie_sim_score_vec;
typedef std::map<sp_movie, feature_vec, equal_func> movie_map;




class RecommendationSystem
{

private:
    movie_map _m_m;
    double content_helper_avg_calc (rank_map& rank_map);
    feature_vec content_helper_pref_calc (rank_map& rank_map, double average);
    static double norm_calc (const feature_vec& vec);
    static double cf_helper_get_sim(const feature_vec& vec1, const feature_vec& vec2);




public:

	explicit RecommendationSystem();
    /**
     * adds a new movie to the system
     * @param name name of movie
     * @param year year it was made
     * @param features features for movie
     * @return shared pointer for movie in system
     */
	sp_movie add_movie(const std::string& name,int year,const std::vector<double>& features);


    /**
     * a function that calculates the movie with highest score based on movie features
     * @param ranks user ranking to use for algorithm
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_content(const User& user);

    /**
     * a function that calculates the movie with highest predicted score based on ranking of other movies
     * @param ranks user ranking to use for algorithm
     * @param k
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_cf(const User& user, int k);


    /**
     * Predict a user rating for a movie given argument using item cf procedure with k most similar movies.
     * @param user_rankings: ranking to use
     * @param movie: movie to predict
     * @param k:
     * @return score based on algorithm as described in pdf
     */
	double predict_movie_score(const User &user, const sp_movie &movie,
												  int k);

	/**
	 * gets a shared pointer to movie in system
	 * @param name name of movie
	 * @param year year movie was made
	 * @return shared pointer to movie in system
	 */
	sp_movie get_movie(const std::string &name, int year) const;


    friend std::ostream &operator<<(std::ostream &os, const RecommendationSystem &rs);
    friend bool equal_f(const sp_movie& lhs, const sp_movie& rhs);


};


#endif //RECOMMENDATIONSYSTEM_H
