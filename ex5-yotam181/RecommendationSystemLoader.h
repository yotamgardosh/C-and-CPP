
#ifndef RECOMMENDATIONSYSTEMLOADER_H
#define RECOMMENDATIONSYSTEMLOADER_H
#include "RecommendationSystem.h"

class RecommendationSystemLoader {

 private:

 public:
  RecommendationSystemLoader () = delete;
  /**
   * loads movies by the given format for movies with their feature's score
   * @param movies_file_path a path to the file of the movies
   * @return smart pointer to a RecommendationSystem which was created with
   * those movies
   */
  static std::unique_ptr<RecommendationSystem> create_rs_from_movies // maybe change to unique - changed
	  (const std::string &movies_file_path) noexcept (false);
};

#endif //RECOMMENDATIONSYSTEMLOADER_H
