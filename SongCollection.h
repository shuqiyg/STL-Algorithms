/* Workshop  7 - STL Algorithms
   Name: Shuqi Yang
   Std ID: 132162207
   Email: syang136@myseneca.ca
   Date: 07-15-2021
   -------------------------------------------------------
   I have done all the coding by myself and only copied the
   code that my professor provided to complete my workshops
   and assignments.
 */
#ifndef SONGCOLLECTION_H_
#define SONGCOLLECTION_H_
#include <vector>

namespace sdds {
	struct Song{
		std::string artist{};
		std::string title{};
		std::string album{};
		double m_price{};
		std::string release_year{};
		size_t length_song{};
	};
	class SongCollection {
		std::vector<Song> songs{};
		size_t numOfSongs{};
	public:
		SongCollection(const char*);
		void display(std::ostream& out) const;
		void sort(const char*);
		void cleanAlbum();
		bool inCollection(const char*) const;
		std::list<Song> getSongsForArtist(const char*) const;
	};
	std::ostream& operator << (std::ostream& out, const Song& theSong);
}
#endif
